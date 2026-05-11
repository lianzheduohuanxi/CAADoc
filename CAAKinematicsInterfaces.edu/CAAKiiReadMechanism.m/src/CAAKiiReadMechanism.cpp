/**
 * @quickReview SVV 02:06:27
 * @quickReview SVV 02:07:02
 * @quickReview SVV 03:03:31
 * @quickReview SVV 04:01:07
 * @quickReview RKN 04:10:25
 * @quickreview Q42 16:05:30 output path  english transation of Path de la sortie IR446369
 */
/**
 * @fullreview JCS RKN EER 01:12:04
 * @error UDOO Y err_1 (.h) =/constructeur en private + destructeur virtuel
 * @error MISC Y err_2 argc doit initialise a 0
 * @error UNP Y err_3 Doit t on tester jointList ? Ou on fait confiance au HR
 * @error UNP Y err_4 (*jointList)[i] non teste
 * @error UNP Y err_5 piJoint non teste
 * @error UNP Y err_6 Doit t on tester productList ? Ou on fait confiance au HR
 * @error MISC Y err_7 On ne sort pas les valeurs des Frames de liaions sur outputFile
 * @error BCMM Y err_8 Faire un delete de parm si necessaire
 * @error UNP Y err_9 Doit t on tester paConstraints ? Ou on fait confiance au HR
 * @error UNP Y err_10 Doit t on tester paConnectors ? Ou on fait confiance au HR
 * @error BCMM Y err_11 Faire un Release sur piJoint
 * @error UNP Y err_12 Doit t on tester cmdList et  (*cmdList)[l] ? Ou on fait confiance au HR
 * @error UNP Y err_13 tester le HRESULT du QueryInterface
 * @error BCMM Y err_14 Faire un Release sur piCmd
 * @error UDOO Y err_15 Mise a NULL de piMechanismFactoryOnDocument
*/
// --------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//============================================================================================
//  Abstract:
//  ---------
//
//  Batch program which reads the mechanism contained in a *.CATProduct
//  document and write the related data in a text file.
//
//  Illustrates :
//     Document loading in session
//     Access to a mechanism within document
//     Access to the mechanism structure within a mechanism
//
//============================================================================================
//  Usage:
//  ------
//
//  Type        : CAAKiiReadMechanism inputDirectory inputFile.CATProduct outputDirectory
//
//  Inputs      :
//     inputDirectory        : directory containing the file
//     inputFile.CATProduct  : name of the file
//     outputDirectory       : directory which will contain the output text file
//
//  Return Code :
//     0 : OK
//     1 : Bad input (argument number or file)
//     2 : Problem in loading the file
//     3 : Kinematics error
//
// If required, uncomment traces before building this sample
//============================================================================================
//  History:
//  --------
//  07/01/2004 : RKN : CATDocumentServices::Open method is deprecated, 
//               and replaced with CATDocumentServices::OpenDocument.
//  25/10/2004 : SVV : Switch from CATInteractiveApplication to Main() base batch.
//  
//============================================================================================

// Standard C++ library
#include <iostream.h>
#include <fstream.h>

// System Frameworks
#include "CATBaseUnknown.h"
#include "CATString.h"

// Access to documents Frameworks
#include "CATLib.h" 
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "LifeCycleObject.h"

// Product Structure Frameworks
#include "CATIProduct.h"
#include "CATIAlias.h"

// Kinematics Frameworks
#include "CATIKinMechanismFactory.h"
#include "CATIKinMechanism.h"
#include "CATIKinJoint.h"
#include "CATIKinCmd.h"

//============================================================================================
// 1 - Check arguments
// 2 - Load the CATProduct and make it ready
// 3 - Read all the mechanisms of the document
// 3 - Open the output file
// 5 - Read information of all joints
// 6 - Read information of all commands
// 7 - Read information of the mechanism
//============================================================================================

