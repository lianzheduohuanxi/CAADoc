#ifndef CAAEGSMFeaturesSplReplace_H
#define CAAEGSMFeaturesSplReplace_H
// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// CAAEGSMFeaturesSplReplace.h
// Provide implementation to interface
//    CATIReplace
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//   IMPLEMENTATION
//   TIE: CATIReplace
//===================================================================

// ObjectSpecsModeler Framework 
#include "CATSpecReplaceExt.h"   // The adapter class for the Replace Capability  

class CATISpecObject_var;        // To handle features
class CATISpecAttrKey_var;
/**
 * Implement CATIReplace on CAASewskinBasic and CAACircleSweepTg LateType. 
 */
class CAAEGSMFeaturesSplReplace : public CATSpecReplaceExt
{
	CATDeclareClass;

public :

	CAAEGSMFeaturesSplReplace();
	virtual ~CAAEGSMFeaturesSplReplace();


	HRESULT IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
		const CATBaseUnknown_var& ispElement,
		CATUnicodeString& oMessage, 
		int& oElementValidity,
		const CATBaseUnknown_var& ispOldValue=NULL_var);

	HRESULT Replace(const CATUnicodeString& iNameOfRole,
		CATBaseUnknown_var& ispNewElement,
		const CATBaseUnknown_var& ispOldValue=NULL_var);


private:

	// Copy constructor, not implemented
	// Set as private to prevent from compiler automatic creation as public.
	CAAEGSMFeaturesSplReplace(const CAAEGSMFeaturesSplReplace &iObjectToCopy);

	// Assignment operator, not implemented
	// Set as private to prevent from compiler automatic creation as public.
	CAAEGSMFeaturesSplReplace & operator = (const CAAEGSMFeaturesSplReplace &iObjectToCopy);

	// On the fly featurization for selection objects
	CATISpecObject_var ExtractFeature(const CATBaseUnknown_var& ispSelectedObject);


	CATISpecObject_var InvertFeature(const CATBaseUnknown_var& ispSelectedObject,
		const CATISpecObject_var& ispCurrentSpec);


	// Refresh visu tool (OGS) 
	void AppendVisu(CATISpecObject_var spSpec ); 


};

#endif
