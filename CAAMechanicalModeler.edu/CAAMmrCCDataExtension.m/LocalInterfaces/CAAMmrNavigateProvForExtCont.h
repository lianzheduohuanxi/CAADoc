#ifndef CAAMmrNavigateProvForExtCont_H
#define CAAMmrNavigateProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrNavigateProvForExtCont: CATIUpdateProviderExtension
//  Extends CATINavigateObject Mechanism to FeatureExtensions Contained in MmrDataExtensionCont
//=================================================================================

#include "CATINavigateProvider.h"

class CAAMmrNavigateProvForExtCont: public CATINavigateProvider
{
    CATDeclareClass;

    CAAMmrNavigateProvForExtCont();
    virtual ~CAAMmrNavigateProvForExtCont();

public:

    /**
    * Returns a list of the children of a base object.
    * @param iObj
    *    The base feature object.
    *    <br><b>Legal values</b>: it must not be NULL.
    * @param ioListChildren
    *    The list of the children of the base object known by applicative code.
    *    <br><b>Legal values</b>: 
    *       ioProvidedChildren must not be NULL. *ioProvidedChildren may be NULL or a pointer to a valid CATLISTP(CATBaseUnknown).
    *    <br><b>Lifecycle rules deviation</b>
    *       When *ioProvidedChildren is not NULL, it has to be kept by callee as input argument. 
    */
    
  HRESULT GetChildren (CATBaseUnknown *  iObj  , CATListPtrCATBaseUnknown **  oListChildren ) ;

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAMmrNavigateProvForExtCont(CAAMmrNavigateProvForExtCont&);
    CAAMmrNavigateProvForExtCont& operator=(CAAMmrNavigateProvForExtCont&);
};
#endif
