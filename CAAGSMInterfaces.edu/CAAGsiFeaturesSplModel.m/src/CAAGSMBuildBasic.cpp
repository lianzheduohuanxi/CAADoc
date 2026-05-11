// COPYRIGHT Dassault Systemes 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAGSMBuildBasic
// Provide implementation to interface
//    CATIBuild
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// MINC 
#include "CATIGeometricalElement.h"

#include "CAAGSMBuildBasic.h" 

#include "CATIContainer.h"
#include "CATIPrtContainer.h"

//GeometricObjects
#include "CATCGMJournal.h"
#include "CATGeoFactory.h"
#include "CATCGMJournalList.h"

//NewTopologicalObjects
#include "CATBody.h"

//TopologicalOperators
#include "CATDynTransformation.h"
#include "CATTopData.h"

//Mathematics
#include "CATMathVector.h"
#include "CATSoftwareConfiguration.h"
#include "CATMathTransformation.h"
#include "CATCloneManager.h"



//ObjectSpecsModeler
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"

//MechanicalModeler
#include "CATIMechanicalProperties.h"
#include "CATIMfResultManagement.h"
#include "CATIMfProcReport.h"
#include "CATMfBRepDefs.h"
#include "CATMfErrUpdate.h"
#include "CATIMfBRep.h"

#include "CATInstantiateComponent.h" //System
#include "CATIMmiPartInfrastructurePreferencesAtt.h"  //MecModInterfaces


#include "CATIInputDescription.h"
#include "CATIUpdateError.h"
#include "CATIMmiNonOrderedGeometricalSet.h"
#include "CATIMmiOrderedGeometricalSet.h"
#include "CATIMechanicalTool.h"

// Application Frame 
#include "CATMsgCatalog.h"

//System
#include "CATError.h"
#include "CATUnicodeString.h"
#include "CATDataType.h"

//---------------------------------------------------------------------
// MACROS for Report 
//---------------------------------------------------------------------
#define CATGSMInitReportStart(taille)                                  \
   CATLISTV(CATBaseUnknown_var) ListeSpecInOperateur(taille);          \
   CATListOfCATUnicodeString    ListeSpecInOperateurKeys(taille);

#define CATGSMInitReportAdd(spectoadd,mode)                            \
   ListeSpecInOperateur.Append(spectoadd);                             \
   ListeSpecInOperateurKeys.Append(mode);

#define CATGSMInitReportEnd(Journal)                                   \
   Journal = CreateGSMProcReport(ListeSpecInOperateur);             

#define CATGSMInitReportEndWithSpec(Spec, Journal)                     \
   Journal = CreateGSMProcReport(Spec, ListeSpecInOperateur);       

#define CATGSMInitReportEndWithSpecConfig(Spec, Journal, Config)       \
   Journal = CreateGSMProcReport(Spec, ListeSpecInOperateur, Config);       

#define CATGSMListResetMemory                                          \
  ListeSpecInOperateur.RemoveAll();                                    \
  ListeSpecInOperateurKeys.RemoveAll();		                             \




//---------------------------------------------------------------------
// MACROS for Report save
//---------------------------------------------------------------------
#define CATGSMStoreReport(pDuplicatedBody)                                              \
     CATBody_var BodyTmp = pDuplicatedBody;                                           \
     StoreGSMProcReport(BodyTmp, ListeSpecInOperateur, ListeSpecInOperateurKeys); \

#define CATGSMStoreReportWithSpec(Spec, pDuplicatedBody)                                     \
     CATBody_var BodyTmp = pDuplicatedBody;                                                 \
     StoreGSMProcReport(Spec, BodyTmp, ListeSpecInOperateur, ListeSpecInOperateurKeys); \



//---------------------------------------------------------------------
//      Constructor/Destructor
//---------------------------------------------------------------------
CAAGSMBuildBasic::CAAGSMBuildBasic(): CATBaseUnknown()
{
}


CAAGSMBuildBasic::~CAAGSMBuildBasic()
{
}


