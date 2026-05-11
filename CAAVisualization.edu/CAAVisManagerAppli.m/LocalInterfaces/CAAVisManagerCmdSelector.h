#ifndef CAAVisManagerCmdSelector_H
#define CAAVisManagerCmdSelector_H

// COPYRIGHT DASSAULT SYSTEMES 1999

// System FrameWork
#include "CATCommand.h"

//Visualization FrameWork
#include "CATHSO.h"
#include "CATPSO.h"


//System FrameWork
class CATPathElement;
class CATNotification;

//Local FrameWork
class CAAVisManagerCxtMenu;

class CAAVisManagerCmdSelector : public CATCommand
{
public :

   //Constructs the command selector from a Hso and a Pso.
   CAAVisManagerCmdSelector(CATHSO &iHso,CATPSO&iPso);
   virtual ~CAAVisManagerCmdSelector();

   // Analyses eventsb received by the current object thru 
   // the send/receive mechanism of the CATCommand objects.
   CATNotifPropagationMode AnalyseNotification(CATCommand * iFromClient,
               CATNotification * iNotification);
private: 

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCmdSelector ();
        
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCmdSelector(const CAAVisManagerCmdSelector &iObjectToCopy);

    // Assignment operator , not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerCmdSelector & operator = (const CAAVisManagerCmdSelector &iObjectToCopy);

private:
   CATHSO &_Hso;
   CATPSO &_Pso;
   CAAVisManagerCxtMenu * _pCxtMenu;
   
};

#endif
