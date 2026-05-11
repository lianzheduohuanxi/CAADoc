#ifndef CAAISysDocumentChartWindow_H
#define CAAISysDocumentChartWindow_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//==========================================================================
//
// Abstract of the class: 
// -----------------------
// Interface which allows to create a chart window for document. 
//
//
//=============================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Local framework
#include "CAASysGeoModelInf.h"  // Needed to export the IID and the class

// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAASysGeoModelInf IID IID_CAAISysDocumentChartWindow;

class ExportedByCAASysGeoModelInf CAAISysDocumentChartWindow : public CATBaseUnknown
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

  // CreateHistogramWindow
  // ---------------------
  // Create a window which contains a new representation of the
  // Document. 
  //
  virtual HRESULT CreateHistogramWindow() = 0;

};

#endif 
