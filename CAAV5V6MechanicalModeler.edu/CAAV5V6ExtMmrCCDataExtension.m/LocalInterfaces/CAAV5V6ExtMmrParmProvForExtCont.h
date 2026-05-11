#ifndef CAAV5V6ExtMmrParmProvForExtCont_H
#define CAAV5V6ExtMmrParmProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAV5V6ExtMmrNavigateProvForExtCont: 
//  Implements CATIParmProvider interface.
//  Extends CATIParmPublisher Mechanism to Extension Features contained in the 
//    applicative container V5V6ExtMmrDataExtensionCont (type = CAAV5V6ExtMmrNavigateProvForExtCont)
//
//==================================================================================================

// ObjectModelerBase Framework in V5
// DataCommonProtocolUse Framework in V6
#include "CATIParmProvider.h"


class CAAV5V6ExtMmrParmProvForExtCont: public CATIParmProvider
{
    CATDeclareClass;

    CAAV5V6ExtMmrParmProvForExtCont();
    virtual ~CAAV5V6ExtMmrParmProvForExtCont();

public:

  /**
  * Returns the list of the parameters aggregated by a product's extension.   
  * @param intfName
  *        The interface name.
  * @param oList
  *        The list of the direct children of the given object.
  * @param iObj
  *        The extended object whose direct children are to be retrieved.
  */
  HRESULT GetDirectChildren(CATClassId intfName, CATListValCATBaseUnknown_var* oList,CATBaseUnknown* iObj);
   
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAV5V6ExtMmrParmProvForExtCont(CAAV5V6ExtMmrParmProvForExtCont&);
    CAAV5V6ExtMmrParmProvForExtCont& operator=(CAAV5V6ExtMmrParmProvForExtCont&);

};
#endif
