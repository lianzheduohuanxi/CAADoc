/**
 * @quickreview wxu 07:05:08 Disable EsuDeletionMicro.
 * @quickreview eml 07:04:25 Replace tabs with spaces.
 * @fullreview eml svo 07:04:24 Creation
 */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2007
//=============================================================================
//  
//  Component Identifier: CAADVTubeAttributes.cpp
//  
//=============================================================================
//  
//  Implementation Notes:
//
//  This checks tube attributes.
//  Input attributes:
//    Operating Pressure (from line)
//    Nominal Size
//    Material Category
//
//  Output attributes:
//    Allowed nominal sizes.
//    Allowed material.
//
//  Violation Object ---> CATCloViolation_Atr 
//
//
//  HRESULT return has the following meaning:
//
//         CATReturnSuccess (S_OK) ...... Design violation detected & Violation object created
//         S_FALSE ... No violation found (or Check not applicable)
//         CATReturnFailure (E_FAIL) .... Violation check not performed due to invalid input/errors
//
//
//=============================================================================
//
// Creation:  2007 April 23                                    Eric Miller
//
//=============================================================================

#include "CAADVTubeAttributes.h"

#include "CAAViolationTubeAttributes.h"

#include "CATError.h"
#include "CATErrorMacros.h"

//#include "CATEsuDeletionMacro.h"

#include "CATIPspAttribute.h"
#include "CATIPspGroupable.h"
#include "CATIPspLogicalLine.h"
#include "CATIPspObject.h"
#include "CATICkeParm.h"
#include "IUnknown.h"
#include "CATIUnknownList.h"
#include "CATObject.h"
#include "CATISpecObject.h"
#include "CATUnicodeString.h"


CATImplementClass( CAADVTubeAttributes, 
                   CodeExtension, 
                   CATEAPspDesignValidation,  // adaptor
                   CAATubAttr );

#include <TIE_CATIPspDesignValidation.h>
TIE_CATIPspDesignValidation(CAADVTubeAttributes);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAADVTubeAttributes::CAADVTubeAttributes():CATEAPspDesignValidation () {}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAADVTubeAttributes::~CAADVTubeAttributes() {}

//-----------------------------------------------------------------------------
//  CATIPspDesignValidation methods
//-----------------------------------------------------------------------------
HRESULT CAADVTubeAttributes::GetValidationChecks( CATListValCATUnicodeString& oChecks )
{
  oChecks.RemoveAll();
  oChecks.Append( "TubeSize" );
  oChecks.Append( "TubeMaterial" );
  return CATReturnSuccess;
}

//-----------------------------------------------------------------------------
HRESULT CAADVTubeAttributes::IsObjectAViolation( const CATBaseUnknown* iObject,
                                                 const CATListValCATUnicodeString& iChecks,
                                                 CATListPV** oViolation, 
                                                 const unsigned int& iErrorFile )
{
  HRESULT returnCode = CATReturnFailure;
  *oViolation = NULL;

  //--------------------------------------------------------------------------
  // Declare variables here to avoid memory leaks from thrown errors
  //--------------------------------------------------------------------------
  // Variables that need release handling.

  // Variables that do not need release handling.
  int numChecks = 0;

  CATTry
  {
    // Determine which checks were requested
    int numChecks = iChecks.Size();

    if (iObject && 
        0 <= numChecks)
    {
      returnCode = S_FALSE; // Input OK, now most failure because test not applicable.

      if ( SUCCEEDED(returnCode) && iChecks.Locate ("TubeSize") > 0 )
      {
        HRESULT rcCheck = CheckTubeSize(iObject, 
                                        oViolation, 
                                        iErrorFile);
        if (S_FALSE != rcCheck)
          returnCode = rcCheck;
      }
      if ( SUCCEEDED(returnCode) && iChecks.Locate ("TubeMaterial") > 0 )
      {
        HRESULT rcCheck = CheckTubeMaterial(iObject, 
                                            oViolation, 
                                            iErrorFile);
        if (S_FALSE != rcCheck)
          returnCode = rcCheck;
      }

    } // End if valid input.
  } // End CATTry

  CATCatch( CATError, pError )
  {    
    returnCode = CATReturnError(pError);
  }
  CATEndTry;

  // Release memory

  return returnCode;
}

