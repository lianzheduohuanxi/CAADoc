#ifndef CAAEAfrAliasDocument_H
#define CAAEAfrAliasDocument_H

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
//  Data extension of the CAAGeometry Late Type. 
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
//  GiveDocSuffix
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

class CATUnicodeString;    // CATIDocAlias 

class CAAEAfrAliasDocument: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrAliasDocument();
    virtual ~CAAEAfrAliasDocument();

    // GiveDocSufix
    // ------------
    // Returns the suffix of the document's file names.
    //
    // This suffix must be used as the late type of the extension classes
    // implementing  CATIEditor, CATIDocumentEdit and so on.
    // 
    // Warning: this string must be less than or equal to 15 characters.   
    //
    CATUnicodeString         GiveDocSuffix();


  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrAliasDocument(const CAAEAfrAliasDocument &iObjectToCopy);
 
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrAliasDocument & operator  = (const CAAEAfrAliasDocument &iObjectToCopy);
 
};
#endif
