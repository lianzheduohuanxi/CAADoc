/**
 * @quickreview nd1 12:04:07 Removed #includes of CATICatalog & CATCatalogFactoryServices
                             APIs deprecated with effect from CXR23.
 * @quickreview vso jsk 08:02:07
 */
// COPYRIGHT DASSAULT SYSTEMES  2001+ 
//=============================================================================
//

#include "CAASchAppFeatureSUServices.h"
#include "CAASchAppBaseServices.h"
#include "CAASchAppClassNames.h"

#include "CATISchAppRoute.h"
#include "CATISchAppConnectable.h"

// ApplicationFrame
#include "CATFrmEditor.h"
#include "CATDocument.h"

// Product Structure
#include "CATIProduct.h"

// ObjectModelerBase
#include "CATInit.h"
#include "CATSessionServices.h"
#include "CATIProperty.h"

#include "CATIUserId.h"

// ObjectSpecsModeler
#include "CATISpecAttrAccess.h"
#include "CATLISTV_CATISpecAttrKey.h"
#include "CATLISTV_CATISpecAttribute.h"

// System
#include "IUnknown.h"
#include "CATIEditor.h"
#include "CATLib.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATIDocRoots.h"
#include "CATGetEnvValue.h"

//=============================================================================
//  Find a document in session.
//=============================================================================
CATDocument * CAASchAppBaseServices::GetDocInSession (const char *iDocType)
{
   CATDocument *pDoc = NULL;

   CATFrmEditor *pFrmEditor = CATFrmEditor::GetCurrentEditor();
   if (NULL != pFrmEditor) 
   {
      pDoc = pFrmEditor->GetDocument();
   }

   //-------------------------------------------------------------------------
   // There are times when the CATFrmEditor is not yet activated (e.g.
   // during document creation time or that we are running an ODT,
   // therefore pDoc is NULL. In those
   // cases, we try to find the pDoc from the session
   //-------------------------------------------------------------------------
   if (NULL == pDoc)
   {
     CATString SDocType ("CATProduct");
     if (NULL != iDocType) SDocType = iDocType;
     const CATLISTP(CATDocument)* LDoc = ListDocuments();
     if (NULL != LDoc)
     {
        int SizeOfLDoc = LDoc->Size();
        CATDocument *pDocMem;
        for (int iDoc=1; iDoc <= SizeOfLDoc; iDoc++)
        {
           pDocMem = (*LDoc)[iDoc];         
           if ( NULL != pDocMem && pDocMem->IsAKindOf(SDocType.CastToCharPtr()))
           {
              pDoc = pDocMem;
              break;
           }
        }
     }
   }
   return pDoc;
}
//=============================================================================
//  Find an feature object in a container by a specific name
//=============================================================================
CATISpecObject_var CAASchAppBaseServices::FindFeatureByName (
   const char *iObjectName, const CATIContainer_var &iCont)
{
   CATISpecObject_var spObjFound = NULL_var;
   CATUnicodeString UObjectName (iObjectName);

   // @CSC-Filter VIOI vso(04-04-01)
   SEQUENCE (CATBaseUnknown_ptr) L0Obj = iCont->
      ListMembers(CATISpecObject::ClassName());
      
   int SizeOfL0Obj = L0Obj.length();
   CATISpecObject *piSpec = NULL;
   for (int iObj=0; iObj<SizeOfL0Obj; iObj++)
   {
	    piSpec = (CATISpecObject *) L0Obj[iObj];
	    if (NULL != piSpec) 
	    {
        if (piSpec->GetName()== UObjectName)
        {
          spObjFound = piSpec;
        }
        piSpec->Release(); piSpec = NULL;
	    }
   }
   return spObjFound;
}

//---------------------------------------------------------------------------
//  Find a route reference in a container by a specific class type
//---------------------------------------------------------------------------

