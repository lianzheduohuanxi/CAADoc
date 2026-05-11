// Copyright Dassault Systemes 2002
//------------------------------------------------------------------------
//
// Two implement classes for CATIDelegateInstanciation and
// CATICreateInstance interfaces.
// 
// In the first implementation, the Instanciate() method gives the way to
// instanciate the user algorithm feature created in the CAAPeoAddTypeLibrary::Add()
// method and to return it as a CATIInstance (possible since the 
// algorithm adheres to the CATIInstance interface - see CAAPeoUserAlgoInstance).
// This method will be called by the Optimizer dialog as soon as you choose
// this algorithm in the algorithms list.
//
// The second implementation is a code extension of the previous class,
// in which we only implement the CreateInstance mechanism.
//
// In the current .dic we have added 2 rows :
// CAAPeoDelegateInstanciation		CATIDelegateInstanciation	LibCAAPeoCreateUserAlgorithm
// CAAPeoDelegateInstanciation		CATICreateInstance			LibCAAPeoCreateUserAlgorithm
//
//------------------------------------------------------------------------
#ifndef CAAPeoDelegateInstanciation_H
#define CAAPeoDelegateInstanciation_H

#include "CATBaseUnknown.h"

// forwards
class CATIInstance_var;
class CATInstanciationContext;
class CATUnicodeString;

class  CAAPeoDelegateInstanciation : public CATBaseUnknown
{
public:
	// Constructor
	CAAPeoDelegateInstanciation();
	virtual ~CAAPeoDelegateInstanciation();
	
	virtual HRESULT Instanciate(const CATIInstance_var& iOwner,
		const CATUnicodeString& iKey,
		const CATUnicodeString& typeName,
		CATIInstance_var& oInstanciated,
		const CATInstanciationContext *iContext);
	
	CATDeclareClass;
	
private:
	CAAPeoDelegateInstanciation (CAAPeoDelegateInstanciation &);
	CAAPeoDelegateInstanciation& operator=(CAAPeoDelegateInstanciation&);
};

//------------------------------------------------------------------------

class CAAPeoDelegateInstanciationExt : public CATBaseUnknown
{
public:
	CAAPeoDelegateInstanciationExt() {};
	virtual ~CAAPeoDelegateInstanciationExt() {};
	
	virtual HRESULT __stdcall CreateInstance (void **oPPV);
	
	CATDeclareClass;
	
private:
	CAAPeoDelegateInstanciationExt (CAAPeoDelegateInstanciationExt &);
	CAAPeoDelegateInstanciationExt& operator=(CAAPeoDelegateInstanciationExt&);
};
//------------------------------------------------------------------------

#endif
