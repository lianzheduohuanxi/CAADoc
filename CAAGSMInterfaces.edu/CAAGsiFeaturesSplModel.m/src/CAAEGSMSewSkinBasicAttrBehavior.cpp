// COPYRIGHT Dassault Systemes 2005
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
//CAAEGSMSewSkinBasicAttrBehavior
// Provide implementation to interface
//    CATIAttrBehavior
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// MINC 
#include "CATCollec.h"

#include <CAAEGSMSewSkinBasicAttrBehavior.h>

// System Framework
#include "CATUnicodeString.h"       // To handle Unicode String 


// MechanicalModeler Framework
#include "CATIMfMonoDimResult.h"    // To put the CATIMfMonoDimResult IID int the CATBehaviorSpecs
#include "CATIMfBiDimResult.h"    // To put the CATIMfMonoDimResult IID int the CATBehaviorSpecs

//#include <iostream.h>

CATImplementClass(CAAEGSMSewSkinBasicAttrBehavior,CodeExtension,CATBaseUnknown,CAASewSkinBasic);

#include "TIE_CATIAttrBehavior.h"
TIE_CATIAttrBehavior(CAAEGSMSewSkinBasicAttrBehavior);

//========================================================================
// Constructor - Destructor
//========================================================================
CAAEGSMSewSkinBasicAttrBehavior::CAAEGSMSewSkinBasicAttrBehavior():CATBaseUnknown()
{
  //  cout << "CAAEGSMSewSkinBasicAttrBehavior::CAAEGSMSewSkinBasicAttrBehavior" << endl;
}

CAAEGSMSewSkinBasicAttrBehavior::~CAAEGSMSewSkinBasicAttrBehavior()
{
    //cout << "CAAEGSMSewSkinBasicAttrBehavior::~CAAEGSMSewSkinBasicAttrBehavior" << endl;
}

//------------------------------------------------------------------------
//   GetRequestedBehavior
//------------------------------------------------------------------------
HRESULT CAAEGSMSewSkinBasicAttrBehavior::GetRequestedBehavior(const CATUnicodeString* ipAttrId, CATBehaviorSpecs** oppBehavior)
{
//   cout << "CAAEGSMSewSkinBasicAttrBehavior::GetRequestedBehavior" << endl;

   HRESULT exit=E_FAIL;
   if ( (NULL != oppBehavior) && ( NULL != ipAttrId) )
   {
      *oppBehavior = new CATBehaviorSpecs;

      if ( NULL != *oppBehavior )
      {
         // If the input String is equal to "SurfaceToSew"  or "SurfaceSupport" which are the name 
         // of attributes then the Filter will be IID_CATIMfMonoDimResult
         // That is to say, we can Replace in  the attribute Feature  implementing the interface CATIMfBiDimResult by another one 
         if ( (2 == ipAttrId->Compare("SurfaceToSew")) ||(2 == ipAttrId->Compare("SurfaceSupport")) )
		 {
            CATListPV* aMyFirstList = new CATListPV;
            aMyFirstList->Append((void*)&IID_CATIMfBiDimResult);
            (*oppBehavior)->Append(aMyFirstList);
            exit = S_OK ;
         }
      }
   }

   return exit;
}
