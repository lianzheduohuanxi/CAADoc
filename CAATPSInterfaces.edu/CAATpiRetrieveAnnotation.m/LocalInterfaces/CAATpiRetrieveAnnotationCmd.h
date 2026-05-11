// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//  Abstract of the sample:
//  ----------------------
//   
//  Interactive command
//
//    Command to select a geometry and then retrieve and highlight all
//    3D annotations which are applied on selected geometry.
//
//  Illustrates:
//
//    Using TPS (Technological Product Specifications) interfaces to retrieve
//    annotations and tolerances linked to a geometry. The main APIs used here
//    are CATITPSRetrieveServices and CATIBuildPath.
//
//=============================================================================
//  Usage:
//  ------
//
//  Build the fw containing that command and create run time view.
//  Start CATIA V5
//  Menu Start + Mechanical Design + Functional Tolerancing & Annotation
//  Menu : View + Toolbar + CAA Samples to make the toolbar appear.
//  "Retrieve Annotation" command can be launched from the toolbar.
//
//  Notice that the toolbar CAA Samples is also available in the following 
//  workbenches :
//   Mechanical Design + Product Fonctionnal Tolerancing & Annotations
//   DPM Powertrain + Process Tolerancing & Annotations
//
//=============================================================================

#ifndef CAATpiRetrieveAnnotationCmd_H
#define CAATpiRetrieveAnnotationCmd_H

#include "CATStateCommand.h"

class CATPathElementAgent;
class CATDialogAgent;
class CAATpiRetrieveAnnotationWnd;

//-----------------------------------------------------------------------------
class CAATpiRetrieveAnnotationCmd : public CATStateCommand
{
  CmdDeclareResource (CAATpiRetrieveAnnotationCmd, CATStateCommand)

  public:

    CAATpiRetrieveAnnotationCmd ();
    virtual ~CAATpiRetrieveAnnotationCmd ();

    virtual void BuildGraph ();

    boolean SomethingSelected (void * ipData);

  private:
    // must not be implemented for command
    CAATpiRetrieveAnnotationCmd (CAATpiRetrieveAnnotationCmd &);
    CAATpiRetrieveAnnotationCmd& operator=(CAATpiRetrieveAnnotationCmd&);

    CATPathElementAgent         * _pSelectionAgent;
    CATDialogAgent              * _pClosePanelAgent;
    CAATpiRetrieveAnnotationWnd * _pPanel;

};
#endif


