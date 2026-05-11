// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspServices - This sample illustrates how to use the utilies
//  functions in 
// CATPspServices and CATPspListServices
//
#include <iostream.h>

// This framework
#include "CAAPspServices.h"

// CATPlantShipInterfaces
#include "CATIPspPhysicalProduct.h"
#include "CATIPspPhysical.h"

// CATPlantShipModeler
#include "CATPspServices.h"
#include "CATPspListServices.h"

//ObjectModelerBase
#include "CATDocument.h"

// System
#include "CATICStringList.h"
#include "CATIStringList.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATListOfCATUnicodeString.h"


//=============================================================================
//  Constructor
//=============================================================================
CAAPspServices::CAAPspServices() 
{
  cout << "CAAPspServices::CAAPspServices()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspServices::~CAAPspServices()
{
  cout << "CAAPspServices::~CAAPspServices()" << endl;
}

//=============================================================================
//  List and query part connectors
//=============================================================================
int CAAPspServices::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspServices::DoSample               ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspPhysical        *piPhysical = NULL;
  CATICStringList        *pLApplNames= NULL;
  CATICStringList        *pLDomainNames= NULL;

  IUnknown               *piUnknown = NULL;
  CATIUnknownList        *piUnkList = NULL;
  CATICStringList        *pLCStrNames = NULL;
  CATIStringList         *pListStrings=NULL;

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);
    //  Initialize Piping Design application
    ApplicationInit();
    //  Get a physical object from the input document
    piPhysical = GetAPhysicalObject();
    //
    // Use of CATPspListServices functions
    //   CreateCATIUnknownList and Locate
    //
    if ( NULL != piPhysical )
    {
       rc = CATPspListServices::CreateCATIUnknownList(&piUnkList); // Create a list of unknowns

       if( SUCCEEDED (rc) )
       {
          cout << "CAAPspServices: "
               << "Succeeded in creating a CATIUnknownList interface implementation object" << endl;
       }
    
       if ( NULL != piPhysical )
          rc = piPhysical->QueryInterface (IID_IUnknown, (void **)&piUnknown);

       if (SUCCEEDED(rc) && (NULL != piUnknown) && (NULL != piUnkList))
       {
          rc = piUnkList->Add(0,piUnknown);

          if( SUCCEEDED( rc) )
          {
            int iLocation = 0;
            iLocation = CATPspListServices::Locate(piUnkList, piUnknown);  
                
            if( iLocation >= 0)
            {
               cout << "Found Physical object in the list at index" << iLocation<< endl;
            }
            else
            {
               cout << "Could not find the physical object"  << endl;
            }                                           
          }     
        }
        if( NULL !=  piUnknown )
        {
           piUnknown->Release(); 
           piUnknown = NULL;
        }
        if( NULL != piUnkList )
        {
           piUnkList->Release(); 
           piUnkList = NULL;
        }
            
        piPhysical->Release();
        piPhysical = NULL;
    }

    //      
    //  CreateCATICStringList
    //
    if ( SUCCEEDED(CATPspListServices::CreateCATICStringList(&pLCStrNames)) && pLCStrNames )
    {
       const char* cStrPiping = "Piping";
       const char* cStrTubing = "Tubing";
            
       // Adding strings to the list
            
       pLCStrNames->Add(0,cStrPiping);
       pLCStrNames->Add(0,cStrTubing);

       //
       // Calling CATPspListServices::Locate() function to locate "Piping"
       // 
       int iLocation = 0;
       iLocation = CATPspListServices::Locate( pLCStrNames, cStrPiping);
       cout << "Location index =" <<  iLocation << endl;
       if( iLocation >= 0)
       {
          cout << "Found the string" << endl;
       }
       else
       {
          cout << "Could not find the string"  << endl;
       }            

            
       pLCStrNames->Release();
       pLCStrNames = NULL;
    }
    

    //
    // Use of CATPspListServices::CreateCATIStringList, 
    //      
    if ( SUCCEEDED(CATPspListServices::CreateCATIStringList(&pListStrings)) && pListStrings )
    {
       const wchar_t *wStrPiping = L"Piping";
       const wchar_t *wStrTubing = L"Tubing";
       // Adding wide character string to the list
       pListStrings->Add(0,wStrPiping);
       pListStrings->Add(0,wStrTubing);

       //
       // Calling CATPspListServices::Locate() function to locate "Piping"
       // 
       int iLocation = 0;
       iLocation = CATPspListServices::Locate( pListStrings, wStrPiping);
       cout << "Location index =" <<  iLocation << endl;
       if( iLocation >= 0)
       {
          cout << "Found the wide character string"  << endl;
       }
       else
       {
          cout << "Could not find the wide character string"  << endl;
       }                    
       pListStrings->Release();
       pListStrings = NULL;
    }
    

    //-------------------------------------------------------------------------
    // Use of CATPspServices::ListAllApplicationNames
    //-------------------------------------------------------------------------
    if( SUCCEEDED( CATPspServices::ListAllApplicationNames( &pLApplNames) )  )
    {
       unsigned int LCStrSize = 0;
       int NumOfCStr = 0;
       if (pLApplNames) HRESULT rc = pLApplNames->Count (&LCStrSize);
       NumOfCStr = LCStrSize;
       if (NumOfCStr)
       {
          cout << "Number of Applications = " << NumOfCStr <<endl;
          for (int iCStr=1; iCStr <= NumOfCStr; iCStr++)
          {
            char *piCStrAppl = NULL;
            HRESULT rc = pLApplNames->Item (iCStr-1,&piCStrAppl);
            if ( SUCCEEDED(rc) && piCStrAppl )
            {
               cout <<  iCStr << ") " << piCStrAppl <<endl;                                 
               delete [] piCStrAppl; piCStrAppl=NULL;
            }
          }
       }
       if( NULL != pLApplNames )
       {
         pLApplNames->Release();
         pLApplNames = NULL;
       }
    }       
    
        
    //-------------------------------------------------------------------------
    // Use if CATPspServices:: ListAllDomainNames
    //-------------------------------------------------------------------------
    if( SUCCEEDED( CATPspServices::ListAllDomainNames( &pLDomainNames) ))
    {
       unsigned int LCStrSize = 0;
       int NumOfCStr = 0;
       if (pLDomainNames) 
          HRESULT rc = pLDomainNames->Count (&LCStrSize);
       NumOfCStr = LCStrSize;
       if (NumOfCStr)
       {
          cout << "Number of Domains =" << NumOfCStr <<endl;
          for (int iCStr=1; iCStr <= NumOfCStr; iCStr++)
          {
             char *piCStrAppl = NULL;
             HRESULT rc = pLDomainNames->Item (iCStr-1,&piCStrAppl);
             if ( SUCCEEDED(rc) && piCStrAppl )
             {
                cout <<  iCStr << ") " << piCStrAppl <<endl;                                    
                delete [] piCStrAppl; piCStrAppl=NULL;
             }
          }
       }
       if( NULL != pLDomainNames )
       {
          pLDomainNames->Release();
          pLDomainNames = NULL;
       }
    }    
    
  } // end CATTry
  CATCatch (CATError, error)
  {         
     if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
     if ( NULL != pLDomainNames ) { pLDomainNames->Release(); pLDomainNames = NULL; }
     if ( NULL != pLApplNames ) { pLApplNames->Release(); pLApplNames = NULL; }      
     if ( NULL != pLCStrNames ) { pLCStrNames->Release(); pLCStrNames = NULL; }
     if ( NULL != pListStrings ) { pListStrings->Release(); pListStrings = NULL; }
     if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
     if ( NULL != piUnkList ) { piUnkList->Release(); piUnkList = NULL; }

     cout << "CAAPspServices::DoSample *** CATRethrow" << endl;
     CATRethrow;
  } 
  CATEndTry;
  return 0;
}
