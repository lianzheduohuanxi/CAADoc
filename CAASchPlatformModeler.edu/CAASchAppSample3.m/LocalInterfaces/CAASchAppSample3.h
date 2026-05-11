// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//

#ifndef CAASchAppSample3_H
#define CAASchAppSample3_H

#include "CAASchAppBaseEnv.h"
#include "CATISpecObject.h"
#include "CATString.h"

class CATDocument;
class CATISchBaseFactory;
class CATISchGRRFactory;
class CATISchRoute;
class CATISchGRRRoute;
class CATIUnknownList;
class IUnknown;
class CATISchAppObjectFactory2;

//-----------------------------------------------------------------------------

class CAASchAppSample3 : public CAASchAppBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAASchAppSample3 ();
    virtual ~CAASchAppSample3();

    //-------------------------------------------------------------------------
    // Create schematic route
    // Input: iFileToBeLoaded - path of document name to be loaded (CATProduct
    //        containing 2D geometry, details ...
    //        iPathToOutputFile - path to save the file in 
    //-------------------------------------------------------------------------
    int DoSample (
      const char *iFileToBeLoaded, const char *iPathToOutputFile);

  private:

    void InitEnvironment(const char *iFileToBeLoaded);

    CATDocument             *_pSchDoc;
    CATISchBaseFactory      *_piBaseFact;
    CATISchGRRFactory       *_piGRRFact;
    CATIUnknownList         *_piLUK;
    IUnknown                *_piUK;
    CATISchRoute            *_piSchRoute1;
    CATISchRoute            *_piSchRoute2;
    IUnknown                *_piUKAppRoute1;
    IUnknown                *_piUKAppRoute2;
    CATISpecObject          *_piSpecSchRoute1;
    CATISpecObject          *_piSpecSchRoute2;
    CATISchGRRRoute         *_piSchGRRRoute1;
    CATISchGRRRoute         *_piSchGRRRoute2;
    CATISchAppObjectFactory2 *_piSchAppObjFact;

};
#endif
