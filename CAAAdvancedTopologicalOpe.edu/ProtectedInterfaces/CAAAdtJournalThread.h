//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// Header definition of CAATAdtJournalThread
//===================================================================

#ifndef CAAAdtJournalThread_H
#define CAAAdtJournalThread_H

#include "CAAAdtJournalThreadUtility.h"

class CATCylinder;
class CATBody;
class CATGeoFactory;
class CATCGMJournalList;
class CATTopData;

//-----------------------------------------------------------------------

/**
 * Threading operator.
 */
class ExportedByCAAAdtJournalThreadUtility CAAAdtJournalThread
{
   

  public:

  // Standard constructors and destructors
  // -------------------------------------
   CAAAdtJournalThread ( CATGeoFactory *iGeoFactory, CATTopData *ioTopData, 
                     CATBody *iBody, CATCylinder *iCylinder, 
                     double iLength);
   virtual ~CAAAdtJournalThread ();

   int Run();  // 
   CATBody *GetResult();


  private:
    CATBody *_bodyResult;
    CATGeoFactory *_factory;
    CATBody *_inputBody;
    CATCylinder *_inputCylinder;
    double _length;
    CATCGMJournalList *_journal;
    CATTopData *_topData;
};

//-----------------------------------------------------------------------

#endif
