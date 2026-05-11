// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CAAGetFLEXEquivalentModulusExt.cpp
// Provide implementation to interface
//    CATIEhiFLEX
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// LRO 08:01:15
#include "CATUnicodeString.h"

#include "CAAGetFLEXEquivalentModulusExt.h"
#include "CATLISTV_CATBaseUnknown.h" 
#include "CATIElecAttrAccess.h"

// LiteralFeatures
#include "CATICkeParm.h"
//- ProductStructure
#include "CATIProduct.h"

CATImplementClass( CAAGetFLEXEquivalentModulusExt,
                   CodeExtension,
                   CATBaseUnknown,
                   ElecBranchableC );
 
//-----------------------------------------------------------------------------
// CAAGetFLEXEquivalentModulusExt : constructor
//-----------------------------------------------------------------------------
CAAGetFLEXEquivalentModulusExt::CAAGetFLEXEquivalentModulusExt():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAGetFLEXEquivalentModulusExt : destructor
//-----------------------------------------------------------------------------
CAAGetFLEXEquivalentModulusExt::~CAAGetFLEXEquivalentModulusExt()
{
}
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIEhiFLEX.h"
TIE_CATIEhiFLEX( CAAGetFLEXEquivalentModulusExt);
//==========================================================================
// GetFLEXEquivalentModulus
//==========================================================================
HRESULT CAAGetFLEXEquivalentModulusExt::GetFLEXEquivalentModulus (CATListValCATBaseUnknown_var *  ipListOfWireWireGroup , CATListValCATBaseUnknown_var *  ipOrderedListOfProtectionReference , CATListValCATBaseUnknown_var * ipInternalSpliceReferenceList, CATEhiProfileType iProfile , double  iProfileLength1 , double  iProfileLength2 , int  iBundleSegmentFlexibility , double & oYoungModulusEquivalent , double & oEquivalentRatioToBend , double & oEquivalentRatioToTwist)
{
  HRESULT HR=E_FAIL;
  int nbOfWiresWireGroups= ipListOfWireWireGroup ? ipListOfWireWireGroup->Size(): 0;
  int nbOfProtections= ipOrderedListOfProtectionReference ? ipOrderedListOfProtectionReference ->Size():0;
  int nbOfSplices=ipInternalSpliceReferenceList ? ipInternalSpliceReferenceList ->Size():0;
  if(iProfile == Circular)
  {
     oYoungModulusEquivalent=1.24*10e09;
     oEquivalentRatioToBend=0.001;
     oEquivalentRatioToTwist=10;
	 const CATUnicodeString ElecType("_Elec_Type");
	 CATUnicodeString ProtectionType;
     for(int i=1;i<=nbOfProtections ;i++)
     {
       CATIProduct_var hProtection =(*ipOrderedListOfProtectionReference )[i];
       CATIElecAttrAccess_var hElecAttrAccess(hProtection); 
       CATICkeParm_var hTypeCkeParm;
       HRESULT RC =E_FAIL;
	   if(!!hElecAttrAccess)
		   hElecAttrAccess->GetAttribute(ElecType, hTypeCkeParm);
       if (!!hTypeCkeParm)
         ProtectionType = hTypeCkeParm->Value()->AsString();
       if(ProtectionType=="ElecTape")
       {
         if(oEquivalentRatioToBend<1) oEquivalentRatioToBend=oEquivalentRatioToBend*3;
         oEquivalentRatioToTwist=oEquivalentRatioToTwist*2;
       }
       else
       {
         if(oEquivalentRatioToBend<=1/100 && oEquivalentRatioToTwist<=100)
         {
           oEquivalentRatioToBend=oEquivalentRatioToBend*100;
           oEquivalentRatioToTwist=oEquivalentRatioToTwist*10;
         }
         else
         {
           oEquivalentRatioToBend=1;
           oEquivalentRatioToTwist=100;
         }
       }
       
	 }
	 const CATUnicodeString ElecEquivThickness("Elec_Equivalent_Thickness");
	 double elecEquivThickness=0.;
	 for(int k=1;k<=nbOfSplices;k++)
	 {
		 CATIProduct_var hSplice =(*ipInternalSpliceReferenceList)[k];
		 CATIElecAttrAccess_var hElecAttrAccess(hSplice);
		 CATICkeParm_var hEquivThicknessCkeParm;
		 HRESULT RC = E_FAIL;
		 if(!!hElecAttrAccess)
			 hElecAttrAccess->GetAttribute(ElecEquivThickness, hEquivThicknessCkeParm);
		 if (!!hEquivThicknessCkeParm)
			 elecEquivThickness = elecEquivThickness+hEquivThicknessCkeParm->Value()->AsReal();
	 }
	 if(elecEquivThickness>0)
	 {
		 oEquivalentRatioToBend=oEquivalentRatioToBend*10;
	 }
     HR=S_OK;						  
  }
  else if(iProfile == Elliptical)
  {
	   if(iProfileLength1 < 10 && iProfileLength2>2)
     {
       oYoungModulusEquivalent=10e07;
       oEquivalentRatioToBend=1/100;
       oEquivalentRatioToTwist=10;
     }
     else
     {
       if(iBundleSegmentFlexibility<3)
       {
         oYoungModulusEquivalent=1.24*10e11;
         oEquivalentRatioToBend=1;
         oEquivalentRatioToTwist=100;
       }
       else
       {
         oYoungModulusEquivalent=10e8;
         oEquivalentRatioToBend=1/2;
         oEquivalentRatioToTwist=10;
       }
     }
     HR=S_OK;	
     
  }
  else if(iProfile == Rectangular)
  {
    oYoungModulusEquivalent=1.24*10e11;
    oEquivalentRatioToBend=1/10;
    oEquivalentRatioToTwist=10;
    if(nbOfWiresWireGroups<2)
    {
      oYoungModulusEquivalent=10e07;
    }
    else
    {
      oYoungModulusEquivalent=1.24*10e11;
    }
    HR=S_OK;
  }
  else
  {
     oYoungModulusEquivalent=1.24*10e12;
     oEquivalentRatioToBend=1;
     oEquivalentRatioToTwist=10;
     HR=S_OK;
  }
  return HR;
}


