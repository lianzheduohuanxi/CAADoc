/* -*-c++-*- */
// -------------------------------------------------------------------
// COPYRIGHT Dassault Systemes 2006
//---------------------------------------------------------------------
// Responsable: CAA Shape Design 
//---------------------------------------------------------------------
// CAAGSMIntegrationCmdServices.h
//---------------------------------------------------------------------
// 
//   Integration command services 
//   - Support Datum Mode
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 06/06/15 
//---------------------------------------------------------------------
#ifndef CAAGSMIntegrationCmdServices_H
#define CAAGSMIntegrationCmdServices_H

#include "CAAGsiFeaturesSplUI.h" 

#include "CATBaseUnknown.h"
class CATISpecObject_var;

class ExportedByCAAGsiFeaturesSplUI CAAGSMIntegrationCmdServices : public CATBaseUnknown
{
	CATDeclareClass;
  public :

    // Convert feature into Datum / Note: To be used in UpdateOkAction of a command in Creation mode 
	static HRESULT ValidateResult (const CATISpecObject_var& ispSpec);

  protected:

	CAAGSMIntegrationCmdServices ();
	virtual ~CAAGSMIntegrationCmdServices ();
  
  private:
	CAAGSMIntegrationCmdServices(CAAGSMIntegrationCmdServices &);
	CAAGSMIntegrationCmdServices& operator=(CAAGSMIntegrationCmdServices&);

};

#endif
