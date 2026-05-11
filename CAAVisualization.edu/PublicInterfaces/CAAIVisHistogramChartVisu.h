#ifndef CAAIVisHistogramChartVisu_H
#define CAAIVisHistogramChartVisu_H

// COPYRIGHT DASSAULT SYSTEMES 1999


//===========================================================================
// Abstract : 
// ----------
//     Interface which defines an histogram chart with graphic representation. 
//     
//===========================================================================

// Visualization FrameWork
#include "CATIVisu.h" // Needed to derive from CATIVisu

// Local framework
#include "CAAVisGeoModelInt.h"  // Needed to export the IID and the class

// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAAVisGeoModelInt IID IID_CAAIVisHistogramChartVisu;

class  ExportedByCAAVisGeoModelInt CAAIVisHistogramChartVisu : public CATIVisu
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;
  public: 
} ; 


#endif
