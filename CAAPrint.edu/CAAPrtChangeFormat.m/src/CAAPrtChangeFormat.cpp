// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract:
//  ---------
//
//  Batch program which reads a cgm file and generates a raster file.
//    
//  Illustrates:
//     Creation of a CATPrintFileImage from an input cgm file
//     Creation of a CATPrintDeviceFile in order to generate a raster file
//     Definition of print parameters
//     Generation of a raster file
//    
//  What the program does:
//
//     1- Decodes the command line argument which must be a CGM file
//     2- Builds the name of the ouput file
//     3- Creates an image from the input file
//     4- Creates a raster file device
//     5- Defines Print parameters
//     6- Writes the output file
//     7- Cleans the application
//
//=============================================================================
//  How to launch :
//  ---------------
//
//  Type:
//     CAAPrtChangeFormat File.cgm
//  
//     A File.tif is generated in the directory specified by the 
//     CAAPrtOut environment variable
//
//     In CAAPrint.edu/CNext/resources/graphic/image you find a .cgm file. 
//
//  Return Code:
//     0 : OK
//     1 : Bad argument number 
//     2 : Bad format for the input file, must be .cgm 
//     3 : The CAAPrtOut environment variable is not set
//     4 : Error during printing 
//
//=============================================================================

//Print Framework
#include "CATPrintFileImage.h"   // To create an image from the input file
#include "CATPrintParameters.h"  // To define print parameters
#include "CATPrintFileDevice.h"  // To create a file device
#include "CATPrinterManager.h"   // To make initialization

// System Framework
#include "CATGetEnvValue.h" // To retrieve an environment variable
#include "CATString.h"      // To manage strings
 
//C++ Standard library
#include <iostream.h>       // To display traces 

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

int main(int argc, char* argv[])
{
  int ReturnCode = 0;

  cout << endl << "The Sample CAAPrtChangeFormat begins....." << endl<<endl;

  //-----------------------------------------------------------------
  // 1- Decodes the command line argument which is the input CGM file
  //-----------------------------------------------------------------

  if ( 2 != argc )
  {
    cout <<"Usage: CAAPrtChangeFormat inputFile.cgm "<< endl;
    cout <<"  Try with CAAPrint.edu/CNext/resources/graphic/images/CAAPrtChangeFormat.cgm" << endl;
    cout <<"  Think to export the variable CAAPrtOut" << endl<<endl;
    return 1;  
  } 
  CATString InputName=argv[1];     

  // Checks that the input file is a CGM file  
  CATString CGM = InputName.SubString(InputName.GetLengthInChar()-4,4);
  if ( 0 != CGM.Compare(".cgm") )
  {
    cout << "Usage: CAAPrtChangeFormat inputFile.cgm "<< endl;
    cout <<"  Try with CAAPrint.edu/CNext/resources/graphic/images/CAAPrtChangeFormat.cgm" << endl<<endl;
    return 2;
  }

  cout << "The input file is=" << InputName.ConvertToChar() <<endl<<endl;

  //-----------------------------------------------------------------
  // 2- Builds the name of the output file
  //-----------------------------------------------------------------

  // 2-A) Retrieves the output directory from the CAAPrtOut environment variable.

  CATString OutDirectory;
  char * CharOutDirectory=NULL;
  CATLibStatus status = CATGetEnvValue("CAAPrtOut",&CharOutDirectory);

  if (status == CATLibSuccess)
  {
    OutDirectory = CharOutDirectory;
    // deallocates the chars allocated by CATGetEnvValue
    free(CharOutDirectory);
  }else
  {
    cout << "Usage: The CAAPrtOut environment variable is not set"<< endl<<endl;
    return 3;
  } 

  // 2-B) Retrieves the file name without its suffix from the input path name 

  int iStart=-1;
  int Pos = 0;
  // Searches the last Slash character to remove the directory name from
  // the path name
  while (Pos>-1)
  {
    iStart ++;
    Pos = InputName.FindPosition(Slash, iStart);
  }  

  CATString OutFile = InputName.SubString(iStart,InputName.GetLengthInChar()-iStart-4);

  // 2-C) Builds the output file name:
  //      CAAPrtOut + Slash + InputFileNameWithoutSuffix + ".tif" 

  CATString TmpFile(OutDirectory);
  TmpFile += Slash;
  TmpFile += OutFile;
  TmpFile += ".tif";
     
  cout <<"The file to create is: " << TmpFile.ConvertToChar() << endl<< endl;

  //-----------------------------------------------------------------
  // 3- Creates an image from the input cgm file
  //-----------------------------------------------------------------
  
  //Necessary 
  CATPrinterManager::Begin();

  
  CATPrintFileImage * pImage ;
  pImage = new CATPrintFileImage(InputName, "CGM");
    

  //-----------------------------------------------------------------
  // 4- Creates a raster file device
  //-----------------------------------------------------------------
  CATPrintFileDevice *pDevice;
  pDevice = new CATPrintFileDevice( (const char*) TmpFile, "RASTER" );
   

  //-----------------------------------------------------------------
  // 5- Defines Print parameters
  //----------------------------------------------------------------- 
  CATPrintParameters Parameters;

  // Specifies that the white pixels are not printed in black
  Parameters.SetWhitePixel(1);
  // Specifies that the image must be resized to match the paper
  Parameters.SetMapToPaper(1);
  // Adds a banner at the top of the image
  Parameters.SetBanner("CAAPrtChangeFormat");
  Parameters.SetBannerPosition(CATPRINT_TOP);
  // Specifies that the line width changes with the scale
  Parameters.SetLineWidthSpecificationMode(CATPRINT_SCALED);
  // Specifies that the segment length of not solid lines type changes with the
  // scale
  Parameters.SetLineTypeSpecificationMode(CATPRINT_SCALED);
 
  // Retrieves the dimensions of the image in order to get an image twice 
  // as wide as the input image   
  float imageWidth=0,imageHeight=0;
  int result = pImage->GetSize(imageWidth, imageHeight);  
  if ( 0 != result )
  { 
    // Retrieves the format (a CATPrintForm instance) to specify
    // dimensions
    Parameters.GetCurrentForm().SetSize(imageWidth*1.5,imageHeight);
  } 

  //-----------------------------------------------------------------
  // 6- Writes the output file
  //-----------------------------------------------------------------
  if ( 0 == pImage->Print(pDevice, Parameters) )
  {
    cout << " Error during printing " << endl<<endl;
    ReturnCode = 4;
  }else
  {
     cout << "The rastered file is created" << endl; 
  }    
 
  
  //-----------------------------------------------------------------
  // 7- Cleans the application
  //-----------------------------------------------------------------
  
  // Deallocates created objects
  pDevice->Release();
  pImage->Release();

  // Done with the printer manager
  CATPrinterManager::End();

  cout << endl << "The Sample CAAPrtChangeFormat is finished." << endl <<endl;

  return ReturnCode;
}