//------------------------------------------------------------------------------------------------
//      Centralization active/inactive
//------------------------------------------------------------------------------------------------
int CAAGSMBuildBasic::BuildGeneralizedInactiveResult(CATISpecObject_var *iphSpecToCopy)
{
	int LocRc = 0;
	
	CATISpecObject_var ICurrentSpec(this);
	
	CATIMechanicalProperties_var ItfActivity(this);
	if (!!ItfActivity && ItfActivity -> IsInactive())
	{
		CATIInputDescription_var ItfDescr(this);
		if (!!ItfDescr)
		{
		
			CATIUpdateError_var ErrFeat(this);
			CATBaseUnknown_var oMainInput;
			CATISpecObject_var SpecMainInput;

			// GetMain Input 
			if(!iphSpecToCopy)	{
				ItfDescr -> GetMainInput(oMainInput);
				SpecMainInput = oMainInput;
			}
			else { 
				SpecMainInput = *iphSpecToCopy;
			}

			CATISpecObject_var SpecThis(this);
			CATIInputDescription::FeatureType iTypeOfFeature ;
			ItfDescr -> GetFeatureType(iTypeOfFeature);

			// In OGS/HybridBody context, 
			//  only modification features can copy their main input while being deactivated
			// In GS 
			//   OpenBody context is more tolerant
			if  ( ( GetFeatureToolType(SpecThis) != 1 ) &&  (!!SpecMainInput) && 			
				  ( iTypeOfFeature == CATIInputDescription::FeatureType_Modification || iphSpecToCopy)) {

					CATTry
					{
						LocRc = BuildCopiedInactiveResult(SpecMainInput);
					}
					CATCatch(CATError,error)
					{
						ItfActivity = NULL_var;
						ItfDescr = NULL_var;
						oMainInput = NULL_var;
						SpecMainInput = NULL_var;

						CATMfErrUpdate * err = new CATMfErrUpdate();
						err -> SetDiagnostic(error -> GetNLSMessage());
						error -> Release();
						ErrFeat -> SetUpdateError(err);
						ErrFeat = NULL_var;

						CATThrow(err);
					}
					CATEndTry;
				}		
			else { 
				LocRc =BuildDestroyedInactiveResult();

			}
		}
	}
	return LocRc;
}



//------------------------------------------------------------------------------------------------
// Case 1 : General : Case - Result remove 
//------------------------------------------------------------------------------------------------

// Dans le cas general, l'inactivation d'un feature revient
// a detruire la geometrie associe et le scope
//  => le feature ne pourra plus etre utilise en entree d'un autre
int CAAGSMBuildBasic::BuildDestroyedInactiveResult()
{
   int iExit=0;
   CATIMechanicalProperties_var activity(this);
   if (!!activity && activity->IsInactive())
	{
		iExit=1;
		// Delete Proc Report 
		// Sur le bon element
		 CATIMfProcReport_var ReportSpec(this);
		 if (!!ReportSpec) ReportSpec -> DeleteProcReport();
   
		// Or Delete report (Simple) 
		/*
		CATIGeometricalElement_var geom(this);
		if (!!geom)
		{
         geom -> DeleteScope();

         // GenericNaming demand (MDL): for connectors model events
         //  CATMfBRepServices::Completed(GetImpl(), MfCompletedOnly);
		}
		*/
		CATIMfResultManagement_var spMfResult ( this) ; 
		if (!! spMfResult) {
			spMfResult -> DeleteScopeResult() ; 
		}
   }
   return iExit;
}

//------------------------------------------------------------------------------------------------
//Case 2 : Modification feature  : Case - Result - MainInput duplication 
//------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------
// Dans le cas ou on appelle cette methode en revanche, un build de
// substitution peut etre effectue en donnant en premier argument
// l'entree privilegiee que l'on va recopier (translation nulle)

// First signature 
//---------------------------------------------------------------------
int CAAGSMBuildBasic::BuildCopiedInactiveResult(const CATISpecObject_var& refspec)
{
   int iExit = 0;
   CATISpecObject_var tempoSpec(this);
   iExit = BuildCopiedInactiveResult(refspec, tempoSpec);
   return iExit;
}

