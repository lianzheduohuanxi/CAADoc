// COPYRIGHT DASSAULT SYSTEMES 2000

// Local FrameWork
#include "CAAEMmrCatalogInstantiationForCombCrv.h"

// MecModInterfaces Framework
#include "CATIPartRequest.h"

// ComponentsCatalogsInterfaces Framework
#include "CATICatalogDescription.h"
#include "CATICatalogLink.h"
#include "CATICatalogBrowser.h"

// ApplicationFrame Framework
#include "CATFrmEditor.h"

// Visualization Framework
#include "CATPathElement.h"

// System Framework
#include "CATCreateExternalObject.h"
#include "CATCommand.h"
#include "CATUnicodeString.h"
#include "CATString.h"


#include "iostream.h"

CATImplementClass ( CAAEMmrCatalogInstantiationForCombCrv ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CombinedCurve         );

//-----------------------------------------------------------------------------
// CAAEMmrCatalogInstantiationForCombCrv : constructor
//-----------------------------------------------------------------------------
CAAEMmrCatalogInstantiationForCombCrv::CAAEMmrCatalogInstantiationForCombCrv()
{
}

//-----------------------------------------------------------------------------
// CAAEMmrCatalogInstantiationForCombCrv : destructor
//-----------------------------------------------------------------------------
CAAEMmrCatalogInstantiationForCombCrv::~CAAEMmrCatalogInstantiationForCombCrv()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICatalogInstantiation.h" // needed to tie the implementation to its interface
TIE_CATICatalogInstantiation( CAAEMmrCatalogInstantiationForCombCrv);

// 
// To declare that CombinedCurve implements CATICatalogInstantiation , insert 
// the following line in the interface dictionary :
//
// CombinedCurve      CATICatalogInstantiation    libCAAMmrCatalogCombCrv



HRESULT CAAEMmrCatalogInstantiationForCombCrv::RunInstantiationCmd (
                                       const CATICatalogLink    * pCatalogLink,
                                       const CATICatalogBrowser * pBrowser,
                                       int InstantiateMode,
                                       int RepeatMode,
                                       int & NotDone)
{
   cout <<" CAAEMmrCatalogInstantiationForCombCrv::RunInstantiationCmd" << endl;

   // The job is done by this method
   NotDone = 0;

   HRESULT rc = E_FAIL;
   if ( NULL == pCatalogLink ) return rc ; 
  
   // Retrieving the description 
   CATICatalogDescription * pDesc = NULL;
   rc = pCatalogLink->GetPointedDescription (&pDesc) ;
   if ( SUCCEEDED(rc) && ( NULL!= pDesc) )
   {
      // Testing if the UI active object is a MechanicalPart
       CATFrmEditor * pCurrentEditor = CATFrmEditor::GetCurrentEditor();
       if ( NULL != pCurrentEditor )
       {
         CATPathElement path = pCurrentEditor->GetUIActiveObject();
         int nbSizePath = path.GetSize();
         
         rc = E_FAIL ;
         if ( nbSizePath > 0 )
         {
             CATBaseUnknown * pLeaf = NULL ;
             pLeaf = path[nbSizePath-1] ;
             if ( NULL != pLeaf )
             {
                CATIPartRequest * pInt = NULL ;
                rc = pLeaf->QueryInterface(IID_CATIPartRequest,(void**)& pInt);
                if ( SUCCEEDED(rc) )
                {
                   pInt->Release();
                   pInt = NULL ;
                }
             }
         }
         
         if ( SUCCEEDED(rc)  )
         {
             CATICatalogDescription::CATCatalogDescriptionType ComponentType ;
             ComponentType = CATICatalogDescription::CATCatalogUnset ;
             rc = pDesc->GetDescriptionType (ComponentType);

	         if ( SUCCEEDED (rc) && 
                  (ComponentType == CATICatalogDescription::CATCatalogFeature) )
             {
                // The command to create the combined curve
                CATCommand * newCommand = NULL;
                CATUnicodeString CommandName="CAAMmrCombCrvPanelStCmd";
                CATUnicodeString CommandLib="CAAMmrCombinedCurveUI";

                // The command, a CATStateCommand, will be automatically deleted 
                newCommand = (CATCommand *)::CATCreateExternalObject(
                             CommandName.ConvertToChar(),
                             NULL,    
                             CommandLib.ConvertToChar(),
                             NULL); // without argument

                if ( NULL == newCommand )
                {
                   rc = E_FAIL ;
                }
             } 
             pDesc->Release(); 
             pDesc = NULL;
         }
      }
   }

   return rc;
}

