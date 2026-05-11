// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
// Abstract of Use Case "CAAOsmMainManageExt":
// -------------------------------------------
//
// This sample illustrates how to add extensions within an applicative container, 
// thus extending the data and behavioral capabilities of a base feature.
//
// This sample uses the two existing catalogs containing extensions and created in the
// CAAOsmMainCreateExt use case. It also uses the StartUp catalog created in the
// CAAOsmCatalogSU use case. The execution of these two use cases is, therefore, a
// pre-requisite to this use case.
//
// The StartUp "Novel" whose late type is "Nov" is used as a base feature in this use case.
// In other words, the extensions added in the document will extend an instance of
// this StartUp.
//
// The new document created will contain three applicative containers.  In the first, the "Novel"
// StartUp will be instantiated to create a new feature "Novel1".  This is the base feature.
// In the second applicative container, the two extensions from the first extensions 
// catalog will be added on "Novel1".  Finally, in the third applicative container,
// the extension from the second extensions catalog will be added on "Novel1".  The 
// use case will then show that for "Novel1", three extensions are added from two
// different applicative containers.  Then, the extensions from the second applicative
// container will be removed to show that now, only the one extension from the third
// applicative container remain on "Novel1", thereby illustrating that a feature's
// behavioral and data capabilities is dependant on the existence of a given applicative
// extension.
//
//=============================================================================
//  Main Methods:
//  ------------
//
//  Create_Session: Creates a new session, necessary in a batch program.
//  ManageExtensions: Utility that illustrates working with extensions in a Part document.
//     CATCreateApplicativeContainer: Creates a new applicative container in the current 
//        document.
//     AccessCatalog: Opens an existing catalog.
//     RetrieveSU: Retrieves a StartUp from a catalog.
//     Instanciate: Creates a new feature in the applicative container by instantiating a
//        StartUp
//     AddExtension: Adds an extension in an applicative container.
//     RemoveExtension: Removes an extension with removing it from the applicative containter.
//     QueryAllExtensions: Retrieves a list of pointers to all the extensions related to
//        the current feature. 
//     GetID: Retrieves the id (name) of the current extension.
//     SaveAs: Saves the document.
//     Remove: Removes the document from the session.
//  Delete_Session:  Deletes the session.
//
//=============================================================================
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in New document
//  3 - ERROR in CATCreateApplicativeContainer for applicative container 1
//  4 - ERROR in QueryInterface
//  5 - ERROR in QueryExtension or QueryAllExtensions
//  6 - ERROR in AccessCatalog
//  7 - ERROR in RetrieveSU 
//  8 - ERROR in Instanciate
//  9 - ERROR in AddExtension for CAAOsmHistoricalNovel extension
// 10 - ERROR in RemoveApplicativeExtensions for CAAOsmHistoricalNovel extension
// 11 - ERROR in SaveAs du document
// 12 - ERROR in Remove du document
// 13 - ERROR in Delete_Session 
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//        mkrun -c "CAAOsmMainManageExt ExtCatalog1Name ExtCatalog2Name 
//                                  BaseFeatureCatalogName DocumentStoragePathName" 
//  where the "ExtCatalog1Name" is the name and .CATfct extension of the first new
//     extensions catalog. Remember that the catalog must be found under the "WS" + "OS"
//     + resources + graphic directory.
//  where the "ExtCatalog2Name" is the name and .CATfct extension of the second new
//     extensions catalog. Remember that the catalog must be found under the "WS" + "OS"
//     + resources + graphic directory.
//  where the "BaseFeatureCatalogName" is the name and .CATfct extension of the existing
//     catalog of StartUps created by the "CAAOsmCatalogSU" use case, and
//  where the "DocumentStoragePathName" is the entire pathname, name and .CATPart extension
//     of the new document created.
//==========================================================================================

//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session

//System
#include "CATErrorDef.h"                 // Error handling

//Other includes
#include "iostream.h"

//CAAObjectSpecsModeler.edu
#include "CAAOsmIllustrateExtensions.h"  // Utility that illustrates working with extensions
                                         //   in a Part document.
#include "CATSession.h"

int main (int argc, char * argv[] )
{ 

//----------------------------------------
// Create the session for batch execution.
//----------------------------------------

	char *sessionName = "CAA2_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(sessionName, 
		                        pSession);
	if ((FAILED(rc)) || (NULL == pSession))
	{
		cout << "ERROR in creating session" << endl << flush;
		return 1;
	}

//-------------------------------------------------
// Work with the new extensions in a Part document.
//-------------------------------------------------

	int retCode = 0;
	retCode = ::CAAOsmIllustrateExtensions(argv[1], argv[2], argv[3], argv[4]);
	if (retCode != 0) 
	{ 
		cout << "ERROR in CAAOsmIllustrateExtensions" << endl << flush;
        return retCode;
	}

//----------------
// Delete session
//----------------

	rc = ::Delete_Session(sessionName);
	if (FAILED(rc))
	{
			cout << "ERROR in deleting session" << endl << flush;
			return 11;
	}
			
	return 0;
  
}

