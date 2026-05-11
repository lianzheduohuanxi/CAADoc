// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAArrPathwayRun - This sample illustrates how to use the following
// interfaces CATIArrSegmentsString, CATIArrSegment, CATIArrNode
// CATIRouSection, CATIRouRectSection, CATIRouRoundSection, CATIRouRadiusCornerSection
//
//
#include <iostream.h>

// This framework
#include "CAAArrPathwayRun.h"

//CATArrangementInterfaces
#include "CATIArrSegmentsString.h"
#include "CATIArrSegment.h"
#include "CATIArrNode.h"
#include "CATIRouSection.h"
#include "CATIRouRectSection.h"
#include "CATIRouRoundSection.h"
#include "CATIRouRadiusCornerSection.h"

#include "CATRouSectionTypes.h"
#include "CATRouSetPointNames.h"
#include "CATRouNodeGeomStatus.h"

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

// Note about PathReservations
  //
  //        The PathReservation is of type "RoutableSegmentsString"(CATIArrSegmentsString)
  //
  //        It is made up of one or more "RoutableSegments"(CATIArrSegment)
  //        Two adjacent segments can have a bend radius between them. In such a case, the
  //        relevant data on the common node can be accessed (CATIArrNode)
  //
  //          Each segment in turn is made up of 2 nodes.  
  //          A Support Line always goes through the nodes on the segment, while 
  //          Center Line is the centerline of the section.
  //
  //        The skin or the envelope of the PathReservation is governed by a cross-section.
  //        This section can be obtained by using CATIArrSegmentsString. Details about the
  //        section can be found by using CATIRouSection, CATIRouRectSection, 
  //        CATIRouRoundSection, CATIRouRadiusCornerSection
  //
  //        Enums:- 
  //
  //        CATRouNodeGeomStatus has information about a node and its adjacent segments
  //        (in context of the support and center lines of the segments)
  //
  //        CATRouSectionTypes lists the possible section types
  //
  //        CATRouSetPointNames value indicates the location of the node and 
  //        also the support line on the section.
  //

