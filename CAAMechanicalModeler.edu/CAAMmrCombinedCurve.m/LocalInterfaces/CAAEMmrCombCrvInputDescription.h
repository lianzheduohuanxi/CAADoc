#ifndef CAAEMmrCombCrvInputDescription_H
#define CAAEMmrCombCrvInputDescription_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATIniInputDescriptionAdaptor.h" // needed to derive from

class CAAEMmrCombCrvInputDescription: public CATIniInputDescriptionAdaptor
{
    CATDeclareClass;
    
public:
     
    CAAEMmrCombCrvInputDescription ();
    virtual ~CAAEMmrCombCrvInputDescription ();
    
    virtual HRESULT GetListOfModifiedFeatures(CATListValCATBaseUnknown_var& oListOfModifiedFeatures );

    virtual HRESULT GetMainInput(CATBaseUnknown_var& oMainInput);

    virtual HRESULT GetFeatureType(CATIInputDescription::FeatureType& oFeature_type);

private:

    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombCrvInputDescription (CAAEMmrCombCrvInputDescription &);
    CAAEMmrCombCrvInputDescription& operator=(CAAEMmrCombCrvInputDescription&);
    
};

#endif
