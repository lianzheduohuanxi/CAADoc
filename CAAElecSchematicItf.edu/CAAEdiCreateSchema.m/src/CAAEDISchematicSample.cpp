//
// COPYRIGHT DASSAULT SYSTEMES 2001
//

/***********************************************************************************/
/*                    CAAEDICreateSchema.m                                         */
/***********************************************************************************/

/*
Abstract :
--------
This sample illustrates the way to Create and Connect in-line Schematic entities.


                  ________                                  ________
                 |      __|__                            __|__      |
                 |     |  |  |__________________________|  |  |     |
                 |     |__|__|                          |__|__|     |
                 |________|                                |________|


  This sample:
  
    - 1. Prolog.

    - 2. Create Schematic Document

    - 3. Create the Equipment Reference

    - 4. Create the Socket Reference

    - 5. Create the Plug Reference

    - 6. Place the Components Twice

    - 7. Annotate the Components

    - 8. Assemble the Equipments and the Sockets and Connect the Plugs to the Sockets
                  
    - 9. Route a Cable Between Plugs
                    
    - 10.Epilog
                               
                                                
    Usage:
    ------
    To run this sample, you can use the command:
    mkrun -c "CAAEDISchematicSample outputName.CATProduct" 
    where outputName is the name of the document including the path where it is saved.

    * Return Errors:
    * -------------
    *
    *    1 - ERROR in Sample Input.
    *    2 - ERROR in creating an Object Modeler Session.
    *    3 - ERROR in changing interface from CATSession to CATISchSession.
    *    4 - ERROR in creating document.
    *    5 - ERROR in changing interface from CATDocument to CATIDftDocumentServices.
    *    6 - ERROR in getting the drawing.
    *    7 - ERROR in changing interface from CATIDrawing to CATISpecObject.
    *    8 - ERROR in getting the feature container.
    *    9 - ERROR in changing interface from CATIContainer to CATIDrwFactory.
    *   10 - ERROR in creating a detail sheet for the equipment to the document.
    *   11 - ERROR in creating a view for socket detail sheet.
    *   12 - ERROR in getting the view for the equipment detail sheet.
    *   13 - ERROR in setting the position of view of the equipment detail sheet.
    *   14 - ERROR in adding the view to the equipment detail sheet.
    *   15 - ERROR in changing interface from CATIView to CATI2DWFFactory.
    *   16 - ERROR in creating a 2d line.
    *   17 - ERROR in getting the CATISchAppObjectFactory.
    *   18 - ERROR in creating the equipment component.
    *   19 - ERROR in creating a IUnknown list.
    *   20 - ERROR in changing interface from CATIView to IUnknown.
    *   21 - ERROR in adding to list.
    *   22 - ERROR in getting schematic extension container.
    *   23 - ERROR in changing from CATIContainer to CATISchBaseFactory.
    *   24 - ERROR in creating the schematic object (linking the equipment to the graphical representation).
    *   25 - ERROR in changing interface from CATISchComponent to CATISchComponnector.
    *   26 - ERROR in adding a Wide Pin to the equipment.
    *   27 - ERROR in adding an Assembly Connector to the equipment.
    *   28 - ERROR in adding a detail sheet for the socket.
    *   29 - ERROR in creating a view for socket detail sheet.
    *   30 - ERROR in getting the view for the socket detail sheet.
    *   31 - ERROR in setting the position of view of the socket detail sheet.
    *   32 - ERROR in adding the view to the socket detail sheet.
    *   34 - ERROR in changing interface from CATIView to CATI2DWFFactory.
    *   35 - ERROR in creating a 2d line.
    *   36 - ERROR in creating the socket component.
    *   37 - ERROR in creating a IUnknown list.
    *   38 - ERROR in changing interface from CATIView to IUnknown.
    *   39 - ERROR in creating the schematic object (linking the socket to the graphical representation).
    *   40 - ERROR in changing interface from CATISchComponent to CATISchComponnector.
    *   41 - ERROR in adding a Wide Pin to the socket.
    *   42 - ERROR in adding an Mating Connector to the socket.
    *   43 - ERROR in adding an Assembly Connector to the socket.
    *   44 - ERROR in creating a detail sheet for the plug.
    *   45 - ERROR in creating a view for plug detail sheet.
    *   46 - ERROR in getting the view for plug detail sheet.
    *   47 - ERROR in setting the position of view of the plug detail sheet.
    *   48 - ERROR in adding the view to the plug detail sheet.
    *   50 - ERROR in changing interface from CATIView to CATI2DWFFactory.
    *   51 - ERROR in creating a 2d line.
    *   52 - ERROR in creating the plug component.
    *   53 - ERROR in creating a IUnknown list.
    *   54 - ERROR in changing interface from CATIView to IUnknown.
    *   55 - ERROR in adding to list.
    *   56 - ERROR in creating the schematic object (linking the plug to the graphical representation).
    *   57 - ERROR in changing interface from CATISchComponent to CATISchComponnector.
    *   58 - ERROR in adding a Wide Pin to the plug.
    *   59 - ERROR in adding an Mating Connector to the plug.
    *   60 - ERROR in getting the main sheet.
    *   61 - ERROR in placing first equipment on main sheet.
    *   62 - ERROR in placing second equipment on main sheet.
    *   63 - ERROR in placing first socket on main sheet.
    *   64 - ERROR in placing second socket on main sheet.
    *   65 - ERROR in placing first plug on main sheet.
    *   66 - ERROR in placing first plug on main sheet.
    *   67 - ERROR in getting the main view of the main sheet.
    *   68 - ERROR in creating first annotation.
    *   69 - ERROR in creating second annotation.
    *   70 - ERROR in QueryInterface on a CATISchAppConnectable from a CATISchComponent for the first equipment.
    *   71 - ERROR in creating a list to list the connectors on the equipments/socket/plug/...
    *   72 - ERROR in listing assembly connectors on the first equipment.
    *   73 - ERROR in counting connectors on the first equipment.
    *   74 - ERROR in reading the assembly connector of the first equipment from the list of connectors.
    *   75 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the assembly connector of the first equipment.
    *   76 - ERROR in QueryInterface on a CATISchAppConnectable from a CATISchComponent for the first socket.
    *   77 - ERROR in listing assembly connectors on the first socket.
    *   78 - ERROR in counting connectors on the first socket.
    *   79 - ERROR in reading the assembly connector of the first socket from the list of connectors.
    *   80 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the assembly connector of the first socket.
    *   81 - ERROR in connecting the first equipment to the first socket through an Assembly Connection.
    *   82 - ERROR in creating a list to list the connectors on the sockets.
    *   83 - ERROR in listing mating connectors on the first socket.
    *   84 - ERROR in reading the mating connector of the first socket from the list of connectors.
    *   85 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the mating connector of the first socket.
    *   86 - ERROR in QueryInterface on a CATISchAppConnectable from a CATISchComponent for the first plug.
    *   87 - ERROR in listing mating connectors on the first plug.
    *   88 - ERROR in counting connectors on the first plug.
    *   89 - ERROR in reading the mating connector of the first plug from the list of connectors.
    *   90 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the mating connector of the first plug.
    *   91 - ERROR in connecting first plug to first socket through a Mating Connection.
    *   92 - ERROR in QueryInterface on a CATISchAppConnectable from a CATISchComponent for the second equipment.
    *   93 - ERROR in listing assembly connectors on the second equipment.
    *   94 - ERROR in counting connectors on the second equipment.
    *   95 - ERROR in reading the assembly connector of the second equipment from the list of connectors.
    *   96 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the assembly connector of the second equipment.
    *   97 - ERROR in QueryInterface on a CATISchAppConnectable from a CATISchComponent for the second socket.
    *   98 - ERROR in listing assembly connectors on the second socket.
    *   99 - ERROR in counting connectors on the second socket.
    *  100 - ERROR in reading the assembly connector of the second socket from the list of connectors.
    *  101 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the assembly connector of the second socket.
    *  102 - ERROR in connecting the second equipment to the second socket through an Assembly Connection.
    *  103 - ERROR in listing mating connectors on the second socket.
    *  104 - ERROR in counting connectors on the second socket.
    *  105 - ERROR in reading the mating connector of the second socket from the list of connectors.
    *  106 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the mating connector of the second socket.
    *  107 - ERROR in QueryInterface on a CATISchAppConnectable from a CATISchComponent for the second plug.
    *  108 - ERROR in listing mating connectors on the second plug.
    *  109 - ERROR in counting connectors on the second plug.
    *  110 - ERROR in reading the mating connector of the second plug from the list of connectors.
    *  111 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the mating connector of the second plug.
    *  112 - ERROR in connecting second plug to second socket through a Mating Connection.
    *  113 - ERROR in creating a list to list the connectors on the plugs.
    *  114 - ERROR in listing wide pin connectors on the first plug.
    *  115 - ERROR in counting connectors on the first plug.
    *  116 - ERROR in reading the wide pin of the plug plug from the list of connectors.
    *  117 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the wipe pin of the first plug.
    *  118 - ERROR in listing wide pin connectors on the second plug.
    *  119 - ERROR in counting connectors on the second plug.
    *  120 - ERROR in reading the wide pin of the second plug from the list of connectors.
    *  121 - ERROR in QueryInterface on a CATISchAppConnector from a IUknown for the wipe pin of the second plug.
    *  122 - ERROR in creating the cable.
    *  123 - ERROR in creating the cable in the main sheet.
    *  124 - ERROR in reading the first extremity of the cable.
    *  125 - ERROR in reading the second extremity of the cable.
    *  126 - ERROR in connecting the first cable extremity to the wide pin of the first plug.
    *  127 - ERROR in connecting the second cable extremity to the wide pin of the second plug.
    *  128 - ERROR in Saving the Document. 
    *  129 - ERROR in Saving the Document. 
    /***********************************************************************************
*/
#include "CAAEdiSampleParameters.h"   // name the Electrical Schematic Objects

