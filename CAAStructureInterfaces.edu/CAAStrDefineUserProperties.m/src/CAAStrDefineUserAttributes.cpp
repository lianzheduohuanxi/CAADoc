// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================
//
// CAAStrDefineUserAttributes - This sample illustrates how to 
// 1) Add computed attributes to an expose type in a Knowledgeware package.
// 2) Implement the GetValue() for the computed attribute added.
// 3) Get Enovia attributes 
//
//  CATIPspKweUserAttr
//
#include "CATLib.h"
#include <iostream.h>

// This framework
#include "CAAStrDefineUserAttributes.h"

// ProductStructure
#include "CATIPrdProperties.h"
#include "CATIProduct.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATOmbDocPropertyServices.h"
#include "CATILinkableObject.h"
#include "CATInit.h"
#include "CATIDocId.h"

// KnowledgeInterfaces
#include "CATAttributeInfos.h"
#include "CATListValCATAttributeInfos.h"
#include "CATIInstance.h"
#include "CATIType.h"
#include "CATCkeGlobalFunctions.h"
#include "CATIParmDictionary.h"

#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATIParmPublisher.h"
#include "CATITypeDictionary.h"
#include "CATGlobalFunctions.h"

// MecModInterfaces
#include "CATIPrtContainer.h"
// System
#include "CATICStringList.h"
#include "CATListOfCATUnicodeString.h"
#include "CATString.h"
#include "CATErrorMacros.h"
#include "CATErrorDef.h"
#include "CATGetEnvValue.h"
#include "CATIStructureMember.h"
#include "CATLISTV_CATBaseUnknown.h"

#define USER_ATTR_SectionArea "SectionArea"
#define USER_ATTR_SectionArea_NLS "Section Area"

CATImplementClass(CAAStrDefineUserAttributes,
                   DataExtension,
                   CATBaseUnknown,
                   StrFunctionalDesign);

                  

#include "TIE_CATIPspKweUserAttr.h"
TIEchain_CATIPspKweUserAttr(CAAStrDefineUserAttributes);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAAStrDefineUserAttributes::CAAStrDefineUserAttributes() : CATPspKweUserAttrAdapter()
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAAStrDefineUserAttributes::~CAAStrDefineUserAttributes()
{  
}


//-----------------------------------------------------------------------------
// HRESULT CAAStrDefineUserAttributes::DefineKweUserAttr
//-----------------------------------------------------------------------------

