//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//=============================================================================
// CAAEMaiUserReverseMachiningConditions.cpp
// Provides implementation to interface CATIMfgUserReverseMachiningConditions
//=============================================================================

#include "CAAEMaiUserReverseMachiningConditions.h"

#include "CATBaseUnknown.h"
#include "CATIMfgActivity.h"
#include "CATSettingRepository.h"
#include "CATListOfCATBaseUnknown.h"
#include "CATIMfgProfileContouringRelimitingElement.h"

//-----------------------------------------------------------------------------
// Supported Interface
//-----------------------------------------------------------------------------
#include "TIE_CATIMfgUserReverseMachiningConditions.h"
TIE_CATIMfgUserReverseMachiningConditions(CAAEMaiUserReverseMachiningConditions);
CATImplementClass(CAAEMaiUserReverseMachiningConditions,DataExtension,CATBaseUnknown,ProfileContouring);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEMaiUserReverseMachiningConditions::CAAEMaiUserReverseMachiningConditions() {}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEMaiUserReverseMachiningConditions::~CAAEMaiUserReverseMachiningConditions() {}

//-----------------------------------------------------------------------------
// ReverseMachiningConditions
//-----------------------------------------------------------------------------
HRESULT CAAEMaiUserReverseMachiningConditions::ReverseMachiningConditions()
{
	HRESULT RC = S_OK;
	{
		int SettingsOKForReverseCAAProfileContouring=0;
		CATSettingRepository* pOperation = CATSettingRepository::GetRepository("NCMfgOperation");
		if (NULL!=pOperation)
		{
			pOperation -> ReadSetting("ReverseMO_CAAProfileContouring",&SettingsOKForReverseCAAProfileContouring);
		}

		if (SettingsOKForReverseCAAProfileContouring==1)
		{
			CATIMfgActivity_var hActivity(GetImpl());
			if (NULL_var!=hActivity)
			{
				CATBaseUnknown_var hFeature = hActivity -> GetFeatureInContext();
				if (NULL_var!=hFeature)
				{
					CATIMfgProfileContouringRelimitingElement_var hPCRE(hFeature);
					if (NULL_var!=hPCRE)
					{
						// Swap start/end relimiting geometry
						CATUnicodeString StartPos,EndPos;
						double StartOffset=0.,EndOffset=0.;
						CATBaseUnknown_var hStartProduct,hEndProduct;
						CATLISTP(CATBaseUnknown) LOStartElt,LOEndElt;
						CATUnicodeString UStart("StartElement"),UEnd("EndElement");

						RC = hPCRE -> GetRelimitingGeometry(UStart,LOStartElt,hStartProduct,StartOffset,StartPos);
						if (FAILED(RC)) goto LABEL_END;
						RC = hPCRE -> GetRelimitingGeometry(UEnd  ,LOEndElt  ,hEndProduct  ,EndOffset  ,EndPos);
						if (FAILED(RC)) goto LABEL_END;

						RC = hPCRE -> SetRelimitingGeometry(UStart,LOEndElt  ,hEndProduct  ,EndOffset  ,EndPos);
						if (FAILED(RC)) goto LABEL_END;
						RC = hPCRE -> SetRelimitingGeometry(UEnd  ,LOStartElt,hStartProduct,StartOffset,StartPos);
						if (FAILED(RC)) goto LABEL_END;
					}
				}
			}
		}
	}
LABEL_END:
	return RC;
}
