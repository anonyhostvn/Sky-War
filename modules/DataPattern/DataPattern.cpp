#include "DataConstance.h"
#include "DataStructure.h"

// template <typename _T>
// struct CoordVector {
//     PolarVector<_T> ConvertToPolar () {
//         PolarVector<_T> Res ; 

//         Res.SetR (Other.GetCoordX() * Other.GetCoordX() + Other.GetCoordY() * Other.GetCoordY()) ;
//         _T Phi = acos((float) Other.GetCoordX() / Res.GetR()) ; 
//         if (Other.GetCoordY() < 0) Phi = 2 * pii - Phi ; 

//         Res.SetPhi(Phi) ; 
//         return Res ; 
//     }
// }