/**
* @quickReview CRE 04:05:13
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//
// Sample code for : Geometric Modeler
// Mission         : Create composite laws
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return Codes 
//                   0- OK
//                   1- Null pointer       
//
// Illustrates     : A - Create a composite law with two degree-one polynoms
//                   B - Create a composite law with a user defined function
//
// How to run it   : CAAGobMakeLaws   
//         
// =============================================================================

#include <iostream.h>
//#include <iomanip.h>
//#include "fstream.h"

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory
#include "CATCGMContainerMngt.h"       // Management of the geometry factory
#include "CATCompositeLaw.h"  

// AdvancedMathematics
#include "CATMathFunctionX.h"
#include "CATMathPolynomX.h"

// User defined function
// *******************************************************************
class MyTrigoFunc : public CATMathFunctionX 
{
public:

    // It is mandatory to overwrite IsA, Eval, Duplicate and DeepDuplicate 
    // EvalFirstDeriv as well as other derivatives are not mandatory but
    // recommended for performances and accuracy. If not rewritten, a finite difference 
    // method is used to compute the derivatives.

    MyTrigoFunc(){}   // Mandatory
    ~MyTrigoFunc(){}
    CATMathClassId IsA() const { return "MyTrigoFunc"; } 
    double Eval(const double & t) const     {return cos( (CATPI /2 )*t); } 
    //double EvalFirstDeriv(const double & t) const { return sin( (CATPI /2 )*t); }
    CATMathFunctionX * Duplicate() const { return (CATMathFunctionX *) (new MyTrigoFunc()) ; }
    CATMathFunctionX * DeepDuplicate() const {  return (this)->Duplicate();}
};
// *******************************************************************
// 
//  
int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
       
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL==piGeomFactory) return (1);	
    //
    int i = 0 ; 
    double val = 0.0 ;
    //
    // -----------------------------------------------------------------------------
    // A - CREATE A COMPOSITE LAW with two degree-one polynoms
    //
    //     (a) - first polynom is F1(x) = 1 + 2x 
    //           definition interval  [ 0 , 0.5 ] 
    //     (b) - second polynom is F2(x) = 1.25 + 1.5x (this is your specification)
    //           definition  interval is [ 0.5 , 2 ]
    //  
    //      ***********************************************************************
    //      WARNING: in each interval of a composite law, the values are calculated
    //               from zero. Zero being the upper bound of the previous interval.
    //               If you expect a value of 2 for x = 0.5 and a slope of 1.5,
    //               you must specify 2 + 1.5x for F2(x)
    //      ***********************************************************************
    // -----------------------------------------------------------------------------
    //
    cout  << "Composite Law with two degree-one polynoms" << endl;
    int NbLaws1 = 2 ;                            // Number of laws

    // 1 - Define intervals
    //     
    double LimitParameters1 [3];                 // Intervals
    LimitParameters1[0] = 0;                     // lower bound of first interval
    LimitParameters1[1] = 0.5;                   // upper bound of first interval
    LimitParameters1[2] = 2;                     // upper bound of second interval

    // 2 - Define the functions
    // 
    CATMathFunctionX *ListOfFunctions1[2] = { NULL, NULL };
    double array1[2] = {1,2};      
    CATMathPolynomX P1(1,array1);
	ListOfFunctions1[0]=&P1;
	double array2[2] = {2,1.5};   
    CATMathPolynomX P2(1,array2);
	ListOfFunctions1[1]=&P2;

	// 3 - Create the composite law
	//
	CATCompositeLaw * compLaw1 = piGeomFactory->CreateCompositeLaw (2,LimitParameters1,
		(const CATMathFunctionX**)ListOfFunctions1);
	
    // 
    cout << " Nb of constraint parameters = " << compLaw1->GetNumberOfConstraintParameters () <<endl ;
    for (i = 0; i < compLaw1->GetNumberOfConstraintParameters () ; i++)
    {
        cout << " Constraint["<<i<<"]="<< compLaw1->GetOneConstraintParameter(i) << endl;
    }
    
    // 4 - Evaluate the composite law
    //
    cout  << "Evaluate the composite law" << endl;
    val = 0.00 ; 
    val = 0.0 ; cout << " Value ["<<val <<"]="<<  compLaw1->Eval(val) << endl;
    val = 0.5 ; cout << " Value ["<<val <<"]="<<  compLaw1->Eval(val) << endl;
    val = 1.0 ; cout << " Value ["<<val <<"]="<<  compLaw1->Eval(val) << endl;
    val = 2.0 ; cout << " Value ["<<val <<"]="<<  compLaw1->Eval(val) << endl;
   
    cout <<endl; 
    //
    // ----------------------------------------------------------------------------
    // B - CREATE A COMPOSITE LAW with one user defined function and a constant polynome
    //
    //     (a) - first law MyTrigoFunc
    //           definition interval  [ 0 , 1] 
    //     (b) - second law is a polynom  F2(x) = 0 
    //           definition  interval is [ 1 , 3 ]
    // ---------------------------------------------------------------------------- 
    //
    cout  << "Composite with a user defined function" << endl;
   
    // 1 - Define intervals
    //     
    int NbLaws2 = 2 ;
    double LimitParameters2 [3];                 // Intervals
    LimitParameters2[0] = 0;                     // lower bound of first interval
    LimitParameters2[1] = 1;                     // upper bound of first interval
    LimitParameters2[2] = 3;                     // upper bound of second interval
    
	 // 2 - Define the functions
    // 
    CATMathFunctionX *ListOfFunctions2[2] = { NULL, NULL };
    MyTrigoFunc * X = new MyTrigoFunc() ; 
	ListOfFunctions2[0] = (CATMathPolynomX *)X;
    double array[2] = {0};  
    CATMathPolynomX P3(0,array);
	ListOfFunctions2[1]=&P3;
	CATCompositeLaw * compLaw2 = piGeomFactory->CreateCompositeLaw (2,LimitParameters2,
		(const CATMathFunctionX**)ListOfFunctions2);

    cout << "Nb of constraint parameters = " << compLaw2->GetNumberOfConstraintParameters ()  << endl; 
    for (i = 0; i < compLaw2->GetNumberOfConstraintParameters(); i++)
    {
        cout << " Constraint["<<i<<"]="<<compLaw2->GetOneConstraintParameter(i) << endl;
    }

    // 4 - Evaluate the composite law
    //
    cout  << "Evaluate the composite law" << endl;
    val = 0.00 ; 
    val = 0.0 ; cout << " Value ["<<val <<"]="<<  compLaw2->Eval(val) << endl;
    val = 0.5 ; cout << " Value ["<<val <<"]="<<  compLaw2->Eval(val) << endl;
    val = 1.0 ; cout << " Value ["<<val <<"]="<<  compLaw2->Eval(val) << endl;
    val = 3.0 ; cout << " Value ["<<val <<"]="<<  compLaw2->Eval(val) << endl;
    
	delete X ; X = NULL;
      
  ::CATCloseCGMContainer(piGeomFactory);
     
    return (rc);
}
