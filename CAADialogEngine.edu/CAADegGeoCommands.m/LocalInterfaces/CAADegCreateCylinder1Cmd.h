#ifndef CAADegCreateCylinder1Cmd_h
#define CAADegCreateCylinder1Cmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop 
//  (CAAAfrGeometryWks) and its own commands.
//     
//  CAAGeometry and CAAAfrGeometryWks are described in the 
//  CAAApplicationFrame.edu FW, and state commands are described in this FW
//      
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  State command which creates a Cylinder 
//
//  Illustrates:
//
//     - Creation of a state command
//     - Use of a selection Agent
//     - Use of an agent to select in another editor.
//     - Use of the CATBasicMultiDocumentCommand class
//
//  Usage:
//
//     - Select a line in the current editor
//     - Select a circle in the current or in another editor.
//     - The command is ended when you have selected the 2 elements. (The first
//        element can be changed)
//
//  Graph:
//
//
//
//       +------------------+ 
//       !                  !   
//       !                  ! - CATPathElementAgent
//       !                  ! - CATOtherDocumentAgent  
//       !                  ! 
//       !                  !    
//       +---------+--------+ 
//                 !     
//              Ok: CreateCylinder 
//                 !
//                 V
//               NULL
//
//
//===========================================================================

// DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand

// DialogEngine Framework
class CATPathElementAgent ;    //Dialog agent 
class CATOtherDocumentAgent ;  //Dialog agent 

// Mathematic Framework
#include <CATMathPoint.h>

class CAADegCreateCylinder1Cmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegFileCmd.CATNls  
  // 
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreateCylinder1Cmd.

  CmdDeclareResource(CAADegCreateCylinder1Cmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegCreateCylinder1Cmd();
    virtual ~CAADegCreateCylinder1Cmd();  

    // Activate
    // --------
    // Called when the command selector gives the focus to this command. 
    // Two cases can happen:
    //  -The command starts from the beginning.
    //  -The command restarts at the state that was current when a shared command 
    //   took the focus from it.
    //
    // These two cases can be distinguished thanks to the notification type.
    //
    CATStatusChangeRC Activate   (CATCommand * iCmd,CATNotification * iNotif);


    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    //
    //
    virtual void BuildGraph() ;


    // CreateCylinder 
    // -----------------------
    // Creates a CAASysCylinder in the model. 
    //
    CATBoolean  CreateCylinder   (void * iDummy);

    // GetValuation
    // ------------
    // Retrieves information for the cylinder on acquisition agents
    //
    void  GetValuation   (CATMathPoint & oBasePoint,
                          CATMathPoint & oTopPoint, 
                          float & oRadius);

  private :

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateCylinder1Cmd(const CAADegCreateCylinder1Cmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateCylinder1Cmd & operator = (const CAADegCreateCylinder1Cmd &iObjectToCopy);

  private :

    // Dialog agent to get the line of the cylinder ( neutral fiber)
    CATPathElementAgent     * _daSelectionLine ; 
	
    // Dialog agent to get the radius of the cylinder
    //
    CATOtherDocumentAgent   * _daSelectionCircle ;

    // To create an element in a document
    CATBaseUnknown          * _pUIActiveObject    ;   
    CATBaseUnknown          * _pContainer     ; 


};
#endif