//----------------------------------------------------------------------------- 
//  CATEAPspDesignValidation  methods
//-----------------------------------------------------------------------------
HRESULT CAADVTubeAttributes::GetClassification( CATUnicodeString& oClassification )
{
  oClassification = Validation_Object;
  return CATReturnSuccess;
}

HRESULT CAADVTubeAttributes::GetResource( CATUnicodeString& oName )
{
  oName = "CAAPspDesignValidation";
  return CATReturnSuccess;
}

//----------------------------------------------------------------------------- 
HRESULT CAADVTubeAttributes::GetColumnTitles( CATListValCATUnicodeString& oTitles )
{
  HRESULT returnCode = CATReturnFailure;
  oTitles.RemoveAll();
  CATListValCATUnicodeString column;

  // From CAAPspDesignValidation.CATNls file
  column.Append( "TubeAttributeColPressure" );
  column.Append( "TubeAttributeColSize" );
  column.Append( "TubeAttributeColMaterial" );
  column.Append( "TubeAttributeColAuthorized" );

  if ( GetDescriptions( column, oTitles ) )
    returnCode = CATReturnSuccess;

  return returnCode;
}

//-----------------------------------------------------------------------------
HRESULT CAADVTubeAttributes::CheckTubeSize(const CATBaseUnknown* iObject,
                                           CATListPV** oViolation, 
                                           const unsigned int& iErrorFile)
{
  HRESULT returnCode = CATReturnFailure;

  //--------------------------------------------------------------------------
  // Declare variables here to avoid memory leaks from thrown errors
  //--------------------------------------------------------------------------
  // Variables that need release handling.
  CATISpecObject* piObjectSpec = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  CATIPspAttribute* piAttr = NULL;
  CATICkeParm *piPressureParm = NULL;
  CATICkeParm *piNominalSizeParm = NULL;
  CATICkeParm *piMaterialParm = NULL;
  CAAViolationTubeAttributes *pViolation = NULL;

  // Variables that do not need release handling.
  HRESULT rcInternal = CATReturnSuccess;
  CATUnicodeString uClassification;
  CATUnicodeString uValidationType;
  CATUnicodeString uNLSResource;
  CATUnicodeString uPartType;
  CATUnicodeString uPartName;
  double pressure = 0.0;
  CATUnicodeString uPressure;
  CATUnicodeString uNominalSize;
  CATUnicodeString uMaterial;
  CATUnicodeString uAuthorizedSizes;

  CATTry
  {
    // Get classification
    GetClassification (uClassification);

    // Get validation type
    GetType (uValidationType);

    // Get resource for NLS.
    GetResource (uNLSResource);


    if (iObject && 
        !uClassification.IsNull() && 
        !uValidationType.IsNull() && 
        !uNLSResource.IsNull())
    {
      returnCode = S_FALSE; // Input OK, now most failure because test not applicable.

      // Get spec object.
      if (SUCCEEDED(((CATBaseUnknown*)iObject)->QueryInterface(IID_CATISpecObject,(void**)&piObjectSpec)) && 
          piObjectSpec)
      {
        uPartType = piObjectSpec->GetType ();
        uPartName = piObjectSpec->GetName ();

        // Test that object is a tube.
        if (piObjectSpec->IsSubTypeOf("CATTubStraightTube") || 
            piObjectSpec->IsSubTypeOf("CATTubBendableTube"))
        {
          if (SUCCEEDED(rcInternal = GetLogicalLine(piObjectSpec, piLogicalLine)))
          {
            // Get attributes needed for calculation.
            if (SUCCEEDED(rcInternal = GetObjectAttribute(piLogicalLine, "Operating pressure", piPressureParm)) && 
                SUCCEEDED(rcInternal = GetObjectAttribute(piObjectSpec, "Nominal size", piNominalSizeParm)) && 
                SUCCEEDED(rcInternal = GetObjectAttribute(piObjectSpec, "MaterialCategory", piMaterialParm)))
            {
              // Get test data.
              rcInternal = GetTestData(piPressureParm, 
                                       piNominalSizeParm, 
                                       piMaterialParm, 
                                       pressure, 
                                       uPressure, 
                                       uNominalSize, 
                                       uMaterial);
              if (SUCCEEDED(rcInternal))
              {
                // Test nominal size against rules.
                rcInternal = TestTubeSize(pressure, 
                                          uNominalSize, 
                                          uAuthorizedSizes);

                if (CATReturnSuccess == rcInternal)
                { // Have a violation
                  pViolation = new CAAViolationTubeAttributes (uValidationType, "TubeSize", uNLSResource);
                  if (pViolation)
                  {
                    // Set violation info.
                    pViolation->SetInfo(uPressure, 
                                        uNominalSize, 
                                        uMaterial, 
                                        uAuthorizedSizes);

                    // Add violation to output list.
                    AddViolation (oViolation, pViolation);
                  } // End if valid violation pointer.
                } // End if violation returned.
              } // End if succeeded getting test data.
            } // End if valid attributes.
          } // End if valid logical line.
        } // End if tube.
      } // End if valid spec object.
    } // End if valid input and supporting data.
  } // End CATTry

  CATCatch( CATError, pError )
  {    
    rcInternal = CATReturnError(pError);
  }
  CATEndTry;

  // Release memory
  /*
  #define DeleteBaseUnknown(CATBaseUnknownObject)  
if (CATBaseUnknownObject) 
{  
  CATBaseUnknownObject->Release(); 
  CATBaseUnknownObject = NULL; 
}
  */
/*
  CATEsuDeleteBaseUnknown(piObjectSpec);
  CATEsuDeleteBaseUnknown(piLogicalLine);
  CATEsuDeleteBaseUnknown(piAttr);
  CATEsuDeleteBaseUnknown(piPressureParm);
  CATEsuDeleteBaseUnknown(piNominalSizeParm);
  CATEsuDeleteBaseUnknown(piMaterialParm);
*/
  if(piObjectSpec)
  {
    piObjectSpec->Release();
    piObjectSpec=NULL;
  }
  if(piLogicalLine)
  {
    piLogicalLine->Release();
    piLogicalLine=NULL;
  }
  if(piAttr)
  {
    piAttr->Release();
    piAttr=NULL;
  }
  if(piPressureParm)
  {
    piPressureParm->Release();
    piPressureParm=NULL;
  }  
  if(piNominalSizeParm)
  {
    piNominalSizeParm->Release();
    piNominalSizeParm=NULL;
  }
  if(piMaterialParm)
  {
    piMaterialParm->Release();
    piMaterialParm=NULL;
  }  
  


  if (FAILED(rcInternal))
  {
    returnCode = rcInternal;
  }
  else if (oViolation && *oViolation)
  {
    returnCode = CATReturnSuccess;
  }

  return returnCode;
}

