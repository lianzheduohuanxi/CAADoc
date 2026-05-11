// COPYRIGHT DASSAULT SYSTEMES  1999

// ObjectModelerBase
#include "CATIContainer.h"
// KnowledgeInterfaces
#include "CATICkeInst.h"
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"
#include "CATICkeRelation.h"
#include "CATICkeType.h"
#include "CATIParmPublisher.h"
#include "CATIVisitor.h"

// CAALiteralFeatures.edu
#include "CAALifMyVisitor.h"
#include "CAALifReturnCodes.h"
#include "CAALifServices.h"

// ObjectSpecsLegacy
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATOsmSUHandler.h"

#include "iostream.h" 

/** @quickReview tvq 2001:06:25 */
// ===================================================================================
// 
// ABSTRACT
// --------
//
// Illustrates how to proceed to publish a literal.
// Publishing a literal means be able to:
//    * Access the f(x) capabilities
//    * Visualize your parameters and relations in the specification tree
//    * Filter parameter lists
//    * Create and delete of parameters and relations.
//
// Here are the programming steps to follow to publish a literal
//    1 - Extend the CATParmPublihserAdapter implementation of CATIParmPublisher and redefine
//        the GetDirectChildren, GetAllChildren(if need be) and CompAttrComp methods.
//    2 - Create a feature with the type specified in the CATParmPublihserAdapter extension
//    3 - Add an attribute of tk_list(tk_component) type to the created feature
//    4 - Aggregate the literal to be published to the created feature, to do so:
//          a) add an attribute of tk_component type to the created feature.
//          b) create your own literal and assign the literal value to the
//             tk_component attribute 
//
// ===================================================================================
int CAALifEventsExit(CATIContainer*& piContainer, int iReturnCode)
{
    if( piContainer != NULL)
        piContainer->Release();
    
    piContainer = NULL;
    
    return iReturnCode;
}

