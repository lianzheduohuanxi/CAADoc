//------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2006


//=============================================================================
//  Abstract of Use Case "CAABatBatchSample":
//  ------------------------------------
//
//  This Use Case illustrates how to create a CAA V5 batch
//  To make a V5 batch you need 3 things :
//  - An XML descriptor file which describe your batch
//  - An XML parameter file which describe the inputs and outputs of your batch
//  - A library containing the implementation of your batch code through the symbol batchmain
//
// This cpp file is an example of a batch implementation. 
// The descriptor file is located in CNext/resources/batchdesc/batchSample.xml
//   of CAABatchInfrastructure.edu
// The parameter file is located in FunctionTests/InputData/ParamSample.xml
//
// This batch sample just take as input a list of .model files and rename it to .CATPart files.
// this batch as any V5 batch does not use its command line to read its input arguments but 
// get it from its XML parameter file.
//
// It is up to the batch writer to formalize the inputs and outputs of the batch with XML tags in 
// the XML parameter file. To do this the batch writer can use predefined XML tag : <file>, 
// <folder>, <simple_arg>.
//
// For this batch the inputs are several .model files therefore we used the <file> tag in the
// <inputParameters> section. A "flag" also used as input, for this we used <simple_arg> tag.The
// output is a directory formalized with the <folder> tag in the <outputParameters> section
//
// From the batchmain symbol, below, the XML parameter file is accessible through the interfaces
// CATIBatch, CATIBatchElement and CATIBatchElements as shown below.

//Concerning return codes : the value of the RC of your batch is the value you'll use to return from
// batchmain symbol. Several return codes are used by BatchInfrastructure to report specific problems.
// They range from 1 to 19 (except 4 and 8)
// In addition all V5 batch agreed to give special meanings to several return code ranging from 20
// up to 49 (plus 4 and 8)
// 0 means the batch is OK
// 8 means the batch didn't produce results
// 4  means the batch produced partially its results
// You can follow the convention
//
//  TO define your own specific RC you can use the range 50 to 128, avoiding the RC used by the OS 
// (50, 126, 127, 128, ...)
  
//=============================================================================
/**
* @quickReview JNM 02:06:25
*/

#include "CATIBatchCAA.h"  
#include "CATIBatchElementCAA.h"  
#include "CATIBatchElementsCAA.h"  
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLib.h"
#include "CATStdIO.h"

#include "CATBatchAccessCAA.h"

#include "CATBatStatePubCAA.h"
#include "CATBatchPublicDefinitions.h"
#include "CATBatchParameters.h"
#include "CATBatchLogCAA.h"

#ifdef _WINDOWS_SOURCE
extern "C" __declspec(dllexport) int batchmain (int argc, char** argv);
#else
extern "C" int batchmain (int argc, char** argv);
#endif