// System
#include "IUnknown.h"                 // IUnknown class definition
#include "CATICStringList.h"          // Add
#include "CATIUnknownList.h"          // Add, Count
#include "CATUnicodeString.h"         // CATUnicodeString class definition

// ObjectModelerBase Fw
#include "CATSession.h"               
#include "CATDocument.h"              // CATDocument class definition
#include "CATDocumentServices.h"      // SaveAs, Remove
#include "CATSessionServices.h"       // Create_Session, Delete_Session

// CATSchPlatformModeler Fw
#include "CATSchListServices.h"       // CreateCATIUnknownList, CreateCATICStringList
#include "CATISchBaseFactory.h"       // CreateSchComponent, CreateSchRouteByPoints
#include "CATISchAppObjectFactory2.h"  // AppCreateCompRef, AppCreateRoute
#include "CATISchAppConnector.h"      // CATISchAppConnector class definition
#include "CATISchAppConnectable.h"    // AppListConnectors, 
#include "CATISchCompConnector.h"     // AddConnector, AppConnect
#include "CATISchComponent.h"         // PlaceInSpace
#include "CATISchRoute.h"             // GetExtremityCntrs
#include "CATISchGRRComp.h"           // CATISchGRRComp class definition
#include "CATISchGRR.h"               // CATISchGRR class definition
#include "CATISchCntrLocation.h"      // GetPosition, GetAlignVector
#include "CATISchAppConnection.h"     // CATISchAppConnection class definition
#include "CATISchSession.h"           // CreateDocument, GetSchExtContainer

// DraftingInterfaces Fw
#include "CATIDftDocumentServices.h"  // GetDrawing
#include "CATIDrawing.h"              // AppendSheet, GetSheetList
#include "CATIDrwFactory.h"           // CreateSheet, CreateDetailWithMakeUp
#include "CATIDftViewMakeUp.h"        // GetView, SetPosition
#include "CATIView.h"                 // SetViewType
#include "CATISheet.h"                // SetCurrentView, SetAsDetail, AddView
#include "CATI2DWFFactory.h"          // CreateLine
#include "CATIDrwAnnotationFactory.h" // CreateDrwText
#include "CATIDrwText.h"              // CATIDrwText class definition

// ObjectSpecsModeler Fw
#include "CATISpecObject.h"           // GetFeatContainer
#include "CATLISTV_CATISpecObject.h"  // CATLISTV(CATISpecObject_var) definition
 
