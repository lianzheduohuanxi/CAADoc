// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspDefineUserAttributes.
//
#ifndef CAAPspDefineUserAttributes_H
#define CAAPspDefineUserAttributes_H


#include "CATPspKweUserAttrAdapter.h"
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATIProduct.h"

class CAAPspDefineUserAttributes: public CATPspKweUserAttrAdapter
{
 public:

    CATDeclareClass;

    CAAPspDefineUserAttributes();
    virtual ~CAAPspDefineUserAttributes();

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
    CATICkeParm_var GetUserStringValue(CATICkeParmFactory *iVolFactory,
                                        CATIProduct *iProd,
                                        const CATUnicodeString &iAttName,
                                        const CATUnicodeString &iAttNLSName);

    CATICkeParm_var GetPLMStringValue(CATICkeParmFactory *iVolFactory,
                                       CATIProduct *iProd,
                                       const CATUnicodeString &iAttName,
                                       const CATUnicodeString &iAttNLSName);



  private:
    // do not implement
    CAAPspDefineUserAttributes (CAAPspDefineUserAttributes &);
    CAAPspDefineUserAttributes& operator=(CATPspKweUserAttrAdapter&);

};

#endif


