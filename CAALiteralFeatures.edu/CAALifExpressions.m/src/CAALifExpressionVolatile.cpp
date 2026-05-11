// COPYRIGHT DASSAULT SYSTEMES  1994 2002

#include <iostream.h>
#include "CAALifExpressionVolatile.h"

// System
#include "CATListOfCATUnicodeString.h"

// LiteralFeatures 
#include "CATICkeParmFactory.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParm.h"
#include "CATICkeRelationFactory.h"
#include "CATICkeFunctionFactory.h"
#include "CATICkeExpression.h"
#include "CATICkeFunction.h"
#include "CATCkeEvalContext.h"

// ================================================================
// 
// ABSTRACT
// --------
// 
// Illustrates how to create and evaluate simple expressions.
// Volatile parameters are literals that are not saved in any form. 
// Volatile expressions are also expressions that are not saved in any form.
// You can evaluate those expressions on volatile parameters.
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAALifExpressionVolatile
//  
//===========================================================================
//  Inheritance:
//  ------------
//         None
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CAALifExpressionVolatile
//
//===========================================================================

CATCke::Boolean CAALifExpressionVolatile()
{
	CATCke::Boolean ret = CATCke::False;

	  cout << endl<< endl<<"Volatile expression creation" << endl<<endl;
	  
	  //Simple type parameters
	  
	  // Create, display and read a parameter of integer type
	  // Parameter name is "intParam", parameter value is 2
	  CATICkeParmFactory_var spVolFactory = CATCkeGlobalFunctions::GetVolatileFactory();
	  CATICkeRelationFactory_var spVolRelFactory = spVolFactory; 

	  if( NULL_var != spVolFactory && NULL_var != spVolRelFactory)
	  {
		    cout << "creation of a set of volatile parameters " << endl;
			CATICkeParm_var spPp1 = spVolFactory->CreateReal ("realParam1",-2.0);

			CATICkeParm_var spPp12 = spVolFactory->CreateReal ("realParam2",1.0);
			CATICkeParm_var spPp13 = spVolFactory->CreateReal ("realParam3",2.0);
			CATICkeParm_var spPp14 = spVolFactory->CreateReal ("realParam4",3.0);
			CATICkeParm_var spPp2 = spVolFactory->CreateBoolean ("boolParam2",CATCke::True);
			CATICkeParm_var spPp3 = spVolFactory->CreateInteger ("intParam3",2);
			CATICkeParm_var spPp4 = spVolFactory->CreateString ("strParam4","Well ");
			CATICkeParm_var spPp4res = spVolFactory->CreateString ("strParam5","");
			CATICkeParm_var spRes = spVolFactory->CreateBoolean ("result",CATCke::True);


			cout<< "creation of an expression of type program"<<endl;
	        CATUnicodeString body (" if x > 0 \n");
			body.Append(" { \n");
			body.Append("    y = true \n");
			body.Append(" } \n");
            body.Append(" else \n");
			body.Append(" { \n");
			body.Append("    y = false \n");
			body.Append(" } \n");

      CATICkeExpression_var spExpProgram = spVolRelFactory->CreateProgram("MyProgram","","(x : #In Real , y : #Out Boolean) : VoidType ",body);

			cout<< "creation of an expression of type constraint"<<endl;
	    CATICkeExpression_var spExpConstraint = spVolRelFactory->CreateConstraint("MyConstraint","","(x : #In Integer) : VoidType ","x > 6");

			cout<< "creation of an expression of type functional"<<endl;
	    CATICkeExpression_var spExpFunctional = spVolRelFactory->CreateFunctionalExpression("MyFunctionalExpression","","(x : #In String) : String ","x+\"done\"");
			
      cout<< "creation of an expression of type functional"<<endl;
	    CATICkeExpression_var spExpFunctional2 = spVolRelFactory->CreateFunctionalExpression("MyFunctionalExpression2","","(x : #In Real , y : #In Real) : Real ","sin(x+y)");
			
      if(   NULL_var != spPp1 && NULL_var != spPp4res && NULL_var != spRes && NULL_var != spPp2 && NULL_var != spPp3 && NULL_var != spPp4 
            && NULL_var != spPp12 &&   NULL_var != spPp13 &&   NULL_var != spPp14
            &&  NULL_var != spExpProgram && NULL_var != spExpConstraint && NULL_var != spExpFunctional && NULL_var != spExpFunctional2 )
			{
				cout << "creation correct" << endl;
				if (spExpProgram->CanBeEvaluated () && spExpConstraint->CanBeEvaluated () && spExpFunctional->CanBeEvaluated () && spExpFunctional2->CanBeEvaluated () )
				{
					cout << "expressions valid syntax " << endl;
 
					CATICkeFunction_var spFuncProgram = spExpProgram;
					CATICkeFunction_var spFuncConstraint = spExpConstraint;
					CATICkeFunction_var spFuncFunctional = spExpFunctional;
					CATICkeFunction_var spFuncFunctional2 = spExpFunctional2;

					if ( NULL_var != spFuncProgram && NULL_var != spFuncConstraint && NULL_var != spFuncFunctional  && NULL_var != spFuncFunctional2)
					{
						// a list of parameters
						CATCkeListOf(Parm) iListOfParameters;

						// need of an evaluation context
						CATCkeEvalContext *pEC = CATCkeGlobalFunctions::GetFunctionFactory()->CreateEvaluationContext(NULL_var);
						
						cout << "Evaluation of the program " << endl;
						iListOfParameters.Append(spPp1);
						iListOfParameters.Append(spPp2);
						spFuncConstraint->Run(&iListOfParameters, NULL_var,pEC);
			
						cout << " value of output boolean :  " << spPp2->Value()->AsBoolean() << endl<<endl;
						
						cout << "Evaluation of the constraint " << endl;
						iListOfParameters.RemoveAll();
						iListOfParameters.Append(spPp3);
						spFuncConstraint->Run(&iListOfParameters, spRes, pEC);
			
						cout << " result of the constraint :  " << spRes->Value()->AsBoolean() << endl<<endl;

						cout << "Evaluation of the function " << endl;
						iListOfParameters.RemoveAll();
						iListOfParameters.Append(spPp4);
						spFuncFunctional->Run(&iListOfParameters, spPp4res, pEC);
						cout << " result of the output parameter : " << (spPp4res->Value()->AsString()).ConvertToChar() << endl<<endl;
						
                        cout << "Evaluation of the function sin(x+y)" << endl;
						iListOfParameters.RemoveAll();
						iListOfParameters.Append(spPp12);
						iListOfParameters.Append(spPp13);
						spFuncFunctional2->Run(&iListOfParameters, spPp14, pEC);
						cout << " result of the output parameter : " << (spPp14->Value()->AsReal()) << endl<<endl;
						
            delete pEC;
					}

					// everything's fine
					ret = CATCke::True;
				}
			}
	  }
	  return ret;
}

