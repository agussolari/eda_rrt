#ifndef GEOMETRY_H    
#define GEOMETRY_H
// ^To make sure I don't declare any function more than once by including the header multiple times.

#include <cmath>
#include <vector>
using namespace std ; 

// Type of data type to be used for all calculations (Ex: long double)
#define ftype int

/*  NOTE: Most of the calculations are done using EPS as a factor of difference
    since double/long double doesn't store floating point values precisely (limited precision) */
const ftype EPS = 1e-6;

struct Point {
    ftype x, y;
    Point() {}
    Point(ftype x, ftype y): x(x), y(y) {}
    Point& operator+=(const Point &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    Point& operator-=(const Point &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    Point& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    Point& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    Point operator+(const Point &t) const {
        return Point(*this) += t;
    }
    Point operator-(const Point &t) const {
        return Point(*this) -= t;
    }
    Point operator*(ftype t) const {
        return Point(*this) *= t;
    }
    Point operator/(ftype t) const {
        return Point(*this) /= t;
    }
    ftype dot(const Point &t) const {
    	return (x*t.x + y*t.y); 
    }
    ftype cross(const Point& t) const { 
        return x * t.y - y * t.x;
    }
    ftype cross(const Point& a, const Point& b) const {
        return (a - *this).cross(b - *this); 
    }
    ftype distance(const Point &t) const {
    	const double x_diff = x - t.x, y_diff = y - t.y ; 
    	return sqrt(x_diff * x_diff + y_diff * y_diff);
    }
    Point steer(const Point& t, ftype DELTA) {
	    if(this->distance(t) < DELTA) {
	        return t ; 
	    }
	    else {
	        double theta = atan2(t.y - y, t.x - x);
	        return Point(x + DELTA * cos(theta), y + DELTA * sin(theta));
	    }
	}
    bool operator==(const Point& rhs) const
    {
        return fabs(x - rhs.x) < EPS and fabs(y - rhs.y) < EPS ; // or another approach as above
    }
};

inline Point operator*(ftype a, Point b) {
    return b * a;
}

inline ftype distance(Point& a, Point &b) {
	const ftype x_diff = a.x - b.x, y_diff = a.y - b.y ; 
	return sqrt(x_diff * x_diff + y_diff * y_diff);
}

inline ftype dot(Point a, Point b) {
	return (a.x*b.x + a.y*b.y);
}

inline ftype cross(Point a, Point b) {
    return (a.x*b.y - b.x*a.y); 
}

/*  Returns a point in the direction of (p2 - p1) vector such that 
    the new point is within a DELTA distance of point1  */
Point stepNear(Point& p1, Point& p2, ftype DELTA);

// Return minimum distance between line segment vw and point p
ftype minimum_distance(Point v, Point w, Point p);

struct Polygon {
	vector < Point > points ;  // Assumes clockwise/anti-clockwise points input 
    int pointCnt = 0 ; 

	void addPoint(const Point pnt) {
		points.push_back(pnt); pointCnt++ ;
	}
	vector < Point > getPoints() {
		return points ; 
	}
	bool pointInside(const Point point) { // Can be done in log(N)
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
};

/*  Return true if the given line segment intersects the circle whose center
    is at location */
bool checkCollision(Point lineFrom, Point lineTo, Point location, ftype radius);

// taken from stackoverflow: https://stackoverflow.com/questions/11716268/point-in-polygon-algorithm
// this can be done in log(N) though
bool PointInPolygon(Point point, Polygon polygon);

// helper function
inline int sign(const ftype x) { 
    return x >= 0 ? x ? 1 : 0 : -1; 
}

/*  Returns true if two line segments on the same line intersect.
    (a, b) denote the endpoints of first line segment and 
    (c, d) denotes the endpoints of the second lint segment */
bool intersectOnLine(ftype a, ftype b, ftype c, ftype d);

// Returns true if the two line segments (a, b) and (c, d) intersect 
bool check_intersection(const Point a, const Point b, const Point c, const Point d);

/*  Returns true if the given line segment represented by ba intersects with any
    side of the polygon */
bool lineSegmentIntersectsPolygon(Point a, Point b, Polygon& polygon);

#endif