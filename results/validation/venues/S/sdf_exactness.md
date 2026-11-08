# Venue S: analytic distance, exactness (Task 5.4 stage 2)

venue_probe exact | commit 34ce181213ce4c8dd3079f50c638860253835407 (dirty 0) | Release | 2026-10-08 18:17

100000 random points (seed 7): x, y uniform over |x|, |y| <= 30.81 m, z uniform from 0.5 m below to 1.5 m above the floor there. Brute force: 1432 solid primitives (seated::primitives, unfolded) and the ground half-space, double precision.

## CPU mirror (seated::sdf) vs brute force

- sign (solid iff z <= floorHeight vs the primitive list): 0 disagreements of 100000
- outside the solid (75057 points): max |sdf - brute force| = 1.48e-08 model units (4.63e-07 m), limit 1e-6: PASS
- inside the solid (24943 points): the ball of radius 0.999 |sdf| (64 directions) lies in the solid at 24943; the point moved |sdf| along the gradient leaves the solid within 1e-6 at 24943 (PASS: exact)
- Eikonal (central differences h = 1e-4, at 72773 points away from kinks, |sdf| > 2h): max ||grad| - 1| = 1.71e-04 (limit 1e-3: PASS); max |finite differences - analytic gradient| = 5.09e-04
- cost: bands visited per evaluation median 2, max 9; cells evaluated median 4, p99 15, max 24 (of 40 bands, <= 6 cells each)
- wall query (seated::wall: the nearest vertical face reaching a point's horizontal plane; physics' clearWalls on S; points above ground): 43062 points outside every wall with one within 1.5 m: max |clearance - brute force| = 3.52e-09 (limit 1e-6: PASS); inside a wall at 15143; sign / reach disagreements 0

## GPU (physics.comp map / mapExactGrad / floorUnderReach on the venue preamble) vs the CPU mirror, 100000 points

- value: max |GPU - CPU| = 5.4e-08 (rounding level: GPU sqrt and division); map() vs mapExactGrad().w on the GPU: 0
- gradient (|sdf| > 1e-5): max |GPU - CPU| = 0.000143
- gradient: the largest differences are at points within ~1e-5 of the surface, where |q - p| is a few float steps (relative rounding)
- wall query (venueWall): max |GPU - CPU| clearance = 5.96e-08
- floor height (venueFloor): 100000 of 100000 bit-identical; floorUnderReach returns it (found or not found as its reach rule says: down 1.0 from a free centre, up BODY_RADIUS from one in solid) at 100000 (PASS)
