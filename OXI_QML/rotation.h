#ifndef ROTATION_H
#define ROTATION_H

#include <functional>

struct Geometrie
{

    static double angle(double cx, double cy , double mx, double my) noexcept ;
//    static coupleXY coord(double cx, double cy , double a);
    template<typename T>
    static double hypothenuse(T cx, T cy , T mx, T  my) noexcept ;

    static double distance(double cx, double cy , double mx, double  my) noexcept ;

    static double valeurRotary(double cx, double cy, double mx, double my, bool sens, double deadvalue, double centre0) noexcept ;
    static double valeurRotary(double a, double aL, double aR, bool sens, double dist, double centre0) noexcept ;

    struct Point{
        int x;
        int y;
    };

    static bool onSegment(Point p, Point q,Point r){
        if(
                q.x <= std::max(p.x,r.x) &&
                q.x >= std::min(p.x,r.x) &&
                q.y <= std::max(p.y,r.y) &&
                q.y >= std::min(p.y,r.y)
                )
            return true;
        return false;
    }
    int orientation(Point p, Point q,Point r){
        int val =
                (q.y - p.y) * (r.x - q.x) -
                (q.x - p.x) * (r.y - q.y) ;
        return (val == 0) ? 0 :  (val > 0) ? 1 : 2;
    }
    bool doIntersects(Point p1, Point q1,Point p2, Point q2){
        int o1 = orientation(p1,q1,p2);
        int o2 = orientation(p1,q1,q2);
        int o3 = orientation(p2,q2,p1);
        int o4 = orientation(p2,q2,q1);
        if(o1 != o2 && o3 != o4)
            return true;
        if(o1 ==0 && onSegment(p1,p2,q1))return true;
        if(o2 ==0 && onSegment(p1,q2,q1))return true;
        if(o3 ==0 && onSegment(p2,p1,q2))return true;
        if(o4 ==0 && onSegment(p2,q1,q2))return true;
        return false;
    }

};


#endif // ROTATION_H
