#ifndef CAADumpJournal_h_
#define CAADumpJournal_h_

// COPYRIGHT DASSAULT SYSTEMES  2002

#include "CAATopDumpJournal.h"          // for windows nt
#include "CATTopOperator.h"

// Gloval function that displays the journal contents on the
// standard output

ExportedByCAATopDumpJournal int CAATopDumpJournal(CATCGMJournalList * iJournal);
                                                
#endif
