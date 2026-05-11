// COPYRIGHT DASSAULT SYSTEMES  2001
//==========================================================================
//
//      Abstract: This use case shows how to create a User Feature reference
//
//            The CAALoft.CATPart is opened. This document is
//            stored in CAAMechanicalCommands.edu/InputData and contains the geometry to define
//            the User Feature reference.
//
//            This document contains: 
//
//            -Part2
//              - xy plane
//              - yz plane
//              - zx plane
//              - PartBody
//              - Inputs
//                 Point.1
//                 Point.2
//              - LoftWith2Circles
//                 Line.2
//                 Plane.1
//                 Plane.2
//                 Circle.3
//                 Circle.4
//                 Extremum.4
//                 Extremum.5
//                 Loft.2               
//
//            This use case creates a User Feature reference named CAAUserFeatureSample. This 
//            feature is defined by selecting the Open body 'LoftWith2Circles'. This body is a 
//            loft (Loft.2) defined by 2 circles ( Circle.3 and Circle.4). These circles are 
//            placed on 2 planes ( Plane.1 and Plane.2). These 2 planes are set at the end of
//            a line (Line.2) defined by two points (Point.1 and Point.2). These 2 points
//            will be the inputs of the User Feature. It means that for each instantiation
//            of this User Feature two points will be necessary. (See the use case
//            CAAMcaUdfInstantiation.m)
//
//            Note that, the 2 points are stored in an another Open Body (Inputs). 
//            Setting the inputs of a given body in another body is the best way to do.
//
//            So this User Feature reference has 2 inputs and we will publish also 2 parameters: 
//            the radius of each circle. This means that for each instantiation of this user
//            User Feature reference you could change these radius.
//            We have changed the name (the role) of the first radius parameter, to show that 
//            customizing a parameter name makes it more comprehensible than using an 
//            internal name. 
//
//            After the execution of this use case you have an output document
//            CAAUdfLoft.CATPart which always contains 
//            the geometry and a feature set with the new User Feature reference:     
//
//            -Part1
//              - xy plane
//              - yz plane
//              - zx plane
//              - Userfeatures   (set of features)
//                - CAAUserFeatureSample  
//                   - 'Radius of the circle placed at the first input' 
//                   - Radius
//              - PartBody 
//              - Inputs
//              - LoftWith2Circles
//
//
///  Steps :
//    1-    Creates the section
//    2-    Opens the CAALoft document
//    3-    Retrieves the root container
//    4-    Retrieves the CATIUdfFactory interface pointer to the root container
//    5-    Creates the new User Feature reference (empty and outside the good set )
//    6-    Retrieves the geometry from the CAALoft document
//    7-    Verifies the components - mandatory step -
//    8-    Fills the new User Feature reference created at the step 5
//    9-    Checks the inputs and changes the role of the first input 
//    10-   Checks all the parameters and publishes two only 
//    11-   Sets the new User Feature reference in the User Feature set
//    12-   Saves as CAALoft into CAAUdfLoft 
//    13-   Closes the CAALoft document
//    14-   Deletes the session
//
//
//==========================================================================
// How to execute :
//
//   CAAMcaUdfCreation  InputPath [OutputPath]
//
//   with     InputPath   : $WSROOT/CAAMechanicalCommands.edu/InputData
//            OutputPath  : directory to save the CAALoft document
//
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================
//
//ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, Save document
#include "CATInit.h"                     // To retrieve the root container
#include "CATDocument.h"

// MechanicalCommands Framework
#include "CATIUdfFactory.h"              // To create a new User Feature
#include "CATIUdfFeature.h"              // To fill the new feature
#include "CATIUdfFeatureSet.h"           // To set the new feature in the feature set

//ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // For the parameters 

//MecModInterfaces Framework
#include "CATIPrtContainer.h"            // The root container

//InteractiveInterface
#include "CATIIcon.h"                    // To modify the default icon

// System Framework
#include "CATString.h"

