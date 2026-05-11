#ifndef CAADegCreatePlaneCmd_h
#define CAADegCreatePlaneCmd_h

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
//  State command which creates a plane from three selected points.
//
//  Illustrates:
//
//     - Creation of a State command
//     - Use of a CATPathElementAgent several times
//     - Use of the CATCSO (Set of Current Objects)
//          
//  Usage:
//
//     Select 3 points ==> The plane is created and becomes 
//                         the current selected object.
//
//  Graph:
//
//     Is composed of 3 states containing the same CATPathElement agent
//     expecting a point.
//     These states are consecutive. One transition enables to progress
//     from one state to the following. 
//     The third transition leaves the third states and reaches the NULL
//     state to end the command. 
//
//       +------------------+
//       !  PointPathAgent  !   
//       +--------+---------+
//                !   RetrievePoint 
//       +--------V---------+
//       !  PointPathAgent  !   
//       +--------+---------+
//                !   RetrievePoint 
//       +--------V---------+
//       !  PointPathAgent  !   
//       +--------+---------+
//                !   CreatePlane
//                V
//               NULL
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATStateCommand (DialogEngine Framework)
//                CATCommand (System Framework)
//                  CATEventSubscriber (System Framework)
//                    CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  BuilGraph    : Implements the state chart
//  RetrievePoint: Retrieves the point coordinates.
//  CreatePlane  : Creates the plane.
//
//===========================================================================
//DialogEngine Framework
#include "CATStateCommand.h"  //Needed to derive from CATStateCommand
//Mathematics Framework
#include "CATMathPoint.h"     //

//DialogEngine Framework
class CATPathElementAgent ;   // DialogEngine Framework

class CAADegCreatePlaneCmd : public CATStateCommand
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAADegCreatePlaneCmd.CATNls 
  //    
  // the beginning of the format of each line in the NLS file is :
  //
  //     CAADegCreatePlaneCmd.
  //
  CmdDeclareResource(CAADegCreatePlaneCmd,CATStateCommand);

  public :

    // Manages the lifecyle of the command.
    //
    CAADegCreatePlaneCmd();
    virtual ~CAADegCreatePlaneCmd(); 
	
    // BuildGraph
    // -----------
    // Implements the statechart. 
    // It is called once, even if the command is in repeat mode
    // 
    //  1- Creates the PathElement Agent 
    //  2- Creates the 3 states (Start, Second, End)
    //  3- Defines a transition from 
    //     3-1 Start to Second State
    //     3-2 Second to End State
    //     3-3 End To Final State 
    //
    virtual void BuildGraph() ;

    // CheckPoint
    // ----------
    // Tests points are not identical.
    //
    CATBoolean  CheckPoint1(void * iUsefulData) ;
    CATBoolean  CheckPoint2(void * iUsefulData) ;
    CATBoolean  CheckPoint3(void * iUsefulData) ;

    // CreatePoint
    // -----------
    // Retrieves from the selected point the CATMathPoint and 
    // saves it in the _aPoint data. It's called for the first and
    // second point.
    //
    CATBoolean  CreatePoint(void * iUsefulData);

    // CreatePlane
    // -----------
    // Retrieves from the last selected point the CATMathPoint and 
    // calls NewPlane to create a new plane in the document.
    //
    CATBoolean  CreatePlane(void * iUsefulData);


  private :

    // Creates a new plane in the document
    void                   NewPlane()  ;

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePlaneCmd(const CAADegCreatePlaneCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADegCreatePlaneCmd & operator = (const CAADegCreatePlaneCmd &iObjectToCopy);

  private :

    // We use the same agent for the 3 selections
    CATPathElementAgent  * _daPathElement ;    

    // CATMathPoint retrieved from the selected point  
    CATMathPoint           _aPoint[3] ;      

    // To create element in the document
    CATBaseUnknown       * _pUIActiveObject ; 
    CATBaseUnknown       * _pContainer ;   

};
#endif
