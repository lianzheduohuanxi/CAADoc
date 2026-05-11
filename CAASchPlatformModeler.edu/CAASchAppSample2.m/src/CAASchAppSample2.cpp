// COPYRIGHT DASSAULT SYSTEMES  2000+
//=============================================================================
//
// CAASchAppSample2 - Creates a component with multiple GRRs and swaps GRRs
//
#include <iostream.h>

// This framework
#include "CAASchApp.h"
#include "CAASchAppSample2.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppBaseServices.h"

// CATSchPlatformInterfaces
#include "CATISchComponent.h"
#include "CATISchCompGraphic.h"
#include "CATISchGRRComp.h"
#include "CATISchGRR.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATIContainer.h"

// System
#include "CAASchAppErrors.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"


// Drafting
#include "CATISheet.h"
#include "CATIView.h"

//=============================================================================
//  Constructor
//=============================================================================
CAASchAppSample2::CAASchAppSample2() :  _pSchDoc (NULL)
{

  cout << "CAASchAppSample2::CAASchAppSample2()" << endl;
};

//=============================================================================
//  Destructor
//=============================================================================
CAASchAppSample2::~CAASchAppSample2()
{
  _pSchDoc = NULL;

  cout << "CAASchAppSample2::~CAASchAppSample2()" << endl;
}

