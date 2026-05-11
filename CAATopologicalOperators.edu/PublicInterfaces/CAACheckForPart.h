#ifndef CAACheckForPart_h_
#define CAACheckForPart_h_

// COPYRIGHT DASSAULT SYSTEMES  2002

#include "CAATopCheckForPart.h"          // for windows nt
#include "CATTopOperator.h"

class CATGeoFactory;
class CATBody;
class CATTopData;

/**
 * Class describing the object whereby you check whether
 * a topological journal is valid.
 */

// Specify whether an input body is to be added in Copy or No Copy mode
enum CAATopCheckForPartType {CAATopCheckNoCopy=32, CAATopCheckCopy=33};

class ExportedByCAATopCheckForPart CAACheckForPart 
{
public:
    
    // Destructor
    virtual ~CAACheckForPart();
    
/**
* Constructs a CAATopCheckForPart object.
* @param iReport
* The pointer to the journal to be checked.
* @param iResult
* The pointer to resulting body.
* @param iFeatureName
* The feature name: mainly to be used when checking a feature - otherwise, any string
* can be specified.
* @param iErrorVerdictOutput
* The name of the stream that contains the check global verdict.
* @param iErrorWarningOutput
* The name of the stream that contains the check details (possible errors
* and warnings).
* @param iVerdictVerbose
* Specifies whether the verdict file must be restricted to the global verdict (FALSE)
* or must provide a verdict for each rule to be checked (TRUE):
* <ul>
* <li>the correct backtracking of cells (mandatory)
* <li>the existence of non bording cells in the report
* <li>the existence of geometry in the report
* <li>the appropriate naming of cells.
* </ul> 
* @return
* The check verdict: O if the check is valid.  
*/
    CAACheckForPart (CATCGMJournalList * iReport,
        CATBody * iResult,
        const CATUnicodeString* iFeatureName,
        ostream*                iErrorVerdictOutput,
        ostream*                iErrorWarningOutput,
        CATBoolean verboseVerdict = TRUE);
    
    // Add an input body to the CAACheckForPart object
    // is needed prior to running CAACheck
    int CAAAddInputBody(CATBody * iInputBody, CAATopCheckForPartType copyNoCopy);
    
    // Test whether the journal is valid
    int CAACheck();

private :
    
    CATCGMJournalList     * _iReport;          // the journal to be tested
    CATBoolean _iVerdictVerbose;
    const CATUnicodeString*  _iFeatureName;    // the feature name
    ostream*  _iErrorWarningOutput;            // the warning file
    ostream*  _iErrorVerdictOutput;            // the verdict file
    CATBody               * _iResult;          // the result body
    CATLISTP(CATBody)       _InputsCopy;       // the list of bodies in copy mode
    CATLISTP(CATBody)       _InputsNoCopy;     // the list of bodies in no copy mode
  
};

#endif
