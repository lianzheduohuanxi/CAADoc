// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAVisManagerCGRDocument.h"

// Local FrameWork
#include "CAAVisModelCGRObject.h"
#include "CAAIVisModelCGRObject.h"

// System Franework
#include "CATErrorDef.h" // for SUCCEEDED macro

//-------------------------------------------------------------------------------

CAAVisManagerCGRDocument::CAAVisManagerCGRDocument ( const char *iFileName) : 
                          CAAVisManagerDocument("CAAVisManagerCGRDocument")
{
   if ( NULL != iFileName)
   {
      // Creation of the Root Object  
      CreateModel(iFileName);
   }
}

//-------------------------------------------------------------------------------

CAAVisManagerCGRDocument::~CAAVisManagerCGRDocument()
{
}

//-------------------------------------------------------------------------------

void CAAVisManagerCGRDocument::CreateModel(const char *iFileName)
{
   // we create a CGR object.
   _pRootContainer = new  CAAVisModelCGRObject();
   
   CAAIVisModelCGRObject *piVisOnCGR = NULL ;
   HRESULT rc0 = _pRootContainer->QueryInterface(IID_CAAIVisModelCGRObject,(void **)&piVisOnCGR);
   if ( SUCCEEDED(rc0) )
   {
      piVisOnCGR->ReadCGRFile(iFileName);
      piVisOnCGR->Release();
      piVisOnCGR = NULL ;
   }

}
//-------------------------------------------------------------------------------