///////////////////// batchmain symbol implementation /////////////////////

 
int batchmain (int argc, char** argv)
{
  
  //Retrieve the CATBatStatePub object used to publish a completion state for the batch
  // This state is displayed in CATUTIL, the interactive batch monitor.
  CATBatStatePubCAA* pub =  CATBatStatePubCAA::GetCAAStatePub();
  if (!pub)	return 61;

  //Set the completion state to 10
  pub->SetBatchState(10);

  //Retrieve CATIBatch the main interface to access XML parameter file from the batch  
  CATIBatchCAA* batch = GetCATIBatchCAA();
  if (!batch)	return 62;


  //Retrieves InputParameters section from the XML parameter file
  CATIBatchElementCAA* inputParameters = NULL;
  HRESULT  hr = batch->get_InputParametersCAA(inputParameters);
  if ( FAILED(hr) )
      return 63;

  //Retieves all the <file> tags included in the inputParameters section
  CATIBatchElementsCAA* inputFiles = NULL;
  hr = inputParameters->get_FileListCAA(inputFiles);
  if ( FAILED(hr) || !inputFiles )
      return 64;

  // We scan the list of <file> 
  long childrenCount = 0;
  hr = inputFiles->get_Count(childrenCount);
  CATIBatchElementCAA * elem  = NULL;
  CATListOfCATUnicodeString  listOfV4Files;

    for ( int i = 0; i<childrenCount; i++ )
      {
           hr = inputFiles->ItemCAA( i, elem  );
           if ( hr != S_OK )
             return 65;
 // for each <file> we retrieve the file path corresponding to the attribute "filePath" of the 
 // <file> tag.
           CATUnicodeString usfile_path;
           elem->get_Path(usfile_path); 

		       elem->Release();
		       elem = NULL;
// We write this path in the log of the batch available in $BATCH_HOME/uuid/uuidLog.txt 
// at the end of the execution. Default for BATCH_HOME is /tmp or C:\temp and uuid is a
// generated identifier for each batch execution.
          CATBatchLogCAA::PutInLog("filepath: ");
          CATBatchLogCAA::PutInLog(usfile_path.CastToCharPtr() );
          CATBatchLogCAA::PutInLog("\n");

// We check the file exists and we are allowed to read it.
           if (CATFileAccess(usfile_path.CastToCharPtr() , 04) != CATLibSuccess)
           {
                CATBatchLogCAA::PutInLog("Cannot access input file:  ");
                CATBatchLogCAA::PutInLog(usfile_path.CastToCharPtr() );
                CATBatchLogCAA::PutInLog("\n");
                return 66;
           }
//We store the file path in a list for later use
              listOfV4Files.Append( usfile_path );   
      }

	inputFiles->Release();
	inputFiles = NULL;

//We retrieve the <simple_arg> tag 
  CATIBatchElementCAA* oAction = NULL;
  CATUnicodeString usId = "action";

//The Parameter method can be used to retrieve any tag (<file>, <folder>, <simple_arg>) giving in // the value of its "id" attribute. Here the tag is <simple_arg id="action" value="1"/>
  hr = inputParameters->ParameterCAA(usId, oAction);

  inputParameters->Release();
  inputParameters = NULL;

  if ( FAILED(hr) )   return 67;

// As we know the type of our value we directly call the right cast method to get it as a long.
  long action = 0;
  hr = oAction->LongArg(action);
  if ( FAILED(hr) )   return 68;

  oAction->Release();
  oAction = NULL;

 //Put this result in the batch log.
 CATUnicodeString usAction;
 usAction.BuildFromNum(action);
 
  CATBatchLogCAA::PutInLog("action : ");
  CATBatchLogCAA::PutInLog(usAction);
  CATBatchLogCAA::PutInLog("\n");


 //Retrieves the outputParameters section
    CATIBatchElementCAA * outputParameters = NULL;
  hr = batch->get_OutputParametersCAA(outputParameters);
    if ( FAILED(hr) )
      return 69;


  //We retrieve the tag which id="out_dir", our output directory
  CATIBatchElementCAA* oDir = NULL;
  usId = "out_dir";

  hr = outputParameters->ParameterCAA(usId, oDir);

  outputParameters->Release();
  outputParameters = NULL;

  if ( FAILED(hr) )
      return 70;
          
    // We retrieve the path of this directory (value of the attribute "folderPath")
    CATUnicodeString us_path;
   oDir->get_Path(us_path);

   oDir->Release();
   oDir = NULL;


   CATBatchLogCAA::PutInLog("target folder path: %s ");
   CATBatchLogCAA::PutInLog(us_path.ConvertToChar() );
   CATBatchLogCAA::PutInLog("\n");
  

  pub->SetBatchState(80);
  
  
  //We retrieve the outputXML file for writing the outputs of the batch (optional)
  CATBatchParameters* output = CATBatchParameters::GetOutputParamFile();
  if (!output)	return 75;
  
  //We open the output section
  output->BeginOutput();
  


  //We rename the input model files into CATPart files to generate outputs
  char in_filename[CATMaxPathSize];
  char in_dirname[CATMaxPathSize];

  char out_fullfilename[CATMaxPathSize];
  CATUnicodeString out_fullfilename_us;

   CATBatchLogCAA::PutInLog("Output Creation \n");
 
  for (int ii=1; ii<=listOfV4Files.Size(); ii++)
  {
      memset(in_filename, '\0', CATMaxPathSize);
      memset(in_dirname, '\0', CATMaxPathSize);
      memset(out_fullfilename, '\0', CATMaxPathSize);

      CATSplitPath( listOfV4Files[ii].CastToCharPtr(), in_dirname, in_filename);
      
      char* ptr = strtok( in_filename, ".");
      sprintf(out_fullfilename, "%s%c%s.CATPart", us_path.ConvertToChar() , dir_delim, in_filename);
       
      //we write this path in outputXML
      output->InsertFile("output_file", out_fullfilename, "" , COMM_FILE_BINARY);
      
      CATBatchLogCAA::PutInLog("creating output : ");
      CATBatchLogCAA::PutInLog(out_fullfilename);
      CATBatchLogCAA::PutInLog("\n");
      out_fullfilename_us = out_fullfilename;

      CATFCopy(&(listOfV4Files[ii]), &out_fullfilename_us, 0);
    
  }
  
    //We close the output section
   output->EndOutput();
  
  
  //We close the outputXMLfile
  output->EndBuffer();

//We're done
  pub->SetBatchState(100); 
  
//We return of our batchmain symbol with the RC we want CATBatch to return.  
    return 0;
  }

