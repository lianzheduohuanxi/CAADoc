// COPYRIGHT DASSAULT SYSTEMES 2003
//============================================================================================
// Sample code for : Migration Report Use
//
// Type            : Batch program
//
// Inputs          : report and the catpart
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Run command     : mkrun -c "CAAV4iMigrationReportExtraction PathReport PathPart"
//					PathReport is the complete path of the reportfile
//	 ex CAACATIAV4Interfaces.edu\CNext\resources\graphic\MigrationReportExtraction\report.txt   
//					PathPart is the complete path of the CATPart file 
//   ex CAACATIAV4Interfaces.edu\CNext\resources\graphic\MigrationReportExtraction\attribut.CATPart   
//
// Illustrates     : o Document loading in session 
//                   o Access to part within document
//                   o Access to bodies within part 
//					 o Decode of Migration report file -> extraction of Labels and Values
//					 o Find the body in the part with the corresponding Label
//============================================================================================

/**
* @quickReview  G88  17:08:28 : VS2015 build convergence.
*/

#include <iostream.h>

// ObjectModelerBase (To open documents)
#include "CATInit.h"
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "CATIContainer.h"

#include "CATISpecObject.h"
#include "CATIBodyRequest.h"
#include "CATIPartRequest.h"
#include "CATIAlias.h"
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"

#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATSession.h"

int EndFileReached;
int LgReportFile;
int PosReportFile;

int ReadReportFile(CATUnicodeString &Name, char *&Buffer, int &LgBuffer, unsigned int &FileDesc, int &ier)
{
  // -> open a file
  // -> create a buffer in memory

  if (Name.GetLengthInByte())
  {
    FILE * table;
    // CRM : pas de new pour creer c_filename sous peine de CD et de MLK
    //char* c_filename = new char[Name.GetLengthInChar()+1] ;
    char * c_filename = (char*)Name.ConvertToChar();
    table = fopen(c_filename, "r");

    int lgtable = 0;
    char c;
    c = fgetc(table);
    while (!feof(table))
    {
      c = fgetc(table);
      lgtable++;
    }
    //		rewind(table);

        //char *pti = ( char*) table->_ptr;

    Buffer = new char[lgtable];
    //memcpy(Buffer,pti,lgtable);
  //fscanf(table, "%s", Buffer);

    //G88 : VS2015 build convergence ->
    long input_file_size = ftell(table);
    rewind(table);
    fread(Buffer, sizeof(char), input_file_size, table);
    //G88 : VS2015 build convergence <-

    fclose(table);

    // storing length
    ::LgReportFile = lgtable;

    //delete [] c_filename;  c_filename = NULL;
  }

  return 0;
}

int CloseReportFile(char *&Buffer, unsigned int &FileDesc, int &ier)
{
  if (Buffer)
  {
    delete[] Buffer; Buffer = NULL;
  }

  return 0;
}

// decode a line
//			oType = 1 -> element;		: Label | Value
//			oType = 2 -> attribute;		:       | Label : Value
// for each type=>  Label and Value are returned

