// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAVisBaseCGRDocument.h"

//Visualization Framework
#include "CAT3DBagRep.h"
#include "CATReadWriteCgr.h"

#include <string.h>
#include <stdlib.h>
#include <malloc.h>

//-------------------------------------------------------------------------------

CAAVisBaseCGRDocument::CAAVisBaseCGRDocument(const char *fileName,
                                             CATDialog *iDialogParent,
                                             const char *iDocumentName)
: CAAVisBaseDocument(iDialogParent, iDocumentName)
{
  //We're storing the file name:
  _pFileToOpen = (char *)malloc((strlen(fileName)+1)*sizeof(char));
  memset(_pFileToOpen, 0, strlen(fileName)+1);
  strcpy(_pFileToOpen, fileName);

  //Reading of the CGR:
  CreateModel();

  //Adding of the retrieved model to
  //the viewer:
  AddRepToViewer();
}

//-------------------------------------------------------------------------------

CAAVisBaseCGRDocument::~CAAVisBaseCGRDocument()
{
  free(_pFileToOpen);
  _pFileToOpen = NULL;
}

//-------------------------------------------------------------------------------

void CAAVisBaseCGRDocument::CreateModel()
{
  _pRootContainer = new CAT3DBagRep;
  //Reading of the CGR file. The rep issued from this reading
  //is added as a children of _pRootContainer.
  CAT3DBagRep * cgr = (CAT3DBagRep *)CATReadCgr((char *)_pFileToOpen,
                                                USE_LODS_TEXTURE_EDGE);
  if(NULL != cgr)
    {
      _pRootContainer->AddChild(*cgr);
    }
}

//-------------------------------------------------------------------------------
