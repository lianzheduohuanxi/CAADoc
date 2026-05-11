// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAStrDefineUserAttributes.
//
#ifndef CAAStrDefineUserAttributes_H
#define CAAStrDefineUserAttributes_H


#include "CATPspKweUserAttrAdapter.h"
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATIProduct.h"

class CAAStrDefineUserAttributes: public CATPspKweUserAttrAdapter
{
 public:

    CATDeclareClass;

    CAAStrDefineUserAttributes();
    virtual ~CAAStrDefineUserAttributes();

   /**
    * Defines a list of computed attributes for the input exposed type isTypeName.
    * @param isTypeName
    *   Exposed type
    * @param olAttrInfos
    *   List of CATAttributeInfos
    * @return
    *   An HRESULT value.
    *   <br><b>Legal values</b>:
    *   <dl>
    *     <dt>S_OK</dt>
    *     <dd>operation is successful</dd>
    *     <dt>E_FAIL</dt>
    *     <dd>operation failed</dd>
    *   </dl>
    */
    virtual HRESULT DefineKweUserAttr(const CATString &isTypeName, 
                                      CATListValCATAttributeInfos &olAttrInfos) ; 


  /**
    * Returns the computed value of the iKey attribute on specified iObject.   
    * @param ipiObject
    *   Input object.
    * @param iKey
    *   Computed attribute name.
    * @return
    *   An CATIValue value. @see CATIValue
    *
    */
    virtual  CATIValue* GetValue (CATIInstance*  ipiObject, 
                           const CATUnicodeString& iKey) ;

  private:
    // do not implement
    CAAStrDefineUserAttributes (CAAStrDefineUserAttributes &);
    CAAStrDefineUserAttributes& operator=(CATPspKweUserAttrAdapter&);

};

#endif


