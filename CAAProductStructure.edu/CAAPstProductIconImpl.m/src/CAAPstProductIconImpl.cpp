#include "CAAPstProductIconImpl.h"

CATImplementClass(CAAPstProductIconImpl,
		  DataExtension,
		  CATBaseUnknown,
		  CAAPstProductIconExt);

#include "TIE_CATICustoIconProduct.h"
TIE_CATICustoIconProduct(CAAPstProductIconImpl); 



CAAPstProductIconImpl::CAAPstProductIconImpl()
{
}


CAAPstProductIconImpl::~CAAPstProductIconImpl()
{
}

/**
 * Returns the icon to be displayed for an external Product.
 *   @param oIcon
 *      The name of the icon that should be used for an external Product
 *   @return
 *      E_FAIL  internal error
 *	S_FALSE no icon provided, use the default
 *      S_OK	use the returned icon
 */
HRESULT CAAPstProductIconImpl::GetIconForProduct(CATUnicodeString& oIcon)
{
	oIcon = "I_CAAPstProductIcon";
	return S_OK;
}

/**
 * Returns the icon to be displayed for a component.
 *   @param oIcon
 *      The name of the icon that should be used for an internal component
 *   @return
 *      E_FAIL  internal error
 *	S_FALSE no icon provided, use the default
 *      S_OK	use the returned icon
 */
HRESULT CAAPstProductIconImpl::GetIconForComponent(CATUnicodeString& oIcon)
{
	oIcon = "I_CAAPstComponentIcon";
	return S_OK;
}

/**
 * Indicates whether or not the Document mask can be overlaid
 */
HRESULT CAAPstProductIconImpl::IsPossibleToAddDocMask()
{
	return S_OK;
}

/**
 * Indicates whether or not the Representation mask can be overlaid
 */
HRESULT CAAPstProductIconImpl::IsPossibleToAddRepMask()
{
	return S_OK;
}

/**
 * Indicates whether or not the Central mask can be overlaid
 */
HRESULT CAAPstProductIconImpl::IsPossibleToAddCentralMask()
{
	return S_OK;
}

/**
 * Indicates whether or not the Gear mask can be overlaid
 */
HRESULT CAAPstProductIconImpl::IsPossibleToAddGearsMask()
{
	return S_FALSE;
}

/**
 * Indicates whether or not the Contextual Design mask can be overlaid
 */
HRESULT CAAPstProductIconImpl::IsPossibleToAddContextDesignMask()
{
	return S_OK;
}

/**
 * Indicates whether or not the Flexible mask can be overlaid
 */
HRESULT CAAPstProductIconImpl::IsPossibleToAddFlexibleDesignMask()
{
	return S_OK;
}
