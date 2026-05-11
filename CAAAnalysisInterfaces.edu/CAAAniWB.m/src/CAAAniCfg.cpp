// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
#include "CAAAniCfg.h"
#include "CATCommandHeader.h"                  // New Class Of command Header
MacDeclareHeader (AniCommandHeader);             
#include "CATCreateWorkshop.h"                 // ApplicationFrame Macros
#include "CATAfrCommandHeaderServices.h"

#include "CAAIAniAddin.h"

CATImplementClass(CAAAniCfg, Implementation, CATBaseUnknown, CATNull);
//===================================================================================
#include "TIE_CATISAMWorkshopConfiguration.h"
TIE_CATISAMWorkshopConfiguration(CAAAniCfg);
//===================================================================================
CAAAniCfg::CAAAniCfg()
{}
//===================================================================================
CAAAniCfg::~CAAAniCfg()
{}
//===================================================================================
void CAAAniCfg::CreateCommands()
{

  CATCommandHeader* PHeader = NULL;
  CATAfrGetCommandHeader( "CATSamDumpFieldModel",PHeader); 
  if (NULL == PHeader) CATAfrCreateCommandHeader( "CATSamDumpFieldModel");

//  new AniCommandHeader ("EXPLHeaderDumpFieldModel","CATSAMExplicitUITools","CATSamCmdDumpModel", // Old way
//                       (void *) NULL );

  new AniCommandHeader ("SAMHeaderGenerateImage","CATAV0UI" ,"CATSPMGenerateImageCmd",
						     (void *) NULL );

  static CATUnicodeString Solution("AeroDynamicSet");
  new AniCommandHeader ( "CAAAniInsertCase" , "CATAnalysisModelerUI" , "CATSamCreateCaseCmd"  ,
  (void *) &Solution);

  static CATUnicodeString Entity1Type = "AniEntityOnSolution";
  new AniCommandHeader ( "CreateEnti1","CATAnalysisModelerUI","CATSamCreateEntityCmd" ,
                       (void *)&Entity1Type );
  static CATUnicodeString Entity2Type = "AniSpeedLoad";
  new AniCommandHeader ( "CreateEnti2","CATAnalysisModelerUI","CATSamCreateEntityCmd" ,
                       (void *)&Entity2Type );

  static CATUnicodeString createOneImage = "createOneImage";
  new AniCommandHeader ( "CreateOneImage","CAAAniWB","CAAAniCreateOneImageCmd" ,
                       (void *)&createOneImage );

  static CATUnicodeString  CreateAFreeGroup = "ANIFreeGroupEntityTst";
  new AniCommandHeader ( "CreateAFreeGroup" , "CATAnalysisModelerUI" , "CATSamCreateEntityCmd" ,
                      (void *)&CreateAFreeGroup );

  static CATUnicodeString  CreateAClamp = "ANISymetricalTensorEntityTst";
  new AniCommandHeader ( "CreateClamp" , "CATAnalysisModelerUI" , "CATSamCreateEntityCmd" ,
                      (void *)&CreateAClamp );

  static CATUnicodeString ExportInVB = "ExportInVB";
  new AniCommandHeader ( "ExportInVB","CAAAniWB","CAAAniExportCmd",(void *)&ExportInVB );

  static CATUnicodeString  SelectNode = "CAAAniSelectNode";
  new AniCommandHeader ("SelectNode","CAAAniWB","CAAAniSelectNodeCmd" ,(void *) &SelectNode );

}

//===================================================================================

CATCmdWorkbench* CAAAniCfg::CreateWorkbench()
{
// CAAAniCfg Workbench layout
  NewAccess(CATCmdWorkbench,pCAAAniWkb,CAAAniCfg);
  
// New Toolbar 
	NewAccess(CATCmdContainer,pAniTlb01,CATNewToolBar001Tlb);
	SetAccessChild(pCAAAniWkb,pAniTlb01);

// 1th commmand: Dump field model
		NewAccess(CATCmdStarter,pDumpModel,CATSamCmdDumpModel);
		SetAccessCommand(pDumpModel,"CATSamDumpFieldModel");
		SetAccessChild(pAniTlb01,pDumpModel);
 
// 2th commmand: Generate an image
		NewAccess(CATCmdStarter,pCreateImage,CreateImage);
		SetAccessCommand(pCreateImage,"SAMHeaderGenerateImage");
		SetAccessNext		( pDumpModel , pCreateImage );

// 3th commmand: Generate an Analysis Entity
		NewAccess(CATCmdStarter,pCreateEntity1,CreateEntity1);
		SetAccessCommand(pCreateEntity1,"CreateEnti1");
		SetAccessNext		( pCreateImage , pCreateEntity1 );

// 4th commmand: Generate an Analysis Entity
		NewAccess(CATCmdStarter,pCreateEntity2,CreateEntity2);
		SetAccessCommand(pCreateEntity2,"CreateEnti2");
		SetAccessNext		( pCreateEntity1 , pCreateEntity2 );

// 5th commmand: Generate a specific image
		NewAccess(CATCmdStarter,pCreateOneImage,CreateOneImage);
		SetAccessCommand(pCreateOneImage,"CreateOneImage");
		SetAccessNext		( pCreateEntity2 , pCreateOneImage );

// 6th commmand: Generate a free group
		NewAccess(CATCmdStarter,pCreateAFreeGroup,CreateAFreeGroup);
		SetAccessCommand(pCreateAFreeGroup,"CreateAFreeGroup");
		SetAccessNext(pCreateOneImage, pCreateAFreeGroup);

// 7th commmand: Generate a symmetrical tensor with the behaviour of the clamp
		NewAccess(CATCmdStarter,pCreateAClamp,CreateAClamp);
		SetAccessCommand(pCreateAClamp,"CreateClamp");
		SetAccessNext(pCreateAFreeGroup, pCreateAClamp);

		NewAccess(CATCmdStarter,pExportInVB,ExportInVB);
		SetAccessCommand(pExportInVB,"ExportInVB");
		SetAccessNext		( pCreateAClamp , pExportInVB );

		NewAccess(CATCmdStarter,pSelectNode,SelectNode);
		SetAccessCommand(pSelectNode,"SelectNode");
		SetAccessNext		( pExportInVB , pSelectNode);

// Visible toolbar
	AddToolbarView(pAniTlb01,1,Right);

    
//---------------------------------
//  Insert menu: New Insert Case to merge 
//---------------------------------
    NewAccess(CATCmdContainer,pCAAAAniInsertMbr,CAAAniInsertMbr);
    NewAccess(CATCmdContainer,pCATAfrInsertMnu,CATAfrInsertMnu);
    SetAccessChild(pCAAAAniInsertMbr,pCATAfrInsertMnu);

    NewAccess(CATCmdStarter,pCAAAniInsertCase,CAAAniInsertCase);
    SetAccessCommand(pCAAAniInsertCase,"CAAAniInsertCase");
    SetAccessChild(pCATAfrInsertMnu,pCAAAniInsertCase);

    SetWorkbenchMenu(pCAAAniWkb, pCAAAAniInsertMbr);
// End InsertMenu.
  return pCAAAniWkb;

}
//===================================================================================

CATClassId CAAAniCfg::GetAddinInterface()
{
	return CAAIAniAddin::ClassName();
}
//===================================================================================

void CAAAniCfg::GetCustomInterfaces(CATListPV * DefaultIIDList,
								                    CATListPV * CustomIIDList)
{
}
//===================================================================================

