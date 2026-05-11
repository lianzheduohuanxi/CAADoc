/**
 * @quickreview MVA5 15:07:02 Providing 2 ERs(ER010781, ER010782) on R25 HF level.
 * @quickreview mva5 15:06:17 IR-380050 Added traces.
 * @quickreview mva5 15:05:22 Added return codes.
 **/
// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAArrRunMngt - This sample illustrates how to use the following
// interfaces CATIArrSegmentsStringMngt, CATIArrSegmentMngt, CATIArrNodeMngt
//

#include <iostream.h>

// This framework
#include "CAAArrRunMngt.h"

//CATArrangementInterfaces
#include "CATIArrSegmentsString.h"
#include "CATIArrSegment.h"
#include "CATIArrNode.h"
#include "CATIArrSegmentsStringMngt.h"
#include "CATIArrSegmentMngt.h"
#include "CATIArrNodeMngt.h"

// Mathematics
#include "CATMathPoint.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// ProductStructure
#include "CATIProduct.h"
#include "CATInit.h"
#include "CATIMovable.h"

// System
#include "CATBaseUnknown.h"
#include "CATICStringList.h"
#include "CATBooleanDef.h"
#include "CATString.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATUnicodeString.h"

// Note about RUN
//
//        The RUN is of type "RoutableSegmentsString"(CATIArrSegmentsString and CATIArrSegmentsStringMngt)
//
//        It is made up of one or more "RoutableSegments"(CATIArrSegment and CATIArrSegmentMngt)
//        Two adjacent segments can have a bend radius between them. In such a case, the
//        relevant data on the common node can be accessed (CATIArrNode and CATIArrNodeMngt)
//
//          Each segment in turn is made up of 2 nodes.  
//          A Support Line always goes through the nodes on the segment, while 
//          Center Line is the centerline of the section.
//
//