// Local Framework
#include "CAAMcaGetGeometry.h"          // To retrieve a specific body 

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
        cout << "CAAMcaUdfCreation InputPath  [OutputPath]" << endl;
        cout << "with : InputPath : $WSROOT/CAAMechanicalCommands.edu/InputData" << endl;
        cout << "        OutputPath: Directory to save as the document with the User Feature reference" << endl;
        cout << endl;
        return 1;
    }
    cout << endl;
    cout << "The CAAMcaUdfCreation main program begins ...." << endl << endl;

    //------------------------------------------------------------------
    //1 - Creates the session
    // A session must always be created in a batch
    // environment.  Deleting the session at the end of the program is
    // also necessary.
    //------------------------------------------------------------------

    char * pSessionName = "CAA_CreationSample_Session";
    CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionName, pSession);

    if (FAILED(rc))
    {
        cout << "Error in creating session" << endl;
        return 1;
    }

    //---------------------------------------------
    //2- Opens the CAALoft document 
    //---------------------------------------------

    CATDocument *pPartDocument = NULL;
    CATString InputData = iArgv[1];
    CATString DocumentName = InputData + Slash + "CAALoft.CATPart";

    rc = CATDocumentServices::OpenDocument(DocumentName.ConvertToChar(), pPartDocument);

    if (FAILED(rc))
    {
        cout << "Error in opening the document= " << DocumentName.ConvertToChar() << endl;
        return 1;
    }
    else
    {
        cout << "   The " << DocumentName.ConvertToChar();
        cout << " document is used to create a new User Feature" << endl << endl;
    }

    //---------------------------------------------------
    // 3- Retrieves the root container
    //---------------------------------------------------

    CATInit *pInitOnDoc = NULL;
    rc = pPartDocument->QueryInterface(IID_CATInit, (void **)&pInitOnDoc);
    if (FAILED(rc))
    {
        cout << "Pb with the CATInit interface" << endl;
        return 1;
    }

    CATIPrtContainer *pIPrtCont = NULL;
    pIPrtCont = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");

    if (NULL == pIPrtCont)
    {
        cout << "The root container is NULL" << endl;
        return 1;
    }

    // No more need of this interface
    pInitOnDoc->Release();
    pInitOnDoc = NULL;

    // Retrieves the MechanicalPart 
    CATISpecObject_var spSpecObjectCAALoftPart = pIPrtCont->GetPart();
    if (NULL_var == spSpecObjectCAALoftPart)
    {
        cout << "The MechanicalPart is NULL" << endl;
        return 1;
    }

    //------------------------------------------------------------------------
    // 4- Retrieves the CATIUdfFactory interface pointer on the root container
    //------------------------------------------------------------------------

    CATIUdfFactory *pIUdfFactory = NULL;
    rc = pIPrtCont->QueryInterface(IID_CATIUdfFactory, (void **)&pIUdfFactory);
    if (FAILED(rc))
    {
        cout << "Pb with the CATIUdfFactory interface" << endl;
        return 1;
    }

    // No more need of this interface pointer
    pIPrtCont->Release();
    pIPrtCont = NULL;

    // Lists the count of User Features before the creation

    CATListValCATISpecObject_var * pUserFeatureList = NULL;
    pUserFeatureList = pIUdfFactory->GetUserFeatureList();
    if (NULL == pUserFeatureList)
    {
        cout << "   At the beginning, the document contains no User Feature" << endl << endl;
    }
    else
    {
        cout << "   The " << DocumentName.ConvertToChar();
        cout << " should contain 0 User Feature" << endl;
        return 1;
    }

    //---------------------------------------------------
    // 5- Creates the new User Feature reference
    //---------------------------------------------------

    CATUnicodeString UserFeatureName = "CAAUserFeatureSample";
    CATIUdfFeature_var spIUdfFeature = pIUdfFactory->CreateUserFeature(UserFeatureName);
    if (NULL_var == spIUdfFeature)
    {
        cout << " Error when creating the User Feature" << endl;
        return 1;
    }
    else
    {
        // The User Feature is created but outside the User Feature set
        // it's just a verification:
        //
        pUserFeatureList = pIUdfFactory->GetUserFeatureList();
        if (NULL != pUserFeatureList)
        {
            cout << " The new User Feature should'nt be in the User Feature Set" << endl;
            return 1;
        }
        cout << "   The User Feature is created empty and outside the User Feature Set" << endl << endl;
    }

    /*
      // To modify the default icon
      CATIIcon_var Icon = spIUdfFeature ;
      if ( NULL_var != Icon )
      {
         Icon->SetIconName("I_CombinedCurve");
      }
    */

    //----------------------------------------------------
    // 6- Retrieves the geometry from the CAALoft document 
    //----------------------------------------------------

    CATBaseUnknown * pLoftOpenBody = NULL;

    rc = ::CAAMcaGetGeometry(spSpecObjectCAALoftPart, "LoftWith2Circles", &pLoftOpenBody);
    if (FAILED(rc))
    {
        cout << " Error in CAAMcaGetGeometry method " << endl;
        return 1;
    }

    CATBaseUnknown_var spLoftOpenBody = pLoftOpenBody;
    pLoftOpenBody->Release();
    pLoftOpenBody = NULL;

    CATListValCATBaseUnknown_var * pComponentList = new  CATLISTV(CATBaseUnknown_var);
    pComponentList->Append(spLoftOpenBody);

    //---------------------------------------------------
    // 7- Verifies the components - mandatory step -
    //---------------------------------------------------

    CATUnicodeString  message;

    rc = spIUdfFeature->VerifyComponents(pComponentList, message);
    if (SUCCEEDED(rc))
    {
        cout << "   The verification is OK, we can use this list of components" << endl << endl;
    }
    else
    {
        cout << " Error in the CATIUdfFeature::SetComponents method" << message.ConvertToChar() << endl;
        return 1;
    }

    //---------------------------------------------------
    // 8- Fills the  new User Feature reference
    //---------------------------------------------------

    rc = spIUdfFeature->SetComponents(pComponentList);

    // No more need 
    delete pComponentList;
    pComponentList = NULL;

    if (FAILED(rc))
    {
        cout << " Error in the CATIUdfFeature::SetComponents method" << endl;
        return 1;
    }

    //--------------------------------------------------------------
    // 9- Checks the inputs - and changes the role of the first input 
    //--------------------------------------------------------------

    int Nbinput = 0;
    CATUnicodeString role;

    // The SetComponents method has determined the inputs 
    // The end user can only change their role
    rc = spIUdfFeature->GetInputsNumber(Nbinput);
    if (SUCCEEDED(rc))
    {
        cout << "   The new User Feature has " << Nbinput << " input" << endl;

        // Changes the role of the first input 
        CATUnicodeString TheRoleOfTheFirstInput = "The top point of the loft";
        rc = spIUdfFeature->SetInputRole(1, TheRoleOfTheFirstInput);
        if (FAILED(rc))
        {
            cout << " Error with CATIUdfFeature::SetInputRole" << endl;
            return 1;
        }
        for (int i = 1; i <= Nbinput; i++)
        {
            // The role is the name displayed
            rc = spIUdfFeature->GetInputRole(i, role);
            if (SUCCEEDED(rc))
            {
                cout << "      The role of the " << i << " ieme input is ->";
                cout << role.ConvertToChar() << endl;
            }
            else
            {
                cout << " Error in the CATIUdfFeature::GetInputRole" << endl;
                return 1;
            }
        }
        cout << endl;
    }
    else
    {
        cout << " Error in the CATIUdfFeature::GetInputsNumber" << endl;
        return 1;
    }

    //---------------------------------------------------
    // 10- Checks all the parameters and publishes only 2
    //---------------------------------------------------

    CATListValCATBaseUnknown_var * pInternalParametersList = NULL;

    // The SetComponents method has determined the parameters, the end user
    // can only published some of them and change the role of those published.

    // List of all parameters
    rc = spIUdfFeature->GetInternalParameters(pInternalParametersList);
    if (SUCCEEDED(rc))
    {
        int NbParameters = pInternalParametersList->Size();
        cout << "   The new User Feature has " << NbParameters << " parameters " << endl << endl;

        // we publish 2 parameters among the total list 

        // The radius of the first circle
        // See in interactive, it is the 5 element 
        CATBaseUnknown_var FirstPublishedParam = (*pInternalParametersList)[5];
        rc = spIUdfFeature->AddParameter(FirstPublishedParam);
        if (FAILED(rc))
        {
            cout << " Error in the first AddParameter method" << endl;
            return 1;
        }

        // The radius of the second circle
        // See in interactive, it is the 8 element 
        CATBaseUnknown_var SecondPublishedParam = (*pInternalParametersList)[8];
        rc = spIUdfFeature->AddParameter(SecondPublishedParam);
        if (FAILED(rc))
        {
            cout << " Error in the second AddParameter method" << endl;
            return 1;
        }

        // Change the name of the first published parameter
        CATUnicodeString Name = "Radius of the circle placed at the first input";
        rc = spIUdfFeature->SetParameterRole(FirstPublishedParam, Name);
        if (FAILED(rc))
        {
            cout << " Error in the SetParameterRole method" << endl;
            return 1;
        }

        // verifications
        CATListValCATBaseUnknown_var * pPublishedParametersList = NULL;

        rc = spIUdfFeature->GetParameters(pPublishedParametersList);
        if (FAILED(rc))
        {
            cout << " Error with GetParameters " << endl;
            return 1;
        }

        int nbpublishedParam = pPublishedParametersList->Size();
        cout << "   We have  published only " << nbpublishedParam;
        cout << " parameters whose role are:" << endl;

        for (int i = 1; i <= nbpublishedParam; i++)
        {
            Name = "";
            CATBaseUnknown_var spCurrentParam = (*pPublishedParametersList)[i];
            rc = spIUdfFeature->GetParameterRole(spCurrentParam, Name);
            if (SUCCEEDED(rc))
            {
                cout << "      " << Name.ConvertToChar() << endl;
            }
            else
            {
                cout << " Error with GetParameterRole method" << i << endl;
                return 1;
            }
        }
        cout << endl;

        delete pPublishedParametersList;
        pPublishedParametersList = NULL;

        delete pInternalParametersList;
        pInternalParametersList = NULL;

    }

    //----------------------------------------------------------------
    // 11- Sets the new User Feature reference in the User Feature set
    //----------------------------------------------------------------

    // 1 = User Feature ; 0= power copy
    CATIUdfFeatureSet_var  spIUdfFeatureSet = pIUdfFactory->GetFeatureSet(1);

    if (NULL_var != spIUdfFeatureSet)
    {
        // Now the User Feature reference is into the User Feature Set 
        spIUdfFeatureSet->AppendFeature(spIUdfFeature);
    }

    pUserFeatureList = pIUdfFactory->GetUserFeatureList();
    if (NULL != pUserFeatureList)
    {
        if (1 == pUserFeatureList->Size())
        {
            cout << "   We have set the new User Feature in the user Feature Set, now the document contains";
            cout << " 1 User Feature" << endl << endl;
        }
        else
        {
            cout << " The document should contain 1 User Feature " << endl;
            return 1;
        }

        delete pUserFeatureList;
        pUserFeatureList = NULL;
    }
    else
    {
        cout << " The document should contain 1 User Feature " << endl;
        return 1;
    }

    pIUdfFactory->Release();
    pIUdfFactory = NULL;

    //---------------------------------------------------------
    // 12- Saves the CAALoft document as CAAUdfLoft
    //---------------------------------------------------------

    CATString DocumentSaveAsName = "CAAUdfLoft.CATPart";
    if (3 == iArgc)
    {
        CATString OutputPath = iArgv[2];
        DocumentSaveAsName = OutputPath + Slash + DocumentSaveAsName;
    }

    // @CSC-Filter UNER 
    rc = CATDocumentServices::SaveAs(*pPartDocument, DocumentSaveAsName.ConvertToChar());
    if (S_OK == rc)
    {
        cout << "   The " << DocumentSaveAsName.ConvertToChar();
        cout << " document contains the new User Feature" << endl;
    }
    else
    {
        cout << "Error in saving document " << DocumentSaveAsName.ConvertToChar() << endl;
        return 1;
    }

    //---------------------------------------------------
    // 13- Closes the CAALoft document
    //---------------------------------------------------

    rc = CATDocumentServices::Remove(*pPartDocument);
    if (FAILED(rc))
    {
        cout << "Error in closing document " << DocumentName.ConvertToChar() << endl;
        return 1;
    }
    pPartDocument = NULL;


    //-------------------------
    // 14- Deletes the session
    //-------------------------

    rc = ::Delete_Session(pSessionName);
    if (FAILED(rc))
    {
        cout << "Error in deleting session" << endl;
        return 1;
    }

    cout << endl;
    cout << "The CAAMcaUdfCreation  main program is ended." << endl << endl;

    return 0;

}

