#ifndef CAACheckJournal_h_
#define CAACheckJournal_h_

// COPYRIGHT DASSAULT SYSTEMES  2002

#include "CAATopCheckJournal.h"          // for windows nt
#include "CATTopOperator.h"

class CATGeoFactory;
class CATBody;
class CATTopData;
class CATMathPoint;

/**
 * Class describing the CAACheckJournal object 
 * To check a journal:
 *  - create a CAACheckJournal
 *  - add the input bodies by using the CAAAddInputBody
 *  - apply the CAACheck(0 method to the created CAACheckJournal
 */

// Specify whether an input body is to be added in Copy or No Copy mode
enum CAATopCheckJournalType {CAATopCheckNoCopy=32, CAATopCheckCopy=33};

class ExportedByCAATopCheckJournal CAACheckJournal 
{
public:
    
    // Destructor
    virtual ~CAACheckJournal();

    // Constructor
    CAACheckJournal (CATCGMJournalList * iReport,
        CATBody * iResult);

    // Add an input body to the CAACheckJournal object
    // is need prior to running CAACheck
    int CAAAddInputBody(CATBody * iInputBody, CAATopCheckJournalType copyNoCopy);

    // Test whether the journal is valid
    int CAACheck();

private :
    
    CATCGMJournalList     * _iReport;          // the journal to be tested
    CATBody               * _iResult;          // the result body
    CATLISTP(CATBody)       _InputsCopy;       // the list of bodies in copy mode
    CATLISTP(CATBody)       _InputsNoCopy;     // the list of bodies in no copy mode
  
};

#endif
