// COPYRIGHT Dassault Systemes 2000
//===================================================================
//
// CAAAniADImport.cpp
// Provide implementation to interface CATISamImport
// Sample of code for managing Analysis data for Aero Dynamic.
// Import of Preprocessing data inside the CATAnalysis.
//  Temporary solution ..
//===================================================================
#include "CAAAniADImport.h"                 // Local Include

/// AnalysisMeshingModel
#include "CATIMSHMeshManager.h"             // Mesh Feature in the TREE
#include "CATIMSHMeshPart.h"                // Mesh part creation
#include "CATIMSHMesh.h"                    // Mesh part creation
#include "CATIMSHMeshDomain.h"              // Mesh part creation
#include "CATMSHNode.h"
#include "CATMSHElement.h"
#include "CATIMSHConnectivity.h"
#include "CATMSHConnectivityServices.h"
#include "CATSamDocumentTools.h"


// Field model (CATAnalysisBase)      
#include "CATAnalysisExplicitModel.h"      // Field Model Access
#include "CATAnalysisExplicitRulesData.h"  // Field Model Access
#include "CATAnalysisExplicitSet.h"        // Field Model Set Access
#include "CATAnalysisExplicitElement.h"    // Field Model Entity Access
#include "CATAnalysisExplicitNode.h"       // Field Model Node Entity Access
#include "CATAnalysisExplicitListUsr.h"    // Field Model List Access
// CATAnalysisInterfaces
#include "CATISamAccess.h"                 // Get AnalysisContainer
#include "CATISamAnalysisContainer.h"      // AnalysisContainer
#include "CATISamAnalysisModelFactory.h"
#include "CATISamAnalysisScan.h"           // Get Set in a case
#include "CATISamAnalysisManager.h"        // Get Analysis Model
#include "CATISamDocumentManager.h"        // Get DocumentManager 
#include "CATISamAnalysisModel.h"          // CATISamAnalysisModel
#include "CATISamAnalysisCase.h"           // CATISamAnalysisCase
#include "CATISamExplicit.h"               // Field model Bridge
#include "CATISamAnalysisSet.h"
#include "CATISamBasicComponent.h"
#include "CATSamDocNotification.h"
#include "CATSamTransitionSetup.h"

// Object Modeler & ObjectSpecModeler
#include "CATISpecObject.h"                // Update method
#include "CATIContainer.h"                 // SamAccess result
#include "CATDocumentServices.h"           // Document management
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATILinkableObject.h"
#include "CATLib.h"
#include "CATIClientContainer.h"

#include "iostream.h"

CATImplementClass( CAAAniADImport,
                   DataExtension,
                   CATBaseUnknown,
                   fif);
 
//-----------------------------------------------------------------------------
// CAAAniADImport : constructor
//-----------------------------------------------------------------------------
CAAAniADImport::CAAAniADImport(): CATBaseUnknown()
{}
//-----------------------------------------------------------------------------
// CAAAniADImport : destructor
//-----------------------------------------------------------------------------
CAAAniADImport::~CAAAniADImport()
{}
//================================================================================ 
// Tie the implementation to its interface
// ----------------------------------------
#include "TIE_CAAIAniAeroImport.h"
TIE_CAAIAniAeroImport(CAAAniADImport);

