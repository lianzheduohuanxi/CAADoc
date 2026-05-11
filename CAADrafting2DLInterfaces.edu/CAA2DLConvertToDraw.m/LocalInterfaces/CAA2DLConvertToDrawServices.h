// COPYRIGHT DASSAULT SYSTEMES 2007
#ifndef CAA2DLConvertToDraw_H
#define CAA2DLConvertToDraw_H
//-----------------------------------------------------------------------------
// This class contains services used by batchConvertToDraw
//-----------------------------------------------------------------------------

class CATDocument;
class CATUnicodeString;
class CATI2DLayoutLayout;
class CATI2DLayoutSheet;
class CATIDftDrawing;
class CATIDftSheet;

#include "CATErrorDef.h"
#include "CATBooleanDef.h"
#include "CATSheetOrientation.h"

class CAA2DLConvertToDrawServices
{
public:

  // Gets the parent standard name and attributes managed by the sheet style.
  static HRESULT Get2DLStandardAndFormat(CATI2DLayoutLayout *pi2DLayout,
                                         CATUnicodeString &oStdName, 
                                         double &oFmtWidth,double &oFmtHeight,
                                         CATSheetOrientation &oSheetOrient,
                                         CATBoolean &oDisplayMode,
                                         int &oNum2DLActiveSheet);
  
  // Init Drawing Standard and extract the 2DLayout to the drawing
  static HRESULT InitDrawingDocument(CATDocument *piDocDraw, 
                                     CATUnicodeString &iStdName,
                                     double &iFmtWidth,double &iFmtHeight,
                                     CATSheetOrientation &iSheetOrient,
                                     CATBoolean &iDisplayMode,
                                     CATI2DLayoutLayout *ipi2DLayout);

  // Print the Sheet iNumSheet of the drawing with iFMtPrt format.
  static HRESULT PrintDrawingDocument(CATDocument *piDocDraw,
                                      CATUnicodeString ipathOutputName,
                                      CATUnicodeString iFmtPrt,
                                      int iNumSheet);
  // Get appropriate format name from a height and a width given
  static HRESULT GetAppropriateFormat(CATIDftDrawing*piDftDrawing,
                                      double &iFmtWidth, 
                                      double &iFmtHeight,
                                      CATUnicodeString &fmtName);
  // Get the Drawing Sheet from its number
  static HRESULT RetrieveDrawingSheetFromNumber(CATIDftDrawing *piDftDrawing,
                                                int &iSheetNumber,
                                                CATIDftSheet **opiDftSheet);
  // Get the number of the 2DL Sheet
  static HRESULT GetTheNumber2DLayoutSheet(CATI2DLayoutSheet *pi2DLSheet,int &oNum2DLSheet);
  // 
};
#endif

