// COPYRIGHT Dassault Systemes 2003
#include "CAAPbiAttributes.h"
#include "CATUnicodeString.h"
#include "iostream.h"

CAAPbiAttributes::CAAPbiAttributes(CATListOfCATUnicodeString& inames,
				   CATListOfCATUnicodeString& itypes,
				   void**& ivalues,
				   int& icount,
				   int imaxCount) :
	_names(inames),		// attribute names
	_types(itypes),		// attribute types
	_values(ivalues),	// attribute values
	_count(icount),		// current count
	_maxCount(imaxCount)	// maximum count
{
	// disable adding new attribute until AllocateValues is called
	_count = _maxCount;
}

//-----------------------------------------------------------------------------
// Allocate the values array
//-----------------------------------------------------------------------------
HRESULT CAAPbiAttributes::AllocateValues()
{
	if (NULL == _values) {
		_values = new void *[_maxCount];
		if (NULL == _values)
			return E_FAIL;
		else
			for (int i = 0; i < _maxCount; i++)
				_values[i] = NULL;
	}
	_count = 0;
	return S_OK;
}

//-----------------------------------------------------------------------------
// Add another attribute to the output arrays
//-----------------------------------------------------------------------------
void CAAPbiAttributes::AddAttribute(const char *iAttrName,
				    const char *iAttrType,
				    const void *iAttrValue)
{
	if (_count >= _maxCount)
		return;
	_names.Append(iAttrName);
	_types.Append(iAttrType);
	_values[_count] = (void*) iAttrValue;
	_count++;
}

//-----------------------------------------------------------------------------
// Add another attribute to the output arrays
//-----------------------------------------------------------------------------
void CAAPbiAttributes::Dump()
{
	cout << " CAAPbiAttributes::Dump" << endl<< flush;
	for (int i = 0; i < _count; i++)
	{
		CATUnicodeString name = _names[i+1];
		CATUnicodeString type = _types[i+1];
		char * value = (char *)_values[i];

		cout << "CATUEPDMCreate: name["<<  i  << "]=" << name.ConvertToChar() ;
		cout << " type=" << type.ConvertToChar() ;
		cout << " value=" << value << endl << flush;
	}

}
