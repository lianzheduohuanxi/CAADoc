// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAEAfrCommandHeaderRepForComboColor_h
#define CAAEAfrCommandHeaderRepForComboColor_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  It is an implementation  of the CATIAfrCommandHeaderRep interface on
//  the CAAAfrComboColorHeader command header. This interface enables you to
//  define the dialog object associated with the starter which represents the command
//  header into a toolbar.
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" // to derive from 
class CATAfrCommandHeaderRep;

//Dialog Framework
class CATDialog;

class CAAEAfrCommandHeaderRepForComboColor : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
public:
  
  CAAEAfrCommandHeaderRepForComboColor();
  virtual ~CAAEAfrCommandHeaderRepForComboColor();
  
  // CATIAfrCommandHeaderRep
  virtual HRESULT  CreateToolbarRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  virtual HRESULT  CreateMenuRep    (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  virtual HRESULT  CreateCtxMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  
private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrCommandHeaderRepForComboColor(const CAAEAfrCommandHeaderRepForComboColor &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrCommandHeaderRepForComboColor & operator = (const CAAEAfrCommandHeaderRepForComboColor &iObjectToCopy);

};

#endif
