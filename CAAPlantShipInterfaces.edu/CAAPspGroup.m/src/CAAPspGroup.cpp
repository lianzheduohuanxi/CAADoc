// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspGroup - This sample illustrates how to use the following
// interfaces to query, instanciate and delete groups or logical lines:
// CATIPspAppFactory, CATIPspGroup, CATIPspGroupable
//
#include <iostream.h>

// This framework
#include "CAAPspGroup.h"

// CATPlantShipInterfaces

#include "CATIPspLogicalLine.h"
#include "CATIPspGroup.h"
#include "CATIPspGroupable.h"
#include "CATIPspPhysical.h"
#include "CATIPspAppFactory.h"

//ObjectModelerBase
#include "CATDocument.h"
#include "CATObject.h"
#include "CATIDocRoots.h"

// System
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

// Product Structure
#include "CATIProduct.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspGroup::CAAPspGroup() 
{
  cout << "CAAPspGroup::CAAPspGroup()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspGroup::~CAAPspGroup()
{
  cout << "CAAPspGroup::~CAAPspGroup()" << endl;
}

//=============================================================================
//  List and query group and member groupables
//=============================================================================
int CAAPspGroup::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspGroup::DoSample                          ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspLogicalLine     *piLogicalLine = NULL; 
  CATIPspGroup           *piGroup = NULL;
  CATIPspGroupable       *piGroupable = NULL;
  CATIPspAppFactory      *piAppFactory = NULL;
  CATIUnknownList        *pListMembers = NULL;
  CATIUnknownList        *pListGroups = NULL;
  CATIUnknownList        *pListLogicalLines = NULL;
  IUnknown               *piUKMember = NULL;
  CATIProduct            *piCurrentProduct = NULL;
  CATListValCATBaseUnknown_var* Roots = NULL;
  
  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    //  Get a Logical line object from the input document   
    piLogicalLine =  GetALogicalLine ();

    if ( NULL != piLogicalLine )
    {
      //  Find CATIPspGroup interface
      rc = piLogicalLine->QueryInterface(IID_CATIPspGroup,(void**)&piGroup);
      piLogicalLine->Release();
      piLogicalLine = NULL;
    }
    
    //-------------------------------------------------------------------------
    //  CATIPspGroup methods
    //-------------------------------------------------------------------------
    if ( NULL != piGroup )
    {
      //----------------------------------------------------------------------
      //  List Members
      //---------------------------------------------------------------------- 
      if ( SUCCEEDED(piGroup->ListMembers ( NULL, &pListMembers )) &&
           ( NULL != pListMembers) )
      {  
        cout << "Succeeded in getting group's members" << endl;

        unsigned int LUnknownSize = 0;
        int NumOfUnknowns = 0;
        pListMembers->Count (&LUnknownSize);
        NumOfUnknowns = LUnknownSize;
         
        cout << "Number of members is " <<  NumOfUnknowns << endl;

        if (NumOfUnknowns > 0)
        {
          for (int iUK=1; iUK <= NumOfUnknowns; iUK++)
          {
            if (SUCCEEDED(pListMembers->Item (iUK-1,&piUKMember)) && piUKMember )
            {     
              //
              // Getting CATIPspGroupable interface pointer
              //
              rc = piUKMember->QueryInterface (IID_CATIPspGroupable, (void **)&piGroupable);            
              piUKMember->Release();
              piUKMember = NULL; 
              if ( NULL != piGroupable ) break;            
            }
          }
        }               
        pListMembers->Release();
        pListMembers = NULL;            
      }

      if ( NULL != piGroupable )
      {
        //--------------------------------------------------------------------
        //  Remove a member
        //-------------------------------------------------------------------- 
        if ( SUCCEEDED(piGroup->RemoveMember(piGroupable)) )
           cout << "Succeeded in removing a member from the group" << endl;  

        //--------------------------------------------------------------------
        //  Add a member
        //-------------------------------------------------------------------- 
        if ( SUCCEEDED(piGroup->AddMember(piGroupable)) )
           cout << "Succeeded in adding a member to the group" << endl;  
      }
    }

    //-------------------------------------------------------------------------
    //  CATIPspGroupable methods
    //-------------------------------------------------------------------------
    if ( (NULL != piGroupable) &&  (NULL != piGroup ) ) 
    {
      //----------------------------------------------------------------------
      //  List groups that the groupable belongs to
      //---------------------------------------------------------------------- 
      if ( SUCCEEDED( piGroupable->ListGroups( NULL, &pListGroups)) 
           && (NULL != pListGroups) )
      {
        cout << "Succeeded in getting list of groups" << endl;
    
        unsigned int LUnknownSize = 0;
        int NumOfUnknowns = 0;
        pListGroups->Count (&LUnknownSize);
        NumOfUnknowns = LUnknownSize;

        cout << "Number of groups is " <<  NumOfUnknowns << endl;
        pListGroups->Release();
        pListGroups = NULL;     
      }
    }
    
    if ( NULL != piGroup )
    {
       piGroup->Release();
       piGroup = NULL;
    }
    if ( NULL != piGroupable )
    {
       piGroupable->Release();
       piGroupable = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspAppFactory methods
    //-------------------------------------------------------------------------

    //  Get CATIPspAppFactory interface
    CATObject *piObj = new CATObject("CATPiping");
    if ( NULL != piObj )
    {
      rc = piObj->QueryInterface(IID_CATIPspAppFactory,(void **)&piAppFactory);
      piObj->Release();
      piObj = NULL;
    }

    //  Get the root product for the input document
    CATDocument *pDocument = GetDocument();
    if ( NULL != pDocument )
    {
      CATIDocRoots_var spDocRoot (pDocument);
      if ( NULL_var != spDocRoot )
      {
        Roots = spDocRoot->GiveDocRoots();
        if ( NULL != Roots )
        {
          CATIProduct_var spRootPrd = (*Roots)[1];
          delete Roots;  Roots = NULL;
          if ( NULL_var != spRootPrd )
          {
            rc = spRootPrd->QueryInterface(IID_CATIProduct,(void**)&piCurrentProduct);
          }
        }
      }
    }

    if ( (NULL != piAppFactory) &&  (NULL != piCurrentProduct ) ) 
    {
      //----------------------------------------------------------------------
      //  Instanciate a PipingLine from the PipingLine catalog
      //---------------------------------------------------------------------- 
      CATUnicodeString PipingLineID = "U1-P103-6in-CS150R-FG";
      if ( SUCCEEDED(piAppFactory->GetLogicalLine(piCurrentProduct,
            PipingLineID, &piLogicalLine)) && (NULL != piLogicalLine) )
      {
        cout << "Succeeded in instanciating a Piping Line" << endl;

        //--------------------------------------------------------------------
        //  List the Logical lines in the document
        //-------------------------------------------------------------------- 
        if ( SUCCEEDED(piAppFactory->ListLogicalLines(piCurrentProduct,&pListLogicalLines))
             && (NULL != pListLogicalLines) ) 
        {
          unsigned int LUnknownSize = 0;
          int NumOfUnknowns = 0;
          pListLogicalLines->Count (&LUnknownSize);
          NumOfUnknowns = LUnknownSize;
          cout << "Number of PipingLines in document = " << NumOfUnknowns << endl;
          pListLogicalLines->Release();
          pListLogicalLines = NULL;
        }

        //--------------------------------------------------------------------
        //  Delete the PipingLine with no members
        //-------------------------------------------------------------------- 
        if ( SUCCEEDED(piAppFactory->DeleteLogicalLine(piLogicalLine)) )
          cout << "Succeeded in deleting a PipingLine instance" << endl;

        piLogicalLine->Release();
        piLogicalLine = NULL;
      }

      //----------------------------------------------------------------------
      //  Create a Piping spool object
      //---------------------------------------------------------------------- 
      CATUnicodeString GroupType = "CATPipSpool";
      CATUnicodeString GroupID = "PipingSpool";
      if ( SUCCEEDED(piAppFactory->CreateGroup(piCurrentProduct,
            GroupType, GroupID, &piGroup)) && (NULL != piGroup) )
      {
        cout << "Succeeded in creating a Piping Spool" << endl;

        //--------------------------------------------------------------------
        //  List the Piping spools in the document
        //-------------------------------------------------------------------- 
        if ( SUCCEEDED(piAppFactory->ListGroups(piCurrentProduct,&pListGroups))
             && (NULL != pListGroups) ) 
        {
          unsigned int LUnknownSize = 0;
          int NumOfUnknowns = 0;
          pListGroups->Count (&LUnknownSize);
          NumOfUnknowns = LUnknownSize;
          cout << "Number of Piping spools in document = " << NumOfUnknowns << endl;
          pListGroups->Release();
          pListGroups = NULL;
        }

        //--------------------------------------------------------------------
        //  Delete a Piping spool
        //-------------------------------------------------------------------- 
        if ( SUCCEEDED(piAppFactory->DeleteGroup(piGroup)) )
          cout << "Succeeded in deleting a Piping spool object" << endl;

        piGroup->Release();
        piGroup = NULL;
      }
    }

    if ( NULL != piAppFactory )
    {
       piAppFactory->Release();
       piAppFactory = NULL;
    }
    if ( NULL != piCurrentProduct )
    {
       piCurrentProduct->Release();
       piCurrentProduct = NULL;
    }
  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piLogicalLine ) { piLogicalLine->Release(); piLogicalLine = NULL; }
    if ( NULL != piGroup ) { piGroup->Release(); piGroup = NULL; }
    if ( NULL != piGroupable ) { piGroupable->Release(); piGroupable = NULL; }
    if ( NULL != piAppFactory ) { piAppFactory->Release(); piAppFactory = NULL; }
    if ( NULL != pListMembers ) { pListMembers->Release(); pListMembers = NULL; }
    if ( NULL != pListGroups ) { pListGroups->Release(); pListGroups = NULL; }
    if ( NULL != pListLogicalLines ) { pListLogicalLines->Release(); pListLogicalLines = NULL; }
    if ( NULL != piUKMember ) { piUKMember->Release(); piUKMember = NULL; }  
    if ( NULL != piCurrentProduct ) { piCurrentProduct->Release(); piCurrentProduct = NULL; }  
    cout << "CAAPspGroup::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}

