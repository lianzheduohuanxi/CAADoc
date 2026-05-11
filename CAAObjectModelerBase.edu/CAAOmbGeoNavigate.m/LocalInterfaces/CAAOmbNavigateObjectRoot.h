#ifndef CAAOmbNavigateObjectRoot_h
#define CAAOmbNavigateObjectRoot_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//
//  This use case illustrates how to implement the CATINavigateObject interface
//  on an element with children
//  
//=============================================================================
//  Execute the Use Case:
//  --------------------
//  To execute this Use Case, you must be in a CATIA V5 session.  Create a new
//  document of type CAAGeometry.  Create geometric elements in the document.  
//
//=============================================================================

// System Framework
#include "CATBaseUnknown.h"             // Needed to derive from

// System Framework 
class CATListValCATUnicodeString;       // Needed by GetIdentificators

// ObjectModelBase 
class CATListValCATBaseUnknown_var;     // Needed by GetChildren

class CAAOmbNavigateObjectRoot : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

  public :

    CAAOmbNavigateObjectRoot();
    virtual ~CAAOmbNavigateObjectRoot();
	
    // GetIdentificators
    // -----------------
    // Returns node identifiers.
    //
    virtual CATListValCATUnicodeString       * GetIdentificators();
    
    // GetChildren
    // ------------
    // Returns a list of the direct children of the current node.
    //
    virtual CATListValCATBaseUnknown_var     * GetChildren();
 
  private :

    // Copy constructor, not implemented
    // Set as private to prevent the automatic creation as public by the compiler.
    CAAOmbNavigateObjectRoot(const CAAOmbNavigateObjectRoot &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAOmbNavigateObjectRoot & operator = (const CAAOmbNavigateObjectRoot &iObjectToCopy);
};

#endif
