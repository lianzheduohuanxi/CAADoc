//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
// Sample code for : Geometric Modeler
// Mission         : Use basic mathematical classes
//
// Type            : Batch program
// Inputs          : None
// Outputs         : the following cout:
//                   coordinates of the projected point : 8	16	0
//                   Eigen value number 1 : 0 eigen vector 0	0	-1
//                   Eigen value number 2 : 0 eigen vector -0.71824	0.695795	0
//                   Eigen value number 3 : 0 no associated eigen vector 
//
// Illustrates     : 1- use of points, vectors, lines, planes; use of overloaded operators
//                   2- matrix eigenvectors
//                   3- defining an axes system transformation 
//
// How to run it   : CAAMthBase 
//
//=============================================================================
// cout
#include <iostream.h>

// basic mathematics
#include "CATMathPoint.h"                // Mathematical point
#include "CATMathVector.h"               // Mathematical vector
#include "CATMathLine.h"                 // Mathematical line
#include "CATMath3x3Matrix.h"            // 3x3 Matrix         
#include "CATMathAxis.h"                 // Axis system
#include "CATMathTransformation.h"       // Tranformation in a 3D affine space

//-------------------------------------------------------------------------------
int main() // The return code of the main is null if the execution is OK, not null if some
           // problem has been detected
{
 int rc=0;
	
 //----------------------------------------------------------------------------
 // 1- use of basic mathematical classes
 //----------------------------------------------------------------------------
	
 CATMathPoint  O, A(20. ,10. ,0.) ; // Default constructor, O is (0.,0.,0.)
	
 CATMathVector u(10., 20. ,0.);
 u.Normalize();                     // Normalize u;
	
 // H: Orthogonal projection of A on the line (O,u): 
 // Use the overloaded operators 
 // A-O is a vector, (A-O)*u the dot product
 //
 CATMathVector OA = A - O ;
 CATMathPoint  H  = O + ( OA*u ) * u;
 
 // Computes the normal of the two vectors (A-O) and u: ^ is the cross product
 CATMathVector n  = OA ^ u;      
	
 //
 // Another way to project to get H: 
 // use the Project method of the CATMathLine class. 
 //
 CATMathLine   line(O,u);
 CATMathPoint  projection;
 line.Project( A , projection );
	 
 // Returns the distance between the two computed points. If non nul, its an error.
 //		
 if ( H.SquareDistanceTo( projection ) != 0.  ) return (1);
	
 // Outputs the coordinates of the projected points
 //
 double aCoord[3];
 H.GetCoord( aCoord );
 cout << "coordinates of the projected point : " 
      << aCoord[0] << "\t" 
      << aCoord[1] << "\t"
      << aCoord[2] << endl;

 //---------------------------------------------------------------------------- 
 // 2- Matrix eigenvectors
 //----------------------------------------------------------------------------

 // M=  0. 12.  13.
 //    21.  0.  23.
 //    31.  32.  0. 
 //	
 CATMath3x3Matrix M ( 0.,  0.,  0., 
                     21.,  0.,  0.,
                     31., 32.,  0.);
	
 // It is not invertible
 //
 CATMath3x3Matrix N;
 if ( TRUE==M.Inverse( N ) ) return (2); // just to test the method!
	
 // Retrieves the eigen vectors and values
 //
 int           nbValues;
 double	       aEigenValues [3];
 CATBoolean    aHasAssociatedVector[3];
 CATMathVector aEigenVectors[3];
 CATBoolean    isDiagonal;
	
 M.EigenVectors( nbValues , aEigenValues , aHasAssociatedVector , aEigenVectors , isDiagonal );
 for (int i = 0 ; i < nbValues ; i++ )
 {
   cout << "Eigen value number " << i+1 << " : " << aEigenValues[i];
   if (TRUE==aHasAssociatedVector[i]) 
	 {
     cout << " eigen vector "	<< aEigenVectors[i].GetX() << "\t"
          << aEigenVectors[i].GetY() << "\t"
          << aEigenVectors[i].GetZ() << endl;
	 }
   else
	 {
     cout << " no associated eigen vector " << endl;
	 }
		
 }

 //	----------------------------------------------------------------------------
 // 3- Transformation that moves any point M(x,y,z) in CATMathOIJK in a point TM(tx,ty,tz) in CATMathOIJK
 // such that the coordinates of M expressed in fromAxis are the same as the coordinates of
 // TM in toAxis. In this case for example, the transformation transforms the origin of fromAxis
 // to the origin of toAxis
 //----------------------------------------------------------------------------

 CATMathAxis fromAxis ( O , OA , u , CATMathK);   // by default, the non specified vectors are the canonical ones.
 CATMathAxis toAxis   ( A , u , H-A);
 CATMathTransformation transfo1( fromAxis, toAxis );

 CATMathPoint transfo1OfO = transfo1 * O; 
 if (transfo1OfO.DistanceTo( A ) > 1.e-15 ) return (3) ;

 // Now define the changement of coordinates from fromAxis to toAxis
 // the transformation is defined as the composition of two transformations as follows:
 CATMathTransformation transfo2 = CATMathTransformation ( toAxis,CATMathOIJK ) 
	                               * CATMathTransformation(  CATMathOIJK, fromAxis);

 // apply it on a point:

 CATMathPoint transfo2OfO = transfo2 * O; 



 if ( transfo2OfO.GetX()>0) return (4) ; // the first coordinate of O in fromAxis is negative in toAxis.
 if ( transfo2OfO.GetY()<0) return (4) ; // the second coordinate of O in fromAxis is positive in toAxis.


 return (0);
}


