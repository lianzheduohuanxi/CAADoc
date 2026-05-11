//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

#ifndef CAAOsmIllustrateExtensions_H
#define CAAOsmIllustrateExtensions_H

//Local Framework
#include "CAAOsmManageExtensions.h" 

//System Framework
#include "CATBaseUnknown.h"

/**
 * Service to illustrate working with feature extensions.
 * ipExtensionsCatalog1Name
 *     the name of the first catalog containing feature extensions.
 * ipExtensionsCatalog2Name
 *     the name of the second catalog containing feature extensions.
 * ipFeatureCatalogName
 *     the name of the catalog containing base feature StartUps.
 * ipDocumentStorageName
 *     the entire pathname and name of the new document created.
 */

ExportedByCAAOsmManageExtensions
int CAAOsmIllustrateExtensions(const char *ipExtensionsCatalog1Name,
    	              		   const char *ipExtensionsCatalog2Name,
			  			       const char *ipFeatureCatalogName,
						       const char *ipDocumentStorageName);

#endif
