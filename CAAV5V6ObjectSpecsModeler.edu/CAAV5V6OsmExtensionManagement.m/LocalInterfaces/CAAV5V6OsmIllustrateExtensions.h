//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

#ifndef CAAV5V6OsmIllustrateExtensions_H
#define CAAV5V6OsmIllustrateExtensions_H

//System Framework
#include "CATString.h"

/**
 * Service to illustrate working with feature extensions.

 */

//int CAAFmExtManageExtensions( CATString iEnvToUse,CATString iRepository);

int CAAV5V6OsmIllustrateExtensions(const char *pExtensionsCatalog1Name,
									const char *pExtensionsCatalog2Name,
									const char *pFeatureCatalogName,
									const char *pDocumentStorageName);
			      
			       

#endif
