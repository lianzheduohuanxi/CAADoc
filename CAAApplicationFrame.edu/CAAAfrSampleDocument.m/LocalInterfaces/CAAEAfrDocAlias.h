#ifndef CAAEAfrDocAlias_H
#define CAAEAfrDocAlias_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type CAASample.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Abstract:
//  ---------
//  Class which implements the CATIDocAlias interface for the CAASample 
//  document.
//  It's a data extension of a late type (CAASample) which is the Document 
//  identifier that is shown is the File->New dialog box.
//
//  It returns the document suffix. This suffix is also used as late type
//  to implement other interfaces for the document (CATInit, CATIEditor,
//  CATIDocumentEdit).
//
//  Therefore, this document is represented by two components:
//     the first one whose late type is CAASample (the document name)
//     the second one whose late type is CAADoc (the suffix) 
//
//  Illustrates
//     Implementation of CATIDocAlias on a document.
//
//===========================================================================
//  Inheritance:
//  ------------
//                CATBaseUnknown (System Framework).
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GiveDocSuffix
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

class CATUnicodeString; // Needed by GiveDocSuffix


class CAAEAfrDocAlias: public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAEAfrDocAlias();
    virtual ~CAAEAfrDocAlias();

    // GiveDocSufix
    // ------------
    // Returns the suffix of the document's file names.
    // Warning: this string must be less than or equal to 15 characters. 
    // 
    CATUnicodeString GiveDocSuffix();

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrDocAlias(const CAAEAfrDocAlias &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEAfrDocAlias & operator = (const CAAEAfrDocAlias &iObjectToCopy);
};
#endif
