// COPYRIGHT DASSAULT SYSTEMES 2000
//----------------------------------------------------------------------------------
// CAAOmmBuildCatalog.cpp                                           
//----------------------------------------------------------------------------------
//
//  Abstract:
//  ---------
//
//  Batch program which generates a catalog for the CAAOmmVerticalLine feature
//    
//  Illustrates:
//     o -1- Creating a path to the catalog.
//     o -2- Creating the catalog.
//     o -3- Adding a client identification to the catalog.
//     o -4- Calling Shape Design start-up factory to get our new startup's father startup.
//     o -5- Adding attributes to this startup.
//     o -6- Saving the catalog.
//    
//----------------------------------------------------------------------------------
//
//  Usage:
//  ------
//
//  Type:
//     o CAAOmmBuildCatalog <directory name>
//
//  Example under Windows NT : 
//     o CAAOmmBuildCatalog E:\CAAV5WS
//     o then copy CAAOmmCatalog.CATfct to CAAOLE4MecMod.edu\CNext\resources\graphic
//     o then generate the runtimeview : mkCreateRuntimeView
//
//  NB : to be found at run-time, catalog must be in a resources\graphic directory.
//
//----------------------------------------------------------------------------------


// code commented the 17th of April 2012
// obsolete code : proper way to manage catalog has changed and don't uses C++ code but the executable CATfctEditorAssistant 


