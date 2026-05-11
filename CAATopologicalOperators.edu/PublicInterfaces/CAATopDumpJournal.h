#include "CATIACGMLevel.h"
#ifdef CATIACGMR420CAA
#ifdef	__CAATopDumpJournal


//

// COPYRIGHT DASSAULT SYSTEMES 2000

//
#define ExportedByCAATopDumpJournal DSYExport
#else
#define ExportedByCAATopDumpJournal DSYImport
#endif
#include "DSYExport.h"
#else
#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAATopDumpJournal
#define	ExportedByCAATopDumpJournal	__declspec(dllexport)
#else
#define	ExportedByCAATopDumpJournal	__declspec(dllimport)
#endif
#else
#define	ExportedByCAATopDumpJournal
#endif
#endif
