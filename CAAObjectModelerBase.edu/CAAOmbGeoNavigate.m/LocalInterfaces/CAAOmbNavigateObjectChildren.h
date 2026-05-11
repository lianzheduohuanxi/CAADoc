#ifndef CAAOmbNavigateObjectChildren_h
#define CAAOmbNavigateObjectChildren_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//
//  This Use Case illustrates how to implement the CATINavigateObject interface.
//  for elements without children
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

class CAAOmbNavigateObjectChildren : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

  public :

    CAAOmbNavigateObjectChildren();
    virtual ~CAAOmbNavigateObjectChildren();
	
    // GetIdentificators
    // -----------------
    // Returns node identifier which here is the name of the component
    //
    virtual CATListValCATUnicodeString       * GetIdentificators();
    
    // GetChildren
    // ------------
    // Returns an empty list
    //
    virtual CATListValCATBaseUnknown_var     * GetChildren();
 
  private :

    // Copy constructor, not implemented
    // Set as private to prevent the automatic creation as public by the compiler.
    CAAOmbNavigateObjectChildren(const CAAOmbNavigateObjectChildren &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAOmbNavigateObjectChildren & operator = (const CAAOmbNavigateObjectChildren &iObjectToCopy);
};

#endif
