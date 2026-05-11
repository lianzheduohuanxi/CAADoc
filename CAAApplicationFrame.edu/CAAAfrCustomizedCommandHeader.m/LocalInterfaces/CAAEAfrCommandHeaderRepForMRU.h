// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAEAfrCommandHeaderRepForMRU_h
#define CAAEAfrCommandHeaderRepForMRU_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  It is an implementation  of the CATIAfrCommandHeaderRep interface on
//  the CAAAfrMRUHeader command header. This interface enables you to
//  define the dialog object associated with the starter which represents the command
//  header into the menu bar. 
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h" // to derive from 
class CATAfrCommandHeaderRep ;

//Dialog Framework
class CATDialog;

class CAAEAfrCommandHeaderRepForMRU : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
public:
  
  CAAEAfrCommandHeaderRepForMRU();
  virtual ~CAAEAfrCommandHeaderRepForMRU();

  // CATIAfrCommandHeaderRep
  virtual HRESULT  CreateToolbarRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  virtual HRESULT  CreateMenuRep    (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
  virtual HRESULT  CreateCtxMenuRep (const CATDialog * iParent,CATAfrCommandHeaderRep ** oHdrRep) ;
 
private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrCommandHeaderRepForMRU(const CAAEAfrCommandHeaderRepForMRU &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrCommandHeaderRepForMRU & operator = (const CAAEAfrCommandHeaderRepForMRU &iObjectToCopy);

};

#endif