//=============================================================================
//  Constructor
//=============================================================================
CAAArrPathwayRun::CAAArrPathwayRun() 
{
  cout << "CAAArrPathwayRun::CAAArrPathwayRun()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAArrPathwayRun::~CAAArrPathwayRun()
{
  cout << "CAAArrPathwayRun::~CAAArrPathwayRun()" << endl;
}

//=============================================================================
//  DoSample for Piping domain and application
//=============================================================================
int CAAArrPathwayRun::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAArrPathwayRun::DoSample Start              ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc = 0;

  // Interface pointer variables used below in the try section.
  CATDocument                   * pDoc                      = NULL;
  CATIDocRoots                  * piDocRootsOnDoc           = NULL;
  CATListValCATBaseUnknown_var  * lstPrd                    = NULL;
  CATListValCATBaseUnknown_var  * pRootProducts             = NULL;
  CATIProduct                   * piProdOnPathRes01         = NULL;
  CATIProduct                   * piProdOnPathRes02         = NULL;
  CATIProduct                   * piProdOnPathRes03         = NULL;
  CATISpecObject                * piSpecOnPathRes01         = NULL;
  CATISpecObject                * piSpecOnPathRes02         = NULL;
  CATISpecObject                * piSpecOnPathRes03         = NULL;
  CATIArrSegmentsString         * piArrSegmentsString01     = NULL;
  CATIArrSegmentsString         * piArrSegmentsString02     = NULL;
  CATIArrSegmentsString         * piArrSegmentsString03     = NULL;
  CATIArrSegment                * piArrSegment              = NULL;
  CATIRouRoundSection           * piRouRoundSection         = NULL;
  CATIRouRadiusCornerSection    * piRouRadiusCornerSection  = NULL;
  
  CATIProduct_var                 spRootPrd;
  CATBaseUnknown_var              spSpec1,      spSpec2,      spSpec3;
  CATIRouSection_var              spRouSect01,  spRouSect02,  spRouSect03; 
  CATListValCATBaseUnknown_var    oLstSegs01,   oLstSegs02,   oLstSegs03;

  CATRouSectionTypes              oSectType01,  oSectType02,  oSectType03;
  CATRouSetPointNames             oPointName01, oPointName02, oPointName03;
  
  CATUnicodeString                uSpecName01,  uSpecName02,  uSpecName03;
  CATUnicodeString                uArrPathway = "ArrPathway";
  CATUnicodeString                uArrRun     = "ArrRun";
  CATBoolean                      oStatus01,    oStatus03;

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
        // Retrieve the list of PathReservations from the Document
        // The document under study has 3 PathReservations(PR):-
        // First  PR has one segment  and round cross-section, location of sectionpoint being center-center
        // Second PR has two segments and rectangle cross-section, location of sectionpoint being bottom-center
        //               The segments are at 90 deg to each other and have a turning radius.
        // Third  PR has one segment  and rectangle cross-section with a radius fillet at all corners,
        //               location of sectionpoint being bottom-center
        // 
        // If the Section of the PathReservation / Run is Round, a handle to CATIRouRoundSection should be obtained
        // If the Section of the PathReservation / Run is NOT Round, a handle to CATIRouRectSection should be obtained

        lstPrd = spRootPrd->GetChildren();
        int iSizelstPrd = 0;
        if ( lstPrd )
          iSizelstPrd = lstPrd->Size();

        if(iSizelstPrd >= 3)
        {
          // Retrieve and scan the first PathReservation
          spSpec1 = (*lstPrd)[1];
          if ( !! spSpec1 )
          {
            if(SUCCEEDED( spSpec1->QueryInterface(IID_CATIProduct,(void**)&piProdOnPathRes01) )) 
            {
              piProdOnPathRes01 -> GetPrdInstanceName(uSpecName01);
              cout << "\n Child No. ONE Name is " << uSpecName01.ConvertToChar() << endl;
              piProdOnPathRes01 -> Release(); piProdOnPathRes01 = NULL;
            }
            
            spSpec1->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnPathRes01);
            if(piSpecOnPathRes01 && ( piSpecOnPathRes01->IsSubTypeOf(uArrPathway) || piSpecOnPathRes01->IsSubTypeOf(uArrRun) ) )
            {
              if(SUCCEEDED(piSpecOnPathRes01->QueryInterface(IID_CATIArrSegmentsString,(void**)&piArrSegmentsString01)))
              {
                if(SUCCEEDED(piArrSegmentsString01->GetSection(spRouSect01)))
                {
                  spRouSect01->GetSectionType(oSectType01);
                  if(CatRouSectionRound == oSectType01)
                  {
                    cout<< "\n\t This Child No. ONE has a Round Section"<<endl;
                    if(SUCCEEDED(spRouSect01 -> QueryInterface(IID_CATIRouRoundSection,(void**)&piRouRoundSection)))
                    {
                      double oDiameter = .0;
                      piRouRoundSection->GetDiameter(oDiameter);
                      cout << "\n\t\t The Diameter of the RoundSection of this Child No. ONE is " << oDiameter << endl;

                      piRouRoundSection->Release(); piRouRoundSection = NULL;
                    }
                  }
                }

                piArrSegmentsString01->ListSegments(oLstSegs01);
                int iSizeOfSegments = oLstSegs01.Size();
                
                for(int iSeg01=1; iSeg01<=iSizeOfSegments; iSeg01++)
                {
                  CATBaseUnknown_var spThisSegment = oLstSegs01[iSeg01];
                  if(!! spThisSegment)
                  {
                    if(SUCCEEDED(spThisSegment->QueryInterface(IID_CATIArrSegment,(void**)&piArrSegment)))
                    {
                      piArrSegment -> GetSectionSetPoint(oPointName01);
                      if(CatRouSetPointCenterCenter == oPointName01 )
                        cout << "\n\t Segment No " << iSeg01 << " ,has Section point set as CenterCenter"<<endl; 

                      CATIArrNode_var spNode1, spNode2;
                      piArrSegment->GetNodes(spNode1, spNode2);
                      if(!! spNode1)
                      {
                        cout << "\n\t Segment No " << iSeg01 << " , Node 1 "<<endl;
                        spNode1 -> IsExtremity(oStatus01);
                        if(oStatus01)
                          cout << "\n\t\t Node is Extremity Node"<<endl;
                      }
                      else
                        cout << "\n\t Segment No " << iSeg01 << " , Node 1 could not be obtained"<<endl;
                      
                      if(!! spNode2)
                      {
                        cout << "\n\t Segment No " << iSeg01 << " , Node 2 "<<endl;
                        spNode2 -> IsExtremity(oStatus01);
                        if(oStatus01)
                          cout << "\n\t\t Node is Extremity Node"<<endl;
                      }
                      else
                        cout << "\n Segment No " << iSeg01 << " , Node 2 could not be obtained"<<endl;

                      piArrSegment->Release(); piArrSegment = NULL;
                    }
                  }
                }
                piArrSegmentsString01->Release(); piArrSegmentsString01 = NULL; 
              }
              else
              {
                cout << "\n Handle to CATIArrSegmentsString from ArrPathway / ArrRun could not be obtained"<<endl;
                return 024;
              }
              piSpecOnPathRes01->Release(); piSpecOnPathRes01 = NULL;
            }
            else
            {
              cout << "\n Child No. ONE within Root Document could not be obtained "<< endl;
              return 023;
            }
          }
          
          // Retrieve and scan the second PathReservation
          spSpec2 = (*lstPrd)[2];
          if(!! spSpec2)
          {
            if(SUCCEEDED( spSpec2->QueryInterface(IID_CATIProduct,(void**)&piProdOnPathRes02) )) 
            {
              piProdOnPathRes02 -> GetPrdInstanceName(uSpecName02);
              cout << "\n Child No. TWO Name is " << uSpecName02.ConvertToChar() << endl;
              piProdOnPathRes02 -> Release(); piProdOnPathRes02 = NULL;
            }
              
            spSpec2->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnPathRes02);
            if(piSpecOnPathRes02 && ( piSpecOnPathRes02->IsSubTypeOf(uArrPathway) || piSpecOnPathRes02->IsSubTypeOf(uArrRun) ))
            {
              if(SUCCEEDED(piSpecOnPathRes02 -> QueryInterface(IID_CATIArrSegmentsString,(void**)&piArrSegmentsString02)))
              {
                if(SUCCEEDED(piArrSegmentsString02->GetSection(spRouSect02)))
                {
                  spRouSect02->GetSectionType(oSectType02);
                  if(CatRouSectionRect == oSectType02)
                  {
                    cout<< "\n\t This Child No. TWO has a Rectangle Section"<<endl;
                    DisplayRectSection(spRouSect02);
                  }
                }

                piArrSegmentsString02->ListSegments(oLstSegs02);
                int iSizeOfSegments = oLstSegs02.Size();
                // cycle through the individual segments
                for(int iSeg02=1; iSeg02<=iSizeOfSegments; iSeg02++)
                {
                  cout << "\n\t Segment Number " << iSeg02<<endl;
                  CATBaseUnknown_var spThisSegment = oLstSegs02[iSeg02];
                  if(!! spThisSegment)
                  {
                    if(SUCCEEDED(spThisSegment->QueryInterface(IID_CATIArrSegment,(void**)&piArrSegment)))
                    {
                      piArrSegment -> GetSectionSetPoint(oPointName02);
                      if(CatRouSetPointBottomCenter == oPointName02)
                        cout << "\n\t Section Point for this segment is set as BottomCenter"<<endl; 

                      DisplayNodeDataForSegment(piArrSegment);

                      piArrSegment->Release(); piArrSegment = NULL;
                    }
                  }
                }
                piArrSegmentsString02->Release(); piArrSegmentsString02 = NULL; 
              }
              else
              {
                cout << "\n Handle to CATIArrSegmentsString from ArrPathway / ArrRun could not be obtained"<<endl;
                return 026;
              }
              piSpecOnPathRes02->Release(); piSpecOnPathRes02 = NULL;
            }
            else
            {
              cout << "\n Child No. TWO 02 within Root Document could not be obtained "<< endl;
              return 025;
            }
          }
          
          // Retrieve and scan the third PathReservation
          spSpec3 = (*lstPrd)[3];
          if(!! spSpec3)
          {
            if(SUCCEEDED( spSpec3->QueryInterface(IID_CATIProduct,(void**)&piProdOnPathRes03) )) 
            {
              piProdOnPathRes03->GetPrdInstanceName(uSpecName03);
              cout << "\n Child No. THREE Name is " << uSpecName03.ConvertToChar() << endl;
              piProdOnPathRes03 -> Release(); piProdOnPathRes03 = NULL;
            }
              
            spSpec3->QueryInterface(IID_CATISpecObject,(void**)&piSpecOnPathRes03);
            if(piSpecOnPathRes03 && (piSpecOnPathRes03->IsSubTypeOf(uArrPathway) || piSpecOnPathRes03->IsSubTypeOf(uArrRun)))
            {
              if(SUCCEEDED(piSpecOnPathRes03 -> QueryInterface(IID_CATIArrSegmentsString,(void**)&piArrSegmentsString03)))
              {
                if(SUCCEEDED(piArrSegmentsString03->GetSection(spRouSect03)))
                {
                  spRouSect03->GetSectionType(oSectType03);
                  if(CatRouSectionRadiusCorner == oSectType03)
                  {
                    cout<< "\n\t This Child No. THREE has a RadiusCorner Section"<<endl;
                    if(SUCCEEDED(spRouSect03 -> QueryInterface(IID_CATIRouRadiusCornerSection,(void**)&piRouRadiusCornerSection)))
                    {
                      double oHeight = .0, oWidth = .0, oRadiusCorner = .0;
                      piRouRadiusCornerSection -> GetHeight(oHeight);
                      piRouRadiusCornerSection -> GetWidth(oWidth);
                      piRouRadiusCornerSection -> GetRadiusCorner(oRadiusCorner);

                      cout << "\n\t\t The Height of the Section of this Child No. THREE is " << oHeight << endl;
                      cout << "\n\t\t The Width of the Section of this Child No. THREE is " << oWidth << endl;
                      cout << "\n\t\t The Radius Corner of the Section of this Child No. THREE is " << oRadiusCorner << endl;

                      piRouRadiusCornerSection->Release(); piRouRadiusCornerSection = NULL;
                    }
                  }
                }

                piArrSegmentsString03->ListSegments(oLstSegs03);
                int iSizeOfSegments = oLstSegs03.Size();
              
                for(int iSeg03=1; iSeg03<=iSizeOfSegments; iSeg03++)
                {
                  CATBaseUnknown_var spThisSegment = oLstSegs03[iSeg03];
                  if(!! spThisSegment)
                  {
                    if(SUCCEEDED(spThisSegment->QueryInterface(IID_CATIArrSegment,(void**)&piArrSegment)))
                    {
                      piArrSegment -> GetSectionSetPoint(oPointName03);
                      if(CatRouSetPointBottomCenter == oPointName03)
                        cout << "\n\t Segment No " << iSeg03 << " ,has Section point set as BottomCenter"<<endl; 

                      CATIArrNode_var spNode1, spNode2;
                      piArrSegment->GetNodes(spNode1, spNode2);
                      if(!! spNode1)
                      {
                        cout << "\n\t Segment No " << iSeg03 << " , Node 1 "<<endl;
                        spNode1 -> IsExtremity(oStatus03);
                        if(oStatus03)
                          cout << "\n\t\t Node is Extremity Node"<<endl;
                      }
                      else
                        cout << "\n\t Segment No " << iSeg03 << " , Node 1 could not be obtained"<<endl;

                      if(!! spNode2)
                      {
                        cout << "\n\t Segment No " << iSeg03 << " , Node 2 "<<endl;
                        spNode2 -> IsExtremity(oStatus03);
                        if(oStatus03)
                          cout << "\n\t\t Node is Extremity Node"<<endl;
                      }
                      else
                        cout << "\n\t Segment No " << iSeg03 << " , Node 2 could not be obtained"<<endl;

                    piArrSegment->Release(); piArrSegment = NULL;
                    }
                  }
                }
                piArrSegmentsString03->Release(); piArrSegmentsString03 = NULL; 
              }
              else
              {
                cout << "\n Handle to CATIArrSegmentsString from ArrPathway / ArrRun could not be obtained"<<endl;
                return 99;
              }
              piSpecOnPathRes03->Release(); piSpecOnPathRes03 = NULL;
            }
            else
            {
              cout << "\n Child No. THREE 03 within Root Document could not be obtained "<< endl;
              return 027;
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
    cout << "CAAArrPathwayRun::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;

  if(lstPrd)                   {  delete lstPrd;                            lstPrd    = NULL;                }
  if(pRootProducts)            {  delete pRootProducts;                     pRootProducts    = NULL;         }
  if(piSpecOnPathRes01)        {  piSpecOnPathRes01 ->  Release();          piSpecOnPathRes01 = NULL;        }
  if(piSpecOnPathRes02)        {  piSpecOnPathRes02 ->  Release();          piSpecOnPathRes02 = NULL;        }
  if(piSpecOnPathRes03)        {  piSpecOnPathRes03 ->  Release();          piSpecOnPathRes03 = NULL;        }
  if(piArrSegmentsString01)    {  piArrSegmentsString01 ->  Release();      piArrSegmentsString01 = NULL;    }
  if(piArrSegmentsString02)    {  piArrSegmentsString02 ->  Release();      piArrSegmentsString02 = NULL;    }
  if(piArrSegmentsString03)    {  piArrSegmentsString03 ->  Release();      piArrSegmentsString03 = NULL;    }
  if(piArrSegment)             {  piArrSegment ->  Release();               piArrSegment = NULL;             }
  if(piRouRoundSection)        {  piRouRoundSection ->  Release();          piRouRoundSection = NULL;        }
  if(piRouRadiusCornerSection) {  piRouRadiusCornerSection ->  Release();   piRouRadiusCornerSection = NULL; }
  if(piDocRootsOnDoc)          {  piDocRootsOnDoc ->  Release();            piDocRootsOnDoc = NULL;          }
  
 
  cout <<"============================================================"<< endl;
  cout <<"===       CAAArrPathwayRun::DoSample End                ==="<< endl;
  cout <<"============================================================"<< endl;

  return rc;
}


void CAAArrPathwayRun::DisplayRectSection(CATIRouSection_var spRouSect02)
{
  if(!! spRouSect02)
  {
    CATIRouRectSection *piRouRectSection = NULL;
    if(SUCCEEDED(spRouSect02 -> QueryInterface(IID_CATIRouRectSection,(void**)&piRouRectSection)))
    {
      double oHeight = .0, oWidth = .0;
      piRouRectSection -> GetHeight(oHeight);
      piRouRectSection -> GetWidth(oWidth);
  
      cout << "\n\t\t The Height of the Section of this Child No. TWO is " << oHeight << endl;
      cout << "\n\t\t The Width of the Section of this Child No. TWO is " << oWidth << endl;

      piRouRectSection->Release(); piRouRectSection = NULL;
    }
  }
}


void CAAArrPathwayRun::DisplayNodeDataForSegment(CATIArrSegment *piArrSegment)
{  
  if(piArrSegment)
  {
    CATBoolean           oStatus02;
    CATRouNodeGeomStatus oGeomStatus;
    CATIArrNode_var      spNode1, spNode2;

    piArrSegment->GetNodes(spNode1, spNode2);
    if(!! spNode1)
    {
      cout << "\n\t Node 1 "<<endl;
      spNode1 -> IsExtremity(oStatus02);
      if(oStatus02)
        cout << "\n\t\t Node is Extremity Node"<<endl;
      else
      {
        CATAngle oAngleDegree;
        if(SUCCEEDED(spNode1 -> CalculateAngle(oAngleDegree, oGeomStatus)))
        {
          cout << "\n\t\t CalculateAngle SUCCEEDED, Angle is " << oAngleDegree << endl;
          if(SuprtLinesInt == oGeomStatus)
            cout << "\n\t\t\t Support Lines Intersect"<<endl;
        }
        else
          cout << "\n\t\t CalculateAngle FAILED"<<endl;

        CATIMovable_var  ihRelAxis;
        CATMathPoint     oPoint1;
        CATMathPoint     oPoint2;
        CATRouNodeGeomStatus  oGeomStatus_01;

        HRESULT hresCLPoint = spNode1 -> GetCenterLinePoint 
                              ( ihRelAxis, oPoint1, oPoint2, oGeomStatus_01 );
        if(SUCCEEDED(hresCLPoint))
        {
          if(SuprtLinesInt == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as SuprtLinesInt_0101"<<endl;
          if(SuprtLinesIntAndCntrLinesInt == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as SuprtLinesIntAndCntrLinesInt"<<endl;
        }
      }
    }
    else
      cout << "\n\t Node 1 could not be obtained"<<endl;
    
    if(!! spNode2)
    {
      cout << "\n\t Node 2 "<<endl;
      spNode2 -> IsExtremity(oStatus02);
      if(oStatus02)
        cout << "\n\t\t Node is Extremity Node"<<endl;
      else
      {
        CATAngle oAngleDegree2;
        CATRouNodeGeomStatus oGeomStatus2;
        if(SUCCEEDED(spNode1 -> CalculateAngle(oAngleDegree2, oGeomStatus2)))
        {
          cout << "\n\t\t CalculateAngle SUCCEEDED, Angle is " << oAngleDegree2 << endl;
          if(SuprtLinesInt == oGeomStatus)
            cout << "\n\t\t\t SuprtLinesInt"<<endl;
        }
        else
          cout << "\n\t\t CalculateAngle FAILED"<<endl;

        CATIMovable_var  ihRelAxis;
        CATMathPoint     oPoint1;
        CATMathPoint     oPoint2;
        CATRouNodeGeomStatus  oGeomStatus_01;

        HRESULT hresCLPoint = spNode1 -> GetCenterLinePoint 
                              ( ihRelAxis, oPoint1, oPoint2, oGeomStatus_01 );
        if(SUCCEEDED(hresCLPoint))
        {
          if(SuprtLinesInt == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as SuprtLinesInt_0101"<<endl;
          if(SuprtLinesIntAndCntrLinesInt == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as SuprtLinesIntAndCntrLinesInt"<<endl;
          if(NoStatus == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as NoStatus"<<endl;
          if(SuprtLinesColinearAndCntrLinesColinear == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as SuprtLinesColinearAndCntrLinesColinear"<<endl;
          if(SuprtLinesIntAndCntrLinesSkew == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as SuprtLinesIntAndCntrLinesSkew"<<endl;
          if(SuprtLinesSkew == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as SuprtLinesSkew"<<endl;
          if(ExtremityNodeConnected == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as ExtremityNodeConnected"<<endl;
          if(ExtremityNodeNotConnected == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as ExtremityNodeNotConnected"<<endl;
          if(TurnRadiusFits == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as TurnRadiusFits"<<endl;
          if(TurnRadiusTooLarge == oGeomStatus_01)
            cout << "\n\t\t GetCenterLinePoint returns CATRouNodeGeomStatus as TurnRadiusTooLarge"<<endl;
        }
      }
    }
    else
      cout << "\n\t Node 2 could not be obtained"<<endl;      
  }
}
