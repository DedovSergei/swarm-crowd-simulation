#pragma once

// Fence-gated asynchronous readback of small diagnostic counters. The rule: no
// readback may stall the pipeline; agent state is never read back in the application loop; small
// diagnostic counters (active count, exit counters, step) may be read once their fence has signalled,
// and the CPU never waits.
//
// A ring of small buffers: capture() queues a GPU-side copy of the counters into the next free slot
// followed by a fence; poll() checks the in-flight fences oldest first with glClientWaitSync and a
// timeout of 0 (it flushes, it never blocks) and reads every slot whose fence has signalled, so the
// copy it reads is complete and the read does not wait either. latest() is the newest data read, at
// most ringSize captures behind the newest capture. When every slot is in flight, capture() skips
// (it never waits for a slot) and counts the skip.

#include <glad/glad.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace swarm {

class AsyncCounterReader {
public:
    AsyncCounterReader(GLsizeiptr bytes, int ringSize = 4);
    ~AsyncCounterReader();
    AsyncCounterReader(const AsyncCounterReader&) = delete;
    AsyncCounterReader& operator=(const AsyncCounterReader&) = delete;

    // Queues a copy of src[srcOffset, srcOffset + bytes) into a free slot and fences it. Returns false
    // (and counts a skip) if every slot is still in flight. Never waits.
    bool capture(GLuint src, GLintptr srcOffset = 0);
    // Reads every in-flight slot whose fence has signalled, oldest first, and stops at the first one that
    // has not. Returns true if newer data became available. Never waits.
    bool poll();

    bool hasData() const { return latestSeq_ > 0; }
    const std::vector<unsigned char>& latest() const { return latest_; }
    template <class T> T latestAs() const {
        if (sizeof(T) > latest_.size()) throw std::logic_error("AsyncCounterReader::latestAs: type larger than the counters");
        T t;
        std::memcpy(&t, latest_.data(), sizeof(T));
        return t;
    }
    uint64_t latestSequence() const { return latestSeq_; }     // capture number of latest() (1 = first capture; 0 = none yet)
    uint64_t capturedSequence() const { return capturedSeq_; } // number of captures queued so far
    int inFlight() const { return inFlight_; }
    int ringSize() const { return int(slots_.size()); }
    uint64_t skipped() const { return skipped_; }

private:
    struct Slot { GLuint buffer = 0; GLsync fence = nullptr; uint64_t seq = 0; };
    std::vector<Slot> slots_;
    GLsizeiptr bytes_;
    int head_ = 0;       // next slot to fill
    int oldest_ = 0;     // oldest in-flight slot
    int inFlight_ = 0;
    uint64_t capturedSeq_ = 0, latestSeq_ = 0, skipped_ = 0;
    std::vector<unsigned char> latest_;
};

} // namespace swarm
