#include "CATIACGMLevel.h"
#ifdef CATIACGMR420CAA
#ifdef	__CAAAmtForeignFct


// COPYRIGHT DASSAULT SYSTEMES  2000
#define ExportedByCAAAmtForeignFct DSYExport
#else
#define ExportedByCAAAmtForeignFct DSYImport
#endif
#include "DSYExport.h"
#else
#ifdef	_WINDOWS_SOURCE
// COPYRIGHT DASSAULT SYSTEMES  2000
#ifdef	__CAAAmtForeignFct
#define	ExportedByCAAAmtForeignFct	__declspec(dllexport)
#else
#define	ExportedByCAAAmtForeignFct	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAAmtForeignFct
#endif
#endif
