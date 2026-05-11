/**
 * @quickreview nd1 12:04:07 Removed #includes of CATICatalog & CATCatalogFactoryServices
                             APIs deprecated with effect from CXR23.
 * @quickreview vso jsk 08:02:07
 */
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

/***********************************************************************************/
/*                   CAAEdiSchematic.m                                             */
/***********************************************************************************/
 
/*
Abstract :
--------
  This sample illustrates the way to manage Schematic entities.

    This sample:
  
    - 1. Create an Object Modeler Session.
    
    - 2. Open a Document and Create a New Document.
      
    - 3. Create Reference Factory.
        
    - 4. Create Reference Equipment. 
          
    - 5. Create the  Reference Cable.
            
    - 6. Instanciates  the First Equipment.
              
    - 7. Instanciates the Second Equipment.
                
    - 8. Instanciates the Cable
                  
    - 9. Retrieves the Cable extremities.
                    
    - 10.Adds WidePins on Equipment 1.
                      
    - 11.List the WidePins on Equipment 1.
                         
    - 12.Connect CABLE/Ext1 on EQT1/Pin1.
                          
    - 13.Retrieves the WidePin from the Connection CABLE/Ext1 to EQT1/Pin1 .
                            
    - 14.Removes the EQT1/Pin1.
                              
    - 15.Retrieves the WidePin from the connection CABLE/Ext1 to EQT1/Pin1 after Remove...   
                                
    - 16.Connect CABLE/Ext1 on EQT1/Pin2.
                                  
    - 17.Disconnect CABLE/Ext1 on EQT1/Pin2.
                                    
    - 18.Connect CABLE/Ext1 on EQT1/Pin2 after disconnection.
                                      
    - 19.Connect CABLE/Ext2 on EQT2/Pin1.
                                        
    - 20.List Associated Equipments of the Cable. 
                                          
    - 21.List Associated Cables of the Equipments.
                                            
    - 22.Saves the Document. 
                                              
                                                
    Usage:
    ------
      To run this sample, you can use the command:
      mkrun -c "CAAEdiSchematic CAAEdiSchematic_InstIn.CATProduct 
                                output_Inst.CATProduct
                                output_CompRef.CATProduct
                                output_CableRef.CATProduct"
    
      where "CAAEdiSchematic_InstIn.CATProduct" is the full path name of the input document, and
      "output_Inst.CATProduct" is the full path name of the 1st output document (modified input document),
      "output_CompRef.CATProduct" is the full path name of the 2nd output document,
      "output_CableRef.CATProduct" is the full path name of the 3rd output document.

        * Return Errors:
        * -------------
        *   
        *  1  - ERROR in creating an Object Modeler Session.
        *  2  - ERROR in creating a new Document or in retrieving the Root container.
        *  3  - ERROR in creating Reference Factory.
        *  4  - ERROR in creating the Reference Equipment.
        *  5  - ERROR in creating the Reference Cable. 
        *  6  - ERROR in creating the Equipment Instance one. 
        *  7  - ERROR in creating the Equipment Instance two.
        *  8  - ERROR in creating the Cable Instance. 
        *  9  - ERROR in query interface (Cable).
        *  10 - ERROR in retrieving Cable's Extremities..
        *  11 - ERROR in retrieving Cable from extremity.
        *  12 - ERROR in query interface(Equipment).
        *  13 - ERROR in Adding WidePins on Equipment 1.
        *  14 - ERROR in query interface (Equipment).
        *  15 - ERROR in Listing the WidePins on Equipment 1.
        *  16 - ERROR in query interface (WidePin 1) or in Item method.
        *  17 - ERROR in query interface (WidePin 2) or in Item method.
        *  18 - ERROR in Counting the Wide Pins.
        *  19 - ERROR in retrieving the Equipment from the WidePin.
        *  20 - ERROR in Connecting CABLE/Ext1 on EQT1/Pin1. 
        *  21 - ERROR in retrieving the WidePin from the connection CABLE/Ext1 to EQT1/Pin1 .
        *  22 - ERROR in retrieving the extremity from the connection EQT1/Pin1 to CABLE/Ext1.
        *  23 - ERROR in Removing EQT1/Pin1.  
        *  24 - ERROR in retrieving the WidePin from the connection CABLE/Ext1 to EQT1/Pin1 after Remove...   
        *  25 - ERROR in Connecting CABLE/Ext1 on EQT1/Pin2.
        *  26 - ERROR in Disconnecting CABLE/Ext1 on EQT1/Pin2.
        *  27 - ERROR in Connecting CABLE/Ext1 on EQT1/Pin2 after disconnection.
        *  28 - ERROR in Connecting CABLE/Ext2 on EQT2/Pin2.
        *  29 - ERROR in Listing Associated Equipments of the Cable.  
        *  30 - ERROR in Listing Associated Cables of the Equipments.
        *  31 - ERROR in Saving the Document. 
        /***********************************************************************************
*/
#include "CAAEdiSampleParameters.h"

