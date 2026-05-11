/**
* @quickReview BPG 05:10:31
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2004
//                 
// Sample code for : TopologicalOperators
// Mission         : Use of topological journal to access objects
//                   
//                   SCENARIO: 
//                       (1) -  Intersect to bodies bodyA or bodyB
//                       (2) -  Analyze the journal to determine, for each face of the resulting
//                              body, where the faces come from (bodyA or bodyB)
//
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (if not null, the model is not saved)
//                   0- OK
//                   1- Null pointer
//
// Coding steps    : 1 - Preliminary declarations
//                   2 - Get the faces of bodyA and bodyB
//                   3 - Perform the boolean intersection
//                   4 - Display the journal
//                   5 - Analyse the journal
//                   6 - Display the lists of faces (faces from bodyA, faces from bodyB. absorbed faces) 
//                   7 - Close the application
//
// How to run it   : CAATopClashIntersect  inputFile.ncgm  outputFile.ncgm 
//                   inputfile to be used is bodiesForClash.ncgm
//                                           bodiesForClash1.ncgm
//                                           bodiesForClash2.ncgm
//                                           bodiesForClash3.ncgm
//                                           bodiesForClash4.ncgm
//                                           bodiesForClash5.ncgm
//
//                   bodiesForClashx.ncgm are provided in the 
//                   FunctionTests/InputData folder
//=============================================================================
#include <iostream.h>
#include "fstream.h"

// Mathematics
#include "CATSoftwareConfiguration.h"  // Configuration of the operator

// GeometricObjects
#include "CATGeoFactory.h"             // Geometry factory 
#include "CATCGMContainerMngt.h"       // Geometry factory management                
#include "CATCGMJournalList.h"           // Journal
#include "CATCGMJournalInfo.h"
// TopologicalObjects
#include "CATBody.h"                   // body
#include "CATFace.h"
#include "CATDomain.h"
#include "CATCell.h" 
#include "CATTopData.h"                // TopData of an operator
//#include "CATGeometry.h"
#include "CATTopSimplify.h"

// TopologicalOperators
#include "CATDynBoolean.h"

// Error management
#include "CATError.h"              // errors
#include "CATErrorMacros.h"        // to catch errors 

#include "CAACheckForPart.h"           // Journal checker
#include "CAADumpJournal.h"  
//------------------------------------------------------------------------------
// The return code of the main is null if the execution is OK, not null if some
// problem has been detected
int main(int    iArgc,   // Number of arguments (3) 
         char** iArgv)   
{
    int rc=0;
    if(3<iArgc) return (1);
    
    char *pFileName1 = 0;
    int  toStore = 0;
    
    
    char *pFileName = NULL;
    if( 3 != iArgc ) 
    {
        cout << "one .ncgm file is missing" << endl;
        return (1);
    }
    else
    {
        toStore = 1; 
        pFileName = iArgv[1];
        pFileName1 = iArgv[2];
    }
    
    
#ifdef _WINDOWS_SOURCE
    ifstream filetoread(pFileName, ios::binary ) ;
#else
    ifstream filetoread(pFileName) ;
#endif
    //
    // -----------------------------------------------------------
    // 1 - Preliminary declarations
    // -----------------------------------------------------------
    //
    // (a) Loads the container 
    //
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    if (NULL==piGeomFactory) return (1);
    //
    // (b) Configuration management
    //
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();
	//
    // (c) - Create the default journal
	//
    CATCGMJournalList* pJournal = new CATCGMJournalList(pConfig,NULL);
    CATTopData topdata(pConfig, pJournal);
   
	//
    // -----------------------------------------------------------
    // Body A
    // -----------------------------------------------------------
    //
	// (a) - Retrieve it 
	//
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(2518); // bodiesForClash.ncgm
	//CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(2518); // bodiesForClash1.ncgm
	//CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(6728); // bodiesForClash2.ncgm
	//CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(1522); // bodiesForClash3.ncgm
	//CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(1522); // bodiesForClash4.ncgm
    //CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(1522); // bodiesForClash5.ncgm
    if (piCGMObj1 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piBodyA= (CATBody *) piCGMObj1;
	//
	// (b) - Display its faces
	//
	CATLISTP(CATCell) listOfFacesA;
    piBodyA->GetAllCells(listOfFacesA,2);
	cout << "Body A" << endl;
	for (int fA = 1; fA < listOfFacesA.Size()+1; fA++)
	{
		CATCell * myptr = listOfFacesA[fA];
	  if (myptr != NULL)	cout << myptr->GetPersistentTag() << endl;
	}
	cout << "------" << endl;

    // -----------------------------------------------------------
    // Body B
    // -----------------------------------------------------------
    //
	// (a) - Retrieve it 
	//
	CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(2765);  // bodiesForClash.ncgm
	//CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(4777);  // bodiesForClash1.ncgm
	//CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(4777);  // bodiesForClash2.ncgm
	//CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(1874);  // bodiesForClash3.ncgm
	//CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(2257);  // bodiesForClash4.ncgm
	//CATICGMObject * piCGMObj2 = piGeomFactory->FindObjectFromTag(2640);  // bodiesForClash5.ncgm -1 edge
    if (piCGMObj2 == NULL)
    {
        cout << "No object with the specified tag" <<endl;
        return 1;
    }
    CATBody * piBodyB= (CATBody *) piCGMObj2;
	//
	// (b) - Display its faces
	//
	CATLISTP(CATCell) listOfFacesB;
	piBodyB->GetAllCells(listOfFacesB,2);
	cout << "Body B" << endl;
	for (int fB = 1; fB < listOfFacesB.Size()+1; fB++)
	{
		CATCell * myptr = listOfFacesB[fB];
	 if (myptr != NULL)	cout << myptr->GetPersistentTag() << endl;
	}
	cout << "------" << endl;
	//
    // -----------------------------------------------------------
    // 3 - Intersect the Body A and Body B
    // -----------------------------------------------------------
    //
	CATDynBoolean * pBoolOpe = NULL;
	pBoolOpe =::CATCreateDynBoolean(piGeomFactory,&topdata, 
		CATBoolIntersection, piBodyA, piBodyB);
	if (NULL==pBoolOpe)
    {
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
    pBoolOpe->Run();
	CATBody * pBodyIntersect = pBoolOpe->GetResult();
    if (NULL==pBodyIntersect)
    {
		cout << "No solid intersection" << endl;
		::CATCloseCGMContainer(piGeomFactory);
		return (1);
    }
	
	// -----------------------------------------------------------
    // 4 - Display the default journal 
    // -----------------------------------------------------------
	//
    cout << "Displaying the journal after Tass" << endl;
    pJournal->Tass();
    CAATopDumpJournal(pJournal);
    cout << "End of journal" << endl;

	CATLISTP(CATCell) listOfFaces;
    pBodyIntersect->GetAllCells(listOfFaces,2);
	//
	// -----------------------------------------------------------
    // 5 - Analyse the journal 
    // -----------------------------------------------------------
	//
    // (a) - In the topological journal resulting from the boolean 
	//       intersection, the faces which belong to the resulting body appear 
	//       modified or absorbed.
	//       Retrieving the parent face(s) of these modified/absorbed faces
	//       and determining what input body they belong to 
	//       tells you where each face of the resulting body comes from.
	// 
    
    CATLISTP(CATCell) facesCommingFromA;    // faces comming from BodyA
    CATLISTP(CATCell) facesCommingFromB;    // faces comming from BodyB
    CATLISTP(CATCell) absorbedFaces;        // faces comming from BodyA and BodyB as well
    //
    // (b) - Scan the faces of the resulting body
    //
    for (int k = 1; k < listOfFaces.Size()+1; k++)
    {
      CATLISTP(CATGeometry) originObjects;
      //
      // Get the parent faces if the order is creation/modification/absorption
      //
      CATCell * myptr = listOfFaces[k];
      pJournal->FindFirsts(myptr, originObjects, ThroughAllCreateAndModify);
      if (myptr != NULL )
      {
        cout << "Face :" << myptr->GetPersistentTag() << endl;
      }
      int isInBodyA = 0;
      int isInBodyB = 0;
      for (int j = 1; j < originObjects.Size()+1; j++)
      {
        CATGeometry *originObject = originObjects[j];
        if (originObject != NULL)
        {
          cout << "Parent face: " << originObject->GetPersistentTag() << endl;
          // Belongs to BodyA ?
          if (originObject->IsATypeOf(CATCellType)) 
          {
            CATCell * pCell = (CATCell *) (originObjects[j]);
            if  ( listOfFacesA.Locate(pCell) ) 
            {
              isInBodyA = 1;
            }
            // or to BodyB ?
            else if ( listOfFacesB.Locate(pCell) ) 
            {
              isInBodyB =1;
            }
          }
          else
          {
            cout << "Unknown faces - check how your part has been created" << endl;
            cout << "OR journal problem" << endl;
          }
        }
      }
      cout << "-------" << endl; 
      if ( (isInBodyA==1) && (isInBodyB == 1) ) 
        absorbedFaces.Append(myptr); 
      if ( (isInBodyA == 1) && (isInBodyB ==0) ) 
        facesCommingFromA.Append(myptr);
      if ( (isInBodyA == 0) && (isInBodyB ==1) ) 
        facesCommingFromB.Append(myptr);
    }
    delete pBoolOpe;

    //
    // -----------------------------------------------------------
    // 6 - Display the list of faces
    // -----------------------------------------------------------
    //
    // ---------------------------------------------------
    cout << "List of faces in the resulting body" << endl;
    // ---------------------------------------------------
    cout << "Faces coming from BodyA and only from A " << endl;
    int i = 0;
    for (i = 1; i < facesCommingFromA.Size()+1; i++)
    {
      CATCell *faceCommingFromA = facesCommingFromA[i];
      if (faceCommingFromA != NULL ) cout << faceCommingFromA->GetPersistentTag() << endl;
    }
    // 
    // ---------------------------------------------------
    cout << "Faces coming from BodyB and only from BodyB " << endl;
    // ---------------------------------------------------
    for (i = 1; i < facesCommingFromB.Size()+1; i++)
    {
      CATCell *faceCommingFromB = facesCommingFromB[i];
      if (faceCommingFromB != NULL ) cout <<  faceCommingFromB->GetPersistentTag() << endl;
    }
    //
    // ---------------------------------------------------
    cout << "Absorbed faces" << endl;
    // ---------------------------------------------------
    for (int l = 1; l < absorbedFaces.Size()+1; l++)
    {
      CATCell *absorbedFace = absorbedFaces[l];
      if (absorbedFace != NULL ) cout << absorbedFace->GetPersistentTag() << endl;
    }
    cout << "-------" << endl; 

    // ----------------------------------------------------------
    // 7 - Close the application
    // ----------------------------------------------------------
    //
	 pConfig->Release();
         pConfig = NULL;

         delete pJournal; 
         pJournal = NULL;
    if(1==toStore)
    {
        cout << "Writing the model" << endl;
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pFileName1, ios::binary ) ;
#else
        ofstream filetowrite(pFileName1,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }	
    
    filetoread.close();
    CATCloseCGMContainer(piGeomFactory);
    return rc;
    }