int DecodeLine(char *&ioPos, int &oStart, int &oEnd, int &oType, CATUnicodeString &oLabel, CATUnicodeString &oValue)
{

  int goodline = 0;
  int EndLine = 0;
  int IsAttribute = 0;
  oStart = 0;
  oEnd = 0;

  oType = 0;

  char * CS = ioPos;
  char * Pos0 = ioPos;
  int i = 0;

  int StartLabel = 0;
  int EndLabel = 0;
  int StartValue = 0;
  int EndValue = 0;
  int lastchar = 0;

  char * ioPos0 = ioPos;
  int i0 = 0;

  // is it a valid line ? the | indicates it's a valid line
  while ((*ioPos0) != '\n')
  {
    i0 += 1;
    ioPos0 += 1;
    if ((*ioPos0) == '|')
    {
      // a valid line is found, oType is initialized with 1
      oType = 1;
      break;
    }
  }
  if (!oType)
  {
    // not a valid line, length of the line to skip
    ioPos = ioPos0;
    i = i0;
  }

  if (oType)
  {
    // count first spaces and find the real type
    ioPos0 = ioPos;
    i0 = 0;
    while ((((*ioPos0) == ' ') || ((*ioPos0) != '\t') || ((*ioPos0) != '|')) && ((*ioPos) != '\n'))
    {
      i0 += 1;
      ioPos0 += 1;
      // if no character are found before the | it is an attribut
      if ((*ioPos0) == '|')
      {
        // attribute found
        IsAttribute = 1;
        oType = 2;

        i = i0 + 1;
        ioPos = ioPos0 + 1;

        break;
      }
      else if (((*ioPos0) != ' ') && ((*ioPos0) != '\t'))
      {
        // element found
        IsAttribute = 0;
        oType = 1;
        break;
      }
    }


    // LABEL DECODING
    // first spaces filter
    while (((*ioPos) == ' ') && ((*ioPos) != '\t'))
    {
      i += 1;
      ioPos += 1;
    }
    StartLabel = i;

    lastchar = StartLabel;

    if (IsAttribute)
    {
      StartLabel = lastchar;
      while (((*ioPos) != ':'))
      {
        i += 1;
        if ((*ioPos) != ' ')
          lastchar = i;

        ioPos += 1;
      }
    }
    else
    {
      while (((*ioPos) != '|'))
      {
        i += 1;
        if ((*ioPos) != ' ')
          lastchar = i;

        ioPos += 1;
      }
    }

    EndLabel = lastchar;

    // next character after | or :
    ioPos += 1;
    i += 1;

    // VALUE
    // first spaces filtering
    while (((*ioPos) == ' '))
    {
      i += 1;
      ioPos += 1;
    }
    StartValue = i;

    lastchar = StartValue;
    // end spaces filtered
    while (((*ioPos) != '\n'))
    {
      i += 1;
      if ((*ioPos) != ' ')
        lastchar = i;
      ioPos += 1;
    }
    EndValue = lastchar;

    char *ret = "\0";

    // label transfer
    char * lab = new char[EndLabel - StartLabel + 1];
    memcpy(lab, CS + StartLabel, EndLabel - StartLabel);
    memcpy(lab + EndLabel - StartLabel, ret, 1);
    oLabel = lab;
    if (lab) { delete[]lab; lab = NULL; }

    // value transfer
    char * val = new char[EndValue - StartValue + 1];
    memcpy(val, CS + StartValue, EndValue - StartValue);
    memcpy(val + EndValue - StartValue, ret, 1);
    oValue = val;
    if (val) { delete[]val; val = NULL; }
  }

  // next line
  ioPos += 1;
  ::PosReportFile = ::PosReportFile + i + 1;
  if (::PosReportFile >= ::LgReportFile)
    ::EndFileReached = 1;


  return 0;
}

int RetrieveObject(CATListValCATBaseUnknown_var &bodyList, CATUnicodeString &iName, CATBaseUnknown *&opObj)
{

  CATIAlias* piAlias = NULL;

  for (int i = 1; i <= bodyList.Size(); i++)
  {
    CATBaseUnknown* bodyTmp = bodyList[i];
    if (bodyTmp)
    {
      bodyTmp->QueryInterface(IID_CATIAlias, (void**)&piAlias);
      CATUnicodeString CurentName;
      if (piAlias)
      {
        CurentName = piAlias->GetAlias();
        piAlias->Release();

        // retrieve the string
        int pos = CurentName.SearchSubString(iName);
        if (pos != -1)
        {
          opObj = bodyTmp;
          break;
        }
      }
    }
  }

  return 0;
}

int GetListOfBodies(CATDocument *&ipDoc, CATListValCATBaseUnknown_var &oList)
{

  if (!ipDoc)
    return 1;

  HRESULT rc = S_OK;

  CATListValCATBaseUnknown_var obodyList;

  CATIPrtPart *piPart = NULL;
  CATIPartRequest* piPartReq = NULL;
  CATIContainer_var FeatContainer = NULL_var;
  CATIPrtPart_var Part = NULL_var;

  CATIPrtContainer *pSpecContainer = NULL;
  CATInit *pDocAsInit = NULL;
  if (SUCCEEDED(ipDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit)))
  {
    // Extracts from document a reference to its part in hPartAsRequest
    pSpecContainer =
      (CATIPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");
    pDocAsInit->Release();
    pDocAsInit = NULL;
    if (pSpecContainer)
    {
      CATIPartRequest_var spPart(pSpecContainer->GetPart());

      pSpecContainer->Release();
      pSpecContainer = NULL;

      CATUnicodeString context(" ");

      spPart->GetAllBodies(context, obodyList);

      rc = (obodyList.Size()) ? S_OK : E_FAIL;
      if (FAILED(rc))
        return rc;
    }
  }

  const CATUnicodeString stdContext(" ");

  for (int curBodyIdx = 1; curBodyIdx <= obodyList.Size(); curBodyIdx++)
  {

    // Gets features holding the results for mechanical body
    CATLISTV(CATBaseUnknown_var) resultFeatures;

    CATBaseUnknown* bodyTmp = obodyList[curBodyIdx];
    if (!bodyTmp)
      break;
    CATIBodyRequest *pCurBody = NULL;

    HRESULT rc = bodyTmp->QueryInterface(IID_CATIBodyRequest, (void**)&pCurBody);

    if (FAILED(rc))
    {
      break;
    }
    else if (NULL != pCurBody)
    {
      pCurBody->GetResults(stdContext, resultFeatures);
      pCurBody->Release();
      pCurBody = NULL;

      for (int curFeatIdx = 1; curFeatIdx <= resultFeatures.Size(); curFeatIdx++)
      {
        // Gets the topological results linked to the feature
        CATISpecObject *pCurFeat = 0;

        CATBaseUnknown_var featureTmp = resultFeatures[curFeatIdx];
        if (!featureTmp)
          break;

        rc = featureTmp->QueryInterface(IID_CATISpecObject, (void**)&pCurFeat);
        if (FAILED(rc))
        {
          break;
        }

        oList.Append(pCurFeat);
      }
    }
  }

  return 0;
}