//-----------------------------------------------------------------------------
HRESULT CAADVTubeAttributes::CheckTubeMaterial(const CATBaseUnknown* iObject,
                                               CATListPV** oViolation, 
                                               const unsigned int& iErrorFile)
{
  HRESULT returnCode = CATReturnFailure;

  //--------------------------------------------------------------------------
  // Declare variables here to avoid memory leaks from thrown errors
  //--------------------------------------------------------------------------
  // Variables that need release handling.
  CATISpecObject* piObjectSpec = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  CATIPspAttribute* piAttr = NULL;
  CATICkeParm *piPressureParm = NULL;
  CATICkeParm *piNominalSizeParm = NULL;
  CATICkeParm *piMaterialParm = NULL;
  CAAViolationTubeAttributes *pViolation = NULL;

  // Variables that do not need release handling.
  HRESULT rcInternal = CATReturnSuccess;
  CATUnicodeString uClassification;
  CATUnicodeString uValidationType;
  CATUnicodeString uNLSResource;
  CATUnicodeString uPartType;
  CATUnicodeString uPartName;
  double pressure = 0.0;
  CATUnicodeString uPressure;
  CATUnicodeString uNominalSize;
  CATUnicodeString uMaterial;
  CATUnicodeString uAuthorizedMaterialForSize;

  CATTry
  {
    // Get classification
    GetClassification (uClassification);

    // Get validation type
    GetType (uValidationType);

    // Get resource for NLS.
    GetResource (uNLSResource);


    if (iObject && 
        !uClassification.IsNull() && 
        !uValidationType.IsNull() && 
        !uNLSResource.IsNull())
    {
      returnCode = S_FALSE; // Input OK, now most failure because test not applicable.

      // Get spec object.
      if (SUCCEEDED(((CATBaseUnknown*)iObject)->QueryInterface(IID_CATISpecObject,(void**)&piObjectSpec)) && 
          piObjectSpec)
      {
        uPartType = piObjectSpec->GetType ();
        uPartName = piObjectSpec->GetName ();

        // Test that object is a tube.
        if (piObjectSpec->IsSubTypeOf("CATTubStraightTube") || 
            piObjectSpec->IsSubTypeOf("CATTubBendableTube"))
        {
          if (SUCCEEDED(rcInternal = GetLogicalLine(piObjectSpec, piLogicalLine)))
          {
            // Get attributes needed for calculation.
            if (SUCCEEDED(rcInternal = GetObjectAttribute(piLogicalLine, "Operating pressure", piPressureParm)) && 
                SUCCEEDED(rcInternal = GetObjectAttribute(piObjectSpec, "Nominal size", piNominalSizeParm)) && 
                SUCCEEDED(rcInternal = GetObjectAttribute(piObjectSpec, "MaterialCategory", piMaterialParm)))
            {
              // Get test data.
              rcInternal = GetTestData(piPressureParm, 
                                       piNominalSizeParm, 
                                       piMaterialParm, 
                                       pressure, 
                                       uPressure, 
                                       uNominalSize, 
                                       uMaterial);
              if (SUCCEEDED(rcInternal))
              {
                // Test nominal size against rules.
                rcInternal = TestTubeMaterial(pressure, 
                                              uNominalSize, 
                                              uMaterial, 
                                              uAuthorizedMaterialForSize);

                if (CATReturnSuccess == rcInternal)
                { // Have a violation
                  pViolation = new CAAViolationTubeAttributes (uValidationType, "TubeMaterial", uNLSResource);
                  if (pViolation)
                  {
                    // Set violation info.
                    pViolation->SetInfo(uPressure, 
                                        uNominalSize, 
                                        uMaterial, 
                                        uAuthorizedMaterialForSize);

                    // Add violation to output list.
                    AddViolation (oViolation, pViolation);
                  } // End if valid violation pointer.
                } // End if violation returned.
              } // End if succeeded getting test data.
            } // End if valid attributes.
          } // End if valid logical line.
        } // End if tube.
      } // End if valid spec object.
    } // End if valid input and supporting data.
  } // End CATTry

  CATCatch( CATError, pError )
  {    
    rcInternal = CATReturnError(pError);
  }
  CATEndTry;

  // Release memory
/*
  CATEsuDeleteBaseUnknown(piObjectSpec);
  CATEsuDeleteBaseUnknown(piLogicalLine);
  CATEsuDeleteBaseUnknown(piAttr);
  CATEsuDeleteBaseUnknown(piPressureParm);
  CATEsuDeleteBaseUnknown(piNominalSizeParm);
  CATEsuDeleteBaseUnknown(piMaterialParm);
*/
  if(piObjectSpec)
  {
    piObjectSpec->Release();
    piObjectSpec=NULL;
  }
  if(piLogicalLine)
  {
    piLogicalLine->Release();
    piLogicalLine=NULL;
  }
  if(piAttr)
  {
    piAttr->Release();
    piAttr=NULL;
  }
  if(piPressureParm)
  {
    piPressureParm->Release();
    piPressureParm=NULL;
  }  
  if(piNominalSizeParm)
  {
    piNominalSizeParm->Release();
    piNominalSizeParm=NULL;
  }
  if(piMaterialParm)
  {
    piMaterialParm->Release();
    piMaterialParm=NULL;
  }

  if (FAILED(rcInternal))
  {
    returnCode = rcInternal;
  }
  else if (oViolation && *oViolation)
  {
    returnCode = CATReturnSuccess;
  }

  return returnCode;
}

