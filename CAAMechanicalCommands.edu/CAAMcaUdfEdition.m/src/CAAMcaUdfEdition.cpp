// COPYRIGHT DASSAULT SYSTEMES  2000
//==========================================================================
//
//      Abstract: This use case shows how to edit an instance of User Feature
//
//
//            In input we have a document, CAAUdfModelWithInstances which contains two
//            user features:
//
//            -Part1
//              - xy plane
//              - yz plane
//              - zx plane
//              -Open Body.1
//                - Point.1
//                - Point.2
//                - Point.3
//                - CAAUserFeatureSample.1  
//                - The Loft With Point2 and Point3  
//
//            For the first instance ( CAAUserFeatureSample.1 ) we change:
//                 -  the value of each input
//            For the second instance ( The Loft With Point2 and Point3 ) we change:
//                 -  the value of one published parameter
//
//            The document is saved into the CAAUdfModelWithInstancesModified.
//
//
//  Steps :
//    1- Creates the session
//    2- Opens CAAUdfModelWithInstances
//    3- Retrieves the part  
//    4- Modifies the first instance 
//       4-1 Retrieves the instance in the part 
//       4-2 Begins modification
//       4-3 Verification of the input before
//       4-4 Modifies the first input
//       4-5 Modifies the second input
//       4-6 Verification of the input after
//       4-7 Ends modification
//    5- Modifies the second instance 
//       5-1 Retrieves the instance in the part 
//       5-2 Begins modification
//       5-3 Modifies one parameter
//       5-4 Ends modification
//    6- Saves as the part document
//    7- Closes part document
//    8- Closes the session
//
//
//==========================================================================
// How to execute :
//
//   CAAMcaUdfEdition InputPath [OutputPath]
//
//   with     InputPath   : $WSROOT/CAAMechanicalCommands.edu/InputData
//            OutputPath  : directory to save the modified model 
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================
//
//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, Save
#include "CATInit.h"                     // To retrieve the root container
#include "CATDocument.h"

// MechanicalCommands Framework
#include "CATIUdfFeatureInstance.h"      // To edit instances

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // For the parameters 
#include "CATIAlias.h"                   // To display the name of some inputs

//MecModInterfaces Framework
#include "CATIPrtContainer.h"            // The root container

//LiteralFeatures Framework
#include "CATICkeParm.h"                 // To modify the parameters

// Visualization Framework
#include "CATPathElement.h"              // To set new inputs

// System Framework
#include "CATString.h"

// Local Framework
#include "CAAMcaGetGeometry.h"          // To retrieve inputs from CAAUdfModelWithInstances

#include <iostream.h>

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif


//==========================================================================

int main(int iArgc, char *iArgv[])

