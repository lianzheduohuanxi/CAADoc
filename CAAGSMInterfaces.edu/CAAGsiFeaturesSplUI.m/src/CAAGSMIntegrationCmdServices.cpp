//---------------------------------------------------------------------
// COPYRIGHT Dassault Systemes 2006
//---------------------------------------------------------------------
// Responsable: CAA Shape Design 
//---------------------------------------------------------------------
// CAAGSMIntegrationCmdServices.cpp
//---------------------------------------------------------------------
// 
//   Convert Feature in Datum  and remove it 
//
//---------------------------------------------------------------------
// Historique:
//---------------------------------------------------------------------
#include "CAAGSMIntegrationCmdServices.h"

#include "CATIContainer.h"
#include "CATIDescendants.h"
#include "LifeCycleObject.h"

#include "CATInstantiateComponent.h"
#include "CATIMmiPartInfrastructurePreferencesAtt.h"

#include "CATIGSMFactory.h"
#include "CATIGSMProceduralView.h"
#include "CATISpecObject.h"          // To handle Feature 
#include "CATLISTV_CATISpecObject.h" // To handle List of Features


HRESULT ConvertToDatum(const CATISpecObject_var& spSpecToConvert); 

CATImplementClass(CAAGSMIntegrationCmdServices, Implementation, CATBaseUnknown,  CATNull );
//-----------------------------------------------------------------------------
// CAAGSMIntegrationCmdServices : constructor
//-----------------------------------------------------------------------------
CAAGSMIntegrationCmdServices::CAAGSMIntegrationCmdServices(): CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAGSMIntegrationCmdServices : destructor
//-----------------------------------------------------------------------------
CAAGSMIntegrationCmdServices::~CAAGSMIntegrationCmdServices()
{
}
//---------------------------------------------------------------------
// Datum Mode 
//---------------------------------------------------------------------
HRESULT  CAAGSMIntegrationCmdServices::ValidateResult(const CATISpecObject_var& ispCurrentFeature)
{

	HRESULT rc = S_OK ; 
	if(!!ispCurrentFeature)
	{

		//Mode Datum ?
		//-----------------
		CATIMmiPartInfrastructurePreferencesAtt *pIPreferencesController=NULL;
		rc = ::CATInstantiateComponent("CATMmuPartInfrastructurePreferencesCtrl", 
			IID_CATIMmiPartInfrastructurePreferencesAtt,(void**)&pIPreferencesController); 
		if(SUCCEEDED(rc )){

			CATIMmiPartInfrastructurePreferencesAtt::PreferenceMode TheMode ; 
			rc = pIPreferencesController->GetDatumMode(TheMode);

			//Creation de datum
			//-----------------
			if ( TheMode == CATIMmiPartInfrastructurePreferencesAtt::PermanentMode || 
				TheMode == CATIMmiPartInfrastructurePreferencesAtt::TemporaryMode) {
					rc = ConvertToDatum(ispCurrentFeature);

					//Temporary Mode - Datum has been created : Reset to NoMode  
					//-----------------------------------------------------------
					if (SUCCEEDED(rc) ){ 
						if (TheMode ==  CATIMmiPartInfrastructurePreferencesAtt::TemporaryMode) {
							// Send event to refresh Datum  mode in interatif   
							pIPreferencesController->ValidateDatumMode(TRUE);
						}
					}
				}
				pIPreferencesController->Release(); pIPreferencesController=NULL;
		}
	}
	return rc ; 
}

/*
***************************************************************************************
*
****************************************************************************************
*/
HRESULT  ConvertToDatum(const CATISpecObject_var& spSpecToConvert)
{
	HRESULT rc = E_FAIL; 
	CATIContainer_var spFeatCont = spSpecToConvert->GetFeatContainer() ;
	if (!! spFeatCont){ 
		CATIGSMFactory * pIGSMFactory = NULL ;   
		rc = spFeatCont->QueryInterface(IID_CATIGSMFactory,(void**)&pIGSMFactory);
		if ( SUCCEEDED(rc) ) {


		    CATListValCATISpecObject_var *ListDatum=NULL;

            int iVerif =1 ;
            rc= pIGSMFactory ->ConvertToDatum(spSpecToConvert, ListDatum,iVerif);
			if (SUCCEEDED(rc)){

				// --> Delete Specification 
				// --------------------------------------------------------
                CATISpecObject_var ispFather = spSpecToConvert->GetFather();
               

				if (!!ListDatum ) {

					int size =  ListDatum-> Size();
					// Specification  is aggretated in the prodecural view   
					if (NULL_var != ispFather) {
						ispFather->Release();
						CATIDescendants_var ispDes = ispFather;
						ispDes->RemoveChild (spSpecToConvert);
					}
					// Specification is not in the prodecural view   
					else {
						LifeCycleObject_var LCO = spSpecToConvert;
						LCO -> remove();
					}	

					// Datums management /  Insert in procedural view 
					int i;
					for(i=1;i<=size;i++) {
						CATIGSMProceduralView_var curobj =(*ListDatum)[i];
						if (NULL_var != curobj ) {
							rc = curobj->InsertInProceduralView();
						}
					}
					delete ListDatum;ListDatum=NULL;

				}
				else { 
					rc = E_FAIL; 
				}
			}
			pIGSMFactory-> Release();pIGSMFactory=NULL;
		}
	}
	return rc;
}
