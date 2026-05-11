// COPYRIGHT DASSAULT SYSTEMES  2007
//=============================================================================
//  
//  Component Identifier: CAADVTubeAttributes.h
//  
//=============================================================================
//  
//  Description: 
//  CATIPspDesignValidation implementation
//
//=============================================================================
// Usage Notes:
//
//=============================================================================

#ifndef CAADVTubeAttributes_H
#define CAADVTubeAttributes_H

#include "CATEAPspDesignValidation.h"

class CATIPspLogicalLine;
class CATICkeParm;

/**
 * Validation check implementation class.
 * <b>Role</b>: Implements a sample design validation check.
 * @see CATIPspValidation.
 * @see CATIPspDesignValidation.
 * @see CATEAPspValidation.
 * @see CATEAPspDesignValidation.
 */

class CAADVTubeAttributes : public CATEAPspDesignValidation  
{
  CATDeclareClass;
  
public:
  
  CAADVTubeAttributes();
  ~CAADVTubeAttributes();

   /**
    * Implements a function from an interface.
    * @see CATIPspValidation#GetValidationChecks
    */
  HRESULT GetValidationChecks(CATListValCATUnicodeString& oChecks);

   /**
    * Implements a function from an interface.
    * @see CATIPspValidation#IsObjectAViolation
    */
  HRESULT IsObjectAViolation(const CATBaseUnknown* iObject,
								             const CATListValCATUnicodeString& iChecks,
								             CATListPV** oViolation,
								             const unsigned int& iErrorFile);

   /**
    * Override base class method.
    * @see CATEAPspValidation#GetClassification
    */
  HRESULT GetClassification(CATUnicodeString& oClassification);

   /**
    * Override base class method.
    * @see CATEAPspValidation#GetResource
    */
  HRESULT GetResource(CATUnicodeString& oName);

   /**
    * Override base class method.
    * @see CATEAPspValidation#GetColumnTitles
    */
  HRESULT GetColumnTitles(CATListValCATUnicodeString& oTitles);

  /**
  * Check the size of the tube object.
  *   @param iObject
  *     The object to be checked
  *   @param oViolation
  *     The check violation, CATPspCheckViolation, information.  
  *     Method assumes oViolation is NULL or points to a valid list.
  *     Found violations are added to any existing list.
  *     Delete array when done.
  *   @param iErrorFile
  *     The file descriptor to the opened error file.
  *   @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>iObject violated at least one check</dd>
  *     <dt>S_FALSE</dt>
  *     <dd>iObject did not violate any checks or not applicable for check</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>invalid input or error found such that check can not be performed</dd>
  *   </dl>
  */
  HRESULT CheckTubeSize(const CATBaseUnknown* iObject,
								        CATListPV** oViolation,
								        const unsigned int& iErrorFile);

  /**
  * Check the material of the tube object.
  *   @param iObject
  *     The object to be checked
  *   @param oViolation
  *     The check violation, CATPspCheckViolation, information.  
  *     Method assumes oViolation is NULL or points to a valid list.
  *     Found violations are added to any existing list.
  *     Delete array when done.
  *   @param iErrorFile
  *     The file descriptor to the opened error file.
  *   @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>iObject violated at least one check</dd>
  *     <dt>S_FALSE</dt>
  *     <dd>iObject did not violate any checks or not applicable for check</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>invalid input or error found such that check can not be performed</dd>
  *   </dl>
  */
  HRESULT CheckTubeMaterial(const CATBaseUnknown* iObject,
								            CATListPV** oViolation,
								            const unsigned int& iErrorFile);

  /**
  * Get the logical line (tubing line) that an object belongs to.
  *   @param ipiLogicalLineMember
  *     The object that is a member of a logical line.
  *   @param opiLogicalLine
  *     The the logical line.
  *   @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>logical line successfully retrieved</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>error retrieving logical line</dd>
  *   </dl>
  */
  HRESULT GetLogicalLine(const IUnknown *ipiLogicalLineMember, 
                         CATIPspLogicalLine *&opiLogicalLine);

  /**
  * Get an attribute parameter for an object.
  *   @param iObject
  *     The object.
  *   @param iuAttributeName
  *     The name of the attribute.
  *   @param opiAttributeParm
  *     The attribute parameter of the object.
  *   @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>parameter successfully retrieved</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>error retrieving parameter</dd>
  *   </dl>
  */
  HRESULT GetObjectAttribute(const IUnknown *ipiObject, 
                             CATUnicodeString iuAttributeName, 
                             CATICkeParm *&opiAttributeParm);

  /**
  * Get data used to test tube size and material.
  *   @param ipiPressureParm
  *     The operating pressure parameter for the object.
  *   @param ipiNominalSizeParm
  *     The nominal size parameter of the object.
  *   @param ipiMaterialParm
  *     The material parameter of the object.
  *   @param oPressure
  *     The operating pressure for the object.
  *   @param ouPressure
  *     The operating pressure for the object as a string in the current units.
  *   @param ouNominalSize
  *     The nominal size of the object.
  *   @param ouMaterial
  *     The material of the object.
  *   @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>data successfully retrieved</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>error retrieving data</dd>
  *   </dl>
  */
  HRESULT GetTestData(const CATICkeParm *ipiPressureParm, 
                      const CATICkeParm *ipiNominalSizeParm, 
                      const CATICkeParm *ipiMaterialParm, 
                      double &oPressure, 
                      CATUnicodeString &ouPressure, 
                      CATUnicodeString &ouNominalSize, 
                      CATUnicodeString &ouMaterial);
  /**
  * Test tube object size to see if it is authorized.
  *   @param iPressure
  *     The operating pressure for the object in Pa (N/m2).
  *   @param iuNominalSize
  *     The nominal size of the object.
  *   @param ouAuthorizedSizes
  *     A string with authorized sizes separated by commas.
  *     The string is only set if the material is unauthorized.
  *   @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>iObject violated at least one check</dd>
  *     <dt>S_FALSE</dt>
  *     <dd>iObject did not violate any checks or not applicable for check</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>invalid input or error found such that check can not be performed</dd>
  *   </dl>
  */
  HRESULT TestTubeSize(const double &iPressure, 
                       const CATUnicodeString &iuNominalSize, 
                       CATUnicodeString &ouAuthorizedSizes);
  /**
  * Test tube object size to see if it is authorized.
  *   @param iPressure
  *     The operating pressure for the object in Pa (N/m2).
  *   @param iuNominalSize
  *     The nominal size of the object.
  *   @param iuMaterial
  *     The material of the object.
  *   @param ouAuthorizedMaterialForSize
  *     A string with authorized materials (for the nominal size) separated by commas.
  *     The string is only set if the material is unauthorized.
  *   @return
  *   An HRESULT value.
  *   <br><b>Legal values</b>:
  *   <dl>
  *     <dt>S_OK</dt>
  *     <dd>iObject violated at least one check</dd>
  *     <dt>S_FALSE</dt>
  *     <dd>iObject did not violate any checks or not applicable for check</dd>
  *     <dt>E_FAIL</dt>
  *     <dd>invalid input or error found such that check can not be performed</dd>
  *   </dl>
  */
  HRESULT TestTubeMaterial(const double &iPressure, 
                           const CATUnicodeString &iuNominalSize, 
                           const CATUnicodeString &iuMaterial, 
                           CATUnicodeString &ouAuthorizedMaterialForSize);

private:

  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
  CAADVTubeAttributes (CAADVTubeAttributes &);
  CAADVTubeAttributes& operator=(CAADVTubeAttributes&);

};

#endif



