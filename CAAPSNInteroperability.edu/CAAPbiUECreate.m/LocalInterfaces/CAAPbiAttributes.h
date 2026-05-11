// COPYRIGHT Dassault Systemes 2003
//===================================================================
// A handy class to handle our output arguments
#ifndef CAAPbiAttributes_H
#define CAAPbiAttributes_H

#include "CATListOfCATUnicodeString.h"
#include "IUnknown.h"

class CAAPbiAttributes {

public:
	// construct with references to the output arguments
	// so that we don't have to pass them around
	CAAPbiAttributes(CATListOfCATUnicodeString& inames,
			 CATListOfCATUnicodeString& itypes,
			 void**& ivalues,
			 int& icount,
			 int imaxCount);
	// NOTE: no destructor needs be defined because it will destroy
	// the objects referenced...

	// allocate the values array
	HRESULT AllocateValues();
	// add another attribute
	void AddAttribute(const char *iAttrName,
			  const char *iAttrType,
			  const void *iAttrValue);

	void Dump();

private:
	CATListOfCATUnicodeString& _names;
	CATListOfCATUnicodeString& _types;
	void**& _values;
	int& _count;
	int _maxCount;
	
};

#endif