//=================================================================================================
// Implements CATISamImport::Import
// Input argument
//                idocument  : Current CATAnalysis for import
//=================================================================================================
HRESULT CAAAniADImport::Import (CATDocument * idocument)
{
	HRESULT hr = S_OK;
//=================================================================================================
// Get the Analysis Container
//=================================================================================================
	CATISamAccess_var  spSamAccess (idocument);
	if( NULL_var == spSamAccess) return E_FAIL;
  CATIContainer     *piSpecContainer=NULL;
	CATISamAnalysisContainer_var spAnalysisContainer ;
  CATDocument *pDocToLink = NULL;

  hr = spSamAccess -> GetSpecContainer(piSpecContainer) ;
	CATISamAnalysisModelFactory_var spFactory;
	if (NULL == piSpecContainer) return E_FAIL;

  // Test if the solution is already created On the SamContainer of CATAnalysis Document.
  CATIClientContainer_var spContClient (piSpecContainer);
  if (NULL_var != spContClient) 
  {
    CATListPtrCATBaseUnknown* pLst = NULL;
    CATUnicodeString ClientID ("CAAAniCatalog");
    spContClient -> ListMembers(IID_CATISpecObject,ClientID,&pLst);
    if (NULL == pLst || NULL ==  pLst -> Size())  CATSamTransitionSetup(idocument,"AeroDynamic");
    if (pLst) {
      for ( int j = 1; j <= pLst -> Size(); j++ ) {
        CATBaseUnknown * pCbu = (*pLst)[j];
        if (pCbu) pCbu -> Release();
      }
      delete pLst ; pLst = NULL;
    }

  }
	spAnalysisContainer = piSpecContainer ;
  spFactory           = piSpecContainer ;
	piSpecContainer -> Release();  piSpecContainer = NULL;

  if (NULL_var == spAnalysisContainer) return E_FAIL;

//=================================================================================================
// Get the AnalysisManager
//=================================================================================================
	CATISamAnalysisManager_var   spAnalysisManager ;
  hr = spAnalysisContainer->GetAnalysisManager(spAnalysisManager) ;
	if (FAILED(hr)) return E_FAIL;
//=================================================================================================
// Get the DocumentManager To plug the document.
//=================================================================================================
	CATISamDocumentManager_var   spDocManager ;
  hr = spAnalysisManager ->GetDocumentManager(spDocManager) ;
	if (FAILED(hr)) return E_FAIL;
//
  CATISpecObject * piLink= NULL;
// Create an analysis link to link the file and insert this in the document manager to the external file
	if (NULL_var != spDocManager)
	{
    if (NULL_var != spFactory)  piLink = spFactory -> CreateAnalysisLink("fif","SAMFeatureLinkFile");

    pDocToLink = GetDocument();
		if (NULL != pDocToLink)     spDocManager ->InsertDocument(pDocToLink,"fif",piLink);
	}
//=================================================================================================
// Get the AnalysisModel to extract the Field model Sets 
// They are retireved by getting the CATISamExplicit implementation on the 
// Feature Sets.
//=================================================================================================
	CATISamAnalysisScan_var     spScan;
	CATIMSHMeshManager * piManager  = NULL;
	CATISpecObject* piAnalysisModel = NULL;
// Retreive the AnalysisModel
  hr = spAnalysisManager ->GetCurrentModel(piAnalysisModel);
	if (NULL != piAnalysisModel) 
	{
		CATISamExplicit *piExplicitFeat = NULL;
		CATISamAnalysisModel *piAnalysisMod = NULL ;
		piAnalysisModel -> QueryInterface(IID_CATISamAnalysisModel,(void**)&piAnalysisMod);
		if (NULL != piAnalysisMod)
		{
// Retreive the Case created in the transition and its field modele version
			CATISamAnalysisCase* piFoundCase = NULL; 
			piAnalysisMod->GetNamedCase("Aero Case",piFoundCase);
			if (piFoundCase)
			{
				spScan = piFoundCase;
				piFoundCase-> Release();
				piFoundCase=NULL;
			}
// Retreive the CATIMSHMeshManager associated to the Anlysis Model.
			CATBaseUnknown* piBaseMesh=NULL;
			piAnalysisMod->GetMesh(piBaseMesh);
			if (piBaseMesh!= NULL) 
			{
				piBaseMesh -> QueryInterface(IID_CATIMSHMeshManager,(void**)&piManager);
				piBaseMesh -> Release();
				piBaseMesh =  NULL;
			}
			piAnalysisMod -> Release();
			piAnalysisMod =  NULL;
		}
		piAnalysisModel-> Release();
		piAnalysisModel=NULL;
	}
//
	if (piManager == NULL ) return E_NOINTERFACE;
//==========================================================================
// Create the MeshPart associated to the import.
	CATIMSHMeshPart* piMshPart = piManager -> CreateMeshPart("AeroMeshPart");

	if (piMshPart && piLink) 
	{
		CATISpecAttrAccess* piMPAc = NULL;
    piMshPart -> QueryInterface (IID_CATISpecAttrAccess,(void **)&piMPAc);
		if (NULL != piMPAc)
    {
   		CATISpecAttrKey* Key = piMPAc -> GetAttrKey("InputLink");
      if (NULL != Key)
      {
        piMPAc -> SetSpecObject(Key,piLink);
        Key    -> Release();
      }
      piMPAc -> Release();
    }
		CATILinkableObject *piLinka = NULL;
		piLink -> QueryInterface(IID_CATILinkableObject,(void **)&piLinka);
    if (piLinka)
    {
      piMshPart -> SetSupport (NULL,piLinka);
      piLinka   -> Release();
    }
  }
  if (NULL != piMshPart) piMshPart -> Release();
  if (NULL != piLink)    piLink -> Release();
//=================================================================================================
	if (piManager) piManager -> Release(); piManager = NULL;
//=================================================================================================

// Feature Validation 
	if (NULL_var != spScan)
	{
		CATLISTV(CATBaseUnknown_var) oSetsList = NULL;
		spScan ->GetTypedSet("AeroDynamicSet",oSetsList);
		if (oSetsList.Size())
		{
			CATISamAnalysisSet_var spSamSet(oSetsList[1]);
			if (NULL_var != spSamSet && pDocToLink) 
			{
				char Dir [CATMaxPathSize];
        CATUnicodeString DocPath;
	      if (pDocToLink) CATSamDocumentTools::GetFileStorage(pDocToLink,DocPath);

        char FileName[80];
				CATSplitPath (DocPath.ConvertToChar(),Dir,FileName);
				char OutFileName[1024];
				CATMakePath (Dir,"Car1_dp.print",OutFileName); 
				CATDocument *DocResult = NULL;

        hr = CATDocumentServices::OpenDocument(OutFileName,DocResult);
				if (DocResult)
				{
          CATISamBasicComponent_var spComponent;
          spSamSet -> GetNamedBasicComponent("ANIFileLink",spComponent);
          if (NULL_var != spComponent) spComponent -> 
                          SetBaseUnknownValue((CATBaseUnknown_var)(DocResult),"ExternDoc");
				}
        CATISpecObject_var spSpecOnSet (spSamSet);
				if (NULL_var != spSpecOnSet) spSpecOnSet -> Update();
			}
		}
	}
	
	CATCallback RenameCB = ::AddCallback ( this , idocument , "CATSamDocNotification" ,
                              (CATSubscriberMethod)&CAAAniADImport::OnRenameCB );

	CATCallback RenameCB2 = CATSamDocumentTools::AddRenameCB(pDocToLink, idocument, (CATSubscriberMethod)&CAAAniADImport::OnRenameCB2);
	
	return S_OK;
}

