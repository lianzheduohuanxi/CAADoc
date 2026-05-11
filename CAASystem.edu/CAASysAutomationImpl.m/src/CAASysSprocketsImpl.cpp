/**
 * @fullreview JDU DMO 02:07:05
 */
/**
 * @quickreview DMO 05:11:24 Migration CATLONG  
 */

// CAASystem.edu framework
#include "CAASysSprocketsImpl.h"
#include "CAAIASysSprocket.h"

// System framework
#include "CATAutoConversions.h"
#include "CATUnicodeString.h"
#include "CATBaseDispatch.h"
#include "IUnknown.h"
#include "CATCreateIEnumVARIANT.h"

// Declaration of the class as a CNext implementation class.
CATImplementClass(CAASysSprocketsImpl, Implementation, CATBaseUnknown, CATnull);

// Implement the CAAIASysSprockets interface.
#include "TIE_CAAIASysSprockets.h"
TIE_CAAIASysSprockets(CAASysSprocketsImpl);

CAASysSprocketsImpl::CAASysSprocketsImpl() {
}

CAASysSprocketsImpl::~CAASysSprocketsImpl() {
	// Clean-up the internal collection of sprockets.
	// Since the internal collection is a CATList, which does
	// not automatically manage AddRef/Release for the objects
	// it contains, we need to call Release on the elements
	// before emptying the list.
	for (int i = 1; i <= _sprockets.Size(); i++) {
		CAAIASysSprocket *sprocket = _sprockets[i];
		if (sprocket != NULL) {
			sprocket->Release();
			sprocket = NULL;
			_sprockets[i] = NULL;
		}
	}
	_sprockets.RemoveAll();
}

HRESULT __stdcall CAASysSprocketsImpl::CreateSprockets(
	CAAIASysSprockets*& oCAAIASysSprockets) {
	
	// Instantiate a new CAASysSprocketsImpl and get its
	// CAAIASysSprockets interface.
	CAASysSprocketsImpl* sprocketsImpl = new CAASysSprocketsImpl();
	HRESULT hr = sprocketsImpl->QueryInterface(IID_CAAIASysSprockets, (void**)&oCAAIASysSprockets);
	sprocketsImpl->Release();
	sprocketsImpl = NULL;
	return hr;
}

HRESULT __stdcall CAASysSprocketsImpl::get_Name(
	CATBSTR & oNameBSTR) {
	
	// Call ConvertToBSTR to convert a BSTR to a CATUnicodeString
	CATUnicodeString name = "Sprockets";
	name.ConvertToBSTR(&oNameBSTR);
	return S_OK;
}

HRESULT __stdcall CAASysSprocketsImpl::get__NewEnum(
	IUnknown *& oEnumerator) {
	
	oEnumerator = NULL;
	
	// Transform the CATList of CAAIASysSprocket into a C++ array of CAAIASysSprocket
	CAAIASysSprocket **sprocketArray = new CAAIASysSprocket*[_sprockets.Size()];
	_sprockets.FillArray(sprocketArray, _sprockets.Size());
	
	// To implement get__NewEnum, we create a new object which
	// implements IEnumVARIANT using the CATCreateIEnumVARIANT function.
	// The IEnumVARIANT object enumerates the objects passed
	// to it at construction time. The CATCreateIEnumVARIANT function
	// requires three parameters: the C++ array of objects, the array size
	// and the type (IID) of the objects
	HRESULT hr = CATCreateIEnumVARIANT((IUnknown**)sprocketArray, _sprockets.Size(), IID_CAAIASysSprocket, (IEnumVARIANT*&)oEnumerator);

	
	delete[] sprocketArray;
	sprocketArray = NULL;
	
	return hr;
}

