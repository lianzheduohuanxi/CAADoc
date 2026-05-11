#ifndef CAAEPstNavigateObject_h
#define CAAEPstNavigateObject_h

// COPYRIGHT DASSAULT SYSTEMES 2001

// System Framework
#include "CATBaseUnknown.h"             // Needed to derive from

// System Framework 
class CATListValCATUnicodeString;       // Needed by GetIdentificators

// ObjectModelBase 
class CATListValCATBaseUnknown_var;     // Needed by GetChildren

class CAAEPstNavigateObject : public CATBaseUnknown
{
   // Used in conjunction with CATImplementClass in the .cpp file
    CATDeclareClass;

  public :

    CAAEPstNavigateObject();
    virtual ~CAAEPstNavigateObject();
	
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
    CAAEPstNavigateObject(const CAAEPstNavigateObject &iObjectToCopy);

};

#endif