//=============================================================================
//  CreateComponent
//=============================================================================
int CAASchAppSample2::DoSample(const char *iFileToBeLoaded, const char *iPathToOutputFile)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAASchAppSample2::DoSample                     ==="<< endl;
  cout <<"============================================================"<< endl;

  InitEnvironment(iFileToBeLoaded);

  HRESULT RC = S_OK;

  CATISchCompGraphic *piCompGraphic = NULL;
  CATISchComponent   *piComponent   = NULL;
  CATISchComponent   *piSchComp     = NULL;
  
  CATIUnknownList *pLIGRRs    = NULL;
  CATIView        *piViewGRR1 = NULL;   
  CATISheet_var   spDtlSheet  = NULL_var;
  
  CATISchGRRComp  *piGRRComp    = NULL;
  CATISchGRRComp  *piGRRComp1   = NULL;
  CATISchGRRComp  *piGRRComp2   = NULL;
  CATISchGRRComp  *piGRRComp3   = NULL;
  CATISchGRRComp  *piNewGRRComp = NULL;

  CATISchGRR      *piSchGRR = NULL;

  CATTry 
	{
    //-------------------------------------------------------------------------
    //  At this point, we should have a pointer to our reference object.
    //  If not, this might not be the correct drawing.
    //-------------------------------------------------------------------------    
    if (NULL_var == _spAppRef)
    {
       cout << "Cannot find Application reference object " << endl;
       return 0;
    }

    //-------------------------------------------------------------------------
    //  Using the reference object, find CATISchCompGraphic interface.
    //-------------------------------------------------------------------------    
    HRESULT rc = _spAppRef->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGraphic);
    if (FAILED(rc))
    {
       cout << "cannot get CATISchCompGraphic interface " << endl;
       return 0;
    }
  
    //-------------------------------------------------------------------------
    //  Use the CATISchCompGraphic's method, ListGraphicalRepresentations, to
    //  find the current graphical representations for the object. 
    //
    //  Since this object was created in sample1, we know it will only have
    //  one GRR.  Use this to find the detail sheet and view of the GRR.
    //-------------------------------------------------------------------------
    int NbGRR = 0;
    if (SUCCEEDED (piCompGraphic->ListGraphicalRepresentations (&pLIGRRs)))
    {
       unsigned int uSize = 0;
       if (SUCCEEDED (pLIGRRs->Count(&uSize)))
       {
          cout << "Size of GRR List = " << uSize << endl;
          NbGRR = uSize;
          if (uSize != 0)
          {
             IUnknown *piUK = NULL;
             if (SUCCEEDED (pLIGRRs->Item(0,&piUK)))
             {
                if ( SUCCEEDED (piUK->QueryInterface (IID_CATIView,(void **) &piViewGRR1)))
                {
                   spDtlSheet = piViewGRR1->GetSheet();
                   if (NULL_var != spDtlSheet)
                   {
                      cout << "Got detail sheet containing the GRR detail "
                           << endl;
                   }
                }
                rc = piUK->QueryInterface (IID_CATISchGRRComp,(void **) &piGRRComp1);
                piUK->Release(); piUK = NULL;
             }
          } 
       }
    } 

    //-------------------------------------------------------------------------
    //  Now that we know the detail sheet and the view from which the GRR
    //  is from, loop through the other views on the detail sheet
    //  to make additional GRRs for the reference object.
    // 
    //  We know the detail sheet will have two other views from which two
    //  additional GRRs will be added.
    //-------------------------------------------------------------------------
    if (NULL_var != spDtlSheet )
    {
       CATLISTV(CATISpecObject_var) LView = spDtlSheet->GetViewList();
       int SizeOfLView = LView.Size();
       cout << "Size of view list = " << SizeOfLView << endl;

       if (SizeOfLView >= 3) // See documention for CATISheet Interfaces for why (>=3)
       {
         CATISpecObject *piSpecView = NULL;
         CATISpecObject_var spSpecView = NULL_var;
         CATISpecObject_var spSpecTemp;
         if ( NULL != piViewGRR1 )
         {
          if (SUCCEEDED (piViewGRR1->QueryInterface (IID_CATISpecObject,(void **) &piSpecView )) )
          {
           spSpecView = piSpecView;
           piSpecView->Release(); piSpecView = NULL;
           for (int iView = 3; iView <= SizeOfLView; iView++) 
           {
             spSpecTemp = LView[iView];
             if (!!spSpecTemp && spSpecTemp != spSpecView)
             {
               if (!!spSpecTemp)
               {
                  if (SUCCEEDED ( spSpecTemp->QueryInterface (IID_CATISchGRRComp,(void **) &piGRRComp)))
                  {
                   if ( NULL != piGRRComp )
                   {
                    if (SUCCEEDED (piCompGraphic->AddGraphicalRepresentation (piGRRComp)))
                    {
                      cout << "successfully added GRR at position " << iView << endl;
   
                      NbGRR ++;
                      if ( NbGRR == 2 ) piGRRComp2 = piGRRComp;
                      if ( NbGRR == 3 ) piGRRComp3 = piGRRComp;
   
   
                      if ( NULL != piGRRComp && SUCCEEDED (piGRRComp->QueryInterface(IID_CATISchGRR,(void**)&piSchGRR) ) )
                      {
                        switch ( NbGRR )
                        {
                        case 2:
                                 if ( NULL != piSchGRR ) piSchGRR->SetGRRName(CAASCHAPP_GRR_REP2);
                                 break;
                        case 3:
                                 if ( NULL != piSchGRR ) piSchGRR->SetGRRName(CAASCHAPP_GRR_REP3);
                                 break;
                        default:
                          break;
                        }
                        piSchGRR->Release(); piSchGRR = NULL;
                      }
                    } // if (SUCCEEDED (piCompGraphic->AddGraphicalRepresentation
                   } // if ( NULL != piGRRComp )
                  } // if (SUCCEEDED ( spSpecTemp->QueryInterface 
               } // if (!!spSpecTemp)
             } // if (!!spSpecTemp && spSpecTemp != spSpecView)
           } // for (int iView = 3; iView <= SizeOfLView; iView++) 
           if ( NbGRR >= 2 ) piGRRComp = NULL;
           cout << "Total GRR after adding is " << NbGRR << endl;
          } // QI for piSpecView
         } // if piViewGRR1
       } // SizeOfLView >= 3
    }
    if ( NULL != piCompGraphic ) { piCompGraphic->Release(); piCompGraphic = NULL; }

    //-------------------------------------------------------------------------
    //  Make sure the main sheet is active before instanciating the reference
    //-------------------------------------------------------------------------
    SetMainSheet();

    //-------------------------------------------------------------------------
    //  As in sample1, we create a component instance from the reference.
    //  Then a second occurance of the component is activated with a different
    //  GRR.  Finaly all occurances of the component's images are replaced
    //  with 2nd GRR.
    //-------------------------------------------------------------------------

    if ( SUCCEEDED(_spAppRef->QueryInterface (IID_CATISchComponent,(void **) &piComponent)) )
    {
      double aDb6Axis[6] = {1.0,0.0, 0.0,1.0, 50.0,170.0};

      rc = piComponent->PlaceInSpace (NULL, aDb6Axis, &piSchComp);
      if (SUCCEEDED (rc))
      {

        CATISpecObject *piSchCompInst = NULL;
        if (SUCCEEDED (piSchComp->QueryInterface (IID_CATISpecObject,(void **) &piSchCompInst)))
        {
          piSchCompInst->Release(); piSchCompInst = NULL;
        }

        double Db2Loc[2] = {220.0,170.0};
        char *pGRRName = NULL;
        if ( NULL != piGRRComp2 && SUCCEEDED (piGRRComp2->QueryInterface(IID_CATISchGRR,(void**)&piSchGRR) ) )
        {
          if ( SUCCEEDED (piSchGRR->GetGRRName(&pGRRName)) )
          {
            rc = piSchComp->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGraphic);
            if ( SUCCEEDED(rc) && piCompGraphic) 
            {
              rc = piCompGraphic->Activate(pGRRName,Db2Loc,&piNewGRRComp);
            }
            if ( SUCCEEDED(rc) && piCompGraphic)
            {
              cout << "Successfully activated " << pGRRName << endl;

              if ( SUCCEEDED(piCompGraphic->SwitchAll(pGRRName)) )
              {
                 cout << "Successfully switched all images" << endl;
              }
              else cout << "Failed to switch all images" << endl;
            }
            else
            {
              cout << "Failed to Activate " << pGRRName << endl;
            }
          }
          piSchGRR->Release(); piSchGRR = NULL;
        }
        if ( NULL != pGRRName )
        {
           delete [] pGRRName; pGRRName = NULL;
        }
      }
      else
      {
         cout << "Fail in PlaceInSpace for creating first instance " 
              << "from the reference"
              << endl;
      }
    }
  } // end CATTry


  if (NULL != iPathToOutputFile) 
  {
    cout << "Document saved as : " << iPathToOutputFile << endl;
    SaveDocument (iPathToOutputFile);
  }

  if ( NULL != piCompGraphic ) { piCompGraphic->Release(); piCompGraphic = NULL; }
  if ( NULL != piComponent ) { piComponent->Release(); piComponent = NULL; }
  if ( NULL != piSchComp ) { piSchComp->Release(); piSchComp = NULL; }
  if ( NULL != pLIGRRs ) { pLIGRRs->Release(); pLIGRRs = NULL; }
  if ( NULL != piViewGRR1 ) { piViewGRR1->Release(); piViewGRR1 = NULL; }
  if ( NULL != piGRRComp ) { piGRRComp->Release(); piGRRComp = NULL; }
  if ( NULL != piGRRComp1 ) { piGRRComp1->Release(); piGRRComp1 = NULL; }
  if ( NULL != piGRRComp2 ) { piGRRComp2->Release(); piGRRComp2 = NULL; }
  if ( NULL != piGRRComp3 ) { piGRRComp3->Release(); piGRRComp3 = NULL; }
  if ( NULL != piNewGRRComp ) { piNewGRRComp->Release(); piNewGRRComp = NULL; }

  CATCatch (CATError, error)
	{
    if ( NULL != piCompGraphic ) { piCompGraphic->Release(); piCompGraphic = NULL; }
    if ( NULL != piComponent ) { piComponent->Release(); piComponent = NULL; }
    if ( NULL != piSchComp ) { piSchComp->Release(); piSchComp = NULL; }
    if ( NULL != pLIGRRs ) { pLIGRRs->Release(); pLIGRRs = NULL; }
    if ( NULL != piViewGRR1 ) { piViewGRR1->Release(); piViewGRR1 = NULL; }
    if ( NULL != piGRRComp ) { piGRRComp->Release(); piGRRComp = NULL; }
    if ( NULL != piGRRComp1 ) { piGRRComp1->Release(); piGRRComp1 = NULL; }
    if ( NULL != piGRRComp2 ) { piGRRComp2->Release(); piGRRComp2 = NULL; }
    if ( NULL != piGRRComp3 ) { piGRRComp3->Release(); piGRRComp3 = NULL; }
    if ( NULL != piNewGRRComp ) { piNewGRRComp->Release(); piNewGRRComp = NULL; }
    if ( NULL != piSchGRR ) { piSchGRR->Release(); piSchGRR = NULL; }

    cout << "CAASchAppSample2::DoSample *** CATRethrow" 
         << endl;
	  CATRethrow;
	}	
  CATEndTry;
	return 0 ;
}

