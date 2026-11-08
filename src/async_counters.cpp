#include <swarm/async_counters.hpp>

namespace swarm {

AsyncCounterReader::AsyncCounterReader(GLsizeiptr bytes, int ringSize) : slots_(size_t(ringSize)), bytes_(bytes), latest_(size_t(bytes), 0) {
    if (bytes <= 0 || ringSize < 2) throw std::invalid_argument("AsyncCounterReader: bytes > 0 and ringSize >= 2 required");
    for (Slot& s : slots_) {
        glGenBuffers(1, &s.buffer);
        glBindBuffer(GL_COPY_WRITE_BUFFER, s.buffer);
        // Written by the GL (a copy), read by the application: the readback hint
        glBufferData(GL_COPY_WRITE_BUFFER, bytes, nullptr, GL_STREAM_READ);
    }
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

AsyncCounterReader::~AsyncCounterReader() {
    for (Slot& s : slots_) {
        if (s.fence) glDeleteSync(s.fence);
        glDeleteBuffers(1, &s.buffer);
    }
}

bool AsyncCounterReader::capture(GLuint src, GLintptr srcOffset) {
    if (inFlight_ == int(slots_.size())) { ++skipped_; return false; }
    Slot& s = slots_[size_t(head_)];
    glMemoryBarrier(GL_BUFFER_UPDATE_BARRIER_BIT);   // shader writes to src before the copy reads it
    glBindBuffer(GL_COPY_READ_BUFFER, src);
    glBindBuffer(GL_COPY_WRITE_BUFFER, s.buffer);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, srcOffset, 0, bytes_);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    s.fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
    s.seq = ++capturedSeq_;
    head_ = (head_ + 1) % int(slots_.size());
    ++inFlight_;
    return true;
}

bool AsyncCounterReader::poll() {
    bool fresh = false;
    while (inFlight_ > 0) {
        Slot& s = slots_[size_t(oldest_)];
        // Timeout 0: returns at once. The flush bit submits the fence if it is still queued (no wait).
        const GLenum r = glClientWaitSync(s.fence, GL_SYNC_FLUSH_COMMANDS_BIT, 0);
        if (r != GL_ALREADY_SIGNALED && r != GL_CONDITION_SATISFIED) break;   // GL_TIMEOUT_EXPIRED (or GL_WAIT_FAILED): later
        glDeleteSync(s.fence);
        s.fence = nullptr;
        // The copy into this slot has completed, so reading it does not wait for the GPU
        glBindBuffer(GL_COPY_READ_BUFFER, s.buffer);
        glGetBufferSubData(GL_COPY_READ_BUFFER, 0, bytes_, latest_.data());
        glBindBuffer(GL_COPY_READ_BUFFER, 0);
        latestSeq_ = s.seq;
        fresh = true;
        oldest_ = (oldest_ + 1) % int(slots_.size());
        --inFlight_;
    }
    return fresh;
}

} // namespace swarm
