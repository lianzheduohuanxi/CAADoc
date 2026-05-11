#include <iostream.h>
#include <stdlib.h>

#include "CATDocument.h"
#include "CATV4iV4Element.h"
#include "CATV4iFunctions.h"
#include "CATIPersistent.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"

#include "fstream.h"


/*
  This batch is a sample to use the CAA functions of CATIAV4Interfaces.
  0) Open the output file
  1) open the model passed in argument.
  2) retrieves the firts element of the first set of the MASTER.
  3) retrieves the data of the element.
  4) release the elements.
*/
int main(int nbarg, char ** argv)
{
  // -0--- Open the Output file
  ofstream outputFile (argv[2]);

  char *pathname;
  int ier = 0, result =1;

  outputFile << "==> CAAV4iEduV4DataAccess "<<endl;

  // create the session
  char * pSessionName = "CAA_CreationSample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);
  if ( FAILED(rc) )
  {
      return 1;
  }

  // -1--- Open the model ---
  pathname = argv[1];
  CATDocument * doc=NULL;
  boolean readOnlyFlag = 1 ;
  CATUnicodeString filename( pathname );
  CATDocumentServices::OpenDocument( filename, doc, readOnlyFlag );
  outputFile << "model input: "<<pathname<<endl;

  CATV4iV4Element* masterElem=NULL;
  CATV4iV4Element* setElem=NULL;
  CATV4iV4Element* element=NULL;
  int end =0;

  // -2--- Retrieves the element to be studied

  // -2.1- Retrieves the workspace *MASTER
  if (! CATV4iGetMaster(doc, masterElem, ier) )
  {

  // -2.2- Retrieves the first set of the first wsp (*MASTER)
    if (! CATV4iGisset(masterElem, setElem, end, ier) )
    {

  // -2.3- Retrieves the first element (solid) of the set      
      if (! CATV4iGisels(setElem, NULL, element, end, ier) )
      {
        if (element)
        {
  // -3--- Retrieves the DATA of the element
  // -3.1- The Identificator
          outputFile<<"id: "<<element->GetId()<<endl;

  // -3.2- The primary and secondary types of the element
          int itp, its;
          element->GetType(itp, its);
          outputFile<<"itp: "<<itp<<" its:"<<its<<endl;        

  // -3.3- The number of the layer of the element
          int layer =-1;
          result = CATV4iGirlay(element, layer, ier);
          if (! result)
          {
            outputFile << "The number of the layer of the element is : " << layer <<endl;
          }
          else
          {
            outputFile << "*** Unable to retrieves the layer, ier= " << ier <<endl;
          }

  // -3.4- The graphical information of the element
          int oShow=-1, oPick=-1, oCol=-1, oBlink=-1, oThick=-1, oLine=-1;
          result = CATV4iGirvis( element, oShow, oPick, oCol, oBlink, oThick, oLine, ier);
          if (! result)
          {
            outputFile<<"show:"<<oShow<<", pick:"<<oPick<<", col:"<<oCol<<", blink:"<<oBlink<<", thk:"<<oThick<<", line:"<<oLine<<endl;
          }
          else
          {
            outputFile << "*** Unable to retrieves the graphical information, ier= " << ier <<endl;
          }
        }
      }
      else
        outputFile << "*** Unable to retrieve the element ***" << endl;
    }
    else
      outputFile << "*** Unable to retrieve the set ***" << endl;
  }
  else
    outputFile << "*** Unable to retrieve the workspace ***" << endl;


  // -4--- Release the elements.
  if ( element )
    element->Release();
  if ( setElem )
    setElem->Release();
  if ( masterElem )
    masterElem->Release();

  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc))
  {
     cout << "ERROR in deleting session" << endl ;
     return 1;
  }

  return result;
}
