//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2015
//=============================================================================
//
// CAASchAppSample4
//
#ifndef CAASchAppSample4_H
#define CAASchAppSample4_H

#include "CATDocument.h"

class CATISchDocFrmXml;
class CATSession;

class CAASchAppSample4
{
public:

	CAASchAppSample4();
	virtual ~CAASchAppSample4();

	//------------------------------------------------------------------------------------------------------------------
	// Input: iFileToBeLoaded   - Absolute path of xml file containing 2D geometry details.
	//        iPathToOutputFile - Absolute path of directory, where the newly created schematic product should be saved.
	//------------------------------------------------------------------------------------------------------------------
	int DoSample(CATUnicodeString iFileToBeLoaded, CATUnicodeString iPathToOutputFile);

private:

	char                 *_pSessionIdent;
	CATSession           *_pSession;
	CATObject            *_pObj;
	CATISchDocFrmXml     *_piSchDoc;
};
#endif
