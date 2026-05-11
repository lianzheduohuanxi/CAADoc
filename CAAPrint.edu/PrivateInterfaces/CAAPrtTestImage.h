#ifndef CAAPrtTestImage_H
#define CAAPrtTestImage_H

// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Test image, that is to say an image composed of many elements of different 
//  types and different colors. 
//  Moreover, this image object is printable. It implements the CATIPrintable
//  interface which enables to pass it to the CATPrintDialog to have it 
//  printed. To do it, it OM-derives from CATPrintImage which already
//  implements CATIPrintable. There is nothing else to do.
//  That avoids creating another printable object which returns this image as
//  the image to print.
//
//=============================================================================
//  Inheritance:
//  ------------
//             CATPrintImage (Print Framework)
//                CATBaseUnknown (System Framework)
//
// 
//=============================================================================
//  How to test:
//  ------------
//  
//  Launch the CAAPrtApplication and choose the menu PrintableObject. The
//  first item displays the image into the screen and the second item prints it. 
// 
//=============================================================================
//  Main Methods:
//  -------------
//
//  Decode: Displays the image using a given generator and speficied 
//          parameters.
//          This method calls other methods specialized in specific 
//          element types.
//
//
//=============================================================================

// Print framework
#include "CATPrintImage.h"           // To derive from CATPrintImage

// Local Framework
#include "CAAPrtPrintableObjects.h"  // To export this class

// Print framework
class CATPrintGenerator;             // The generator to draw the image
class CATPrintParameters;            // The print parameters

class ExportedByCAAPrtPrintableObjects CAAPrtTestImage : public CATPrintImage
{
  // Declares that the class belongs to a component
  CATDeclareClass;
  
public:

    // Constructs the printable object
    CAAPrtTestImage();

    virtual ~CAAPrtTestImage();

    // Retrieves the size of the image
    int GetSize(float &oWidth, float &oHeight);

    // Draws the image using a given generator and specified print parameters
    int Decode(CATPrintGenerator *iGenerator, const CATPrintParameters &iParameters);

private:

    // Methods called by the Decode method.
    // Each of them is specialized and draws one type of objects.
    // Parameters:
    //   iGenerator: the generator used to draw the elements
    //   iBase:      the y coordinate where to draw the elements
    //
    void DrawTexts  (CATPrintGenerator *iGenerator, float iBase);
    void DrawColors (CATPrintGenerator *iGenerator, float iBase);
    void DrawLines  (CATPrintGenerator *iGenerator, float iBase);
    void DrawBitmaps(CATPrintGenerator *iGenerator, float iBase);

    // Copy constructor. Not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPrtTestImage (const CAAPrtTestImage &iObjectToCopy);

    // Assignment operator. Not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAPrtTestImage & operator = (const CAAPrtTestImage &iObjectToCopy);
};

#endif
