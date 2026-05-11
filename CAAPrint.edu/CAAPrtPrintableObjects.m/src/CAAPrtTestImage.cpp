// COPYRIGHT DASSAULT SYSTEMES 1999

// Local framework
#include "CAAPrtTestImage.h"     // Header of the current class

// Print framework
#include "CATPrintParameters.h"  // To define print parameters
#include "CATPrintGenerator.h"   // To use a generator to draw the image

// Visualization framework
#include "CATPixelImage.h"       // To draw bitmaps

// Mathematics
#include <CATMath.h>

//----------------------------------------------------------------------------

// Declares that this class is an implementation and OM-derives from
// CATPrintImage. 
CATImplementClass(CAAPrtTestImage,Implementation,CATPrintImage, CATNull);

// This OM-derivation enables it to inherit the 
// implementation of CATIPrintable.
// There's no need to fill the dictionary.

//----------------------------------------------------------------------------
CAAPrtTestImage::CAAPrtTestImage()
{
  SetDescription( "Test image" );
}

//----------------------------------------------------------------------------
CAAPrtTestImage::~CAAPrtTestImage() 
{}

//----------------------------------------------------------------------------
int CAAPrtTestImage::GetSize(float &oWidth, float& oHeight)
{
  oWidth  = 200.f;
  oHeight = 300.f;
    
  return 1;
}

//----------------------------------------------------------------------------
int CAAPrtTestImage::Decode(CATPrintGenerator * iGenerator, 
                            const CATPrintParameters  &iParameters)
{
  if ( NULL != iGenerator)
  {
     // Initializes generation
     iGenerator->Begin(iParameters);
   
     // Draws Texts
     DrawTexts(iGenerator, 180.0);
     // Draws ranges of colors
     DrawColors(iGenerator, 130.0);
     // Draws lines in different styles, widths and colors
     DrawLines(iGenerator,  70.0);
     // Draws bitmaps
     DrawBitmaps(iGenerator, 50.0);
   
     // Ends generation 
     iGenerator->End();
  }
  // Returns 1 to indicate successful execution
  return 1;
}

//----------------------------------------------------------------------------
void CAAPrtTestImage::DrawTexts(CATPrintGenerator * iGenerator, float iBase)
{
  if ( NULL != iGenerator)
  {
     // Defines the number-0 color: black
     iGenerator->DefineColor(0, 0.0, 0.0, 0.0);
     // Sets the number-0 color
     iGenerator->SelectDrawColor(0);
     // Sets horizontal direction from left to rigth
     iGenerator->SetTextAttribute(CATPRINTTEXT_DIRECTION, 0.0);
     // Sets the Helvetica font
     iGenerator->SetTextAttribute(CATPRINTTEXT_TYPEFACE, CATPRINTTEXT_HELVETICA);
     // Requests bold caracters
     iGenerator->SetTextAttribute(CATPRINTTEXT_WEIGHT,   CATPRINTTEXT_BOLD);
     // Sets the font height
     iGenerator->SetTextAttribute(CATPRINTTEXT_HEIGHT, 10.0);
     // Draws a string giving its location
     iGenerator->DrawGeometricText(0.f, iBase+10.f, "CATIA V5 Print Test Page");
     // changes the font height
     iGenerator->SetTextAttribute(CATPRINTTEXT_HEIGHT, 4.f);
     // cancels the bold caracter request
     iGenerator->SetTextAttribute(CATPRINTTEXT_WEIGHT,   CATPRINTTEXT_NORMAL);
     // Draws another string
     iGenerator->DrawGeometricText(0.f, iBase, 
                                   "Congratulations : your printer has passed the test !");
  }
}