//=================================================================================================
// Input argument
//                piMeshPart : MeshPart using this mesher
//                piMesh     : Current CATIMSHMesh for mesh creation
//=================================================================================================
HRESULT CAAAniADImport::ImportFif (CATIMSHMeshPart * piMeshPart,
                                   CATIMSHMesh * piMesh)
{
//=================================================================================================
  if (NULL == piMesh || NULL == piMeshPart ) return E_FAIL;
  CATDocument * pThisDoc = GetDocument();
  CATUnicodeString StorageIdent;

  CATSamDocumentTools::GetFileStorage(pThisDoc,StorageIdent);
  if ( 0 == StorageIdent.GetLengthInChar()) return E_FAIL;

  CATISamExplicit_var spExplicit = piMeshPart;
  if (NULL_var == spExplicit) return E_NOINTERFACE;

  const CATAnalysisExplicitModel *pExplModel = spExplicit->GetExplicitModel();
  if (NULL == pExplModel) return E_FAIL;
  const CATAnalysisExplicitRulesData *pRulesData = pExplModel->GetRulesData();
  if (NULL == pRulesData) return E_FAIL;
  

  // Physical type of elements
  CATIMSHConnectivity *  pConnect   = NULL;
  CATMSHMeshDomain * pdomain = piMesh -> CreateMeshDomain (piMeshPart);
  if (NULL == pdomain) return E_FAIL;
  
	int max = 30000,NbNodes=0;
	char buffer [100];

// Open the file
	FILE * stream = fopen (StorageIdent.ConvertToChar(),"r");
// Look after the GRID cards  for node extraction.

	while (fgets (buffer,100,stream))
	{
		if (!strncmp (buffer,"GRID ",5)) break;
	}

  // processing NODE cards  

	int lAlloc = max;
	double * xyz = new double [3*lAlloc];
	int * ind = new int [max];

	while (!strncmp (buffer,"GRID ",5))
	{
		int num;
		double x , y , z;
    sscanf ( buffer+8 ,"%d",&num);
    sscanf ( buffer+24,"%lf%lf%lf",&x,&y,&z);

// Check allocation length
	    if (NbNodes == lAlloc)
		{
			int newmax = 2 * lAlloc;
			double * newxyz = new double [3*newmax];
			memcpy (newxyz,xyz,3*NbNodes*sizeof(double));
      delete [] xyz;
			xyz = newxyz;
			lAlloc = newmax;
		}
		if (num > max)
		{
			int newmax = 2 * max;
			if ( num > newmax ) newmax = num;
		    int * newind = new int [newmax];
		    int noct = max * sizeof (int);
			memcpy (newind,ind,noct);
		    delete [] ind;
			ind = newind;
			max = newmax;
		}

		ind[num-1]        = NbNodes;
    xyz[3*NbNodes]   = x;
		xyz[3*NbNodes+1] = y;
		xyz[3*NbNodes+2] = z;

		NbNodes++;
		if (!fgets(buffer,100,stream)) 
			break;
	 }

  // Node Creation inside the Mesh container
	CATMSHNode ** Nodes = new CATMSHNode * [NbNodes];
	piMesh -> CreateNodes (xyz,NbNodes,Nodes);

	if (xyz) delete [] xyz; xyz= NULL;
// Find Element Cards
  if (buffer[0] != 'C')
	  while (fgets (buffer,100,stream))
	  {
	    if (buffer[0] == 'C') break;
	  }

// Cards beginning with Cxxxx
// This file should contain Triangle and Quad
	int n1 , n2 , n3 , n4;
	int jQD4=0;
	int jTR3=0;
	int nbelemQD4 = 0;
	int nbelemTR3 = 0;
	CATMSHNode ** linkednodesQD4 = new CATMSHNode * [4*max];
	CATMSHNode ** linkednodesTR3 = new CATMSHNode * [3*max];

	while (buffer[0] == 'C')
	{
		if (!strncmp(buffer,"CQUAD4 ",7))
		{
			sscanf (buffer+24,"%d%d%d%d",&n1,&n2,&n3,&n4);
			nbelemQD4 ++;
			linkednodesQD4[jQD4++] = Nodes[ind[n1-1]]; 
			linkednodesQD4[jQD4++] = Nodes[ind[n2-1]];
			linkednodesQD4[jQD4++] = Nodes[ind[n3-1]];
			linkednodesQD4[jQD4++] = Nodes[ind[n4-1]];
	    }
		else if (!strncmp (buffer,"CTRIA3 ",7))
		{
			sscanf (buffer+24,"%d%d%d",&n1,&n2,&n3);
			nbelemTR3 ++;
			linkednodesTR3[jTR3++] = Nodes[ind[n1-1]];
			linkednodesTR3[jTR3++] = Nodes[ind[n2-1]];
			linkednodesTR3[jTR3++] = Nodes[ind[n3-1]];
		}
		if (!fgets(buffer,100,stream)) break;
	}

	if (nbelemQD4)
	{
    pConnect = CATMSHConnectivityServices::GetConnectivity("QD4");
		piMesh -> CreateElements(pConnect,4,linkednodesQD4,nbelemQD4);
	}
	if (nbelemTR3)
	{
    pConnect = CATMSHConnectivityServices::GetConnectivity("TR3");
		piMesh -> CreateElements (pConnect,3,linkednodesTR3,nbelemTR3);
	}

	if (stream) fclose (stream);
// reset Allocations !
	if (ind)           delete [] ind;           ind=NULL;
	if (linkednodesQD4)delete [] linkednodesQD4;linkednodesQD4=NULL;
	if (linkednodesTR3)delete [] linkednodesTR3;linkednodesTR3=NULL;
  if (Nodes)         delete [] Nodes;         Nodes=NULL;
  return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATISamExplicit::Explicit
//-----------------------------------------------------------------------------
HRESULT CAAAniADImport::TranslateToFieldModel(CATISpecObject* iFeatToTranslate, CATISamAnalysisModel* iFEMModel, 
                                              CATAnalysisExplicitListUsr& iOldExplObjects, 
                                              CATAnalysisExplicitListUsr& oNewExplObjects)
{
  HRESULT hr = S_OK;

// Retrieve the field model pointer and RulesData
  const CATAnalysisExplicitModel *pExplModel = iOldExplObjects.GetModel();
  if (NULL == pExplModel) return E_FAIL;
  const CATAnalysisExplicitRulesData *pRulesData = pExplModel->GetRulesData();
  if (NULL == pRulesData) return E_FAIL;
  int Nbelem(0),NbMeshNode(0),i;
  CATMSHElement** Elements = NULL;
  CATMSHNode * Node = NULL,* MkcsNode = NULL;
  CATMSHElement* MkcsElement = NULL;
  char* Enti = NULL;
  CATIMSHConnectivity * Ref_connect = NULL;
  CATIMSHMesh* piMesh = NULL;

  CATISamExplicit_var spExplicit = iFeatToTranslate;
  if ( NULL_var == spExplicit ) return E_NOINTERFACE;

  CATIMSHMeshPart_var spMeshPart = iFeatToTranslate;
  if ( NULL_var == spMeshPart ) return E_NOINTERFACE;

  CATAnalysisExplicitListUsr ContainingData ;
  CATAnalysisExplicitSet MeshSet,NodeSet, ElemSet;
  CATAnalysisExplicitNode ExpNode;
  CATAnalysisExplicitElement ExpElement; 


  ContainingData.CreateList(pExplModel) ;
  spExplicit -> GetContainingData(iOldExplObjects, ContainingData) ;

// Physical type for Node & Element behavior
	CATSamPhysicalType NODES,ELEMENTS,MESH,QD4,TR3;
  pRulesData->GetPhysicalTypeNumber("NODES",NODES);
  pRulesData->GetPhysicalTypeNumber("ELEMENTS",ELEMENTS);
  pRulesData->GetPhysicalTypeNumber("MESH",MESH);
  pRulesData->GetPhysicalTypeNumber("ELEMENT_DRAWING_QUAD4",QD4);
  pRulesData->GetPhysicalTypeNumber("ELEMENT_DRAWING_TRIA3",TR3);


  MeshSet.CreateSet(pExplModel,MESH);
  oNewExplObjects += MeshSet;
  NodeSet.CreateSet(MeshSet,NODES);
  ElemSet.CreateSet(MeshSet,ELEMENTS);
//====================================================================================	
	Nbelem = spMeshPart -> GetElements(Elements);
  if ( Nbelem <= 0) goto NoMesh; // remove Mesh

  if (Elements)  {
    MkcsElement = Elements[0];
    if (MkcsElement) piMesh = MkcsElement -> GetMesh();
  }
  if (! piMesh) return E_FAIL;
  NbMeshNode = piMesh -> GetNumberOfNodes () ;
  if (NbMeshNode) 
  {
    Enti = new char [NbMeshNode];
    if( Enti) memset(Enti,0,NbMeshNode) ; 
  }

  for (i = 0 ; i < Nbelem ; i++)
  {
    MkcsElement = Elements[i];
    if (!MkcsElement) continue;
    int NbNode = (MkcsElement) -> GetNumberOfLinkedNodes();
    if (NbNode)
    {
      CATMSHNode * const * LinkedNodes = (MkcsElement) -> GetLinkedNodes () ;
      for (int j = 0 ; j < NbNode ; j++)  {
        MkcsNode  = LinkedNodes[j];
        if (MkcsNode) Enti[MkcsNode -> GetNumber()] = 1;
      }
    }

    ExpElement.LinkWithMeshPointer(MkcsElement,pExplModel);
    if (ExpElement != NULL_exp) 
      ElemSet.AddChild(ExpElement);
    else 
    {
      Ref_connect = MkcsElement -> GetConnectivity();
      if (Ref_connect) {
        const char * c_connectivity = Ref_connect -> GetName();
        if (c_connectivity) {
          if (strcmp(c_connectivity, "QD4") == 0)
            ExpElement.CreateElement(ElemSet,MkcsElement,QD4);
          else if (strcmp(c_connectivity, "TR3") == 0)
            ExpElement.CreateElement(ElemSet,MkcsElement,TR3);
        }
      }
    }
  }

  i = 0;
  Node = piMesh ->GetFirstNode ();
  while ( Node )
  {
    if (Enti[i])
    {
      ExpNode.LinkWithMeshPointer(Node,pExplModel);
      if (ExpNode == NULL_exp) ExpNode.CreateNode(NodeSet,Node);
      else                     NodeSet.AddChild(ExpNode);
    }
    Node = Node -> Next ();
    i ++;
  }


NoMesh:

  hr = spExplicit -> UpdateExplicitList(iOldExplObjects, ContainingData, oNewExplObjects) ;
  if (ContainingData != NULL_exp)  ContainingData.Delete() ;
  if (piMesh) piMesh -> Release(); piMesh = NULL;
  if (Enti) delete [] Enti; Enti = NULL;
  if (Elements) delete [] Elements; Elements= NULL;

  return hr;
}
//============================================================================================================
CATDocument * CAAAniADImport::GetDocument()
{
  CATDocument * pDocToLink = NULL;
  CATILinkableObject *piLinka = NULL;
  QueryInterface(IID_CATILinkableObject,(void **)&piLinka);
  if (NULL != piLinka)
  {
    pDocToLink = piLinka -> GetDocument();
    piLinka -> Release();
  }
  return pDocToLink;
}
//=======================================================================================
void CAAAniADImport::OnRenameCB(CATCallbackEvent,void*,CATNotification *notif,
                                    CATSubscriberData,CATCallback)
{ 
  CATSamDocNotification * pNotif = (CATSamDocNotification *) notif;
  if ( !pNotif ) return;
  CATSamDocActionType type = pNotif -> GetActionType ();
  if (type != SamRename) return;

  cout<<"GiveOldName " <<(pNotif->GiveOldName()).ConvertToChar()  <<endl;
  cout<<"GiveNewName " <<(pNotif->GiveNewName()).ConvertToChar() <<endl;
  
  return;
}
//=======================================================================================
void CAAAniADImport::OnRenameCB2(CATCallbackEvent,void*,CATNotification *notif,
                                    CATSubscriberData,CATCallback)
{ 
  CATSamDocNotification * pNotif = (CATSamDocNotification *) notif;
  if ( !pNotif ) return;
  CATSamDocActionType type = pNotif -> GetActionType ();
  if (type != SamRename) return;

  cout<<"GiveOldName2 " <<(pNotif->GiveOldName()).ConvertToChar() <<endl;
  cout<<"GiveNewName2 " <<(pNotif->GiveNewName()).ConvertToChar() <<endl;
  
  return;
}
//=======================================================================================

