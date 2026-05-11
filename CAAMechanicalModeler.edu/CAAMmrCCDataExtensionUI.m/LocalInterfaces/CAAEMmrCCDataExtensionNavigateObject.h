#ifndef CAAEMmrCCDataExtensionNavigateObject_H
#define CAAEMmrCCDataExtensionNavigateObject_H

//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2007
//=======================================================================
//
// Class  CAAEMmrCCDataExtensionNavigateObject:
// Implementation CATINavigateObject pour les MmrCCDataExtensions
//
//========================================================================

#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

#include "CATINavigateObject.h"

class CAAEMmrCCDataExtensionNavigateObject: public CATINavigateObject
{
public :
	CATDeclareClass;

	//-------------------------------------------------
	//____________Constructor/Destructor_______________
	//-------------------------------------------------
	CAAEMmrCCDataExtensionNavigateObject();
	virtual ~CAAEMmrCCDataExtensionNavigateObject();

	//-------------------------------------------------
	//_________Interfaces CATINavigateObject___________
	//-------------------------------------------------
	CATLISTV(CATBaseUnknown_var)* GetChildren ();
	CATListOfCATUnicodeString* GetIdentificators();

};
#endif
