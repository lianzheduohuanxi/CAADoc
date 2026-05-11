/**
 * @fullreview DCN 04:06:21
 */
/**
 * @quickreview DCN 04:08:24
 * @quickreview DCN 04:09:02
 */
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAMaiMachiningProcessLog: implementation of the 
// CATIMfgMachiningProcessLog CAA interface for a type of User Defined Features
//
// ===================================================================
// DCN V5R14 16/06/04 Creation 
// ===================================================================
//
#include "CAAMaiMachiningProcessLog.h"


// ObjectSpecsModeler
#include "CATIAlias.h"
#include "CATISpecObject.h"

#include "CATLib.h"
#include "CATString.h"

#include <iostream.h>

CATImplementBOA (CATIMfgMachiningProcessLog, CAAMaiMachiningProcessLog);

CATImplementClass (CAAMaiMachiningProcessLog,DataExtension,CATIMfgMachiningProcessLog,ManufacturingActivity);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAMaiMachiningProcessLog::CAAMaiMachiningProcessLog()
{
  _Active = CATTrue;

  if (NULL_var != GetImpl() && GetImpl()->IsAKindOf("MachiningProcess"))
  {    
    CATUnicodeString Name = "?";
    CATUnicodeString Line;
    CATIAlias_var spAlias(GetImpl());
    if( NULL_var != spAlias)
    {
      Name = spAlias->GetAlias();
    }
    Line = " Instantiation information on "+Name+" maching process ";
    cout << Line.ConvertToChar() << endl;
  }
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAMaiMachiningProcessLog::~CAAMaiMachiningProcessLog()
{
  if (NULL_var != GetImpl() && GetImpl()->IsAKindOf("MachiningProcess"))
  {
    CATUnicodeString Line;
    CATUnicodeString Name = "?";
    CATIAlias_var spAlias(GetImpl());
    if( NULL_var != spAlias)
    {
      Name = spAlias->GetAlias();
    }
    Line = " End of instantiation information on "+Name+" maching process ";
    cout << Line.ConvertToChar() << endl;
  }
}


//-----------------------------------------------------------------------------
// Activate
//-----------------------------------------------------------------------------
HRESULT CAAMaiMachiningProcessLog::Activate(CATBoolean iActive)
{
  _Active = iActive;
  return S_OK;
}

//-----------------------------------------------------------------------------
// IsActive
//-----------------------------------------------------------------------------
HRESULT CAAMaiMachiningProcessLog::IsActive(CATBoolean& oActive)
{
  oActive = _Active;
  return S_OK;
}
//-----------------------------------------------------------------------------
// Trace
//-----------------------------------------------------------------------------
HRESULT CAAMaiMachiningProcessLog::Trace(int iContext, const CATListOfCATUnicodeString& iTraces)
{
  HRESULT retCode = S_OK;

  CATUnicodeString Name;
  CATIAlias_var spAlias(GetImpl());
	if( NULL_var != spAlias)
	{
    Name = spAlias->GetAlias();
	}

  CATUnicodeString Line;
  if (1 == iContext)
    Line = " Checking of operation availabality for "+Name;
  else if (2 == iContext)
    Line = " Tooling Query for "+Name;
  else if (3 == iContext)
    Line = " Formulas processing for "+Name;
  else 
    Line = " Informations on "+Name;

  cout << Line.ConvertToChar() << endl;
  int nbLines = iTraces.Size();
  
  for (int i=1; i<=nbLines; i++)
  {
    cout << iTraces[i].ConvertToChar() << endl;
  }
  if (1 == iContext)
    Line ="  End of checking of operation availabality for "+Name;
  else if (2 == iContext)
    Line ="  End of Tooling Query for "+Name;
  else if (3 == iContext)
    Line =" End of formulas processing for "+Name;
  else 
    Line =" End of informations on "+Name;

  cout << Line.ConvertToChar() << endl;
  cout << " "<< endl;

  return retCode;
}