// System
#include "CATDocumentServices.h" // New, SaveAs and Remove
#include "CATBSTR.h"
#include "CATUnicodeString.h"    // contains the CATUnicodeString class definition
#include "CATSession.h"          
#include "CATIUnknownList.h"     // needed to manage Lists
#include "CATInit.h"             // GetRootContainer

//ProductStructure
#include "CATIProduct.h"
#include "CATIDocRoots.h"
//
// ObjectSpecsModeler
#include "CATISpecObject.h"

// ObjectModelerBase
#include "CATObject.h"
#include "CATDocument.h"
#include "CATILinkableObject.h"
#include "CATSessionServices.h"  // Create_Session

// ElectricalDiagramModeler
#include "CATIEdiWidePin.h"            //needed to create WidePins 
#include "CATIEdiEquipment.h"          //needed to create an Electrical Equipment
#include "CATIEdiEquipmentReference.h" 
#include "CATIEdiReferenceFactory.h"   //needed to create References
#include "CATIEdiCable.h"              //needed to create Cables
#include "CATIEdiCableExtremity.h"     //needed to create Cable extremities
#include "CATIEdiCableReference.h"
#include "CATIEdiWire.h"

// CATSchPlatformInterfaces
#include "CATISchAppObjectFactory2.h"
#include "CATISchComponent.h"
#include "CATISchAppComponent.h"
#include "CATISchAppConnectable.h"
#include "CATISchAppConnector.h"

//Other includes
#include <iostream.h>

