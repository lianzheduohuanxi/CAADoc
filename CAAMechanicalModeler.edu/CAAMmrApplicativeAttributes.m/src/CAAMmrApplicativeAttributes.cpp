// COPYRIGHT DASSAULT SYSTEMES 2006
//============================================================================================
// 
// Mission         : Set and get applicative attributes on a part sub element.
//                   Set and get a color that overload a part sub element
//
//
// Illustrates     : o Document loading in session 
//                   o Access to part within document
//                   o Retrieving BRepAccess of sub element (in this case : faces)
//                   o Set Colors on faces
//                   o Retrieving the overloaded color
//                   o Set applicative attributes on faces
//                   o Retrieving the applicative attributes
//                   o "save as" of the modified document
//
//==========================================================================
// How to execute :
//
//   mkrun -c "CAAMmrApplicativeAttributes  FileNameIn FileNameOut"
//
//   where    FileNameIn  : The complete name of a Part document
//            FileNameOut : The complete name to saveas FileNameIn                         
//
//   ex:
//
//   CAAMmrApplicativeAttributes $WSROOT/CAAMechanicalModeler.edu/InputData/CAAMmrApplicativeAttributesPart.CATPart
//                             PartModified.CATPart
//
//   In the current directory, PartModified.CATPart will be created
//
//============================================================================================

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATSessionServices.h"     // To Create,delete a session
#include "CATSession.h"
#include "CATDocumentServices.h" 
#include "CATInit.h"
#include "CATInterfaceEvents.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATLISTV_CATBaseUnknown.h"

// NewTopologicalObjects Framework
#include "CATBody.h"
#include "CATCell.h"
#include "CATIMfGeometryAccess.h"

// MechanicalModeler Framework
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"
#include "CATIShapeFeatureBody.h"
#include "CATIGeometricalElement.h"

//Part
#include "CATIPartRequest.h"
#include "CATIBodyRequest.h"

// MecModInterfaces Framework
#include "CATIBRepAccess.h"

// Visualization Framework
#include "CATIVisProperties.h"            // To change faces color
#include "CATVisPropertiesValues.h"

//ApplicativeAttributes
#include "CATMmrApplicativeAttributes.h"
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeRelationForwards.h"

//System
#include "CATBaseUnknown.h"
#include "CATCollec.h"

#include <iostream.h> 

int main(int iArgc,
         char **iArgv) 

