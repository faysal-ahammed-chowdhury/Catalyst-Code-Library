ld pointSegmentDistance( const point &A, const point &B, const point &P ) {
  ld dx = B.x - A.x;
  ld dy = B.y - A.y;
  if ( dx == 0 && dy == 0 )
    return sqrt((P.x - A.x) * (P.x - A.x) + (P.y - A.y) * (P.y - A.y));
  // projection t of P onto AB in [0,1]
  ld t = ((P.x - A.x) * dx + (P.y - A.y) * dy) / (dx * dx + dy * dy);
  if ( t < 0 ) t = 0;
  else if ( t > 1 ) t = 1;
  ld projX = A.x + t * dx;
  ld projY = A.y + t * dy;
  return sqrt((P.x - projX) * (P.x - projX) + (P.y - projY) * (P.y - projY));
}