// COPYRIGHT DASSAULT SYSTEMES  2000

//=============================================================================
//  Abstract:
//  ---------
//
//  Batch program which creates a formula using the "CAAHypothenuse" user function.
//  Given x and y, two input arguments,the user function returns sqrt(x*x + y*y)
//  The function signature is created in the CAALifDicoLibrary.cpp file of the
//  CAALifBasis.m module. 
//  The function evaluator is defined in the CAALifEval.cpp file of 
//  the CAALifBasis.m module.
//  The function belongs to a package. Packages are made for structuring objects into
//  different sets. They creation is shown in CAALifDicoLibrary.cpp
//      
//
//     Checks the validity of the user function and illustrates:
//       * How to create a formula using a user function in its expression
//       * How to determine whether s formula synatx is correct
//         
//=============================================================================
//  Usage:
//  ------
//
//  Your dictionary should include the declarations below:
//  CAALifDicoLibrary		CATIAddLibrary               libCAALifBasis
//  CAALifDicoLibrary		CATICreateInstance           libCAALifBasis
//
//  In case of interactive use of this function you also must 
// define a CATPackageMethodCAALif.CATNls file containing the NLS name of this 
// package. ( for instance: PackageName = "CAALiteralFeatures";)
// Then do not forget to update the runtime view.
//  If the created library is used outside catia, do not forget to load your library.
// (see this sample, LoadPackageAndListUserFunctions() method).
// Inside catia use the Tools/Option/Parameters dialog to ask for the loading of your
// own library.
//=============================================================================

// Initialize the environment
#include "CAALifServices.h"
#include "CAALifReturnCodes.h"

// LiteralFeatures
#include "CATCke.h"
#include "CATICkeParm.h"
#include "CATICkeRelation.h"
#include "CATCkeGlobalFunctions.h"
#include "CATGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"
#include "CATICkeParmFactory.h"
#include "CATICkeFunction.h"
#include "CATICkeSignature.h"


//KnowledgeInterfaces
#include "CATITypeDictionary.h"
#include "CATIParmDictionary.h"

// ObjectModelerBase
#include "CATIContainer.h"

#include "CATISpecObject.h"

// Just required for traces
#include "iostream.h"

class CATListValCATBaseUnknown_var;

/**
* Dump the function name and its signature.
*/
HRESULT DumpUserFunctionInfo(CATICkeFunction_var ispFunction)
{
    if(ispFunction != NULL_var)
    {
        CATICkeSignature_var spSign = ispFunction;
        
        cout << " Function Name: " << spSign->Show().ConvertToChar() << endl;
    }
    return S_OK;
}



/**
* List all the functions of a package.
*/
HRESULT ListUserFunctionsForPackage(CATUnicodeString& iPackageName)
{
    CATITypeDictionary_var spTypeDictionary = NULL_var;
    
    spTypeDictionary = CATGlobalFunctions::GetTypeDictionary();
    
    
    CATListValCATBaseUnknown_var* olListOfMethods = new CATLISTV(CATBaseUnknown_var);
    HRESULT hr = spTypeDictionary->ListMethodsForPackage( iPackageName, *olListOfMethods );
    
    
    if(olListOfMethods!=NULL )
    {   
        int s = olListOfMethods->Size();
        int i;
        
        cout << iPackageName.ConvertToChar() << " Size: " << olListOfMethods->Size() << endl;
        for(i=1; i<=s; i++)
        {
            CATICkeFunction_var spFunc = (*olListOfMethods)[i];
            DumpUserFunctionInfo( spFunc );
        }
        
    }
    cout << "=======================================" << endl<<endl;
    olListOfMethods->RemoveAll();
    delete olListOfMethods;
    
    return S_OK;
}


/**
* This function shows how to load a package when its name is known.
* The CATPackageCAALifMethod was created in CAALifDicoLibrary::Add().
* The CATPackageMethodMath is a knowledgeware internal package.
* The link between the name of the package and the library it is implemented
* must be put inside a ressource file named CATPackagepackagename.CATRsc 
* (see CAALiteralFeatures.edu resources for an example). 
*/
void LoadPackageAndListUserFunctions()
{
    CATITypeDictionary_var spTypeDic = CATGlobalFunctions::GetTypeDictionary();
    
    if( spTypeDic == NULL_var)
    {
        cout << " Unable to retrieve the type dictionary. " << endl;
        return;
    }
    
    HRESULT hr;
    
    //LoadPackage force the CAALifBasis library (where the package CATPackageMethodCAALif)
    //is defined to be loaded if it was not previously loaded.
    //Pakages are very often already loaded since they are used by internal DS implementations.
    CATUnicodeString pack = "CATPackageMethodCAALif";
    hr = spTypeDic->LoadPackage( pack );
    if(FAILED(hr))
        cout << " Unable to load package or package already loaded" << pack.ConvertToChar() << endl<<endl;
    ListUserFunctionsForPackage(pack);
}




