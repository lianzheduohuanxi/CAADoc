// COPYRIGHT DASSAULT SYSTEMES 2000
// =========================================================================================
// Required methods to perform the Use Case and global variable declaration
// =========================================================================================
class CATDocument ;
class CATISamAnalysisSet_var;
class CATAnalysisCharacCollector;
// =========================================================================================
// Static variable to identify the file to be exported
// =========================================================================================
#include <stdio.h>		    	// System include for traces
#include <iostream.h>           // System include for traces
#include <string.h>             // System include for traces
// =========================================================================================
// Physical type management and predefined physical types ty be used in all methods
// =========================================================================================
#include "CATAnalysisExplicitTypes.h"  // Physical type management
#include "CATAnalysisExplicitModel.h"  //  Access to the physical types.
// =========================================================================================
// Macro for management of error
#define CATSampleError(CODE) \
error :\
   CODE\
	return E_FAIL;
// =========================================================================================
// =========================================================================================
//  MainExport Scan From the CATAnalysis document to the Analysis Sets.
//
//  Input Argument:
//  --------------
//  CATDocument *idocument : Pointer on the current CATAnalysis Document
//  char        *ifile     : Complete path for the ascii file.
// =========================================================================================
HRESULT CAAAniExport(CATDocument *idocument,char* ifile) ;
// =========================================================================================
//  CAAAniExportMesh Export of meshing geometry.
//
//  Input Argument:
//  --------------
//  CATISamAnalysisSet_var    *ihFeatureSet   : Handler on the CATISamAnalysisSet that manage the mesh.
//  CATAnalysisExplicitModel  *iExplicitModel : Pointer on the CATAnalysisExplicitModel.
// =========================================================================================
HRESULT CAAAniExportMesh(FILE *iFile,CATISamAnalysisSet_var    ihFeatureSet,
									CATAnalysisExplicitModel *iExplicitModel) ;
// =========================================================================================
//  CAAAniSelectPhysics Scan the physical information that can be producted by the
//                      analysis set and select some CharacCollector for dumping.
//
//  Input Argument:
//  --------------
//  FILE                      *iFile          : File pointer to generate the print
//  CATAnalysisExplicitModel  *iExplicitModel : Pointer on the CATAnalysisExplicitModel.
//  CATISamAnalysisSet_var    *ihFeatureSet   : Handler on the CATISamAnalysisSet that manage the mesh.
// =========================================================================================
HRESULT CAAAniSelectPhysics (FILE *iFile,CATAnalysisExplicitModel *iExplicitModel,
							 CATISamAnalysisSet_var    ihFeatureSet);
// =========================================================================================
//  CAAAniDumpByGroup Dump characcollector attached to group of entities 
//                    This is for Material, Local Axis , properties.. 
//
//  Input Argument:
//  --------------
//  FILE                      *iFile          : File pointer to generate the print
//  CATAnalysisExplicitModel   * iExplicitModel  : Pointer on the CATAnalysisExplicitModel.
//  int                          iMax Collect    : Size of next array.
//  CATAnalysisCharacCollector **iListCollector  : Array of returned CC pointer
//  CATAnalysisCharacCollector * iGpePerElementCollector : CC pointer that allow to retreive the 
//                                Groupe number associated to a list of FE
// =========================================================================================
HRESULT CAAAniDumpByGroup(FILE *iFile,CATAnalysisExplicitModel *iExplicitModel,
									 int iMaxCollect,
									 const CATAnalysisCharacCollector ** iListCollector,
									 const CATAnalysisCharacCollector *iGpePerElementCollector);
// =========================================================================================
//  CAAAniDumpByFEentity Dump characcollector attached to Finite element entities 
//                       This is for Restraints, Loads, Solution sets.. 
// 
//  Input Argument:
//  --------------
//  FILE                      *iFile          : File pointer to generate the print
//  CATAnalysisExplicitModel   * iExplicitModel  : Pointer on the CATAnalysisExplicitModel.
//  int                          iMax Collect    : Size of next array.
//  CATAnalysisCharacCollector **iListCollector  : Array of returned CC pointer
// =========================================================================================
HRESULT CAAAniDumpByFEentity(FILE *iFile,CATAnalysisExplicitModel *iExplicitModel,
							int iMaxCollect,
							const CATAnalysisCharacCollector **iListCollector);
// =========================================================================================
