#ifndef CAAEV5V6ExtMmrCombCrvInputDescription_H
#define CAAEV5V6ExtMmrCombCrvInputDescription_H

// COPYRIGHT DASSAULT SYSTEMES 2012

// System Framework
#include "CATIniInputDescriptionAdaptor.h" // needed to derive from

class CAAEV5V6ExtMmrCombCrvInputDescription: public CATIniInputDescriptionAdaptor
{
    CATDeclareClass;
    
public:
     
    CAAEV5V6ExtMmrCombCrvInputDescription ();
    virtual ~CAAEV5V6ExtMmrCombCrvInputDescription ();
    
    virtual HRESULT GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures );

    virtual HRESULT GetMainInput(CATBaseUnknown_var& oMainInput);

    virtual HRESULT GetFeatureType(CATIInputDescription::FeatureType& oFeature_type);

private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEV5V6ExtMmrCombCrvInputDescription (CAAEV5V6ExtMmrCombCrvInputDescription &);
    CAAEV5V6ExtMmrCombCrvInputDescription& operator=(CAAEV5V6ExtMmrCombCrvInputDescription&);
    
};

#endif
