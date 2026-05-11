#ifndef CAACafTexturePropertyPageEdt_H
#define CAACafTexturePropertyPageEdt_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class representing an Edit Properties Page Editor, and implementing 
//  the CATIEditProperties interface.
//
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, click File/New, select CAAGeometry in the New dialog box.
//  Create some elements (point, line, circle, ellipse, plane,...)
//  Launch the Edit/Properties command and select any element: 
//     . The circle and the ellipse implement the Texture properties. 
//     . The line, the circle implement the Color properties.
//  
//===========================================================================
//  Inheritance:
//  ------------
// 
//       CATEditor          ( CATIAApplicationFrame Framework)
//          CATImplementationAdapter ( ObjectModelerBase Framework)
//              CATEventSubscriber      ( System Framework )
//                 CATBaseUnknown          (System Framework).
//                   
//
//===========================================================================
//
// Main Methods :  
// -------------- 
// 
// BuildEditor           -> Creates the property page  
// ExtractFromSelection  -> Extracts from the CSO involved object in this page.
// GetEditorTitle        -> NLS title
// SetEditorSize         -> 1 (small) ,2(medium), 3(large) 
// SetPropertyValue      -> Initializes the property page 
// CommitModification    -> After OK/Apply, modifies extracted object
// CancelModification    -> After Cancel push button
// CloseWindowFromEditor -> When you leave this page for another
//
//===========================================================================


// CATIAApplicationFrame framework
#include "CATEditor.h"                 // Needed to derive from CATEditor

// System framework
#include "CATLISTV_CATBaseUnknown.h"   // Needed by ExtractFromSelection,...

// Local Framework
class CAACafTexturePropertyPageDlg;       // Dialog Page

// CATIAApplicationFrame framework
class CATEditorPage;                   // Tabpage frame father


class  CAACafTexturePropertyPageEdt : public CATEditor
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;

   public:
 
   // The constructor is called only once during the application. 
   // 
   //   - as soon as the end user clicks on the Properties command, but only in
   //     these 2 cases:
   //       * In the CSO, any object has in its path an object which implements the 
   //         CATIRootProperties interface. 
   //       * In the CSO, at least one object has in its path an object which implements the 
   //         CATIRootProperties interface, and this implementation has this current Editor
   //         in its list. 
   // 
   //     ==>See CATCafRootProperties.m 
   //
   //   - when the end user clicks on the "More" push button of any 
   //     Edit/Properties Dialog Box. 
   //    
   // The destructor is called at the end of the application 
   // 
   CAACafTexturePropertyPageEdt();
   virtual ~CAACafTexturePropertyPageEdt(); 

   // ExtractFromSelection
   // --------------------
   // Extracts from the CSO the list of objects that have properties 
   // accessible in this page, that is, the objects that implement the 
   // CAAISysTextureProperties interface.
   //  
   // This method is called first:
   //   - as soon as the end user clicks on the Properties command, but only in
   //     these 2 cases:
   //       * In the CSO, any object has in its path an object which implements the 
   //         CATIRootProperties interface. 
   //       * In the CSO, at least one object has in its path an object which implements the 
   //         CATIRootProperties interface, and this implementation has this current Editor
   //         in its list. 
   //   - when the end user clicks on the "More" push button of any 
   //     Edit/Properties Dialog Box if the associated property page is not displayed.
   //    
   // If the extracted list is empty, no other method is called. 
   //
   virtual void ExtractFromSelection ( CATLISTV(CATBaseUnknown_var) & oExtract, 
                                const  CATLISTV(CATBaseUnknown_var) * iSelection =NULL );
   
   // GetEditorTitle 
   // ---------------
   // Returns the NLS title of the page.
   //
   // In the NLS file associated with the CAACafTexturePropertyPageDlg class 
   // you can customize it.
   // 
   // This method is called if the extraction is not empty. 
   // 
   virtual CATUnicodeString  GetEditorTitle();

   // SetEditorSize 
   // ---------------
   // Returns the size of the page. 
   //
   // This method is called if the extraction is not empty. 
   //
   // oSize can take the following values:
   //   1 : small size
   //   2 : medium size 
   //   3 : large size
   //
   // The Properties command analyzes the size returned by all Property pages and 
   // creates a box from the largest one. 
   //
   virtual void SetEditorSize(int & oSize );

   // BuildEditor
   // ------------
   // Creates the page Dialog (_pTextureFrame). 
   //
   // This method is called at the first selection of the page.
   //  
   // When the end user swaps between pages, this method is not called. 
   //
   // iEditor is the parent of _pTextureFrame. It kills _pTextureFrame when
   // the dialog box is closed.
   //
   virtual void BuildEditor(CATEditorPage * iEditor); 

   // SetPropertyValue 
   // -----------------
   // Sets the values and options in the Dialog object from elements 
   // of the extracted list. 
   //
   // This method is called after the BuildEditor method. 
   //
   virtual void SetPropertyValue ( CATLISTV(CATBaseUnknown_var)& iExtract, 
                                                   ModeReadWrite iMode);

   // CommitModification 
   // -------------------
   // Modifies the elements of the extracted list with the current values 
   // of the page.
   //
   // This method is called when the end user clicks Ok or Apply and if 
   // this page has been once displayed.
   // 
   virtual void CommitModification ( CATLISTV(CATBaseUnknown_var)& iExtract);

   // CancelModification 
   // -------------------
   // The Cancel Button becomes Close Button after the first Apply. 
   //
   // This method is called when the end user clicks this Button (Cancel or Close) 
   // and if this page has been once displayed.
   //
   // In these two cases, you don't modify the model: for a cancel, the model keeps
   // the initial values, and for a close, the model keeps the last applied values.
   // 
   virtual void CancelModification ( CATLISTV(CATBaseUnknown_var)& iExtract);

   // CloseWindowFromEditor()
   // -----------------------
   // This method is called when the end user swaps between pages, but not when 
   // the Edit Properties Dialog box is closed. 
   //  
   virtual void CloseWindowFromEditor();

 private:
 
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafTexturePropertyPageEdt(const CAACafTexturePropertyPageEdt &iObjectToCopy);
 
   // Assigment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafTexturePropertyPageEdt & operator = (const CAACafTexturePropertyPageEdt &iObjectToCopy);
 
 private:
  
   // _pTextureFrame Life Cycle
   // -------------------------
   //
   //   -> Created in the BuildEditor method
   //
   //   -> Deleted at the end of the Properties command 
   // 
   // 
   // When the Dialog box is closed, the editor is not informed
   //
   //  CANCEL : in the CancelModification you know that the page will be deleted
   //  OK     : in the CommitModification, you cannot write _pTextureFrame=NULL
   //            because this method is also called in the Apply case. 
   //
   //
   // In the following methods, _pTextureFrame is not always valid because BuildEditor  
   // may be not executed when these methods are called
   //
   //    - ExtractFromSelection 
   //    - GetEditorTitle 
   //    - GetEditorSize 
   //
   // 
   // In these methods, _pTextureFrame  is always valid because it was already 
   // instaniated by the BuildEditor method and it hasn't been still deleted by 
   // the properties command:
   // 
   //
   //    - SetPropertyValue
   //    - CommitModification
   //    - CancelModification
   //    - CloseWindowFromEditor
   //
   // If you want to use this value in the ExtractFromSelection method, 
   // you must create a method which resets this parameter, and call it
   // in the Dialog page destructor. 
   //
   CAACafTexturePropertyPageDlg    * _pTextureFrame ;

};


#endif
