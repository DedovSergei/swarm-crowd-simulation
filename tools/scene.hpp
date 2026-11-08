#pragma once

// The venue the CPU-side checks sample (tools/plausibility.hpp, tools/stepup.hpp, test and tool code only): the
// baked terrace (the exact CPU sampler of stadium.sdf, sampleSDF_CPU) unless a
// seated venue is selected (its exact analytic distance, seated::sdf). Selected per run with scene::Select, from the thread
// that drives the run (the checks' OpenMP loops only read it).

#include <glm/glm.hpp>

#include <swarm/sdf.hpp>
#include <swarm/venue.hpp>

namespace swarm::scene {

inline const Venue*& selected() {
    static const Venue* v = nullptr;
    return v;
}

// The venue's field (the fence is separate: sdFence)
inline float sdf(glm::vec3 p) {
    const Venue* v = selected();
    return v && v->seated() ? seated::sdf(v->layout, p) : sampleSDF_CPU(p);
}

inline bool seatedSelected() { const Venue* v = selected(); return v && v->seated(); }

// Selects a venue for the lifetime of the object (the terrace: no selection)
struct Select {
    const Venue* prev;
    explicit Select(const Venue& v) : prev(selected()) { selected() = v.seated() ? &v : nullptr; }
    ~Select() { selected() = prev; }
    Select(const Select&) = delete;
    Select& operator=(const Select&) = delete;
};

} // namespace swarm::scene
