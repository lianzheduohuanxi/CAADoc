// COPYRIGHT DASSAULT SYSTEMES 2002
//-----------------------------------------------------------------------------------
//
// Two implementation classes :
// - one class to implement CATIAddTypeLibrary
// - one class to implement CATICreateInstance
// These implementations are mandatory to be able to see your own algorithm
// in the Optimizer dialog since they allow us to instanciate an algorithm
// by knowing only its type (the user can choose a type interactively in a
// combo box).
//
// In the CATIAddTypeLibary implementation, the Add() method :
// - creates the new package that will be used to stored the user algorithm types
// - adds the user algorithm types in the new package
// The Add() method will be called automatically as soon as CATIA starts (if you have
// chosen to load the package name CAAPeoPackage thanks to the Tools->Options)
// in order to add the user algorithm type in the types dictionnary (to display
// all the available algorithms, the Optimizer dialog will look for all
// the types deriving from the generic optimization algorithm in the types dictionnary).
// Here, we add only one type, but we could add several.
//
// The CATICreateInstance implementation is a code extension of the previous class,
// in which we only implement the CreateInstance mechanism.
//
// In the current .dic we have added 2 rows :
// CAAPeoAddTypeLibrary		CATIAddTypeLibrary		LibCAAPeoCreateUserAlgorithm
// CAAPeoAddTypeLibrary		CATICreateInstance		LibCAAPeoCreateUserAlgorithm
//
//------------------------------------------------------------------------------------

#ifndef CAAPeoAddTypeLibrary_H
#define CAAPeoAddTypeLibrary_H

#include "CAAPeoCreateUserAlgorithm.h"
#include "CATBaseUnknown.h"

//-----------------------------------------------------------

class ExportedByCAAPeoCreateUserAlgorithm CAAPeoAddTypeLibrary : public CATBaseUnknown
{
public:

	CAAPeoAddTypeLibrary() {};
	virtual ~CAAPeoAddTypeLibrary() {};
	
	virtual void Add();
	
	CATDeclareClass;
	
private:

	CAAPeoAddTypeLibrary (CAAPeoAddTypeLibrary &);
	CAAPeoAddTypeLibrary& operator=(CAAPeoAddTypeLibrary&);
};

//-----------------------------------------------------------

class CAAPeoAddTypeLibraryExt : public CATBaseUnknown
{
public:
	CAAPeoAddTypeLibraryExt() {};
	virtual ~CAAPeoAddTypeLibraryExt() {};
	
	virtual HRESULT __stdcall CreateInstance (void **oPPV);
	
	CATDeclareClass;
	
private:
	CAAPeoAddTypeLibraryExt (CAAPeoAddTypeLibraryExt &);
	CAAPeoAddTypeLibraryExt& operator=(CAAPeoAddTypeLibraryExt&);
};

//-----------------------------------------------------------

#endif
