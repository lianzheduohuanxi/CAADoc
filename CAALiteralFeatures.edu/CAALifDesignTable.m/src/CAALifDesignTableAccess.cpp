// COPYRIGHT DASSAULT SYSTEMES  1999

#include <iostream.h>

//CAALiteralFeatures headers
#include "CAALifDesignTableAccess.h"

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

//============================================================================
//  Illustrates:
//     Creating a design table from an external file in txt format 
//     Adding associations 
//     Displaying the names of the columns
//     Getting the column where a parameter is
//     Retrieving the parameter in a gievn column
//     Retrieving the value in a given cell
//============================================================================

CATCke::Boolean CAALifDesignTableAccess(CATIContainer_var cont, char* path)
{
  // Retrieve the literal factory 
  CATICkeParmFactory_var spFact = cont;

  // Create the parameters required
  // for the purpose of this sample 
  CATICkeParm_var spPp1 = spFact->CreateInteger ("Column1",0);
  CATICkeParm_var spPp2 = spFact->CreateReal ("Column2",0.0);
  CATICkeParm_var spPp3 = spFact->CreateString ("Column3","");
  CATICkeParm_var spPp4 = spFact->CreateBoolean ("Column4",CATCke::True);
  CATICkeParm_var spPp5 = spFact->CreateLength ("Column5",0);
  CATICkeParm_var spPp6 = spFact->CreateAngle ("Column6",0);


  // It is important (but not necessary) to aggregate those parameters especially in part context
  CATIPrtContainer_var spPrtCont = cont;
  CATIParmPublisher_var spPubroot = NULL_var;
  if (!!spPrtCont)
	  spPubroot = spPrtCont->GetPart();

  CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,spPubroot,CATCke::True);
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

  if(spDesign == NULL_var)
  {
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

  // Create the list of parameters to be associated automatically with 
  // the design table columns  
  CATLISTV(CATBaseUnknown_var) list;
  list.Append(spPp1);
  list.Append(spPp2);
  list.Append(spPp3);
  list.Append(spPp4);
  list.Append(spPp5);
  list.Append(spPp6);

  // Associate automatically the parameters of the list which has been
  // declared above with the design table columns with the same name 
  int nbAssoc = spDesign->AutomaticAssociations(cont, NULL_var, &list);
   
  // Display the table column names
  const CATListOfCATUnicodeString* pLass = spDesign->Associations();
  cout << "List of associations" << endl;
  for (int i=1 ; i <= pLass->Size() ; i++)
    {
     cout << ((*pLass)[i]).ConvertToChar() << endl;
    }
   
  if( nbAssoc != 6 )
  {
       cout << "Problem in associations. Verify parameters name in dt file." << endl;
       return CATCke::False;
  }
  // Display the column number of p2
  cout << (spPp2->Name()).ConvertToChar() << " is on column" ;
  cout << spDesign->ParameterColumn(spPp2) << endl;
 
  // Set Configuration2 as active 
  spDesign->SetCurrentConfiguration(2);  

  // Retrieve the parameter located in Column4
  CATUnicodeString  col4 = "Part1\\Column4";
  CATICkeParm_var spPar0 = spDesign->ColumnParameter(0,&col4);
  if( spPar0 == NULL_var)
  {
       cout << "Problem in retreiving a parameter bby its name." << endl;
       return CATCke::False;
  }
  cout << "The value of the parameter in Column4 is: " ; 
  cout << (spPar0->Show()).ConvertToChar() << endl;
   
  // Display the value in Col5/Row5 with unit 
  cout << "The parameter value(CellWithColumnType) in Column5 Row2 is: " ; 
  cout << (spDesign->CellWithColumnType(2,5)).ConvertToChar() << endl;
   
  // Display the value in Col5/Row2 as a double in MKS unit 
  cout << "The parameter value(CellAsDouble) in Column5 Row2 is: " ; 
  cout << spDesign->CellAsDouble(2,5) << endl;

  return CATCke::True;
}



