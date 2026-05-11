#ifndef CAAV5V6ExtMmrNavigateProvForExtCont_H
#define CAAV5V6ExtMmrNavigateProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAV5V6ExtMmrNavigateProvForExtCont: 
//  Implements CATINavigateProvider interface.
//  Extends CATINavigateObject mechanism to Extension Features contained in the 
//    applicative container MmrDataExtensionCont
//=================================================================================

// ObjectModelerBase Framework in V5
// DataCommonProtocolUse Framework in V6
#include "CATINavigateProvider.h"


class CAAV5V6ExtMmrNavigateProvForExtCont: public CATINavigateProvider
{
    CATDeclareClass;

    CAAV5V6ExtMmrNavigateProvForExtCont();
    virtual ~CAAV5V6ExtMmrNavigateProvForExtCont();

public:

    /**
    * Returns a list of the children of a base object.
    * @param iObj
    *    The base feature object.
    *    <br><b>Legal values</b>: it must not be NULL.
    * @param ioProvidedChildren
    *    The list of the children of the base object known by applicative code.
    *    <br><b>Legal values</b>: 
    *       ioProvidedChildren must not be NULL. *ioProvidedChildren may be NULL or a pointer to a valid CATLISTP(CATBaseUnknown).
    *    <br><b>Lifecycle rules deviation</b>
    *       When *ioProvidedChildren is not NULL, it has to be kept by callee as input argument. 
    */
    
  HRESULT GetChildren (CATBaseUnknown *  iObj, CATListPtrCATBaseUnknown **  ioProvidedChildren);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAV5V6ExtMmrNavigateProvForExtCont(CAAV5V6ExtMmrNavigateProvForExtCont&);
    CAAV5V6ExtMmrNavigateProvForExtCont& operator=(CAAV5V6ExtMmrNavigateProvForExtCont&);

};
#endif