CATISpecObject_var CAASchAppBaseServices::FindRouteRefByClass (
   const CATUnicodeString &iUClass, const CATIContainer_var &iCont)
{
   HRESULT RC = S_OK;
   CATISpecObject_var spObjFound = NULL_var;
   CATUnicodeString ClassType;
   int MatchPos;
   CATISchAppRoute *piSchRoute = NULL;

   // @CSC-Filter VIOI vso(04-04-01)
   SEQUENCE (CATBaseUnknown_ptr) L0Obj = iCont->
      ListMembers(CATISpecObject::ClassName());
      
   int SizeOfL0Obj = L0Obj.length();
   CATISpecObject *piSpec = NULL;
   int iObj;
   for (iObj=0; iObj<SizeOfL0Obj; iObj++)
   {
	    piSpec = (CATISpecObject *) L0Obj[iObj];
	    if (NULL != piSpec) 
	    {
        ClassType = piSpec->GetType();
        MatchPos = ClassType.SearchSubString(iUClass);
        if (MatchPos >= 0)
        {
           RC = piSpec->QueryInterface(IID_CATISchAppRoute,
                              (void **) &piSchRoute);
           if ( SUCCEEDED (RC) && piSchRoute )
           {
             spObjFound = piSpec;
             piSchRoute->Release(); piSchRoute = NULL;
             break;
           }
        }
	    }
   } // for 

   // clean up
   for (iObj=0; iObj<SizeOfL0Obj; iObj++)
   { 
     if (L0Obj[iObj])
     { 
       (L0Obj[iObj])->Release();
        L0Obj[iObj] = NULL;
     }
   } 

   return spObjFound;
}

//=============================================================================
//  Get the product root object
//=============================================================================
CATIProduct_var CAASchAppBaseServices::GetProductRootObject (
   CATDocument *iDoc)
{
   CATDocument *pDoc = NULL;
   CATIProduct_var spRootPrd = NULL_var;
   CATISpecObject_var spRootSpec = NULL_var;

   if (NULL != iDoc)
   {
      pDoc = iDoc;
   }
   else
   {
      pDoc = CAASchAppBaseServices::GetDocInSession();
   }

   // Should have done this if there is a CATProduct document
   if ( NULL != pDoc && pDoc->IsAKindOf ("CATProduct"))
   {
      spRootPrd = GetSchematicRoot(pDoc);  
   }
   return spRootPrd;
}

//=============================================================================
//  Create/Get product structure application sub-Container
//  create one if not exists, otherwise return existing one
//=============================================================================
CATIContainer_var CAASchAppBaseServices::GetAppObjContainer (
   CATDocument *iDoc)
{
   CATIContainer_var spSubCont = NULL_var;
   CATInit_var spInit = iDoc;
   if (NULL_var != spInit)
   {
     CATIContainer *piCont = (CATIContainer *)spInit->GetRootContainer (CATIContainer::ClassName());
     spSubCont = piCont;
     if (piCont) { piCont->Release(); piCont = NULL; }     
   }
   return spSubCont;
}

//=============================================================================
//  Get the schematic root object.
//=============================================================================
CATISpecObject_var CAASchAppBaseServices::GetSchematicRoot (CATDocument *iDoc)
{
   CATISpecObject_var spSchRoot = NULL_var;
   CATDocument *pDoc  = NULL;
   if (NULL == iDoc)
   {
      pDoc = CAASchAppBaseServices::GetDocInSession();
   }
   else
   {
      pDoc = iDoc;
   }
   CATIDocRoots_var spDocRoot = pDoc;
   CATLISTV(CATBaseUnknown_var) *pLBUK = NULL;
   if (NULL_var != spDocRoot) pLBUK = spDocRoot->GiveDocRoots();
   if (NULL != pLBUK) 
   {
      if (pLBUK->Size()) spSchRoot = (*pLBUK)[1];
      delete pLBUK; pLBUK = NULL;
   }
   return spSchRoot;
}

