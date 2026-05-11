/* -*-c++-*- */
// -------------------------------------------------------------------
// MCAD/SDS(c) Copyright Dassault Systemes 1998
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMBuildBasic.h
//---------------------------------------------------------------------
// 
//  Centralisation des methodes communes pour le Build
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 98/05/27 > PFS
// Ajout        : 00/03/17 > YLI : Versionning : gestion des configurations
//---------------------------------------------------------------------
#ifndef CAAGSMBuildBasic_h
#define CAAGSMBuildBasic_h

#include "CATBaseUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATErrorMacros.h"
#include "CAAGsiFeaturesSplModel.h" 

class CATCGMJournalList;
class CATISpecObject_var;
class CATBody_var;
class CATMfErrUpdate;
class CATSoftwareConfiguration;
class CATTopData;
class CATTopOpInError;

class  ExportedByCAAGsiFeaturesSplModel CAAGSMBuildBasic : public CATBaseUnknown
{
public:
	
	CAAGSMBuildBasic();
	virtual ~CAAGSMBuildBasic();
	
	//---------------------------------------------------------------------
	//   Centralization de l'active/inactive
	//---------------------------------------------------------------------
   // iphSpecToCopy is added. 
    int BuildGeneralizedInactiveResult(CATISpecObject_var *ihSpecToCopy = NULL);
	int BuildCopiedInactiveResult(const CATISpecObject_var& refspec);
	int BuildCopiedInactiveResult(const CATISpecObject_var& refSpec,const CATISpecObject_var& outSpec);
	int BuildDestroyedInactiveResult();
	
	
	//---------------------------------------------------------------------
	//  Topological Journal 
	//---------------------------------------------------------------------
	//creation  journal
	static CATCGMJournalList * CreateGSMProcReport(const CATISpecObject_var & Operateur,
		CATLISTV(CATBaseUnknown_var) & ListeSpecInOperateur,
		CATSoftwareConfiguration * Config = NULL);

	CATCGMJournalList * CreateGSMProcReport(CATLISTV(CATBaseUnknown_var) & ListeSpecInOperateur,
		CATSoftwareConfiguration * Config = NULL);
	
	//save  journal
	HRESULT StoreGSMProcReport(const CATISpecObject_var& Operateur,
		CATBody_var &Body, 
		CATLISTV(CATBaseUnknown_var) &ListeSpecInOperateur, 
		CATListOfCATUnicodeString &CopyOrNocopy); 

	HRESULT StoreGSMProcReport(CATBody_var &Body, 
		CATLISTV(CATBaseUnknown_var) &ListeSpecInOperateur, 
		CATListOfCATUnicodeString &CopyOrNocopy); 
	
	//Delete  journal
	HRESULT DeleteGSMProcReport(CATISpecObject_var & Operateur);
	HRESULT DeleteGSMProcReport();

	//creation  scope (Mode without report) 
	static HRESULT SetGSMScope(const CATISpecObject_var & Spec, const CATBody_var & Body);
	HRESULT SetGSMScope(const CATBody_var & Body);

	//---------------------------------------------------------------------
	// Tool type 
	//---------------------------------------------------------------------
	int GetFeatureToolType ( const CATISpecObject_var & spSpecObj );

	//---------------------------------------------------------------------
	//   Errors  / Throw 
	//---------------------------------------------------------------------
   static CATError * CAABuildActivateError         ();
 
};
#endif











