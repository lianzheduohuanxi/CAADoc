// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAEAfrCommandHeaderRepForEltCount_h
#define CAAEAfrCommandHeaderRepForEltCount_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  It is an implementation  of the CATIAfrCommandHeaderRep interface on
//  the CAAAfrEltCountHeader command header. This interface enables you to
//  define the dialog object associated with the starter which represents the command
//  header into a toolbar.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" // to derive from 
class CATAfrCommandHeaderRep;

//Dialog Framework
class CATDialog;

class CAAEAfrCommandHeaderRepForEltCount : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
public:
  
  CAAEAfrCommandHeaderRepForEltCount();
  virtual ~CAAEAfrCommandHeaderRepForEltCount();
  
  // CATIAfrCommandHeaderRep
  virtual HRESULT  CreateToolbarRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  virtual HRESULT  CreateMenuRep    (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  virtual HRESULT  CreateCtxMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  
private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrCommandHeaderRepForEltCount(const CAAEAfrCommandHeaderRepForEltCount &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrCommandHeaderRepForEltCount & operator = (const CAAEAfrCommandHeaderRepForEltCount &iObjectToCopy);

};

#endif
