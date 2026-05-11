// COPYRIGHT DASSAULT SYSTEMES  2000
//==========================================================================
//
//	Abstract: This sample shows how to apply graphic properties in using the
//            CATIVisProperties interface
//
//            The CAAProperty.CATPart is opened. This document is
//            located in the CAAGeometryVisualization/InputData directory.
//
//            This document contains 
//            
//                - Point.1   : a green point with a full square as symbol
//                - Line.1    : a white line with a solid line type (standard values)
//                - Extrude.1 : a surface (yellow faces)
//                - Sweep.2   : a surface (standard color faces)
//                - Extrude.2 : a hidden surface 
//
//            After the execution of this sample you have an output document 
//            CAAPropertyWithNewProperties.CATPart which contains the same
//            elements but with differents graphic properties:
//
//                - Point.1   : a red point with a cross as symbol
//                - Line.1    : a line not pickable and dashed 
//                - Extrude.1 : a surface with a standard surfacic color
//                - Sweep.2   : a transparency surface with red edges 
//                - Extrude.2 : a visible surface 
//
//  Steps :
//    1.   Opens the section 
//    2.   Opens the Part document
//    3.   Retrieves elements in the document
//      3.1 Retrieves the MechanicalPart
//      3.2 Retrieves the OpenBody1
//      3.3 Retrieves the five elements to modify
//    4.   Modifies the point
//    5.   Modifies the line
//    6.   Modifies the sweep
//    7.   Resets graphic properties
//    8.   Revisualizes the hidden surface
//    9.   Saves as the Part document
//    10.  Closes the Part document 
//    11.  Closes the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAGviApplyProperties InputPath [OutputPath]
//
//   with     InputPath   : $WSROOT/CAAGeometryVisualization.edu/InputData
//            OutputPath  : directory to save the part
//
//          
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, Save 
#include "CATInit.h"                     // To retrieve the root container
#include "CATDocument.h"

//MecModInterfaces Framework
#include "CATIPrtContainer.h"            // The root container of the Part document
#include "CATIPartRequest.h"             // To access to the OpenBody1

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // To get the MechanicalPart,and element of the OpenBody1
#include "CATIDescendants.h"             // To access to each element of the OpenBody1

// Visualization Framework
#include "CATIVisProperties.h"           // Access to graphic properties

// System Framework
#include "CATString.h"

// C++ Standard Library
#include <iostream.h>  

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

int main(int iArgc, char *iArgv[])        
		    
