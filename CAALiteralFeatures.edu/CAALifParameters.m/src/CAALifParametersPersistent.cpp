// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#include <iostream.h>
#include "CAALifParametersPersistent.h"

// ObjectModelerBase
#include "CATIContainer.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// System
#include "CATListOfCATUnicodeString.h"
#include "CATListOfDouble.h"

// LiteralFeatures
#include "CATICkeParmFactory.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParm.h"
#include "CATIParmAsStored.h"
#include "CATICkeFunctionFactory.h"
#include "CATICkeParameterSet.h"
#include "CATIParmManipulator.h"

// ===========================================================================
//
// ABSTRACT
// --------
// 
// Illustrates:
//   1 ) Simple type parameters (integer, real, string and boolean)
//       * creating simple type parameters
//       * retrieving and display their values
//       * modifying their values
//   2 ) Dimension type parameters (Length and Angle)
//       * creating, modifying - retrieving and displaying their values
//   3 ) Magnitude type parameters other than Length and Angle
//       * creating and modifying a volume
//
// ===========================================================================
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
//  CAALifParametersPersistent
//
//===========================================================================

CATCke::Boolean CAALifParametersPersistent(CATICkeParmFactory* ipFact, CAALifServices& iServices)
{
	CATCke::Boolean returnCode = CATCke::True;

	cout << endl<< endl<<"Persistent parameter creation" << endl<<endl;

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

		//Simple type parameters

		// Create, display and read a parameter of integer type
		// Parameter name is "intParam", parameter value is 2
		CATICkeParm_var spPp1 = ipFact->CreateInteger ("intParam",2);
		if( NULL_var != spPp1 )
		{
			piPublisher->Append(spPp1); 
			cout << spPp1->Name().ConvertToChar() << " value is: " << endl;
			cout << spPp1->Show().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
			cout << spPp1->Value()->AsInteger ()  << " (with CATICkeInst::AsInteger)" << endl;

			// Modify "intParm" 
			spPp1->Valuate (6);
			cout << spPp1->Name().ConvertToChar() << " new value is (6 expected): " << endl;
			cout << spPp1->Show ().ConvertToChar() << endl;
		}

		// Create, display and read a parameter of real type
		// Parameter name is "realParam", parameter value is 2.3
		CATICkeParm_var spPp2 = ipFact->CreateReal ("realParam",2.3);
		if( NULL_var != spPp2 )
		{
			piPublisher->Append(spPp2);
			cout << spPp2->Name().ConvertToChar() << " value is: " << endl;
			cout << spPp2->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
			cout << spPp2->Value()->AsReal ()      << " (with CATICkeInst::AsReal)" << endl;

			// Modify "realParam"
			spPp2->Valuate (6.8);
			cout << spPp2->Name().ConvertToChar() << " new value is (6.8 expected): " << endl;
			cout << spPp2->Show ().ConvertToChar() << endl;
		}

		// Create, display and read a parameter of string type
		// Parameter name is "stringParam", parameter value is "Bonjour"
		CATICkeParm_var spPp3 = ipFact->CreateString ("stringParam","Bonjour");
		if( NULL_var != spPp3 )
		{
			piPublisher->Append(spPp3);

			cout << spPp3->Name().ConvertToChar() << " value is: " << endl;
			cout << spPp3->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
			cout << spPp3->Value()->AsString ().ConvertToChar() << " (with CATICkeInst::AsString)" << endl;

			// Modify "stringParam"
			spPp3->Valuate ("Good Morning");
			cout << spPp3->Name().ConvertToChar() << " new value is (\"Good Morming\" expected): " << endl ;
			cout << spPp3->Show ().ConvertToChar() << endl;
		}

		// Create, display and read a parameter of boolean type
		CATICkeParm_var spPp4 = ipFact->CreateBoolean ("booleanParam",CATCke::True);
		if( NULL_var != spPp4 )
		{
			piPublisher->Append(spPp4);

			cout << spPp4->Name().ConvertToChar() << " value is: " << endl;
			cout << spPp4->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;

			cout << spPp4->Value()->AsBoolean () << " (with CATICkeInst::AsBoolean)" << endl;
			cout << spPp4->Value()->AsInteger () << " (with CATICkeInst::AsInteger)" << endl;
			cout << spPp4->Value()->AsString ().ConvertToChar() << " (with CATICkeInst::AsString)" << endl;

			// Modify "booleanParam"
			spPp4->Valuate (CATCke::False);
			cout << spPp4->Name().ConvertToChar() << " new value is (false expected): " << endl;
			cout << spPp4->Show ().ConvertToChar() << endl;
		}

		//Dimension type parameters (Length and Angle) 

		// Create and display a Length type parameter
		// Parameter name is "lengthParam", parameter value is 2
		CATICkeParm_var spPp5 = ipFact->CreateLength ("lengthParam",2);
		if( NULL_var != spPp5 )
		{
			piPublisher->Append(spPp5);

			cout << spPp5->Name().ConvertToChar() << " value in MKS unit is: " << endl;
			cout << spPp5->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
			cout << spPp5->Value()->AsReal () << " (with CATICkeInst::AsReal)" << endl;

			CATIParmAsStored_var spPps5 = spPp5;
			cout << spPps5->ValueStored() << " (with CATIParmAsStored::ValueStored (in mm)) " << endl;
		}

		// Create and display an Angle type parameter
		// Parameter name is "angleParam", parameter value is 3.1416
		CATICkeParm_var spPp6 = ipFact->CreateAngle ("angleParam",3.1416);
		if( NULL_var != spPp6 )
		{
			piPublisher->Append(spPp6);

			cout << spPp6->Name().ConvertToChar() << " value in MKS unit is: " << endl;
			cout << spPp6->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
			cout << spPp6->Value()->AsReal () <<" (with CATICkeInst::AsReal)" << endl;
		}

		CATIParmAsStored_var spPps6 = spPp6;
		if( NULL_var != spPps6 )
		{			
			int val = int(spPps6->ValueStored());
			cout << val << " (with CATIParmAsStored::ValueStored (in deg)) " << endl;
		}

		// Dimension type parameters others than Length and Angle

		// Create and display a Volume type parameter
		// Parameter name is "volumeParameter", parameter value is 20.5
		CATICkeParm_var spPp7 = ipFact->CreateDimension (CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),"volumeParam",20.5);
		if( NULL_var != spPp7 )
		{
			piPublisher->Append(spPp7);
			cout << spPp7->Name().ConvertToChar() << " value in MKS unit is: " << endl;
			cout << spPp7->Show().ConvertToChar() << " (with CATICkeParm::Show)"   << endl ;
			cout << spPp7->Value()->AsReal ()     << " (with CATICkeInst::AsReal)" << endl;
		}

		CATIParmAsStored_var spPps7 = spPp7;
		if( NULL_var != spPps7 )
		{
			cout << spPps7->ValueStored() << " (with CATIParmAsStored::ValueStored (in m3)) " << endl;

			// Modify volumeParm
			spPp7->Valuate (3);
			cout << spPp7->Name().ConvertToChar() << " new value is (3m3 expected): " << endl;
			cout << spPp7->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
			cout << spPps7->ValueStored() << " (with CATIParmAsStored::ValueStored (in m3)) " << endl;
		}


		// Create, display and read a parameter of real type with multiple values
		// Parameter name is "realParam", parameter value is 2.3
		CATICkeParm_var spPp9 = ipFact->CreateReal ("realParamWithListOfValues",2.3);
		if( NULL_var != spPp9 )
		{
			const CATListOfDouble* pListOfValues=NULL;

			piPublisher->Append(spPp9);
			cout << spPp9->Name().ConvertToChar() << " value is: " << endl;
			cout << spPp9->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
			cout << spPp9->Value()->AsReal ()      << " (with CATICkeInst::AsReal)" << endl;

			// Modify "realParam"
			CATIParmManipulator_var spMan = NULL_var;
			spPp9->SetManipulator( NULL_var );

			spMan = spPp9->CreateManipulator();

			if( NULL_var != spMan)
			{
				spMan->SetNbValues(3);
				spMan->SetValue(3.4);
				spMan->SetValue(5.6);
				spMan->SetValue(7.8);
			}
			pListOfValues = spMan->Values();
			if( pListOfValues != NULL )
			{
				cout << spPp9->Name().ConvertToChar() << ": " << pListOfValues->Size() << " values for realParamWithListOfValues: " << endl;

				for(int i = 1; i <= pListOfValues->Size(); i++)
				{
					cout << i << ": "<< (*pListOfValues)[i] << endl;	
				}
			}
		}

		piPublisher->Release(); 
		piPublisher = NULL;
	}
	else
		returnCode = CATCke::False;

	return returnCode;
}
