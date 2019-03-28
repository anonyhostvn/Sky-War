#include "ControlEngine.h"

CoordVector Turning (CoordVector A , int TurningRate , int Dimension) {
    int a = A.CoordX , b = A.CoordY ; 
    double ab = sqrt(a * a + b * b) ; 
    CoordVector P1((b * TurningRate) / ab, (-a * TurningRate) / ab) , 
                P2((-b * TurningRate) / ab , (a * TurningRate) / ab) ;  

    // P1.print() ; // For debug  
    // P2.print() ; // For debug 

    int temp = A ^ P1 ; 
    if (Dimension == TurnLeft) {
        if (temp > 0) return P1 ; 
        // printf("return P2 \n") ; //For Degbug
        return P2 ; 
    } else {
        if (temp > 0) return P2 ; 
        return P1 ; 
    }
}