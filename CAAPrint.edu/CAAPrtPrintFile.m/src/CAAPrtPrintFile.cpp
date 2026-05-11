// COPYRIGHT DASSAULT SYSTEMES 1999

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which prints a JPEG file with a chosen printer.
//    
//  Illustrates:
//     Retrieving the list of printers 
//     Creating a CATPrintFileImage from an input jpg file
//     Creating a CATPrintDeviceFile
//     Defining print parameters
//     Printing
//    
//  What it does :
// 
//     1- Decodes the command line argument which must be a JPEG file
//     2- Displays the list of Printers
//     3- Waits for the user's printer choice
//     4- Creates an image from the input file
//     5- Creates a printer device
//     6- Defines Print parameters
//     7- Prints the image 
//     8- Cleans the application
//
//============================================================================
//  Usage:
//  ------
//
//  Type:
//     CAAPrtPrintFile File.jpg
//  
//     The list of available printers is displayed.
//     Type the number associated to the chosen printer.
//     The chosen printer prints the input file. 
//  
//  Return Code:
//     0 : OK
//     1 : Bad argument count 
//     2 : Bad format for the input file, must be .jpg 
//     3 : Error in printing
//
//============================================================================

//Print Framework
#include "CATPrintFileImage.h"   // To create an image from the input file
#include "CATPrintParameters.h"  // To define print parameters
#include "CATPrinterDevice.h"    // To define a print device
#include "CATPrinterManager.h"   // To retrieve the printer list
#include "CATPrinter.h"          // To print

// System Framework
#include "CATGetEnvValue.h" // To retrieve an environment variable
#include "CATString.h"      // To manage string

//C++ standard Library
#include <iostream.h>       // To display traces


int main(int argc, char* argv[])
{
  int ReturnCode = 0;

  cout << "The CAAPrtPrintFile programs begins ..."<< endl << endl;

  //-----------------------------------------------------------------
  // 1- Decodes the command line argument which must be a JPEG file
  //-----------------------------------------------------------------

  if ( 2 != argc )
  {
    cout << "Usage: CAAPrtPrintFile inputFile.jpg "<< endl;
    cout << "Try with the file: CAAPrint.edu/CNext/resources/graphic/images/CAAPrtPrintFile.jpg" << endl<<endl;
    return 1;  
  } 
  CATString InputName(argv[1]);     
    
  // Checks that the input file is a JPEG file  
  CATString JPG = InputName.SubString(InputName.GetLengthInChar()-4,4);
  if ( 0 != JPG.Compare(".jpg") )
  {
    cout << "Usage: CAAPrtPrintFile inputFile.jpg "<< endl;
    cout << "Try with the file: CAAPrint.edu/CNext/resources/graphic/images/CAAPrtPrintFile.jpg" << endl<<endl;
    return 2;
  }

  cout << "The file to print is= " << InputName.ConvertToChar() << endl<< endl;

  //-----------------------------------------------------------------
  // 2- Displays the list of Printers
  //-----------------------------------------------------------------

  // 2-A) Printer manager initialization
  CATPrinterManager::Begin();

  // 2-B) Retrieves and displays the list of printers
  cout << "Available printers : " << endl << endl;

  for (int i=0; i<CATPrinterManager::GetPrinterCount(); i++)
  {
    CATPrinter printer = CATPrinterManager::GetPrinterFromIndex(i);
    int old_width = cout.width(3);
    cout.setf( ios::right );
    cout << i+1;
    cout.setf( ios::left );
    cout << " : " << (const char*) printer.GetDescription() << endl;
  }

  //-----------------------------------------------------------------
  // 3- Waits for the user's printer choice
  //-----------------------------------------------------------------

  int PrinterIndex;
  cout << "Target printer ? (0=exit) : " << flush;
  cin >> PrinterIndex;

  // Loops to treat the input errors
  while (!(PrinterIndex>=0 && 
              PrinterIndex<=CATPrinterManager::GetPrinterCount()))
  {
    cout << "Wrong number. Enter a number between 0 and " ;
    cout << CATPrinterManager::GetPrinterCount();
    cout << " : ";
    cin >> PrinterIndex;
  }
  if ( 0 == PrinterIndex ) 
  {
    return 0;
  }

  // Retrieves the printer  
  PrinterIndex--;
  CATPrinter Printer = CATPrinterManager::GetPrinterFromIndex(PrinterIndex);

  //-----------------------------------------------------------------
  // 4- Creates an image from the input JPEG file
  //-----------------------------------------------------------------

  CATPrintFileImage *pImage = new CATPrintFileImage(InputName, "JPEG");


  //-----------------------------------------------------------------
  // 5- Creates a printer device
  //-----------------------------------------------------------------

  CATPrinterDevice Device( &Printer );


  //-----------------------------------------------------------------
  // 6- Defines Print parameters
  //-----------------------------------------------------------------

  CATPrintParameters Parameters;
  
  // Rotates the image 
  Parameters.SetRotation( CATPRINTCCW_90 );
  // Specifies that the image must be resized to match the paper
  Parameters.SetMapToPaper(1);
  // Sets the margins
  Parameters.SetMargins(20.0, 20.0, 10.0, 10.0);


  //-----------------------------------------------------------------
  // 7- Prints the image 
  //-----------------------------------------------------------------

  cout << "Now printing " << (const char*) pImage->GetDescription() << "... " << endl;

  if ( 0 == pImage->Print(&Device, Parameters) )
  {
    cout << " Error during printing " << endl<<endl;
    ReturnCode = 3;
  }else
  {
     cout << "Done." << endl<<endl;
  }

  
  //-----------------------------------------------------------------
  // 7- Cleans the application
  //-----------------------------------------------------------------

  // Deallocates created objects
  pImage->Release();
  pImage = NULL ;

  // Done with the printer manager
  CATPrinterManager::End();

  cout << "The CAAPrtPrintFile programs is finished ..."<< endl << endl;

  return ReturnCode;

}

