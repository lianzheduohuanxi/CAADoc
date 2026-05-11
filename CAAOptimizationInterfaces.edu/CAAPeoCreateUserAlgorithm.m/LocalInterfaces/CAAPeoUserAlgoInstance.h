// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------------
//
// Implementation of the CATIInstance interface for the feature CAAPeoUserAlgo
// This class provide sercice to get the algorithm type from a CAAPeoUserAlgo instance.
// Notice that this class derives from CATCkeInstanceAdapter
// in order to return a generic type in case of the one
// corresponding in the types dictionnary is not found.
//
//
// In the current .dic we have added the following rows :
// CAAPeoUserAlgo	CATIInstance				LibCAAPeoCreateUserAlgorithm
// CAAPeoUserAlgo	CATIInstanceAttributes		LibCAAPeoCreateUserAlgorithm
//
//---------------------------------------------------------
#ifndef CAAPeoUserAlgoInstance_H
#define CAAPeoUserAlgoInstance_H

#include "CATKweInstanceAdapter.h"

class CATIType;

class CAAPeoUserAlgoInstance : public CATKweInstanceAdapter
{
public:
	CATDeclareKindOf;
	
	/**
	* This method returns the feature type.
	* Notice that an AddRef() is done.
	*/
	virtual CATIType* Type();
};

#endif
