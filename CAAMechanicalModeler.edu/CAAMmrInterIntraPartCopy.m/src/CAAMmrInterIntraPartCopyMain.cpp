// COPYRIGHT DASSAULT SYSTEMES  2000 
//==========================================================================
//
//	Abstract: This program shows how to copy mechanical objects from a Part document:
//                 - to another Part document with or without the context product, 
//                 - into the same Part,
//
//            using the CATMmrInterPartCopy class.
//
//            It is based on the CAAMmrPartCopy Product document. This 
//            document is composed of four components:
//            
//            
//                - Root Product
//                     . Comp1 -> CAAMmrPartCopy_Comp1.CATPart ( with a matrix )
//                     . Product2 (a Product with a Matrix)
//                         . Comp3 -> CAAMmrPartCopy_Comp3.CATPart ( with a matrix )
//                     . Comp4 -> CAAMmrPartCopy_Comp1.CATPart ( without matrix )
//
//            Comp1/Comp4: The CAAMmrPartCopy_Comp1 Part document contains the following data
//       
//                - Part
//                     . PartBody  
//                               
//                     . Geometrical Set.1
//                     . Geometrical Set.2  (set as the current object)
//                     . Ordered Geometrical Set.3 
//
//            Comp3: The CAAMmrPartCopy_Comp3 Part document contains the following data
//       
//                - Part
//                     . PartBody  
//                         . Sketch.1
//                         . Pad.1
//                         . EdgeFillet.1                         
//
//                     . Geometrical Set.1  
//                         . Point.1
//                         . Point.2
//                         . Point.3
//                       Ordered Geometrical Set.2
//                         . Sketch.2  (the current feature)
//                         . Extrude.1
//                         . Split.1                 
//        
//           The CAAMmrPartCopy.CATProduct and its included Part documents are
//           located in the CAAMechanicalModeler.edu/InputData directory.
//
//           What kind of copies it does: 
//            
//            1/ Copies between two Part documents 
//
//              - Copy PartBody of Comp3 into Part of Comp1
//              - Copy Point.1  of Comp3 into Part of Comp1   
//              - Copy Point.2  of Comp3 into PartBody of Comp1 
//              - Copy Point.3  of Comp3 into Geometrical Set.1 of Comp1  
//              - Copy Geometrical Set.1 of Comp3 into Part of Comp1  
//              - Copy Ordered Geometrical Set.2 of Comp3 into PartBody of Comp1      
//              - Copy Ordered Geometrical Set.2 of Comp3 into OGS3 of Comp1  
//  
//             Note: An option of the use case enables you to choose context
//              - 1: Product structure context
//              - Otherwise: no Product structure context

//            2/ Copies between the same Part document 
// 
//              - Copy PartBody of Comp3 into Part of Comp3
//              - Copy Point.1  of Comp3 into Part of Comp3 
//              - Copy Point.2  of Comp3 into PartBody of Comp3
//              - Copy Point.3  of Comp3 into Geometrical Set.2 of Comp3
//
//
//            In the two cases, an option of the use case enables you to choose the kind of copy
//              - 1: Copy and paste As Result with link
//              - Otherwise: Copy and paste As Result (without link)
//       
//
//  Steps :
//    1.   Opens the session
//    2.   Opens the CAAMmrPartCopy Product document
//    3.   Retrieves objects useful for the copy
//      3.1 Root product
//      3.2 Comp1, Comp2 and Comp3, the three components of the root product
//      3.3 Objects from Comp3: The Part, PartBody, Point.1, Point.2, Point.3
//      3.4 Objects from Comp1: The Part, GeomSet.1,
//    4.   Copies between two Part Documents
//      4.1   Copy PartBody of Comp3 into Part      of Comp1
//      4.2   Copy Point.1  of Comp3 into Part      of Comp1 
//      4.2b  Copy Point.3  of Comp3 into PartBody  of Comp1 
//      4.3   Copy Point.2  of Comp3 into GeomSet.1 of Comp1 
//      4.4   Copy Geometrical Set.1 of Comp3 into Part of Comp1 
//      4.5   Copy Ordered Geometrical Set.2 of Comp3 into PartBody of Comp1 
//      4.6   Copy Ordered Geometrical Set.2 of Comp3 into OGS3 of Comp1 
//    5.   Copies in the Same Document
//      5.1   Copy PartBody of Comp3 into Part      of Comp3
//      5.2   Copy Point.1  of Comp3 into Part      of Comp3 
//      5.3   Copy Point.3  of Comp3 into PartBody  of Comp3   
//      5.4   Copy Point.2  of Comp3 into Ordered Geometrical Set.2 of Comp3 
//    6.   Saves as the modified documents
//      6.1 Saves CAAMmrPartCopy_Comp1  
//      6.2 Saves CAAMmrPartCopy_Comp3 
//      6.3 Saves CAAMmrProduct2  
//      6.4 Saves CAAMmrPartCopy  
//    7.   Closes all the documents
//    8.   Deletes the session
//
//
//==========================================================================
// How to execute :
// 
//   CAAMmrPartCopy InputPath CopyOption [OutputPath]
//
//   with     InputPath   : $WSROOT/CAAMechanicalModeler.edu/InputData
//            CopyOption  : 1: Paste As Result with Link, 2: Paste As Result (without link)
//            OutputPath  : directory to save the result
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
#include "CATIDocRoots.h"
#include "CATIAlias.h"
#include "CATSession.h"
#include "CATILinkableObject.h"

