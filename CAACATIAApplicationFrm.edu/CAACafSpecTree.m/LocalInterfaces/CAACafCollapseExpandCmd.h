#ifndef CAACafCollapseExpandCmd_h
#define CAACafCollapseExpandCmd_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This state command illustrates how to carry out a collapse/expand in 
//  the specification tree displayed in a CATFrmNavigGraphicWindow.
//
//
//===========================================================================

// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// DialogEngine Framework 
class CATPathElementAgent ;  
class CATPathElement ;  

// ObjectModelerBase Framework    
class CATNavigController  ;

class CAACafCollapseExpandCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAACafCollapseExpandCmd.CATNls  
  // 

  CmdDeclareResource(CAACafCollapseExpandCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAACafCollapseExpandCmd();
    virtual ~CAACafCollapseExpandCmd();  


    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    //
    virtual void BuildGraph() ;

    // ExpandNode
    // -----------
    // This action method 
    //
    CATBoolean  ExpandObject (void * iDummy);

  private :

     HRESULT DumpPathElement (CATPathElement * ipPathElement);

    // GetNavigController
    // -------------------
    //
    void GetNavigController();

    // ExpandCollapseNode
    // ------------------
    // Expands or collapses the selected object
    //
    void ExpandCollapseNode(CATBaseUnknown_var iObject);

    // ExpandAllNode
    // -------------
    // Expands all the elements from the selected object
     
    void ExpandAllNode(CATBaseUnknown_var iObject);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafCollapseExpandCmd(const CAACafCollapseExpandCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafCollapseExpandCmd & operator = (const CAACafCollapseExpandCmd &iObjectToCopy);

  private :

    // Agent to select the object to expand
    CATPathElementAgent                 * _daObjectToExpandNode ; 

    CATNavigController                  * _pNavigController ;

    char                                * _pExpandMode ;
 
};
#endif