HRESULT __stdcall CAASysSprocketsImpl::Item(
	const CATVariant & iIndex, 
	CAAIASysSprocket *& oSprocket) {
	
	HRESULT hr = E_FAIL;
	oSprocket = NULL;
	
	// To determine the kind of element contained in the CATVariant
	// use the V_VT macro.
	VARTYPE vt = V_VT(&iIndex);

	// Do not forget to strip the VT_BYREF flag.
	if (vt & VT_BYREF) {
		vt ^= VT_BYREF;
	}

	// Access the collection by positionnal index (short or long).
	if ((vt == VT_I2) || (vt == VT_I4)) {
		long index = 0;
		HRESULT hr2 = ConvertVariant(iIndex, index);
		if (SUCCEEDED(hr2) && (index > 0) && (index <= _sprockets.Size()) && (_sprockets[index] != NULL)) {
			oSprocket = _sprockets[index];
			_sprockets[index]->AddRef();
			hr = S_OK;
		}
		
		// Access the collection by name
	} else if (vt == VT_BSTR) { /* CATBSTR */
		CATUnicodeString index;
		HRESULT hr2 = ConvertVariant(iIndex, index);
		if (SUCCEEDED(hr2)) {
			
			// Iterate over the collection items.
			for (int i = 1; i <= _sprockets.Size(); i++) {
				CAAIASysSprocket *sprocket = _sprockets[i];
				if (sprocket != NULL) {
					CATBSTR sprocketName = NULL;
					hr2 = sprocket->get_Name(sprocketName);
					if (SUCCEEDED(hr2) && (sprocketName != NULL)) {
						CATUnicodeString usSprocketName;
						usSprocketName.BuildFromBSTR(sprocketName);
						
						// Cleanup
						CATFreeString(sprocketName);
						sprocketName = NULL;
						
						if (index == usSprocketName) {
							oSprocket = sprocket;
							oSprocket->AddRef();
							hr = S_OK;
							break;
						}
					}
				}
			}
		}
		
		// Access the collection by value
	} else if (vt == VT_DISPATCH) { /* CATBaseDispatch */
		CATBaseDispatch *value = NULL;
		HRESULT hr2 = ConvertVariant(iIndex, value);
		if (SUCCEEDED(hr2) && (value != NULL)) {
			IUnknown* valueUnk = NULL;
			hr2 = value->QueryInterface(IID_IUnknown, (void**)&valueUnk);
			if (SUCCEEDED(hr2) && (valueUnk != NULL)) {
				
				// Iterate over the collection items.
				for (int i = 1; i <= _sprockets.Size(); i++) {
					CAAIASysSprocket *sprocket = _sprockets[i];
					if (sprocket != NULL) {
						
						// Determine if the objects are the same by
						// comparing their IUnknown pointers
						IUnknown *sprocketUnk = NULL;
						hr2 = sprocket->QueryInterface(IID_IUnknown, (void**)&sprocketUnk);
						if (SUCCEEDED(hr2) && (sprocketUnk != NULL)) {
							
							if (sprocketUnk == valueUnk) {
								oSprocket = sprocket;
								oSprocket->AddRef();
								hr = S_OK;
							}
							sprocketUnk->Release();
							sprocketUnk = NULL;
							if (SUCCEEDED(hr)) {
								break;
							}
						}
					}
				}
				
				valueUnk->Release();
				valueUnk = NULL;
			}
			
			// Cleanup
			value->Release();
			value = NULL;
		}
	}
	return hr;
}

HRESULT __stdcall CAASysSprocketsImpl::get_Count(
	CATLONG & oCount) {
	
	oCount = _sprockets.Size();
	return S_OK;
}

HRESULT __stdcall CAASysSprocketsImpl::AddAll(
	const CATSafeArrayVariant & iSprocketArray) {
	
	HRESULT hr = E_FAIL;
	
	// Get the array size
	long arraySize = ConvertSafeArrayVariant(&iSprocketArray, (CATBaseDispatch**)NULL, 0);
	if (arraySize >= 0) {
		
		// Convert the VB Array to a C++ array
		CATBaseDispatch **sprocketArray = new CATBaseDispatch*[arraySize];
		if (arraySize == ConvertSafeArrayVariant(&iSprocketArray, sprocketArray, arraySize)) {
			// Put the Sprockets to add in a temporary list to
			// allow the method to succeed or fail atomically.
			CATListOfCAAIASysSprocket sprocketsToAdd;
			
			// Iterate over the array elements and add them to the internal list.
			for (int i = 0; i < arraySize; i++) {
				if (sprocketArray[i] != NULL) {
					CAAIASysSprocket *sprocket = NULL;
					HRESULT hr2 = sprocketArray[i]->QueryInterface(IID_CAAIASysSprocket, (void**)&sprocket);
					if (SUCCEEDED(hr2) && (sprocket != NULL)) {
						sprocketsToAdd.Append(sprocket);
					}
					sprocketArray[i]->Release();
					sprocketArray[i] = NULL;
				}
			}
			
			// If everything went right, add the temporary list to
			// the internal list
			if (sprocketsToAdd.Size() == arraySize) {
				_sprockets.Append(sprocketsToAdd);
				hr = S_OK;
			}
			
			delete[] sprocketArray;
			sprocketArray = NULL;
		}
	}
	return hr;
}

HRESULT __stdcall CAASysSprocketsImpl::ToArray(
	CATSafeArrayVariant & ioArray) {
	
	HRESULT hr = E_FAIL;
	// Make sure the supplied array has the right size.
	long arraySize = ConvertSafeArrayVariant(&ioArray, (CATBaseDispatch**)NULL, 0);
	if (arraySize == _sprockets.Size()) {
		// Convert the internal list to a C++ array.
		CAAIASysSprocket **sprocketArray = new CAAIASysSprocket*[arraySize];
		_sprockets.FillArray(sprocketArray, arraySize);
		
		// Copy the C++ array to a VB array
		hr = FillSafeArrayVariant(&ioArray, (const CATBaseDispatch**)sprocketArray, arraySize);
		delete[] sprocketArray;
		sprocketArray = NULL;
	}
	return hr;
}


