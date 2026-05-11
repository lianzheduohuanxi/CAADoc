//===============================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//  What does the Build method implement ?
//
// -1- : Removes all possible update error associated with
// -2- : Handles the input specifications
// -3- : Defines the procedural report
// -4- : Handles the toplogical and geometrical inputs
// -5- : Computes the resulting line between Point1 and Point2
// -6- : Stores the procedural report
// -7- : Manages all the potential errors raised during topological evaluation
//===============================================================================================

// Local framework
#include "CAAEOmmBuildVerticalLine.h"  // needed as class header file

// system resources
#include <iostream.h>                  // needed for trace management

// System framework
#include "CATUnicodeString.h"          // needed to create error messages
#include "CATListOfCATUnicodeString.h" // needed to create lists of keys

// ObjectModelerBase Framework
#include "CATLISTV_CATBaseUnknown.h"   // needed to store the objects to track

// ObjectSpecsModeler framework
#include "CATISpecObject.h"            // needed to handle the line as a specification
#include "CATISpecAttrKey.h"           // needed to read specification attributes
#include "CATISpecAttrAccess.h"        // needed to read specification attributes

// MechanicalModeler Framework
#include "CATIMfProcReport.h"          // needed to store the procedural report
#include "CATMfBRepDefs.h"             // needed to indicate what the procedural report should follow
#include "CATMfErrUpdate.h"            // needed to manage mechanical modeler update error
#include "CATIUpdateError.h"           // needed to associate an error to a feature
#include "CATIGeometricalElement.h"

// MecModInterfaces Framework
#include "CATIPrtContainer.h"          // needed to retrieve the geometrical factory

// Mathenatics framework
#include "CATMathPoint.h"              // needed to get point coordinates
#include "CATSoftwareConfiguration.h"  // needed to handle topological operators versioning

// GeometricObjects Framework
#include "CATGeoFactory.h"             // needed to create a vertex
#include "CATCartesianPoint.h"         // needed to create a cartesian point
#include "CATPoint.h"                  // needed to get point geometry
#include "CATCGMJournalList.h"         // needed to insure topological journaling

// NewTopologicalObjects Framework
#include "CATBody.h"                   // needed as a base object for the line
#include "CATDomain.h"                 // needed as debug tool                  
#include "CATCell.h"                   // needed as debug tool    
#include "CATTopData.h"                // needed as data structure for operator versionning                     

// TopologicalOperators framework
#include "CATTopVertex.h"              // needed to create a vertex in volume

// BasicTopologicalOpe framework
#include "CATTopLineOperator.h"        // needed to create a linear body

// Tie the implementation to its interface

CATImplementClass(CAAEOmmBuildVerticalLine,
                  DataExtension,
                  CATBaseUnknown,
                  CAAOmmVerticalLine);

#include <TIE_CATIBuild.h>
TIE_CATIBuild(CAAEOmmBuildVerticalLine);

// Dictionary entry to be added :
//CAAOmmVerticalLine    CATIBuild               libCAAOmmImpl

//-----------------------------------------------------------------------------
// CAAEOmmBuildVerticalLine : constructor
//-----------------------------------------------------------------------------
CAAEOmmBuildVerticalLine::CAAEOmmBuildVerticalLine():CATBaseUnknown()
{
   cout<< "CAAEOmmBuildVerticalLine::CTOR" << endl;
}

//-----------------------------------------------------------------------------
// CAAEOmmBuildVerticalLine : destructor
//-----------------------------------------------------------------------------
CAAEOmmBuildVerticalLine::~CAAEOmmBuildVerticalLine()
{
   cout << "CAAOmmBuildVerticalLine::DTOR" << endl;
}