// Second signature 
//---------------------------------------------------------------------
int CAAGSMBuildBasic::BuildCopiedInactiveResult(const CATISpecObject_var& refSpec,const CATISpecObject_var& outSpec)
{
	int iExit = 0;
	CATIMechanicalProperties_var activity(this);
	if (!!activity && activity -> IsInactive())
	{
		//Le feature est inactif, on fait une translation de 0,0,0 de l'entree de reference
		iExit = 1;

		CATISpecObject_var ICurrentSpec(this);

		//Report : Follow Refspec=MainInput by default
		CATISpecObject_var SpecToFollow=refSpec;

		// Open Configuration 
		CATSoftwareConfiguration * Config=NULL;
		Config = new CATSoftwareConfiguration();

		
		// uses GetBodyResult to retrieve the first body
		CATIGeometricalElement_var spRefGeom = refSpec;
		CATBody_var spInputBody= spRefGeom->GetBodyResult();

		if (!spInputBody)
		{
			//Refspec body can be NULL for two reasons :
			//- Refspec is deactivated and destructive (inactivation chain...)
			//- Refspec has a NULL result : for example Volumic Add of an empty body (IR 440861)

			return BuildDestroyedInactiveResult();
		}
		else
		{
			// Recuperation de la geo factory du document en cours
			CATGeoFactory_var Fac ;
			CATIContainer_var Cont = ICurrentSpec->GetFeatContainer();
			CATIPrtContainer_var PrtCont(Cont);
			if (!!PrtCont)
			{
				CATIContainer_var GeoCont  = PrtCont -> GetGeometricContainer();
				Fac = GeoCont;
			}

#ifdef USE_CLONEMANAGER 

			CATCGMJournalList * pCGMJournal  = NULL;

			// Init of the Report  
			CATGSMInitReportStart               (1);
			CATGSMInitReportAdd                 (SpecToFollow,"NoCopy");
			CATGSMInitReportEndWithSpecConfig   (outSpec     ,pCGMJournal,Config);

			// Clone 
			CATBody * pDuplicatedBody = NULL; 
			CATCloneManager pCloneManager(Fac,CatCGMSingleDuplicate,Config);
			pCloneManager.Add(spInputBody);
			pCloneManager.Run();
			pDuplicatedBody = (CATBody *)pCloneManager.ReadImage(spInputBody);
			
			// Report 
			if (NULL!= pDuplicatedBody) { 
				// Sauvegarde de Report
				pCloneManager.WriteReport (pCGMJournal, CATCGMJournal::Modification,CATFalse);

				// Initialisation de Report
				CATGSMStoreReportWithSpec (outSpec,pDuplicatedBody);
			}
			else 
			{
				if (Config) { Config -> Release(); Config = NULL; }
				CATError * err = CAAGSMBuildBasic::CAABuildActivateError();
				CATThrow(err);
			}

			
#else 

			// Initialisation de Report
			CATCGMJournalList * Journal = NULL;
			CATGSMInitReportStart(1)
			CATGSMInitReportAdd(SpecToFollow,"NoCopy")
			CATGSMInitReportEndWithSpec(outSpec,Journal)

			ICurrentSpec = NULL_var;
			

			CATTopData TopData(Config, Journal);
			CATBody * pDuplicatedBody = NULL; 
			CATMathVector TranslationVector(0.0, 0.0, 0.0);
	

			// Creation du Translate avec un vecteur nul
			CATDynTransformation * Translate = CATCreateDynTransformation(Fac, &TopData, spInputBody);
			Fac = NULL_var;
			if (Translate)
			{

				Translate -> SetTranslation(TranslationVector);
				Translate -> SetReportMode(CATDynTransformation::CATDynModification);
				Translate -> SetJournalInfo(FALSE); //Pur modification (without info)

				Translate -> Run();
				pDuplicatedBody = Translate -> GetResult();
				delete Translate;
				Translate = NULL;

				// Verification du resultat
				if (NULL == pDuplicatedBody)
				{
					if (Config) { Config -> Release(); Config = NULL; }
					CATError * err = CAAGSMBuildBasic::CAABuildActivateError();
					CATThrow(err);
				}
				// Sauvegarde de Report
				CATGSMStoreReportWithSpec(outSpec,pDuplicatedBody)
			}
#endif 
		}
		if (Config) { Config -> Release(); Config = NULL; }
	}
	return iExit;
}



