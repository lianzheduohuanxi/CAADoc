//
// Copyright DASSAULT SYSTEMES 2004
//
// Implement CATICustoIconProduct interface
//
#ifndef CAAPstProductIconImpl_H
#define CAAPstProductIconImpl_H

#include "CATBaseUnknown.h"
#include "CATICustoIconProduct.h"

class CAAPstProductIconImpl: public CATBaseUnknown
{
	CATDeclareClass;

public:

	CAAPstProductIconImpl();
	virtual ~CAAPstProductIconImpl();

	/**
	 * Returns the icon to be displayed for an external Product.
	 *   @param oIcon
	 *      The name of the icon that should be used for an external Product
	 *   @return
	 *      E_FAIL  internal error
	 *	S_FALSE no icon provided, use the default
	 *      S_OK	use the returned icon
	 */
	HRESULT GetIconForProduct(CATUnicodeString& oIcon);

	/**
	 * Returns the icon to be displayed for a component.
	 *   @param oIcon
	 *      The name of the icon that should be used for an internal component
	 *   @return
	 *      E_FAIL  internal error
	 *	S_FALSE no icon provided, use the default
	 *      S_OK	use the returned icon
	 */
	HRESULT GetIconForComponent(CATUnicodeString& oIcon);

	/**
	 * Indicates whether or not the Document mask can be overlaid
	 */
	HRESULT IsPossibleToAddDocMask();

	/**
	 * Indicates whether or not the Representation mask can be overlaid
	 */
	HRESULT IsPossibleToAddRepMask();


	/**
	 * Indicates whether or not the Central mask can be overlaid
	 */
	HRESULT IsPossibleToAddCentralMask();

	/**
	 * Indicates whether or not the Gear mask can be overlaid
	 */
	HRESULT IsPossibleToAddGearsMask();

	/**
	 * Indicates whether or not the Contextual Design mask can be overlaid
	 */
	HRESULT IsPossibleToAddContextDesignMask();

	/**
	 * Indicates whether or not the Flexible mask can be overlaid
	 */
	HRESULT IsPossibleToAddFlexibleDesignMask();
	
private:
	// Copy constructors not to be implemented:
	CAAPstProductIconImpl(CAAPstProductIconImpl&);
	CAAPstProductIconImpl& operator=(CAAPstProductIconImpl*);
};

#endif
