// COPYRIGHT DASSAULT SYSTEMES  2000 +
//=============================================================================
//
// CAASchAppSample1
//
#ifndef CAASchAppSample1_H
#define CAASchAppSample1_H

#include "CAASchAppBaseEnv.h"
#include "CATISpecObject.h"
#include "CATISheet.h"
#include "CATString.h"

class CATDocument;
class CATIDrawing;
class CATISchBaseFactory;
class CATISchComponent;
class CATIUnknownList;
class IUnknown;
class CATISchAppObjectFactory2;

//-----------------------------------------------------------------------------

class CAASchAppSample1 : public CAASchAppBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAASchAppSample1 ();
    virtual ~CAASchAppSample1();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATDrawing
    //        containing 2D geometry, details ...
    //        iPathToOutputFile - path to save the file in 
    //-------------------------------------------------------------------------
    int DoSample(const char *iFileToBeLoaded, const char *iPathToOutputFile);

  private:

    void GetDraftingObjects();
    void InitEnvironment(const char *iFileToBeLoaded);

    CATDocument             *_pSchDoc;
    CATISchBaseFactory      *_piBaseFact;
    CATISchComponent        *_piSchComp;
    IUnknown                *_piUKAppRef;
    CATISpecObject          *_piSpecSchComp;
    CATIUnknownList         *_piLUK;
    IUnknown                *_piUK;
    CATISchAppObjectFactory2 *_piSchAppObjFact;

    CATISpecObject_var      _spDetailSpec;
    CATISheet_var           _spDetailSheet;
    CATIDrawing_var         _spDrawing;
};
#endif
