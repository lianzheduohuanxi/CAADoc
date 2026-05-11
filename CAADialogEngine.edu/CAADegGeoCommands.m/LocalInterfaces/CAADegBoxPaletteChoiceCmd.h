#ifndef CAADegBoxPaletteChoiceCmd_h
#define CAADegBoxPaletteChoiceCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This command is launched when the end user clicks on a check header 
//  set in the Palette by the CAADegCreateBoxCmd. Each check header defines 
//  a way to create a box. 
//  This command is associated at the same time with the check state and the 
//  uncheck state. 
//
//===========================================================================

// System framework
#include "CATCommand.h"   //Needed to derive from CATCommand

class CAADegBoxPaletteChoiceCmd : public CATCommand
{
  public :

    CAADegBoxPaletteChoiceCmd(void * iArgument);

    virtual ~CAADegBoxPaletteChoiceCmd();  

  private :

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegBoxPaletteChoiceCmd();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegBoxPaletteChoiceCmd(const CAADegBoxPaletteChoiceCmd &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegBoxPaletteChoiceCmd & operator = (const CAADegBoxPaletteChoiceCmd &iObjectToCopy);
  
};
#endif



