// Problem: Pyramid-ICPC Dhaka 2023
// Given the surface area of a square base pyramid, Need to maximize volume.
double suface_area;
double fun(double square_area) {
  double base = sqrt(square_area);
  double triangle_area = suface_area - square_area;
  double per_triangle_area = triangle_area / 4;
  double triangle_height = (per_triangle_area * 2) / base;
  double x = base / 2;
  double height = sqrt((triangle_height * triangle_height) - (x * x));
  double volume = (base * base * height) / 3;
  if (x > triangle_height) volume = 0;
  return volume;
}
int32_t main() {
  cin >> suface_area;
  double l = 0, r = suface_area, ans = -1;
  int it = 100;
  while (it--) {
    double mid1 = l + (r - l) / 3;
    double mid2 = r - (r - l) / 3;
    double x = fun(mid1);
    double y = fun(mid2);
    if (x > y) {
      ans = x;
      r = mid2;
    }
    else l = mid1;
  }
}