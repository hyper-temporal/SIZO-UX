#include "rotation.h"
#include <cstdlib>
#include <cmath>


double Geometrie::angle(double cx, double cy ,double  mx,double  my) noexcept {
    if(mx == cx){
        if(my == cy){
            return 0.0;
        }
        if(my > cy){
            return 0.75 ;
        }else{
            return 0.25 ;
        }
    }
    if(my == cy){
        if(mx > cx){
            return 0.0 ;
        }else{
            return 0.5 ;
        }
    }
    double angle(0.0);
    double ca = std::abs(mx - cx);
    double co = std::abs(my - cy);
    if(ca!=0){
        angle = atan(co/ca);
    }
    if(mx > cx){
        if(my > cy){    //DB
            angle = (2.0*M_PI)-angle;
        }else{          //DH
        }
    }else{
        if(my < cy){    //GH
            angle = M_PI-angle;
        }else{          //GB
            angle += M_PI;
        }
    }
    return angle/(2*M_PI);
}


//static coupleXY coord(double cx, double cy , double r, double a){
//    coupleXY ret;
//    tan(a*M_PI)
//}
template<typename T>
double Geometrie::hypothenuse(T cx, T cy , T mx, T  my) noexcept {
    auto distx = (mx-cx);
    auto disty = (my-cy);
    return sqrt(distx*distx + disty*disty);
}

double Geometrie::distance(double cx, double cy , double mx, double  my)
 noexcept {
    return hypothenuse<double>(cx,cy,mx,my);
}

double Geometrie::valeurRotary(
        double cx,
        double cy,
        double mx,
        double my,
        bool sens,
        double deadvalue,
        double centre0) noexcept
{
    auto dv = std::abs(deadvalue);
    auto dv_2  =  dv/2.0;   
    double dist = 1.0-dv;

    double aL,aR;
//la plage de validité est de 0 a 1, de maniere continue
    aL = centre0 - dv_2;
    aR = centre0 + dv_2;
    if(aL < 0.0 ){aL +=1.0;}
    if(aR > 1.0 ){aR -=1.0;}
    auto a =  Geometrie::angle(cx,cy,mx,my);
    return valeurRotary(a,aL,aR,sens,dist,centre0);
}




double Geometrie::valeurRotary(
        double a,
        double aL,
        double aR,
        bool sens,
        double dist,
        double centre0
        ) noexcept
{
    if(a == aL){                //limites
        return 1.0;
    }
    else if(a == aR){
        return 0.0;
    }
    if(aL > aR){    //cas entre deux
        if(a < aR){
            return sens?1.0:0.0;
        }
        else if(a > aL){
            return sens?0.0:1.0;
        }
        else{
            return sens? (aL-a)/dist : (a-aR)/dist;
        }
    }else {
        if(a < aR && a > aL){
            if(a > centre0){
                return sens?1.0:0.0;
            }else{
                return sens?0.0:1.0;
            }
        }
        else{
            if(a < aR){  //portion entre le  0 et aL
                if(sens){
                    return (aL-a) / dist;
                }else{
                    return (1.0 -aR + a) / dist;
                }
            }else{  //cas le plus "simple"
                if(sens){
                    return (aL + 1.0 - a) / dist;
                }else{
                    return (a- aR) / dist;
                }
            }
        }
    }

}



