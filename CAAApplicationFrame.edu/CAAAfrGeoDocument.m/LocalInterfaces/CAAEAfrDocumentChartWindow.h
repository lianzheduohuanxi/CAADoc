#ifndef CAAEAfrDocumentChartWindow_H
#define CAAEAfrDocumentChartWindow_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type (CAAGeometry) with its own workshop
//  and commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data Extension of the Late type CAAGeometry. This Late Type is seen 
//  In the file Box.
//
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, File/New In the Dialog Box the new document type  
//  appears.
//  
//===========================================================================
//  Inheritance:
//  ------------
//         CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CreateHistogramWindow
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

class CAAEAfrDocumentChartWindow: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrDocumentChartWindow();
    virtual ~CAAEAfrDocumentChartWindow();

    // CreateHistogramWindow
    // ----------------------
	//
    HRESULT  CreateHistogramWindow();


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrDocumentChartWindow(const CAAEAfrDocumentChartWindow &iObjectToCopy);
  
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrDocumentChartWindow & operator = (const CAAEAfrDocumentChartWindow &iObjectToCopy);
  
     
};
#endif