//----------------------------------------------------------------------------
void CAAPrtTestImage::DrawColors(CATPrintGenerator * iGenerator, float iBase)
{
  const int gradientSize = 40;
  
  if ( NULL != iGenerator)
  {
     // Defines text attributes: courier font, normal caracters, font height, 
     // left alignment
     iGenerator->SetTextAttribute(CATPRINTTEXT_TYPEFACE, CATPRINTTEXT_COURIER);
     iGenerator->SetTextAttribute(CATPRINTTEXT_WEIGHT,   CATPRINTTEXT_NORMAL);
     iGenerator->SetTextAttribute(CATPRINTTEXT_HEIGHT, 4.0);
     iGenerator->SetTextAttribute(CATPRINTTEXT_ALIGNMENT, CATPRINTTEXT_BASELEFT);  
   
     // Sets the number-1 color as the draw color and redefines the number-1 color 
     // several times.
     // With redefined number-1 color, draws a text describing the color.
   
     // Red
     iGenerator->DefineColor(1, 1.f, 0.f, 0.f);
     iGenerator->SelectDrawColor(1);
     iGenerator->DrawGeometricText(0.f, iBase+30.f, "Red gradient");
     // Green
     iGenerator->DefineColor(1, 0.f, 1.f, 0.f);
     iGenerator->DrawGeometricText(0.f, iBase+20.f, "Green gradient");
     // Blue
     iGenerator->DefineColor(1, 0.f, 0.f, 1.f);
     iGenerator->DrawGeometricText(0.f, iBase+10.f, "Blue gradient");
     // Gray
     iGenerator->DefineColor(1, 0.f, 0.f, 0.f);
     iGenerator->DrawGeometricText(0.f, iBase,      "Grey gradient");
     
     // Sets the number-1 color as the filling color.
     iGenerator->SelectFillColor(1);
   
     // Draws rectangles, each one filling with a gradual range of the shades  
     // of a color from the darkest to the lightest.
     // This is done by redefining the number-1 color which has been declared 
     // as the filling color.
     int i = 0;
     for (; i<gradientSize; i++)
     {
       const float c = float(i)/float(gradientSize-1);
   
       // Red
       iGenerator->DefineColor(1, c, 0.f, 0.f);
       iGenerator->FillRectangle(40.f+i*4.f, iBase+30.f-4.f, 40.f+(i+1)*4.f, iBase+30.f+4.f);
   
       // Green
       iGenerator->DefineColor(1, 0.f, c, 0.f);
       iGenerator->FillRectangle(40.f+i*4.f, iBase+20.f-4.f, 40.f+(i+1)*4.f, iBase+20.f+4.f);
   
       // Blue
       iGenerator->DefineColor(1, 0.f, 0.f, c);
       iGenerator->FillRectangle(40.f+i*4.f, iBase+10.f-4.f, 40.f+(i+1)*4.f, iBase+10.f+4.f);
           
       // Grey
       iGenerator->DefineColor(1, c, c, c);
       iGenerator->FillRectangle(40.f+i*4.f, iBase     -4.f, 40.f+(i+1)*4.f, iBase+4.f);
     }
   
     //  Draws a frame in black (number-0 color) around each rectangle
   
     // Selects the black color
     iGenerator->SelectDrawColor(0);
     
     float x0, y0, x1, y1;
     x0 = 40.f;
     y0 = iBase+30.f-4.f;
     x1 = 40.f+gradientSize*4.f;
     y1 = iBase+30.f+4.f;
       
     for (i=0; i<4; i++)
     {
       // Moves to the bottom left corner of the rectangle
       iGenerator->MoveTo(x0, y0);   
       // Draws the horizontal line to the bottom right corner
       iGenerator->LineTo(x1, y0);
       // Draws the vertical line to the top right corner
       iGenerator->LineTo(x1, y1);        
       iGenerator->LineTo(x0, y1);
       // Draws the horizontal line to the bottom left corner
       iGenerator->LineTo(x0, y0);
    
       // Changes the y coordinates to draw the following rectangle
       y0 -= 10.f;
       y1 -= 10.f;
     }
  }
}

