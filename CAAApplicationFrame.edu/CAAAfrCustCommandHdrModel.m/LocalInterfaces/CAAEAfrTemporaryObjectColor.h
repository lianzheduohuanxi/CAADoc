// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAEAfrTemporaryObjectColor_h
#define CAAEAfrTemporaryObjectColor_h

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  It is mainly an implementation  of the CATIAfrCommandHeaderRep interface on
//  the CAAAfrComboColorHeader command header. This interface enables you to
//  define the dialog object associated with the starter which represents the command
//  header into: a toolbar, the menu bar or a contextual menu. 
//
//  This class is also an implementation  of the CAAIAfrComboColorHeader interface
//  on the same component. This interface "exports" the current r,g,b color composant. 
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h" // to derive from 

class CAAEAfrTemporaryObjectColor : public CATBaseUnknown
{
  CATDeclareClass;
  
public:
  
  CAAEAfrTemporaryObjectColor();
  virtual ~CAAEAfrTemporaryObjectColor();

  // CAAIAfrTemporaryObjectColor
  virtual HRESULT GetCurrentColor(int & oRed, int & oGreen, int & oBlue) const ;

  virtual HRESULT SetCurrentColor(int & oRed, int & oGreen, int & oBlue) ;

private:

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrTemporaryObjectColor(const CAAEAfrTemporaryObjectColor &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAEAfrTemporaryObjectColor & operator = (const CAAEAfrTemporaryObjectColor &iObjectToCopy);

private:

  int _RedComp, _GreenComp , _BlueComp ;

};

#endif
