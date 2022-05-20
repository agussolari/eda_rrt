#include "geometry.h"

/*  Returns a point in the direction of (p2 - p1) vector such that 
    the new point is within a DELTA distance of point1  */
Point stepNear(Point& p1, Point& p2, ftype DELTA) {
    if( (distance(p1, p2) - DELTA) <= EPS) 
        return p2 ; 
    else {
        ftype theta = atan2(p2.y - p1.y, p2.x - p1.x);
        return Point(p1.x + DELTA * cos(theta), p1.y + DELTA * sin(theta));
    }
}

// Return minimum distance between line segment vw and point p
ftype minimum_distance(Point v, Point w, Point p) {
  ftype l2 = distance(v, w);  l2 *= l2 ; // i.e. |w-v|^2 -  avoid a sqrt
  if (l2 < EPS) return distance(p, v);   // v == w case

  // Consider the line extending the segment, parameterized as v + t (w - v).
  // We find projection of point p onto the line. 
  // It falls where t = [(p-v) . (w-v)] / |w-v|^2
  // We clamp t from [0,1] to handle points outside the segment vw.
  const ftype t = max<ftype>(0.0, min<ftype>(1.0, dot(p - v, w - v) / l2));

  Point projection = v + t * (w - v);  // Projection falls on the segment
  return distance(p, projection);
}

/*  Return true if the given line segment intersects the circle whose center
    is at location */
bool checkCollision(Point lineFrom, Point lineTo, Point location, ftype radius)
{
	location += Point(radius, radius); // Adjust location from top-left corner to center coordinates 
    ftype ab2, acab, h2;
    Point ac = location - lineFrom;
    Point ab = lineTo - lineFrom;
    ab2 = dot(ab, ab); acab = dot(ac, ab);
    ftype t = acab / ab2;

    if (t < 0) t = 0;
    else if (t > 1) t = 1;

    Point h = ((ab * t) + lineFrom) - location;
    h2 = dot(h, h); 
    return (h2 <= (radius * radius));
}

// taken from stackoverflow: https://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
// this can be done in log(N) though
bool PointInPolygon(Point point, Polygon polygon) {
  vector<Point> points = polygon.getPoints();
  int i, j, nvert = points.size();
  bool c = false;

  for(i = 0, j = nvert - 1; i < nvert; j = i++) {
    if( ( (points[i].y >= point.y ) != (points[j].y >= point.y) ) &&
        (point.x <= (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
      )
      c = !c;
  }
  return c;
}

/*  Returns true if two line segments on the same line intersect.
    (a, b) denote the endpoints of first line segment and 
    (c, d) denotes the endpoints of the second lint segment */
bool intersectOnLine(ftype a, ftype b, ftype c, ftype d) {
    if ((a - b) > EPS) swap(a, b);
    if ((c - d) > EPS) swap(c, d);
    return max(a, c) <= min(b, d);
}

// Returns true if the two line segments (a, b) and (c, d) intersect 
bool check_intersection(const Point a, const Point b, const Point c, const Point d) {
    // Check if both line segments lie on the same line
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0) 
        return intersectOnLine(a.x, b.x, c.x, d.x) && intersectOnLine(a.y, b.y, c.y, d.y);

    // Check if a and b both lie on different side of line segment CD 
    // Similarly check for c and d to lie on different side of line segment AC 
    return sign(a.cross(b, c)) != sign(a.cross(b, d)) && sign(c.cross(d, a)) != sign(c.cross(d, b));
}

/*  Returns true if the given line segment represented by ba intersects with any
    side of the polygon */
bool lineSegmentIntersectsPolygon(Point a, Point b, Polygon& polygon) {
    // PQ is merely a point not enough distance for it be line segment
    if( a.distance(b) < EPS ) 
        return PointInPolygon( (a+b)/2.0, polygon); 

    int num = polygon.pointCnt ; 
    vector < Point > points = polygon.getPoints();
    for(int i = 0; i < num; i++) {
        int nxt = i+1; if(nxt == num) nxt = 0 ;
        if(check_intersection(a, b, points[i], points[nxt])) return true ; 
    }
    return false ; 
}