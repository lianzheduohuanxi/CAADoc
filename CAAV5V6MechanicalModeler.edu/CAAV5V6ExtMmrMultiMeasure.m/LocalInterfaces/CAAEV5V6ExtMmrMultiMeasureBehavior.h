//===========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012
//=============================================================================
// CAAEV5V6ExtMmrMultiMeasureBehavior Class
// ----------------------------------
//
// This is the implementation of the CATIFmFeatureBehaviorCustomization interface for the 
// CAAMmrMultiMeasure feature
//
//=============================================================================
#ifndef CAAEV5V6ExtMmrMultiMeasureBehavior_H_
#define CAAEV5V6ExtMmrMultiMeasureBehavior_H_

#include "CATIFmFeatureBehaviorCustomization.h" // needed to derive from

class CATUnicodeString;
class CATBaseUnknown;
class CATListValCATBaseUnknown_var;

class CAAEV5V6ExtMmrMultiMeasureBehavior : public CATIFmFeatureBehaviorCustomization 
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors for an implementation class
  // -----------------------------------------------------------------
  CAAEV5V6ExtMmrMultiMeasureBehavior ();
  virtual ~CAAEV5V6ExtMmrMultiMeasureBehavior ();
 

  virtual HRESULT CanBeRemoved(CATBoolean & oDeletable) const;
  virtual HRESULT BeforeRemove();
  virtual HRESULT Build();
  virtual HRESULT CcpRegisterAdditionalObjectsForCopy(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const;
  virtual HRESULT CcpUpdate(const CATFmCCPContext & iContext);
  virtual HRESULT CcpUpdate(CATFmCCPContext & iContext);
  virtual HRESULT CcpPaste(const CATFmCCPContext & iContext);
  virtual HRESULT CcpPaste(CATFmCCPContext & iContext);
  virtual HRESULT CcpRegisterAdditionalObjectsForRemove(const CATListValCATBaseUnknown_var & iInitialSetOfObjects, CATListValCATBaseUnknown_var & oObjectToAddToBoundary) const;


private:

	// Copy constructor and equal operator, not implemented
    // Set as private to prevent the compiler from automatically creating them as public.
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrMultiMeasureBehavior (CAAEV5V6ExtMmrMultiMeasureBehavior &);
    CAAEV5V6ExtMmrMultiMeasureBehavior& operator=(CAAEV5V6ExtMmrMultiMeasureBehavior&);
		 
		void RaiseAnError(CATUnicodeString& ErrorLabel, CATBaseUnknown_var &iAssociatedFeature);
};

#endif
