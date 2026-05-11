#ifndef CAAViolationTubeAttributes_H
#define CAAViolationTubeAttributes_H

//===================================================================
// COPYRIGHT Dassault Systemes 2007
//===================================================================
//
// CAAViolationTubeAttributes.h
//
// A design violation object for tube attribute check.
//
//===================================================================
//
// Usage notes:
//
//===================================================================

//  CATPlantShipInterfaces
#include "CATPspCheckViolation.h"

//  System
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

/**
 * Tube attribute violation class.
 * <b>Role</b>: Store and report unauthorized tube attribute.
 */

class CAAViolationTubeAttributes : public CATPspCheckViolation
{
  public: 
      
   /**
    * Class constructor.
    * @see CATPspCheckViolation#CATPspCheckViolation
    */
    CAAViolationTubeAttributes(const CATUnicodeString& iType,
                               const CATUnicodeString& iCheck,
                               const CATUnicodeString& iResource );
    virtual ~CAAViolationTubeAttributes();  

    /**
    * Set information relevant to this violation.
    *   @param iuPressure
    *     The operating pressure for the model object on which the unauthorized attribute was found.
    *   @param iuNominalSize
    *     The nominal size of the model object on which the unauthorized attribute was found.
    *   @param iuMaterial
    *     The material of the model object on which the unauthorized attribute was .
    *   @param iuAuthorizedValues
    *     A string with authorized values separated by commas.
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
    void SetInfo(CATUnicodeString &iuPressure, 
	               CATUnicodeString &iuNominalSize, 
	               CATUnicodeString &iuMaterial, 
	               CATUnicodeString &iuAuthorizedValues);

   /**
    * Override base class method.
    * @see CATPspCheckViolation#GetCheckViolationData
    */
	HRESULT GetCheckViolationData(int& oRow, 
                                CATListValCATUnicodeString** oLValues );

  private:

    // do not implement
    CAAViolationTubeAttributes (CAAViolationTubeAttributes &);
    CAAViolationTubeAttributes& operator=(CAAViolationTubeAttributes&);

  /**
   * Violation pressure.
   *   The operating pressure for the model object on which the unauthorized attribute was found.
   */
	CATUnicodeString _uPressure;
  /**
   * Violation pressure.
   *   The nominal size for the model object on which the unauthorized attribute was found.
   */
	CATUnicodeString _uNominalSize;
  /**
   * Violation pressure.
   *   The material for the model object on which the unauthorized attribute was found.
   */
	CATUnicodeString _uMaterial;
  /**
   * Authorized values.
   *   Authorized values for the unauthorized attribute on the model object.
   */
	CATUnicodeString _uAuthorizedValues;
};

#endif
