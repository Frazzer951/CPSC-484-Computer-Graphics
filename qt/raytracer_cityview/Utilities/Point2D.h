#ifndef __POINT_2D__
#define __POINT_2D__


//=====================================
// Point2D
//=====================================
//
struct Point2D {
public:
    Point2D () = default;
    Point2D (const float k) : x(k), y(k) { }
    Point2D (const float x1, const float y1) : x(x1), y(y1) { }

    Point2D(const Point2D& p) : x(p.x), y(p.y) { }
    Point2D& operator=(const Point2D& p) {
        if (this != &p) { x = p.x;  y = p.y; }
        return *this;
    }

    ~Point2D () { }


    Point2D	operator*(float k) { return Point2D(k * x, k * y); }


    float	x, y;
};




#endif