HRESULT CAAStrDefineUserAttributes::DefineKweUserAttr(const CATString &isTypeName, 
                                  CATListValCATAttributeInfos &olAttrInfos) 
{

  HRESULT rc = E_FAIL;

  //
  // To activate this implementation remove the following "if" conditional block.
  //

  if (CATGetEnvValue("RunSample",0) != CATLibSuccess)
  {
    return rc;
  }


  CATTry 
  {
    CATITypeDictionary_var spDico = CATGlobalFunctions::GetTypeDictionary();

    // Get Dictionary of types
    CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();

    if(!!spDico && !!spParmDictionary)
    {
      if( isTypeName == "CATSfmStiffenerExt" ||
          isTypeName == "CATSfmBeamExt"      ||
          isTypeName == "CATSfmStiffenerOnFreeEdgeExt")
      {   
        cout<<"Defining computed attribute for " << isTypeName.CastToCharPtr() << endl;
        //
        // Define Real type computed attribute SectionArea
        //
        CATUnicodeString uAttrInternalName(USER_ATTR_SectionArea);
        CATUnicodeString uAttrNLSName(USER_ATTR_SectionArea_NLS);

        CATICkeType_var spCkeReal = spParmDictionary->GetRealType();
        CATIType_var spTypeReal(spCkeReal);         

        CATAttributeInfos infoAttr(spTypeReal, uAttrInternalName, uAttrNLSName);
        olAttrInfos.Append(infoAttr);       
      }
      rc = S_OK;
    }
  }
  CATCatch (CATError, error)
  {    
    cout << "CAAStrDefineUserAttributes::DefineKweUserAttr *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;

  return rc;
}

//-----------------------------------------------------------------------------
// CAAStrDefineUserAttributes::GetValue
//-----------------------------------------------------------------------------

CATIValue* CAAStrDefineUserAttributes::GetValue (CATIInstance*  ipiObject, 
                       const CATUnicodeString& iKey) 
{
  HRESULT rc = E_FAIL;


  CATIValue * piResultValue = NULL;

  //
  // To active this implementation remove the following condition
  //
  if (CATGetEnvValue("RunSample",0) != CATLibSuccess)
  {
    return piResultValue;
  }

  if( NULL == ipiObject) return piResultValue;

  // Get volatile factory of values
  CATICkeParmFactory_var spVolFactory = CATCkeGlobalFunctions::GetVolatileFactory();

  CATTry 
  {
    CATUnicodeString uAttrInternalName(USER_ATTR_SectionArea);
    if (iKey == uAttrInternalName)
    {
      CATIStructureMember *piStrMember = NULL;
      ipiObject->QueryInterface(IID_CATIStructureMember, (void **)&piStrMember);
      if ( NULL != piStrMember)
      {
        CATLISTV(CATISpecObject_var) oListParameters;
        CATISpecObject_var spSpecObjectPart;
        CATDocument *piSectionDoc = NULL;
        piStrMember->GetSection(piSectionDoc);
        if (piSectionDoc)
        {
          CATInit *pInitOnDoc = NULL ;
          if (SUCCEEDED(piSectionDoc->QueryInterface(IID_CATInit,(void **) &pInitOnDoc)) && pInitOnDoc)
          {
            CATIPrtContainer *pIPrtCont = NULL ;
            pIPrtCont = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");
            if (pIPrtCont)
            {
              spSpecObjectPart = pIPrtCont->GetPart();
              pIPrtCont->Release(); pIPrtCont = NULL;
            }
            pInitOnDoc->Release(); pInitOnDoc = NULL;
          }
        }

        // Get all the parameters under the part
        CATIParmPublisher_var spParmPub(spSpecObjectPart);
        if (!! spParmPub)
        {
          spParmPub->GetAllChildren("CATICkeParm",oListParameters);
        }

        double SectionArea = 0.;
        CATICkeParm_var spResultParm;

        // Get the Section Area from Parameter "A"
        int lSize = oListParameters.Size();
        for (int i=1; i <= lSize; i++)
        {
          CATICkeParm_var spCkeParm(oListParameters[i]);
          cout << " Parameter name "  << (spCkeParm->Name()).ConvertToChar() << endl;
          cout << " Parameter Role " << (spCkeParm->Role()).ConvertToChar() << endl;
          cout << " Parameter value " << (spCkeParm->Show()).ConvertToChar() << endl;
          if (!! spCkeParm )
          {
            CATUnicodeString SectionParameterArea("A");
            CATUnicodeString ParameterRole = (spCkeParm->Role()).Strip(CATUnicodeString::CATStripModeBoth);
            if (ParameterRole == SectionParameterArea )
            {
              SectionArea = (spCkeParm->Value())->AsReal();
              break;
            }
          }
        }

        if (!!spVolFactory)
        {
          CATUnicodeString iUnit = "AREA";
          CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();
          if (!! spParmDictionary)
          {
            CATICkeMagnitude_var spMagnitude = spParmDictionary->FindMagnitude(iUnit);
            spResultParm = spVolFactory->CreateDimension(spMagnitude,iKey,SectionArea);
          }
        }
        if (!! spResultParm)
        {
          spResultParm->Valuate(SectionArea);
			    spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
        }
        piStrMember->Release();
        piStrMember = NULL;
      }
    }
  }
  CATCatch (CATError, error)
  {    
    cout << "CAAStrDefineUserAttributes::GetValue *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;

  if (piResultValue)
  {
    cout << "Returning value: " << (piResultValue->Show()).ConvertToChar() << endl;    
  }
  
  return piResultValue;
}


