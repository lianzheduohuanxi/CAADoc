// COPYRIGHT DASSAULT SYSTEMES 2007
//==================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrVisuProvForExtCont : CATI3DVisuProvider Extension for MmrDataExtensionCont
//
//  Extends Visu to FeatureExtensions Contained in MmrDataExtensionCont
//==================================================================================

// Local Framework
#include "CAAMmrVisuProvForExtCont.h"

// ObjectSpecsModeler Framework
#include "CATI3DVisuProvider.h"
#include "CATI3DGeoVisu.h"
// ObjectModelerBase Framework
#include "CATILinkableObject.h"
#include "CATAppliContServices.h"
#include "CATIOsmExtendable.h"
#include "CATIOsmExtension.h"
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATListOfCATBaseUnknown.h"

// Include System FW
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// Include SpecialAPI
#include "CATDataType.h"
//==================================================================================

CATImplementClass(CAAMmrVisuProvForExtCont,
                  Implementation,
                  CATI3DVisuProvider,
                  CATNULL);

//CATTImplementClass( <ClassName>,
//                    <OM Type>,
//                    <OM Inheritance> ,
//                    <What It Extends | CATNULL>);
//
//As CAAMmrVisuProvForExtCont is a component in Object Modeler Meaning,
//   <OM Type> == Implementation

CATImplementBOA(CATI3DVisuProvider, CAAMmrVisuProvForExtCont);

CAAMmrVisuProvForExtCont::CAAMmrVisuProvForExtCont()
{
}

CAAMmrVisuProvForExtCont::~CAAMmrVisuProvForExtCont()
{
}

HRESULT CAAMmrVisuProvForExtCont::GetChildren(CATBaseUnknown * iObj, CATLISTP(CATBaseUnknown) ** oListChildren)
{
  HRESULT rc = E_FAIL;

  if ( NULL == iObj)
    return rc;

  CATIContainer * piMmrDataCont = NULL; 

  // 1] Retrieves a pointer to the applicative container.
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
      rc = pApplicativeCont-> QueryInterface(IID_CATIContainer, (void**) &piMmrDataCont);
    }
  }

  if(SUCCEEDED(rc) && piMmrDataCont!= NULL)
  {
    // 2] Retrieves the Extension contained in the container.
    SEQUENCE(CATBaseUnknown_ptr)  pMemberList;

    // @CSC-Filter VIOI
    CATLONG32 NbObjects = piMmrDataCont -> ListMembersHere("CATIOsmExtension", pMemberList);
    if(NbObjects != NULL)
    {
      CATI3DGeoVisu_var hMemberForVisu = NULL_var;
      // 3] Filters Extension with visu impl.
      for(int i=0;i<NbObjects;i++)
      {
        hMemberForVisu = pMemberList[i];
        if( !(*oListChildren) )
          *oListChildren = new CATLISTP(CATBaseUnknown);

        if (hMemberForVisu!= NULL_var)
        {
          // Add member with visu impl
          CATBaseUnknown* pExtensionWithVisu = NULL;
          rc = pMemberList[i] -> QueryInterface(IID_CATBaseUnknown, (void**) & pExtensionWithVisu);
          if(SUCCEEDED(rc) && pExtensionWithVisu != NULL)
          {
            (*oListChildren) -> Append(pExtensionWithVisu);
            pExtensionWithVisu -> Release();
            pExtensionWithVisu = NULL;
          }
          //Beware Must Release pMemberList elements after use
          //(C.f. CATIContainer::ListMembersHere)
          pMemberList[i]->Release();
          pMemberList[i] = NULL;
        }
      }
    }
    //Release due to addref of GetMmrDataExtension !
    piMmrDataCont-> Release();
    piMmrDataCont = NULL;
  }
  return rc;
}

