#ifndef CAAAfrChangeViewNormalCmd_h
#define CAAAfrChangeViewNormalCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Command which changes the view point according to its constructor's
//  argument.
//  This command is used three times in the workshop for the three directions
//  (Normal X, Normal Y, Normal Z).
//  The command header which launches this function is instantiated three
//  times with a different argument and passes this argument to the command.
//
//  Illustrates:
//     - creating a simple exclusive command derived from CATCommand and
//       parameterized by an argument. 
//     - Using cameras.
//
//===========================================================================
//  Inheritance:
//  ------------
//                  CATCommand  (System Framework)
//                      CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Activate : Creates a camera and gives it to the current window. 
//
//===========================================================================

// System Framework
#include "CATCommand.h"   //Needed to derive from CATCommand

class CAAAfrChangeViewNormalCmd : public CATCommand
{
  public :

   // iArgument is the normal direction of the view:   
   // ( 1: x direction , 2: y direction, 3: z direction ) 
   //
   CAAAfrChangeViewNormalCmd(void * iArgument);

   virtual ~CAAAfrChangeViewNormalCmd();  
	
   // Activate:
   // --------
   // Contains the command code. 
   // The method is called when the command gets the focus.
   //
   virtual CATStatusChangeRC Activate(CATCommand       * iFromClient,
                                      CATNotification * iEvtData);

   // Cancel:
   // --------
   // This method is called when the command loses the focus definitively
   // because an excluse command requires it. 
   // This method must request explicitely the deallocation of the 
   // current command.
   virtual CATStatusChangeRC Cancel(CATCommand         * iFromClient,
                                    CATNotification * iEvtData);
  private : 

   // Default constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAAfrChangeViewNormalCmd ();

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAAfrChangeViewNormalCmd(const CAAAfrChangeViewNormalCmd &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAAAfrChangeViewNormalCmd & operator = (const CAAAfrChangeViewNormalCmd &iObjectToCopy);

  private :

   // Choice of the normal view 
   int  _ArgumentCmd ;
};
#endif
