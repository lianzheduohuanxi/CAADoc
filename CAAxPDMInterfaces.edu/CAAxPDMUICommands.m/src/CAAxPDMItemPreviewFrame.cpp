// COPYRIGHT DASSAULT SYSTEMES 2006
#include "CAAxPDMItemPreviewFrame.h"

//include System
#include "CATGetEnvValue.h"
//include Visualization
#include "CATRep.h"
#include "CAT2DViewer.h"
#include "CAT2DImagePixelRep.h"
#include "CATPixelImage.h"

CATImplementClass(CAAxPDMItemPreviewFrame,Implementation,CATDlgFrame,CATNull);

// --------------------------------------------------------------------------
//                              Constructor
// --------------------------------------------------------------------------
CAAxPDMItemPreviewFrame::CAAxPDMItemPreviewFrame(CATDialog *parent,const CATString& name,CATDlgStyle style):
 CATDlgFrame(parent,name,style),
 _imageRep(NULL)
{
   _PixelIconViewer = new CAT2DViewer(this,"PixelImageFrame",CATDlgFraNoFrame,130,110,NULL);
   _PixelIconViewer->SetGraduatedBackground(0);
   CATViewer* Viewer = (CATViewer*)_PixelIconViewer;
   Attach4Sides(Viewer);
}

// --------------------------------------------------------------------------
//                              Destructor
// --------------------------------------------------------------------------
CAAxPDMItemPreviewFrame::~CAAxPDMItemPreviewFrame()
{
   _PixelIconViewer=NULL;
   if (_imageRep) _imageRep->Destroy();
   _imageRep=NULL;
}

// --------------------------------------------------------------------------
//                          Clean
// --------------------------------------------------------------------------
void CAAxPDMItemPreviewFrame::Clean()
{
   if (_PixelIconViewer && _imageRep)
   {
      _PixelIconViewer->RemoveRep(_imageRep);
      _imageRep->Destroy();
      _imageRep = NULL;
   }
}

// --------------------------------------------------------------------------
//                          UpdatePixelIconViewer
// --------------------------------------------------------------------------
void CAAxPDMItemPreviewFrame::UpdatePixelIconViewer(CATIxPDMItem_var& iItem)
{
   Clean();
   if (!!iItem)
   {
      if (_PixelIconViewer)
      {
         CATUnicodeString oPreviewFileName,TmpDir,File;
         char *slash_tmp = NULL;
         if (CATGetEnvValue("CATTemp", &slash_tmp) == CATLibSuccess)
            oPreviewFileName = slash_tmp;
         if (slash_tmp) free(slash_tmp); slash_tmp=NULL;
#ifndef _WINDOWS_SOURCE
         oPreviewFileName.Append("\\");
#else
         oPreviewFileName.Append("/");
#endif
         oPreviewFileName.Append("CAAxPDMPreview.jpg");
	      if (SUCCEEDED(iItem->GeneratePreview("jpg",oPreviewFileName)))
         {
            CATString FileName(oPreviewFileName.ConvertToChar());
            CATPixelImage* image = CATPixelImage::CreateFromFile(FileName);
            if (image)
            {
               SetImage(image);
               image->Release();
               image=NULL;
            }
         }
      }
   }
   else
      _PixelIconViewer->Draw();//to remove previous picture
   return;
}

// --------------------------------------------------------------------------
void CAAxPDMItemPreviewFrame::SetImage(const CATPixelImage* image)
{
   if (image)
   {
      float point[2] = {0.,0.};
      if (_imageRep) _imageRep->Destroy();
      _imageRep = new CAT2DImagePixelRep(point,image,2);
      _PixelIconViewer->AddRep((CAT2DRep *)_imageRep);
      _PixelIconViewer->Draw();
      _PixelIconViewer->Reframe();
   }
   else
      _PixelIconViewer->Draw();//to remove previous picture

}
