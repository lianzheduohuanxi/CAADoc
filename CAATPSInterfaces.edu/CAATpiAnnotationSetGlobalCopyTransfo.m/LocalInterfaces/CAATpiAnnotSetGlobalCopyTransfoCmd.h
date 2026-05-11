// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//  Abstract of the sample:
//  ----------------------
//   
//  Interactive command
//
//    Command to select a geometry and then create a 3D annotation text linked 
//    on selection.
//
//  Illustrates:
//
//    Using TPS (Technological Product Specifications) interfaces to create a
//    3D Text Annotation. The main API used here is CATITPSFactoryAdvanced.
//
//=============================================================================
//  Usage:
//  ------
//
//  Build the fw containing that command and create run time view.
//  Start CATIA V5
//  Menu Start + Mechanical Design + Functional Tolerancing & Annotations
//  Menu : View + Toolbar + CAA Samples to make the toolbar appear.
//  "Create Text" command can be launched from the toolbar.
//
//  Notice that the toolbar CAA Samples is also available in the following 
//  workbenches :
//   Mechanical Design + Product Fonctionnal Tolerancing & Annotation
//   DPM Powertrain + Process Tolerancing & Annotation
//
//=============================================================================

#ifndef CAATpiAnnotSetGlobalCopyTransfoCmd_H
#define CAATpiAnnotSetGlobalCopyTransfoCmd_H

#include "CATStateCommand.h"

class CATPathElementAgent;
class CATIPrtPart;

//-----------------------------------------------------------------------------
class CAATpiAnnotSetGlobalCopyTransfoCmd : public CATStateCommand
{
  CmdDeclareResource(CAATpiAnnotSetGlobalCopyTransfoCmd, CATStateCommand)

  public:

    CAATpiAnnotSetGlobalCopyTransfoCmd ();
    virtual ~CAATpiAnnotSetGlobalCopyTransfoCmd ();

    virtual void BuildGraph();

    boolean LaunchGlobalCopy (void * ipData);

  private:
    // must not be implemented for command
    CAATpiAnnotSetGlobalCopyTransfoCmd (CAATpiAnnotSetGlobalCopyTransfoCmd &);
    CAATpiAnnotSetGlobalCopyTransfoCmd& operator=(CAATpiAnnotSetGlobalCopyTransfoCmd&);

    void LaunchWarningPanel();

    CATPathElementAgent * _pAgentAnnotationSet;
};
#endif


