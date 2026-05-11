// COPYRIGHT DASSAULT SYSTEMES 2007

// Local Framework
#include "CAAMmrUpdateProvForExtCont.h"

// ObjectSpecsModeler Framework
#include "CATIUpdateProvider.h"
#include "CATISpecObject.h"
#include "CATIOsmExtension.h"
#include "CATIOsmUpdate.h"
#include "CATErrorMacros.h"

// ObjectModelerBase Framework
#include "CATIContainer.h"
#include "CATILinkableObject.h"
#include "CATAppliContServices.h"
#include "CATDocument.h"
#include "CATIModelEvents.h"
#include "CATModify.h"

// Include System FW
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"

// Include SpecialAPI
#include "CATDataType.h"

//=================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrUpdateProvForExtCont : CATIUpdateProvider Extension for MmrDataExtensionCont
//
//  Extends UpdateMechanism to ExtensionFeatures Contained in MmrDataExtensionCont
//==================================================================================

CATImplementClass(CAAMmrUpdateProvForExtCont,
                  Implementation,
                  CATIUpdateProvider,
                  CATNULL);
//CATTImplementClass( <ClassName>,
//                    <OM Type>,
//                    <OM Inheritance> ,
//                    <What It Extends | CATNULL>);
//
//As CAAMmrUpdateProvForExtCont is a component in Object Modeler Meaning,
//   <OM Type> == Implementation
//   <What It Extends | CATNULL> == CATNULL

CATImplementBOA(CATIUpdateProvider, CAAMmrUpdateProvForExtCont);

CAAMmrUpdateProvForExtCont::CAAMmrUpdateProvForExtCont()
{
}

CAAMmrUpdateProvForExtCont::~CAAMmrUpdateProvForExtCont()
{
}

int CAAMmrUpdateProvForExtCont::Update(CATBaseUnknown* iWorkingObj, CATIDomain_var iDomain)
{
  int retnum = 1; 

  if (NULL == iWorkingObj)
    return retnum;

  CATIContainer * piMmrDataCont = NULL; 

  //Keep in Mind The MechanicalPart context: iWorkingObj represents the Mechanical Part.
  //
  //1 ]Retrieves the MmrDataExtensionCont container
  //
  HRESULT rc = CAAMmrUpdateProvForExtCont::GetMmrDataExtension(iWorkingObj, &piMmrDataCont);

  if(SUCCEEDED(rc) && piMmrDataCont!= NULL)
  {
    // 2 ] Retrieves the Extension Features contained in MmrDataExtensionCont container
    SEQUENCE(CATBaseUnknown_ptr)  pMemberList;

    // @CSC-Filter VIOI
    CATLONG32 NbObjects = piMmrDataCont -> ListMembersHere("CATIOsmExtension",
                                                           pMemberList);
    if(NbObjects != NULL)
    {
      CATISpecObject_var  hSpecsMemberForUpdate = NULL_var;
      for(int i=0;i<NbObjects;i++)
      {
        hSpecsMemberForUpdate = pMemberList[i];
        if (hSpecsMemberForUpdate != NULL_var)
        {
          // 3 ] Update Extension Features
          //     Don't forget to use a CATTry - CATCatch - CATEndTry when you try to Update a Feature !!
          CATTry
          {
            retnum = hSpecsMemberForUpdate -> Update();

            // 4 ] After Update, Send an Event for Visu in order to advice VisuManager for a modification in Model
            CATIModelEvents_var hModelEventOnThis = hSpecsMemberForUpdate;
            if(!!hModelEventOnThis)
            {
              CATModify BuiltInfo(pMemberList[i]);     
              hModelEventOnThis -> Dispatch(BuiltInfo);
            }
          } 
          CATCatch(CATError, error)
            CATRethrow;
          CATEndTry;

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
  return retnum;
}

CATBoolean CAAMmrUpdateProvForExtCont::IsUpToDate(CATBaseUnknown* iWorkingObj, CATIDomain_var iDomain) const
{
  CATBoolean RetBool = TRUE;

  if (NULL == iWorkingObj)
    return RetBool;

  CATIContainer * piMmrDataCont = NULL; 

  //Keep in Mind The MechanicalPart context: iWorkingObj represents the Mechanical Part.
  //
  //1 ]Retrieves the MmrDataExtensionCont container
  //
  HRESULT rc = CAAMmrUpdateProvForExtCont::GetMmrDataExtension(iWorkingObj, &piMmrDataCont);

  if(SUCCEEDED(rc) && piMmrDataCont!= NULL)
  {
    // 2 ] Retrieves the Extension Features contained in MmrDataExtensionCont container
    SEQUENCE(CATBaseUnknown_ptr)  pMemberList;

    // @CSC-Filter VIOI
    CATLONG32 NbObjects = piMmrDataCont -> ListMembersHere("CATIOsmExtension", pMemberList);
    //Release due to addref of GetMmrDataExtension !
    piMmrDataCont -> Release();
    piMmrDataCont = NULL;

    if(NbObjects != NULL)
    {
      CATISpecObject_var  hSpecsMember = NULL_var;
      for(int i=0;i<NbObjects;i++)
      {
        hSpecsMember = pMemberList[i];
        if (hSpecsMember != NULL_var)
        {
          // 3 ] Test "IsUpToDate" on Extension Features
          if(hSpecsMember -> IsUpToDate(iDomain) == FALSE)
            RetBool = FALSE ;
          
          //Beware Must Release pMemberList elements after use
          //(C.f. CATIContainer::ListMembersHere)
          pMemberList[i]->Release();
          pMemberList[i] = NULL;
        }
      }
    }
  }
  return RetBool;
}

void CAAMmrUpdateProvForExtCont::SetUpToDate(CATBaseUnknown* iWorkingObj, boolean iFlag )
{
  return; //Not Implemented
}

int CAAMmrUpdateProvForExtCont::IsInactive(CATBaseUnknown* iWorkingObj) const
{
  return 0;//Not Implemented
}

HRESULT CAAMmrUpdateProvForExtCont::GetMmrDataExtension(CATBaseUnknown* iWorkingObj, CATIContainer ** ioMmrDataCont)
{
  // Retrieves a pointer to the applicative container.
  CATILinkableObject *piLinkableOnObj = NULL;

  if(iWorkingObj == NULL)
    return E_FAIL;

  HRESULT rc = iWorkingObj -> QueryInterface (IID_CATILinkableObject, (void**) &piLinkableOnObj);
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
      rc = pApplicativeCont-> QueryInterface(IID_CATIContainer, (void**) ioMmrDataCont);
    }
  }
  return rc;
}