//==========================================================================
// InstanciateEdiInlineProduct
//==========================================================================
HRESULT InstanciateEdiInlineProduct (const CATIContainer *iTargetCont,
  IUnknown *iEdiInlineProduct,const char *iEdiInstanceName, 
  IUnknown **oEdiInstance)
{
  HRESULT RC = E_FAIL;
  CATIContainer *piTargetCont = (CATIContainer *) iTargetCont;
  if (!iEdiInlineProduct || !oEdiInstance || !piTargetCont) return RC;
  *oEdiInstance = NULL;

  CATISpecObject *piSpecRef = NULL;
  CATObject *pObj = NULL;
  CATISchAppObjectFactory2 *piSchAppFact2 = NULL;
  CATISchAppComponent *piAppComp = NULL;
  IUnknown *piUKLocalRef = NULL;
  CATIProduct *piPrdNewInst = NULL;

  CATILinkableObject_var spLinkTarget (piTargetCont);
  if (!spLinkTarget) return RC;

  CATUnicodeString UPrdInstName(iEdiInstanceName);
  HRESULT rc1 = E_FAIL;
  CATDocument *pDoc = spLinkTarget->GetDocument();
  if (pDoc) 
  {
     pObj = new CATObject (SCHELEClass_Application);
     if (pObj) RC = pObj->QueryInterface (IID_CATISchAppObjectFactory2,
       (void **) &piSchAppFact2);
  }

  if (SUCCEEDED (RC)) RC = iEdiInlineProduct->QueryInterface (
    IID_CATISpecObject,(void **) &piSpecRef);

  if (SUCCEEDED(RC) && piSchAppFact2 && !!piSpecRef)
  {
     CATUnicodeString UType = piSpecRef->GetType();

     //---------------------------------------------------------------------
     // String function - Cable
     //---------------------------------------------------------------------
     if (piSpecRef->IsSubTypeOf (SCHELEClass_Cable))
     {
        RC = piSchAppFact2->AppCreateRouteWithInfo (
             piSpecRef->GetType(),iEdiInlineProduct, oEdiInstance);
     }
     //---------------------------------------------------------------------
     // Component function - Cable
     //---------------------------------------------------------------------
     else if (piSpecRef->IsSubTypeOf (SCHELEClass_Component))
     {
        RC = piSpecRef->QueryInterface (IID_CATISchAppComponent,
             (void **) &piAppComp);
        if (SUCCEEDED (RC) && piAppComp)
        {
           RC = piAppComp->AppCreateLocalReference (pDoc,&piUKLocalRef);         
        }

        if (piAppComp){piAppComp->Release();piAppComp=NULL;}

        if (SUCCEEDED (RC) && piUKLocalRef)
        {
           RC = piUKLocalRef->QueryInterface (IID_CATISchAppComponent,
                (void **) &piAppComp);
           if (SUCCEEDED (RC) && piAppComp)
           {
              RC = piAppComp->AppCreateComponentInst (oEdiInstance);
           }
        }
     }  // else if (piSpecRef->IsSubTypeOf (PspCLASS_CompFunc))                    
     if (SUCCEEDED (RC) && *oEdiInstance)
     {
        if (SUCCEEDED ((*oEdiInstance)->QueryInterface (IID_CATIProduct,
            (void **) &piPrdNewInst)) && piPrdNewInst)
        {
           if (SUCCEEDED (RC) && UPrdInstName.GetLengthInChar()>0)
           {
              rc1 = piPrdNewInst->SetPrdInstanceName (UPrdInstName);
           }
        } //if (!!spPrdNewInst)
     } // if (SUCCEEDED (RC) && oEdiInstance)
  } // !!spPrdRoot  

  if (FAILED (RC))
  {
    if (*oEdiInstance){(*oEdiInstance)->Release();(*oEdiInstance)=NULL;}
  }

  if (pObj)          {pObj->Release()         ;pObj=NULL;}
  if (piSchAppFact2) {piSchAppFact2->Release();piSchAppFact2=NULL;}
  if (piAppComp)     {piAppComp->Release()    ;piAppComp=NULL;}
  if (piUKLocalRef)  {piUKLocalRef->Release() ;piUKLocalRef=NULL;}
  if (piPrdNewInst)  {piPrdNewInst->Release() ;piPrdNewInst=NULL;}
  if (piSpecRef)     {piSpecRef->Release()    ;piSpecRef=NULL;}

  return RC;
}

