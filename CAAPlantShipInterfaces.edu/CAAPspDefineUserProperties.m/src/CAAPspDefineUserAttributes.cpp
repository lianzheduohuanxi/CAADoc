// COPYRIGHT DASSAULT SYSTEMES  2005
//=============================================================================
//
// CAAPspDefineUserAttributes - This sample illustrates how to 
// 1) Add computed attributes to an expose type in a Knowledgeware package.
// 2) Implement the GetValue() for the computed attribute added.
// 3) Get Enovia attributes 
//
//  CATIPspKweUserAttr
//
#include "CATLib.h"
#include <iostream.h>

// This framework
#include "CAAPspDefineUserAttributes.h"

// ProductStructure
#include "CATIPrdProperties.h"
#include "CATIProduct.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATOmbDocPropertyServices.h"
#include "CATILinkableObject.h"
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
#include "CATITypeDictionary.h"
#include "CATGlobalFunctions.h"


// System
#include "CATICStringList.h"
#include "CATListOfCATUnicodeString.h"
#include "CATString.h"
#include "CATErrorMacros.h"
#include "CATErrorDef.h"
#include "CATGetEnvValue.h"
#include "CATLISTV_CATBaseUnknown.h"

#define USER_ATTRIB1 "user_attrib1"
#define USER_ATTRIB2 "user_attrib2"
#define USER_ATTRIB3 "user_attrib3"
#define USER_ATTRIB4 "user_attrib4"

#define USER_ATTRIB1_NLS "Revision"
#define USER_ATTRIB2_NLS "Life Cycle Status"
#define USER_ATTRIB3_NLS "User In Enovia"
#define USER_ATTRIB4_NLS "Nomenclature"

#define PLM_ATTRIB1 "ENOVIA5.DocumentRevision.Value"
#define PLM_ATTRIB2 "ENOVIA5.DocumentStatus.Value"

#define PLM_ATTRIB1_NLS "Document Revision"
#define PLM_ATTRIB2_NLS "Document Status"

#define CAA_PSP_OPTIONAL 0

CATImplementClass(CAAPspDefineUserAttributes,
                   DataExtension,
                   CATBaseUnknown,
                   PipingLayout);

                  

