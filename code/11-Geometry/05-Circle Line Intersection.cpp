void circle_line() {
  double r, a, b, c; // ax + by + c = 0
  double cx, cy;  // circle center
  double c1 = c + a * cx + b * cy;
  double x0 = -a * c1 / (a * a + b * b);
  double y0 = -b * c1 / (a * a + b * b);
  if (c1 * c1 > r * r * (a * a + b * b) + EPS)
    cout << "no points" << endl;
  else if (abs(c1 * c1 - r * r * (a * a + b * b)) < EPS) {
    cout << "1 point" << endl;
    cout << x0 + cx << ' ' << y0 + cy << endl;
  } else {
    double d = r * r - c1 * c1 / (a * a + b * b);
    double mult = sqrt(d / (a * a + b * b));
    double ax = x0 + b * mult;
    double bx = x0 - b * mult;
    double ay = y0 - a * mult;
    double by = y0 + a * mult;
    cout << "2 points" << endl;
    cout << ax + cx << ' ' << ay + cy << endl;
    cout << bx + cx << ' ' << by + cy << endl;
  }
}