//==========================================================================
// main
//==========================================================================
int main (int argc, char **argv )
{ 
  if(argc!=5) return -1;
  
  HRESULT RC(S_OK);

  CATUnicodeString PATHInstIN (argv[1]);
  CATUnicodeString PATHInst (argv[2]);
  CATUnicodeString PATHCompRef (argv[3]);
  CATUnicodeString PATHCableRef (argv[4]);
  CATUnicodeString ELECTYPE ("CATProduct");
  
  // -------------------------------------------------------------------------
  // Creating an Object Modeler Session 
  // -------------------------------------------------------------------------
  char* psessionIdent = "Working Session";
  CATSession* psession = NULL;
  ::Create_Session(psessionIdent, psession);
  if (NULL == psession) return 1;
  
  // ------------------------------------------------------------------------- 
  // Open the main document (for instance objects)
  // -------------------------------------------------------------------------  
  CATDocument *pCATDocument1 = NULL;
  CATDocumentServices::OpenDocument (PATHInstIN, pCATDocument1);
  // ------------------------------------------------------------------------- 
  // Create new Documents (for reference objects)
  // -------------------------------------------------------------------------  
  CATDocument *pCATDocumentEqt = NULL;
  CATDocumentServices::New (ELECTYPE, pCATDocumentEqt);
  CATDocument *pCATDocumentCable = NULL;
  CATDocumentServices::New (ELECTYPE, pCATDocumentCable);  

  if (NULL == pCATDocument1 || NULL == pCATDocumentEqt || NULL == pCATDocumentCable) return 2;  

  cout << "Successfully initialized all documents" << endl;

  CATIContainer* pCont = (CATIContainer*) pCATDocument1->GetRootContainer(CATIContainer::ClassName());  
  CATIContainer* pContEqt = (CATIContainer*) pCATDocumentEqt->GetRootContainer(CATIContainer::ClassName());  
  CATIContainer* pContCable = (CATIContainer*) pCATDocumentCable->GetRootContainer(CATIContainer::ClassName());
  
  if(NULL == pCont || NULL == pContEqt || NULL == pContCable )return 2;

  // -------------------------------------------------------------------------
  // Create Reference factories
  // -------------------------------------------------------------------------
  
  CATIEdiReferenceFactory * piReferenceFactoryEqt = NULL;
  RC = pContEqt->QueryInterface(IID_CATIEdiReferenceFactory, 
    (void**)& piReferenceFactoryEqt);
  
  if(FAILED(RC) || NULL == piReferenceFactoryEqt) return 3;
  
  CATIEdiReferenceFactory * piReferenceFactoryCable = NULL;
  RC = pContCable->QueryInterface(IID_CATIEdiReferenceFactory, 
    (void**)& piReferenceFactoryCable);
  
  if(FAILED(RC) || NULL == piReferenceFactoryCable) return 3; 

  cout << "Found reference factories" << endl;

  // -------------------------------------------------------------------------
  // Create Equipment Reference 
  // -------------------------------------------------------------------------
  IUnknown* piEdiEquipmentReference = NULL;
  const wchar_t* wchar_EquipmentPartNumber = L"EQT_PartNumber";
  RC = piReferenceFactoryEqt->CreateEdiComponentReference (SCHELEClass_Equipment, 
       NULL,&piEdiEquipmentReference);    
  if(FAILED(RC) || NULL == piEdiEquipmentReference) return 4;    

  cout << "Successfully created component reference" << endl;

  // -------------------------------------------------------------------------
  // Instanciate Equipment in the same doc just to resolve LIF-2 
  // -------------------------------------------------------------------------
  IUnknown *pEqtInst = NULL;
  RC = InstanciateEdiInlineProduct (pContEqt,piEdiEquipmentReference,"Eqt",&pEqtInst);
  if (FAILED(RC) || !pEqtInst) return 6;

  // -------------------------------------------------------------------------
  // Create Cable Reference 
  // -------------------------------------------------------------------------  
  IUnknown* piEdiRefCable = NULL;
  const wchar_t* wchar_CablePartNumber = L"CABLE_PartNumber";
  RC = piReferenceFactoryCable->CreateEdiRoutableReference (SCHELEClass_Cable, 
       NULL,&piEdiRefCable);    
  if(FAILED(RC) || NULL == piEdiRefCable) return 5;   

  cout << "Successfully created cable reference" << endl;

  // -------------------------------------------------------------------------
  // Instanciate Cable in the same doc just to resolve LIF-2
  // -------------------------------------------------------------------------
  IUnknown *pCableInst = NULL;
  RC = InstanciateEdiInlineProduct (pContCable,piEdiRefCable,"Cable",&pCableInst);
  if (FAILED(RC) || !pCableInst) return 8;

  CATILinkableObject * pLinkCable = NULL;
  RC = piEdiRefCable->QueryInterface (IID_CATILinkableObject, (void **)&pLinkCable);
  if (FAILED(RC) || !pLinkCable) return 5;

  CATDocument *pCableRealRefDoc = NULL;
  if (pLinkCable)
  {
     pCableRealRefDoc = pLinkCable->GetDocument(); 
     pLinkCable->Release();
     pLinkCable=NULL;
  }

  if (!pCableRealRefDoc) return 5;
  
  // -------------------------------------------------------------------------
  // Add wire connectors and cable-extremity connectors to the cable reference
  // -------------------------------------------------------------------------  
  CATISchAppConnectable *piAppCntbl = NULL;
  CATISchAppConnector *piAppCntr = NULL;
  CATIEdiWire* pEdiWire1 = NULL;
  CATIEdiWire* pEdiWire2 = NULL;
  CATIEdiWire* pEdiWire3 = NULL;
  CATIEdiWire* pEdiWire4 = NULL;
  CATIEdiCableReference * pEdiCableRef = NULL;

  RC = piEdiRefCable->QueryInterface(IID_CATIEdiCableReference, (void**) &pEdiCableRef);
  if(FAILED(RC) || NULL == pEdiCableRef) return 5; 

  RC = piEdiRefCable->QueryInterface(IID_CATISchAppConnectable, (void**) &piAppCntbl);
  if(FAILED(RC) || NULL == piAppCntbl) return 5; 

  RC = pEdiCableRef->AddWire (SCHELEClass_WireCtr, NULL, &pEdiWire1);
  if(FAILED(RC) || NULL == pEdiWire1) return 5; 
  //    
  RC = pEdiCableRef->AddWire (SCHELEClass_WireCtr, NULL, &pEdiWire2);
  if(FAILED(RC) || NULL == pEdiWire2) return 5; 
  //    
  RC = pEdiCableRef->AddWire (SCHELEClass_WireCtr, NULL, &pEdiWire3);
  if(FAILED(RC) || NULL == pEdiWire3) return 5; 
  //     
  RC = pEdiCableRef->AddWire (SCHELEClass_WireCtr, NULL, &pEdiWire4);
  if(FAILED(RC) || NULL == pEdiWire4) return 5; 

  cout << "Successfully added cable wires" << endl;

  //
  // Create extremity connectors
  // ------------------------------------    
  RC = piAppCntbl->AppAddConnector (SCHELEClass_CableExtremityCtr,&piAppCntr);
  if(FAILED(RC) || NULL == piAppCntr) return 5; 
  if (piAppCntr){piAppCntr->Release();piAppCntr=NULL;}

  RC = piAppCntbl->AppAddConnector (SCHELEClass_CableExtremityCtr,&piAppCntr);
  if(FAILED(RC) || NULL == piAppCntr) return 5; 
  if (piAppCntr){piAppCntr->Release();piAppCntr=NULL;}

  cout << "Successfully added cable extremity connectors" << endl;

  if (piAppCntbl){piAppCntbl->Release();piAppCntbl=NULL;}
  if (pEdiWire1){pEdiWire1->Release();pEdiWire1=NULL;}
  if (pEdiWire2){pEdiWire2->Release();pEdiWire2=NULL;}
  if (pEdiWire3){pEdiWire3->Release();pEdiWire3=NULL;}  
  if (pEdiWire4){pEdiWire4->Release();pEdiWire4=NULL;}
  if (pEdiCableRef){pEdiCableRef->Release();pEdiCableRef=NULL;}

  // -------------------------------------------------------------------------
  // Save the Cable reference document before creating instances 
  // -------------------------------------------------------------------------
  RC = CATDocumentServices::SaveAs (*pCableRealRefDoc,
      PATHCableRef);
  if (FAILED(RC)) return 30;

  cout << "Successfully saved output document containing cable reference" << endl;

  // -------------------------------------------------------------------------
  // Instanciate Equipment Eqt1 
  // -------------------------------------------------------------------------
  IUnknown *pEqtInst1 = NULL;
  RC = InstanciateEdiInlineProduct (pCont,piEdiEquipmentReference,"Eqt1",&pEqtInst1);
  if (FAILED(RC) || !pEqtInst1) return 6;
  cout << "Successfully created instance 1 of equipment reference" << endl;

  // -------------------------------------------------------------------------
  // Instanciate Equipment Eqt2
  // -------------------------------------------------------------------------
  IUnknown *pEqtInst2 = NULL;
  RC = InstanciateEdiInlineProduct (pCont,piEdiEquipmentReference,"Eqt2",&pEqtInst2);
  if (FAILED(RC) || !pEqtInst2) return 7;
  cout << "Successfully created instance 2 of equipment reference" << endl;

  // -------------------------------------------------------------------------
  // Instanciate Cable  
  // -------------------------------------------------------------------------
  IUnknown *pCableInst1 = NULL;
  RC = InstanciateEdiInlineProduct (pCont,piEdiRefCable,"Cable1",&pCableInst1);
  if (FAILED(RC) || !pCableInst1) return 8;
  cout << "Successfully instanciated cable reference" << endl;

  // -------------------------------------------------------------------------
  // Get Cable Extremities 
  // -------------------------------------------------------------------------
  CATIEdiCable * piEdiCable = NULL;
  RC = pCableInst1->QueryInterface(IID_CATIEdiCable, (void**)& piEdiCable);
  
  if( FAILED(RC) || NULL == piEdiCable   ) return 9;

  CATIEdiCableExtremity * piEdiCableExt1 = NULL;
  CATIEdiCableExtremity * piEdiCableExt2 = NULL;
  RC = piEdiCable->GetExtremities(&piEdiCableExt1, &piEdiCableExt2);
  
  if( FAILED(RC) || NULL == piEdiCableExt1 || NULL == piEdiCableExt2   ) return 10; 

  // -------------------------------------------------------------------------
  // From cable extremity to cable 
  // -------------------------------------------------------------------------
  CATIEdiCable * piEdiRetCable = NULL;
  RC = piEdiCableExt1->GetCable(&piEdiRetCable);
  
  if( FAILED(RC) || NULL == piEdiRetCable     ) return 11;

  // -------------------------------------------------------------------------
  // Add WidePins on Equipment 1  
  // -------------------------------------------------------------------------
  CATIEdiEquipmentReference * piEdiEquipmentRef1 = NULL;
  RC = piEdiEquipmentReference ->QueryInterface(IID_CATIEdiEquipmentReference, 
    (void**)& piEdiEquipmentRef1);
  
  if( FAILED(RC)) return 12;
  
  const int NUM1 = 1; 
  const int NUM2 = 2; 
  
  const wchar_t* wcharId_WidePin1 = L"Wide Pin 1";
  const wchar_t* wcharId_WidePin2 = L"Wide Pin 2";
  
  CATIEdiWidePin *piWidePinCntr1Eqt1 = NULL;
  RC = piEdiEquipmentRef1->AddWidePin (NUM1,
    wcharId_WidePin1, 
    &piWidePinCntr1Eqt1);
  
  if( FAILED(RC) || NULL ==  piWidePinCntr1Eqt1 ) return 13;
  
  CATIEdiWidePin *piWidePinCntr2Eqt1 = NULL;
  RC = piEdiEquipmentRef1->AddWidePin (NUM2, 
    wcharId_WidePin2, 
    &piWidePinCntr2Eqt1);
  if( FAILED(RC)|| NULL == piWidePinCntr2Eqt1) return 13;  

  // -------------------------------------------------------------------------
  // WidePin list on EQT 1
  // -------------------------------------------------------------------------    
  CATIEdiEquipment* piEdiEquipmentInst1 = NULL;   
  RC = pEqtInst1->QueryInterface(IID_CATIEdiEquipment, 
    (void**)& piEdiEquipmentInst1);
  
  if( FAILED(RC)) return 14;

  CATIUnknownList* piLUKWidePins = NULL;
  RC = piEdiEquipmentInst1->ListWidePins (&piLUKWidePins);
  if( NULL == piLUKWidePins) return 15;
  
  IUnknown *piWidePinElem1 = NULL;
  IUnknown *piWidePinElem2 = NULL;
  
  piLUKWidePins->Item(0, &piWidePinElem1);
  piLUKWidePins->Item(1, &piWidePinElem2);
  
  CATIEdiWidePin* piWidePin1 = NULL;
  if(NULL == piWidePinElem1) return 16;
  RC = piWidePinElem1 -> QueryInterface(IID_CATIEdiWidePin, (void**)& piWidePin1);
  piWidePinElem1->Release();
  piWidePinElem1 = NULL;
  if( FAILED(RC)) return 16;
  
  CATIEdiWidePin* piWidePin2 = NULL;
  if(NULL == piWidePinElem2) return 17;
  RC = piWidePinElem2 -> QueryInterface(IID_CATIEdiWidePin, (void**)& piWidePin2);
  piWidePinElem2->Release();
  piWidePinElem2 = NULL;
  if( FAILED(RC)) return 17;

  unsigned uSizeCntrs = 0;
  piLUKWidePins->Count(&uSizeCntrs);
  if (uSizeCntrs != 2) return 18;
  
  piLUKWidePins -> Release();
  piLUKWidePins = NULL;

  // -------------------------------------------------------------------------
  // From WidePin to equipment 
  // -------------------------------------------------------------------------
  IUnknown *piEdiRetEquipment = NULL;
  RC = piWidePinCntr2Eqt1->GetDevice(&piEdiRetEquipment);
  
  if( FAILED(RC) || NULL == piEdiRetEquipment     ) return 19;
  piEdiRetEquipment->Release();
  piEdiRetEquipment = NULL;

  // -------------------------------------------------------------------------
  // Connect CABLE/Ext1 on EQT1/Pin1   
  // -------------------------------------------------------------------------
  RC = piEdiCableExt1->Connect (piWidePin1);
  if( FAILED(RC)) return 20;

  // -------------------------------------------------------------------------
  // From CABLE/Ext1 to EQT1/Pin1 
  // -------------------------------------------------------------------------
  CATIEdiWidePin *piFromToWidePin = NULL;
  RC = piEdiCableExt1->GetConnectedWidePin (&piFromToWidePin);
  
  if( FAILED(RC) || NULL == piFromToWidePin) return 21;

  // -------------------------------------------------------------------------
  // From EQT1/Pin1 to CABLE/Ext1
  // -------------------------------------------------------------------------
  CATIUnknownList* piLCableExtremities = NULL;
  RC = piWidePin1->ListConnectedCableExtremities (&piLCableExtremities);
  
  if( FAILED(RC) || NULL == piLCableExtremities ) return 22;

  // -------------------------------------------------------------------------
  // Remove EQT1/Pin1 - must never do this with instance connector!
  // -------------------------------------------------------------------------
  // RC = piFromToWidePin->Remove();
  // if (FAILED(RC)) return 23;

  // -------------------------------------------------------------------------
  // Remove EQT1/Pin1 by removing connector reference, not an instance
  // -------------------------------------------------------------------------
  CATIEdiWidePin *piWidePinRef = NULL;
  CATISpecObject *piSpecInst = NULL;
  RC = piFromToWidePin->QueryInterface(IID_CATISpecObject, (void**)&piSpecInst);
  if (FAILED(RC)) return 31;

  CATISpecObject *piSpecRef = piSpecInst->GetReference();
  if (NULL == piSpecRef) return 32;

  RC = piSpecRef->QueryInterface(IID_CATIEdiWidePin,(void**)&piWidePinRef);
  if (FAILED(RC)) return 33;

  RC = piWidePinRef->Remove();
  if (FAILED(RC)) return 34;

  if (piWidePinRef != NULL) {piWidePinRef->Release(); piWidePinRef=NULL;}
  if (piSpecInst != NULL) {piSpecInst->Release(); piSpecInst=NULL;}
  if (piSpecRef != NULL) {piSpecRef->Release(); piSpecRef=NULL;}

  if (piFromToWidePin != NULL) piFromToWidePin -> Release();

  // -------------------------------------------------------------------------
  // From CABLE/Ext1 to EQT1/Pin1
  // -------------------------------------------------------------------------
  CATIEdiWidePin *piWidePinBid = NULL;
  RC = piEdiCableExt1->GetConnectedWidePin (&piWidePinBid);
  
  if(NULL != piWidePinBid ) return 24;    

  // -------------------------------------------------------------------------
  // Connect CABLE/Ext1 on EQT1/Pin2 
  // -------------------------------------------------------------------------
  RC = piEdiCableExt1->Connect (piWidePin2);
  if (FAILED(RC)) return 25;
  
  // -------------------------------------------------------------------------
  // Disconnect CABLE/Ext1 on EQT1/Pin2 
  // -------------------------------------------------------------------------
  RC = piEdiCableExt1->Disconnect ();
  if (FAILED(RC)) return 26;
  
  // -------------------------------------------------------------------------
  // Connect CABLE/Ext1 on EQT1/Pin2 
  // -------------------------------------------------------------------------
  RC = piEdiCableExt1->Connect (piWidePin2);
  if (FAILED(RC)) return 27;
  
  // -------------------------------------------------------------------------
  // Cable to Equipments
  // -------------------------------------------------------------------------
  CATIUnknownList* piLUKEquipments = NULL;
  RC = piEdiCable->ListAssociatedDevices (&piLUKEquipments);
  if(NULL == piLUKEquipments) return 28;
  
  unsigned uSizeEquipments = 0;
  piLUKEquipments->Count(&uSizeEquipments);
  if(uSizeEquipments != 1) return 29;
  
  if(piLUKEquipments != NULL) piLUKEquipments ->Release();  


  // Release...    
  if (pCont != NULL) pCont ->Release();
  if (pContEqt != NULL) pContEqt ->Release();
  if (pContCable != NULL) pContCable ->Release();
  if (piReferenceFactoryEqt != NULL) piReferenceFactoryEqt ->Release();
  if (piReferenceFactoryCable != NULL) piReferenceFactoryCable ->Release();
  if (piEdiEquipmentReference != NULL) piEdiEquipmentReference ->Release();
  if(piWidePinCntr1Eqt1 != NULL) piWidePinCntr1Eqt1 -> Release();
  if(piWidePinCntr2Eqt1 != NULL) piWidePinCntr2Eqt1 -> Release();  
  if(piLCableExtremities != NULL) piLCableExtremities -> Release();
  if(piWidePin1 != NULL) piWidePin1 -> Release(); 
  if(piWidePin2 != NULL) piWidePin2 -> Release();  
  if(piWidePinBid != NULL) piWidePinBid ->Release();
  if(piEdiRefCable != NULL)  piEdiRefCable->Release();
  if(piEdiRetCable != NULL)  piEdiRetCable->Release();
  if(piEdiEquipmentRef1 != NULL)  piEdiEquipmentRef1->Release();
  if(piEdiEquipmentInst1 != NULL)  piEdiEquipmentInst1->Release();
  if(piEdiCable != NULL)  piEdiCable->Release();
  // 
  if ( NULL != piEdiCableExt1 ) piEdiCableExt1->Release();
  piEdiCableExt1 = NULL;
  if ( NULL != piEdiCableExt2 ) piEdiCableExt2->Release();
  piEdiCableExt2 = NULL;
  //
  if (pCableInst){pCableInst->Release(); pCableInst = NULL;}
  if (pCableInst1){pCableInst1->Release(); pCableInst1 = NULL;}
  if (pEqtInst)  {pEqtInst->Release();   pEqtInst = NULL;}
  if (pEqtInst1)  {pEqtInst1->Release();   pEqtInst1 = NULL;}
  if (pEqtInst2)  {pEqtInst2->Release();   pEqtInst2 = NULL;}

  // -------------------------------------------------------------------------
  // Save document 
  // -------------------------------------------------------------------------
  RC = CATDocumentServices::SaveAs (*pCATDocument1,
      PATHInst);  
  if (FAILED(RC)) return 30;

  cout << "Successfully saved output document containing instances" << endl;

  RC = CATDocumentServices::SaveAs (*pCATDocumentEqt,
      PATHCompRef);
  if (FAILED(RC)) return 30;

  cout << "Successfully saved output document containing component references" << endl;

  // -------------------------------------------------------------------------
  // Object Modeler Session Destroyed
  // -------------------------------------------------------------------------
  ::Delete_Session(psessionIdent);
  return 0;
}
