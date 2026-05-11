// COPYRIGHT DASSAULT SYSTEMES 2002

#ifndef CAAEPstINFNavigateObjectRoot_h
#define CAAEPstINFNavigateObjectRoot_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension of the CAAPstINFRoot component, implementing
//  the CATINavigateObject interface of the ObjectModelerBase framework in orderto
//  allow listing the children features aggregated by the root.
//
//  Illustrates programming the GetIdentificators and GetChildren methods for
//  a root object.
//
//===========================================================================
//  Inheritance:
//  ------------
//            
//  CATBaseUnknown (System Framework) 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"             // Needed to derive from 
class CATListValCATUnicodeString;       // Needed by GetIdentificators

// ObjectModelBase 
class CATListValCATBaseUnknown_var;     // Needed by GetChildren

class CAAEPstINFNavigateObjectRoot : public CATBaseUnknown
{
    CATDeclareClass;

    public :

	// Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEPstINFNavigateObjectRoot();
    virtual ~CAAEPstINFNavigateObjectRoot();
	
    // Returns the identifier of the root feature.
    CATListValCATUnicodeString * GetIdentificators();
    
    // Returns a list of the direct children of the root node.
    CATListValCATBaseUnknown_var * GetChildren();
 
    private :

    // Copy constructor, not implemented
    // Set as private to prevent the automatic creation as public by the compiler.
    CAAEPstINFNavigateObjectRoot(const CAAEPstINFNavigateObjectRoot &iObjectToCopy);

};

#endif
