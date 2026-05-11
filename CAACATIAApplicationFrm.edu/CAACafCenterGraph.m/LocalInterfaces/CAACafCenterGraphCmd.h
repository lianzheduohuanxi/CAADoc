#ifndef CAACafCenterGraphCmd_h
#define CAACafCenterGraphCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2006

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This state command illustrates how to use the CATCafCenterGraph class
//  to center a node in the specification tree displayed in a 
//  CATFrmNavigGraphicWindow.
//
//
//===========================================================================

// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// DialogEngine Framework 
class CATPathElementAgent ;  

// ObjectModelerBase Framework    
class CATNavigController  ;

class CAACafCenterGraphCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAACafCenterGraphCmd.CATNls  
  // 

  CmdDeclareResource(CAACafCenterGraphCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAACafCenterGraphCmd();
    virtual ~CAACafCenterGraphCmd();  


    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    //
    virtual void BuildGraph() ;

    // Center node
    // -----------
    // This action method 
    //
    CATBoolean  CenterGraphOnObject (void * iDummy);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafCenterGraphCmd(const CAACafCenterGraphCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafCenterGraphCmd & operator = (const CAACafCenterGraphCmd &iObjectToCopy);

  private :

    // Agent to select the object to expand
    CATPathElementAgent                 * _daObjectToCenterNode ; 

};
#endif