//----------------------------------------------------------------------------
void CAAPrtTestImage::DrawLines(CATPrintGenerator * iGenerator, float iBase)
{

  // Array of line styles
  const CATPrintLineAttribute aLineTypes[] =
  {
    CATPRINTLINE_SOLID, CATPRINTLINE_DOT, CATPRINTLINE_DASH, 
    CATPRINTLINE_DASHDOT, CATPRINTLINE_PHANTOM,
  };
  
  if ( NULL != iGenerator)
  {
     int i, lineWidth, lineColor, lineType ;

     // Defines 5 colors
     iGenerator->DefineColor(1, 1.0, 0.0, 0.0);  // Red
     iGenerator->DefineColor(2, 0.0, 1.0, 0.0);  // Green
     iGenerator->DefineColor(3, 0.0, 0.0, 1.0);  // Blue
     iGenerator->DefineColor(4, 1.0, 0.0, 1.0);  // pink
     iGenerator->DefineColor(5, 1.0, 1.0, 0.0);  // yellow
       
     // Draws 6 sets of lines, each set in a different width.
     // Every set is composed of 5 lines in different styles and colors.
     float x0 = 10.0;
     for (lineWidth=1; lineWidth<=6; lineWidth++)
     {
       lineColor = 1;
       iGenerator->SetDrawWidth(lineWidth/5.f);
       for (lineType=0; lineType<5; lineType++)
       {
         iGenerator->SetLineStyle(aLineTypes[lineType]);
         iGenerator->SelectDrawColor(lineColor++);
         iGenerator->DrawLine(x0, iBase+30.f, x0, iBase+50.f);
         x0 += 3.f;
       }
       x0 += 20.f;
     }
       
     // Draws 5 sets of circle arcs, each set in a different line styles.
     // Every set is composed of 5 circle arcs in different colors.
     // The arcs alternates with the previous lines.
     iGenerator->SetDrawWidth(0.25f);
     iGenerator->SetLineStyle(CATPRINTLINE_CONTINUE);    
     x0 = 35.0;
     for (lineType=0; lineType<5; lineType++)
     {
       iGenerator->SetLineStyle(aLineTypes[lineType]);
       for (i=1; i<6; i++)
       {
         iGenerator->SelectDrawColor(i);
         iGenerator->DrawArcCircle(x0, iBase+40.f, i*1.5f, (float) +CATPIBY4, (float) -CATPIBY4);
       }
       x0 += 35.f;
     }
   
     // Draws 5 sets of ellipse arcs, each set in a different line styles.
     // Every set is composed of 5 ellipse arcs in different colors.
     // The ellipse arcs are located under the previous circle arcs.
     x0 = 35.0;
     for (lineType=0; lineType<5; lineType++)
     {
       iGenerator->SetLineStyle(aLineTypes[lineType]);
       for (i=1; i<6; i++)
       {
         iGenerator->SelectDrawColor(i);
         iGenerator->DrawArcEllipse(x0, iBase+20.f, i*1.5f, i*2.5f, 
                                    (float) +CATPIBY4, (float) -CATPIBY4, (float) CATPIBY4);
       }
       x0 += 35.f;
     }
       
     // Draws 5 sets of folded lines, each set in a different line styles.
     // Every set is composed of 5 folded lines in different colors.
     iGenerator->SetLineStyle(CATPRINTLINE_ADAPTATIVE_CONTINUE);
     x0 = 20.f;
       
     for (lineType=0; lineType<5; lineType++)
     {
       iGenerator->SetLineStyle(aLineTypes[lineType]);
       x0 -= 10.0;
       iGenerator->MoveTo(x0, iBase);
       for (i=0; i<5; i++)
       {
         iGenerator->SelectDrawColor(i);
         x0 += 1.5;
         iGenerator->LineTo(x0, iBase+7.5f);
         x0 += 1.5;
         iGenerator->LineTo(x0, iBase);
       }
       x0 += 35.0;
     }
  }
}

//----------------------------------------------------------------------------
void CAAPrtTestImage::DrawBitmaps(CATPrintGenerator * iGenerator, float iBase)
{
  if ( NULL != iGenerator)
  {
     int i, x, y;
     unsigned char *p;
     const int xMax = 100, yMax = 100;
     float x0;
       
     // Creates a RGB Image
     CATPixelImage * pBitmap = new CATPixelImage(xMax, yMax, RGB);
   
     // Retrieves the array of the image's pixels
     p = pBitmap->GetPixelsToModify();
       
     // Fills the pixel array to get a gradual range of colors
     for (y=0; y<yMax; y++)
       for (x=0; x<xMax; x++)
       {
         // R
         p[0] = (unsigned char) floor(255.*(1.-double(x)/double(xMax))*double(y)/double(yMax));
         // G
         p[1] = (unsigned char) floor(255.*double(x*y)/double(xMax*yMax));
         // B
         p[2] = (unsigned char) floor(255.*(1.0-double(y)/double(yMax))*double(x)/double(xMax));
         p += 3;
       }
       
     // Sets the pixel size
     pBitmap->SetXPixelSize(0.1f);
     pBitmap->SetYPixelSize(0.1f);
       
     // Draws the bitmap images 4 times with a different rotation angle 
     // (0, 90, 180, 270 degrees)
     x0 = 10.0;
     for (i=0; i<4; i++)
     {
       iGenerator->DrawBitmap(x0, iBase, i, pBitmap);
       x0 += 20.f;
     }
      
     // Deallocates the image
     pBitmap->Release();
     pBitmap = NULL ;
     
     x0 += 10.0;
       
     // Creates a L (Luminance) Image. (gray levels) 
     pBitmap = new CATPixelImage(xMax, yMax, L);
   
     // Retrieves the array of the image's pixels
     p = pBitmap->GetPixelsToModify();
       
     // Fills the pixel array to get a gradual range of colors
     for (y=0; y<yMax; y++)
           for (x=0; x<xMax; x++)
               *(p++) = (unsigned char) floor(255.0*double(x*y)/double(xMax*yMax));
       
     // Sets the pixel size
     pBitmap->SetXPixelSize(0.1f);
     pBitmap->SetYPixelSize(0.1f);
       
     // Draws the bitmap images 4 times with a different rotation angle 
     // (0, 90, 180, 270 degrees)
     for (i=0; i<4; i++)
     {
       iGenerator->DrawBitmap(x0, iBase, i, pBitmap);
       x0 += 20.0;
     }
       
     // Deallocates the image
     pBitmap->Release();
     pBitmap = NULL ;
  }
}