//---------------------------------------------------------------------------
//  Find an application object in a container by a specific class type
//---------------------------------------------------------------------------
CATISpecObject_var CAASchAppBaseServices::FindAppObjByClass (
   const CATUnicodeString &iUClass, const CATIContainer_var &iCont)
{
   HRESULT RC = S_OK;
   CATISpecObject_var spObjFound = NULL_var;
   CATUnicodeString ClassType;
   int MatchPos;
   CATISchAppConnectable *piSchAppCntbl = NULL;

   // @CSC-Filter VIOI vso(04-04-01)
   SEQUENCE (CATBaseUnknown_ptr) L0Obj = iCont->
      ListMembers(CATISpecObject::ClassName());
      
   int SizeOfL0Obj = L0Obj.length();
   CATISpecObject *piSpec;
   for (int iObj=0; iObj<SizeOfL0Obj; iObj++)
   {
	    piSpec = (CATISpecObject *) L0Obj[iObj];
	    if (NULL != piSpec) 
	    {
        if (!spObjFound)
        {
          ClassType = piSpec->GetType();
          MatchPos = ClassType.SearchSubString(iUClass);
          if (MatchPos >= 0)
          { 
            spObjFound = piSpec;
          }
        }
        piSpec->Release();
        piSpec = NULL;
	    }
   }
   return spObjFound;
}

//---------------------------------------------------------------------------
//  Find an application object in a container by a specific class type
//---------------------------------------------------------------------------
HRESULT CAASchAppBaseServices::FindAppObjByClass (
   const CATUnicodeString &iUClass, const CATIContainer_var &iCont,
   CATListValCATISpecObject_var &oLAppObjects)
{
   HRESULT RC = S_OK;
   oLAppObjects.RemoveAll();
   CATISpecObject_var spObjFound = NULL_var;
   CATUnicodeString ClassType;
   int MatchPos;
   CATISchAppConnectable *piSchAppCntbl = NULL;

   // @CSC-Filter VIOI vso(04-04-01)
   SEQUENCE (CATBaseUnknown_ptr) L0Obj = iCont->
      ListMembers(CATISpecObject::ClassName());
      
   int SizeOfL0Obj = L0Obj.length();
   CATISpecObject *piSpec;
   for (int iObj=0; iObj<SizeOfL0Obj; iObj++)
   {
	    piSpec = (CATISpecObject *) L0Obj[iObj];
	    if (NULL != piSpec) 
	    {
        ClassType = piSpec->GetType();
        MatchPos = ClassType.SearchSubString(iUClass);
        if (MatchPos >= 0)
        {
           spObjFound = piSpec;
           oLAppObjects.Append(spObjFound);
        }
        piSpec->Release();
        piSpec = NULL;
	    }
   }
   return RC;
}

//---------------------------------------------------------------------------
//  Find an application object in a container by a specific class type
//---------------------------------------------------------------------------
HRESULT CAASchAppBaseServices::RemoveAppObjInstByClass (
   const CATUnicodeString &iUClass, CATDocument *iDoc)
{
   HRESULT RC = S_OK;

   CATISpecObject_var spObjFound;
   CATUnicodeString ClassType;
   int MatchPos;
   CATIContainer_var spAppCont;
   CATIProduct_var spPrdRoot;
   CATIProduct_var spPrd;

   if (iDoc) spAppCont = GetAppObjContainer(iDoc);
   if (!!spAppCont)
   {
     spPrdRoot = GetProductRootObject(iDoc);
   }
   if (!!spAppCont && !!spPrdRoot)
   {
     // @CSC-Filter VIOI jsk(04-05-05)
     SEQUENCE (CATBaseUnknown_ptr) L0Obj = spAppCont->
        ListMembers(CATISpecObject::ClassName());
      
     int SizeOfL0Obj = L0Obj.length();
     CATISpecObject *piSpec;
     for (int iObj=0; iObj<SizeOfL0Obj; iObj++)
     {
	     piSpec = (CATISpecObject *) L0Obj[iObj];
	     if (NULL != piSpec) 
       { 
         ClassType = piSpec->GetType();
         MatchPos = ClassType.SearchSubString(iUClass);
         if (MatchPos >= 0)
         { 
           spObjFound = piSpec;

           // make sure this is an instance
           spPrd = spObjFound;
           if (!!spPrd) 
           {
             if (FAILED(spPrd->IsReference()))
             {
               // RemoveProduct
               spPrdRoot->RemoveProduct(spPrd);
             }
           } // if (!!spPrdRef) 
         }
         piSpec->Release();
         piSpec = NULL;
       }
     } // for iObj
   }
   return RC;
}
