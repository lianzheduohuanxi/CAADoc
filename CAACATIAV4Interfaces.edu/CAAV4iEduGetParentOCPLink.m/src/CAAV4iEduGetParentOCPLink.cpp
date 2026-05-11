// COPYRIGHT DASSAULT SYSTEMES 2010

#include <iostream.h>
#include <stdlib.h>

#include "CATDocument.h"
#include "CATV4iV4Element.h"
#include "CATV4iFunctions.h"
#include "CATV4iPipeFunctions.h"
#include "CATIPersistent.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"

#include "fstream.h"

/*
  This batch is a sample to use the API CATV4iGetParentOCPLink of CATIAV4Interfaces
  0. Open the output file
  1. Open the model passed in argument
  2. Scan the model
  3. Scan all workspaces, sets and elements in the model
  4. Retrieve the connector occurrence in the model
  5. Retrieve the parent connector occurrence of the above connector occurrence
*/
int main(int nbarg, char ** argv)
{

	// -0--- Open the Output file
	ofstream outputFile (argv[2]);
	outputFile << "==> CATV4iTstGetParentOCPLink " << endl;

	char *pathname;
	int ier = 0, ier1 = 0, result = 0, flag = 0 ;
	boolean readOnlyFlag = 1 ;

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
	CATUnicodeString filename( pathname );
	CATDocumentServices::OpenDocument( filename, doc, readOnlyFlag );
	if (!doc)
	{
		outputFile << "*** Unable to open the model ***"<<endl;
		return 1;
	}

	CATV4iV4Element* wspElem     =NULL;
	CATV4iV4Element* nextWspElem =NULL;
	CATV4iV4Element* setElem     =NULL;
	CATV4iV4Element* nextSetElem =NULL;
	CATV4iV4Element* element     =NULL;
	CATV4iV4Element* nextElement =NULL;
	int wspType =0, endWsp =0, endSet =0, endEls =0;		

	// -2--- Scans all the model

	// ---- Retrieves the first workspace of the model: *MASTER
	if (! CATV4iGetMaster(doc, wspElem, ier) )
	{
		while(!endWsp && !ier)
		{
			if (wspElem)
				outputFile << "--"<<wspElem->GetId()<<endl;
			else
				outputFile << "??"<<endl;

			// ---- Retrieves the first set of the wsp
			if (! CATV4iGisset(wspElem, setElem, endSet, ier) )
			{
				while(!endSet && !ier)
				{
					if (setElem)
						outputFile << "----"<<setElem->GetId()<<endl;
					else
						outputFile << "????"<<endl;

					// ---- Retrieves the first element of the set
					if (! CATV4iGisels(setElem, NULL, element, endEls, ier) )
					{
						while(!endEls && !ier)
						{
							if (element)
								outputFile << "------"<<element->GetId()<<endl;
							else
								outputFile << "??????"<<endl;

							// ---- Retrieves the next elements of the set
							if (! CATV4iGisels(setElem, element, nextElement, endEls, ier) )
							{
								if (element)
								{
									int itp = 0;
									int its = 0;
									element->GetType(itp, its);
									if (itp == 61)
									{
										CATV4iV4Element* oElement = NULL;
										int retcode = CATV4iGetParentOCPLink(element, oElement, ier1);										 
										if ((retcode == 0)&&(oElement != NULL))
										{
											flag = 1 ;
											outputFile << "Valid connector occurrence ==> " << element->GetId() << " Parent connector occurrence ==> " << oElement->GetId() << " , " << "errorcode = " <<ier1 <<endl;
										}			
									}
									element->Release();
									element=NULL;
								}
								element=nextElement;
							}
							else
							{
								outputFile << "*** Unable to retrieve next element, ier=" <<ier<< endl;
								if ( element )
								{
									element->Release();
									element=NULL;
								}
								result =1;
							}
						}
					}
					else
					{
						outputFile << "*** Unable to retrieve first element, ier=" <<ier<< endl;
						if ( element )
						{
							element->Release();
							element=NULL;
						}
						result =1;
					}

					// ---- Retrieves the next set
					if (! CATV4iGisset(setElem, nextSetElem, endSet, ier) )
					{
						if ( setElem )
						{
							setElem->Release();
							setElem=NULL;
						}
						setElem=nextSetElem;
					}
					else
					{
						outputFile << "*** Unable to retrieve the next set, ier=" <<ier<< endl;
						if ( setElem )
						{
							setElem->Release();
							setElem=NULL;
						}
						result =1;
					}
				}

			}
			else
			{
				outputFile << "*** Unable to retrieve the first set, ier=" <<ier<< endl;
				if ( setElem )
				{
					setElem->Release();
					setElem=NULL;
				}
				result =1;
			}

			// ---- Retrieves the next workspace of the model
			if ( ! CATV4iGiswsp(wspElem, nextWspElem, wspType, endWsp, ier) )
			{
				if ( wspElem )
				{
					wspElem->Release();
					wspElem=NULL;
				}
				wspElem=nextWspElem;
			}
			else
			{
				outputFile << "*** Unable to retrieve next workspace, ier=" <<ier<< endl;
				if ( wspElem )
				{
					wspElem->Release();
					wspElem=NULL;
				}
				result =1;
			}
		}
		if ( flag == 0 ) 
		{
            outputFile << "<== CATV4iTstGetParentOCPLink " << endl;
			outputFile << "Valid connector occurrence not found in the model" << " , " << "errorcode = " << -1 << endl;
			result = 1;
		}
	}
	else
	{
		outputFile << "*** Unable to retrieve the MASTER, ier=" <<ier<< endl;
		result =1;
	}

	outputFile.close();

	rc = ::Delete_Session(pSessionName);
	if (FAILED(rc))
	{
		cout << "ERROR in deleting session" << endl ;
		return 1;
	}

	return result;
}
