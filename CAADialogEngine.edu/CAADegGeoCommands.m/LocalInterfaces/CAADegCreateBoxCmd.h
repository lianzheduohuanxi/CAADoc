#ifndef CAADegCreateBoxCmd_h
#define CAADegCreateBoxCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//==========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class is a state command which creates a Box in a CAAGeometry document.
//
//  Illustrates:
//
//     - Creation of a state command
//     - Creation and usage of check headers
//     - Usage of the palette. This command implements the CATIAfrCmdPaletteOptions
//       interface
//
//  Usage:
//
//     To create a Box:
//      
//     - step 1: Select a first point which is the origin corner of the Box
//     - step 2: Select a second point to indicate the width of the Box
//     - step 3: Indicate a point to give the depth dimension
//     - step 4: Indicate a point to give the height dimension
//     
//     You can change the way to create the box thanks three icons in
//     the Palette:
//
//       - When the first icon is selected you create a cube (three dim are equal).
//         The state command stops at the second step.
//
//       - When the second icon is selected you create a box where the width and
//          the depth is defined. The Height is equal to the depth. The state 
//          command stops at the third step.
//         
//       - When the third icon is selected you create a box where each dimension
//         is defined. The state command goes to the forth step.
//
//     These three icons are check headers. They are managed in order to create a
//     kind of radio header. When a check header is with the check state, the two 
//     others are automatically unchecked. 
//
//     At any time the end user can toggle an check header set in the palette at 
//     the beginning of the state command. This tools is always available during 
//     the command life. When the check header is ON, the box is created in (0,0,0)
//     otherwise its position is defined by the first selected point.
//     
//  Graph:
//                        
//                         
//       +-------------+
//       !Corner State !   In the Palette, three icons are added
//       !             !
//       ! Sel. Agent  !   
//       !             !
//       !             !    
//       +----+--------+
//            !    
//          Ok: AcquisitionCorner
//            !          
//            V       
//         +-------------+   In the Palette, three icons are added
//         !Width State  !
//         !             !
//         ! Sel. Agent  !   
//         !             ! 
//         !             !    
//         +-------+-----+ 
//         !       !
//         !     Ok: AcquisitionWidth (Icon>1)
//         !       !      
// Icon=1  !       !       V
//         !      +-------------+     In the Palette, two icons are added
// CreateBox      !             !
//         !      !Depth State  !<--+   
//         V      !             !   !
//        NULL    !             !   ! DrawTemporaryDepth
//                ! Ind. Agent  !---+
//                !             ! 
//                !             !    
//                +-------+-----+ 
//                !       !
//  Icon=2        !     Ok: AcquisitionDepth ( Icon =3 )
//  CreateBox     !       !     
//                V       !  
//               NULL     V
//                     +-------------+  In the Palette, no icons
//                     !Height State !
//                     !             !<-+
//                     ! Ind. Agent  !  ! DrawTemporaryHight
//                     !             !--+
//                     !             !   
//                     +-------------+
//                     !    
//                   Ok: CreateBox  
//                     !        
//                     V  
//                    NULL 
//    
//===========================================================================

// DialogEngine framework
#include "CATStateCommand.h"   //Needed to derive from CATStateCommand
class CATPathElementAgent ;    //Dialog agent 
class CATDialogAgent ;         //Dialog agent 
class CATIndicationAgent  ;    //Dialog agent 

// CAASystem.edu framework
class CAAISysLine            ;   // Needed to create the temporaries lines
class CAAISysPoint           ;   // Needed to create the temporaries points

// ApplicationFrame framework
#include "CATListOfCATCommandHeader.h" // 
class CATAfrCheckHeaderAccessor ; // Class to access check header instances
class CATISO ;                    // Needed to visualize the temporaries element
class CATICamera ;                // Needed to use the camera 
class CATI3DCamera ;              // Needed to use the camera 

// Mathematics Framework
#include "CATMathVector.h"    
#include "CATMathPoint.h"


class CAADegCreateBoxCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreateBoxCmd.CATNls  
  //
  // The beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreateBoxCmd.
  //
  CmdDeclareResource(CAADegCreateBoxCmd,CATStateCommand);

  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass ;

  public :

    // Manages the lifecyle of the command.
    //
    CAADegCreateBoxCmd();
    virtual ~CAADegCreateBoxCmd(); 
    
    // CATIAfrCmdPaletteOptions Interface

    // To provide three, two or any command header cdepending on the current state
    virtual CATLISTP(CATCommandHeader) GetPaletteStateOptions() ;

    // To provide the command header associated with the origin check header
    virtual CATLISTP(CATCommandHeader) GetPaletteOptions() ;

 
  private :

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

    // Cancel
    // --------
    // Called when the command selector gives the focus to an exclusive command,
    // or if this command completes. In this latter case, the focus is given to 
    // the default command (usually Select). 
    // You should not take care of the command destruction. This is done
    // by the dialog state command engine.
    // 
    // If the end user selects this command again, it is recreated. 
    //
    CATStatusChangeRC Cancel     (CATCommand * iCmd,CATNotification * iNotif);

    // Deactivate
    // ----------
    // Called when the command selector freezes this command to give
    // the focus to a shared command. When the shared command completes, this
    // frozen command will be reactivated from its current state. 
    //  
    CATStatusChangeRC Desactivate(CATCommand * iCmd,CATNotification * iNotif);

    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    //
    //
    virtual void BuildGraph() ;

    // CheckChoice
    // ----------
    // Tests if the current checked icon is iChoice.
    //
    CATBoolean  CheckChoice(void * iChoice);


    // CreateBox  
    // ---------
    // Action method which creates a CAASysCuboid element in the model. 
    //
    CATBoolean  CreateBox(void * iDummy);

    // AcquisitionCorner
    // -----------------
    // Action method called when the end user has selected a point which represents
    // the origin corner of the box. 
    //
    CATBoolean  AcquisitionCorner(void * iDummy);

    // AcquisitionWidth
    // ----------------
    // Action method called when the end user has selected the second point and that the 
    // active icon is not the first . 
    // To select the depth dimension, we visualize a temporary line ended by a 
    // a temporary point. This line is perpendicular to the width line. 
    // The viewpoint is changed and restored at the end of the command. 
    //
    CATBoolean  AcquisitionWidth(void * iDummy);

    // AcquisitionDepth
    // ----------------
    // Action method called when the end user has indicated the depth point and 
    // that the active icon is the third . 
    // To select the height dimension, we visualize a temporary line ended by a 
    // a temporary point. This line is perpendicular to the width line. 
    // The viewpoint is changed and restored at the end of the command. 
    //
    CATBoolean  AcquisitionDepth(void * iDummy);

    // DrawTemporaryDepth
    // -------------------
    // Action method called in the loop transition to achieve the depth point.
    //
    CATBoolean  DrawTemporaryDepth(void * iDummy);
	
    // DrawTemporaryHeight
    // -------------------
    // Action method called in the loop transition to achieve the height point.
    //
    CATBoolean  DrawTemporaryHeight(void * iDummy);

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateBoxCmd(const CAADegCreateBoxCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreateBoxCmd & operator = (const CAADegCreateBoxCmd &iObjectToCopy);

    // FindBoxParameters
    // -------------------
    // Called by the CreateBox Method to retrieve the box
    // parameters from acquisition agents
    //
    void FindBoxParameters( const CATMathPoint  & iOrigin,
                               CATMathVector & oWidth,
                               CATMathVector & oDepth ,
                               CATMathVector & oHeight ) const ;

    // FindBoxOrigin
    // ---------------
    // Finds coordinates point for the path element agent
    //
    void FindBoxCornerPoint( CATMathPoint  & oOrigin) const ;

    // FindBoxWidthPoint
    // --------------------
    // Finds coordinates point for the path element agent
    //
    void FindBoxWidthPoint( CATMathPoint  & oWidthPoint) const ;

    // BoxCreationChoiceChange
    // -----------------------
    // Callback method called when the CAADegBoxPaletteChoiceCmd command sends a 
    // CAADegBoxCreationChoiceNotification notification. In other words when the
    // end uses clicks on one of the three icons representing the way to create a box.
    // This method enables to create a kind of radio button between the three icons
    //
    void BoxCreationChoiceChange (CATCommand        * iPublisher, 
		          CATNotification      * iNotification, 
		          CATCommandClientData   iUsefulData);


  private :

    // To select the origin corner of the box. 
    CATPathElementAgent  * _daPathElementCornerPoint ;   
    	
    // To select the second point 
    // The lenght between the Corner Point and the Width Point 
    // defines the width of the Box. 
    CATPathElementAgent  * _daPathElementWidthPoint ; 
      
    // To select the third point
    // This point is on a line which is perpendicular to the axe define 
    // by the line between the Corner Point and the Width Point
    // The lenght between the Corner Point and the Depth Point 
    // defines the depth of the Box.
    CATIndicationAgent   * _daIndicationDepthPoint ;
    
    // To select the forth point
    // This point is on a line which is perpendicular to the axe define 
    // by the line between the Corner Point and the Width Point
    // The lenght between the Corner Point and the Height Point 
    // defines the height of the Box.
    CATIndicationAgent   * _daIndicationHeightPoint ;
    
    // Lines and points to visualize temporarely the Box in Wireframe
    CATISO               * _pISO ;
    CAAISysLine          * _apiTemporaryV[3]; 
    CAAISysPoint         * _apiTemporaryP[2] ;
      
    // Viewpoint at the beginning of the Command 
    // This VP is restored at the end ( Cancel Method )
    CATICamera           * _piCamera ;
    
    // To create an element in a document
    CATBaseUnknown      * _pUIActiveObject    ;   
    CATBaseUnknown      * _pContainer     ; 

    // To manage the current choice to create the box in the Palette
    int                            _CurrentBoxCreationTypeChoice ;

    // The class instances to access the check header instances set in 
    // the palette
    //
    CATAfrCheckHeaderAccessor    * _pTwoPointsCmdHdr ;
    CATAfrCheckHeaderAccessor    * _pThreePointsCmdHdr ;
    CATAfrCheckHeaderAccessor    * _pFourPointsCmdHdr ;
    CATAfrCheckHeaderAccessor    * _pOriginCheckHdr ;
};
#endif
