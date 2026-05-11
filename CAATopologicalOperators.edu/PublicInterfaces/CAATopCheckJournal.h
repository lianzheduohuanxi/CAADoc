#include "CATIACGMLevel.h"
#ifdef CATIACGMR420CAA
#ifdef	__CAATopCheckJournal


//

// COPYRIGHT DASSAULT SYSTEMES 2000

//
#define ExportedByCAATopCheckJournal DSYExport
#else
#define ExportedByCAATopCheckJournal DSYImport
#endif
#include "DSYExport.h"
#else
#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAATopCheckJournal
#define	ExportedByCAATopCheckJournal	__declspec(dllexport)
#else
#define	ExportedByCAATopCheckJournal	__declspec(dllimport)
#endif
#else
#define	ExportedByCAATopCheckJournal
#endif
#endif
