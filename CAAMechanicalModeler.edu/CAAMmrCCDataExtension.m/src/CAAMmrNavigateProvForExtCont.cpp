// Local Framework
#include "CAAMmrNavigateProvForExtCont.h"
#include "CAAIMmrCCDataExtension.h"

// ObjectSpecsModeler Framework
#include "CATINavigateProvider.h"
#include "CATISpecObject.h"
#include "CATIOsmExtension.h"
#include "CATBaseUnknown.h"

// ObjectModelerBase Framework
#include "CATIContainer.h"
#include "CATILinkableObject.h"
#include "CATAppliContServices.h"
#include "CATDocument.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

// Include System
#include "CATUnicodeString.h"

// Include SpecialAPI
#include "CATDataType.h"

// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrNavigateProvForExtCont: CATIUpdateProviderExtension
//  Extends CATINavigateObject Mechanism to Extension Features Contained in MmrDataExtensionCont
//=================================================================================

CATImplementClass(CAAMmrNavigateProvForExtCont,
                  Implementation,
                  CATINavigateProvider,
                  CATNULL);

//CATTImplementClass( <ClassName>,
//                    <OM Type>,
//                    <OM Inheritance> ,
//                    <What It Extends | CATNULL>);
//
//As CAAMmrNavigateProvForExtCont is a component in Object Modeler Meaning,
//   <OM Type> == Implementation
//   <What It Extends | CATNULL> == CATNULL

CATImplementBOA(CATINavigateProvider, CAAMmrNavigateProvForExtCont);

CAAMmrNavigateProvForExtCont::CAAMmrNavigateProvForExtCont()
{
}

CAAMmrNavigateProvForExtCont::~CAAMmrNavigateProvForExtCont()
{
}

HRESULT CAAMmrNavigateProvForExtCont::GetChildren(CATBaseUnknown *  iObj , CATListPtrCATBaseUnknown **  oListChildren)
{
  HRESULT rc = E_FAIL;

  if ( NULL == iObj)
    return rc;

  if (*oListChildren  == NULL)
    *oListChildren = new CATListPtrCATBaseUnknown;

  //====================================================
  // 1] Retrieves a pointer to the applicative container.
  //====================================================
  CATILinkableObject *piLinkableOnObj = NULL;
  rc = iObj -> QueryInterface (IID_CATILinkableObject, (void**) &piLinkableOnObj);
  if (SUCCEEDED(rc) && piLinkableOnObj!= NULL)
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

    if(SUCCEEDED(rc) && pApplicativeCont!= NULL)
    {
      CATIContainer *piAppliCont = NULL;

      rc = pApplicativeCont-> QueryInterface(IID_CATIContainer, (void**) &piAppliCont);
      pApplicativeCont -> Release();
      pApplicativeCont = NULL;

      if(SUCCEEDED(rc) &&piAppliCont!= NULL)
      {
        //====================================================
        // 2] Retrieves the list of features in the applicative container
        //    Search Feature deriving from CATIOsmExtension
        //====================================================
        SEQUENCE(CATBaseUnknown_ptr)  pMemberList;
    
        // @CSC-Filter VIOI
        CATLONG32 NbObjects = piAppliCont -> ListMembersHere("CATIOsmExtension", pMemberList);

        piAppliCont -> Release();
        piAppliCont = NULL;

        if(NbObjects == NULL) return rc;

        for(int i=0;i<NbObjects;i++)
        {
          CAAIMmrCCDataExtension *piMmrCCDataExtension = NULL;
          rc = pMemberList[i] -> QueryInterface(IID_CAAIMmrCCDataExtension, (void**) &piMmrCCDataExtension);
          if(SUCCEEDED(rc) && piMmrCCDataExtension != NULL)
          {
            //====================================================
            // 3] We Show only Built Extension
            //====================================================
            CATICkeParm_var spValuatedParm;
            rc = piMmrCCDataExtension -> GetValuatedParam(spValuatedParm);
            if (SUCCEEDED (rc) && !!spValuatedParm)
              (*oListChildren)->Append(pMemberList[i]);
          }
        }
      }
    }
  }
  return rc;
}
