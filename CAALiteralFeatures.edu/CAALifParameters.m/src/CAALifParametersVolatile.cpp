// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#include <iostream.h>
#include "CAALifParametersVolatile.h"

// System
#include "CATListOfCATUnicodeString.h"

// LiteralFeatures 
#include "CATICkeParmFactory.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParm.h"

// ================================================================
// 
// ABSTRACT
// --------
// 
// Illustrates how to manage volatile parameters.
// Volatile parameters are literals that are not saved in any form. 
// Unlike persistent parameters, they cannot be retrieved when a document is unloaded. 
// Here are the parameter types examplified in this sample: 
//   1 ) Simple type parameters (integer, real, string and boolean)
//   2 ) Dimension type parameters (Length and Angle)
//   3 ) Magnitude type parameters other than Length and Angle
//   4 ) Enum type parameters (creating, reading and modifying)
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
//  CAALifParametersVolatile
//
//===========================================================================

CATCke::Boolean CAALifParametersVolatile()
{
	  cout << endl<< endl<<"Volatile parameter creation" << endl<<endl;
	  
	  //Simple type parameters
	  
	  // Create, display and read a parameter of integer type
	  // Parameter name is "intParam", parameter value is 2
	  CATICkeParmFactory_var spVolFactory = CATCkeGlobalFunctions::GetVolatileFactory();
	  CATICkeType_var spType = NULL_var;
	  CATICkeMagnitude* piMagnitude = NULL;
	  
	  if( NULL_var != spVolFactory )
	  {
			CATICkeParm_var spPp1 = spVolFactory->CreateInteger ("intParam",2);
			if( NULL_var != spPp1)
			{
				  cout << spPp1->Name().ConvertToChar() << " value is: " << endl;
				  spType = spPp1->Type();
				  if(spType != NULL_var )
				  {
						cout << " Type name is (CATICkeType::Name(): " << spType->Name().ConvertToChar() << endl;
						HRESULT rc = spType -> QueryInterface(IID_CATICkeMagnitude,
							  (void**) &piMagnitude);
						if (SUCCEEDED(rc)) 
						{	  
							  cout << " Magnitude name is (CATICkeMagnitude::Name): " << piMagnitude->Name().ConvertToChar() << endl;
						}
				  } 
				  cout << spPp1->Show().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
				  cout << spPp1->Value()->AsInteger ()  << " (with CATICkeInst::AsInteger)" << endl;
				  
				  // Modify "intParm" 
				  spPp1->Valuate (6);
				  cout << spPp1->Name().ConvertToChar() << " new value is (6 expected): " << endl;
				  cout << spPp1->Show ().ConvertToChar() << endl;
			}
			
			cout << endl;
			// Create, display and read a parameter of boolean type
			CATICkeParm_var spPp4 = spVolFactory->CreateBoolean ("booleanParam",CATCke::True);
			if( NULL_var != spPp4)
			{			
				  cout << spPp4->Name().ConvertToChar() << " value is: " << endl;
				  cout << spPp4->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
				  
				  cout << spPp4->Value()->AsBoolean () << " (with CATICkeInst::AsBoolean)" << endl;
				  cout << spPp4->Value()->AsInteger () << " (with CATICkeInst::AsInteger)" << endl;
				  cout << spPp4->Value()->AsString ().ConvertToChar() << " (with CATICkeInst::AsString)" << endl;
				  
				  // Modify "booleanParam"
				  spPp4->Valuate (CATCke::False);
				  cout << spPp4->Name().ConvertToChar() << " new value is (false expected): " << endl;
				  cout << spPp4->Show().ConvertToChar() << endl;
			}
			cout << endl;
			
			//Dimension type parameters (Length and Angle) 
			
			// Create and display a Length type parameter
			// Parameter name is "lengthParam", parameter value is 2
			CATICkeParm_var spPp5 = spVolFactory->CreateLength ("lengthParam",2);
			if( NULL_var != spPp5)
			{			
				  cout << spPp5->Name().ConvertToChar() << " value in MKS unit is: " << endl;
				  cout << spPp5->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
				  spType = spPp5->Type();
				  if(spType != NULL_var )
				  {
						cout << " Type name is (CATICkeType::Name(): " << spType->Name().ConvertToChar() << endl;
						HRESULT rc = spType -> QueryInterface(IID_CATICkeMagnitude,
							  (void**) &piMagnitude);
						if (SUCCEEDED(rc)) 
						{	  
							  cout << " Magnitude name is (CATICkeMagnitude::Name): " << piMagnitude->Name().ConvertToChar() << endl;
							   piMagnitude->Release();
						}
				  } 
				  cout << endl;
				  
				  // Create and display an Angle type parameter
				  // Parameter name is "angleParam", parameter value is 3.14
				  CATICkeParm_var spPp6 = spVolFactory->CreateAngle ("angleParam",3.14);
				  cout << spPp6->Name().ConvertToChar() << " value in MKS unit is: " << endl;
				  cout << spPp6->Show ().ConvertToChar() << " (with CATICkeParm::Show)" << endl ;
				  spType = spPp6->Type();
				  if(spType != NULL_var )
				  {
						cout << " Type name is (CATICkeType::Name(): " << spType->Name().ConvertToChar() << endl;
						HRESULT rc = spType -> QueryInterface(IID_CATICkeMagnitude,
							  (void**) &piMagnitude);
						if (SUCCEEDED(rc)) 
						{	  
							  cout << " Magnitude name is (CATICkeMagnitude::Name): " << piMagnitude->Name().ConvertToChar() << endl;
							  piMagnitude->Release();
						}
				  } 
				  cout << endl;
				  
			}
			
			//Dimension type parameters others than Length and Angle
			
			// Create and display a Volume type parameter
			// Parameter name is "volumeParameter", parameter value is 20.5
			CATICkeParm_var
				  spPp7 = spVolFactory->CreateDimension (CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),"volumeParam",20.5);
			if( NULL_var != spPp7)
			{			
				  cout << spPp7->Name().ConvertToChar() << " value in MKS unit is: " << endl;
				  cout << spPp7->Show().ConvertToChar() << " (with CATICkeParm::Show)"   << endl ;
				  spType = spPp7->Type();
				  if(spType != NULL_var )
				  {
						cout << " Type name is (CATICkeType::Name(): " << spType->Name().ConvertToChar() << endl;
						HRESULT rc = spType -> QueryInterface(IID_CATICkeMagnitude,
							  (void**) &piMagnitude);
						if (SUCCEEDED(rc)) 
						{	  
							  cout << " Magnitude name is (CATICkeMagnitude::Name): " << piMagnitude->Name().ConvertToChar() << endl;
							  piMagnitude->Release();
						}
				  }
				  cout << endl;
				  
			}
			
			//Create a literal from its type
			CATICkeParm_var spLast = spVolFactory->CreateLiteral (CATCkeGlobalFunctions::GetParmDictionary()->GetIntegerType(),"int0");
			if( NULL_var != spLast)
			{			
				  spLast->Valuate(5);
				  cout << spLast->Name().ConvertToChar() << " value is: " ;
				  cout << spLast->Value()->AsInteger() << endl;
				  
				  spLast = spVolFactory->CreateLiteral (CATCkeGlobalFunctions::GetParmDictionary()->GetBooleanType(),"bool0");
				  spLast->Valuate(CATCke::True);
				  cout << spLast->Name().ConvertToChar() << " value is: " ;
				  cout << spLast->Value()->AsBoolean() << endl;
			}
			cout << endl;
	  }

	//Enum type parameters 

	// Create, display and read an enum type parameter
	CATListOfCATUnicodeString lst;
	lst.Append("John");
	lst.Append("Emmanuel");
	lst.Append("Pierre");
	lst.Append("Frederic");

	// Create a new enumerated type (volatile)
	CATIEnumere_var spTypeEnumere = spVolFactory->CreateEnumereType("ListOfPeople",lst);  

	// Create the object of type "ListOfPeople" 
	// Pierre is the value assigned to the enum at creation
	CATICkeParm_var spPp8 = spVolFactory->CreateEnumere (spTypeEnumere,"ListOfPeople1","Pierre");
	if( NULL_var != spPp8 )
	{
		cout << spPp8->Show ().ConvertToChar() << endl;
		cout << spPp8->Value()->AsInteger () << endl;
		cout << spPp8->Value()->AsString ().ConvertToChar() << endl;

		// Modify "ListOfPeople1"
		spPp8->Valuate (1);
		cout << spPp8->Name().ConvertToChar() << " enum new value is (John): " << endl;
		cout << spPp8->Show().ConvertToChar() << endl;
		cout << spPp8->Name().ConvertToChar() << " enum new value is (Frederic): " << endl;
		spPp8->Valuate ("Frederic");
		cout << spPp8->Show ().ConvertToChar() << endl;
	}


	  return CATCke::True;
}

