// COPYRIGHT DASSAULT SYSTEMES  2002
#ifndef CAACciChapterBrowser_H
#define CAACciChapterBrowser_H

// System Framework
#include "IUnknown.h"
class CATICatalogChapter ;
class CATUnicodeString ;

HRESULT CAABrowsingChapter(CATICatalogChapter * pICatalogChapter,
                           const CATUnicodeString & iChapterType,
                           int iMoveText);
                           

#endif

