//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// Header definition of CAATAdtThread
//===================================================================

#ifndef CAAAdtThread_H
#define CAAAdtThread_H

#include "CAAAdtThreadUtility.h"

class CATCylinder;
class CATBody;
class CATGeoFactory;
class CATTopData;

//-----------------------------------------------------------------------

/**
 * Threading operator.
 */
class ExportedByCAAAdtThreadUtility CAAAdtThread
{
   

  public:

  // Standard constructors and destructors
  // -------------------------------------
   CAAAdtThread ( CATGeoFactory *iGeoFactory, CATTopData *ioTopData, 
                     CATBody *iBody, CATCylinder *iCylinder, 
                     double iLength);
   virtual ~CAAAdtThread ();

   int Run();  // 
   CATBody *GetResult();


  private:
    CATBody *_bodyResult;
    CATGeoFactory *_factory;
    CATBody *_inputBody;
    CATCylinder *_inputCylinder;
    double _length;
    CATTopData *_topData;
};

//-----------------------------------------------------------------------

#endif