//
//
//
// **************************************************************************************
//
//
// Report Structure:
//			Element 1
//					ATT 1 : Value
//					ATT 2 : Value
//					....
//			Element 2
//
//

int main(int    iArgc,
  char** iArgv)
{
  int rc = 0;

  // Check arguments
  if (3 != iArgc) return 1;
  const char *pfileNameReport = iArgv[1];
  const char *pfileNamePart = iArgv[2];

  // Open the report file
  CATUnicodeString Name(pfileNameReport);
  char * Buffer = NULL;
  int LgBuffer = 0;
  unsigned int FileDesc = 0;
  int ier = 0;
  int errread = ::ReadReportFile(Name, Buffer, LgBuffer, FileDesc, ier);

  char * Line = Buffer;

  CATUnicodeString Label;
  CATUnicodeString Value;
  CATUnicodeString ContextLabel;
  CATUnicodeString ContextValue;

  int Type = 0;

  // create the session
  char * pSessionName = "CAA_CreationSample_Session";
  CATSession *pSession = NULL;
  HRESULT hrs = ::Create_Session(pSessionName, pSession);
  if (FAILED(hrs))
  {
    return 1;
  }

  // open the v5 document
  CATDocument *pDoc = NULL;
  HRESULT hr = CATDocumentServices::OpenDocument(pfileNamePart, pDoc);

  // get the entities of the part
  CATListValCATBaseUnknown_var bodyList;
  int errlst = GetListOfBodies(pDoc, bodyList);

  // migrated object decoding
  CATBaseUnknown * pObj = NULL;

  int Start = 0;
  int End = 0;

  char * FirstLine = Buffer;

  cout << " Pointer, label and value dump " << endl << flush;

  // skip the header
  while ((!::EndFileReached) && (Type == 0))
  {
    FirstLine = Line;
    int erdec = ::DecodeLine(Line, Start, End, Type, Label, Value);
  }

  // first line to decode is already read, we don't have to decode it again
  int firstline = 1;

  while (!::EndFileReached)
  {
    // decode line of the report
    if (!firstline)
    {
      int erdec = ::DecodeLine(Line, Start, End, Type, Label, Value);

    }
    else
      firstline = 0;

    // in this case, object label are found: *LN1, *SOL2, etc...
    if (Type == 1)
    {
      // retrieving migrated object, using modified label
      // ( because wsp name is repeated in migrated object name)
      // ex V4 Name: *SOL1
      // ex V5 Name: PartBody ( *SOL1 - wsp *MASTER -  )

      CATUnicodeString Name = "( " + Label; // Label = *SOL1, *LN1, etc..
      int err = ::RetrieveObject(bodyList, Name, pObj);

      // to do
      // ...
      // ... or
      cout << endl << endl << flush;
      cout << Label.ConvertToChar() << "   " << pObj << "    " << Value.ConvertToChar() << endl << flush;
    }
    else if (Type == 2)
    {
      // it s an attribute of the previous found object
      // Attribute: Label, Value
      // to do
      // ...
      // ... or
      cout << "       " << pObj << "   Att.:  " << Label.ConvertToChar() << "  Val.: " << Value.ConvertToChar() << endl << flush;

    }
  }

  // close the report file and delete buffer
  int errclose = ::CloseReportFile(Buffer, FileDesc, ier);

  // if the read failed
  if (::LgReportFile != ::PosReportFile)
    rc = 1;

  ::EndFileReached = 0;
  ::LgReportFile = 0;
  ::PosReportFile = 0;

  CATDocumentServices::Remove(*pDoc);
  //Ends session and drops document	

  hrs = ::Delete_Session(pSessionName);
  if (FAILED(hrs))
  {
    cout << "ERROR in deleting session" << endl;
    return 1;
  }

  return rc;
}
