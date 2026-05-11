#ifndef CAADegPointErrorBox_h
#define CAADegPointErrorBox_h

// COPYRIGHT DASSAULT SYSTEMES 1999
 
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Dialog window which displays an error message indicating that 2 points 
//  given by the user are equal.
//  This window is used by the CAADegCreatePlaneCmd, CAADegCreateTriangleCmd,
//  CAADegCreatePolylineCmd.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Build  : Displays the message and subscribes to the Ok notification.
//  ClickOK: Callback which requests the dialog box destruction.
//
//===========================================================================

// Dialog Framework
#include "CATDlgNotify.h"  //Needed to derive from CATDlgNotify

class CAADegPointErrorBox : public CATDlgNotify
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegPointErrorBox.CATNls 
  //    
  DeclareResource(CAADegPointErrorBox,CATDlgNotify) ;

  public :

    CAADegPointErrorBox(CATDialog *iParent, const int iFirstPoint,const int iSecondPoint );
    virtual ~CAADegPointErrorBox(); 
	
    // Construct the message to print in the box
    void Build();

  private : 

    // Asks a destruction of the Dialog box
    void ClickOK (CATCommand           * iPublisher, 
		          CATNotification      * iNotification, 
		          CATCommandClientData   iUsefulData);

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegPointErrorBox ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegPointErrorBox(const CAADegPointErrorBox &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegPointErrorBox & operator = (const CAADegPointErrorBox &iObjectToCopy);

  private : 

    int  _FirstPoint ;
    int  _SecondPoint;

};
#endif
