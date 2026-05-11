#ifndef CAACafViewerFeedbackCmd_h
#define CAACafViewerFeedbackCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class is a command automatically lauched by a command header. 
//  This command header is created in an addin of the general workshop.
//  See the CAAApplicationFrame.edu/CAAAfrGeneralWksAddin.m module. 
//  
//  This command enables to activate or deactivate a visual feedback in the 
//  current viewer. 
//
//===========================================================================

// System Framework
#include "CATCommand.h"   //Needed to derive from CATCommand

class CAACafViewerFeedbackCmd : public CATCommand
{
  public :

   // iArgument : 
   // ( 1: check action , 2: uncheck action) 
   //
   CAACafViewerFeedbackCmd(void * iArgument);

   virtual ~CAACafViewerFeedbackCmd();  
	
 
  private : 

   // Default constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafViewerFeedbackCmd ();

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafViewerFeedbackCmd(const CAACafViewerFeedbackCmd &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafViewerFeedbackCmd & operator = (const CAACafViewerFeedbackCmd &iObjectToCopy);


};
#endif
