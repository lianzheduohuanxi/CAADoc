// COPYRIGHT DASSAULT SYSTEMES  1999
#include <iostream.h>

//CAALiteralFeatures headers
#include "CAALifDesignTableCreate.h"

// ObjectModelerBase
#include "CATIContainer.h"
#include "CATIPrtContainer.h"

// LiteralFeatures 
#include "CATICkeParmFactory.h"
#include "CATIDesignTable.h"
#include "CATICkeParm.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"
#include "CATISpecObject.h"

#include "CATLib.h"
#include "CATGetEnvValue.h"

// =============================================================================
//   Illustrates:
//     Creating a design table from an external file in txt format 
//     Adding automatically associations 
//     Adding one-by-one associations
//     Retrieving the list of associations
//     Displaying the current configuration
//     Setting the current configuration
// =============================================================================

CATCke::Boolean CAALifDesignTableCreate(CATIContainer_var cont, char* path)
{
 
  // Retrieve the literal factory 
  CATICkeParmFactory_var spFact = cont;

  // Create the parameters required
  // for the purpose of this sample 
  CATICkeParm_var spPp1 = spFact->CreateInteger ("Column1",0);
  CATICkeParm_var spPp2 = spFact->CreateReal ("r",0.0);
  CATICkeParm_var spPp3 = spFact->CreateString ("s","");
  CATICkeParm_var spPp4 = spFact->CreateBoolean ("b",CATCke::True);
  CATICkeParm_var spPp5 = spFact->CreateLength ("l",0);
  CATICkeParm_var spPp6 = spFact->CreateAngle ("a",0);

  if( spPp1 == NULL_var || spPp2 == NULL_var || spPp3 == NULL_var || spPp4 == NULL_var || spPp5 == NULL_var || spPp6 == NULL_var )
    {
      cout << "Problem when creating parameters." << endl;
      return CATCke::False;
    }

  // It is important (but not necessary) to aggregate those parameters especially in part context
  CATIPrtContainer_var spPrtCont = cont;
  CATIParmPublisher_var spPubroot = NULL_var;
  if (!!spPrtCont)
	  spPubroot = spPrtCont->GetPart();

  CATICkeFunctionFactory_var fact = CATCkeGlobalFunctions::GetFunctionFactory();
  CATISpecObject_var spParameterSet = NULL_var;
  if (!!fact)
 	spParameterSet = fact->GetCurrentSet(CATICkeFunctionFactory::Parameter,spPubroot,CATCke::True);
  if (!!spParameterSet)
  {
	CATIParmPublisher_var spParmPublisher = spParameterSet;
	if (!!spParmPublisher)
	{
		spParmPublisher->Append(spPp1);
		spParmPublisher->Append(spPp2);
		spParmPublisher->Append(spPp3);
		spParmPublisher->Append(spPp4);
		spParmPublisher->Append(spPp5);
		spParmPublisher->Append(spPp6);
	}
  }

  // Create a design table from the txt file specified below
  CATIDesignTable_var spDesign ;
    
  char file[300];
  strcpy(file, path);
  strcat(file, "/CAALifDesignTable00.txt");

  spDesign = spFact->CreateDesignTable("DesignTable.1", "Design table test", file);

  if(spDesign == NULL_var) {
    cout << "Unable to create design table." << endl;
    return CATCke::False;
  }

  // It is important (but not necessary) to aggregate those relations especially in part context
  CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,spPubroot,CATCke::True);
  if (!!spRelationSet)
  {
	CATIParmPublisher_var spParmPublisher = spRelationSet;
	if (!!spParmPublisher)
	{
		spParmPublisher->Append(spDesign);

	}
  }
  else
	  cout<< "on a pas le relationset"<< endl;

  // Create the list of parameters to be associated automatically with 
  // the design table columns  
  CATLISTV(CATBaseUnknown_var) list;
  list.Append(spPp1);

  // Associate automatically the parameters of the list which has been
  // declared above with the design table columns with the same name 
  spDesign->AutomaticAssociations(cont, NULL_var, &list);

  // Add new associations
  spDesign->AddAssociation("Column2", spPp2);
  spDesign->AddAssociation("Column3", spPp3);
  spDesign->AddAssociation("Column4", spPp4);
  spDesign->AddAssociation("Column5", spPp5); 
  cout<< spDesign->AddAssociation("Column16", spPp6) << endl;
  
  // Display the number of associations 
  cout << "The number of associations is: ";     
  cout << spDesign->Associations()->Size() << endl;

  // Display the current configuration 
  cout << "The current configuration is: " ;
  cout << spDesign->ConfigurationRow() << endl;
 
  // Set Configuration1 as current configuration
  // and display the active configuration
  spDesign->SetCurrentConfiguration(1); 
  cout << "The new current configuration is: " ;
  spDesign->SetCurrentConfiguration(1); 
  cout << spDesign->ConfigurationRow() << endl;

  // Check the output parameters                        
  cout << "Configuration1 parameter values" << endl;
  cout << (spPp1->Show()).ConvertToChar() << endl;
  cout << (spPp2->Show()).ConvertToChar() << endl;
  cout << (spPp3->Show()).ConvertToChar() << endl;
  cout << (spPp4->Show()).ConvertToChar() << endl;
  cout << (spPp5->Show()).ConvertToChar() << endl;
  cout << (spPp6->Show()).ConvertToChar() << endl;

  // Remove association with column4
  spDesign->RemoveAssociation("Column4");
  
  cout << "The number of associations after column4 is removed: ";     
  cout << spDesign->Associations()->Size() << endl;

  // Select Configuration2
  spDesign->SetCurrentConfiguration(2);

  cout << "Configuration2 parameter values" << endl;
  cout << (spPp1->Show()).ConvertToChar() << endl;
  cout << (spPp2->Show()).ConvertToChar() << endl;
  cout << (spPp3->Show()).ConvertToChar() << endl;
  cout << (spPp4->Show()).ConvertToChar() << endl;
  cout << (spPp5->Show()).ConvertToChar() << endl;
  cout << (spPp6->Show()).ConvertToChar() << endl;
  
  return CATCke::True;
}