{

    //---------------------
    // 0- Checks arguments
    //---------------------
    if ((3 != iArgc) && (2 != iArgc))
    {
        cout << endl;
        cout << "CAAMcaUdfEdition InputPath  [OutputPath]" << endl;
        cout << "with : InputPath        : $WSROOT/CAAMechanicalCommands.edu/InputData" << endl;
        cout << "        OutputPath: Directory to save as the modified document " << endl;
        cout << endl;
        return 1;
    }
    cout << endl;
    cout << "The CAAMcaUdfEdition main program begins ...." << endl << endl;

    //------------------------------------------------------------------
    //1 - Creates Session
    //------------------------------------------------------------------

    char * pSessionName = "CAA_CreationSample_Session";
    CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionName, pSession);

    if (FAILED(rc))
    {
        cout << "ERROR in creating session" << endl;
        return 1;
    }

    //----------------------------------------------------
    //2- Opens the CAAUdfModelWithInstances model
    //-----------------------------------------------------

    // The input directory 
    CATString InputData = iArgv[1];

    CATDocument *pCAAUdfModel = NULL;
    CATString CAAUdfModelDocName = InputData + Slash + "CAAUdfModelWithInstances.CATPart";

    rc = CATDocumentServices::OpenDocument(CAAUdfModelDocName.ConvertToChar(), pCAAUdfModel);

    if (FAILED(rc))
    {
        cout << "ERROR in opening the document= " << CAAUdfModelDocName.ConvertToChar() << endl;
        return 1;
    }
    else
    {
        cout << "   The " << CAAUdfModelDocName.ConvertToChar();
        cout << " is the model used to edit 2 user feature instances" << endl << endl;
    }

    //----------------------
    // 3- Retrieves the Part
    //----------------------

    CATInit *pInitOnDoc = NULL;
    rc = pCAAUdfModel->QueryInterface(IID_CATInit, (void **)&pInitOnDoc);
    if (FAILED(rc))
    {
        cout << "Error with the CATInit interface" << endl;
        return 1;
    }

    CATIPrtContainer *pIPrtContOnCAAUdfModel = NULL;
    pIPrtContOnCAAUdfModel = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

    if (NULL == pIPrtContOnCAAUdfModel)
    {
        cout << "The root container is NULL" << endl;
        return 1;
    }

    // No more need of this interface
    pInitOnDoc->Release();
    pInitOnDoc = NULL;

    // Retrieves the part 
    CATISpecObject_var spSpecObjectCAAUdfModelPart = NULL_var;
    spSpecObjectCAAUdfModelPart = pIPrtContOnCAAUdfModel->GetPart();

    // No more need of this interface
    pIPrtContOnCAAUdfModel->Release();
    pIPrtContOnCAAUdfModel = NULL;

    //--------------------------------------
    // 4- Modification on the first instance 
    //--------------------------------------

    // 4-1 Retrieves the instance in the part 
    // --------------------------------------

    CATBaseUnknown * pOnFirstInstance = NULL;
    CATIUdfFeatureInstance * pIUdfFeatInstance = NULL;
    rc = ::CAAMcaGetGeometry(spSpecObjectCAAUdfModelPart, "CAAUserFeatureSample.1", &pOnFirstInstance);
    if (FAILED(rc))
    {
        cout << "Error the model " << CAAUdfModelDocName.ConvertToChar() << " does not contain ";
        cout << " the CAAUserFeatureSample.1 feature" << endl;
        return 1;
    }
    else
    {
        rc = pOnFirstInstance->QueryInterface(IID_CATIUdfFeatureInstance, (void **)&pIUdfFeatInstance);
        if (FAILED(rc))
        {
            cout << " Error, the  CAAUserFeatureSample.1 feature is not a User Feature" << endl;
            return 1;
        }
        pOnFirstInstance->Release();
        pOnFirstInstance = NULL;

    }
    cout << "   We are modifying the first instance CAAUserFeatureSample.1" << endl << endl;

    // 4-2 Begins the modification
    // ---------------------------

    rc = pIUdfFeatInstance->Init();
    if (FAILED(rc))
    {
        cout << " Error in the Init method" << endl;
        return 1;
    }


    // 4-3 Verification of the inputs before
    // --------------------------------------

    int nbinput1 = 0;
    rc = pIUdfFeatInstance->GetInputsNumber(nbinput1);
    if (SUCCEEDED(rc) && (2 == nbinput1))
    {
        cout << "      Instance with 2 inputs whose values are before any modification:" << endl;
        CATUnicodeString InputRole;
        for (int i = 1; i <= nbinput1; i++)
        {
            pIUdfFeatInstance->GetInputRole(i, InputRole);

            CATBaseUnknown_var spUknOnInput;
            pIUdfFeatInstance->GetInput(i, spUknOnInput);

            CATIAlias_var spAliasOnInput = spUknOnInput;

            cout << "      The value of " << InputRole.ConvertToChar();
            cout << " is " << spAliasOnInput->GetAlias().ConvertToChar() << endl;
        }
        cout << endl;
    }
    else
    {
        cout << " The first instance should have 2 inputs" << endl;
        return 1;
    }

    // 4-4 Modifies the first input
    // ----------------------------

    CATBaseUnknown * pInput1 = NULL;
    rc = ::CAAMcaGetGeometry(spSpecObjectCAAUdfModelPart, "Point.1", &pInput1);
    if (FAILED(rc))
    {
        cout << "Error the model " << CAAUdfModelDocName.ConvertToChar() << " does not contain ";
        cout << " the Point.1 feature" << endl;
        return 1;
    }

    CATPathElement * pPathFirstInput1 = new CATPathElement(pInput1);
    rc = pIUdfFeatInstance->SetNewInput(1, pPathFirstInput1);
    if (FAILED(rc))
    {
        cout << " Error with the first SetNewInput " << endl;
        return 1;
    }
    pPathFirstInput1->Release();
    pPathFirstInput1 = NULL;

    pInput1->Release();
    pInput1 = NULL;

    // 4-5 Modifies the second input
    // ---------------------------

    rc = ::CAAMcaGetGeometry(spSpecObjectCAAUdfModelPart, "Point.2", &pInput1);
    if (FAILED(rc))
    {
        cout << "Error the model " << CAAUdfModelDocName.ConvertToChar() << " does not contain ";
        cout << " the Point.2 feature" << endl;
        return 1;
    }

    CATPathElement * pPathSecondInput1 = new CATPathElement(pInput1);
    rc = pIUdfFeatInstance->SetNewInput(2, pPathSecondInput1);
    if (FAILED(rc))
    {
        cout << " Error with the first SetNewInput " << endl;
        return 1;
    }
    pPathSecondInput1->Release();
    pPathSecondInput1 = NULL;

    pInput1->Release();
    pInput1 = NULL;

    // 4-6 Verification of the inputs after
    // -----------------------------------

    cout << "      After the modifications the values of each input are:" << endl;
    CATUnicodeString InputRole;
    for (int i = 1; i <= nbinput1; i++)
    {
        pIUdfFeatInstance->GetInputRole(i, InputRole);

        CATBaseUnknown_var spUknOnInput;
        pIUdfFeatInstance->GetInput(i, spUknOnInput);

        CATIAlias_var spAliasOnInput = spUknOnInput;

        cout << "      The value of " << InputRole.ConvertToChar();
        cout << " is " << spAliasOnInput->GetAlias().ConvertToChar() << endl;
    }
    cout << endl;

    // 4-7 Ends the modification
    // ---------------------------

    rc = pIUdfFeatInstance->Reset();
    if (FAILED(rc))
    {
        cout << " Error is the Reset method" << endl;
        return 1;
    }

    pIUdfFeatInstance->Release();
    pIUdfFeatInstance = NULL;

    //---------------------------------------
    // 5- Modification on the second instance 
    //---------------------------------------

    // 5-1 Retrieves the instance in the part 
    // ---------------------------------------
    CATBaseUnknown * pOnSecondInstance = NULL;
    rc = ::CAAMcaGetGeometry(spSpecObjectCAAUdfModelPart, "The Loft With Point2 and Point3", &pOnSecondInstance);
    if (FAILED(rc))
    {
        cout << "Error the model " << CAAUdfModelDocName.ConvertToChar() << " does not contain ";
        cout << " the 'The Loft With Point2 and Point3' feature" << endl;
        return 1;
    }
    else
    {
        rc = pOnSecondInstance->QueryInterface(IID_CATIUdfFeatureInstance, (void **)&pIUdfFeatInstance);
        if (FAILED(rc))
        {
            cout << " Error, the 'The Loft With Point2 and Point3' feature is not a User Feature" << endl;
            return 1;
        }
        pOnSecondInstance->Release();
        pOnSecondInstance = NULL;
    }
    cout << "   We are modifying the second instance 'The Loft With Point2 and Point3' " << endl << endl;

    // 5-2 Begins the modification
    // ---------------------------

    rc = pIUdfFeatInstance->Init();
    if (FAILED(rc))
    {
        cout << " Error is the Init method" << endl;
        return 1;
    }

    // 5-3 Modifies one parameter
    // --------------------------
    CATListValCATBaseUnknown_var * pListParam = NULL;
    rc = pIUdfFeatInstance->GetParameters(pListParam);

    if (SUCCEEDED(rc) && (NULL != pListParam))
    {
        CATUnicodeString Role;
        rc = pIUdfFeatInstance->GetParameterRole((*pListParam)[1], Role);
        if (FAILED(rc))
        {
            cout << " Error in the GetParameterRole method " << endl;
            return 1;
        }
        cout << "      Role for the first parameter=" << Role.ConvertToChar() << endl;

        // Retrieves and displays old value and sets a new value
        CATICkeParm_var spCkeParm = (*pListParam)[1];
        if (NULL_var != spCkeParm)
        {
            CATUnicodeString oldvalue = spCkeParm->Show();
            cout << "         its old value=" << oldvalue.ConvertToChar() << endl;

            // Valuate is in MKS unit
            spCkeParm->Valuate(0.050f);
            CATUnicodeString newvalue = spCkeParm->Show();
            cout << "         its new value=" << newvalue.ConvertToChar() << endl;
        }
        cout << endl;

        delete pListParam;
        pListParam = NULL;
    }
    else
    {
        cout << " Error with the GetParameters method" << endl;
        return 1;
    }

    // 5-4 Ends the modification
    // ---------------------------

    rc = pIUdfFeatInstance->Reset();
    if (FAILED(rc))
    {
        cout << " Error with the Reset method" << endl;
        return 1;
    }

    // We have finished with the second instance's edition 
    pIUdfFeatInstance->Release();
    pIUdfFeatInstance = NULL;

    //----------------------
    // 6- Saves the document
    //----------------------

    CATString DocumentSaveName = "CAAUdfModelWithInstancesModified.CATPart";
    if (3 == iArgc)
    {
        CATString OutputPath = iArgv[2];
        DocumentSaveName = OutputPath + Slash + DocumentSaveName;
    }

    // @CSC-Filter UNER
    rc = CATDocumentServices::SaveAs(*pCAAUdfModel, DocumentSaveName.ConvertToChar());
    if (S_OK == rc)
    {
        cout << "   The " << DocumentSaveName.ConvertToChar() << " document with the 2 ";
        cout << " modified User Features is saved" << endl;
    }
    else
    {
        cout << "ERROR in saving document " << DocumentSaveName.ConvertToChar() << endl;
        return 1;
    }

    //-------------------------------
    // 7- Closes the part document
    //-------------------------------

    rc = CATDocumentServices::Remove(*pCAAUdfModel);
    if (FAILED(rc))
    {
        cout << "ERROR in closing document " << CAAUdfModelDocName.ConvertToChar() << endl;
        return 1;
    }
    pCAAUdfModel = NULL;

    //-------------------
    // 8- Deletes session
    //-------------------

    rc = ::Delete_Session(pSessionName);
    if (FAILED(rc))
    {
        cout << "ERROR in deleting session" << endl;
        return 1;
    }

    cout << endl;
    cout << "The CAAMcaUdfEdition  main program is ended." << endl << endl;

    return 0;

}