int main(int argc, char ** argv)
{
  int returnCode = 0;

  //==========================================================================================
  // 1 - Check arguments
  //==========================================================================================

  if(4 != argc)
  {
    /*    cout << "Usage: CAAKiiReadMechanism inputDirectory inputFile.CATProduct"<< endl; */
    returnCode = 1;
    return returnCode;
  }
  CATString inputName(argv[2]);
  CATString suffix = inputName.SubString(inputName.GetLengthInChar()-11,11);
  if (0 != suffix.compare(".CATProduct"))
  {
    /*    cout << "inputFile is not a CATProduct"<< endl; */
    returnCode = 1;
    return returnCode;
  }
  
  //==========================================================================================
  // 2 - Load the CATProduct and make it ready
  //==========================================================================================
  char inputPath[CATMaxPathSize]; 
  CATMakePath (argv[1], argv[2], inputPath);
  
  HRESULT HR = E_FAIL;
  CATSession* pSession = NULL;
  HR = Create_Session("CAAKiiReadMechanismSession", pSession);
  if (!SUCCEEDED(HR))
  {
    /*    cout << "Session could not be created"<< endl; */
    returnCode = 2;
    return returnCode;
  }
  CATDocument* pDocument = NULL;
  HR = CATDocumentServices::OpenDocument(inputPath, pDocument);
  if (!SUCCEEDED(HR))
  {
    /*    cout << inputPath << " could not be loaded"<< endl; */
    returnCode = 2;
    return returnCode;
  }

  //==========================================================================================
  // 3 - Open the output file
  //==========================================================================================
  CATString name = inputName.SubString(0,inputName.GetLengthInChar()-11) + ".txt";
  char outputPath[CATMaxPathSize]; 
  CATMakePath (argv[3], name.CastToCharPtr(), outputPath);
  ofstream outputFile;
  outputFile.open (outputPath, ios::out);
  outputFile << "Mechanisms_from " << inputPath << endl << flush;
  printf("output path : %s\n",outputPath);
  
  //==========================================================================================
  // 4 - Read all the mechanisms of the document
  //==========================================================================================
  CATIKinMechanismFactory* piMechanismFactoryOnDocument = NULL;
  HR = pDocument->QueryInterface(IID_CATIKinMechanismFactory,(void**)&piMechanismFactoryOnDocument);
  if (SUCCEEDED(HR))
  {
    CATLISTP(CATBaseUnknown) ListOfMechanisms;
    HR = piMechanismFactoryOnDocument->ListInstances (ListOfMechanisms);
    if (SUCCEEDED(HR))
    {
      // Read all the mechanisms of the document
      int nbMechanisms = ListOfMechanisms.Size();
      CATBaseUnknown * pMechanism_bu = NULL;
      int i = 1;
      for (;i<=nbMechanisms;i++)
      {
        CATIKinMechanism* piMechanism = NULL;
        pMechanism_bu = ListOfMechanisms[i];
        if (pMechanism_bu &&
            SUCCEEDED(pMechanism_bu->QueryInterface(IID_CATIKinMechanism,(void**)&piMechanism)))
        {
          // Print the name of the mechanism
          CATIAlias* piAliasOnMechanism = NULL;
          if (SUCCEEDED(piMechanism->QueryInterface(IID_CATIAlias,(void**)&piAliasOnMechanism)))
          {
            outputFile << "Mechanism " << piAliasOnMechanism->GetAlias().ConvertToChar() <<endl << flush;
            piAliasOnMechanism->Release();
            piAliasOnMechanism = NULL;
          }
          
          //======================================================================================
          // 5 - Read information of all joints
          //======================================================================================
          CATLISTP(CATBaseUnknown)* jointList=NULL;
          CATBaseUnknown * pJoint_bu = NULL;
          HR = piMechanism->GetJointList(&jointList);
          if (SUCCEEDED(HR) && jointList)
          {
            outputFile << "   Joint" <<endl << flush;
            
            int nbJoints = jointList->Size();
            for (int j = 1;j<=nbJoints; j++)
            {
              outputFile << "      " << j << " : ";
              
              // Get the type of joint
              CATIKinJoint* piJoint = NULL;
              pJoint_bu = (*jointList)[i];
              if (pJoint_bu && 
                SUCCEEDED(pJoint_bu->QueryInterface(IID_CATIKinJoint,(void**)&piJoint)))
              {
                const char* JointType = NULL;
                HR = piJoint->GetType(&JointType);
                if (SUCCEEDED(HR)) 
                {
                  outputFile << JointType << "; ";
                }
                
                // Get the parts involved in the joint
                int nbPartInJoint = 0;
                CATLISTP(CATBaseUnknown)* productList=NULL;
                HR = piJoint->GetProductList(&productList);
                if (SUCCEEDED(HR) && productList)
                { 
                  nbPartInJoint = productList->Size();
                  outputFile << nbPartInJoint << " products; ";
                  delete productList;
                  productList = NULL;
                }
                
                // Get the first frame from the joint definition
                double* axis1 = NULL;
                HR = piJoint->GetFrame(1,&axis1);
                if (axis1)
                {
                  delete [] axis1;
                  axis1 = NULL;
                }
                
                // Get the second frame from the joint definition
                double* axis2 = NULL;
                HR = piJoint->GetFrame(2,&axis2);
                if (axis2)
                {
                  delete [] axis2;
                  axis2 = NULL;
                }
                
                // Get the ratio of the joint
                
                double ratio;
                HR = piJoint->GetRatio(&ratio);
                
                // Get the parameters of the joint
                double* parm = NULL;
                int oSize = 0;
                
                HR = piJoint->GetJointValues(&parm,&oSize);
                
                if (parm)
                {
                  delete [] parm;
                  parm = NULL;
                }
                
                //  Get the constraints of the joint
                int nbConstraints = 0;
                CATLISTP(CATBaseUnknown)* paConstraints = NULL;
                HR = piJoint->GetConstraints(&paConstraints);
                if (SUCCEEDED(HR) && paConstraints)
                {
                  nbConstraints = paConstraints->Size();
                  outputFile << nbConstraints << " constraints; "; 
                  delete paConstraints;
                  paConstraints = NULL;
                }
                
                //  Get the connectors of the joint
                int nbConnectors = 0;
                CATLISTP(CATBaseUnknown)* paConnectors = NULL;
                HR = piJoint->GetConnectors(&paConnectors);
                if (SUCCEEDED(HR) && paConnectors) 
                {
                  nbConnectors = paConnectors->Size();
                  outputFile << nbConnectors << " connectors; ";
                  delete paConnectors;
                  paConnectors = NULL;
                }
                
                outputFile << endl << flush;
                piJoint->Release();
                piJoint = NULL;
              }
              outputFile << "   EndJoint" <<endl << flush;
            }
            delete jointList;
            jointList = NULL;
          }
          
          //======================================================================================
          // 6 - Read information of all commands
          //======================================================================================
          CATLISTP(CATBaseUnknown)* cmdList = NULL;
          CATBaseUnknown * pCmd_bu = NULL;
          HR = piMechanism->GetCmdList(&cmdList);
          if (SUCCEEDED(HR) && cmdList)
          {
            outputFile << "   Command" <<endl << flush;
            
            int nbCmds = cmdList->Size();
            for (int l = 1;l<=nbCmds;l++)
            {
              outputFile << "      " << l << " : ";
              CATIKinCmd* piCmd = NULL;
              pCmd_bu = (*cmdList)[l];
              
              if (pCmd_bu)
              {
                if (SUCCEEDED(pCmd_bu->QueryInterface(IID_CATIKinCmd,(void**)&piCmd)))
                {
                
                  // Get the command type
                  const char* cmdType = NULL;
                  HR =piCmd->GetType(&cmdType);
                  if (SUCCEEDED(HR)) 
                  {
                    outputFile << cmdType << "; ";
                  }
                
                  // Get the joint associated to the command
                  CATIKinJoint* papiAssociatedJoint = NULL; 
                  HR =piCmd->GetJoint(&papiAssociatedJoint);
                  if (SUCCEEDED(HR))
                  {
                    outputFile << "joint Ok;";
                    papiAssociatedJoint->Release();
                    papiAssociatedJoint = NULL;
                  }
                  outputFile << endl << flush;
                  piCmd->Release();
                  piCmd = NULL;
                }
                pCmd_bu->Release();
                pCmd_bu = NULL;
              }
            }
            outputFile << "   EndCommand" << endl << flush;
            
            // Get the value of each command of the mechanism
            //        CATListOfDouble ListCommandValue;
            //HR = piMechanism->GetCmdValues(&ListCommandValue);
            //        if (SUCCEEDED(HR))
            //        {
            //          outputFile << "   Command values : ";
            //          for (int l = 0; l < ListCommandValue.Size(); l++) {outputFile << ListCommandValue[l] << "; ";}
            //          outputFile << endl << flush;
            //        }
            if (cmdList)
            {
              delete cmdList;
              cmdList = NULL;
            }
          }
          
          //======================================================================================
          // 7 - Read information of the mechanism
          //======================================================================================
          
          // Get the fixed product of the mechanism
          CATIProduct* piProductOnFixedProduct = NULL;
          if (SUCCEEDED(piMechanism->GetFixedProduct(&piProductOnFixedProduct)))
          {
            CATIAlias* piAliasOnFixedProduct = NULL;
            if (SUCCEEDED(piProductOnFixedProduct->QueryInterface(IID_CATIAlias,(void**)&piAliasOnFixedProduct)))
            {
              outputFile << "   Fixed part : " << piAliasOnFixedProduct->GetAlias().ConvertToChar() << endl << flush;
              piAliasOnFixedProduct->Release();
              piAliasOnFixedProduct = NULL;
            }
            piProductOnFixedProduct->Release();
            piProductOnFixedProduct = NULL;
          }
          
          // Get the list of the products involved in the mechanism
          int nbInvolvedProducts = 0;
          CATLISTP(CATBaseUnknown)* papiProductOfMechanism = NULL;
          HR = piMechanism->GetProductList (&papiProductOfMechanism);
          if (SUCCEEDED(HR) && papiProductOfMechanism)
          {
            nbInvolvedProducts = papiProductOfMechanism->Size();
            
            outputFile << "   Products involved : " << nbInvolvedProducts << "; " << endl << flush;
            delete papiProductOfMechanism;
            papiProductOfMechanism = NULL;
          }
          
          // Clean the environment
          piMechanism->Release();
          piMechanism = NULL;
          
          outputFile << "EndMechanism" <<endl << flush;
        }
      }
      // Release the elements of the list
      for (i = 1;i<=nbMechanisms;i++)
      {
        pMechanism_bu = ListOfMechanisms[i];
        if (pMechanism_bu)
        {
          pMechanism_bu->Release();
          pMechanism_bu = NULL;
        }
      }
      ListOfMechanisms.RemoveAll();
    }
    piMechanismFactoryOnDocument->Release();
    piMechanismFactoryOnDocument = NULL;
  }    
  // Close the output file
  outputFile.close();
  
   // Close the document
  LifeCycleObject *piLifeCycleOfDocument = NULL;
  HR = pDocument->QueryInterface(IID_LifeCycleObject,(void**)&piLifeCycleOfDocument);
  if (SUCCEEDED(HR))
  {
    piLifeCycleOfDocument->remove();
    piLifeCycleOfDocument->Release();
    piLifeCycleOfDocument = NULL;
  }
  
  // End session	
  Delete_Session("CAAKiiReadMechanismSession");
  
  if (SUCCEEDED(HR)) returnCode = 0;
  else returnCode = 3;

  return returnCode;
}
