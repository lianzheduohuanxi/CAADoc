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

#ifndef CAATpiCreateTextCmd_H
#define CAATpiCreateTextCmd_H

#include "CATStateCommand.h"

class CATITPS;
class CATString;
class CATPathElementAgent;

//-----------------------------------------------------------------------------
class CAATpiCreateTextCmd : public CATStateCommand
{
  CmdDeclareResource (CAATpiCreateTextCmd, CATStateCommand)

  public:

    CAATpiCreateTextCmd( CATString * ipEntityType ) ;
    virtual ~CAATpiCreateTextCmd( ) ;

    virtual void BuildGraph ();

  private:

    boolean CreateTextOnSelection (void * ipData);
    boolean CreateFlagNoteOnSelection (void * ipData);

    void BringSomeTPSUsualModification( CATITPS * ipiNewlyCreatedEntity );
    void RefreshVisualizationAfterFewChange( CATITPS * ipiNewlyCreatedEntity );

    // must not be implemented for command
    CAATpiCreateTextCmd (CAATpiCreateTextCmd &);
    CAATpiCreateTextCmd& operator=(CAATpiCreateTextCmd&);

    CATPathElementAgent * _pAgentGeometry ;
    char                * _FlagNoteExpected ;
};
#endif


