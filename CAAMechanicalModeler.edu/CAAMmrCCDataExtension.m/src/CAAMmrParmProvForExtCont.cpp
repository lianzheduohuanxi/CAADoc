// COPYRIGHT DASSAULT SYSTEMES 2007
//==================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrParmProvForExtCont : CATIParmProvider Extension for MmrDataExtensionCont
//
//  Extends ParmPublisher to FeatureExtensions Contained in MmrDataExtensionCont
//==================================================================================

// Local Framework
#include "CAAMmrParmProvForExtCont.h"
#include "CAAIMmrCCDataExtension.h"

// ObjectSpecsModeler Framework
#include "CATIParmProvider.h"
#include "CATISpecObject.h"

// ObjectModelerBase Framework
#include "CATILinkableObject.h"
#include "CATAppliContServices.h"
#include "CATIOsmExtendable.h"
#include "CATIOsmExtension.h"
#include "CATIContainer.h"
#include "CATDocument.h"

// Include System FW
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"

// Include SpecialAPI
#include "CATDataType.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

//==================================================================================

CATImplementClass(CAAMmrParmProvForExtCont,
                  Implementation,
                  CATIParmProvider,
                  CATNULL);

//CATTImplementClass( <ClassName>,
//                    <OM Type>,
//                    <OM Inheritance> ,
//                    <What It Extends | CATNULL>);
//
//As CAAMmrParmProvForExtCont is a component in Object Modeler Meaning,
//   <OM Type> == Implementation
//   <What It Extends | CATNULL> == CATNULL

CATImplementBOA(CATIParmProvider, CAAMmrParmProvForExtCont);

CAAMmrParmProvForExtCont::CAAMmrParmProvForExtCont()
{
}

CAAMmrParmProvForExtCont::~CAAMmrParmProvForExtCont()
{
}

HRESULT CAAMmrParmProvForExtCont::GetDirectChildren(CATClassId intfName, CATListValCATBaseUnknown_var* oList,CATBaseUnknown* iObj)
{
  //
  //  Don't Forget "The MechanicalPart context": iObj represents the Mechanical Part.
  //
  HRESULT rc = E_FAIL;

  if ( NULL == iObj)
    return rc;
  if (oList  == NULL)
    oList = new CATListValCATBaseUnknown_var;

  rc = AddExtendedParmToPublish(iObj,
                                intfName, 
                                oList);

  //====================================================
  // 1] Retrieves a pointer to the applicative container.
  //====================================================
  CATILinkableObject *piLinkableOnObj = NULL;

  rc = iObj -> QueryInterface (IID_CATILinkableObject, (void**) &piLinkableOnObj);
  if(SUCCEEDED(rc) && piLinkableOnObj != NULL)
  {
    CATDocument* pDoc = piLinkableOnObj -> GetDocument();

    piLinkableOnObj -> Release();
    piLinkableOnObj = NULL;

    const CATUnicodeString AppContTypeLate ("MmrDataExtensionCont");
    CATBaseUnknown *pApplicativeCont = NULL;

    rc = ::CATGetApplicativeContainer(&pApplicativeCont,
                                      pDoc,
                                      IID_CATIContainer,
                                      AppContTypeLate);

    if(SUCCEEDED(rc) && pApplicativeCont != NULL)
    {
      CATIContainer *piAppliCont = NULL;
      rc = pApplicativeCont-> QueryInterface(IID_CATIContainer, (void**) &piAppliCont);

      if(SUCCEEDED(rc) && piAppliCont!= NULL)
      {
        //====================================================
        // 2] Retrieves the list of features in the applicative container
        //    Search Feature deriving from CATIOsmExtension
        //====================================================
        SEQUENCE(CATBaseUnknown_ptr)  pMemberList;
        
        // @CSC-Filter VIOI
        CATLONG32 NbObjects = piAppliCont -> ListMembersHere("CATIOsmExtension",
                                                           pMemberList);
        piAppliCont -> Release();
        piAppliCont = NULL;

        if(NbObjects != NULL)
        {
          CATISpecObject *piSpecsMember = NULL; 	
        
          for(int i=0;i<NbObjects;i++)
          {
            CATIOsmExtension_var hOsmExtension = NULL_var;
            hOsmExtension = pMemberList[i];
            rc = hOsmExtension -> QueryBaseObject(IID_CATISpecObject, (void**)& piSpecsMember);
            if(SUCCEEDED(rc) && piSpecsMember != NULL)
            {
               rc = AddExtendedParmToPublish(piSpecsMember,
                                             intfName, 
                                             oList);
               piSpecsMember -> Release();
               piSpecsMember = NULL;
            }
            pMemberList[i] -> Release();
            pMemberList[i] = NULL;
          }
        }
      }
    }
  }
  return rc;
}


HRESULT CAAMmrParmProvForExtCont::AddExtendedParmToPublish(CATBaseUnknown* iBaseFeature,
                                                           CATClassId intfName, 
                                                           CATListValCATBaseUnknown_var* lst)
{
  HRESULT rc = E_FAIL;

  if (lst == NULL)
    return rc;

  CATIOsmExtendable_var hExtendableOnBaseFeature = iBaseFeature;

  CATBaseUnknown *piMmrCCDataExtension = NULL_var;

  // 1 ] Retrieves Features Extending iBaseFeature and adhering to CAAIMmrCCDataExtension.
  rc = hExtendableOnBaseFeature -> QueryExtension("MmrCCDataExtension", IID_CAAIMmrCCDataExtension, (void**) &piMmrCCDataExtension);
  if(SUCCEEDED(rc) && piMmrCCDataExtension != NULL)
  {
    //2 ] Retrieves the paramter to publish with f(x)
    CATICkeParm_var spValuatedParm;

    rc = ((CAAIMmrCCDataExtension*)piMmrCCDataExtension )-> GetValuatedParam(spValuatedParm);
    if (SUCCEEDED (rc) && !!spValuatedParm)
    {
      // 3 ] Append the Valuated Parameter to list of published parameter.
      CATBaseUnknown* obj = (CATBaseUnknown*)spValuatedParm -> QueryInterface(intfName);
      if (obj!=NULL)
      {
        obj->Release();
        lst -> Append(spValuatedParm);
      }
    }
    piMmrCCDataExtension -> Release();
    piMmrCCDataExtension = NULL;
  }
  else
    rc = S_FALSE;
  return rc;
}
