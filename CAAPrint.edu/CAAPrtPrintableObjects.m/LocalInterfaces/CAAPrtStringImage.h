#ifndef CAAPrtStringImage_H
#define CAAPrtStringImage_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class representing an image which draws a string surrounded by a frame 
//  composed of zigzag folded lines.
//
//=============================================================================
//  Inheritance:
//  ------------
//             CATPrintImage (Print Framework)
//                CATBaseUnknown (System Framework)
//
//=============================================================================
//  Main Methods:
//  -------------
//
//  Decode: displays the image using a given generator and speficied parameters.
//
//=============================================================================

// Print framework
#include "CATPrintImage.h"       // To derive from 

// System framework
#include "CATUnicodeString.h"    // To store the string

// Print framework
class CATPrintGenerator;  // To use a generator to draw the image
class CATPrintParameters; // To use print parameters


class CAAPrtStringImage : public CATPrintImage
{
  
public:

  // Constructs the image using the string to draw
  CAAPrtStringImage(const CATUnicodeString &iString);

  virtual ~CAAPrtStringImage();
    
  // Retrieves the size of the image
  int GetSize(float &oWidth, float &oHeight);

  // Draws the image using a given generator and specified print parameters
  int Decode(CATPrintGenerator *iGenerator, const CATPrintParameters &iParameters);

private:

  // Default constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtStringImage ();

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtStringImage(const CAAPrtStringImage &iObjectToCopy);

  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtStringImage & operator = (const CAAPrtStringImage &iObjectToCopy);

private:

  // The string to draw
  CATUnicodeString _String;
    
};

#endif