{

  //---------------------
  // 0- Checks arguments
  //---------------------
  if ((3 != iArgc) && ( 2 != iArgc) ) 
  {
     cout << endl;
     cout << "CAAGviApplyProperties InputPath  [OutputPart]"<< endl;
     cout << "with : InputPath        : $WSROOT/CAAGeometryVisualization.edu/InputData"<< endl;
     cout <<"        OutPutPath: Directory to save as the part document "<<endl;
     cout << endl;
     return 1;
  }

  cout << "The CAAGviApplyProperties main program begins ...."<< endl << endl;
  
  //------------------------------------------------------------------
  //1 - Creates Session
  // A session must always be created in a batch
  // environment.  Deleting the session at the end of the program is
  // also necessary.
  //------------------------------------------------------------------

  char * pSessionName = "CAA2_Sample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);
		                          
  if (FAILED(rc) )
  {
      cout << "ERROR in creating session" << endl ;
      return 1;
  }

  //---------------------------------
  //2- Opens the document CAAProperty
  //---------------------------------

  CATDocument *pPartDocument = NULL;
  CATString InputData = iArgv[1] ;
  CATString DocumentName  = InputData + Slash + "CAAProperty.CATPart";

  rc = CATDocumentServices::OpenDocument(DocumentName.ConvertToChar(), pPartDocument);
		                           
  if (SUCCEEDED(rc) )
  {
     cout << "Document "<< DocumentName.ConvertToChar() <<" opened OK" << endl ;
  }
  else
  {
     cout << "ERROR in opening the document= "<< DocumentName.ConvertToChar() << endl ;
     return 1;
  }

  //---------------------------------------------------
  // 3- Retrieves the elements of the document
  //---------------------------------------------------

  CATInit *pInitOnDoc = NULL ;
  rc = pPartDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
  if ( FAILED(rc) )
  {
     cout << "Problem with the CATInit interface"<< endl;
     return 1 ;
  }

  CATIPrtContainer *pIPrtCont = NULL ;
  pIPrtCont = (CATIPrtContainer*) pInitOnDoc->GetRootContainer("CATIPrtContainer");

  if ( NULL == pIPrtCont )
  {
     cout << "The root container is NULL"<< endl;
     return 1 ;
  }

  // No more need of this interface
  pInitOnDoc->Release();
  pInitOnDoc = NULL ;

  //
  // 3-1 Retrieves the MechanicalPart
  //
  CATISpecObject_var spPart = pIPrtCont->GetPart();

  if ( NULL_var == spPart )
  {
     cout << "The part is NULL"<< endl;
     return 1 ;
  }

  // No more need of this interface
  pIPrtCont->Release();
  pIPrtCont = NULL ;
  
  //
  // 3-2 Retrieves the OpenBody1
  //
  CATLISTV(CATBaseUnknown_var) surfBodies;  

  CATIPartRequest *pPartAsRequest = 0;
  rc = spPart->QueryInterface(IID_CATIPartRequest, (void**)&pPartAsRequest) ;

  if ( SUCCEEDED(rc) )
  {
     const CATUnicodeString stdContext(" "); // Sets the context for topo bodies lookup 
  	  
     // Extracts the lists of its surfacic mechanical bodies from the part ...
     pPartAsRequest->GetSurfBodies(stdContext, surfBodies);

     if ( (1 != surfBodies.Size()) && ( NULL_var != surfBodies[1]) )
     {
        cout << "The document "<< DocumentName.ConvertToChar() ;
        cout << " is not the original model"<< endl;
        return 1 ;
     }

     pPartAsRequest->Release();
     pPartAsRequest = NULL ;
  }else
  {
     cout << "Error in CATIPartRequest"<< endl;
     return 1 ;
  }
   
  CATIDescendants * pIDescendantOnOpenBody1 = NULL ;

  CATBaseUnknown_var spSurfBody = surfBodies[1];
  if(NULL_var == spSurfBody)
  {
    rc = E_FAIL;
  }
  else
  {  
    rc = spSurfBody->QueryInterface(IID_CATIDescendants, (void**)&pIDescendantOnOpenBody1) ;
  }

  if ( FAILED(rc) )
  {
      cout << "The document "<< DocumentName.ConvertToChar() << " is not the original model"<< endl;
      return 1 ;
  }
  
  int nbelt = pIDescendantOnOpenBody1->GetNumberOfChildren();
  if ( 20 != nbelt )
  {
      cout << "The document "<< DocumentName.ConvertToChar() << " is not the original model"<< endl;
      return 1 ;
  }

  //
  // 3-3 Retrieves the five elements to modify
  //

  // The point - Point.1
  CATISpecObject_var ThePoint = pIDescendantOnOpenBody1->GetChildAtPosition(1);

  // The line  - Line.1
  CATISpecObject_var TheLine = pIDescendantOnOpenBody1->GetChildAtPosition(8);

  // The yellow surface - Extrude.1
  CATISpecObject_var TheExtrude1Surface = pIDescendantOnOpenBody1->GetChildAtPosition(15);

  // The violet surface - Sweep.2
  CATISpecObject_var TheSweep2Surface = pIDescendantOnOpenBody1->GetChildAtPosition(10);

  // The hidden surface - Extrude.2 
  CATISpecObject_var TheExtrude2Surface = pIDescendantOnOpenBody1->GetChildAtPosition(20);

  if ( (NULL_var == ThePoint) || (NULL_var == TheLine) || (NULL_var == TheSweep2Surface) ||
       (NULL_var == TheExtrude1Surface) || (NULL_var == TheExtrude2Surface)  )
  {
      cout << "The document "<< DocumentName.ConvertToChar() ; 
      cout << " is not the original model"<< endl;
      return 1 ;
  }

  // No more need of this interface pointer
  pIDescendantOnOpenBody1->Release();
  pIDescendantOnOpenBody1 = NULL ;

  //---------------------------------------------------
  // 4-Modifies the point
  //---------------------------------------------------

  cout << endl << "Case of Point.1 ----------"<< endl << endl ;

  CATIVisProperties * pIPropertiesOnPoint = NULL ;
  rc = ThePoint->QueryInterface(IID_CATIVisProperties, (void**)&pIPropertiesOnPoint) ;
  if ( FAILED(rc) )
  {
      cout << "Error with the point"<< endl;
      return 1 ;
  }
  
  // Is the point green ?
  CATVisPropertiesValues               MyPropertyOnPoint ;
  CATVisPropertyType PropTypeOnPoint = CATVPColor ;
  CATVisGeomType GeomTypeOnPoint     = CATVPPoint ;

  rc = pIPropertiesOnPoint->GetPropertiesAtt(MyPropertyOnPoint,
	                                    PropTypeOnPoint,
                                            GeomTypeOnPoint);
  if ( rc == S_OK )
  {
     // The color of the point is not the standard
     unsigned int r,g,b ;
     MyPropertyOnPoint.GetColor(r,g,b);
     cout << "The color of Point.1 is not the standard color"<< endl ;
     cout << "Its color is  red= "<< r << " green="<< g << " blue=" << b << endl;

  }else
  {
     cout << "Error with the GetPropertiesAtt with the color point"<< endl;
     return 1;
  }

  // Is it a full square point ? 
  PropTypeOnPoint = CATVPSymbol;
  rc = pIPropertiesOnPoint->GetPropertiesAtt(MyPropertyOnPoint,
	                                    PropTypeOnPoint,
                                            GeomTypeOnPoint);

  if ( rc == S_OK )
  {
     // The symbol of the point is not the standard
     CATSymbolType symbol ;
     MyPropertyOnPoint.GetSymbolType(symbol);
     cout << "The symbol of Point.1 is not the standard symbol"<< endl ;
     if ( symbol == FULLSQUARE )
     {
        cout << "Its symbol is a FullSquare "<< endl;
     }else 
     {
        cout <<" The point should be a full square point" << endl;
        cout <<" The value is " << symbol << endl;
        return 1 ;
     }
  }else
  {
     cout << "Error with GetPropertiesAtt with the symbol point"<< endl;
     return 1;
  }

  // The point becomes red 
  PropTypeOnPoint = CATVPColor ;
  MyPropertyOnPoint.SetColor(255,0,0);
  rc = pIPropertiesOnPoint->SetPropertiesAtt(MyPropertyOnPoint,
                                                PropTypeOnPoint,
                                                GeomTypeOnPoint);
  if ( E_FAIL == rc )
  {
     return 1 ;
  }

  // The point becomes a cross 
  PropTypeOnPoint = CATVPSymbol ;
  MyPropertyOnPoint.SetSymbolType(CROSS);
  rc = pIPropertiesOnPoint->SetPropertiesAtt(MyPropertyOnPoint,
                                             PropTypeOnPoint,
                                             GeomTypeOnPoint);

  if ( E_FAIL == rc )
  {
      cout <<" Error with the SetPropertiesAtt on the point" << endl;
	  return 1 ;
  }

  cout << "The Point.1 is now red and its symbol is a cross"<< endl;

  // No more Need of this interface pointer
  pIPropertiesOnPoint->Release();
  pIPropertiesOnPoint = NULL;

  cout << endl << "End of the case of Point.1 ----------"<< endl << endl ;

  //---------------------------------------------------
  // 5-Modifies the line
  //---------------------------------------------------

  cout << endl << "Case of Line.1 ----------"<< endl << endl ;

  CATIVisProperties * pIPropertiesOnLine = NULL ;
  rc = TheLine->QueryInterface(IID_CATIVisProperties, (void**)&pIPropertiesOnLine) ;
  if ( FAILED(rc) )
  {
     cout << "Error with the line"<< endl;
     return 1 ;
  }
  
  // Verify that the line is not an edge
  CATVisGeomType TypeLine = CATVPLine;
  CATVisGeomType TypeEdge = CATVPEdge;
  HRESULT rc1 = pIPropertiesOnLine->IsGeomTypeDefined(TypeLine);
  HRESULT rc2 = pIPropertiesOnLine->IsGeomTypeDefined(TypeEdge);
  if ( SUCCEEDED(rc1) && FAILED(rc2) )
  {
     cout << "Line.1 is a line not an edge"<< endl;
  }else
  {
     cout << "Line.1 should be a line not an edge" << endl;
     return 1 ;
  }

  // Is the type of the line a standard value for this feature ?
  CATVisPropertiesValues MyPropertyOnLine ;
  CATVisPropertyType PropTypeOnLine = CATVPLineType ;
  CATVisGeomType GeomTypeOnLine = CATVPLine ;

  rc = pIPropertiesOnLine->GetPropertiesAtt(MyPropertyOnLine,
                                            PropTypeOnLine,
                                            GeomTypeOnLine);
  if ( S_AUTOMATIC  == rc )
  {
     cout << "The line type of Line.1 is the standard "<< endl ;
     rc = pIPropertiesOnLine->GetStandardProperties(MyPropertyOnLine,
                                                PropTypeOnLine,
                                                GeomTypeOnLine);
     if ( SUCCEEDED(rc) )
     {
        unsigned int linetype ;
        MyPropertyOnLine.GetLineType(linetype);
        if ( 1 == linetype )
        {
           cout << "For a GSM feature the standard line type is SOLID"<<endl ; 
        }else
        {
           cout << "For a GSM feature the standard line type is "<< linetype << endl ;
        }
     }
     
  }else
  {
     cout << "Error with GetPropertiesAtt with the color line"<< endl;
     return 1;
  }

  // Sets the dotted line type for the line .
  MyPropertyOnLine.SetLineType(2);
  rc = pIPropertiesOnLine->SetPropertiesAtt(MyPropertyOnLine,
                                            PropTypeOnLine,
                                            GeomTypeOnLine);
 
  if ( FAILED(rc) )
  {
     cout << "Error with the SetPropertiesAtt method on the line" << endl;
     return 1;
  }

  // Sets the line no pickable
  // If you open the output model in an interactive session,test that the 
  // line is not highlighted when you pass over it
  MyPropertyOnLine.SetPickAttr(CATNoPickAttr);
  
  // With this type of geometry you can define : show/pick and layer property
  GeomTypeOnLine = CATVPGlobalType ;
  PropTypeOnLine = CATVPPick ;
  rc = pIPropertiesOnLine->SetPropertiesAtt(MyPropertyOnLine,
                                            PropTypeOnLine,
                                            GeomTypeOnLine);
 
  if ( FAILED(rc) )
  {
     cout <<" Error with the SetPropertiesAtt on the line" << endl;
     return 1;
  }

  cout << "The  Line.1 is now not pickable and dashed"<<endl ;

  // No more Need of this interface pointer
  pIPropertiesOnLine->Release();
  pIPropertiesOnLine = NULL;

  cout << endl << "End of the case of Line.1 ----------"<< endl << endl ;

  //-----------------------------------------------------------
  // 6-Modifies the sweep
  //-----------------------------------------------------------

  cout << endl << "Case of Sweep.2 ----------"<< endl << endl ;

  CATIVisProperties * pIPropertiesOnSurface2 = NULL ;
  rc = TheSweep2Surface->QueryInterface(IID_CATIVisProperties, (void**)&pIPropertiesOnSurface2) ;
  if ( FAILED(rc) )
  {
     cout << "Error with the surface TheSweep2Surface"<< endl;
     return 1 ;
  }
  
  // Verify the type of properties for a surface 
  CATVisGeomType TypePoint = CATVPPoint;
  CATVisGeomType TypeMesh = CATVPMesh;
  CATVisGeomType TypeGlobal = CATVPGlobalType;

  HRESULT rc3 = pIPropertiesOnSurface2->IsGeomTypeDefined(TypePoint);
  HRESULT rc4 = pIPropertiesOnSurface2->IsGeomTypeDefined(TypeEdge);
  HRESULT rc5 = pIPropertiesOnSurface2->IsGeomTypeDefined(TypeMesh);
  HRESULT rc6 = pIPropertiesOnSurface2->IsGeomTypeDefined(TypeGlobal);

  cout << "In this application the surface has the following geometry types="  ;
  if ( SUCCEEDED(rc3) )
  {
     cout << " CATVPPoint, " ;
  }
  if ( SUCCEEDED(rc4) )
  {
     cout << " CATVPEdge, " ;
  }
  if ( SUCCEEDED(rc5) )
  {
     cout << " CATVPMesh, " ;
  }
  if ( SUCCEEDED(rc6) )
  {
     cout << " CATVPGlobalType, " ;
  }
  cout << endl;

  // Modifications for the edge geometry
  CATVisPropertiesValues MyPropertyOnSurface2 ;
  CATVisPropertyType PropTypeOnSurface2 = CATVPAllPropertyType ;
  CATVisGeomType GeomTypeOnSurface2     = CATVPEdge ;

  // Initializes the MyPropertyOnSurface2 value
  rc = pIPropertiesOnSurface2->GetPropertiesAtt(MyPropertyOnSurface2,
                                                PropTypeOnSurface2,
                                                GeomTypeOnSurface2);
  if ( FAILED(rc) )
  {
     cout << "Error with the surface Sweep.2"<< endl;
     return 1 ;
  }

  // we can change the color and the width of the edge of the surface
  MyPropertyOnSurface2.SetColor(230,0,0);
  MyPropertyOnSurface2.SetWidth(4);

  rc = pIPropertiesOnSurface2->SetPropertiesAtt(MyPropertyOnSurface2,
                                                PropTypeOnSurface2,
                                                GeomTypeOnSurface2);

  if ( FAILED(rc) )
  {
     cout << "Error with the surface Sweep.2"<< endl;
     return 1 ;
  }

  // Modifications for the mesh geometry
  PropTypeOnSurface2 = CATVPAllPropertyType ;
  GeomTypeOnSurface2 = CATVPMesh ;

  // Initializes the MyPropertyOnSurface2 value
  rc = pIPropertiesOnSurface2->GetPropertiesAtt(MyPropertyOnSurface2,
                                                PropTypeOnSurface2,
                                                GeomTypeOnSurface2);
  if ( FAILED(rc) )
  {
     cout << "Error with the surface Sweep.2"<< endl;
     return 1 ;
  }

  // we can change the color and the opacity of the surface
  MyPropertyOnSurface2.SetColor(0,0,20);
  MyPropertyOnSurface2.SetOpacity(50);

  rc = pIPropertiesOnSurface2->SetPropertiesAtt(MyPropertyOnSurface2,
                                                PropTypeOnSurface2,
                                                GeomTypeOnSurface2);

  if ( FAILED(rc) )
  {
     cout << "Error with the surface Sweep.2 "<< endl;
     return 1 ;
  }

  cout << "The surface Sweep.2 is now transparency blue, with large edge in red "<< endl ;
  
  // No more Need of this interface pointer
  pIPropertiesOnSurface2->Release();
  pIPropertiesOnSurface2 = NULL;

  cout << endl << "End of the case of Sweep.2 ----------"<< endl << endl ;

  //---------------------------------------------------
  // 7-Resets graphic properties
  //---------------------------------------------------

  cout << endl << "Case of Extrude.1 ----------"<< endl << endl ;

  CATIVisProperties * pIPropertiesOnSurface1 = NULL ;
  rc = TheExtrude1Surface->QueryInterface(IID_CATIVisProperties, (void**)&pIPropertiesOnSurface1) ;
  if ( FAILED(rc) )
  {
     cout << "Error with the surface TheExtrude1Surface"<< endl;
     return 1 ;
  }
  
  // Retrieves the color of the surface 
  CATVisPropertiesValues MyPropertyOnSurface1 ;
  CATVisPropertyType PropTypeOnSurface1 = CATVPColor ;
  CATVisGeomType GeomTypeOnSurface1     = CATVPMesh ;

  rc = pIPropertiesOnSurface1->GetPropertiesAtt(MyPropertyOnSurface1,
                                                PropTypeOnSurface1,
                                                GeomTypeOnSurface1);
  if ( S_OK == rc )
  {
     // The color of the surface is not the standard
     unsigned int r,g,b ;
     MyPropertyOnSurface1.GetColor(r,g,b);
     cout << "The surfacic color of Extrude.1 is not the standard color"<< endl ;
     cout << "Its surfacic color is  red= "<< r << " green="<< g << " blue=" << b << endl;      
  }else
  {
     cout << "Error in the model"<< endl;
     return 1 ;
  }

  // Resets the standard for all properties of the mesh geometry
  PropTypeOnSurface1     = CATVPAllPropertyType;
  GeomTypeOnSurface1     = CATVPMesh ;
  rc = pIPropertiesOnSurface1->ResetPropertiesAtt(PropTypeOnSurface1,GeomTypeOnSurface1);
  if ( FAILED(rc) )
  {
     cout << "Error with the surface Extrude.1 "<< endl;
     return 1 ;
  }									

  // Gets all properties of the  mesh geometry
  rc = pIPropertiesOnSurface1->GetPropertiesAtt(MyPropertyOnSurface1,
                                                PropTypeOnSurface1,
                                                GeomTypeOnSurface1);
  if ( SUCCEEDED(rc) )
  {
      cout << "The sufacic color of Extrude.1 is now the standard color"<< endl;
  }else
  {
     cout << "Problem with the Extrude.1 surface"<< endl;
     return 1 ;
  }

  // No more Need of this interface pointer
  pIPropertiesOnSurface1->Release();
  pIPropertiesOnSurface1 = NULL;

  cout << endl << "End of the case of Extrude.1 ----------"<< endl << endl ;

  //---------------------------------------------------
  // 8-Revisualizes the hidden extrude
  //---------------------------------------------------
  
  cout << endl << "Case of Extrude.2 ----------"<< endl << endl ;

  CATIVisProperties * pIPropertiesOnSurface3 = NULL ;
  rc = TheExtrude2Surface->QueryInterface(IID_CATIVisProperties, (void**)&pIPropertiesOnSurface3) ;
  if ( FAILED(rc) )
  {
     cout << "Error with the surface Extrude.2"<< endl;
     return 1 ;
  }

  // Revisualizes the hidden surface
  CATVisPropertiesValues MyPropertyOnSurface3 ;
  CATVisPropertyType PropTypeOnSurface3 = CATVPShow ;
  CATVisGeomType GeomTypeOnSurface3     = CATVPGlobalType ;
  MyPropertyOnSurface3.SetShowAttr(CATShowAttr);

  rc = pIPropertiesOnSurface3->SetPropertiesAtt(MyPropertyOnSurface3,
                                                PropTypeOnSurface3,
                                                GeomTypeOnSurface3);
  if ( FAILED(rc) )
  {
     cout << "Error with the surface Extrude.2"<< endl;
     return 1 ;
  }

  cout << "The Extrude.2 surface is now visible "<< endl ;

  // No more Need of this interface pointer
  pIPropertiesOnSurface3->Release();
  pIPropertiesOnSurface3 = NULL;

  cout << endl << "End of the case of Extrude.2 ----------"<< endl << endl ;

  //---------------------------------------------------------
  // 9- Saves the document 
  //---------------------------------------------------------

  CATString DocumentSavecName = "CAAPropertyWithNewProperties.CATPart" ;
  if ( 3 == iArgc )
  {
     CATString OutputPath = iArgv[2] ;
     DocumentSavecName = OutputPath + Slash + DocumentSavecName ;
  }

  rc = CATDocumentServices::SaveAs (*pPartDocument,DocumentSavecName.ConvertToChar());
  if (S_OK == rc) 
  {
     cout << endl << "The Document "<< DocumentSavecName.ConvertToChar() << " is saved OK" << endl ;
  }
  else
  {
     cout << "ERROR in saving document "<< DocumentSavecName.ConvertToChar() << endl ;
     return 1;
  }
  
  //---------------------------------------------------
  // 10- Closes document
  //---------------------------------------------------
 
  rc = CATDocumentServices::Remove (*pPartDocument);
  if (SUCCEEDED(rc)) 
  {
     cout << endl << "The Document "<< DocumentName.ConvertToChar() << " is closed OK" << endl ;
  }
  else
  {
     cout << "ERROR in closing document "<< DocumentName.ConvertToChar() << endl ;
     return 1;
  }
  pPartDocument = NULL ;


  //-------------------
  // 11- Delete session
  //-------------------

  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc)) 
  {
     cout << "ERROR in deleting session" << endl ;
     return 1;
  }  
	
  cout << "The CAAGviApplyProperties main program is ended."<< endl << endl;

  return 0;
}