//---------------------------------------------------------------------
// Tests if a given feature is aggregated to a ShapeBody
//---------------------------------------------------------------------
int CAAGSMBuildBasic::GetFeatureToolType (const CATISpecObject_var & feature)
{
	int iExit=0;
	CATISpecObject_var curobject = feature;
	if (!!curobject)
	{
		int iTypeFound = 0 ; 
        CATISpecObject* father = curobject->GetFather();
		while(father)
		{
			CATIMmiNonOrderedGeometricalSet_var spNonOrderedGeomSet = father  ; 
			CATIMmiOrderedGeometricalSet_var    spOrderedGeomSet    = father ; 
			CATIMechanicalTool_var              spMechanicalSet     = father ; 
			if ( NULL_var != spNonOrderedGeomSet )  {
				iTypeFound = 1 ; 
			}
			else if ( NULL_var != spOrderedGeomSet ) {
				iTypeFound = 2 ; 
			}
			else if (NULL_var !=  spMechanicalSet  ) {
				iTypeFound = 3 ; 
			}
			if (iTypeFound > 0 ) break ; 
			else
			{
				curobject = father;
				father -> Release();
				father = curobject -> GetFather();
			}
		}
		if(father)
		{
			iExit = iTypeFound ; 	 
			father -> Release();
			father = NULL;
		}
	}
	return iExit;
}


//---------------------------------------------------------------------
//      Open a "Report Transaction"
// Must be optimized (old code of JDP)
// - destruction of the old scope in the StoreReport
// - Keep the CATIMfProcReport_var interface for StoreReport
// - error management
//---------------------------------------------------------------------
CATCGMJournalList* CAAGSMBuildBasic::CreateGSMProcReport(const CATISpecObject_var& ihSpecObject,
   CATLISTV(CATBaseUnknown_var)& listOfSpecsIN,
   CATSoftwareConfiguration* pSoftwareConfiguration )
{
	CATCGMJournalList * pJournalList = NULL; 

	// Create the list of keys.
	CATLONG32 numberOfSpecsIN = listOfSpecsIN.Size();
	CATListOfCATUnicodeString ListOfKeys(numberOfSpecsIN);

	for(CATLONG32 i=1 ; i<=numberOfSpecsIN ; i++) {
		ListOfKeys.Append(MfKeyNone);
	}

	CATIGeometricalElement_var  hGeometricalElement(ihSpecObject);
	if(NULL_var!=hGeometricalElement){

		hGeometricalElement->DeleteScope();
		// Creation du report
		CATIMfProcReport_var hMfProcReport(ihSpecObject);
		if(NULL_var!=hMfProcReport) { 

			if(NULL!=pSoftwareConfiguration){ 
				hMfProcReport->CreateProcReport(pSoftwareConfiguration, listOfSpecsIN, ListOfKeys);
			}
			else  {
				hMfProcReport->CreateProcReport(listOfSpecsIN, ListOfKeys);
			}
		}
		pJournalList= hMfProcReport->GetCGMJournalList(); 
	}
	return pJournalList ;
}

