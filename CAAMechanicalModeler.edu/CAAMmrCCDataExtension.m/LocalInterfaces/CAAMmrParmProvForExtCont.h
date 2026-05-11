#ifndef CAAMmrParmProvForExtCont_H
#define CAAMmrParmProvForExtCont_H

// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================
//  Abstract of the class:
//  ----------------------
//
//  CAAMmrParmProvForExtCont : CATIParmProvider Extension for MmrDataExtensionCont
//
//  Extends ParmPublisher to FeatureExtensions Contained in MmrDataExtensionCont
//==================================================================================


#include "CATIParmProvider.h"

class CAAMmrParmProvForExtCont: public CATIParmProvider
{
    CATDeclareClass;

    CAAMmrParmProvForExtCont();
    virtual ~CAAMmrParmProvForExtCont();

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
    CAAMmrParmProvForExtCont(CAAMmrParmProvForExtCont&);
    CAAMmrParmProvForExtCont& operator=(CAAMmrParmProvForExtCont&);

    HRESULT AddExtendedParmToPublish(CATBaseUnknown* iBaseFeature,CATClassId intfName,CATListValCATBaseUnknown_var* lst);
};
#endif
