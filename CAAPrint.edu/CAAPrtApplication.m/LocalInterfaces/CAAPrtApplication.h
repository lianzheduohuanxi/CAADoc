#ifndef CAAPrtApplication_H
#define CAAPrtApplication_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Interactive application composed of two menus:
//
//  - The File menu which enables the user to 
//    * visualize images from TIFF files
//    * create new images by capturing parts of visualized images
//    * manage images in an album
//    * manage the list of available printers 
//    * print images
// 
//  - The Printable Objects menu which enables
//    * to display a test image
//    * to print a test image
//    * to print a label from a specified string 
//    
//  Illustrates:
//
//     Creation of a CATPrintFileImage from an input TIFF file
//     Creation of a CATPrint2DRep from a CATPrintFileImage
//     Integration of print standard commands in an application:
//           CATPrintCaptureDialog
//           CATPrintAlbumDialog
//           CATPrinterManagerDialog
//           CATPrintDialog
//
//     Creation of a image derived from CATPrintImage from nothing
//     Display of this image by creating a CATPrint2DRep from it
//     Print of an image by using a printable object
//      
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAAPrtApplication  [File.tif]
//  
//  A frame composed of a menu bar and a 2D viewer is displayed. 
//  If the File.tif file is specified, its image is drawn in the viewer.
//  
//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  Application class.
//  This is the main object in the process. It avoids writing a main function.
//  Event loop is managed automatically by deriving from 
//  CATInteractiveApplication. 
//  CAAPrtApplication only creates the main window and subscribes to the 
//  window closing to terminate the application.  
//
//=============================================================================
//  Inheritance:
//  ------------
//           CATInteractiveApplication (Dialog Framework)
//              CATApplication (System Framework)
//
//=============================================================================
//  Main Method:
//  ------------
//
//  BeginApplication: Contains the whole application code.
//
//
//=============================================================================

// Dialog Framework
#include "CATInteractiveApplication.h"  // To derive from CATInteractiveApplication

class CAAPrtApplication : public CATInteractiveApplication
{
public:

  // Constructs the application given an identifier
  // Parameters:
  //    iIdentifier: 
  //        The identifier 
  CAAPrtApplication(const CATString &iIdentifier);

  ~CAAPrtApplication();
  
  // Closes the application. 
  // Callback called when the user requests the end of the application  
  // Parameters:
  //    iPublishingCommand: 
  //        The publisher of the iNotification notification 
  //    iNotification: 
  //        The received notification 
  //    iUsefulData: 
  //        The data sent. NULL here. 
  void DestroyCB(CATCommand           *iPublishingCommand, 
                  CATNotification     *iNotification, 
                  CATCommandClientData iUsefulData);
      
  // Contains the whole application code.
  void BeginApplication();

  //Returns the application return code.
  int EndApplication();

private:

  // Default constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtApplication ();

  // Copy constructor, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtApplication(const CAAPrtApplication &iObjectToCopy);
  	
  // Assignment operator, not implemented
  // Set as private to prevent from compiler automatic creation as public.
  CAAPrtApplication & operator = (const CAAPrtApplication &iObjectToCopy);
  	
};

#endif
