#ifndef CAAPrtPrintableString_h
#define CAAPrtPrintableString_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Printable object whose image is composed of a frame surrounding a string 
//  specified as an argument of the object's constructor.
//  The print dialog needs a printable object as an argument of its 
//  constructor, that is to say an object which implements the CATIPrintable 
//  interface.
//  The only method of this interface is CreatePrintableImage which returns the
//  image to print.
//  The image could have implementes the CATIPrintable interface itself as it 
//  is done in the "test image" sample in the same module. 
//  But the current solution is useful when an existing component needs to 
//  become printable. In this case, the component implements the CATIPrintable 
//  interface in its implementation or in a data extension.
//  For example, if CATUnicodeString had been a component (CATUnicodeString 
//  does not derive from CATBaseUnknown), CATIPrintable could have been 
//  implemented in a data extension. 
//
//=============================================================================
//  Inheritance:
//  ------------
//             CATBaseUnknown (System Framework)
//
//=============================================================================
//  Main Method:
//  ------------
//  CreatePrintableImage: returns the image representing the string given as
//  an  argument of the constructor. 
//
//=============================================================================


// System framework
#include "CATBaseUnknown.h"     // To derive from CATBaseUnknown
#include "CATUnicodeString.h"   // The string to represent

// Print framework 
class CATPrintImage;  // To return the image

class  CAAPrtPrintableString : public CATBaseUnknown
{
 public:

  // Declares that this class belongs to a component
  CATDeclareClass;

  // Constructs the printable object using the string to print
  // Parameter
  //     iString: The string to print.
  CAAPrtPrintableString (const CATUnicodeString & iString);

  virtual ~CAAPrtPrintableString ();

  // Returns the image representing the string 
  CATPrintImage * CreatePrintableImage(void);

 private:

  // Default constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtPrintableString ();

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtPrintableString(const CAAPrtPrintableString &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtPrintableString & operator = (const CAAPrtPrintableString &iObjectToCopy);


 private:

  // The string to print 
  CATUnicodeString _String;
 
};

#endif