//---------------------------------------------------------------------
CATCGMJournalList * CAAGSMBuildBasic::CreateGSMProcReport(CATLISTV(CATBaseUnknown_var)& listOfSpecsIN,
   CATSoftwareConfiguration* pSoftwareConfiguration)
{
   CATISpecObject_var ihSpecObject(this);
   if(NULL_var==ihSpecObject) return NULL;

   return CreateGSMProcReport(ihSpecObject, listOfSpecsIN, pSoftwareConfiguration);
}
//---------------------------------------------------------------------
//      Close a "Report Transaction"
// Must be optimized (old code of JDP)
// - destruction of the old scope in the StoreReport
// - avoid the test of UnicodeString for the NoCopyMode
// - error management
//---------------------------------------------------------------------
HRESULT CAAGSMBuildBasic::StoreGSMProcReport(const CATISpecObject_var& ihSpecObject,
   CATBody_var& ihBody,
   CATLISTV(CATBaseUnknown_var)& listOfSpecsIN,
   CATListOfCATUnicodeString& listOfCopyOrNoCopyMode)  
 {
   CATLISTV(CATBaseUnknown_var) listOfSpecsInNoCopy;
   CATListOfCATUnicodeString listOfKeys;

   CATLONG32 numberOfSpecsIN=listOfSpecsIN.Size();

   if ( numberOfSpecsIN!=listOfCopyOrNoCopyMode.Size())
      return CATReturnFailure;

   for(CATLONG32 i=1; i<=numberOfSpecsIN; i++)
   {
      if((listOfCopyOrNoCopyMode[i])=="NoCopy")
      {
         listOfSpecsInNoCopy.Append (listOfSpecsIN[i]); 
         listOfKeys.Append ("None");
      }
   }

   CATIMfProcReport_var hMfProcReport(ihSpecObject);
   if(NULL_var!=hMfProcReport)  {
	   hMfProcReport->StoreProcReport(ihBody, listOfSpecsInNoCopy, listOfKeys);
	   return S_OK;
   }
   else { 
	   return CATReturnFailure;
   }
}
//---------------------------------------------------------------------
HRESULT CAAGSMBuildBasic::StoreGSMProcReport(CATBody_var& ihBody,
	                                          CATLISTV(CATBaseUnknown_var)& listOfSpecsIN, 
	                                          CATListOfCATUnicodeString& listOfCopyOrNoCopyMode)
{
   CATISpecObject_var ihSpecObject(this);
   if(NULL_var==ihSpecObject) return CATReturnFailure;

   return StoreGSMProcReport(ihSpecObject, ihBody, listOfSpecsIN, listOfCopyOrNoCopyMode);
}


//---------------------------------------------------------------------
//      Destruction journal
//---------------------------------------------------------------------
HRESULT CAAGSMBuildBasic::DeleteGSMProcReport(CATISpecObject_var & ihSpecObject)
{
   // Sur le bon element
   CATIMfProcReport_var ReportSpec(ihSpecObject);
   if (!!ReportSpec) ReportSpec -> DeleteProcReport();
   return S_OK;
}

//---------------------------------------------------------------------
HRESULT CAAGSMBuildBasic::DeleteGSMProcReport()
{
   CATISpecObject_var Spec(this);
   return DeleteGSMProcReport(Spec);
}


//---------------------------------------------------------------------
//      Creation Scope
//---------------------------------------------------------------------
HRESULT CAAGSMBuildBasic::SetGSMScope(const CATBody_var & Body)
{
	CATISpecObject_var SpecCourante(this);
	return SetGSMScope(SpecCourante, Body);
}

//---------------------------------------------------------------------
HRESULT CAAGSMBuildBasic::SetGSMScope(const CATISpecObject_var & Spec, const CATBody_var & Body)
{

	CATIMfResultManagement_var spMfResult(Spec ) ; 
	// 	CATIGeometricalElement_var geomelem(Spec);
	if (!!spMfResult)
		// 	if (!!geomelem)
	{
		spMfResult -> DeleteScopeResult ();
		// geomelem-> DeleteScope();
		if (!!Body)
		{
			//			CATLISTV(CATBaseUnknown_var) liste(1);
			//			liste.Append(Body);
			//			geomelem-> CreateScopeAndNodes(&liste);
			spMfResult -> CreateScopeResult (Body);
		}
	}
	return S_OK;
}


//---------------------------------------------------------------------
//   Error Management 
//---------------------------------------------------------------------
CATError * CAAGSMBuildBasic::CAABuildActivateError()  // ThrowIfNull
{
	CATError * err = new CATInternalError("CAADeActivateErrorMessage", "CAAGSMCircleSweepTgDlg");
	return err;
}