//=============================================================================
//  Constructor
//=============================================================================
CAAArrRunMngt::CAAArrRunMngt() 
{
	cout << "CAAArrRunMngt::CAAArrRunMngt()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAArrRunMngt::~CAAArrRunMngt()
{
	cout << "CAAArrRunMngt::~CAAArrRunMngt()" << endl;
}

//=============================================================================
//  DoSample for Piping domain and application
//=============================================================================
int CAAArrRunMngt::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
	cout <<"============================================================"<< endl;
	cout <<"===       CAAArrRunMngt::DoSample Start              ==="<< endl;
	cout <<"============================================================"<< endl;

	HRESULT rc = 0;

	// Interface pointer variables used below in the try section.
	CATDocument                   * pDoc                      = NULL;
	CATIDocRoots                  * piDocRootsOnDoc           = NULL;
	CATListValCATBaseUnknown_var  * lstPrd                    = NULL;
	CATListValCATBaseUnknown_var  * pRootProducts             = NULL;
	CATIProduct                   * piProdOnRun01         = NULL;
	CATIProduct                   * piProdOnRun02         = NULL;
	CATIProduct                   * piProdOnRun03         = NULL;
	CATIProduct                   * piProdOnRun04         = NULL;
	CATISpecObject                * piSpecOnRun01         = NULL;
	CATISpecObject                * piSpecOnRun02         = NULL;
	CATISpecObject                * piSpecOnRun03         = NULL;
	CATISpecObject                * piSpecOnRun04         = NULL;
	CATIArrSegmentsString         * piArrSegmentsString01     = NULL;
	CATIArrSegmentsString         * piArrSegmentsString02     = NULL;
	CATIArrSegmentsString         * piArrSegmentsString03     = NULL;
	CATIArrSegmentsString         * piArrSegmentsString04     = NULL;
	CATIArrSegmentsStringMngt     * piArrSegmentsStringMngt03 = NULL;
	CATIArrSegmentsStringMngt     * piArrSegmentsStringMngt04 = NULL;
	CATIArrSegmentMngt            * piArrSegmentMngt          = NULL;

	CATIProduct_var                 spRootPrd;
	CATBaseUnknown_var              spSpec1,      spSpec2,      spSpec3,      spSpec4;
	CATListValCATBaseUnknown_var    oLstSegs02,   oLstSegs04;
	CATListValCATBaseUnknown_var    oLstNodes01,	oLstNodes03;

	CATUnicodeString                uSpecName01,  uSpecName02,  uSpecName03,  uSpecName04;

	CATUnicodeString                uArrRun     = "ArrRun";


	CATTry 
	{
		// Load input document
		CAAArrBaseEnv::CreateCATProductEnv (iFileToBeLoaded);

		// It is required for all batch programs accessing Routable/Arrangement
		// objects to call ApplicationInit() so that CMG geometries are saved 
		CAAArrBaseEnv::ApplicationInit();

		// Retrieve the handle to the Document
		pDoc = CAAArrBaseEnv::GetDocument();

		if(pDoc)
		{
			// Obtain the Root of the Document
			if(SUCCEEDED( pDoc->QueryInterface(IID_CATIDocRoots, (void**) &piDocRootsOnDoc) ))
			{
				pRootProducts = piDocRootsOnDoc->GiveDocRoots();
				if( pRootProducts && pRootProducts -> Size()> 0)
				{
					spRootPrd = (*pRootProducts)[1];

					delete pRootProducts; 
					pRootProducts = NULL; 
				}
				piDocRootsOnDoc -> Release(); piDocRootsOnDoc = NULL;
			}

			if(!! spRootPrd)
			{
				// Retrieve the list of products from the Document
				// The document under study has 4 Runs:-
				// First  RUN has one segment  and is used to test SetPoint method of CATIArrNodeMngt
				// Second RUN has three segments and and is used to demonstrate InsertNodes of CATIArrSegmentMngt,
				//               Two nodes are inserted on each segment.
				// Third  RUN has two segments  and is used to demonstrate DeleteNode method of CATIArrSegmentsStringMngt,
				// Fourth  RUN has three segments  and is used to demonstrate DeleteSegment method of CATIArrSegmentsStringMngt,

				CATIMovable_var hRelAxis(spRootPrd);
				lstPrd = spRootPrd->GetChildren();
				int iSizelstPrd = 0;
				if ( lstPrd )
					iSizelstPrd = lstPrd->Size();

				if(iSizelstPrd >= 4)
				{
					// Retrieve and scan the first RUN
					spSpec1 = (*lstPrd)[1];
					if ( !! spSpec1 )
					{
						if(SUCCEEDED( spSpec1->QueryInterface(IID_CATIProduct,(void**)&piProdOnRun01) )) 
						{
							piProdOnRun01 -> GetPrdInstanceName(uSpecName01);
							cout << "\n Child No. ONE Name is " << uSpecName01.ConvertToChar() << endl;
							cout << "\n Testing modification of Node location"<< endl;
							piProdOnRun01 -> Release(); piProdOnRun01 = NULL;
						}

						spSpec1->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnRun01);
						if(piSpecOnRun01 && ( piSpecOnRun01->IsSubTypeOf(uArrRun) ) )
						{
							if(SUCCEEDED(piSpecOnRun01->QueryInterface(IID_CATIArrSegmentsString,(void**)&piArrSegmentsString01)))
							{
								if(SUCCEEDED(piArrSegmentsString01->ListNodes(oLstNodes01)))
								{
									int NodeNumberToEdit = 2;
									int ListSize = oLstNodes01.Size();
									if(ListSize > 0)
									{ 
										CATBaseUnknown_var spNode = oLstNodes01[NodeNumberToEdit];
										CATIArrNode_var hArrNode(spNode);

										CATIArrNodeMngt *pArrNodeMngt = NULL;
										if(SUCCEEDED(hArrNode->QueryInterface(IID_CATIArrNodeMngt,(void**)&pArrNodeMngt)))
										{
											CATMathPoint point;

											//Retrieve CATMAthPoint of node
											hArrNode->GetPoint(hRelAxis, point);

											double x,y,z;
											x = point.GetX();
											y = point.GetY();
											z = point.GetZ();
											cout << "\n\t Modifying NODE:" << NodeNumberToEdit << endl;
											cout << "\n\t Node cordinate (x, y, z):("<<x<<", "<<y<<", "<<z<<")\n"<<endl;
											//Set new coordinates in CATMathPoint
											cout << "\n\t Increementing y cordinate by 100\n"<<endl;
											point.SetCoord(x,y+100,z);

											//Set new CATMAthPoint on node
											pArrNodeMngt->SetPoint(hRelAxis, point);
											hArrNode->GetPoint(hRelAxis, point);
											x = point.GetX();
											y = point.GetY();
											z = point.GetZ();

											cout<< "\n\t Node cordinate after modification (x, y, z):("<<x<<", "<<y<<", "<<z<<")"<<endl;

											pArrNodeMngt->Release(); pArrNodeMngt = NULL;
										}
										else
										{
											cout << "\n Handle to CATIArrNodeMngt from ArrNode could not be obtained"<<endl;
											return 036;
										}
									}
								}
								piArrSegmentsString01->Release(); piArrSegmentsString01 = NULL; 
							}
							else
							{
								cout << "\n Handle to CATIArrSegmentsString from  ArrRun could not be obtained"<<endl;
								return 035;
							}
							piSpecOnRun01->Release(); piSpecOnRun01 = NULL;
						}
						else
						{
							cout << "\n Child No. ONE within Root Document could not be obtained "<< endl;
							return 034;
						}
					}

					// Retrieve and scan the second RUN
					spSpec2 = (*lstPrd)[3];
					if(!! spSpec2)
					{
						if(SUCCEEDED( spSpec2->QueryInterface(IID_CATIProduct,(void**)&piProdOnRun02) )) 
						{
							piProdOnRun02 -> GetPrdInstanceName(uSpecName02);
							cout << "\n Child No. TWO Name is " << uSpecName02.ConvertToChar() << endl;
							cout << "\n Testing insertion of nodes"<< endl;
							piProdOnRun02 -> Release(); piProdOnRun02 = NULL;
						}

						spSpec2->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnRun02);
						if(piSpecOnRun02 && ( piSpecOnRun02->IsSubTypeOf(uArrRun) ))
						{
							if(SUCCEEDED(piSpecOnRun02 -> QueryInterface(IID_CATIArrSegmentsString,(void**)&piArrSegmentsString02)))
							{
								int NumberOfNodesToInsert = 2;
								piArrSegmentsString02->ListSegments(oLstSegs02);
								int iSizeOfSegments = oLstSegs02.Size();
								cout << "\n\t Number of segments on RUN:" << iSizeOfSegments<<endl;
								// cycle through the individual segments
								for(int iSeg02=1; iSeg02<=iSizeOfSegments; iSeg02++)
								{
									cout << "\n\t Inserting " << NumberOfNodesToInsert << " nodes on Segment Number " << iSeg02<<endl;
									CATBaseUnknown_var spThisSegment = oLstSegs02[iSeg02];
									if(!! spThisSegment)
									{
										if(SUCCEEDED(spThisSegment->QueryInterface(IID_CATIArrSegmentMngt,(void**)&piArrSegmentMngt)))
										{
											piArrSegmentMngt->InsertNodes(NumberOfNodesToInsert);

											piArrSegmentMngt->Release(); 
											piArrSegmentMngt = NULL; 
										}
										else
										{
											cout << "\n Handle to CATIArrSegmentsMngt from ArrSegment could not be obtained"<<endl;
											return 033;
										}
									}
								}
								piArrSegmentsString02->ListSegments(oLstSegs02);
								iSizeOfSegments = oLstSegs02.Size();
								cout << "\n\t Number of segments after insertion of nodes on RUN:" << iSizeOfSegments<<endl;

								piArrSegmentsString02->Release(); piArrSegmentsString02 = NULL; 
							}
							else
							{
								cout << "\n Handle to CATIArrSegmentsString from ArrRun could not be obtained"<<endl;
								return 032;
							}
							piSpecOnRun02->Release(); piSpecOnRun02 = NULL;
						}
						else
						{
							cout << "\n Child No. TWO 02 within Root Document could not be obtained "<< endl;
							return 031;
						}
					}

					// Retrieve and scan the third RUN
					spSpec3 = (*lstPrd)[4];
					if(!! spSpec3)
					{
						if(SUCCEEDED( spSpec3->QueryInterface(IID_CATIProduct,(void**)&piProdOnRun03) )) 
						{
							piProdOnRun03->GetPrdInstanceName(uSpecName03);
							cout << "\n Child No. THREE Name is " << uSpecName03.ConvertToChar() << endl;
							cout << "\n Testing deletion of nodes"<< endl;
							piProdOnRun03 -> Release(); piProdOnRun03 = NULL;
						}

						spSpec3->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnRun03);
						if(piSpecOnRun03 && ( piSpecOnRun03->IsSubTypeOf(uArrRun)))
						{
							if(SUCCEEDED(piSpecOnRun03 -> QueryInterface(IID_CATIArrSegmentsString,(void**)&piArrSegmentsString03)))
							{
								if(SUCCEEDED(piArrSegmentsString03 -> QueryInterface(IID_CATIArrSegmentsStringMngt,(void**)&piArrSegmentsStringMngt03)))
								{
									int NodeNumberToDelete = 2;
									piArrSegmentsString03->ListNodes(oLstNodes03);
									int iSizeOfNodes = oLstNodes03.Size();
									cout << "\n\t Number of nodes on RUN:" << iSizeOfNodes<<endl;
									cout << "\n\t Deleting NODE:" << NodeNumberToDelete<<endl;
									CATBaseUnknown_var spNode = oLstNodes03[NodeNumberToDelete];
									CATIArrNode_var hArrNode(spNode);
									piArrSegmentsStringMngt03->DeleteNode(hArrNode);
									piArrSegmentsString03->ListNodes(oLstNodes03);
									iSizeOfNodes = oLstNodes03.Size();
									cout << "\n\t Number of nodes after deletion on RUN:" << iSizeOfNodes<<endl;
									piArrSegmentsStringMngt03->Release(); piArrSegmentsStringMngt03 = NULL; 
								}
								else
								{
									cout << "\n Handle to CATIArrSegmentsStringMngt from ArrRun could not be obtained"<<endl;
									return 030;
								}
								piArrSegmentsString03->Release(); piArrSegmentsString03 = NULL; 
							}
							else
							{
								cout << "\n Handle to CATIArrSegmentsString from ArrRun could not be obtained"<<endl;
								return 027;
							}
							piSpecOnRun03->Release(); piSpecOnRun03 = NULL;
						}
						else
						{
							cout << "\n Child No. THREE 03 within Root Document could not be obtained "<< endl;
							return 026;
						}
					}

					// Retrieve and scan the fourth RUN
					spSpec4 = (*lstPrd)[5];
					if(!! spSpec4)
					{
						if(SUCCEEDED( spSpec4->QueryInterface(IID_CATIProduct,(void**)&piProdOnRun04) )) 
						{
							piProdOnRun04->GetPrdInstanceName(uSpecName04);
							cout << "\n Child No. FOUR Name is " << uSpecName04.ConvertToChar() << endl;
							cout << "\n Testing deletion of segments"<< endl;
							piProdOnRun04 -> Release(); piProdOnRun04 = NULL;
						}

						spSpec4->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnRun04);
						if(piSpecOnRun04 &&  piSpecOnRun04->IsSubTypeOf(uArrRun))
						{
							if(SUCCEEDED(piSpecOnRun04 -> QueryInterface(IID_CATIArrSegmentsString,(void**)&piArrSegmentsString04)))
							{
								if(SUCCEEDED(piArrSegmentsString04 -> QueryInterface(IID_CATIArrSegmentsStringMngt,(void**)&piArrSegmentsStringMngt04)))
								{
									int SegmentNumberToDelete = 2;
									piArrSegmentsString04->ListSegments(oLstSegs04);
									int iSizeOfSegments = oLstSegs04.Size();
									cout << "\n\t Number of segments on RUN:" << iSizeOfSegments<<endl;
									cout << "\n\t Deleting SEGMENT:" << SegmentNumberToDelete<<endl;
									CATBaseUnknown_var spSegment = oLstSegs04[SegmentNumberToDelete];
									CATIArrSegment_var hArrSegment(spSegment);
									piArrSegmentsStringMngt04->DeleteSegment(hArrSegment);

									piArrSegmentsString04->ListSegments(oLstSegs04);
									iSizeOfSegments = oLstSegs04.Size();
									cout << "\n\t Number of segments after deletion on RUN:" << iSizeOfSegments<<endl;

									piArrSegmentsStringMngt04->Release(); piArrSegmentsStringMngt04 = NULL; 
								}
								else
								{
									cout << "\n Handle to CATIArrSegmentsStringMngt from ArrRun could not be obtained"<<endl;
									return 025;
								}
								piArrSegmentsString04->Release(); piArrSegmentsString04 = NULL; 
							}
							else
							{
								cout << "\n Handle to CATIArrSegmentsString from ArrRun could not be obtained"<<endl;
								return 024;
							}
							piSpecOnRun04->Release(); piSpecOnRun04 = NULL;
						}
						else
						{
							cout << "\n Child No. FOUR 04 within Root Document could not be obtained "<< endl;
							return 023;
						}
					}
					delete lstPrd; 
					lstPrd = NULL; 
				}
				else
				{
					cout << "\n Children of the RootProduct could not be obtained, count = " << iSizelstPrd << endl;
					return 022;
				}
			}
			else
			{
				cout << "\n Root Product of Document could not be obtained "<<endl;
				return 021;
			}
		}
		else
		{
			cout << "\n Pointer to current Document is KO "<<endl;
			return 020;
		}

	} // end CATTry

	CATCatch (CATError, error)
	{
		cout << "CAAArrRunMngt::DoSample *** CATRethrow" << endl;
		CATRethrow;
	} 
	CATEndTry;

	if(lstPrd)                   {  delete lstPrd;                            lstPrd    = NULL;                }
	if(pRootProducts)            {  delete pRootProducts;                     pRootProducts    = NULL;         }
	if(piSpecOnRun01)        {  piSpecOnRun01 ->  Release();          piSpecOnRun01 = NULL;        }
	if(piSpecOnRun02)        {  piSpecOnRun02 ->  Release();          piSpecOnRun02 = NULL;        }
	if(piSpecOnRun03)        {  piSpecOnRun03 ->  Release();          piSpecOnRun03 = NULL;        }
	if(piSpecOnRun04)        {  piSpecOnRun04 ->  Release();          piSpecOnRun04 = NULL;        }
	if(piArrSegmentsString01)    {  piArrSegmentsString01 ->  Release();      piArrSegmentsString01 = NULL;    }
	if(piArrSegmentsString02)    {  piArrSegmentsString02 ->  Release();      piArrSegmentsString02 = NULL;    }
	if(piArrSegmentsString03)    {  piArrSegmentsString03 ->  Release();      piArrSegmentsString03 = NULL;    }
	if(piArrSegmentsString04)    {  piArrSegmentsString04 ->  Release();      piArrSegmentsString04 = NULL;    }
	if(piArrSegmentsStringMngt03){  piArrSegmentsStringMngt03 ->  Release();  piArrSegmentsStringMngt03 = NULL;}
	if(piArrSegmentsStringMngt04){  piArrSegmentsStringMngt04 ->  Release();  piArrSegmentsStringMngt04 = NULL;}
	if(piDocRootsOnDoc)          {  piDocRootsOnDoc ->  Release();            piDocRootsOnDoc = NULL;          }


	cout <<"============================================================"<< endl;
	cout <<"===       CAAArrRunMngt::DoSample End                ==="<< endl;
	cout <<"============================================================"<< endl;

	return rc;
}

