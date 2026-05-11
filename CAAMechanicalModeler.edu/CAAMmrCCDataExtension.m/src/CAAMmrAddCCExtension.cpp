// COPYRIGHT DASSAULT SYSTEMES 2007


// Local Framework
#include "CAAMmrAddCCExtension.h"

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrCCDataExtension.h" // needed by the factory to return a pointer on this interface

// Include of Extension 
#include "CATIOsmExtendable.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"      // needed to manage features

// MecModInterfaces Framework
#include "CATIBRepAccess.h"  //For BRepAccess Management
#include "CATIMechanicalFeature.h"
// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"

// Visualization 
#include "CATIModelEvents.h"
#include "CATCreate.h"   

// Include System
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"

#include "iostream.h"

//------------------------------------------------------------------------------------------------

HRESULT CAAMmrAddCCExtension( const CATBaseUnknown *iBaseFeature,CAAIMmrCCDataExtension **ioMmrCCDataExtension)

{
   cout <<" CAAMmrAddCCExtension" << endl;

   // Exit if the input base feature is null or if outpout pointer is not allocated
   if ( (NULL == iBaseFeature) || (NULL==ioMmrCCDataExtension)  )
   {
      return E_FAIL ;
   }

   HRESULT rc = S_OK ;

   CATISpecObject*    pBaseFeature   = NULL;   
   CATBaseUnknown * pBaseFeatureModifiable = (CATBaseUnknown * ) iBaseFeature ;

   (*ioMmrCCDataExtension) = NULL ;

   CATISpecObject_var hSOBaseFeature = pBaseFeatureModifiable ;

   if( NULL_var == hSOBaseFeature )
   {
      // iBaseFeature is a BRepAccess, We must retrieve the SpecObject associated with the Selection
      CATIBRepAccess *pBRepAccess = NULL;
      rc =  pBaseFeatureModifiable-> QueryInterface( IID_CATIBRepAccess, ( void**) &pBRepAccess );

      if (SUCCEEDED(rc) && pBRepAccess != NULL)
      {
         hSOBaseFeature = pBRepAccess -> GetSelectingMasterFeature();

         pBRepAccess ->Release();
         pBRepAccess = NULL;
      }
   }

   // Create the extension on the base feature
   CATIOsmExtendable* pExtendableOnBaseFeature = NULL;

   // Define the name of the extension
   const char          *  ExtensionName = NULL; 
   ExtensionName = "`CAAMmrCCDataExtension`@`CAAMmrCCDataExtensionCatalog.CATfct`";

   if ( NULL_var != hSOBaseFeature)
   {
      rc = hSOBaseFeature -> QueryInterface( IID_CATIOsmExtendable, ( void**) &pExtendableOnBaseFeature );

      // Add the extension to the base feature
      if (SUCCEEDED(rc) && (pExtendableOnBaseFeature != NULL) )
         rc = pExtendableOnBaseFeature -> AddExtension (ExtensionName);
   }
   else
      rc = E_FAIL ;

   // Initialize the new extended feature 
   if(SUCCEEDED(rc ) && (NULL!=pExtendableOnBaseFeature) )
   {
      rc = pExtendableOnBaseFeature -> QueryExtension( ExtensionName,
         IID_CAAIMmrCCDataExtension,
         (void**) ioMmrCCDataExtension);

      if(SUCCEEDED(rc) && ( NULL!= (*ioMmrCCDataExtension) ) )
      {
         //Actually, we only Set SpecObjectFeature!
         //In deed, BRep are not, for the moment, compliant with Extension !
         rc = (*ioMmrCCDataExtension) -> SetGeomFeature (hSOBaseFeature);

         // update the part  
         hSOBaseFeature -> SetUpToDate(FALSE) ;   
      }
   }
   if ( NULL != pExtendableOnBaseFeature)
   {
      pExtendableOnBaseFeature -> Release();
      pExtendableOnBaseFeature = NULL;
   }

   // update the new extended feature
   CATISpecObject_var spSpecsExtendedFeature = (*ioMmrCCDataExtension) ;
   if ( NULL_var != spSpecsExtendedFeature )
   {
      spSpecsExtendedFeature->Update();
   }

   // Connect To
   if ( SUCCEEDED(rc) && (NULL!=(*ioMmrCCDataExtension) ) )
   {
      CATIModelEvents_var spModelEvtBaseFeature = pBaseFeatureModifiable ;
      if ( NULL_var != spModelEvtBaseFeature )
      {
         spModelEvtBaseFeature -> ConnectTo((*ioMmrCCDataExtension)) ;
      }
   }

   // Retrieve the Part feature
   CATIMechanicalFeature_var spMechFeatOnBase = pBaseFeatureModifiable ;
   CATISpecObject_var PartFeat ;
   if ( NULL_var != spMechFeatOnBase )
   {
      PartFeat = spMechFeatOnBase -> GetPart ();
   }

   // CATCreate Event to re-visualize it -> child of Part
   CATIModelEvents_var spModelEvtExtendedFeature = (*ioMmrCCDataExtension) ;
   if ( (NULL_var != spModelEvtExtendedFeature ) && ( NULL_var != PartFeat ) )
   {
      // The second argument of the method must be the Part since it is the Part 
      // which contains the visu of the extended feature.
      // 
      CATCreate notif((*ioMmrCCDataExtension),PartFeat);
      spModelEvtExtendedFeature -> Dispatch (notif);
   }
   // modify the Spec tree
   CATIRedrawEvent_var spDrwEvtExtendedFeature = (*ioMmrCCDataExtension) ;
   if ( NULL_var != spDrwEvtExtendedFeature )
   {
      spDrwEvtExtendedFeature -> Redraw ();
   }

   return rc; 

}

