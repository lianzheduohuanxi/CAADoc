/**
* @quickReview CRE 04:07:28
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  200
//
// Sample code for : Geometric Modeler
// Mission         : Use of the GeometricObject framework
//                   Creation of implicit objects.
//                   Explains the basics about implicit objects / versus explicit object.
//
// Explanations    : Implicit objects are those created by the implicit factory.
//                   These objects are automatically removed when all the objects
//                   that point to them are removed with the RemoveDependancies option
//                   of the CATICGMContainer::Remove method.
//                   In your applications, it is recommended to create geometry with 
//                   the implicit factory and topology with the explicit or standard 
//                   factory.
//                   
// Type            : Batch program
// Inputs          : None
// Outputs         : Return codes (in this case, the file is not saved)
//                   0- OK
//                   1- Null pointer detection
//
// Coding steps    : 1- Explicit and implicit geometry factory creation
//                   2- Geometry creation: plane, PLine and cloned Pline
//                   3- Remove of the initial Pline with RemoveDependancies
//                      and attempt to create a new Pline by reusing the 
//                      pointer to the previous plane
//                   4- Model writing and closing operations
//
// How to run it   : CAAGobLifeCycleImplicit            // to run without storing the NCGM file
//                   CAAGobLifeCycleImplicit  file.NCGM // to run and store the result in file.NCGM  
// ================================================================================       
#include <iostream.h>
#include "fstream.h"

#include "CATMathDirection.h"      // mathematical unitary vector
#include "CATMathPlane.h" 
// Mathematics
#include "CATMathPoint.h"          // Mathematical point

// GeometricObjects
#include "CATGeoFactory.h"         // Geometry factory
#include "CATCGMContainerMngt.h"   // Management of the geometry factory
#include "CATCloneManager.h" 

//#include "CATSurParam.h"           // Surface parameter
#include "CATPLine.h"              // Line on a surface 
#include "CATPlane.h" 

// Error management
#include "CATError.h"              // errors
#include "CATErrorMacros.h"        // to catch errors
//------------------------------------------------------------------------------

int main(int    iArgc,   // Number of arguments (0) or (1) 
         char** iArgv)   // Path to the *.NCGM document that will contain the result of the main.
{
    int rc=0;
    if(2<iArgc) return (1);
    
    char *pFileName = 0;
    int  toStore = 0;
    if (2==iArgc) 
    {
        toStore = 1; 
        pFileName = iArgv[1];
    }
    
    //-----------------------------------------------------------------------------
    // 1 - Initialize the factory and retrieve the implicit factory
    //     It is recommended to create the geometry with the implicit factory
    //-----------------------------------------------------------------------------
    
    CATGeoFactory* piGeomFactory = ::CATCreateCGMContainer() ;
    if (NULL == piGeomFactory) return (1);
    
    // Get the implicit factory 
    //
    CATGeoFactory * piImplicitFactory =piGeomFactory->GetImplicitGeoFactory( );
    if (NULL == piImplicitFactory) return (1);
    
    //-----------------------------------------------------------------------------
    // 2 - Create the geometry - all objects implicit
    //-----------------------------------------------------------------------------
    //
   	CATPlane * piPlane = piImplicitFactory->CreatePlane(CATMathOIJ);
    if (NULL == piPlane)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    
    CATMathPoint mathOrigin;
    CATMathDirection mathU, mathV;
    
    // ----- Retrieve the mathematical definition of the geometrical plane
    piPlane->GetAxis(mathOrigin,mathU,mathV);
    
    // ----- Define points on the plane 
    CATSurParam p1, p2;
    piPlane->GetParam(mathOrigin, p1);
    piPlane->GetParam(mathOrigin - 20*mathU, p2);
    
    // ----- Create a PLine
    CATPLine * pPline =  piImplicitFactory->CreatePLine   (p1, p2, piPlane );
    
    // ----- Clone pPline - Full duplication mode
    //       A duplicate plane is created because the CatCGMFullDuplicate
    //       is specified - if the default option is used, the duplicated 
    //       PLine points to the already existing plane.
    CATCloneManager * pCloneManager= new CATCloneManager(piImplicitFactory, CatCGMFullDuplicate); 
    if (NULL==pCloneManager)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
    pCloneManager->Add(pPline);
    pCloneManager->Run();
    CATICGMObject* piClonedPLine=NULL;
    piClonedPLine = pCloneManager->ReadImage(pPline);
    if (NULL==piClonedPLine)
    {
        ::CATCloseCGMContainer(piGeomFactory);
        return (1);
    }
   
    // ----------------------------------------------------------------------------
    // 3 - Remove the two Plines with RemoveDependancies option and
    //     attempt to create a new PLine with piPlane as the support
    // ----------------------------------------------------------------------------
    //
    // Case 1 - Full duplicate (check the option value in the 
    //                          CATCloneManager constructor above)
    //          (a) - you remove pPline with RemoveDependancies 
    //                ->piPlane is removed
    //                You cannot create a new PLine by re-using piPlane
    //                This is true whether you remove piClonedPLine or not
    // Case 2 - Single duplicate
    //          (a) - you remove pPline with RemoveDependancies 
    //                but not piClonedPLine 
    //                -> piPlane is not removed
    //                because it is still pointed to by piClonedPLine
    //                and you can re-use it to create a new PLine
    //          (b) - you remove pPline with RemoveDependancies as well as piClonedPLine
    //                -> piPlane is removed because it is no longer pointed to other objects
    //                you cannot re-use piPlane
    //
    piImplicitFactory->Remove(pPline,CATICGMContainer::RemoveDependancies);
    piImplicitFactory->Remove(piClonedPLine,CATICGMContainer::RemoveDependancies);
    
    CATPLine * pNewPline = NULL;
    CATTry 
    {
        
        pNewPline =  piImplicitFactory->CreatePLine   (p1, p2, piPlane );
        cout << "New PLine has been created " << endl;
        
	 
    }
    CATCatch(CATError,error)
    { 
        
        cout << "New Pline couldn't be created with the removed initial plane" << endl;
        cout << (error->GetNLSMessage()).ConvertToChar()<<endl;
        Flush(error);
		error=NULL;
		
		rc=0; // just for tests
    }
    CATEndTry;
    if (NULL != pNewPline) 
        piImplicitFactory->Remove(pNewPline,CATICGMContainer::RemoveDependancies);
	//

    // Delete the operator
    //
    if(pCloneManager)
    {
        delete pCloneManager;
        pCloneManager = NULL;
    }
    //-----------------------------------------------------------------------------
    // 4 - Write the model
    //-----------------------------------------------------------------------------
    cout << "Saving the container " << endl;
    if(1==toStore)
    {
#ifdef _WINDOWS_SOURCE
        ofstream filetowrite(pFileName, ios::binary ) ;
#else
        ofstream filetowrite(pFileName,ios::out,filebuf::openprot) ;
#endif
        
        ::CATSaveCGMContainer(piGeomFactory,filetowrite);
        filetowrite.close();
    }			
    
    //
    // Closes the container
    //
    
    ::CATCloseCGMContainer(piGeomFactory);
    
    
    return (rc);
}


