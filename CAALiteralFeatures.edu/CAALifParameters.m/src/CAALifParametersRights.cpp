// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#include "CAALifParametersRights.h"
#include "CAALifServices.h"
#include <iostream.h>

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// LiteralFeatures
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATICkeRelation.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"

// =====================================================================================
//
// ABSTRACT
// --------
// 
// Illustrates how to:
//   * determine the access rights of a parameter
//   * set the access rights of a parameter
// Note: The access rights only become operative when the parameters are edited.
//       i.e. in the example below, we just show you how to proceed to manage the access
//        rights, but you can't check that they are really operative.
//
// ======================================================================================
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
//  CAALifParametersRights
//
//=========================================================================== 

CATCke::Boolean CAALifParametersRights (CATICkeParmFactory* ipFact, CAALifServices& iServices)
{
	if(NULL != ipFact)
	{
		CATIParmPublisher* piPublisher = NULL;
		HRESULT rc = iServices.CAALifRetrievePublisherFromCurrentDoc( &piPublisher );
		if (FAILED(rc) || piPublisher==NULL) 
		{
			cout << "ERROR in QueryInterface to retreive publisher from container" << endl << flush;
			return CATCke::False;
		}

		// Create two parameters
		CATICkeParm_var spPp1 = ipFact->CreateInteger ("intParam0",2);
		CATICkeParm_var spPp2 = ipFact->CreateInteger ("intParam1",2);

		if(NULL_var == spPp1 || NULL_var == spPp2)
		{
			piPublisher->Release();
			return CATCke::False;
		}

		piPublisher->Append(spPp1);      
		piPublisher->Append(spPp2);

		cout << "intParam0 value is: ";
		cout << spPp1->Show ().ConvertToChar() << endl;
		cout << "intParam1 value is: ";
		cout << spPp2->Show ().ConvertToChar() << endl;

		// Retrieve intParam0 access rights
		cout << "Default rights (3 expected - readOnly)" << endl;
		cout << int(spPp1->UserAccess ()) << endl;
		cout << "Default rights (0 expected)" << endl;
		cout << int(spPp1->IsReadOnly () ) << endl;

		// Modify the parameter intParam0 right access -> ReadOnly
		spPp1->SetUserAccess (CATICkeParm::ReadOnly);
		cout << "Default rights (1 expected)" << endl;
		cout << int(spPp1->IsReadOnly ()) << endl;

		// Create the p1 = 3 * p2 - 2 formula 
		CATCkeListOf(Parm) list;
		list.Append (spPp2);
		CATICkeRelation_var 
			spRel = ipFact->CreateFormula ("rel","","",spPp1,&list,"3*a1-2",NULL_var,CATCke::False);
		if( NULL_var !=	spRel)
		{
			// It is important (but not necessary) to aggregate those relations especially in part context
			CATIParmPublisher* piPublisher2 = NULL;
			rc = iServices.CAALifRetrievePublisherFromCurrentDoc( &piPublisher2 );
			if (FAILED(rc) || !piPublisher2)
			{
				cout << "ERROR in QueryInterface to retreive publisher from container" << endl << flush;
				return CATCke::False;
			}

			CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,piPublisher2,CATCke::True);
			if (!!spRelationSet)
			{
				CATIParmPublisher_var spParmPublisher = spRelationSet;
				if (!!spParmPublisher)
				{
					spParmPublisher->Append(spRel);
				}
			}

			// Test whether a relation has been created
			if ( spPp1->Relation() == spRel)
			{
				cout << " There is a relation " << endl;
			}
			else cout << "There is no relation on intParam0" << endl;

			piPublisher2->Release();
		}
		else
			cout << " No Relation created ";

		// Display intParam0 value
		cout << "intParam0 value is: " ;
		cout << spPp1->Value()->AsInteger() << endl;
		piPublisher->Release();
	}
	else
		return CATCke::False;
	return CATCke::True;
}
