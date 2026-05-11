//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

#ifndef CAAPstAddServices_H
#define CAAPstAddServices_H

//Local Framework
#include "CAAPstComponentServices.h" 

//ProductStructure Framework
#include "CATIProduct.h"               

//System Framework
#include "CATUnicodeString.h"

//ObjectModelerBase Framework
#include "CATDocument.h"

/**
 * Service to import an existing document.
 * This services illustrates the way to have same 
 * fonctionnalities as AddExternalComponent of CATIAProducts.
 * iThisProduct
 *        product where the document has to be imported.
 * iDocument
 *        document to import.
 * oNewProduct
 *        product instance of the imported document.
 */

ExportedByCAAPstComponentServices
HRESULT AddExternalComponent(CATIProduct* iThisProd, CATDocument *iDocument, CATIProduct** oNewProduct);

/**
 * Service to create and import a document.
 * This services illustrates the way to have same 
 * fonctionnalities as AddNewComponent of CATIAProducts.
 * iThisProduct
 *        product where the document has to be imported.
 * iDocumentType
 *        type of the document to create. Only part and product documents are allowed.
 * iPartNumber
 *        part number to give to the created document. Has to be single.
 * oNewProduct
 *        product instance of the imported document.
 */

ExportedByCAAPstComponentServices
HRESULT AddNewExternalComponent(CATIProduct* iThisProd, const CATUnicodeString iDocumentType,const CATUnicodeString iPartNumber, CATIProduct** oNewProduct);


#endif