//----------------------------------------------------------------------------- 
HRESULT CAADVTubeAttributes::GetLogicalLine(const IUnknown *ipiLogicalLineMember, 
                                            CATIPspLogicalLine *&opiLogicalLine)
{
  HRESULT returnCode = CATReturnFailure;
  opiLogicalLine = NULL;

  // Define memory pointers
  CATIPspGroupable *piMemberGroupable = NULL;
  CATIUnknownList *piListMemberGroups = NULL;
  IUnknown *piUnk = NULL;

  CATTry 
  {
    if (ipiLogicalLineMember && 
        SUCCEEDED(((IUnknown*)ipiLogicalLineMember)->QueryInterface (IID_CATIPspGroupable, (void **)&piMemberGroupable)) && 
        piMemberGroupable)
    {
      // Get logical lines
      if (SUCCEEDED(piMemberGroupable->ListGroups(NULL, &piListMemberGroups)) &&
          piListMemberGroups)
      {
        // Get groups
        unsigned int piListMemberLinesSize = 0;
        piListMemberGroups->Count(&piListMemberLinesSize);

        // Find group that is logical line.
        for (unsigned int iiGroup = 0; iiGroup < piListMemberLinesSize && !opiLogicalLine; iiGroup++)
        {
          //CATEsuDeleteBaseUnknown(piUnk);
            if(piUnk)
            {
              piUnk->Release();
              piUnk=NULL;
            }
          if (SUCCEEDED(piListMemberGroups->Item(iiGroup, &piUnk)) &&
              piUnk)
          {
            piUnk->QueryInterface(IID_CATIPspLogicalLine, (void **)&opiLogicalLine);
          } // End if valid logical line.
        } // End loop on groups.
      } // End if have logical lines
    } // End if valid member groupable
  } // End CATTry

  CATCatch (CATError, pError)
  {
    returnCode = CATReturnError(pError);
  }

  CATEndTry;

  // Release memory
/*
  CATEsuDeleteBaseUnknown(piMemberGroupable);
  CATEsuDeleteBaseUnknown(piUnk);
  CATEsuDeleteBaseUnknown(piListMemberGroups);
*/
  if(piMemberGroupable)
  {
    piMemberGroupable->Release();
    piMemberGroupable=NULL;
  }
  if(piUnk)
  {
    piUnk->Release();
    piUnk=NULL;
  }
  if(piListMemberGroups)
  {
    piListMemberGroups->Release();
    piListMemberGroups=NULL;
  }

  if (opiLogicalLine)
    returnCode = CATReturnSuccess;
  return returnCode;
}