#include "TIE_CATIPspKweUserAttr.h"
TIEchain_CATIPspKweUserAttr(CAAPspDefineUserAttributes);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAAPspDefineUserAttributes::CAAPspDefineUserAttributes() : CATPspKweUserAttrAdapter()
{
  if (CATGetEnvValue("RunSample",0) == CATLibSuccess)
  {
    cout << "<-> CAAPspDefineUserAttributes::CAAPspDefineUserAttributes()" << endl;
    
  }
  
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAAPspDefineUserAttributes::~CAAPspDefineUserAttributes()
{
  if (CATGetEnvValue("RunSample",0) == CATLibSuccess)
  {
    cout << "<-> CAAPspDefineUserAttributes::~CAAPspDefineUserAttributes" << endl;      
  }
  
}


//-----------------------------------------------------------------------------
// HRESULT CAAPspDefineUserAttributes::DefineKweUserAttr
//-----------------------------------------------------------------------------

HRESULT CAAPspDefineUserAttributes::DefineKweUserAttr(const CATString &isTypeName, 
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
    cout<<"Entering DefineKweUserAttr!!!!"<<endl;
    CATITypeDictionary_var spDico = CATGlobalFunctions::GetTypeDictionary();

    // Get Dictionary of types
    CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();

  
    if(!!spDico && !!spParmDictionary)
    {
      if( isTypeName == "PipingPart" )
      {   
        cout<<"Defining computed attribute for PipingPart "<< endl;
        //
        // Define Real type computed attribute TotalWallThickness
        //
        CATUnicodeString uAttrInternalName("TotalWallThickness");
        CATUnicodeString uAttrNLSName("Total Wall Thickness");

        CATICkeType_var spCkeReal = spParmDictionary->GetRealType();
        CATIType_var spTypeReal(spCkeReal);         

        CATAttributeInfos infoAttr(spTypeReal, uAttrInternalName, uAttrNLSName);
        olAttrInfos.Append(infoAttr);       

#if CAA_PSP_OPTIONAL
        //
        // Define attributes used to retrieve user product attributes
        //
        cout<<"Defining user attributes "<< endl;
        CATIType_var spTypeString1(spParmDictionary->GetStringType());         
        CATIType_var spTypeString2(spParmDictionary->GetStringType());         
        CATIType_var spTypeString3(spParmDictionary->GetStringType());         
        CATIType_var spTypeString4(spParmDictionary->GetStringType());         

        CATAttributeInfos infoAttr1(spTypeString1, USER_ATTRIB1, USER_ATTRIB1_NLS);
        CATAttributeInfos infoAttr2(spTypeString2, USER_ATTRIB2, USER_ATTRIB2_NLS);
        CATAttributeInfos infoAttr3(spTypeString3, USER_ATTRIB3, USER_ATTRIB3_NLS);
        CATAttributeInfos infoAttr4(spTypeString4, USER_ATTRIB4, USER_ATTRIB4_NLS);

        olAttrInfos.Append(infoAttr1);       
        olAttrInfos.Append(infoAttr2);       
        olAttrInfos.Append(infoAttr3);       
        olAttrInfos.Append(infoAttr4);       

        //
        // Define attributes used to retrieve user PLM document properties
        //
        {
          cout<<"Defining PLM Document attributes"<< endl;
         
          CATIType_var spTypeString1(spParmDictionary->GetStringType());         
          CATIType_var spTypeString2(spParmDictionary->GetStringType());         

          CATAttributeInfos infoAttr1(spTypeString1, PLM_ATTRIB1, PLM_ATTRIB1_NLS);
          CATAttributeInfos infoAttr2(spTypeString2, PLM_ATTRIB2, PLM_ATTRIB2_NLS);

          olAttrInfos.Append(infoAttr1);       
          olAttrInfos.Append(infoAttr2);       
        }
#endif
      }
      rc = S_OK;
    }
  }
  CATCatch (CATError, error)
  {    
    cout << "CAAPspDefineUserAttributes::DefineKweUserAttr *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  cout<<"Exit DefineKweUserAttr!!!!"<<endl;

  return rc;
}

//-----------------------------------------------------------------------------
// CAAPspDefineUserAttributes::GetValue
//-----------------------------------------------------------------------------

CATIValue* CAAPspDefineUserAttributes::GetValue (CATIInstance*  ipiObject, 
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

  cout<<"Entering CAAPspDefineUserAttributes::GetValue!!!!"<<endl;

  // Get volatile factory of values
  CATICkeParmFactory_var spVolFactory = CATCkeGlobalFunctions::GetVolatileFactory();

  CATIProduct_var spProd(ipiObject);

  CATIValue * piVal = NULL;
  CATTry 
  {
    CATUnicodeString uAttrInternalName("TotalWallThickness");
    if (iKey == uAttrInternalName)
    {
      CATICkeParm_var spResultParm;
      if (!!spVolFactory)
        spResultParm = spVolFactory->CreateLength(iKey, 0.0);

      double dTotWallThickness = 0.0;

      // Get values for the other exposed attributes that
      // will be used in calculating total of WallThickness* attributes
      CATListOfCATUnicodeString LWallThicknessAttr;
      LWallThicknessAttr.Append("WallThickness");
      LWallThicknessAttr.Append("WallThickness2");
      LWallThicknessAttr.Append("WallThickness3");
      LWallThicknessAttr.Append("WallThickness4");

      for( int idx =1; idx< LWallThicknessAttr.Size(); idx++ )
      {
        piVal = ipiObject->GetValue (LWallThicknessAttr[idx]);
        if( NULL != piVal )
        {
          double dVal;
          HRESULT rc1 = piVal->AsReal(dVal);
          if( SUCCEEDED(rc1) )
          {
            dTotWallThickness = dTotWallThickness + dVal;
          }
        }
        if( NULL != piVal)
        {
          piVal->Release();
          piVal = NULL;        
        }
      }
      if (!! spResultParm)
      {
        spResultParm->Valuate(dTotWallThickness);
			  spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
      } 
    } 
#if CAA_PSP_OPTIONAL
    else if ( iKey == USER_ATTRIB1 )
    {
      CATICkeParm_var spResultParm = GetUserStringValue(spVolFactory,spProd,USER_ATTRIB1,USER_ATTRIB1_NLS);

      if (!! spResultParm)
      {
        spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
      } 
    }
    else if ( iKey == USER_ATTRIB2 )
    {
      CATICkeParm_var spResultParm = GetUserStringValue(spVolFactory,spProd,USER_ATTRIB2,USER_ATTRIB2_NLS);

      if (!! spResultParm)
      {
        spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
      } 
    }
    else if ( iKey == USER_ATTRIB3 )
    {
      CATICkeParm_var spResultParm = GetUserStringValue(spVolFactory,spProd,USER_ATTRIB3,USER_ATTRIB3_NLS);

      if (!! spResultParm)
      {
        spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
      } 
    }
    else if ( iKey == USER_ATTRIB4 )
    {
      CATICkeParm_var spResultParm = GetUserStringValue(spVolFactory,spProd,USER_ATTRIB4,USER_ATTRIB4_NLS);

      if (!! spResultParm)
      {
        spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
      } 
    }

    else if (iKey == PLM_ATTRIB1 )
    {
      CATICkeParm_var spResultParm = GetPLMStringValue(spVolFactory,spProd,PLM_ATTRIB1,PLM_ATTRIB1_NLS);

      if (!! spResultParm)
      {
        spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
      } 
    } 
    else if (iKey == PLM_ATTRIB2 )
    {
      CATICkeParm_var spResultParm = GetPLMStringValue(spVolFactory,spProd,PLM_ATTRIB2,PLM_ATTRIB2_NLS);

      if (!! spResultParm)
      {
        spResultParm->QueryInterface(IID_CATIValue, (void **)&piResultValue);
      } 
    }
#endif
  }
  CATCatch (CATError, error)
  {    
    cout << "CAAPspDefineUserAttributes::GetValue *** CATRethrow" << endl;
    if( NULL != piVal)
    {
      piVal->Release();
      piVal = NULL;        
    }
    CATRethrow;
  } 
  CATEndTry;


  if( NULL != piVal)
  {
    piVal->Release();
    piVal = NULL;        
  }

  if (piResultValue)
  {
    cout << "Returning value:" << (piResultValue->Show()).ConvertToChar();    
  }
  
  cout<<"Exit CAAPspDefineUserAttributes::GetValue!!!!"<<endl;

  return piResultValue;
}

CATICkeParm_var CAAPspDefineUserAttributes::GetUserStringValue(CATICkeParmFactory *iVolFactory,
                                                                CATIProduct *iProd, 
                                                                const CATUnicodeString &iAttName,
                                                                const CATUnicodeString &iAttNLSName)
{
  CATUnicodeString uAttrib = iAttName;
  CATUnicodeString uNLSName = iAttNLSName;
  
  CATUnicodeString uValue = "cannot find";
  uValue += uAttrib;
  uValue += "(";
  uValue += uNLSName;
  uValue += ")";

  CATICkeParm_var spResultParm;

  if ( !iVolFactory || !iProd ) return spResultParm;

  spResultParm = iVolFactory->CreateString(iAttName,uValue);
 

  CATIProduct_var spRefProd = iProd->GetReferenceProduct();
  CATIPrdProperties_var spPrdProps( spRefProd );
  
  if ( !!spPrdProps ) 
  {
    CATListOfCATUnicodeString LNLSNames;
    LNLSNames.Append(uNLSName);
    
    CATListValCATBaseUnknown_var LProp;
    
    spPrdProps->FilterPropertiesByName(LNLSNames,LProp,FALSE);
    
    int nParm = LProp.Size();
    if ( nParm > 0 )
    {
      CATBaseUnknown_var spBUParm = LProp[1];
      CATICkeParm_var hCkeParm = spBUParm;
      if (!!hCkeParm ) 
      {
        CATUnicodeString uValueProp;
        uValueProp = hCkeParm->Show();
        cout << (uNLSName.ConvertToChar()) << " : " << (uValueProp.ConvertToChar()) << endl;
        uValue = uValueProp;
      }
    }
  }

  if (!! spResultParm)
  {
    spResultParm->Valuate(uValue);
  }

  return spResultParm;
}

CATICkeParm_var CAAPspDefineUserAttributes::GetPLMStringValue(CATICkeParmFactory *iVolFactory,
                                                                CATIProduct *iProd, 
                                                                const CATUnicodeString &iAttName,
                                                                const CATUnicodeString &iAttNLSName)
{
  CATUnicodeString uAttrib = iAttName;
  CATUnicodeString uNLSName = iAttNLSName;
  
  CATUnicodeString uValue = "cannot find";
  uValue += uAttrib;
  uValue += "(";
  uValue += uNLSName;
  uValue += ")";

  CATICkeParm_var spResultParm;

  if ( !iVolFactory || !iProd ) return spResultParm;

  spResultParm = iVolFactory->CreateString(iAttName,uValue);
 
  CATILinkableObject_var spLinkShape;
  iProd->GetShapeRep(spLinkShape);
  
  if ( !!spLinkShape )
  {
    CATDocument* pDoc = spLinkShape->GetDocument();
    
    CATIDocId *piDocId = NULL;
    if ( pDoc )
    {
      pDoc->GetDocId(&piDocId);
      
      if ( piDocId )
      {
        CATUnicodeString uValueProp;
        if ( SUCCEEDED( CATOmbDocPropertyServices::GetValue(piDocId,uAttrib,uValueProp) ) )
        {
          cout << (uAttrib.ConvertToChar()) << " = " << uValueProp.ConvertToChar() << endl;
          uValue = uValueProp;
        }
        piDocId->Release();
        piDocId = NULL;
      }
    }
  }

  if (!! spResultParm)
  {
    spResultParm->Valuate(uValue);
  }

  return spResultParm;
}

/* - Within these comments is a sample attribute mapping xml file used for this use case.

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE MappingDescrition SYSTEM "AttributesMapping.dtd">
<!-- COPYRIGHT DASSAULT SYSTEMES 2005 -->
<MappingDescrition>
   <DomainDef EntityType="Part" DefinitionType="FixedValue" Name="PRODUCT" />

   <DomainDef EntityType="Document" DefinitionType="FixedValue" Name="DOCDIR" />

<!-- Attributes for Part Domain -->
   <AttributesMapping EntityType="Part" DomainName="PRODUCT">

   <!-- Part Attribute 1 -->
      <Attribute Name="Revision" Type="STRING">
         <CATIAInfo Name="Revision" Editable="No" Visible="Yes" />
         <DBInfo Name="V_version" LCASubEntity="PV" Editable="Yes" Visible="Yes" />
      </Attribute>

   <!-- Part Attribute 2 -->
      <Attribute Name="Status" Type="STRING">
         <CATIAInfo Name="Life Cycle Status" Editable="No" Visible="Yes" />
         <DBInfo Name="V_status" LCASubEntity="PV" Editable="Yes" Visible="Yes" />
      </Attribute>

   <!-- Part Attribute 3 -->
      <Attribute Name="DBUser" Type="STRING">
         <CATIAInfo Name="User In Enovia" Editable="No" Visible="Yes" />
         <DBInfo Name="V_user" LCASubEntity="PM" Editable="Yes" Visible="Yes" />
      </Attribute>

   <!-- Part Attribute 4 -->
      <Attribute Name="Nomenclature" Type="STRING">
         <CATIAInfo Name="Nomenclature" Editable="No" Visible="Yes" />
         <DBInfo Name="V_organization" LCASubEntity="II" Editable="Yes" Visible="Yes" />
      </Attribute>
   </AttributesMapping>

<!-- Attributes for Document Domain -->
   <AttributesMapping EntityType="Document" DomainName="DOCDIR">
	
   <!-- Document Attribute 1 -->
      <Attribute Name="DocumentRevision" Type="STRING">
         <CATIAInfo Name="ENOVIA5.DocumentRevision" Editable="No" Visible="Yes" />
         <DBInfo    Name="V_version" LCASubEntity="DV" Editable="Yes" Visible="Yes" />
      </Attribute>

   <!-- Document Attribute 2 -->
      <Attribute Name="Status" Type="STRING">
         <CATIAInfo Name="ENOVIA5.DocumentStatus" Editable="No" Visible="Yes" />
         <DBInfo Name="V_status" LCASubEntity="DV" Editable="Yes" Visible="Yes" />
      </Attribute>
   </AttributesMapping>

</MappingDescrition>
*/

