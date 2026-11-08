# Venue L: analytic distance, exactness (Task 5.4 stage 2)

venue_probe exact | commit 03f06b747068f28c722980b9870da95c1d91036c (dirty 0) | Release | 2026-10-11 12:13

100000 random points (seed 7): x, y uniform over |x|, |y| <= 93.21 m, z uniform from 0.5 m below to 1.5 m above the floor there. Brute force: 13736 solid primitives (seated::primitives, unfolded) and the ground half-space, double precision.

## CPU mirror (seated::sdf) vs brute force

- sign (solid iff z <= floorHeight vs the primitive list): 0 disagreements of 100000
- outside the solid (75057 points): max |sdf - brute force| = 8.14e-08 model units (2.54e-06 m), limit 1e-6: PASS
- inside the solid (24943 points): the ball of radius 0.999 |sdf| (64 directions) lies in the solid at 24943; the point moved |sdf| along the gradient leaves the solid within 1e-6 at 24943 (PASS: exact)
- Eikonal (central differences h = 1e-4 x max(1, |x|, |y|), at 57482 points away from kinks, |sdf| > 2h): max ||grad| - 1| = 3.54e-04 (limit 1e-3: PASS); max |finite differences - analytic gradient| = 3.97e-04
- cost: bands visited per evaluation median 3, max 9; cells evaluated median 8, p99 18, max 27 (of 196 bands, <= 6 cells each)
- wall query (seated::wall: the nearest vertical face reaching a point's horizontal plane; physics' clearWalls on S; points above ground): 53051 points outside every wall with one within 1.5 m: max |clearance - brute force| = 3.73e-09 (limit 1e-6: PASS); inside a wall at 20635; sign / reach disagreements 0

## GPU (physics.comp map / mapExactGrad / floorUnderReach on the venue preamble) vs the CPU mirror, 100000 points

- value: max |GPU - CPU| = 1.12e-07 (rounding level: GPU sqrt and division); map() vs mapExactGrad().w on the GPU: 0
- gradient (|sdf| > 1e-5): max |GPU - CPU| = 0.000607
- gradient: the largest differences are at points within ~1e-5 of the surface, where |q - p| is a few float steps (relative rounding)
- wall query (venueWall): max |GPU - CPU| clearance = 5.96e-08
- floor height (venueFloor): 100000 of 100000 bit-identical; floorUnderReach returns it (found or not found as its reach rule says: down 1.0 from a free centre, up BODY_RADIUS from one in solid) at 100000 (PASS)