//----------------------------------------------------------------------------- 
HRESULT CAADVTubeAttributes::GetObjectAttribute(const IUnknown *ipiObject, 
                                                CATUnicodeString iuAttributeName, 
                                                CATICkeParm *&opiAttributeParm)
{
  HRESULT returnCode = CATReturnFailure;
  opiAttributeParm = NULL;

  // Define memory pointers
  CATIPspAttribute *piObjectPspAttr = NULL;

  CATTry 
  {
    if (ipiObject && 
        SUCCEEDED(((IUnknown*)ipiObject)->QueryInterface (IID_CATIPspAttribute, (void **)&piObjectPspAttr)) && 
        piObjectPspAttr)
    {
      returnCode = piObjectPspAttr->GetLiteral(iuAttributeName, &opiAttributeParm);
    }
  } // End CATTry

  CATCatch (CATError, pError)
  {
    returnCode = CATReturnError(pError);
  }

  CATEndTry;

  // Release memory
  //CATEsuDeleteBaseUnknown(piObjectPspAttr);
  if(piObjectPspAttr)
  {
    piObjectPspAttr->Release();
    piObjectPspAttr=NULL;
  }
  if (opiAttributeParm)
    returnCode = CATReturnSuccess;
  return returnCode;
}

//----------------------------------------------------------------------------- 
HRESULT CAADVTubeAttributes::GetTestData(const CATICkeParm *ipiPressureParm, 
                                         const CATICkeParm *ipiNominalSizeParm, 
                                         const CATICkeParm *ipiMaterialParm, 
                                         double &oPressure, 
                                         CATUnicodeString &ouPressure, 
                                         CATUnicodeString &ouNominalSize, 
                                         CATUnicodeString &ouMaterial)
{
  HRESULT returnCode = CATReturnFailure;
  oPressure = 0.0;
  ouPressure = "";
  ouNominalSize = "";
  ouMaterial = "";

  // Define memory pointers

  CATICkeInst_var spPressureValue;

  CATTry 
  {
    if (ipiPressureParm && 
        ipiNominalSizeParm && 
        ipiMaterialParm)
    {
      spPressureValue = ipiPressureParm->Value();
      if (!!spPressureValue)
        oPressure = spPressureValue->AsReal(); // AsReal returns SI unit Pa (N/m2).
      ouPressure = ipiPressureParm->Show();
      ouNominalSize = ipiNominalSizeParm->Show();
      ouMaterial = ipiMaterialParm->Show();

      returnCode = CATReturnSuccess;
    }
  } // End CATTry

  CATCatch (CATError, pError)
  {
    returnCode = CATReturnError(pError);
  }

  CATEndTry;

  // Release memory

  return returnCode;
}

