// COPYRIGHT DASSAULT SYSTEMES 1996
// ===================================================================
//
// CAAMfgTPEUserCommandHeaders.h:
//   Used to give the list of headers of users' command of the tool path editor.
//   He also can activate ou deactivate these headers for a given set
//   of selected Objects.
// ===================================================================
//  Jan 2002 Creation: CRA
// ===================================================================
// History:
// -------------------------------------------------------------------
/// ===================================================================
#ifndef CAAMfgTPEUserCommandHeaders_h
#define CAAMfgTPEUserCommandHeaders_h

#include "CAAMfgTPEUserCommandHeadersEnv.h"

#include "CATBaseUnknown.h"
#include "CATBoolean.h"
#include "CATBooleanDef.h"
#include "CATListOfCATString.h"
class CATCSO;

class ExportedByCAAMfgTPEUserCommandHeadersEnv CAAMfgTPEUserCommandHeaders : public CATBaseUnknown
{
  CATDeclareClass;

public:
 
  CAAMfgTPEUserCommandHeaders();
  virtual ~CAAMfgTPEUserCommandHeaders();

	/**
	* <dl>
	* <dt><b>GetHeaders:</b>
	* <pre> 
	  *   Give the list of headers of command in the tool path editor.
	* </pre>
	* </dl>
	*/
	virtual HRESULT GetHeaders( CATListValCATString &ioHeadersList );

	/**
	* <dl>
	* <dt><b>IsHeaderAvailable:</b>
	* <pre> 
	 *   Say if the header of command is available for a given set of object. 
	* </pre>
	* </dl>
	*/
	virtual HRESULT IsHeadersAvailable( CATListValCATString& ioHeadersList , CATCSO* iCSO );

private :

	// The copy constructor and the equal operator must not be implemented
	// -------------------------------------------------------------------
	CAAMfgTPEUserCommandHeaders (CAAMfgTPEUserCommandHeaders &);
	CAAMfgTPEUserCommandHeaders& operator=(CAAMfgTPEUserCommandHeaders&);

	// ------------------
	// HeaderAvailability
	// ------------------
	void HeaderAvailability(const CATString& HeaderName, CATBoolean isON);

};

#endif

