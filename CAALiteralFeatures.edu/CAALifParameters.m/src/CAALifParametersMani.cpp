//COPYRIGHT DASSAULT SYSTEMES  19994 2000

#include "CAALifParametersMani.h"
#include <iostream.h>

// ObjectModelerBase
#include "CATIContainer.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// LiteralFeatures
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATIParmManipulator.h"
#include "CATIParmAsStored.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"

// =============================================================================
//
// ABSTRACT
// --------
// There exists two types of manipulators.
// - The first category, obtained through the CATICkeParmFactory factory
// is a run-time facility that is used by the Parameter frame (CATICkeParamFrame)
// in order to constrained the user to input values inside a given range.
// - The second category will definitely alter the parameter as persistent data.
// The range input using this second kind of manipulator is persistent.
//
// The first example illustrates how to associate a manipulator with a literal
// When you modify a parameter value, you use the use the up and down
// arrows to increment or decrement the amount to be specified. 
// This object which is made up of the up and down arrows is called a spinner.
// The object which describes how the spinner behaves is called a manipulator.
//
// The second example illustrates how to associate a manipulator with a literal
// such that any modification of the bounds will be persistent.
// =============================================================================
//  Usage:
//  ------
//  Type  CAALifParametersMain
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
//  CAALifParametersMani
//
//===========================================================================



CATCke::Boolean CAALifParametersMani (CATICkeParmFactory* ipFact, CAALifServices& iServices)
{
  CATCke::Boolean returnCode = CATCke::True;
  
  cout << endl<< endl<<"Parameter manipulator creation" << endl<<endl;


  //First retrieve the container in order to aggregate the parameters inside a 
  //parameter set. This can also be done through a parameter passed to the method.
  if(NULL != ipFact)
    { 
      HRESULT rc;
      CATIParmPublisher* piPublisher = NULL;
      rc = iServices.CAALifRetrievePublisherFromCurrentDoc( &piPublisher );
      if (FAILED(rc)) 
        {
          cout << "ERROR in QueryInterface to retreive publisher from container" << endl << flush;
          return CATCke::False;
        }
        
        
      CATIParmManipulator_var spMan = ipFact->CreateParmManipulator ();
      if( NULL_var != spMan)
        {
		  // Create the parameter to be linked with the manipulator 
          CATICkeParm_var spParm = ipFact->CreateLength ("paramLength",0);
          piPublisher->Append( spParm );

          // Associate the manipulator with "paramLength"
          spParm->SetManipulator (spMan);

          // Specify the manipulator range 
          spMan->SetAccurateRange (10,1,20,2);

          CATIParmAsStored_var spAsStored = spParm;
          if( NULL_var != spParm && NULL_var != spAsStored )
            {
              spAsStored->ValuateStored (15);
			
              // Test whether the value 10 could be assigned to "paramLength" 
              cout << "10 is authorized ?? (0 expected) " ;
              cout << spMan->TestValue(10) << endl; 
			
              // Test whether the value 21 could be assigned to "paramLength"
              cout << "21 is authorized ?? (2 expected) " ;
              cout << spMan->TestValue(21) << endl; 
			
              // Try and replace "paramLength" value with 10
              cout << "\"paramLength\" value is replaced with 10 " << endl;
              cout << "\"paramLength\" new value is:  " << endl;
              spAsStored->ValuateStored (10);
              cout << spAsStored->ValueStored() << endl;
			
              // Try and replace "paramLength" value with 21
              cout << "\"paramLength\" value is replaced with 20 " << endl;
              cout << "\"paramLength\" new value is:  " << endl;
              spAsStored->ValuateStored (21);
              cout << spAsStored->ValueStored() << endl<<endl;
            }
          else
            {
              returnCode = CATCke::False;
            }
        }    
      else
        returnCode = CATCke::False;
        piPublisher->Release();  
				piPublisher = NULL;         
     }
    else
      returnCode = CATCke::False;    
	  
  return returnCode;
}




CATCke::Boolean CAALifParametersPersistentMani (CATICkeParmFactory* ipFact, CAALifServices& iServices)
{
  CATCke::Boolean returnCode = CATCke::True;
  
  cout << endl<< endl<<"Parameter manipulator creation" << endl<<endl;


  //First retrieve the container in order to aggregate the parameters inside a 
  //parameter set. This can also be done through a parameter passed to the method.
  if(NULL != ipFact)
    { 
      HRESULT rc;
      CATIParmPublisher* piPublisher = NULL;
      rc = iServices.CAALifRetrievePublisherFromCurrentDoc( &piPublisher );
      if (FAILED(rc)) 
        {
          cout << "ERROR in QueryInterface to retreive publisher from container" << endl << flush;
          return CATCke::False;
        }
				
	  cout << endl<< endl<<"Parameter manipulator creation" << endl<<endl;
	  

	  CATIParmManipulator_var spMan = NULL_var;
      
	  
	  // Create the parameter to be linked with the manipulator 
	  CATICkeParm_var spParm = ipFact->CreateLength ("paramLength",0);
	  
	  // It is important (but not necessary) to aggregate those parameters especially in part context
	  CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,piPublisher,CATCke::True);
	  if (!!spParameterSet)
      {
	    CATIParmPublisher_var spParmPublisher = spParameterSet;
	    if (!!spParmPublisher)
	    {
		  spParmPublisher->Append(spParm);
	    }
      }
 
      // free any previously volatile assigned manipulator.
      spParm->SetManipulator( NULL_var );

      // create a new one.
      spMan = spParm->CreateManipulator();


	  if( NULL_var != spMan)
	  {
	  	 CATIParmAsStored_var spAsStored = spParm;
	  	 if( NULL_var != spParm && NULL_var != spAsStored )
	  	 {
				// Associate the manipulator with "paramLength"
				spParm->SetManipulator (spMan);
				
	  			// Specify the manipulator range 
	  			spMan->SetAccurateRange (10,1,20,2);

				 spAsStored->ValuateStored (15);

				 // Test whether the value 10 could be assigned to "paramLength" 
				 cout << "10 is authorized ?? (0 expected) " ;
				 cout << spMan->TestValue(10) << endl; 

				 // Test whether the value 21 could be assigned to "paramLength"
				 cout << "21 is authorized ?? (2 expected) " ;
				 cout << spMan->TestValue(21) << endl; 

				 // Try and replace "paramLength" value with 10
				 cout << "\"paramLength\" value is replaced with 10 " << endl;
				 cout << "\"paramLength\" new value is:  " << endl;
				 spAsStored->ValuateStored (10);
				 cout << spAsStored->ValueStored() << endl;

				 // Try and replace "paramLength" value with 21
				 cout << "\"paramLength\" value is replaced with 20 " << endl;
				 cout << "\"paramLength\" new value is:  " << endl;
				 spAsStored->ValuateStored (21);
				 cout << spAsStored->ValueStored() << endl<<endl;
	  	 }
	 }
	 else
			returnCode = CATCke::False;
	 
	 	piPublisher->Release(); 
    piPublisher = NULL;
	}

	  return returnCode;
}
