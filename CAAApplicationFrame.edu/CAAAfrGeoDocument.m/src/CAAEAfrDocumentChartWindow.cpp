// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework 
#include "CAAEAfrDocumentChartWindow.h"  // header of the class
#include "CAAAfrHistogramChartWindow.h"  // the window to create

// ApplicationFrame Framework 
#include "CATFrmLayout.h"       
#include "CATFrmEditor.h"  

// ObjectModelBase Framework
#include "CATIEditor.h" 

// C++ standrad library 
#include <iostream.h>  

// Dialog Framework
#include <CATMsgCatalog.h>  

// System framework
#include "CATErrorDef.h" // for the SUCCEEDED macro

//
//  _______________ Extension of a CAAGeometry Document  _______________
//
// To create TIE Objects
#include "TIE_CAAISysDocumentChartWindow.h"              
TIE_CAAISysDocumentChartWindow(CAAEAfrDocumentChartWindow); 

// To declare that the class is a data extension of (the late type) CAAGeom
//
CATImplementClass(CAAEAfrDocumentChartWindow, DataExtension, CATBaseUnknown,CAAGeom);

//  _______________ Dictionary to modify   _____________________________
// 
// To declare that CAAEAfrDocumentChartWindow implements  CAAISysDocumentChartWindow 
// insert the following line in the interface dictionary:
//
//    CAAGeom     CAAISysDocumentChartWindow  libCAAAfrGeoDocument
//

//-------------------------------------------------------------------------

CAAEAfrDocumentChartWindow::CAAEAfrDocumentChartWindow()
{
  cout << "Constructing CAAEAfrDocumentChartWindow"  << endl;
}

//-------------------------------------------------------------------------

CAAEAfrDocumentChartWindow::~CAAEAfrDocumentChartWindow()
{ 
  cout << "Destructing CAAEAfrDocumentChartWindow"  << endl; 
}

//-------------------------------------------------------------------------
HRESULT CAAEAfrDocumentChartWindow::CreateHistogramWindow()  
{
   cout << "CAAEAfrDocumentChartWindow::CreateHistogramWindow"  << endl;

   // CAAAfrHistogramWindow derives from CATFrmWindow
   // see the CAAAfrGeoWindows.m module

   // The window title
   //
   CATUnicodeString WindowName = CATMsgCatalog::BuildMessage("CAAAfrHistogramChartWindow",
                                        "BaseName",NULL,0,"Histogram Chart");
   
   CATString WindowBaseName = WindowName.ConvertToChar();

   // Retrieve the Document's editor
   CATIEditor * pIEditor = NULL ;
   HRESULT rc = QueryInterface(IID_CATIEditor, (void**)&pIEditor);
   if (SUCCEEDED(rc))
   {
      // The window is recognized by the document's editor
      CATFrmEditor * pEditor = pIEditor->GetEditor();
      CAAAfrHistogramChartWindow * pWindow = new CAAAfrHistogramChartWindow(WindowBaseName,pEditor);
      pWindow->Build();

      // In this use case BaseName = WindowName 
      // once WindowName is not the complete path of a document.
      //
      CATUnicodeString BaseName = pWindow->GetBaseName();
      pWindow->SetBaseName(BaseName);


      // To make it the current window 
      CATFrmLayout *currentLayout = CATFrmLayout::GetCurrentLayout();
      currentLayout->SetCurrentWindow(pWindow);

      pIEditor->Release();
      pIEditor = NULL ;
   }

   return rc ;
}









