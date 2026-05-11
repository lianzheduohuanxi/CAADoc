// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//
// CAASchAppSample2
//
#ifndef CAASchAppSample2_H
#define CAASchAppSample2_H

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

//-----------------------------------------------------------------------------

class CAASchAppSample2 : public CAASchAppBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAASchAppSample2 ();
    virtual ~CAASchAppSample2();

    //-------------------------------------------------------------------------
    // Input: iFileToBeLoaded - path of document name to be loaded (CATDrawing
    //        containing 2D geometry, details ...
    //        iPathToOutputFile - path to save the file in 
    //-------------------------------------------------------------------------
    int DoSample(const char *iFileToBeLoaded, const char *iPathToOutputFile);

  private:

    void GetAppReference ();
    void InitEnvironment(const char *iFileToBeLoaded);

    CATDocument         *_pSchDoc;
    CATISpecObject_var  _spAppRef;
};
#endif
