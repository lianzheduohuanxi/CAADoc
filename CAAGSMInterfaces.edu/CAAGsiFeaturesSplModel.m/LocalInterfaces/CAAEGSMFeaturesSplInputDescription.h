#ifndef CAAEGSMFeaturesSplInputDescription_H
#define CAAEGSMFeaturesSplInputDescription_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMFeaturesSplInputDescription.h
// Provide implementation to interface
//    CATIInputDescription
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CATIInputDescription
//===================================================================

// System Framework
#include "CATIniInputDescriptionAdaptor.h" // needed to derive from

class CATISpecObject_var; 

/**
 * Implement CATIInputDescription on CAASewskinBasic and CAACircleSweepTg LateType. 
 */
class CAAEGSMFeaturesSplInputDescription: public CATIniInputDescriptionAdaptor
{
    CATDeclareClass;
    
public:
     
    CAAEGSMFeaturesSplInputDescription ();
    virtual ~CAAEGSMFeaturesSplInputDescription ();
    
    HRESULT GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures );
    HRESULT GetMainInput(CATBaseUnknown_var& oMainInput);
    HRESULT GetFeatureType(CATIInputDescription::FeatureType& oFeature_type);

private:

    HRESULT GetInputDescription(CATIInputDescription::FeatureType& oFeature_type,
                                CATISpecObject_var & oMainInput,
                                CATListValCATBaseUnknown_var& oListOfModifiedFeatures,
                                int iNeedListOfModifiedFeatures=1);

    HRESULT ComputeDescription(CATIInputDescription::FeatureType& oFeature_type,
		 	                                  CATBaseUnknown_var& oMainInput,
			                                  CATListValCATBaseUnknown_var & oListOfModifiedFeatures);



    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEGSMFeaturesSplInputDescription (CAAEGSMFeaturesSplInputDescription &);
    CAAEGSMFeaturesSplInputDescription& operator=(CAAEGSMFeaturesSplInputDescription&);
    
};

#endif
