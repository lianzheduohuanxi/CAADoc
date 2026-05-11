// COPYRIGHT DASSAULT SYSTEMES 2006
#ifndef CAAxPDMItemPreviewFrame_h
#define CAAxPDMItemPreviewFrame_h

#include "CATDlgFrame.h"
#include "CATIxPDMItem.h"

class CAT2DViewer;
class CAT2DImagePixelRep;
class CATPixelImage;

//========================================================================
//                   Frame contenant les preview
//========================================================================
class CAAxPDMItemPreviewFrame:public CATDlgFrame
{
   CATDeclareClass;
public :
   //Constructor - destructor
   CAAxPDMItemPreviewFrame(CATDialog *iParent,const CATString& name,CATDlgStyle style=NULL);
   virtual ~CAAxPDMItemPreviewFrame();
   
   void UpdatePixelIconViewer(CATIxPDMItem_var& iItem);
   void Clean();
   void SetImage(const CATPixelImage* image);

private :

   //variables internes
   CAT2DImagePixelRep          * _imageRep;
   CAT2DViewer                 * _PixelIconViewer;

};
#endif
