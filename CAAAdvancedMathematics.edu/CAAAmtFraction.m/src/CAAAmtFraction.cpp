//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//
// Sample code for : Geometric Modeler
// Mission         : Create user defined CATMathFunction
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return Codes 
//                   0- OK
//                   1- Null pointer       
//
// Programming     : A -  Create 2 polynomials F and G 
// steps             B -  Create the CATMathFunctionX representing the fraction F/G
//                   C -  Evaluate the fraction
//                   D -  Duplicate the fraction
//                   E -  Delete the initial fractions & operands
//                   F -  Evaluate the duplicated fraction                       
//
// How to run it   : CAAAmtFraction   
//         
// =============================================================================

#include <iostream.h>

// AdvancedMathematics
#include "CATMathFunctionX.h"
#include "CATMathPolynomX.h"

#include "CAAMyFract.h"

//  
int main(int    iArgc,   // Number of arguments (0) 
         char** iArgv)   // 
{
    int rc=0;
    int i = 0 ; 
    double val = 0.0 ;
    // 
    // -----------------------------------------------------------------------
    // 1 - Define the functions
    // -----------------------------------------------------------------------
    //
    CATMathFunctionX **  Functions1 = new CATMathFunctionX * [2];
    Functions1[0] = NULL;
    Functions1[1] = NULL;

    // Numerator
    double array1[2] = {1,2};                      // F(x) = 1 + 2x 
    Functions1[0] = new CATMathPolynomX(1,array1); // degree 1

    // Denominator
    double array2[2] = {2,1.5};                    // G(x) = 2 + 1.5x
    Functions1[1] = new CATMathPolynomX(1,array2); // degree 1
    //
    // -----------------------------------------------------------------------
    // 2 - Create the fraction
    // -----------------------------------------------------------------------
    //
    CAAMyFract * myFraction1 = new CAAMyFract(Functions1[0], Functions1[1]);
    if (NULL == myFraction1) return 1 ;

    // -----------------------------------------------------------------------
    // 3 - Evaluate the fraction
    // -----------------------------------------------------------------------
    //
    cout  << "Evaluate the fraction" << endl;
    val = 0.0 ; cout << " Value ["<<val <<"]="<<  myFraction1->Eval(val) << endl;
    val = 1.0 ; cout << " Value ["<<val <<"]="<<  myFraction1->Eval(val) << endl;
    val = 2.0 ; cout << " Value ["<<val <<"]="<<  myFraction1->Eval(val) << endl;

    // -----------------------------------------------------------------------
    // 4 - Duplicate the first fraction
    // -----------------------------------------------------------------------
    //
    CAAMyFract * myFraction2 = (CAAMyFract*)myFraction1->DeepDuplicate();
    if (NULL == myFraction2) {
		delete myFraction1;
		return 1 ;
	}

    if (Functions1)
	{
          if (Functions1[0])
          {
             delete Functions1[0];
             Functions1[0] = NULL;
          }
          if (Functions1[1])
          {
   		     delete Functions1[1];
             Functions1[1] = NULL;
          }
	  delete [] Functions1;
	  Functions1 = NULL;
	}
    // -----------------------------------------------------------------------
    // 6 - Evaluate the duplicated function
    //     The evaluation below is only possible because the DeepDuplicate 
    //     method has been implemented as a DeepDuplicate of both operands
    //     Otherwise -> Throw
    // -----------------------------------------------------------------------
    //
    cout  << "Evaluate the duplicated fraction" << endl;
    val = 0.0 ; cout << " Value ["<<val <<"]="<<  myFraction2->Eval(val) << endl;
    val = 1.0 ; cout << " Value ["<<val <<"]="<<  myFraction2->Eval(val) << endl;
    val = 2.0 ; cout << " Value ["<<val <<"]="<<  myFraction2->Eval(val) << endl;

	const CATMathFunctionX * Num = myFraction2->GetNumerator();
	const CATMathFunctionX * Den = myFraction2->GetDenominator();
	delete Num; Num = NULL;
	delete Den; Den = NULL;

    delete myFraction2 ;
	delete myFraction1;
	
       
    return (rc);
}
