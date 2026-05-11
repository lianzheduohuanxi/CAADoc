#ifndef CAADegBoxCreationChoiceNotification_h
#define CAADegBoxCreationChoiceNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2003
//   
//==============================================================================
//  Abstract of the class:
//  ----------------------
//  
//  This kind of notification are sent by the CAADegBoxPaletteChoiceCmd
//  command when the end user clicks on a check header displayed in the Palette. 
//  Each check header defines a way to create a box. The box creation is defined by 
//  the CAADegCreateBoxCmd state command. It is this command which adds the check 
//  headers in the Palette. 
//
//==============================================================================

// System Framework
#include "CATNotification.h"    // Needed to derive from CATNotification

class CAADegBoxCreationChoiceNotification : public CATNotification
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;
  
  public:

    // Constructor/destructor

    CAADegBoxCreationChoiceNotification();
    virtual ~CAADegBoxCreationChoiceNotification();

    // This method will be used by the CAADegCreateBoxCmd command
    // to know which check header has been pushed by the end user.
    // 
    HRESULT GetChoice(int & oChoiceValue) ;

    // This method is used by the command which sends the notification.
    // This command is CAADegBoxPaletteChoiceCmd
    //
    HRESULT SetChoice(int   iChoiceValue) ;

  private:
    
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegBoxCreationChoiceNotification(const CAADegBoxCreationChoiceNotification &iObjectToCopy);

  private :

    // An indice to represent the check header clicked by 
    // the end user
    int _ChoiceValue ;
};

#endif