//=============================================================================
//   Main
//=============================================================================
int main (int argc, char **argv)
{
  HRESULT RC(S_OK);

  if(2 != argc) return 1;

  //---------------------------------------------------------------------------
  // 1 - Prolog
  //---------------------------------------------------------------------------
  char *pSessionIdent = "MySession";
  CATSession *piSession = NULL;
  ::Create_Session (pSessionIdent, piSession);
  if(NULL == piSession) return 2;

  //---------------------------------------------------------------------------
  // 2 - Create Schematic Document
  //---------------------------------------------------------------------------
  CATISchSession *piSchSession = NULL;
  RC = piSession->QueryInterface(IID_CATISchSession, (void **)&piSchSession);
  if(NULL == piSchSession) return 3;

  CATDocument *piSchemDoc = NULL;
  RC = piSchSession->CreateDocument("CATProduct", FALSE, &piSchemDoc);
  if(NULL == piSchemDoc) return 4;

  CATIDftDocumentServices *piDftDocServices = NULL;
  RC = piSchemDoc->QueryInterface(IID_CATIDftDocumentServices, (void **)&piDftDocServices);
  if(NULL == piDftDocServices) return 5;

  CATIDrawing *piDrawing = NULL;
  RC = piDftDocServices->GetDrawing(IID_CATIDrawing, (void **)&piDrawing);
  piDftDocServices->Release();
  piDftDocServices = NULL;
  if(NULL == piDrawing) return 6;
  
  // Gets the drawing container
  CATISpecObject_var spDrawingSpec = piDrawing;
  if(NULL_var == spDrawingSpec) return 7;

  CATIContainer_var spDrawingCont = spDrawingSpec->GetFeatContainer();
  if(NULL_var == spDrawingCont) return 8;
  
  // The drawing factory is implemented ont the drawing container
  CATIDrwFactory_var spDrwFact = spDrawingCont;
  if(NULL_var == spDrwFact) return 9;

  //---------------------------------------------------------------------------
  // 3 - Create the Equipment Reference
  //---------------------------------------------------------------------------
  // Create a sheet
  CATISheet *piEqtSheet = NULL;
  RC = spDrwFact->CreateSheet(IID_CATISheet, (void **)&piEqtSheet);
  if (NULL == piEqtSheet) return 10;

  // jsk 8/26/03 Migration
  /*
  // Add the sheet to the drawing
  piDrawing->AddSheet(piEqtSheet);
  // Activate this new sheet
  piDrawing->SetCurrentSheet(piEqtSheet);
  piEqtSheet->SetAsDetail();
  */
  piDrawing->AppendSheet(piEqtSheet, CATIDrawing::Detail, CATIDrawing::Current);
  // 

  // Create a view with Make Up
  CATIDftViewMakeUp *piEqtViewMU = NULL;
  RC = spDrwFact->CreateDetailWithMakeUp(IID_CATIDftViewMakeUp,(void **)&piEqtViewMU, 1);
  if (NULL == piEqtViewMU) return 11;
  
  // Get the view from the MakeUp
  CATIView *piEqtView = NULL; 
  RC = piEqtViewMU->GetView(&piEqtView);
  if (!piEqtView) return 12;
  
  // The view has to be typed: FrontView for Interactive view.  
  piEqtView->SetViewType(FrontView);
  RC = piEqtViewMU->SetPosition(100.0,50.0);
  if(FAILED(RC)) return 13;
  
  // Add the view to the sheet
  RC = piEqtSheet->AddView(piEqtViewMU);
  piEqtViewMU->Release();
  piEqtViewMU = NULL;
  if(FAILED(RC)) return 14;
  
  // Activate this new view
  CATIView_var spEqtView(piEqtView);
  piEqtSheet->SetCurrentView(piEqtView);
  piEqtSheet->Release();
  piEqtSheet = NULL;

  // get the graphical factory
  CATI2DWFFactory *piGeomEqtFactory = NULL;
  RC = piEqtView->QueryInterface(IID_CATI2DWFFactory, (void **)&piGeomEqtFactory);
  if(NULL == piGeomEqtFactory) return 15;

  // Creation of a square:
  double Pt1[2], Pt2[2], Pt3[2], Pt4[2];
  Pt1[0]=0.0;
  Pt1[1]=0.0;
  Pt2[0]=20.0;
  Pt2[1]=0.0;
  Pt3[0]=20.0;
  Pt3[1]=20.0;
  Pt4[0]=0.0;
  Pt4[1]=20.0;

  CATISpecObject_var spLine1 = piGeomEqtFactory->CreateLine(Pt1, Pt2);
  if(NULL_var == spLine1) return 16;
  CATISpecObject_var spLine2 = piGeomEqtFactory->CreateLine(Pt2, Pt3);
  if(NULL_var == spLine2) return 16;
  CATISpecObject_var spLine3 = piGeomEqtFactory->CreateLine(Pt3, Pt4);
  if(NULL_var == spLine3) return 16;
  CATISpecObject_var spLine4 = piGeomEqtFactory->CreateLine(Pt4, Pt1);
  piGeomEqtFactory->Release();
  piGeomEqtFactory = NULL;
  if(NULL_var == spLine4) return 16;

  // get the application factory
  CATISchAppObjectFactory2 *piAppFact = NULL;
  RC = piSchSession->GetSchObjInterface(SCHELEClass_Application, IID_CATISchAppObjectFactory2, (void **)&piAppFact);
  if(NULL == piAppFact) return 17;

  // create the applicative schematic component reference
  IUnknown *piCompoRef = NULL;
  RC= piAppFact->AppCreateCompRef(SCHELEClass_Equipment, NULL, &piCompoRef);
  if(NULL == piCompoRef) return 18;
  
  // creating the list of GRR associated to my component
  CATSchListServices list;
  CATIUnknownList *piLUK = NULL;
  RC = list.CreateCATIUnknownList(&piLUK);
  if(NULL == piLUK) return 19;
  
  IUnknown *piUK = NULL;
  RC = piEqtView->QueryInterface(IID_IUnknown, (void **)&piUK);
  piEqtView->Release();
  piEqtView = NULL;
  if(NULL == piUK) return 20;

  RC = piLUK->Add(0,piUK);
  piUK->Release();
  piUK = NULL;
  if (FAILED(RC)) return 21;
  
  // getting schematic extension container
  IUnknown *piSchExtCont = NULL;
  RC = piSchSession->GetSchExtContainer (piSchemDoc, &piSchExtCont);
  piSchSession->Release();
  piSchSession = NULL;
  if(NULL == piSchExtCont) return 22;

  CATISchBaseFactory *piBaseFact = NULL;
  RC = piSchExtCont->QueryInterface(IID_CATISchBaseFactory, (void **)&piBaseFact);
  piSchExtCont->Release();
  piSchExtCont = NULL;
  if(NULL == piBaseFact) return 23;
  
  // schematic ref. component creation
  CATISchComponent *piSchComp = NULL;
  RC = piBaseFact->CreateSchComponent(piCompoRef, piLUK, &piSchComp);
  piCompoRef->Release();
  piCompoRef = NULL;
  piLUK->Release();
  piLUK = NULL;
  if(NULL == piSchComp) return 24;

  // adding a WidePin and an ChildCtr
  CATISchCompConnector *piCompCntr = NULL;
  RC = piSchComp->QueryInterface(IID_CATISchCompConnector, (void **)&piCompCntr);
  if(NULL == piCompCntr) return 25;

  double CntrLoc[2];
  CntrLoc[0] = 20.0;
  CntrLoc[1] = 20.0;
  CATISchAppConnector *piSchCntr = NULL;
  RC = piCompCntr->AddConnector(SCHELEClass_WidePinCtr, NULL, CntrLoc, &piSchCntr);
  if(NULL == piSchCntr) return 26;
  piSchCntr->Release();
  piSchCntr = NULL;

  CntrLoc[0] = 10.0;
  CntrLoc[1] = 10.0;
  CATISchAppConnector *piSchEqtAssemblyCntr = NULL;
  RC = piCompCntr->AddConnector(SCHELEClass_ChildCtr, NULL, CntrLoc, &piSchEqtAssemblyCntr);
  piCompCntr->Release();
  piCompCntr = NULL;
  if(NULL == piSchEqtAssemblyCntr) return 27;

  piSchEqtAssemblyCntr->Release();
  piSchEqtAssemblyCntr = NULL;

  //---------------------------------------------------------------------------
  // 4 - Create the Socket Reference
  //---------------------------------------------------------------------------
  // Create a sheet
  CATISheet *piSocketSheet = NULL;
  RC = spDrwFact->CreateSheet(IID_CATISheet, (void **)&piSocketSheet);
  if (NULL == piSocketSheet) return 28;

  // jsk 8/26/03 Migration
  /*
  // Add the sheet to the drawing
  piDrawing->AddSheet(piSocketSheet);
  // Activate this new sheet
  piDrawing->SetCurrentSheet(piSocketSheet);
  piSocketSheet->SetAsDetail();
  */
  piDrawing->AppendSheet(piSocketSheet, CATIDrawing::Detail, CATIDrawing::Current);
  // 

  // Create a view with Make Up
  CATIDftViewMakeUp *piSocketViewMU = NULL;
  RC = spDrwFact->CreateDetailWithMakeUp(IID_CATIDftViewMakeUp,(void **)&piSocketViewMU, 1);
  if (NULL == piSocketViewMU) return 29;
  
  // Get the view from the MakeUp
  CATIView *piSocketView = NULL; 
  RC = piSocketViewMU->GetView(&piSocketView);
  if (!piSocketView) return 30;
  
  // The view has to be typed: FrontView for Interactive view.  
  piSocketView->SetViewType(FrontView);
  RC = piSocketViewMU->SetPosition(100.0,50.0);
  if(FAILED(RC)) return 31;
  
  // Add the view to the sheet
  RC = piSocketSheet->AddView(piSocketViewMU);
  piSocketViewMU->Release();
  piSocketViewMU = NULL;
  if(FAILED(RC)) return 32;
  
  // Activate this new view
  CATIView_var spSocketView(piSocketView);
  piSocketSheet->SetCurrentView(piSocketView);
  piSocketSheet->Release();
  piSocketSheet = NULL;
    
  // get the graphical factory
  CATI2DWFFactory *piSocketGeomFactory = NULL;
  RC = piSocketView->QueryInterface(IID_CATI2DWFFactory, (void **)&piSocketGeomFactory);
  if(NULL == piSocketGeomFactory) return 34;

  // Creation of a square:
  double SPt1[2], SPt2[2], SPt3[2], SPt4[2];
  SPt1[0]=0.0;
  SPt1[1]=0.0;
  SPt2[0]=10.0;
  SPt2[1]=0.0;
  SPt3[0]=10.0;
  SPt3[1]=10.0;
  SPt4[0]=0.0;
  SPt4[1]=10.0;

  CATISpecObject_var spSocketLine1 = piSocketGeomFactory->CreateLine(SPt1, SPt2);
  if(NULL_var == spSocketLine1) return 35;
  CATISpecObject_var spSocketLine2 = piSocketGeomFactory->CreateLine(SPt2, SPt3);
  if(NULL_var == spSocketLine2) return 35;
  CATISpecObject_var spSocketLine3 = piSocketGeomFactory->CreateLine(SPt3, SPt4);
  if(NULL_var == spSocketLine3) return 35;
  CATISpecObject_var spSocketLine4 = piSocketGeomFactory->CreateLine(SPt4, SPt1);
  piSocketGeomFactory->Release();
  piSocketGeomFactory = NULL;
  if(NULL_var == spSocketLine4) return 35;

  // create the applicative schematic component reference
  IUnknown *piSocketRef = NULL;
  RC= piAppFact->AppCreateCompRef(SCHELEClass_Socket, NULL, &piSocketRef);
  if(NULL == piSocketRef) return 36;
  
  // creating the list of GRR associated to my component
  CATIUnknownList *piLSocketUK = NULL;
  RC = list.CreateCATIUnknownList(&piLSocketUK);
  if(NULL == piLSocketUK) return 37;

  IUnknown *piSoUK = NULL;
  RC = piSocketView->QueryInterface(IID_IUnknown, (void **)&piSoUK);
  piSocketView->Release();
  piSocketView = NULL;
  if(NULL == piSoUK) return 38;

  RC = piLSocketUK->Add(0,piSoUK); 
  piSoUK -> Release();
  piSoUK = NULL;
  
  // schematic ref. component creation
  CATISchComponent *piSchSocket = NULL;
  RC = piBaseFact->CreateSchComponent(piSocketRef, piLSocketUK, &piSchSocket);
  piSocketRef->Release();
  piSocketRef = NULL;
  piLSocketUK->Release();
  piLSocketUK = NULL;
  if(NULL == piSchSocket) return 39;

  // adding a WidePin, a PlugMatingCtr and an ParentCtr
  CATISchCompConnector *piCompSocketCntr = NULL;
  RC = piSchSocket->QueryInterface(IID_CATISchCompConnector, (void **)&piCompSocketCntr);
  if(NULL == piCompSocketCntr) return 40;

  CntrLoc[0] = 10.0;
  CntrLoc[1] =  5.0;
  CATISchAppConnector *piSchWidePinCntr = NULL;
  RC = piCompSocketCntr->AddConnector(SCHELEClass_WidePinCtr, NULL, CntrLoc, &piSchWidePinCntr);
  if(NULL == piSchWidePinCntr) return 41;
  piSchWidePinCntr->Release();
  piSchWidePinCntr = NULL;

  CntrLoc[0] = 10.0;
  CntrLoc[1] =  5.0;
  CATISchAppConnector *piSchMatingSCntr = NULL;
  RC = piCompSocketCntr->AddConnector(SCHELEClass_PlugMatingCtr, NULL, CntrLoc, &piSchMatingSCntr);
  if(NULL == piSchMatingSCntr) return 42;
  piSchMatingSCntr->Release();
  piSchMatingSCntr = NULL;

  CntrLoc[0] = 0.0;
  CntrLoc[1] = 5.0;
  CATISchAppConnector *piSchAssemblyCntr = NULL;
  RC = piCompSocketCntr->AddConnector(SCHELEClass_ParentCtr, NULL, CntrLoc, &piSchAssemblyCntr);
  piCompSocketCntr -> Release();
  piCompSocketCntr = NULL;
  if(NULL == piSchAssemblyCntr) return 43;
  piSchAssemblyCntr->Release();
  piSchAssemblyCntr = NULL;

  //---------------------------------------------------------------------------
  // 5 - Create the Plug Reference
  //---------------------------------------------------------------------------
    // Create a sheet
  CATISheet *piPlugSheet = NULL;
  RC = spDrwFact->CreateSheet(IID_CATISheet, (void **)&piPlugSheet);
  if (NULL == piPlugSheet) return 44;
  
  // jsk 8/26/03 Migration
  /*
  // Add the sheet to the drawing
  piDrawing->AddSheet(piPlugSheet);
  // Activate this new sheet
  piDrawing->SetCurrentSheet(piPlugSheet);
  piPlugSheet->SetAsDetail();
  */
  piDrawing->AppendSheet(piPlugSheet, CATIDrawing::Detail, CATIDrawing::Current);
  // 

  // Create a view with Make Up
  CATIDftViewMakeUp *piPlugViewMU = NULL;
  RC = spDrwFact->CreateDetailWithMakeUp(IID_CATIDftViewMakeUp,(void **)&piPlugViewMU, 1);
  if (NULL == piPlugViewMU) return 45;
  
  // Get the view from the MakeUp
  CATIView *piPlugView = NULL; 
  RC = piPlugViewMU->GetView(&piPlugView);
  if (!piPlugView) return 46;
  
  // The view has to be typed: FrontView for Interactive view.  
  piPlugView->SetViewType(FrontView);
  RC = piPlugViewMU->SetPosition(100.0,50.0);
  if(FAILED(RC)) return 47;
  
  // Add the view to the sheet
  RC = piPlugSheet->AddView(piPlugViewMU);
  piPlugViewMU->Release();
  piPlugViewMU = NULL;
  if(FAILED(RC)) return 48;
  
  // Activate this new view
  CATIView_var spPlugView(piPlugView);
  piPlugSheet->SetCurrentView(spPlugView);
  piPlugSheet->Release();
  piPlugSheet = NULL;

  // get the graphical factory
  CATI2DWFFactory *piPlugGeomFactory = NULL;
  RC = piPlugView->QueryInterface(IID_CATI2DWFFactory, (void **)&piPlugGeomFactory);
  if(NULL == piPlugGeomFactory) return 50;

  // Creation of a square:
  double SPt5[2], SPt6[2], SPt7[2], SPt8[2];
  SPt5[0]=0.0;
  SPt5[1]=0.0;
  SPt6[0]=10.0;
  SPt6[1]=0.0;
  SPt7[0]=10.0;
  SPt7[1]=10.0;
  SPt8[0]=0.0;
  SPt8[1]=10.0;

  CATISpecObject_var spPlugLine1 = piPlugGeomFactory->CreateLine(SPt5, SPt6);
  if(NULL_var == spPlugLine1) return 51;
  CATISpecObject_var spPlugLine2 = piPlugGeomFactory->CreateLine(SPt6, SPt7);
  if(NULL_var == spPlugLine2) return 51;
  CATISpecObject_var spPlugLine3 = piPlugGeomFactory->CreateLine(SPt7, SPt8);
  if(NULL_var == spPlugLine3) return 51;
  CATISpecObject_var spPlugLine4 = piPlugGeomFactory->CreateLine(SPt8, SPt5);
  piPlugGeomFactory->Release();
  piPlugGeomFactory = NULL;
  if(NULL_var == spPlugLine4) return 51;

  // create the applicative schematic component reference
  IUnknown *piPlugRef = NULL;
  RC= piAppFact->AppCreateCompRef(SCHELEClass_Plug, NULL, &piPlugRef);
  if(NULL == piPlugRef) return 52;
  
  // creating the list of GRR associated to my component
  CATIUnknownList *piLPlugUK = NULL;
  RC = list.CreateCATIUnknownList(&piLPlugUK);
  if(NULL == piLPlugUK) return 53;

  IUnknown *piPgUK = NULL;
  RC = piPlugView->QueryInterface(IID_IUnknown, (void **)&piPgUK);
  piPlugView->Release();
  piPlugView = NULL;
  if(NULL == piPgUK) return 54;

  RC = piLPlugUK->Add(0,piPgUK);
  piPgUK->Release();
  piPgUK = NULL;
  if(FAILED(RC)) return 55;

  // schematic ref. component creation
  CATISchComponent *piSchPlug = NULL;
  RC = piBaseFact->CreateSchComponent(piPlugRef, piLPlugUK, &piSchPlug);	
  piPlugRef->Release();
  piPlugRef = NULL;
  piLPlugUK->Release();
  piLPlugUK = NULL;
  if(NULL == piSchPlug) return 56;

  // adding a WidePin and a MatingCtr
  CATISchCompConnector *piCompPlugCntr = NULL;
  RC = piSchPlug->QueryInterface(IID_CATISchCompConnector, (void **)&piCompPlugCntr);
  if(NULL == piCompPlugCntr) return 57;

  CntrLoc[0] = 0.0;
  CntrLoc[1] = 5.0;
  CATISchAppConnector *piSchWidePinPgCntr = NULL;
  RC = piCompPlugCntr->AddConnector(SCHELEClass_WidePinCtr, NULL, CntrLoc, &piSchWidePinPgCntr);
  if(NULL == piSchWidePinPgCntr) return 58;
  piSchWidePinPgCntr->Release();
  piSchWidePinPgCntr = NULL;

  CntrLoc[0] = 10.0;
  CntrLoc[1] =  5.0;
  CATISchAppConnector *piSchMatingPgCntr = NULL;
  RC = piCompPlugCntr->AddConnector(SCHELEClass_SocketMatingCtr, NULL, CntrLoc, &piSchMatingPgCntr);
  piCompPlugCntr->Release();
  piCompPlugCntr = NULL;
  if(NULL == piSchMatingPgCntr) return 59;
  piSchMatingPgCntr->Release();
  piSchMatingPgCntr = NULL;

  //---------------------------------------------------------------------------
  // 6 - Place the components twice
  //---------------------------------------------------------------------------
  CATLISTV(CATISpecObject_var) lSheets = piDrawing->GetSheetList();

  // The first sheet is the main sheet
  CATISheet *piMainSheet = NULL;
  CATISpecObject_var spSheet(lSheets[1]);
  if (!!spSheet)
    RC = spSheet->QueryInterface(IID_CATISheet, (void **)&piMainSheet);
  if(NULL == piMainSheet) return 60;

  // Activate this new sheet
  piDrawing->SetCurrentSheet(piMainSheet);
  piDrawing->Release();
  piDrawing = NULL;

  // instanciation of EQT in main sheet
  CATISchComponent *piComponentInst1 = NULL;
  double iDb6Axis1[6] = { 1.0, 0.0, 0.0, 1.0,  50.0,  50.0};
  RC = piSchComp->PlaceInSpace(NULL, iDb6Axis1, &piComponentInst1);
  if(NULL == piComponentInst1) return 61;

  CATISchComponent *piComponentInst2 = NULL;
  double iDb6Axis2[6] = {-1.0, 0.0, 0.0, 1.0, 200.0, 150.0};
  RC = piSchComp->PlaceInSpace(NULL, iDb6Axis2, &piComponentInst2);
  piSchComp->Release();
  piSchComp = NULL;
  if(NULL == piComponentInst2) return 62;

  // instanciation of Socket in main sheet
  CATISchComponent *piSocketInst1 = NULL;
  double iDb6Axis3[6] = { 1.0, 0.0, 0.0, 1.0,  60.0,  55.0};
  RC = piSchSocket->PlaceInSpace (NULL, iDb6Axis3, &piSocketInst1);
  if(NULL == piSocketInst1) return 63;

  CATISchComponent *piSocketInst2 = NULL;
  double iDb6Axis4[6] = {-1.0, 0.0, 0.0, 1.0, 190.0, 155.0};
  RC = piSchSocket->PlaceInSpace (NULL, iDb6Axis4, &piSocketInst2);
  piSchSocket->Release();
  piSchSocket = NULL;
  if(NULL == piSocketInst2) return 64;

  // instanciation of Plug in main sheet
  CATISchComponent *piPlugInst1 = NULL;
  double iDb6Axis5[6] = {-1.0, 0.0, 0.0, 1.0,  80.0,  55.0};
  RC = piSchPlug->PlaceInSpace (NULL, iDb6Axis5, &piPlugInst1);
  if(NULL == piPlugInst1) return 65;

  CATISchComponent *piPlugInst2 = NULL;
  double iDb6Axis6[6] = { 1.0, 0.0, 0.0, 1.0, 170.0, 155.0};
  RC = piSchPlug->PlaceInSpace (NULL, iDb6Axis6, &piPlugInst2);
  piSchPlug->Release();
  piSchPlug = NULL;
  if(NULL == piPlugInst2) return 66;

  //---------------------------------------------------------------------------
  // 7 - Annotate the components
  //---------------------------------------------------------------------------
  CATIView_var spMainView = piMainSheet->GetMainView();
  if(NULL_var == spMainView) return 67;

  piMainSheet->SetCurrentView(spMainView);
  piMainSheet->Release();
  piMainSheet = NULL;

  CATIDrwAnnotationFactory_var spAnnFactory(spMainView);

  // 1st comp	
  double dx = 50.0;
  double dy = 75.0;
  CATUnicodeString cusComp1Anno("Comp. 1");
  CATIDrwText_var spDrwTextAnno1 = spAnnFactory->CreateDrwText(dx, dy, cusComp1Anno);
  if(NULL_var == spDrwTextAnno1) return 68;

  // 2nd comp	
  dx = 180.0;
  dy = 175.0;
  CATUnicodeString cusComp2Anno("Comp. 2");
  CATIDrwText_var spDrwTextAnno2 = spAnnFactory->CreateDrwText(dx, dy, cusComp2Anno);
  if(NULL_var == spDrwTextAnno2) return 69;

  //---------------------------------------------------------------------------
  // prepare filtering list for querying connectors
  //---------------------------------------------------------------------------
  // 
  CATICStringList *piLChildCtrType = NULL;
  RC = list.CreateCATICStringList(&piLChildCtrType);
  if(NULL == piLChildCtrType) return 71;
  piLChildCtrType->Add(0, SCHELEClass_ChildCtr);

  CATICStringList *piLParentCtrType = NULL;
  RC = list.CreateCATICStringList(&piLParentCtrType);
  if(NULL == piLParentCtrType) return 71;
  piLParentCtrType->Add(0, SCHELEClass_ParentCtr);

  CATICStringList *piLPlugMatingCtrType = NULL;
  RC = list.CreateCATICStringList(&piLPlugMatingCtrType);
  if(NULL == piLPlugMatingCtrType) return 71;  
  piLPlugMatingCtrType->Add(0, SCHELEClass_PlugMatingCtr);

  CATICStringList *piLSocketMatingCtrType = NULL;
  RC = list.CreateCATICStringList(&piLSocketMatingCtrType);
  if(NULL == piLSocketMatingCtrType) return 71;  
  piLSocketMatingCtrType->Add(0, SCHELEClass_SocketMatingCtr);

  CATICStringList *piLWPCtrType = NULL;
  RC = list.CreateCATICStringList(&piLWPCtrType);
  if(NULL == piLWPCtrType) return 71;  
  piLWPCtrType->Add(0, SCHELEClass_WidePinCtr);

  //---------------------------------------------------------------------------
  // 8 - Assemble the Equipments and the Sockets and Connect the Plugs to the 
  //     Sockets
  //---------------------------------------------------------------------------
  // Eqt1
  CATISchAppConnectable *piEqtConnectable1 = NULL;
  RC = piComponentInst1->QueryInterface(IID_CATISchAppConnectable, (void **)&piEqtConnectable1);
  piComponentInst1->Release();
  piComponentInst1 = NULL;
  if(NULL == piEqtConnectable1) return 70;

  CATIUnknownList *piLEqtChildConnector1 = NULL;
  RC = piEqtConnectable1->AppListConnectors(piLChildCtrType, &piLEqtChildConnector1);
  piEqtConnectable1->Release();
  piEqtConnectable1 = NULL;
  if(NULL == piLEqtChildConnector1) return 72;

  unsigned int nb = 0;
  RC = piLEqtChildConnector1->Count(&nb);
  if(0 == nb) return 73;

  IUnknown *piEqtCntr1 = NULL;
  RC = piLEqtChildConnector1->Item(0, &piEqtCntr1);
  piLEqtChildConnector1->Release();
  piLEqtChildConnector1 = NULL;
  if(NULL == piEqtCntr1) return 74;

  CATISchAppConnector *piAppEqtCntr1 = NULL;
  RC= piEqtCntr1->QueryInterface(IID_CATISchAppConnector, (void **)&piAppEqtCntr1);
  piEqtCntr1->Release();
  piEqtCntr1 = NULL;
  if(NULL == piAppEqtCntr1) return 75;

  // Socket1
  CATISchAppConnectable *piSocketConnectable1 = NULL;
  RC = piSocketInst1->QueryInterface(IID_CATISchAppConnectable, (void **)&piSocketConnectable1);
  piSocketInst1->Release();
  piSocketInst1 = NULL;
  if(NULL == piSocketConnectable1) return 76;

  CATIUnknownList *piLSocketParentConnector1 = NULL;
  RC = piSocketConnectable1->AppListConnectors (piLParentCtrType, &piLSocketParentConnector1);
  if(NULL == piLSocketParentConnector1) return 77;

  nb = 0;
  RC = piLSocketParentConnector1->Count(&nb);
  if(0 == nb) return 78;

  IUnknown *piSocketCntr1 = NULL;
  RC = piLSocketParentConnector1->Item(0, &piSocketCntr1);
  piLSocketParentConnector1->Release();
  piLSocketParentConnector1 = NULL;
  if(NULL == piSocketCntr1) return 79;

  CATISchAppConnector *piAppSocketCntr1 = NULL;
  RC= piSocketCntr1->QueryInterface(IID_CATISchAppConnector, (void **)&piAppSocketCntr1);
  piSocketCntr1->Release();
  piSocketCntr1 = NULL;
  if(NULL == piAppSocketCntr1) return 80;

  CATISchAppConnection *piAssyConnection1 = NULL;
  RC = piAppEqtCntr1->AppConnect(piAppSocketCntr1, &piAssyConnection1);
  piAppEqtCntr1->Release();
  piAppEqtCntr1 = NULL;
  piAppSocketCntr1->Release();
  piAppSocketCntr1 = NULL;
  if(NULL == piAssyConnection1) return 81;

  piAssyConnection1->Release();
  piAssyConnection1 = NULL;



  CATIUnknownList *piLSocketMatConnector1 = NULL;
  RC = piSocketConnectable1->AppListConnectors(piLPlugMatingCtrType, &piLSocketMatConnector1);
  piSocketConnectable1->Release();
  piSocketConnectable1 = NULL;
  if(NULL == piLSocketMatConnector1) return 83;

  RC = piLSocketMatConnector1->Item(0, &piSocketCntr1);
  if(NULL == piSocketCntr1) return 84;

  piLSocketMatConnector1->Release();
  piLSocketMatConnector1 = NULL;

  RC= piSocketCntr1->QueryInterface(IID_CATISchAppConnector, (void **)&piAppSocketCntr1);
  piSocketCntr1->Release();
  piSocketCntr1 = NULL;
  if(NULL == piAppSocketCntr1) return 85;

  // Plug 1
  CATISchAppConnectable *piPlugConnectable1 = NULL;
  RC = piPlugInst1->QueryInterface(IID_CATISchAppConnectable, (void **)&piPlugConnectable1);
  piPlugInst1->Release();
  piPlugInst1 = NULL;
  if(NULL == piPlugConnectable1) return 86;

  CATIUnknownList *piLPlugMatingConnector1 = NULL;
  RC = piPlugConnectable1->AppListConnectors (piLSocketMatingCtrType, &piLPlugMatingConnector1);
  if(NULL == piLPlugMatingConnector1) return 87;

  nb = 0;
  RC = piLPlugMatingConnector1->Count(&nb);
  if(0 == nb) return 88;

  IUnknown *piPlugCntr1 = NULL;
  RC = piLPlugMatingConnector1->Item(0, &piPlugCntr1);
  piLPlugMatingConnector1->Release();
  piLPlugMatingConnector1 = NULL;
  if(NULL == piPlugCntr1) return 89;

  CATISchAppConnector *piAppPlugCntr1 = NULL;
  RC = piPlugCntr1->QueryInterface(IID_CATISchAppConnector, (void **)&piAppPlugCntr1);
  piPlugCntr1->Release();
  piPlugCntr1 = NULL;
  if(NULL == piAppPlugCntr1) return 90;

  RC = piAppPlugCntr1->AppConnect(piAppSocketCntr1, &piAssyConnection1);
  piAppPlugCntr1->Release();
  piAppPlugCntr1 = NULL;
  piAppSocketCntr1->Release();
  piAppSocketCntr1 = NULL;
  if(NULL == piAssyConnection1) return 91;

  piAssyConnection1->Release();
  piAssyConnection1 = NULL;

  // Eqt2
  CATISchAppConnectable *piEqtConnectable2 = NULL;
  RC = piComponentInst2->QueryInterface (IID_CATISchAppConnectable, (void **) &piEqtConnectable2);
  piComponentInst2->Release();
  piComponentInst2 = NULL;
  if(NULL == piEqtConnectable2) return 92;

  CATIUnknownList *piLEqtChildConnector2 = NULL;
  RC = piEqtConnectable2->AppListConnectors (piLChildCtrType, &piLEqtChildConnector2);
  piEqtConnectable2->Release();
  piEqtConnectable2 = NULL;
  if(NULL == piLEqtChildConnector2) return 93;

  nb = 0;
  RC = piLEqtChildConnector2->Count(&nb);
  if(0 == nb) return 94;

  IUnknown *piEqtCntr2 = NULL;
  RC = piLEqtChildConnector2->Item(0, &piEqtCntr2);
  piLEqtChildConnector2->Release();
  piLEqtChildConnector2 = NULL;
  if(NULL == piEqtCntr2) return 95;

  CATISchAppConnector *piAppEqtCntr2 = NULL;
  RC= piEqtCntr2->QueryInterface(IID_CATISchAppConnector, (void **)&piAppEqtCntr2);
  piEqtCntr2->Release();
  piEqtCntr2 = NULL;
  if(NULL == piAppEqtCntr2) return 96;

  // Socket2
  CATISchAppConnectable *piSocketConnectable2 = NULL;
  RC = piSocketInst2->QueryInterface(IID_CATISchAppConnectable, (void **)&piSocketConnectable2);
  piSocketInst2->Release();
  piSocketInst2 = NULL;
  if(NULL == piSocketConnectable2) return 97;

  CATIUnknownList *piLSocketParentConnector2 = NULL;
  RC = piSocketConnectable2->AppListConnectors(piLParentCtrType, &piLSocketParentConnector2);
  if(NULL == piLSocketParentConnector2) return 98;

  nb = 0;
  RC = piLSocketParentConnector2->Count(&nb);
  if(0 == nb) return 99;

  IUnknown *piSocketCntr2 = NULL;
  RC = piLSocketParentConnector2->Item(0, &piSocketCntr2);
  piLSocketParentConnector2->Release();
  piLSocketParentConnector2 = NULL;
  if(NULL == piSocketCntr2) return 100;

  CATISchAppConnector *piAppSocketCntr2 = NULL;
  RC= piSocketCntr2->QueryInterface(IID_CATISchAppConnector, (void **)&piAppSocketCntr2);
  piSocketCntr2->Release();
  piSocketCntr2 = NULL;
  if(NULL == piAppSocketCntr2) return 101;

  CATISchAppConnection *piAssyConnection2 = NULL;
  RC = piAppEqtCntr2->AppConnect(piAppSocketCntr2, &piAssyConnection2);
  piAppEqtCntr2->Release();
  piAppEqtCntr2 = NULL;
  piAppSocketCntr2->Release();
  piAppSocketCntr2 = NULL;
  if(NULL == piAssyConnection2) return 102;

  piAssyConnection2->Release();
  piAssyConnection2 = NULL;

  // Mating Connection Socket-Plug
  CATIUnknownList *piLSocketMatingConnector2 = NULL;
  RC = piSocketConnectable2->AppListConnectors (piLPlugMatingCtrType, &piLSocketMatingConnector2);
  piSocketConnectable2->Release();
  piSocketConnectable2 = NULL;
  if(NULL == piLSocketMatingConnector2) return 103;

  nb = 0;
  RC = piLSocketMatingConnector2->Count(&nb);
  if(0 == nb) return 104;

  RC = piLSocketMatingConnector2->Item(0, &piSocketCntr2);
  piLSocketMatingConnector2->Release();
  piLSocketMatingConnector2 = NULL;
  if(NULL == piSocketCntr2) return 105;

  RC= piSocketCntr2->QueryInterface(IID_CATISchAppConnector, (void **)&piAppSocketCntr2);
  piSocketCntr2->Release();
  piSocketCntr2 = NULL;
  if(NULL == piAppSocketCntr2) return 106;

  // Plug 2
  CATISchAppConnectable *piPlugConnectable2 = NULL;
  RC = piPlugInst2->QueryInterface(IID_CATISchAppConnectable, (void **)&piPlugConnectable2);
  piPlugInst2->Release();
  piPlugInst2 = NULL;
  if(NULL == piPlugConnectable2) return 107;

  CATIUnknownList *piLPlugMatingConnector2 = NULL;
  RC = piPlugConnectable2->AppListConnectors(piLSocketMatingCtrType, &piLPlugMatingConnector2);
  if(NULL == piLPlugMatingConnector2) return 108;

  nb = 0;
  RC = piLPlugMatingConnector2->Count(&nb);
  if(0 == nb) return 109;

  IUnknown *piPlugCntr2 = NULL;
  RC = piLPlugMatingConnector2->Item(0, &piPlugCntr2);
  piLPlugMatingConnector2->Release();
  piLPlugMatingConnector2 = NULL;
  if(NULL == piPlugCntr2) return 110;

  CATISchAppConnector *piAppPlugCntr2 = NULL;
  RC= piPlugCntr2->QueryInterface(IID_CATISchAppConnector, (void **)&piAppPlugCntr2);
  piPlugCntr2->Release();
  piPlugCntr2 = NULL;
  if(NULL == piAppPlugCntr2) return 111;

  RC = piAppPlugCntr2->AppConnect(piAppSocketCntr2, &piAssyConnection2);
  piAppPlugCntr2->Release();
  piAppPlugCntr2 = NULL;
  piAppSocketCntr2->Release();
  piAppSocketCntr2 = NULL;
  if(NULL == piAssyConnection2) return 112;

  piAssyConnection2->Release();
  piAssyConnection2 = NULL;

  //---------------------------------------------------------------------------
  // 9 - Route a Cable Between the Plugs
  //---------------------------------------------------------------------------
  // Get the WidePin on Plug1


  CATIUnknownList *piLPlugWPConnector1 = NULL;
  RC = piPlugConnectable1->AppListConnectors(piLWPCtrType, &piLPlugWPConnector1);
  piPlugConnectable1->Release();
  piPlugConnectable1 = NULL;
  if(NULL == piLPlugWPConnector1) return 114;

  nb = 0;
  RC = piLPlugWPConnector1->Count(&nb);
  if(0 == nb) return 115;

  RC = piLPlugWPConnector1->Item(0, &piPlugCntr1);
  piLPlugWPConnector1->Release();
  piLPlugWPConnector1 = NULL;
  if(NULL == piPlugCntr1) return 116;

  CATISchAppConnector *piAppPlugWPCntr1 = NULL;
  RC= piPlugCntr1->QueryInterface(IID_CATISchAppConnector, (void **)&piAppPlugWPCntr1);
  piPlugCntr1->Release();
  piPlugCntr1 = NULL;
  if(NULL == piAppPlugWPCntr1) return 117;

  // Get the WidePin on Plug2
  CATIUnknownList *piLPlugWPConnector2 = NULL;
  RC = piPlugConnectable2->AppListConnectors(piLWPCtrType, &piLPlugWPConnector2);
  piPlugConnectable2->Release();
  piPlugConnectable2 = NULL;
  if(NULL == piLPlugWPConnector2) return 118;

  nb = 0;
  RC = piLPlugWPConnector2->Count(&nb);
  if(0 == nb) return 119;

  RC = piLPlugWPConnector2->Item(0, &piPlugCntr2);
  piLPlugWPConnector2->Release();
  piLPlugWPConnector2 = NULL;
  if(NULL == piPlugCntr2) return 120;

  CATISchAppConnector *piAppPlugWPCntr2 = NULL;
  RC= piPlugCntr2->QueryInterface(IID_CATISchAppConnector, (void **)&piAppPlugWPCntr2);
  piPlugCntr2->Release();
  piPlugCntr2 = NULL;
  if(NULL == piAppPlugWPCntr2) return 121;

  // create applicative route
  IUnknown *piUKAppRoute = NULL;
  RC = piAppFact->AppCreateRoute2(SCHELEClass_Cable, NULL, NULL, &piUKAppRoute);
  piAppFact -> Release();
  piAppFact = NULL;
  if(NULL == piUKAppRoute) return 122;

  double pPts[14] = {80.0, 60.0, 73.0, 60.0, 73.0, 147.0, 197.0, 147.0, 197.0, 173.0, 170.0, 173.0, 170.0, 160.0};

  // create the cable in the main sheet
  CATISchRoute *piSchRoute = NULL;
  RC = piBaseFact->CreateSchRouteByPoints(piUKAppRoute, pPts, 14, &piSchRoute);
  piBaseFact->Release();
  piBaseFact = NULL;
  piUKAppRoute->Release();
  piUKAppRoute = NULL;

  if(NULL == piSchRoute) return 123;

  // and connect the extremities (line -> component)
  CATISchAppConnector *piRouteCntr1 = NULL;
  CATISchAppConnector *piRouteCntr2 = NULL;
  RC = piSchRoute->GetExtremityCntrs(NULL, &piRouteCntr1, &piRouteCntr2);
  piSchRoute->Release();
  piSchRoute = NULL;
  if(NULL == piRouteCntr1) return 124;
  if(NULL == piRouteCntr2) return 125;

  CATISchAppConnection *piConnection1 = NULL;
  RC = piRouteCntr1->AppConnect(piAppPlugWPCntr1, &piConnection1);
  piRouteCntr1->Release();
  piRouteCntr1 = NULL;
  piAppPlugWPCntr1->Release();
  piAppPlugWPCntr1 = NULL;
  if(NULL == piConnection1) return 126;
  piConnection1->Release();
  piConnection1 = NULL;

  CATISchAppConnection *piConnection2 = NULL;
  RC = piRouteCntr2->AppConnect(piAppPlugWPCntr2, &piConnection2);
  piRouteCntr2->Release();
  piRouteCntr2 = NULL;
  piAppPlugWPCntr2->Release();
  piAppPlugWPCntr2 = NULL;
  if(NULL == piConnection2) return 127;
  piConnection2->Release();
  piConnection2 = NULL;

  //---------------------------------------------------------------------------
  // release all connector-query filtering list
  //---------------------------------------------------------------------------
  if (piLChildCtrType) {piLChildCtrType->Release(); piLChildCtrType = NULL;}
  if (piLParentCtrType) {piLParentCtrType->Release(); piLParentCtrType = NULL;}
  if (piLPlugMatingCtrType) {piLPlugMatingCtrType->Release(); piLPlugMatingCtrType = NULL;}
  if (piLSocketMatingCtrType) {piLSocketMatingCtrType->Release(); piLSocketMatingCtrType = NULL;}
  if (piLWPCtrType) {piLWPCtrType->Release(); piLWPCtrType = NULL;}

  //---------------------------------------------------------------------------
  // 10 - Epilog.
  //---------------------------------------------------------------------------
  RC = CATDocumentServices::SaveAs(*piSchemDoc, argv[1]);
  if(FAILED(RC)) return 128;

  RC = CATDocumentServices::Remove (*piSchemDoc);
  if(FAILED(RC)) return 129;

  ::Delete_Session(pSessionIdent);
  return 0;
}