/**
* List all the loaded packages and their methods.
* It may happen that packages contain zero methods.
* This is the case when the package only contains the definition of 
* TYPES.
*/
HRESULT ListLoadedPackages()
{
    CATITypeDictionary_var spTypeDictionary = NULL_var;
    
    spTypeDictionary = CATGlobalFunctions::GetTypeDictionary();
    
    
    CATListOfCATUnicodeString listOfPackages;
    HRESULT hr = spTypeDictionary->ListPackages( listOfPackages );
    
    
    int s = listOfPackages.Size();
    int i;
    cout << endl << "Number of packages loaded: " << s << endl;
    for(i=1; i<=s; i++)
    {
        CATUnicodeString pName = listOfPackages[i];
        cout << "Package " << i << " name: " <<  pName.ConvertToChar() << endl;
    }
    cout << "=======================================" << endl << endl;
    
    
    for(i=1; i<=s; i++)
    {
        CATUnicodeString pName = listOfPackages[i];
        ListUserFunctionsForPackage( pName );
    }
    
    cout << endl;
    return S_OK;
}


int main (int argc, char** argv)
{
    int rc = 0;
    
    CAALifServices services;
    
    // Initialize the session
    rc = services.CAALifInitSession ();
    if( rc != CAALifOk )
        return rc;
    
    CATIContainer* piContainer = NULL;
    HRESULT hr = services.CAALifCreateInstanceContainer(&piContainer);
    if( FAILED(hr) )
        return CAALifKO;	
    
    //Retrieves the parameters factory
    CATICkeParmFactory* piFact = NULL;
    HRESULT rc3 = piContainer->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);
    if (FAILED(rc3)) 
    {
        cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
        piContainer->Release();
        return CAALifParmFactoryError;
    }
    
    // to force the extended language library load of the particular library we have created
    CATIParmDictionary_var spDic = CATCkeGlobalFunctions::GetParmDictionary();
    if(spDic == NULL_var)
    {
        cout << "Unable to retrieve the parameter dictionary" << endl << endl;
        return E_FAIL;
    }
	
	CATITypeDictionary_var spTypeDico = CATGlobalFunctions::GetTypeDictionary();
    if(spTypeDico == NULL_var)
    {
        cout << "Unable to retrieve the type dictionary" << endl << endl;
        return E_FAIL;
    }

	// No longer needed, thanks to index file generated with CATCkeGenerateIdx
	// spTypeDico->LoadPackage("CATPackageMethodCAALif");
    
    // Create the input arguments
    CATICkeParm_var spPp1 = piFact->CreateReal("x", 4.0);
    CATICkeParm_var spPp2 = piFact->CreateReal("y", 3.0);
    CATCkeListOf(Parm) list;
    list.Append(spPp1);
    list.Append(spPp2);
    
    // Create the parameter to be constrained
    CATICkeParm_var spPp3 = piFact->CreateReal("z", 0.0);
    
    // It is important (but not necessary) to aggregate those parameters especially in part context
    CATIParmPublisher* piPublisher = NULL;
    rc = services.CAALifRetrievePublisherFromCurrentDoc( &piPublisher );
	if (FAILED(rc) || !piPublisher)
	{
		cout << "ERROR in QueryInterface to retreive publisher from container" << endl << flush;
		return CATCke::False;
	}

	CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter, piPublisher, CATCke::True);
	if (!!spParameterSet)
	{
		CATIParmPublisher_var spParmPublisher = spParameterSet;
		if (!!spParmPublisher)
		{
			spParmPublisher->Append(spPp1);
			spParmPublisher->Append(spPp2);
			spParmPublisher->Append(spPp3);
		}
	}    

    // Create a formula using the "CAAHypothenuse"
    CATICkeRelation_var spRel = piFact->CreateFormula("Formula1","","",spPp3,
        &list,
        "CAAHypothenuse(a1,a2)*2",
        NULL_var,
        CATCke::False);
    
    // It is important (but not necessary) to aggregate those relations especially in part context
	CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation, piPublisher, CATCke::True);
	if (!!spRelationSet)
	{
		CATIParmPublisher_var spParmPublisher = spRelationSet;
		if (!!spParmPublisher)
		{
			spParmPublisher->Append(spRel);
		}
	}

    // Test whether the formula synatx is correct 
    cout << "Can the user function \"CAAHypothenuse\" be valuated" << endl;
    if (spRel->CanBeEvaluated())
    {
        double result = spPp3->Value()->AsReal(); 
        cout << "Yes - its syntax is correct" << endl;
        cout << "The resulting value is: " <<  result << endl;
        cout << "Expecting: 10" << endl;
        if( result != 10 )
            rc = E_FAIL;
    } 
    else
    {
        cout << "No - there is a syntax error in the formula" << endl;
        rc =  E_FAIL;
    }
    
    ListLoadedPackages();
    LoadPackageAndListUserFunctions();
    
    piContainer->Release();	
    piFact->Release();
	piPublisher->Release();

    if( SUCCEEDED(rc) )
        rc = services.CAALifCloseSession ();
    else
        services.CAALifCloseSession ();
    
    return rc;
};