//----------------------------------------------------------------------------- 
HRESULT CAADVTubeAttributes::TestTubeSize(const double &iPressure, 
                                          const CATUnicodeString &iuNominalSize, 
                                          CATUnicodeString &ouAuthorizedSizes)
{
  HRESULT returnCode = S_FALSE;
  ouAuthorizedSizes = "";

  // Define memory pointers

  CATListValCATUnicodeString listAuthorizedSizes;

  CATTry 
  {
    // Set valid nominal sizes.
    if (0.0 <= iPressure && 100000.0 >= iPressure)
    {
      listAuthorizedSizes.Append("1/4in");
      listAuthorizedSizes.Append("5/16in");
      listAuthorizedSizes.Append("3/8in");
      listAuthorizedSizes.Append("1/2in");
    }
    else if (200000.0 >= iPressure)
    {
      listAuthorizedSizes.Append("1/2in");
      listAuthorizedSizes.Append("5/8in");
      listAuthorizedSizes.Append("3/4in");
      listAuthorizedSizes.Append("1in");
      listAuthorizedSizes.Append("1 1/4in");
    }
    else if (300000.0 >= iPressure)
    {
      listAuthorizedSizes.Append("1 1/4in");
      listAuthorizedSizes.Append("1 1/2in");
      listAuthorizedSizes.Append("2in");
    }

    // Test for violation.      
    if (!listAuthorizedSizes.Locate(iuNominalSize))
    { // Nominal size is not authorized.
      returnCode = CATReturnSuccess;
      for (int iiSize = 1; iiSize <= listAuthorizedSizes.Size(); iiSize++)
      {
        if (1== iiSize)
        {
          ouAuthorizedSizes = listAuthorizedSizes[iiSize];
        }
        else
        {
          ouAuthorizedSizes += ", " + listAuthorizedSizes[iiSize];
        }
      }
    }
  } // End CATTry

  CATCatch (CATError, pError)
  {
    returnCode = CATReturnError(pError);
  }

  CATEndTry;

  // Release memory

  return returnCode;
}

//----------------------------------------------------------------------------- 
HRESULT CAADVTubeAttributes::TestTubeMaterial(const double &iPressure, 
                                              const CATUnicodeString &iuNominalSize, 
                                              const CATUnicodeString &iuMaterial, 
                                              CATUnicodeString &ouAuthorizedMaterialForSize)
{
  HRESULT returnCode = S_FALSE;
  ouAuthorizedMaterialForSize = "";

  // Define memory pointers

  int nomSizeIndex = 0;
  int iiSize = 0;
  CATUnicodeString uCurrentSize;
  CATListValCATUnicodeString listAuthorizedMaterials;

  CATTry 
  {
    // Set valid materials for this size.
    if (iuNominalSize.Compare("1/4in") || 
        iuNominalSize.Compare("5/16in") || 
        iuNominalSize.Compare("3/8in") || 
        iuNominalSize.Compare("1/2in") || 
        iuNominalSize.Compare("5/8in"))
    {
      listAuthorizedMaterials.Append("Carbon steel");
      listAuthorizedMaterials.Append("Stainless steel");
    }
    else if (iuNominalSize.Compare("5/8in") || 
             iuNominalSize.Compare("3/4in") || 
             iuNominalSize.Compare("1in") || 
             iuNominalSize.Compare("1 1/4in"))
    {
      listAuthorizedMaterials.Append("Carbon steel");
      listAuthorizedMaterials.Append("Stainless steel");
      listAuthorizedMaterials.Append("Copper");
    }
    else if (iuNominalSize.Compare("1 1/2in") || 
             iuNominalSize.Compare("2in"))
    {
      listAuthorizedMaterials.Append("Copper");
      listAuthorizedMaterials.Append("Aluminum");
    }

    // Test for violation.      
    if (!listAuthorizedMaterials.Locate(iuMaterial))
    { // Material is not authorized
      returnCode = CATReturnSuccess;
      for (int iiSize = 1; iiSize <= listAuthorizedMaterials.Size(); iiSize++)
      {
        if (1== iiSize)
        {
          ouAuthorizedMaterialForSize = listAuthorizedMaterials[iiSize];
        }
        else
        {
          ouAuthorizedMaterialForSize += ", " + listAuthorizedMaterials[iiSize];
        }
      }
    }
  } // End CATTry

  CATCatch (CATError, pError)
  {
    returnCode = CATReturnError(pError);
  }

  CATEndTry;

  // Release memory

  return returnCode;
}