{
  // return code
  int rcode = 0;

  //
  // 1- Checks number of arguments
  //
  if( 3!=iArgc )
  {
    cout <<"CAAMmrApplicativeAttributes FileNameIn FileNameOut" << endl;
    cout <<"Where FileNameIn is the complete path of a CATPart document" <<endl;
    cout <<" and FileNameOut, the complete path of the output document" <<endl;
    cout <<"For FileNameIn, you can use the following Part: " ;
    cout <<" $WSROOT/CAAMechanicalModeler.edu/InputData/CAAMmrApplicativeAttributesPart.CATPart"<< endl;
    return 1;
  }

  cout << "The CAAMmrApplicativeAttributes use case begins" << endl;

  //
  // 2- Creates the session
  //
  char *pSessionName = "Sample session";
  CATSession *pSession = NULL;
  HRESULT rc = Create_Session(pSessionName, pSession) ;
  if( FAILED(rc) )
  {
    cout << "can not open session" << endl;
    return 1 ;
  }

  //
  // 3- Loads the input document
  //
  CATDocument *pDoc = NULL;
  rc= CATDocumentServices::OpenDocument(iArgv[1], pDoc) ;

  if( FAILED(rc) )
  {
    cout <<"Error in opening the document: " << iArgv[1] << endl ;
    return 1;
  }
  cout <<"   " << iArgv[1] << " is opened" << endl;

  CATInit *pDocAsInit = NULL;
  rc= pDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit) ;
  if( FAILED(rc) )
  {
    cout << "Error, the document does not implement CATInit"<< endl;
    return 1;
  }

  //
  // 4- Gets root container of the document
  //
  CATIPrtContainer *pSpecContainer = NULL ;
  pSpecContainer = (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");

  pDocAsInit->Release();
  pDocAsInit = NULL ;

  if( NULL == pSpecContainer )
  {
    cout <<"Error, the root container is NULL" << endl;
    return 1;
  }

  //
  // 5- Retrieves the MechanicalPart of the document
  //
  CATIPrtPart_var spPart ( pSpecContainer->GetPart() );
  if ( NULL_var == spPart )
  {
    cout <<"Error, the MechanicalPart is NULL" << endl;
    return 1;
  }

  pSpecContainer->Release();
  pSpecContainer = NULL ;

  //
  //6 - Retrieves BRepAccess of all faces
  //

  //6 - 1 Retrieving the feature holding the result of the main body
  //
  //get the part
  CATBaseUnknown_var spMainPartBody ;
  CATLISTV(CATBaseUnknown_var) ListResult ;

  CATIPartRequest_var spPartRequest = spPart ;
  if ( NULL_var == spPartRequest )
  {
    cout <<"Error on CATIPartRequest" << endl;
    return 1;
  }
  
  //get the main tool
  rc = spPartRequest->GetMainBody("",spMainPartBody);
  if ( FAILED(rc) || ( NULL_var == spMainPartBody) )
  {
    cout <<"Error with GetMainBody" << endl;
    return 1;
  }

  //get its associated body
  CATIBodyRequest_var spMainPartBodyRequest = spMainPartBody;
  if ( NULL_var == spMainPartBodyRequest )
  {
    cout <<"Error, spMainPartBodyRequest is NULL" << endl;
    return 1;
  }

  //Retrieves the feature holding the result of the main body
  //It's the first element of the list returned by GetResults (CAA documentation)
  rc = spMainPartBodyRequest->GetResults( "", ListResult) ;
  if (!SUCCEEDED(rc) || 0>= ListResult.Size())
  {
    cout <<"Error with GetResults" << endl;
	  return 1;
  }
    
  CATIGeometricalElement_var spFeatureResultGeomElem = ListResult[1];
  if ( NULL_var == spFeatureResultGeomElem )
  {
    cout <<"Error, spFeatureResultGeomElem is NULL" << endl;
    return 1;
  }

  //retrieves its shape
  CATIShapeFeatureBody_var shapefeat = spFeatureResultGeomElem;
  if ( NULL_var == shapefeat )
  {
    cout <<"Error, the Shape Feature is NULL" << endl;
    return 1;
  }

  //retrieves the feature associated to the BodyOUT
  CATISpecObject_var FeatureSolid = shapefeat->GetResultOUT();
  if ( NULL_var == FeatureSolid )
  {
    cout <<"Error, the Feature Solid is NULL" << endl;
    return 1;
  }


  //6 - 2 retrieving its associated geometry
  //

  CATIMfGeometryAccess_var geoAccess = FeatureSolid;
  if (NULL_var == geoAccess)
  {
    cout <<"Error, the geometry access is NULL" << endl;
    return 1;
  }

  //6 - 3 retrieving BRepAccess from geometry
  //
  CATLISTV(CATBaseUnknown_var) breps;
  int nbfaces = geoAccess -> GetBReps(breps);
  if (0 == nbfaces)
  {
    cout<<"Error, there is no face associated to the geometry"<<endl;
    return 1;
  }
  
  CATLISTP(CATIBRepAccess) ListBreps;
	CATIBRepAccess * Brep = NULL;
  CATBaseUnknown * Unk = NULL;
    
	int compt = 1;
for(; compt <= nbfaces; compt++)
  {
		Unk = breps[compt];
    Brep = (CATIBRepAccess * )Unk;
    if (NULL != Brep)
    {
      Brep->AddRef();
      ListBreps.Append(Brep);
    }
	}
  breps.RemoveAll();
  nbfaces = ListBreps.Size();
  if (0 == nbfaces)
  {
    cout<<"Error, there is no face in the BRepAccess List"<<endl;
    return 1;
  }
  else
  {
    cout<<"There is(are) "<<nbfaces<<" face(s) on the part"<<endl;
  }

  //
  //7 - retrieving and displaying current faces colors
  //
  cout<<"--------------------------"<<endl;
  cout<<"Retrieving current colors"<<endl;
  CATListOfInt retrieveRed,retrieveGreen,retrieveBlue;
   
  rc = CATMmrApplicativeAttributes::GetColorsOnFaces( ListBreps, retrieveRed,retrieveGreen,retrieveBlue);
  if (E_FAIL == rc )
  {
    cout<<"Error, an error occured while retrieving current part colors"<<endl;
    return 1;
  }

  for (compt =1;compt<=nbfaces;compt++)
  {
    cout<<"for the "<<compt<<" face, associated color components are : R "<<retrieveRed[compt]<<" G "<<retrieveGreen[compt]<<" B "<<retrieveBlue[compt]<<endl;
  }

  //
  //8 - Setting a new Color on all faces
  //

  //we are to color the faces with different color according their position : three by three will have the same color
  cout<<"--------------------------"<<endl;
  cout<<"Setting new colors"<<endl;
  
  CATListOfInt newRed,newGreen,newBlue,FailedIndex;
  int x=0;
  for (compt = 1;compt<= nbfaces;compt++)
  {
    x = compt%3;
    int red(0),green(0),blue(0);
    if (1 == x)
      red = 255;
    if (2 == x)
      green = 255;
    if (0 == x)
      blue = 255;
    newRed.Append(red);
    newGreen.Append(green);
    newBlue.Append (blue);
    cout<<"Setting R "<<red<<" G "<<green<<" B "<<blue<<" on the "<<compt<<" face"<<endl;
  }

  rc = CATMmrApplicativeAttributes::SetColorsOnFaces(ListBreps,newRed,newGreen,newBlue,FailedIndex);
  if (E_FAIL == rc)
  {
    cout<<"Error, setting new color on faces failed for all faces"<<endl;
    return 1;
  }
  else if (S_FALSE == rc )
  {
    int nberrors = FailedIndex.Size();
    cout<<"Error, setting new color on faces fails for faces :";
    for (compt = 1;compt<= FailedIndex.Size(); compt++)
    {
      cout<<" "<<FailedIndex[compt];
    }
    cout<<endl;
  }
  else 
    cout<<"Colors successfully set on every faces"<<endl;
  //
  //9 - retrieving colors we have just set
  //
  cout<<"--------------------------"<<endl;
  cout<<"Retrieving new colors"<<endl;
  rc = CATMmrApplicativeAttributes::GetColorsOnFaces( ListBreps, retrieveRed,retrieveGreen,retrieveBlue);
  if (E_FAIL == rc )
  {
    cout<<"Error, an error occured while retrieving current part colors"<<endl;
    return 1;
  }

  for (compt =1;compt<=nbfaces;compt++)
  {
    cout<<"for the "<<compt<<" face, associated color components are : R "<<retrieveRed[compt]<<" G "<<retrieveGreen[compt]<<" B "<<retrieveBlue[compt]<<endl;
  }

  //
  //10 - Setting Applicative Attributes
  //

  //
  //10 - 1 creating new attributes 
  cout<<"--------------------------"<<endl;
  cout<<"Creating applicative attributes for different faces"<<endl;
  CATListOfCATUnicodeString **AttrNameListToSet = new CATListOfCATUnicodeString*[nbfaces];
	CATCkeListOfParm *AttrValueListToSet = new CATCkeListOfParm[nbfaces];
  CATICkeParmFactory_var factory = CATCkeGlobalFunctions::GetVolatileFactory();
  for (compt = 1;compt<= nbfaces;compt++)
  {
    cout<<"Creating ";
    x = compt%3;
    //for each face we create a new list of apllicative attributes
    //an applicative attribute is made of a Name and a value
    if (1 == x)
    {
      AttrNameListToSet [compt-1] = new CATListOfCATUnicodeString (3);
      AttrValueListToSet[compt-1]   = new CATLISTV(CATBaseUnknown_var)(3);

      //The first attribute will be the number of the face
      AttrNameListToSet [compt-1]->Append("FACE_NUMBER");
      CATICkeParm_var tempcke1 = factory -> CreateInteger ("FACE_NUMBER",compt);
      AttrValueListToSet[compt-1]->Append(tempcke1);
      
      cout<<" FACE_NUMBER with value "<<compt; 

      //the second will be the color
      AttrNameListToSet [compt-1]->Append("COLOR");
      CATICkeParm_var tempcke2 = factory -> CreateString ("COLOR","Red");
      AttrValueListToSet[compt-1]->Append(tempcke2);
      
      cout<<" COLOR with value Red";
      
      //the third is x
      AttrNameListToSet [compt-1]->Append("X");
      CATICkeParm_var tempcke3 = factory -> CreateReal ("X",x);
      AttrValueListToSet[compt-1]->Append(tempcke3);
      
      cout<<" X with value "<<x;
      cout<<" for face nb "<<compt<<endl;
    }
    else 
    //just to show you you can have different size of list
    {
      AttrNameListToSet [compt-1] = new CATListOfCATUnicodeString (2);
      AttrValueListToSet[compt-1]   = new CATLISTV(CATBaseUnknown_var)(2);

      //The first attribute will be the number of the face
      AttrNameListToSet [compt-1]->Append("FACE_NUMBER");
      CATICkeParm_var tempcke1 = factory -> CreateInteger ("FACE_NUMBER",compt);
      AttrValueListToSet[compt-1]->Append(tempcke1);

      cout<<" FACE_NUMBER with value "<<compt; 

      //the second will be the color
      AttrNameListToSet [compt-1]->Append("COLOR");
      if (2 == x)
      {
        CATICkeParm_var tempcke2 = factory -> CreateString ("COLOR","Green");
        AttrValueListToSet[compt-1]->Append(tempcke2);
        
        cout<<" COLOR with value Green";
      }
      if (0 == x)
      {
        CATICkeParm_var tempcke2 = factory -> CreateString ("COLOR","Blue");
        AttrValueListToSet[compt-1]->Append(tempcke2);
        
        cout<<" COLOR with value Blue";
      }

      cout<<" on face nb "<<compt<<endl;

    }
  }

  //10 - 2 Setting the applicative attributes
  cout<<endl<<"Setting applicative attributes on different faces"<<endl;
  FailedIndex.RemoveAll();
  rc=CATMmrApplicativeAttributes::SetAttributesOnFaces(ListBreps, AttrNameListToSet,AttrValueListToSet,FailedIndex);
  if (E_FAIL == rc)
  {
    cout<<"Error, we failed to set applicative attributes on all faces"<<endl;
  }
  else if (S_FALSE == rc)
  {
    int nberrors = FailedIndex.Size();
    cout<<"Error, setting applicative attriutes on faces fails for faces :";
    for (compt = 1;compt<= FailedIndex.Size(); compt++)
    {
      cout<<" "<<FailedIndex[compt];
    }
    cout<<endl;
  }
  else
  {
    cout<<"Applicative attributes successfully set"<<endl;
  }

  //10 - 3 cleaning
  for  (compt=1; compt<=nbfaces;compt++)
	{
		AttrNameListToSet[compt-1]->RemoveAll(); delete AttrNameListToSet[compt-1];  AttrNameListToSet[compt-1] = NULL;
		AttrValueListToSet[compt-1]->RemoveAll();delete AttrValueListToSet[compt-1]; AttrValueListToSet[compt-1] = NULL;
	}

	delete [] AttrNameListToSet; AttrNameListToSet = NULL;
	delete [] AttrValueListToSet;AttrValueListToSet = NULL;

  //
  //11 - Retrieving the applicative attributes we have just set
  //
  cout<<"--------------------------"<<endl;
  cout<<"Getting applicative attributes on faces"<<endl;
  //
  //11 - 1 Getting attributes
  CATListOfCATUnicodeString * AttributNameList = new CATListOfCATUnicodeString[nbfaces];
  CATCkeListOfParm  AttrValList = new CATListValCATBaseUnknown_var[nbfaces];
  rc = CATMmrApplicativeAttributes::GetAttributesOnFaces(ListBreps, AttributNameList, AttrValList );
  if (SUCCEEDED(rc))
  {
    CATListOfCATUnicodeString templiststring;
    CATListValCATBaseUnknown_var tempCke;
    for (compt=1;compt<=nbfaces;compt++)
    {
      //retrieve a list a position k (arrays start at position zero).
      templiststring =  (AttributNameList)[compt-1];
      tempCke = (AttrValList)[compt-1];

      int nbAttributes = templiststring.Size();
      int nbValues     = tempCke.Size();

      //the list must have the same size! If not, we jump to the next face
      if (nbAttributes != nbValues)
      {
        cout<<"Error on face "<<compt<<" : nbAttributes and nbValues are different"<<endl;
        continue;
      }
      else
      {
        cout<<"For face "<<compt<<" there is(are) "<<nbAttributes<<" attribute(s) that is(are) : "<<endl;
      }
      for (int i=1;i<=nbAttributes;i++)
      {
        cout<<"    - "<<templiststring[i].ConvertToChar()<<" = "<<((CATICkeParm_var)( tempCke[i] ))->Content().ConvertToChar()<<endl;
      }
      templiststring.RemoveAll();
      tempCke.RemoveAll();

    }
  }
  else if (E_FAIL == rc)
  {
    cout<<"Error, applicative attributes couldn't be retrieved"<<endl;
    return 1;
  }
  //
  //11 - 2 Cleaning List:
  int i = 0;
  for  (i=0; i < nbfaces;i++)
  {
    AttributNameList[i].RemoveAll();
    AttrValList[i].RemoveAll();
  }
  delete [] AttributNameList;	AttributNameList = NULL;
  delete [] AttrValList;	    AttrValList = NULL;

  for (i = 1;i<= nbfaces;i++)
  {
    Brep = ListBreps [i];
    if (NULL != Brep)
    {
      Brep->Release();
    }
  }
  ListBreps.RemoveAll();
  //
  // 12 - Saves the document
  //
  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs(*pDoc, iArgv[2]);
  if (S_OK == rc)
  {
    cout << "   The "<< iArgv[2] ;
    cout << " document contains the modified Part" << endl ;
  }
  else
  {
    cout << "Error in saving document "<< iArgv[2] << endl;
    return 1;
  }   

  //
  // 13 - Closes the document
  //
  rc = CATDocumentServices::Remove(*pDoc);
  if (FAILED(rc))
  {
    cout << "Error in closing document" << endl ;
    return 1;
  }
  pDoc = NULL ;

  //
  // 14 - Deletes all documents in session	
  //
  rc = Delete_Session(pSessionName);
  if (FAILED(rc))
  {
    cout << "Error in deleting session" << endl ;
    return 1;
  }  

  cout << "The CAAMmrApplicativeAttributes use case is ended" << endl;

  return 0;
}