//=============================================================================
//  Initialize the environment
//=============================================================================
void CAASchAppSample2::InitEnvironment (const char *iFileToBeLoaded)
{
  CATTry
  {
     CreateCATProductEnv (iFileToBeLoaded);

     _pSchDoc = GetDocument();
     GetAppReference ();
  }
  CATCatch (CATError, error)
	{
    cout << "CAASchAppSample2::InitEnvironment *** CATRethrow" 
         << endl;
	  CATRethrow;
	}	
  CATEndTry;
}

//=============================================================================
//  Get Application reference object
//=============================================================================
void CAASchAppSample2::GetAppReference ()
{
  HRESULT rc = S_OK;
  if (NULL == _pSchDoc)
  {
    cout << "CAASchAppSample2::Cannot find DOCUMENT " << endl;
    return;
  }
  CATTry 
	{

    CATIContainer_var spAppCont = GetAppObjContainer();
    if (NULL_var == spAppCont)
    {
       cout << "DoSample:"
            << "Cannot find application container"
            << endl;
       return;
    }

    _spAppRef = CAASchAppBaseServices::FindFeatureByName (
                SCHEDUPart_TestRef, spAppCont);

  } // end CATTry

  CATCatch (CATError, error)
	{
    cout << "CAASchAppSample2::GetAppReference *** CATRethrow" 
         << endl;
	  CATRethrow;
	}	
  CATEndTry;
}
