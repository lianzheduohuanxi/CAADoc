// COPYRIGHT DASSAULT SYSTEMES 2003

//Local Framework
#include "CAADegBoxPaletteChoiceCmd.h"
#include "CAADegBoxCreationChoiceNotification.h"

// System framework
#include "CATErrorDef.h" // SUCCEEDED macro

// C++ Standard library
#include <iostream.h>

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClassArg(CAADegBoxPaletteChoiceCmd,void * );

//-------------------------------------------------------------------------

CAADegBoxPaletteChoiceCmd::CAADegBoxPaletteChoiceCmd(void *iArgument): 
                   CATCommand(NULL,"CAADegBoxPaletteChoiceCmd")
{
  cout << "CAADegBoxPaletteChoiceCmd void constructor" << endl ;

  int value = CATPtrToINT32(iArgument) ;
  
   // This notification enables the current state command to receive it 
   // This notification is deleted by the send/receive protocole 
   //
   CAADegBoxCreationChoiceNotification * pNotification = NULL ;
   pNotification = new CAADegBoxCreationChoiceNotification();     
   pNotification->SetChoice(value);
   
   SendNotification(GetFather(),pNotification);

   pNotification = NULL ;

   // This command is undefined, once a CATCommand is by default undefined.
   // It means that it is not seen by the focus manager, and by consequence 
   // it cannot be activated , desactivated or even canceled. So this command,
   // launched by a command header, must do a suicide.
   // But attention, a RequestDelayedDestruction in a constructor if possible
   // only if the three following conditions are ALL met:
   // 
   // 1 - The class is not derived and will be never derived
   // 2 - The class has any methods, to avoid to call them after the constructor
   // 3 - RequestDelayedDestruction is the last instruction of the constructor
   // 
   RequestDelayedDestruction(); 
  
}

//--------------------------------------------------------------------------

CAADegBoxPaletteChoiceCmd::~CAADegBoxPaletteChoiceCmd()
{
  cout << "CAADegBoxPaletteChoiceCmd destructor" << endl ;
}

//--------------------------------------------------------------------------

