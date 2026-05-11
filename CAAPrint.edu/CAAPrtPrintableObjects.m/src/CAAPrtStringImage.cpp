// COPYRIGHT DASSAULT SYSTEMES 1999

// Local framework
#include "CAAPrtStringImage.h"  // Header of the current class

// Print framework
#include "CATPrintGenerator.h"  // To use a generator to draw the image


//-----------------------------------------------------------------------------
CAAPrtStringImage::CAAPrtStringImage(const CATUnicodeString &iString) : 
    _String(iString)
{}

//-----------------------------------------------------------------------------
CAAPrtStringImage::~CAAPrtStringImage()
{}

//-----------------------------------------------------------------------------
int CAAPrtStringImage::GetSize(float &oWidth, float &oHeight)
{
  // The size depends on the lenght of the string
  int lg = _String.GetLengthInChar();
  oHeight = 50.f;
  oWidth  = (lg+4)*10.;

  // Returns 1 to indicate successful execution
  return 1;
}

//-----------------------------------------------------------------------------
int CAAPrtStringImage::Decode(CATPrintGenerator *iGenerator, 
                              const CATPrintParameters &iParameters)
{
  if ( NULL != iGenerator )
  {
     // Initializes generation
     iGenerator -> Begin(iParameters);
   
     // Sets line width
     iGenerator->SetDrawWidth(0.0f);
   
     // Defines the black color
     int Black=0;
     iGenerator->DefineColor(Black, 0.0f, 0.0f, 0.0f);
     // Sets the black color
     iGenerator->SelectDrawColor(Black);
     // Defines the text direction: horizontal, from left to right
     iGenerator->SetTextAttribute(CATPRINTTEXT_DIRECTION, 0.0);
     // Sets the Courier font
     iGenerator->SetTextAttribute(CATPRINTTEXT_TYPEFACE, CATPRINTTEXT_COURIER);
     // Requests bold caracters
     iGenerator->SetTextAttribute(CATPRINTTEXT_WEIGHT,   CATPRINTTEXT_BOLD);
     // Defines the caracter height
     iGenerator->SetTextAttribute(CATPRINTTEXT_HEIGHT, 16.72f);
   
     int lg = _String.GetLengthInChar();
     float w, h;
     GetSize(w, h);
     
     float y = 10.;
     float x = 10.;
     float x0 = x;
     float y1 = 4*y;
     float y0 = y;
     float x1 = (lg+3)*x;
   
     // Draws the string
     iGenerator ->DrawGeometricText(x0+x, y0+y, _String);
   
     // Defines the Red color and sets it as the current one
     int Red =1;
     iGenerator->DefineColor(Red, 1.f, 0.f, 0.f);
     iGenerator->SelectDrawColor(Red);
   
     // Draws a frame around the string.
     // This frame is composed of zigzag folded lines.
   
     // Moves to the botton left corner of the frame
     iGenerator->MoveTo(x0, y0);
   
     // Draws a zigzag folded line to the bottom right corner
     int i = 1;
     for (; i<=lg+2; i++)
     {
       iGenerator->LineTo(x0+i*x-x/2, y0-y/2);
       iGenerator->LineTo(x0+i*x, y0);
     }
     // Draws a zigzag folded line to the top right corner
     for (i=1; i<=3; i++)
     {
       iGenerator->LineTo(x1+x/2, y0+i*y-y/2);
       iGenerator->LineTo(x1, y0+i*y);
     }
     // Draws a zigzag folded line to the top left corner  
     for (i=1; i<=lg+2; i++)
     {
       iGenerator->LineTo(x1-i*x+x/2, y1+y/2);
       iGenerator->LineTo(x1-i*x, y1);
     }
     // Draws a zigzag folded line to the bottom left corner    
     for (i=1; i<=3; i++)
     {
       iGenerator->LineTo(x0-x/2, y1+y/2-i*y);
       iGenerator->LineTo(x0, y1-i*y);
     }
     
     // Ends generation
     iGenerator->End();
   
  }
  // Returns 1 to indicate successful execution
  return 1;
}