// ObjectModelerBase Framework
//#include "CATSessionServices.h"         // needed to manage session
//
//// ObjectSpecsModeler Framework
//#include "CATOsmSUFactory.h"            // To derive from the GSMGeom StartUp
//#include "CATCatalogFactoryServices.h"  // needed to create a catalog
//#include "CATICatalog.h"                // needed to manage catalogs
//#include "CATISpecObject.h"             // needed to manage features such as the vertical line startup
//#include "CATISpecAttribute.h"          // needed to add attributes to the vertical line startup
//
//// System Framework
//#include "CATUnicodeString.h"           // needed to give the catalog name
//#include "CATLib.h"                     // needed to create the path to the catalog file
//
//// Others
//#include <iostream.h>                   // needed for traces
//
//int main (int argc, char * argv[] )
//{ 
//    //----------------------------------------------------------------------------------
//    // -1- Creating a path to the catalog.
//    //  o  "main" first argument is directory path : to use your catalog, it should be
//    //     located under resources\graphic directory.
//    //  o  Catalog file name is set to CAAOmmCatalog.
//    //----------------------------------------------------------------------------------
//    cout << "-1- Creating a path to the catalog." << endl << flush;
//    if ( argc < 2) {
//        cout << "    ERROR  : no directory path given." << endl;
//        return 1;
//        }
//    
//    // CATMakePath of CATLib.h creates an os dependant path.
//    const char *pDirName     = argv[1];
//    const char *pFileName    = "CAAOmmCatalog";
//    char       StorageName[200];
//    CATMakePath( pDirName , pFileName , StorageName );
//  
//    // Creating a session.     
//    cout << "    Creating a session." << endl << flush;
//
//    char       *pSessionName = "CAA_OLE4MecMod_Session";
//    CATSession *pSession     = NULL;
//    HRESULT rc = ::Create_Session( pSessionName , pSession );
//    if ( SUCCEEDED(rc) )
//        cout << "    Session creation OK." << endl << flush;
//    else {
//        cout << "    ERROR in creating the session." << endl << flush;
//        return 1;
//        }
//        
//    //----------------------------------------------------------------------------------
//    // -2- Creating the catalog.
//    //     The ".CATfct" suffix is automatically added by CreateCatalog.
//    //--------------------------------------------------------------------------------
//    cout << "-2- Creating the catalog." << endl << flush;
//
//    CATUnicodeString OmmCatalogStorageName = StorageName;
//    CATICatalog      *piOLE4MecModCatalog  = NULL;
//    rc = ::CreateCatalog( &OmmCatalogStorageName , &piOLE4MecModCatalog );
//    if ( SUCCEEDED(rc) ) 
//        cout << "    OLE4MecMod Catalog created OK." << endl << flush;
//    else { 
//        cout << "    ERROR in creating OLE4MecMod Catalog : check path and potential already existing catalog." << endl << flush; 
//        return 1; 
//        }
//
//    //--------------------------------------------------------------------------------
//    // -3- Adding a client identification to the catalog.
//    //     This is a mandatory step.
//    //--------------------------------------------------------------------------------
//    cout << "-3- Adding a client identification to the catalog." << endl << flush;
//
//    CATUnicodeString ClientId = "CAA_OLE4MecMod";
//    rc = piOLE4MecModCatalog->SetClientId( &ClientId );
//    if ( SUCCEEDED(rc) ) 
//        cout << "    Client Id set OK." << endl << flush;
//    else { 
//        cout << "    ERROR in setting Client Id." << endl << flush; 
//        return 1; 
//        }
//    
//    //--------------------------------------------------------------------------------
//    // -4- Calling Shape Design start-up factory to create our new startup's father startup.
//    //     It creates a start-up inherited from Shape Design startup "GSMGeom".
//    //--------------------------------------------------------------------------------
//    cout << "-4- Calling Shape Design GSMGeom start-up Factory to create our new startup." << endl << flush;
//    
//    CATUnicodeString VerticalLineStartUpType = "CAAOmmVerticalLine";
//    CATISpecObject   *piSpecOnVerticalLineStartUp   = NULL;
//  
//    CATUnicodeString CatalogName = "CATHybridShape" ;
//    CATUnicodeString SuperTypeName = "GSMGeom";
//    CATBoolean       publicSU = FALSE ;
//    CATBoolean       derivableSU = FALSE ;
//
//
//    rc = ::CATOsmSUFactory(&piSpecOnVerticalLineStartUp,
//                           &VerticalLineStartUpType,
//                           piOLE4MecModCatalog,
//                           &SuperTypeName,
//                           &CatalogName,
//                           publicSU,
//                           derivableSU) ; 
//    
//    if ( SUCCEEDED(rc) ) {
//        cout << "    Vertical Line StartUp created using CATOsmSUFactory OK." << endl << flush;
//        }
//    else {
//        cout << "    ERROR in creating Vertical Line StartUp using CATOsmSUFactory." << endl << flush; 
//        return 1;
//        }
//       
//    //--------------------------------------------------------------------------------
//    //  -5- Adding attributes to this startup.
//    //      Here is a short description of the vertical line feature's startup.
//    //      StartUp              Attribute Name    Attribute type    Update
//    //      ------------         --------------    --------------    ------------
//    //      CAAOmmVerticalLine   Point1            tk_specobject     IN attribute
//    //                           Point2            tk_specobject     IN attribute
//    //
//    //      If you wish to get more details about startup and attributes, please
//    //      refer to CAAObjectSpecsModeler.edu use cases.
//    //-------------------------------------------------------------------------------- 
//    cout << "-5- Adding attributes to this startup." << endl << flush;
//
//    // Adding first attribute : Point1    
//    CATUnicodeString Point1Name = "Point1";
//    CATISpecAttribute *piPoint1SpecAttribute = 
//            piSpecOnVerticalLineStartUp->AddAttribute( Point1Name,
//                                                       tk_specobject,
//                                                       sp_IN);
//    
//    if ( NULL != piPoint1SpecAttribute ) 
//        cout << "    Point1 attribute added OK." << endl << flush;
//    else {
//        cout << "    ERROR in adding Point1 attribute." << endl << flush;
//        return 1 ;
//      }
//    piPoint1SpecAttribute->Release();
//    piPoint1SpecAttribute = NULL ;
//    
//    // Adding second attribute : Point2
//    CATUnicodeString Point2Name = "Point2";
//    CATISpecAttribute *piPoint2SpecAttribute =  NULL ;
//    piPoint2SpecAttribute=  piSpecOnVerticalLineStartUp->AddAttribute( Point2Name,
//                                                       tk_specobject,
//                                                       sp_IN);
//    
//    if ( NULL != piPoint2SpecAttribute ) {
//        cout << "    Point2 attribute added OK." << endl << flush;
//        }
//    else {
//        cout << "    ERROR in adding Point2 attribute." << endl << flush;
//        return 1 ;
//      }
//    piPoint2SpecAttribute->Release();
//    piPoint2SpecAttribute = NULL ;
//    
//    // Releasing no longer used pointer on CATISpecObject.
//    piSpecOnVerticalLineStartUp->Release();
//    piSpecOnVerticalLineStartUp = NULL ;
//        
//    //--------------------------------------------------------------------------------
//    // -6- Saving the catalog.
//    //--------------------------------------------------------------------------------
//    cout << "-6- Saving the catalog." << endl << flush;
//
//    rc = ::SaveCatalog(&piOLE4MecModCatalog,&OmmCatalogStorageName );
//
//    if ( FAILED(rc)) 
//    {
//        cout << "    ERROR in saving catalog : check path or already existing catalog." << endl << flush;
//        return 1;
//    }
//
//    piOLE4MecModCatalog->Release();
//    piOLE4MecModCatalog = NULL ;
//
//    // Deleting session
//    rc = ::Delete_Session( pSessionName );
//
//    if (FAILED(rc)) {
//        cout << "    ERROR in deleting session." << endl << flush;
//        return 1;
//        }
//    
//    return 0;
//}