CATCke::Boolean CAALifPublish0()
{
    CATUnicodeString startupType( "CAALifSimpleFeature" );	

    CATISpecObject_var hStartupFeat;
    CATISpecObject* piFeat = NULL;
    CAALifServices CAAliteralFeaturesServices;
    
    int returnCode = -99;
 
    
    CATIContainer* piContainer = NULL;
    
    // First create a document and get the root container.
    HRESULT rc = CAAliteralFeaturesServices.CAALifCreateInstanceContainer(&piContainer);
    if( FAILED(rc) )
        return CAALifKO;
    
	// the object that encapsulates a startup
	CATOsmSUHandler suHandler(startupType, "SAMPLES", "CAA2_CAALifFeatCatalog.CATfct");

	// let's retrieve the startup
	suHandler.RetrieveSU(hStartupFeat);

	if (!hStartupFeat)
		return CAALifEventsExit( piContainer, CAALifKO );

    //Retrieves the parameters factory
    CATICkeParmFactory* piFact = NULL;
    rc = piContainer->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
        return CAALifEventsExit( piContainer, CAALifKO );
    }
    
    /**
    * FIRST FEATURE CREATION.
    */
    // Create an instance of the startup.
	// Caution, you need to specify a destination container in order to avoid the creation of feature in the CATfct.
    CATISpecObject* piSpec0 = hStartupFeat->Instanciate ("myspec0",piContainer);
    if (NULL_var == piSpec0)
    {
        cout << "Unable to instanciate the startup. " << endl;
        piFact->Release();
        return CAALifEventsExit( piContainer, CAALifKO );
    }	
    
	// Valuates the Length Attribute
	CATISpecAttrAccess * piSpecAttrAccessOnLength0 = NULL; 
	rc = piSpec0->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnLength0);
	if ( SUCCEEDED(rc) ) 
	{ 
		// Gets a pointer on the length attribute
		CATISpecAttrKey * piSpecAttrKeyOnLength0 = NULL;    
		piSpecAttrKeyOnLength0 = piSpecAttrAccessOnLength0->GetAttrKey("LifFeatureLength");
      
           if ( NULL != piSpecAttrKeyOnLength0 )
           {
				// Create a Length parameter of length type - its initial value is  1 meter 	
				// Create the parameter to be published
				// It is a Length type parameter and its value is assigned to "LifFeatureLength" attribute.
				CATICkeParm_var spLength = piFact->CreateLength ("Height",2.3);

				piSpecAttrAccessOnLength0->SetSpecObject(piSpecAttrKeyOnLength0,spLength);
				piSpecAttrKeyOnLength0->Release();
				piSpecAttrKeyOnLength0 = NULL;

			}
	}

    
    CATICkeParm_var spLength2 = piFact->CreateLength ("Height2",222);
    CATICkeParm_var spLength3 = piFact->CreateLength ("Height3",333);
    
    // Retrieve the CATIParmPublisher interface  on the specobject.
    CATIParmPublisher* piPub = NULL;
    rc = piSpec0->QueryInterface(IID_CATIParmPublisher, (void**) &piPub);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on CATIParmPublisher from spec object" << endl << flush;
        piFact->Release();
        return CAALifEventsExit( piContainer, CAALifKO );
    } 
    
    // Append other obects to this first publisher  
    piPub->Append( spLength2 );
    piPub->Append( spLength3 );
    
    /* The feature myspec0 (startup CAALifSimpleFeature holds the following objects)                    */
    /* CAALifSimpleFeature                                                                              */
    /*      |-- LifFeatureLength : tk_component   { Height }                                           */
    /*      |-- components : tk_list(tk_components) { myspec1 (CAALifSimpleFeature) , Height2,  Height3 }*/
    
    /**
    * END OF FIRST FEATURE CREATION.
    */
    
    
    /**
    * SECOND FEATURE CREATION.
    */
    
	// Caution, you need to specify a destination container in order to avoid the creation of feature in the CATfct.
    CATISpecObject* piSpec1 = hStartupFeat->Instanciate ("myspec1",piContainer);
    if (NULL_var == piSpec1)
    {
        cout << "Unable to instanciate the startup. " << endl;
        piFact->Release();
        return CAALifEventsExit( piContainer, CAALifKO );
    }	
    
    // Add the current feature to the previous one.
    piPub->Append( piSpec1 );
     
	// Valuates the Length Attribute
	CATISpecAttrAccess * piSpecAttrAccessOnLength1 = NULL; 
	rc = piSpec1->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnLength1);
	if ( SUCCEEDED(rc) ) 
	{ 
		// Gets a pointer on the length attribute
		CATISpecAttrKey * piSpecAttrKeyOnLength1 = NULL;    
		piSpecAttrKeyOnLength1 = piSpecAttrAccessOnLength1->GetAttrKey("LifFeatureLength");
      
           if ( NULL != piSpecAttrKeyOnLength1 )
           {
				// Create a Length parameter of length type - its initial value is  1 meter 	
				// Create the parameter to be published
				// It is a Length type parameter and its value is assigned to "LifFeatureLength" attribute.
			    CATICkeParm_var spLength1 = piFact->CreateLength ("Height1",111);

				piSpecAttrAccessOnLength1->SetSpecObject(piSpecAttrKeyOnLength1,spLength1);
				piSpecAttrKeyOnLength1->Release();
				piSpecAttrKeyOnLength1 = NULL;

			}
	}

    CATICkeParm_var spReal1 = piFact->CreateReal ("Real1",0.1);
    CATICkeParm_var spLength4 = piFact->CreateLength ("Height4",444);
    
    CATIParmPublisher* piPub1 = NULL;
    rc = piSpec1->QueryInterface(IID_CATIParmPublisher, (void**) &piPub1);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on CATIParmPublisher from spec object" << endl << flush;
        piFact->Release();
        return CAALifEventsExit( piContainer, CAALifKO );
    } 
    // Append other obects to this first publisher  
    piPub1->Append( spReal1 );
    piPub1->Append( spLength4 );
    
    
    /* The feature myspec1 (startup CAALifSimpleFeature holds the following objects)                    */
    /* CAALifSimpleFeature                                                                              */
    /*      |-- LifFeatureLength : tk_component   { Height1 }                                           */
    /*      |-- components : tk_list(tk_components) { Real1 , Height4 }                                 */
    
    /**
    * END OF SECOND FEATURE CREATION.
    */
    
    
    
    // Retrieve the list of direct children
    CATListValCATISpecObject_var spLst;
    piPub->GetDirectChildren (CATICkeParm::ClassName(),spLst);
    
    // Display the number of parameters as well as the parameter values
    cout << " The number of parameters is (3 expected): " << spLst.Size() << endl;
    CATICkeParm_var spFirstParam = spLst[1];
    cout << " The first parameter value is (2.3 expected): " << spFirstParam->Value()->AsReal() << endl;
    
    // Remove the parameter list from the memory
    spLst.RemoveAll();
    
    // Retrieve the relation list and display the number of relations
    piPub->GetDirectChildren (CATICkeRelation::ClassName(),spLst);
    cout << " The number of relations is (0 expected):" << spLst.Size() << endl;
    
    /*
    ** Create a new parameter
    **       Create an Angle type parameter
    **       Append this parameter to the published parameter
    **       Clean the previous list of children 
    **       Get the list of direct children supporting CATICkeParm
    **       Display the number of relations
    */
    
    // Create a parameter and append it to "myspec0"
    CATICkeParm_var spPp2 = piFact->CreateAngle ("a",0);
    piPub->Append(spPp2);
    
    /* Now the feature myspec0 has the following structure                                                                        */
    /* CAALifSimpleFeature                                                                              */
    /*      |-- LifFeatureLength : tk_component   { Height }                                           */
    /*      |-- components : tk_list(tk_components) { myspec1 (CAALifSimpleFeature) , Height2,  Height3, a }*/
  


    // Retrieve the direct children supporting CATICkeParm and display its size
    spLst.RemoveAll();

    // Scan all the attributes + components list.
    piPub->GetDirectChildren (CATICkeParm::ClassName(),spLst);
    cout << " The number of direct children supporting CATICkeParm is (4 expected) " ;
    cout << spLst.Size() << endl;
    
    // Retrieve the total list of children supporting CATICkeParm and display its size
    spLst.RemoveAll();
    piPub->GetAllChildren (CATICkeParm::ClassName(),spLst);
    cout << " The total number of children supporting CATICkeParm is (7 expected) " ;
    cout << spLst.Size() << endl;
    
    /*
    ** Create a relation
    **       Create a formula ("a=3deg")
    **       Append this formula to the published parameter
    **       Clean the previous list of children 
    **       Get the list of direct children supporting CATICkeRelation
    **       Display the number of relations
    **       
    */
    
    // Create a formula and append it to the published parameter
    CATCkeListOf(Parm) spLi;
    CATICkeRelation_var spRel = piFact->CreateFormula("","","",spPp2,&spLi,
        "3deg",
        NULL_var,
        CATCke::False);
    piPub->Append(spRel);
    
    // Retrieve the list of direct children supporting CATICkeRelation
    spLst.RemoveAll();
    piPub->GetDirectChildren (CATICkeRelation::ClassName(),spLst);
    cout << " The number of direct children supporting CATICkeRelation is (1 expected) " ;
    cout << spLst.Size() << endl;
    
    // Remove the parameter "a" and the formula from the published parameter
    piPub->RemoveChild(spPp2);
    piPub->RemoveChild(spRel);
    
    // Retrieve the modified list of direct children ("a" has been removed) 
    spLst.RemoveAll();
    piPub->GetDirectChildren (CATICkeParm::ClassName(),spLst);
    cout << " The number of direct children supporting CATICkeParm is (3 expected) " ;
    cout << spLst.Size() << endl;
    
    // Retrieve the modified list of direct children supporting CATICkeRelation
    spLst.RemoveAll();
    piPub->GetDirectChildren (CATICkeRelation::ClassName(),spLst);
    cout << " The number of direct children supporting CATICkeRelation is (0 expected) " ;
    cout << spLst.Size() << endl;
    
    // Now we use a standard visitor to explore the feature.
    CATLISTV(CATBaseUnknown_var) list;
    CATIVisitor_var aStandardVisitor = piFact->CreateStandardVisitor(IID_CATICkeParm, &list);

    piPub->VisitChildren(aStandardVisitor, 1);

    //In the end the list is filled with all the CATICkeParm found on the feature and its references.
    int size = list.Size();
    int i = 0;
    for(i=1; i <=size; i++)
    {
        CATICkeParm_var p = list[i];
        cout << "From the standard visitor: parameter name is: " << p->Name().ConvertToChar() << endl;
    }



    //Otherwise you can create you own visitor (see CAALifBasis.m/src/CAALifMyVisitor).
    //This visitor will be triggered by the method VisitChildren implemented by the extension
    // CAALifBasis.m/src/CAALifMyPublisher.
    cout << endl << endl;
    cout << " Using a visitor to recursively extract the name of all the parameters inside a feature. " << endl;
    CAALifMyVisitor *myVisitor= new CAALifMyVisitor();

	if (myVisitor != NULL)
	{
		CATIVisitor *piVisitor=NULL;
		HRESULT hr = myVisitor->QueryInterface(IID_CATIVisitor,(void **)&piVisitor);
		if (SUCCEEDED(hr))
		{
			piPub->VisitChildren(piVisitor, 1);
			piVisitor->Release(); 
			piVisitor=NULL;
		}
		else
		{
			cout << " QueryInterface for CATIVisitor failed " << endl;
		}
		myVisitor->Release();
    
	}

	CAALifEventsExit( piContainer, CAALifOk );
	piSpecAttrAccessOnLength0->Release();
	piSpecAttrAccessOnLength1->Release();
	piSpec0->Release();
	piSpec1->Release();
    
    piFact->Release();
    piPub->Release();
    piPub1->Release();
    
    piSpecAttrAccessOnLength0 = NULL;
    piSpecAttrAccessOnLength1 = NULL;
    piSpec0 = NULL;
    piSpec1 = NULL;
    
    piFact = NULL;
    piPub = NULL;
    piPub1 = NULL;
        
    return CATCke::True;
}





int main (int argc, char** argv)
{
    int rc = 0;
    
    CAALifServices services;
    
    // Initialize the session
    rc = services.CAALifInitSession ();
    if( rc != CAALifOk )
        return rc;
    
    CAALifPublish0();
    
    // Close the session and environment
    services.CAALifCloseSession();
    
    return rc;
};