//-----------------------------------------------------------------------------
// CAAEOmmBuildVerticalLine : Build
//-----------------------------------------------------------------------------
HRESULT CAAEOmmBuildVerticalLine::Build()
{   
    cout << "-->CAAEOmmBuildVerticalLine::Build" << endl;

    //--------------------------------------------------------------------
    // -1- : Removes all possible update error associated with
    //--------------------------------------------------------------------
    
    // Gets a pointer on CATIUpdateError
    CATIUpdateError *piUpdateErrorOnThis = NULL; 
    HRESULT rc = QueryInterface(IID_CATIUpdateError,(void**) &piUpdateErrorOnThis); 
    if ( FAILED(rc) ) 
    {
        return rc;
    }
    // removes all associated error 
    piUpdateErrorOnThis->UnsetUpdateError();

    //--------------------------------------------------------------------
    // -2- : Handles the input specifications
    //--------------------------------------------------------------------

    // Gets the current object as a specification
    CATISpecObject* piSpecOnThis=NULL;
    rc=QueryInterface(IID_CATISpecObject, (void**) &piSpecOnThis);
    if (FAILED(rc)) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        return rc;
    }

    CATISpecAttrAccess * piSpecAttrAccessOnThis=NULL;
    rc=QueryInterface(IID_CATISpecAttrAccess, (void**) &piSpecAttrAccessOnThis);
    if (FAILED(rc)) 
    {
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        return rc;
    }
   
    // Gets the input attributes : first and second point attributes
    CATISpecAttrKey * piAttrKeyOnPoint1 = piSpecAttrAccessOnThis->GetAttrKey("Point1");
    if ( piAttrKeyOnPoint1 ==  NULL )
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piSpecAttrAccessOnThis->Release();
        piSpecAttrAccessOnThis = NULL ;
        return E_FAIL ;
    }

    CATISpecAttrKey* piAttrKeyOnPoint2 = piSpecAttrAccessOnThis->GetAttrKey("Point2");
    if (NULL==piAttrKeyOnPoint2) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piAttrKeyOnPoint1->Release();
        piAttrKeyOnPoint1 = NULL ;
        piSpecAttrAccessOnThis->Release();
        piSpecAttrAccessOnThis = NULL ;

        return E_FAIL ;
    }
    
    // Gets the input specifications : first and second point
    CATISpecObject* piSpecOnPoint1 = piSpecAttrAccessOnThis->GetSpecObject(piAttrKeyOnPoint1);
    if (NULL==piSpecOnPoint1) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piAttrKeyOnPoint1->Release();
        piAttrKeyOnPoint1 = NULL ;
        piAttrKeyOnPoint2->Release();
        piAttrKeyOnPoint2 = NULL ;
        piSpecAttrAccessOnThis->Release();
        piSpecAttrAccessOnThis = NULL ;

        return E_FAIL ;
    }

    piAttrKeyOnPoint1->Release();
    piAttrKeyOnPoint1 = NULL ;

    CATISpecObject* piSpecOnPoint2 = piSpecAttrAccessOnThis->GetSpecObject(piAttrKeyOnPoint1);
    if (NULL==piSpecOnPoint2) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piSpecOnPoint1->Release();
        piSpecOnPoint1 = NULL ;
        piAttrKeyOnPoint2->Release();
        piAttrKeyOnPoint2 = NULL ;
        piSpecAttrAccessOnThis->Release();
        piSpecAttrAccessOnThis = NULL ;

        return E_FAIL;
    }

    piAttrKeyOnPoint2->Release();
    piAttrKeyOnPoint2 = NULL ;
    piSpecAttrAccessOnThis->Release();
    piSpecAttrAccessOnThis = NULL ;

    //--------------------------------------------------------------------
    // -3- : Defines the procedural report
    //--------------------------------------------------------------------
    
    // gets a pointer on CATIMfProcReport
    CATIMfProcReport *piProcReportOnThis = NULL;
    
    rc = QueryInterface(IID_CATIMfProcReport, (void**) &piProcReportOnThis);
    if ( FAILED(rc) ) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piSpecOnPoint1->Release();
        piSpecOnPoint1 = NULL ;
        piSpecOnPoint2->Release();
        piSpecOnPoint2 = NULL ;

        return E_FAIL ;
    }
    
    // Defines which specifications take part in the creation of the report
    CATLISTV(CATBaseUnknown_var) ListSpec;
    CATListOfCATUnicodeString    ListKeys;
    
    ListSpec.Append(piSpecOnPoint1); 
    ListKeys.Append(MfKeyNone     );
    
    // creates the procedural report
    piProcReportOnThis->CreateProcReport(ListSpec,ListKeys); 
    
    // Gets a pointer to the topological journal which contains 
    // the description of all basic topological operations.
    CATCGMJournalList *pCGMJournalList = piProcReportOnThis->GetCGMJournalList();

    // So far this journal is still empty, it will be filled by the topological 
    // operators that use it.

    // Defines an open configuration for the operator
    CATSoftwareConfiguration * pConfig = new CATSoftwareConfiguration();

    // defines the data of the operator: configuration + journal
    CATTopData topData(pConfig,pCGMJournalList);

    //--------------------------------------------------------------------
    // -4- : Handles the toplogical and geometrical inputs
    //--------------------------------------------------------------------

    // Retrieves geometrical results of points thanks to
    // Delegation mechanism : specification adheres to its result CGM interface
    //
    CATPoint* piPointOnPoint1 = NULL;
    rc=piSpecOnPoint1->QueryInterface(IID_CATPoint, (void**) &piPointOnPoint1);

    if (FAILED(rc)) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piSpecOnPoint2->Release();
        piSpecOnPoint2 = NULL ;
        piSpecOnPoint1->Release();
        piSpecOnPoint1 = NULL ;
        piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        if ( pConfig != NULL) pConfig->Release();
        pConfig = NULL ;

        return E_FAIL;
    }

    // Gets X coordinate for the new projected point
    double XOnProjectedPoint = piPointOnPoint1->GetX();
    piPointOnPoint1->Release();
    piPointOnPoint1 = NULL ;

    CATPoint* piPointOnPoint2 = NULL;
    rc=piSpecOnPoint2->QueryInterface(IID_CATPoint, (void**) &piPointOnPoint2);
    piSpecOnPoint2->Release();
    piSpecOnPoint2 = NULL ;

    if (FAILED(rc)) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piSpecOnPoint1->Release();
        piSpecOnPoint1 = NULL ;
        piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        pConfig->Release();
        pConfig = NULL ;

        return E_FAIL;
    }
    // Gets Y coordinate for the new projected point
    double YOnProjectedPoint = piPointOnPoint2->GetY();
    piPointOnPoint2->Release();
    piPointOnPoint2 = NULL ;

    // Gets the underlying topological objects : Body topological object
    CATIGeometricalElement* piGeoElemOnPoint1 = NULL;
    rc=piSpecOnPoint1->QueryInterface(IID_CATIGeometricalElement, (void**) &piGeoElemOnPoint1);

    piSpecOnPoint1->Release();
    piSpecOnPoint1 = NULL ;

    if (FAILED(rc)) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piSpecOnThis->Release();
        piSpecOnThis = NULL ;
        piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        pConfig->Release();
        pConfig = NULL ;
   
        return E_FAIL;
    }

    CATBody_var spiBodyOfPoint1 = piGeoElemOnPoint1->GetBodyResult();
    piGeoElemOnPoint1->Release();
    piGeoElemOnPoint1 = NULL ;

    //--------------------------------------------------------------------
    // -5- : Computes the resulting line between Point1 and Point2
    //--------------------------------------------------------------------

    // Retrieves the Part Feature container.
    CATIPrtContainer_var spPrtContainerOnThis = piSpecOnThis->GetFeatContainer();
    piSpecOnThis->Release();
    piSpecOnThis = NULL ;
    
    // Retrieves the geometrical container
    CATIContainer_var spiGeoContainer;
    if (NULL_var!=spPrtContainerOnThis) 
    {
      spiGeoContainer = spPrtContainerOnThis->GetGeometricContainer();
    }
    else 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        pConfig->Release();
        pConfig = NULL ;
        
        return E_FAIL;
    }
    if (NULL_var==spiGeoContainer) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        pConfig->Release();
        pConfig = NULL ;
        
        return E_FAIL;
    }
    
    // Retrieves geo/topo factories thanks to its container adhesion
    CATGeoFactory *piGeoFactoryOnCont = NULL;
    rc = spiGeoContainer->QueryInterface(IID_CATGeoFactory, (void**) &piGeoFactoryOnCont);
    if ( FAILED(rc) ) 
    {
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        pConfig->Release();
        pConfig = NULL ;
        
        return E_FAIL;
    }

    // Computes coordinates of pseudo second point .i.e "projected point"
    CATPoint* piPointOnProjectedPoint=piGeoFactoryOnCont->CreateCartesianPoint(
      XOnProjectedPoint,
      YOnProjectedPoint,
      0.);
    
    // Topological computations
    CATTopVertex* pVertexOperator = NULL;

    CATTry 
    {
       // Computes topological representation of previous point, thru a vertex creation
       pVertexOperator = ::CATCreateTopVertex(piGeoFactoryOnCont,
                                             &topData,
                                               piPointOnProjectedPoint);
       if ( NULL == pVertexOperator )
       {
          CATMfErrUpdate *pErrorNoProjResult = new CATMfErrUpdate();
          CATUnicodeString Diagnostic("Cannot create the top vertex");
          pErrorNoProjResult->SetDiagnostic(1,Diagnostic);
          CATThrow(pErrorNoProjResult);
       }

       pVertexOperator->Run();

       CATBody* piBodyOnProjectedPoint = pVertexOperator->GetResult();

       delete pVertexOperator;
       pVertexOperator=NULL;

       if (NULL==piBodyOnProjectedPoint) 
       {
          CATMfErrUpdate *pErrorNoProjResult = new CATMfErrUpdate();
          CATUnicodeString Diagnostic("Cannot compute the projected point");
          pErrorNoProjResult->SetDiagnostic(1,Diagnostic);
          CATThrow(pErrorNoProjResult);
       }

       // Computes the line between point1 and extrapoled point
      CATBody* piBodyOnLine = ::CATCreateTopLineFromPoints(
                                               piGeoFactoryOnCont,
                                               &topData,
                                               spiBodyOfPoint1,
                                               piBodyOnProjectedPoint);
        
    //--------------------------------------------------------------------
    // -6- : Stores the procedural report
    // The report is built using  : the specifications given when creating it 
    //                            : the topological journal
    //--------------------------------------------------------------------
       if (NULL!=piBodyOnLine) 
       {                      
          piProcReportOnThis->StoreProcReport(piBodyOnLine,NoCopy);
       }
       else 
       {
           // creates an error if the line operation fails
           CATMfErrUpdate *pErrorNoResult = new CATMfErrUpdate();
           CATUnicodeString Diagnostic("Cannot compute a line between these points");
           pErrorNoResult->SetDiagnostic(1,Diagnostic);
           CATThrow(pErrorNoResult);
       }     
    }

    //--------------------------------------------------------------------
    // -7- : Manages all the potential errors raised during topological evaluation
    //--------------------------------------------------------------------
    CATCatch (CATMfErrUpdate, pUpdateError) 
    {        
        // Builds a new update error.
        CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();

        // Add it the diagnostic comming from the error previously caugth.
        pErrorToThrow->SetDiagnostic(1,pUpdateError->GetDiagnostic());

        // Destroys the previous error.
        ::Flush(pUpdateError);

        // Associates the error with the combine curve.
        piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);
        
        // Deletes the vertex topological operator
        if (NULL != pVertexOperator) 
        {
            delete pVertexOperator;
            pVertexOperator=NULL;
        }
 
        // Releases useless pointers.
        piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        piGeoFactoryOnCont->Release();
        piGeoFactoryOnCont = NULL ;
        pConfig->Release();
        pConfig = NULL ;
        
        // Dispatches the error.
        // In interactive mode, this errror will be caught by CATPrtUpdateCom that
        // knows how to handle such errors.
        CATThrow(pErrorToThrow);
    }

    // Handles all other errors
    CATCatch (CATError, pError) 
    {
        CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
        pErrorToThrow->SetDiagnostic(1,pError->GetNLSMessage());
        ::Flush(pError);
        if ( NULL != piUpdateErrorOnThis )
           piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);
        
        // Deletes the vertex topological operator
        if (NULL != pVertexOperator) 
        {
            delete pVertexOperator;
            pVertexOperator=NULL;
        }
        
        // Releases useless pointers.
        if ( NULL != piUpdateErrorOnThis) piUpdateErrorOnThis->Release();
        piUpdateErrorOnThis = NULL ;
        if ( NULL != piProcReportOnThis) piProcReportOnThis->Release();
        piProcReportOnThis = NULL ;
        if( NULL != piGeoFactoryOnCont) piGeoFactoryOnCont->Release();
        piGeoFactoryOnCont = NULL ;
        if ( NULL != pConfig) pConfig->Release();
        pConfig = NULL ;
        
        CATThrow(pErrorToThrow);
    }   

    CATEndTry;

    // Releases only remaining local pointers
    if ( NULL != piUpdateErrorOnThis) piUpdateErrorOnThis->Release();
    piUpdateErrorOnThis = NULL ;
    if ( NULL != piProcReportOnThis) piProcReportOnThis->Release();
    piProcReportOnThis = NULL ;
    if( NULL != piGeoFactoryOnCont) piGeoFactoryOnCont->Release();
    piGeoFactoryOnCont = NULL ;
    if ( pConfig != NULL) pConfig->Release();
    pConfig = NULL ;
        
    cout << "<--CAAEOmmBuildVerticalLine::Build" << endl;
   
    return 0;
}