// Product Structure
#include "CATIProduct.h"

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // To get the MechanicalPart,and element of the OpenBody1

// MechanicalModeler
#include "CATMmrInterPartCopy.h"         // To copy mechanical feature

// System Framework
#include "CATString.h"
#include "CATBoolean.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// Local Framework
#include "CAAMmrGetGeometry.h"           // To retrieve features
#include "CAAMmrGetPartFromProduct.h"    // To retrieve the Part from a Product 

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
  if ((4 != iArgc) && ( 5 != iArgc) ) 
  {
     cout << endl;
     cout << "CAAMmrInterIntraPartCopy InputPath Copy_Option PS_Option"<< endl;
     cout << "with : InputPath : $WSROOT/CAAMechanicalModeler.edu/InputData"<< endl;
     cout << "       Copy_Option:  1= Paste with Link, otherwise Paste As Result " << endl;
     cout << "       PS_Option:  PS= Assembly context, otherwise= without Assembly context " << endl;
     cout << endl;
     return 1;
  }
  cout << "The CAAMmrInterIntraPartCopy main program begins ...."<< endl << endl;
  
  // The type of copy option 
  CATBoolean CopyWithLink = FALSE ;
  CATString CopyOption = iArgv[2] ;
  if ( ! strcmp("1",CopyOption) )
  {
      cout <<"      Copy As Result with link" << endl;
      CopyWithLink = TRUE ;

  }else 
  {
     cout <<"      Copy As Result without link" << endl;
  }

  // The copy between documents: with or without PS context
  CATBoolean PSContext = FALSE ;
  CATString PSOption = iArgv[3] ;
  if ( ! strcmp("PS",PSOption) )
  {
      cout <<"      The copy between documents is with Product context" << endl;
      PSContext = TRUE ;

  }else 
  {
     cout <<"      The copy between documents is without Product context" << endl;
  }

  //------------------------------------------------------------------
  //1 - Creates Session
  //------------------------------------------------------------------

  char * pSessionName = "CAA_Sample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);
		                          
  if (FAILED(rc) )
  {
      return 1;
  }
  cout <<"   A session is created" << endl;

  //-----------------------------------------
  //2- Opens the CAAMmrPartCopy document 
  //-----------------------------------------

  CATDocument *pProductDocument = NULL;
  CATString InputData = iArgv[1] ;
  CATString DocumentProductName  = InputData + Slash + "CAAMmrPartCopy.CATProduct";

  rc = CATDocumentServices::OpenDocument(DocumentProductName.ConvertToChar(), pProductDocument);
  if ( FAILED(rc) || ( NULL == pProductDocument) )
  {
     return 1;
  }
  
  cout << "   The "<< DocumentProductName.ConvertToChar() <<" document is opened" << endl ;
  
  //------------------------------------------------------
  // 3- Retrieves objects useful for the copies
  //------------------------------------------------------

  //
  // 3-1 The root product
  // 
  CATIProduct * piProductOnRoot = NULL;

  CATIDocRoots * piDocRootsOnDoc = NULL;
  rc = pProductDocument->QueryInterface(IID_CATIDocRoots,(void**) &piDocRootsOnDoc);
                          
  if ( SUCCEEDED(rc) ) 
  {
     // Gets the root product which is the first element of root elements
     CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc->GiveDocRoots();
   
     if ( NULL == pRootProducts )
     {
        return 1 ;
     }

     if (pRootProducts->Size() > 0 )
     {  
        CATBaseUnknown_var spRootProduct = (*pRootProducts)[1];
     
        // Gets CATIProduct handle on the root product.
        if ( NULL_var != spRootProduct )
        {
           rc = spRootProduct->QueryInterface(IID_CATIProduct,(void**) &piProductOnRoot);     
        }

        delete pRootProducts;
        pRootProducts = NULL;
     }
     piDocRootsOnDoc->Release();
     piDocRootsOnDoc = NULL ;
  }

  if ( NULL == piProductOnRoot )
  {
     return 1 ;
  }
  
  cout <<"   The root product has been found" << endl;
  
  //
  // 3-2 The components of the root product
  // 
  CATListValCATBaseUnknown_var * pListDirectChildren = piProductOnRoot->GetChildren(); 
  if ( (NULL ==pListDirectChildren) || ( pListDirectChildren->Size() !=3) )
  {
        return 1 ;
  }

  piProductOnRoot->Release();
  piProductOnRoot = NULL ;

  // Comp1 and Comp2
  CATIProduct_var spComp1 = (*pListDirectChildren)[1] ;
  CATIProduct_var spComp2 = (*pListDirectChildren)[2] ;

  if ( (NULL_var == spComp1) || (NULL_var == spComp2) )
  {
        return 1 ;
  }
  cout << "   The direct children of the root product has been found" << endl;
  
  delete pListDirectChildren ;
  pListDirectChildren = NULL ;

  // The component of Comp2
  pListDirectChildren = spComp2->GetChildren(); 
  if ( (NULL ==pListDirectChildren) || (pListDirectChildren->Size()!=1) )
  {
        return 1 ;
  }

  // Comp3
  CATIProduct_var spComp3 = (*pListDirectChildren)[1] ;

  if ( NULL_var == spComp3 )
  {
        return 1 ;
  }

  delete pListDirectChildren ;
  pListDirectChildren = NULL ;

  cout <<"   The third component of the root product has been found" << endl;

  //
  // 3-3 Retrieves objects of CAAMmrPartCopy_Comp3 (Comp3)
  //
  cout <<"   Retrieving Objects of CAAMmrPartCopy_Comp3" << endl;

  // The Part feature
  CATISpecObject_var spSpecObjectOnMechPartOfComp3  ;
  rc = ::CAAMmrGetPartFromProduct(spComp3, spSpecObjectOnMechPartOfComp3);
  
  if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfComp3) )
  {    
     return 1 ;
  }
  cout << "      The Part feature has been found" << endl;

  // The PartBody feature
  CATBaseUnknown * pBody = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp3,"PartBody",&pBody);
  if ( FAILED(rc) || ( NULL == pBody) )
  {    
     return 1 ;
  }

  CATBaseUnknown_var spOnBodyOfComp3 = pBody ;
  pBody->Release();
  pBody = NULL ;

  cout << "      The PartBody feature has been found" << endl;

  // The Point.1 feature 
  CATBaseUnknown * pPoint = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp3,"Point.1",&pPoint);
  if ( FAILED(rc) || ( NULL == pPoint) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnPoint1OfComp3 = pPoint ;
  pPoint->Release();
  pPoint = NULL ;

  cout << "      The Point.1 feature has been found" << endl;
 
  // The Point.2 feature 
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp3,"Point.2",&pPoint);
  if ( FAILED(rc) || ( NULL == pPoint) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnPoint2OfComp3 = pPoint ;
  pPoint->Release();
  pPoint = NULL ;

  // The Point.3 feature 
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp3,"Point.3",&pPoint);
  if ( FAILED(rc) || ( NULL == pPoint) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnPoint3OfComp3 = pPoint ;
  pPoint->Release();
  pPoint = NULL ;

  cout << "      The Point.1 feature has been found" << endl;
   // The Geometrical Set.1 feature 
  CATBaseUnknown * pGS = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp3,"Geometrical Set.1",&pGS);
  if ( FAILED(rc) || ( NULL == pGS) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnGeomSet1OfComp3 = pGS ;
  pGS->Release();
  pGS = NULL ;

  cout << "      The Geometrical Set.1 feature has been found" << endl;

  // The Ordered Geometrical Set.2 feature 
  CATBaseUnknown * pOGS = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp3,"Ordered Geometrical Set.2",&pOGS);
  if ( FAILED(rc) || ( NULL == pOGS) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnOrderedGeomSet2OfComp3 = pOGS ;
  pOGS->Release();
  pOGS = NULL ;

  cout << "      The Ordered Geometrical Set.2 feature has been found" << endl;


  //
  // 3-4 Retrieves objects of CAAMmrPartCopy_Comp1 (Comp1)
  //
  cout <<"   Retrieving elements of CAAMmrPartCopy_Comp1" << endl;

  // The Part feature
  CATISpecObject_var spSpecObjectOnMechPartOfComp1  ;
  rc = ::CAAMmrGetPartFromProduct(spComp1,spSpecObjectOnMechPartOfComp1);

  if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfComp1) )
  {    
     return 1 ;
  }
  cout << "      The Part feature has been found" << endl;

  // The PartBody feature
  pBody = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp1,"PartBody",&pBody);
  if ( FAILED(rc) || ( NULL == pBody) )
  {    
     return 1 ;
  }

  CATBaseUnknown_var spOnBodyOfComp1 = pBody ;
  pBody->Release();
  pBody = NULL ;
  cout << "      The PartBody feature has been found" << endl;


  // The GeometricalSet.1 feature
  CATBaseUnknown * pSet = NULL ;
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp1,"Geometrical Set.1",&pSet);
  if ( FAILED(rc) || ( NULL == pSet) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnGeomSet1OfComp1 = pSet ;
  pSet->Release();
  pSet = NULL ;

  cout << "      The GeometricalSet.1 feature has been found" << endl;

  // The GeometricalSet.2 feature
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp1,"Geometrical Set.2",&pSet);
  if ( FAILED(rc) || ( NULL == pSet) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnGeomSet2OfComp1 = pSet ;
  pSet->Release();
  pSet = NULL ;

  cout << "      The GeometricalSet.2 feature has been found" << endl;

  // The Ordered GeometricalSet.3 feature
  rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfComp1,"Ordered Geometrical Set.3",&pOGS);
  if ( FAILED(rc) || ( NULL == pOGS) )
  {
     return 1 ;
  }
  CATBaseUnknown_var spOnOrderedGeomSet3OfComp1 = pOGS ;
  pOGS->Release();
  pOGS = NULL ;

  cout << "      The Ordered Geometrical Set.3 feature has been found" << endl << endl;

  //---------------------------------------------------
  // 4- Copies between two Part documents  
  //---------------------------------------------------

  //
  // 4-1  Copy PartBody of Comp3 into Comp1
  //
  cout <<"   Copy PartBody of CAAMmrPartCopy_Comp3 into CAAMmrPartCopy_Comp1 EGD" << endl;

  CATMmrInterPartCopy * ptCATMmrInterPartCopy = NULL ;

  CATISpecObject_var SourceToCopy = spOnBodyOfComp3 ;
  CATISpecObject_var Target       = spSpecObjectOnMechPartOfComp1 ;

  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
                                                    
                                                    
  // The product source  
  if ( TRUE == PSContext )
  {
     ptCATMmrInterPartCopy ->SetSourceInstance(spComp3);
     ptCATMmrInterPartCopy ->SetTargetInstance(spComp1);
  }

  // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 
  
  // Executes the copy
  CATUnicodeString ErrorMsg ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  CATISpecObject_var Result ;
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }
  }else return 1 ;


  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //
  // 4-2  Copy of Point.1 of Comp3 into Comp1
  //

  cout <<"   Copy Point.1 of CAAMmrPartCopy_Comp3 into CAAMmrPartCopy_Comp1" << endl;
  
  SourceToCopy = spOnPoint1OfComp3 ;
  Target       = spSpecObjectOnMechPartOfComp1 ;
  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
 
  // The product source                                               
  if ( TRUE == PSContext )
  {
     ptCATMmrInterPartCopy ->SetSourceInstance(spComp3);
     ptCATMmrInterPartCopy ->SetTargetInstance(spComp1);
  }

   // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 

  // Executes the copy
  ErrorMsg = "" ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc)  && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }

  }else return 1 ;

  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //
  // 4-2-bis  Copy of Point.2 of Comp3 into Comp1
  //

  cout <<"   Copy Point.2 of CAAMmrPartCopy_Comp3 into CAAMmrPartCopy_Comp1" << endl;
  
  SourceToCopy = spOnPoint2OfComp3 ;
  Target       = spOnBodyOfComp1 ;
  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
 
  // The product source                                               
  if ( TRUE == PSContext )
  {
     ptCATMmrInterPartCopy ->SetSourceInstance(spComp3);
     ptCATMmrInterPartCopy ->SetTargetInstance(spComp1);
  }

   // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 

  // Executes the copy
  ErrorMsg = "" ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc)  && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }

  }else return 1 ;

  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //
  // 4-3  Copy of Point.3 of Comp3 into Geometrical Set.1 of Comp1
  //

  cout <<"   Copy Point.3 of CAAMmrPartCopy_Comp3 into Geometrical Set.1 of CAAMmrPartCopy_Comp1" << endl;

  SourceToCopy = spOnPoint3OfComp3 ;
  Target       = spOnGeomSet1OfComp1 ;
  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
 
  // The product source                                              
  if ( TRUE == PSContext )
  {
     ptCATMmrInterPartCopy ->SetSourceInstance(spComp3);
     ptCATMmrInterPartCopy ->SetTargetInstance(spComp1);
  }

   // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink);

  // Executes the copy
  ErrorMsg = "" ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var spAlias = Result  ;
      if ( NULL_var != spAlias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << spAlias->GetAlias().ConvertToChar() << endl << endl;
      }

  } else return 1 ;

  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //
  // 4-4  Copy of Geometrical Set.1 of Comp3 into Part of Comp1
  //
  cout <<"   Copy Geometrical Set.1 of CAAMmrPartCopy_Comp3 into CAAMmrPartCopy_Comp1" << endl;

  SourceToCopy = spOnGeomSet1OfComp3 ;
  Target       = spSpecObjectOnMechPartOfComp1 ;

  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
                                                    
                                                    
  // The product source                                               
  if ( TRUE == PSContext )
  {
     ptCATMmrInterPartCopy ->SetSourceInstance(spComp3);
     ptCATMmrInterPartCopy ->SetTargetInstance(spComp1);
  }

  // Sets the option of copy
  ptCATMmrInterPartCopy ->SetLinkMode(FALSE) ; 
  
  
  // Executes the copy
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }

  }else return 1 ;


  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;


  //
  // 4-5  Copy of Ordered Geometrical Set.2 of Comp3 into PartBody of Comp1
  //
  cout <<"   Copy OGS 2 of CAAMmrPartCopy_Comp1 into PartBody of CAAMmrPartCopy_Comp3" << endl;

  SourceToCopy = spOnOrderedGeomSet2OfComp3 ;
  Target       = spOnBodyOfComp1 ;

  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
                                                    
                                                    
  // The product source                                               
  if ( TRUE == PSContext )
  {
     ptCATMmrInterPartCopy ->SetSourceInstance(spComp3);
     ptCATMmrInterPartCopy ->SetTargetInstance(spComp1);
  }

  // Sets the option of copy
  ptCATMmrInterPartCopy ->SetLinkMode(FALSE) ; 
  
  
  // Executes the copy
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }

  }else return 1 ;


  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //
  // 4-6  Copy of Ordered Geometrical Set.2 of Comp3 into OGS3 of Comp1
  //
  cout <<"   Copy OGS 2 of CAAMmrPartCopy_Comp1 into OGS 3 CAAMmrPartCopy_Comp3" << endl;

  SourceToCopy = spOnOrderedGeomSet2OfComp3 ;
  Target       = spOnOrderedGeomSet3OfComp1 ;

  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
                                                    
                                                    
  // The product source                                               
  if ( TRUE == PSContext )
  {
     ptCATMmrInterPartCopy ->SetSourceInstance(spComp3);
     ptCATMmrInterPartCopy ->SetTargetInstance(spComp1);
  }

  // Sets the option of copy
  ptCATMmrInterPartCopy ->SetLinkMode(FALSE) ; 
  
  
  // Executes the copy
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }

  }else return 1 ;


  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //---------------------------------------------------
  // 5- Copies Between the Same Part Document 
  //---------------------------------------------------
 
  //
  // 5-1  Copy PartBody of Comp3 
  //
  cout <<"   Copy PartBody of CAAMmrPartCopy_Comp3 into Part" << endl;

  ptCATMmrInterPartCopy = NULL ;

  SourceToCopy = spOnBodyOfComp3 ;
  Target       = spSpecObjectOnMechPartOfComp3 ;

  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
                                                                                                     

  // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 
  
  // Executes the copy
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }
  }else return 1 ;


  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //
  // 5-2  Copy of Point.1 of Comp3 
  //

  cout <<"   Copy Point.1 of CAAMmrPartCopy_Comp3 into Part" << endl;
  
  SourceToCopy = spOnPoint1OfComp3 ;
  Target       = spSpecObjectOnMechPartOfComp3 ;
  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
 

   // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 

  // Executes the copy
  ErrorMsg = "" ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc)  && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }

  }else return 1 ;

  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

   //
  // 5-3  Copy of Point.2 of Comp3 
  //

  cout <<"   Copy Point.2 of CAAMmrPartCopy_Comp3 into Part" << endl;
  
  SourceToCopy = spOnPoint2OfComp3 ;
  Target       = spOnBodyOfComp3 ;
  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
 

   // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 

  // Executes the copy
  ErrorMsg = "" ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc)  && (NULL_var != Result) )
  {
      CATIAlias_var alias = Result  ;
      if ( NULL_var != alias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << alias->GetAlias().ConvertToChar() << endl << endl;
      }

  }else return 1 ;

  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //
  // 5-4  Copy of Point.3 of Comp3 into Ordered Geometrical Set.2 of Comp3
  //

  cout <<"   Copy Point.3 of CAAMmrPartCopy_Comp3 into Ordered Geometrical Set.2 of Comp3" << endl;

  SourceToCopy = spOnPoint3OfComp3 ;
  Target       = spOnOrderedGeomSet2OfComp3 ;
  ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;
 
   // Sets the option of copy 
  ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink);

  // Executes the copy
  ErrorMsg = "" ;
  rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
  if ( FAILED(rc) )
  {
      cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
      return 1 ;
  }
  cout <<"      Run is ok" << endl;

  // Retrieves the result
  rc = ptCATMmrInterPartCopy ->GetResult(Result);
  if ( SUCCEEDED(rc) && (NULL_var != Result) )
  {
      CATIAlias_var spAlias = Result  ;
      if ( NULL_var != spAlias )
      {
         cout <<"      The result of the copy is" ;
         cout <<" " << spAlias->GetAlias().ConvertToChar() << endl << endl;
      }

  } else return 1 ;

  delete ptCATMmrInterPartCopy ;
  ptCATMmrInterPartCopy = NULL ;

  //---------------------------------------------------------
  // 6- Saves documents
  //---------------------------------------------------------

  //
  // 6-1 Saves as CAAMmrPartCopy_Comp1.CATPart
  //

  CATDocument * pPartDocument = NULL ;

  CATIProduct_var  spRef = spComp1->GetReferenceProduct();
  
  if ( NULL_var != spRef )
  {
     CATILinkableObject * piLinkableObject = NULL;
     rc = spRef->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );                            

     if ( SUCCEEDED(rc) )
     {
        // Do not release this pointer       
        pPartDocument = piLinkableObject->GetDocument();

        piLinkableObject->Release();
        piLinkableObject = NULL ;
     }
  }

  if ( NULL == pPartDocument )
  {
      return 1 ;
  }
  
  CATString DocumentSaveName = InputData + Slash + "CAAMmrPartCopy_Comp1.CATPart";
  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs (*pPartDocument,DocumentSaveName.ConvertToChar());
  if (FAILED(rc)) 
  {
     return 1;
  }
  
  cout << endl; 
  cout << "   The "<< DocumentSaveName.ConvertToChar() << " document is saved" << endl ;

  //
  // 6-2 Saves as CAAMmrPartCopy_Comp3.CATPart
  //

  spRef = spComp3->GetReferenceProduct();
  
  if ( NULL_var != spRef )
  {
     CATILinkableObject * piLinkableObject = NULL;
     rc = spRef->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );                            

     if ( SUCCEEDED(rc) )
     {
        // Do not release this pointer       
        pPartDocument = piLinkableObject->GetDocument();

        piLinkableObject->Release();
        piLinkableObject = NULL ;
     }
  }

  if ( NULL == pPartDocument )
  {
      return 1 ;
  }
  
  DocumentSaveName = InputData + Slash + "CAAMmrPartCopy_Comp3.CATPart";
  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs (*pPartDocument,DocumentSaveName.ConvertToChar());
  if (FAILED(rc)) 
  {
     return 1;
  }
  
  cout << "   The "<< DocumentSaveName.ConvertToChar() << " document is saved" << endl ;
  
  //
  // 6-3 Saves as Product2
  //

  spRef = spComp2->GetReferenceProduct();
  
  if ( NULL_var != spRef )
  {
     CATILinkableObject * piLinkableObject = NULL;
     rc = spRef->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );                            

     if ( SUCCEEDED(rc) )
     {
        // Do not release this pointer       
        pPartDocument = piLinkableObject->GetDocument();

        piLinkableObject->Release();
        piLinkableObject = NULL ;
     }
  }

  if ( NULL == pPartDocument )
  {
      return 1 ;
  }
  
  DocumentSaveName = InputData + Slash + "CAAMmrProduct2.CATProduct";
  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs (*pPartDocument,DocumentSaveName.ConvertToChar());
  if (FAILED(rc)) 
  {
     return 1;
  }
  
  cout << "   The "<< DocumentSaveName.ConvertToChar() << " document is saved" << endl ;

  //
  // 6-4 Saves as the CAAMmrPartCopy document
  //
  //
  // Attention, save as the product document does not save its included Part documents 
  // in batch mode.It's why the  modified part document as been saved previoulsy 
  //
  DocumentSaveName = InputData + Slash + "CAAMmrPartCopy.CATProduct" ;
  
  // @CSC-Filter UNER
  rc = CATDocumentServices::SaveAs (*pProductDocument,DocumentSaveName.ConvertToChar());
  if (FAILED(rc)) 
  {
     return 1;
  }
  cout << "   The "<< DocumentSaveName.ConvertToChar() << " document is saved" << endl ;

  //---------------------------------------------------
  // 7- Closes document
  //---------------------------------------------------
 
  // Removes the product, it removes the included Part documents too
  rc = CATDocumentServices::Remove (*pProductDocument);
  if (FAILED(rc)) 
  {
     return 1;
  }
  cout << endl;
  cout << "   The "<< DocumentProductName.ConvertToChar() ;
  cout <<" document and its included files are closed" << endl ;
      
  pProductDocument = NULL ;
  pPartDocument    = NULL ;

  //-------------------
  // 8- Deletes session
  //-------------------

  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc)) 
  {
     return 1;
  }  
  cout<<"   The session is deleted"<< endl << endl;

  cout <<"The CAAGviApplyProperties main program is ended."<< endl << endl;

  return 0;
}
