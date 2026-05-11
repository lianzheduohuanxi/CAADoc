// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//  Abstract of the Method:
//  ------------------------
//  This Method illustrates how to extract the meshing informations in order
//  to create an exported file. The format of this file is not DASSAULT SYSTEMES 
//  proprietary and could be change at any time. 
//=============================================================================
//
//  Main Methods:
//  ------------
//  CAAAniExportMesh Meshing informations extraction
//
//  Input Argument:
//  --------------
//  CATISamAnalysisSet_var    *ihFeatureSet   : Handler on the CATISamAnalysisSet that manage the mesh.
//  CATAnalysisExplicitModel  *iExplicitModel : Pointer on the CATAnalysisExplicitModel.
//
//  Return Errors:
//  -------------
//  1 - HRESULT S_OK is every thing is OK E_FAIL Otherwhise.
//
//=============================================================================
#include "CAAAniExport.h"                // Include of the sample
// Analysis Interfaces
#include "CATISamExplicit.h"             // for CATISamExplicit Methods
#include "CATISamAnalysisSet.h"          // for CATISamAnalysisSet Methods
#include "CATAnalysisExplicitNode.h"     // for CATAnalysisExplicitNode Methods
#include "CATAnalysisExplicitElement.h"  // for CATAnalysisExplicitElement Methods
#include "CATAnalysisExplicitTopology.h" // for CATAnalysisExplicitTopology Methods
// AnalysisMeshingModel 
#include "CATIMSHConnectivity.h"         // for CATIMSHConnectivity Methods
//==================================================================================================
//      To convert the nodes coordinates in SI. 
#define CATSAMMODELUNITCOEFFICIENT  0.001 
//==================================================================================================
HRESULT CAAAniExportMesh(FILE*  File,CATISamAnalysisSet_var ihFeatureSet,CATAnalysisExplicitModel *iExplicitModel)
{
  HRESULT             hr = S_OK;
  CATIMSHConnectivity *m_connectivity = NULL;
	int                 icompt,numseq,Nsqt=0,nno=0,ip,lng;
	double              Coor[3];
	char                Ligne[512];

  //==================================================================================================
  // Loocking for the CATISamExplicit implementation from the feature set
  //==================================================================================================
  CATISamExplicit_var ihExplicit = ihFeatureSet;
	if (ihExplicit == NULL_var) return E_NOINTERFACE ;

  //==================================================================================================
  // Loocking for the CATAnalysisExplicitModel from the CATISamExplicit implementation
  //==================================================================================================
  CATAnalysisExplicitModel* pExplicitModel = ihExplicit->GetExplicitModel();
  if (pExplicitModel == NULL) return E_FAIL ;

  //==================================================================================================
  // Loocking for the CATAnalysisExplicitRuleData from the CATAnalysisExplicitModel
  //==================================================================================================
  const CATAnalysisExplicitRulesData* pExplicitRulesData = pExplicitModel->GetRulesData();
  if (pExplicitRulesData == NULL) return E_FAIL ;

  //==================================================================================================
  // Loocking for the CATAnalysisExplicitTopology from the CATAnalysisExplicitModel
  //==================================================================================================
  const CATAnalysisExplicitTopology* pExplicitTopology = NULL;
  pExplicitModel->GetTopology(pExplicitTopology);
  if (pExplicitTopology == NULL) return E_FAIL ;

  //==================================================================================================
  // Get the Nodes from CATAnalysisExplicitTopology 
  //==================================================================================================
  int NbNodes = 0;
  CATAnalysisExplicitNode Node;
  const CATSamExplicitPtr* NodesPtr = NULL;
  pExplicitTopology->GetNbNodes(NbNodes);
  pExplicitTopology->GetNodes(NodesPtr);
  if (NodesPtr == NULL) return E_FAIL ;

  //==================================================================================================
	sprintf (Ligne,"//  \n");
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	sprintf (Ligne,"//  Nodes number and coordinate \n");
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
  //==================================================================================================
  // Loop to extract the nodes coordinates.
  //==================================================================================================
	for (ip = 0, icompt = 0; ip < NbNodes; ip++, icompt++) {
    Node.LinkWithPointer(NodesPtr[icompt], pExplicitModel);
    Node.GetCoordinates(Coor);
    Node.GetSequentialNumber(numseq);
  	// Output
		Ligne[0] = '\0';
		sprintf (Ligne,"Node  %8d %12.3g %12.3g %12.3g \n", numseq,Coor[0],Coor[1],Coor[2]);
		fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	}
	cout << "Nbnode in the database "<< icompt <<endl;

  //==================================================================================================
  // Get the Elements from CATAnalysisExplicitTopology 
  //==================================================================================================
  int NbElements = 0;
  CATAnalysisExplicitElement Element;
  const CATSamExplicitPtr* ElementsPtr = NULL;
  pExplicitTopology->GetNbElements(NbElements);
  pExplicitTopology->GetElements(ElementsPtr);
  if (ElementsPtr == NULL) return E_FAIL ;


  //==================================================================================================
	sprintf (Ligne,"//  \n");
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
	sprintf (Ligne,"//  Element Connectivity and linked Nodes Number\n");
	fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);

  //==================================================================================================
  // Loop to extract the Connectivity and the nodes linked to elements.
  //==================================================================================================
  CATSamExplicitPtr* LinkedNodesPtr = NULL;
	for (ip = 0, icompt = 0; ip < NbElements; ip++, icompt++) {
    Element.LinkWithPointer(ElementsPtr[icompt], pExplicitModel);
    Element.GetSequentialNumber(numseq);
  	// Get element connectivity to extract the name
    Element.GetConnectivity(m_connectivity);
		lng = sprintf (Ligne,"Elem %s %8d ", m_connectivity->GetName(),numseq);
    // Get number of linked Nodes and the linked Nodes
    Element.GetNumberOfLinkedNodes(nno) ;
    Element.GetLinkedNodes(LinkedNodesPtr);
    // Extract the sequential number of each node linked to the element
    for (int in=0; in<nno ; in++) { 
      Node.LinkWithPointer(LinkedNodesPtr[in], pExplicitModel);
      Node.GetSequentialNumber(Nsqt);
			lng += sprintf (Ligne+lng," %6d ",Nsqt);
		}
		Ligne[lng] = '\n';
		fwrite ((char *)Ligne,sizeof(char),lng+1,File);
    delete []LinkedNodesPtr; LinkedNodesPtr = NULL;
	}

    if (pExplicitTopology)  pExplicitTopology->Release(); pExplicitTopology = NULL;
	cout << "Nbelements in the database "<< icompt <<endl;
	return hr;
}
//==================================================================================================
