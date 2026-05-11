#ifndef CAACafColorPropertyPageEdt_H
#define CAACafColorPropertyPageEdt_H
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
//  See CATCafTexturePropertyPageEdt in CAACafEditTextureProp.m to have more
//  detail about this class.
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

// Local framework
class CAACafColorPropertyPageDlg;      // Dialog Page of this editor

// CATIAApplicationFrame framework
class CATEditorPage;                   // Tabpage frame father


class  CAACafColorPropertyPageEdt : public CATEditor
{
   // Used in conjunction with CATImplementClass in the .cpp file
   CATDeclareClass;

   public:
 
   CAACafColorPropertyPageEdt();
   virtual ~CAACafColorPropertyPageEdt(); 

   virtual void ExtractFromSelection ( CATLISTV(CATBaseUnknown_var) & oExtract, 
                                const  CATLISTV(CATBaseUnknown_var) * iSelection =NULL );
   
   virtual CATUnicodeString  GetEditorTitle();

   virtual void SetEditorSize(int & oSize );

   virtual void BuildEditor(CATEditorPage * iEditor); 

   virtual void SetPropertyValue ( CATLISTV(CATBaseUnknown_var)& iExtract, 
                                                   ModeReadWrite iMode);

   virtual void CommitModification ( CATLISTV(CATBaseUnknown_var)& iExtract);

   virtual void CancelModification ( CATLISTV(CATBaseUnknown_var)& iExtract);

   virtual void CloseWindowFromEditor();

 private:
 
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafColorPropertyPageEdt(const CAACafColorPropertyPageEdt &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafColorPropertyPageEdt & operator = (const CAACafColorPropertyPageEdt &iObjectToCopy);

 private:
  
   // _pColorFrame Life Cycle
   // -------------------------
   //
   //   -> Created in the BuildEditor method , 
   //
   //   -> Deleted at the end of the Properties command, 
   // 
   // 
   // When the Dialog box is closed, the editor is not informed
   //
   //  CANCEL : in the CancelModification you know that the page will be deleted
   //  OK     : in the CommitModification, you cannot write _pColorFrame=NULL
   //            because this method is also called in the Apply case. 
   //
   //
   // In the following methods, _pColorFrame is not always valid because BuildEditor  
   // may be not executed when these methods are called
   //
   //
   //    - ExtractFromSelection 
   //    - GetEditorTitle 
   //    - GetEditorSize 
   //
   // 
   // In these methods, _pColorFrame  is always valid because it was already 
   // instaniated by the BuildEditor method and it hasn't been still deleted by 
   // the properties command:
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
   //
   CAACafColorPropertyPageDlg    * _pColorFrame ;

};


#endif
