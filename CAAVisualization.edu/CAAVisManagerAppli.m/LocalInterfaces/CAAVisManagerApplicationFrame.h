#ifndef CAAVisManagerApplicationFrame_H
#define CAAVisManagerApplicationFrame_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//  The application frame.
//
//  This class defines the main window of the application. 
//  It is created and enclosed by the application.
//
//=============================================================================


//Dialog FrameWork
#include "CATDlgDocument.h" // To derive from 

class CAAVisManagerApplicationFrame : public CATDlgDocument
{
  // Declares the CAAVisManagerApplicationFrame.CATNls file as the dialog message catalog
  DeclareResource(CAAVisManagerApplicationFrame, CATDlgDocument)

	public:
    // Constructor.
    // iParent   : pointer to the application.
    // iObjectId : identificator NLS 
    // iStyle    : the dialog style of the window.
    CAAVisManagerApplicationFrame(CATInteractiveApplication *iParent, 
                                  const CATString& iObjectId, 
                                  CATDlgStyle iStyle=NULL);
   
    //Destructor.
    virtual ~CAAVisManagerApplicationFrame();

    private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerApplicationFrame();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerApplicationFrame(const CAAVisManagerApplicationFrame &iBrother);
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerApplicationFrame & operator = (const CAAVisManagerApplicationFrame &iBrother);
 
};

#endif
