#pragma once

// Physical capacity of a venue: its design capacity, its hard-body jam capacity, and the label every viewer,
// experiment and benchmark output carries for a crowd of N agents. Report metadata only: it never reaches the simulation
// (no N is forbidden; the benchmark stress points stay valid for performance).
//   N <= design:          "within design capacity"
//   design < N <= jam:    "above design capacity (N / design capacity = x)", and a console warning
//   N > jam:              "physically impossible (N / jam capacity = x)", and a console warning: that many hard bodies do
//                         not fit on the venue's floor at once, so the run's densities and overlaps are not physical

#include <swarm/sim_params.hpp>
#include <swarm/venue.hpp>

#include <cmath>
#include <cstdio>
#include <string>

namespace swarm::venue {

// Hexagonal packing of BODY_RADIUS_M disks (0.40 m bodies), the densest any floor holds: 1 / (2 sqrt(3) r^2) = 7.2169
// persons/m^2 (tools/plausibility.hpp uses it for the density ceiling)
inline const double HEX_PACKING_P_M2 = 1.0 / (2.0 * std::sqrt(3.0) * double(BODY_RADIUS_M) * double(BODY_RADIUS_M));

struct Capacity {
    const char* venue;
    int design;            // the crowd the venue is laid out for
    double occupiableM2;   // floor the agents can reach: the metric grid's walkable area minus closed-off floor
    int jam;               // round(occupiableM2 x HEX_PACKING_P_M2): no more hard bodies fit on that floor at once
};

// The terrace reference venue (stadium.obj, stadium.sdf). Design capacity: the reference crowd N = 4096 (the golden pins
// and the reference experiments). Occupiable floor: the 64 x 64 metric grid's
// walkable area, 3241.3 m^2 (metrics::computeMetricVenue), minus the pitch, 400.0 m^2, which no agent reaches (its fence has
// no gates): 2841.3 m^2 of treads, aisles, walkway, avenues, exit gaps and the rear platform behind the top row (reached
// up the aisles). test_gpu metrics.safety recomputes both values from stadium.sdf.
constexpr Capacity TERRACE{ "terrace", 4096, 2841.3, 20506 };

// A venue's capacity. The terrace: TERRACE. A seated venue: design capacity = its seat count; occupiable floor =
// the exact floor area the agents can reach (seated::areas: walkway, avenues, clearways, gangways, concourse and its exits,
// up to the outer wall's outer face where they leave); jam capacity = that area at hexagonal packing.
inline Capacity capacityOf(const Venue& v) {
    if (!v.seated()) return TERRACE;
    const double occupiable = seated::areas(v.layout).occupiable();
    return { v.name, int(seated::seats(v.layout).size()), occupiable, int(std::lround(occupiable * HEX_PACKING_P_M2)) };
}

enum class Load { WithinDesign, AboveDesign, PhysicallyImpossible };

inline Load load(int n, const Capacity& c = TERRACE) {
    return n > c.jam ? Load::PhysicallyImpossible : n > c.design ? Load::AboveDesign : Load::WithinDesign;
}

// The label for N agents (no commas: it goes into CSV fields as is)
inline std::string label(int n, const Capacity& c = TERRACE) {
    char b[96];
    switch (load(n, c)) {
    case Load::PhysicallyImpossible: std::snprintf(b, sizeof b, "physically impossible (N / jam capacity = %.2f)", double(n) / double(c.jam)); break;
    case Load::AboveDesign: std::snprintf(b, sizeof b, "above design capacity (N / design capacity = %.2f)", double(n) / double(c.design)); break;
    default: std::snprintf(b, sizeof b, "within design capacity"); break;
    }
    return b;
}

// The console warning for N above the design capacity ("" otherwise)
inline std::string warning(int n, const Capacity& c = TERRACE) {
    if (load(n, c) == Load::WithinDesign) return "";
    char b[256];
    std::snprintf(b, sizeof b, "WARNING: N = %d agents in the %s venue (design capacity %d, jam capacity %d): %s", n, c.venue, c.design, c.jam,
                  label(n, c).c_str());
    return b;
}

} // namespace swarm::venue
