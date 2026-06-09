struct circle {
  ld cx, cy, r;
  circle(ld x = 0, ld y = 0, ld radius = 0) : cx(x), cy(y), r(radius) {}
};
circle circumcircle(const point &A, const point &B, const point &C) {
  ld x1 = A.x, y1 = A.y;
  ld x2 = B.x, y2 = B.y;
  ld x3 = C.x, y3 = C.y;
  ld D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
  if (D == 0) {
    // Collinear points, no circle
    return circle(0, 0, -1);
  }
  ld Ux = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
  ld Uy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;
  ld R = sqrt((Ux - x1) * (Ux - x1) + (Uy - y1) * (Uy - y1));
  return circle(Ux, Uy, R);
}