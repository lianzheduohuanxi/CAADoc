// COPYRIGHT DASSAULT SYSTEMES 2009
#include <iostream.h>
#include <stdlib.h>

#include "CATDocument.h"
#include "CATV4iV4Element.h"
#include "CATListPtrCATV4iV4Element.h"
#include "CATV4iTubingServices.h"
#include "CATV4iFunctions.h"
#include "CATIPersistent.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"  

#include "fstream.h"
#include "math.h"
/*
  This batch is an ODT to use the methods of CATV4iTubingServices
  0) Open the output file
  1) Open the model passed in argument
  2) Scan all the model
  3) Retrieves tubing data
*/
int main(int nbarg, char ** argv)
{
  char *sessionName = "Sample";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(sessionName, pSession);
  if ((FAILED(rc)) || (NULL == pSession))
    return 1;

  // -0--- Open the Output file
  ofstream outputFile (argv[2]);
  outputFile << "==> CATV4iTstGetTubingData " << endl;

  char *pathname;
  int ier = 0, result =0;
  boolean readOnlyFlag = 1 ;

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

  // -3-- Search for tubing elements
							int TubingType = 0;
              if (element)
              {
                TubingType = CATV4iGetTubType(element);
								if (TubingType != -1) outputFile << "CATV4iGetTubType: TubingType = " << TubingType << endl;

								// Straight tube
								if (TubingType == 1) 
                {
                  outputFile << "" << endl;
                  outputFile << "** STRAIGHT TUBE ** found " << endl;
                  outputFile << "" << endl;

									// Get the tube data
									double Diameter = 0.0;
									double Extremity1[3];
									double Extremity2[3];									
									int iReturnTubGeoData = CATV4iGetTubGeoData(element, Diameter, Extremity1, Extremity2);
									if (iReturnTubGeoData == -1) 
										outputFile << "CATV4iGetTubGeoData failed" << endl;
									else if (iReturnTubGeoData == 0)
									{
										outputFile << "CATV4iGetTubGeoData succeeded" << endl;
										outputFile << "Straight tube diameter = " << Diameter << endl;
										outputFile << "Straight tube Extremity1[0] = " << Extremity1[0] << endl;
										outputFile << "Straight tube Extremity1[1] = " << Extremity1[1] << endl;
										outputFile << "Straight tube Extremity1[2] = " << Extremity1[2] << endl;
										outputFile << "Straight tube Extremity2[0] = " << Extremity2[0] << endl;
										outputFile << "Straight tube Extremity2[1] = " << Extremity2[1] << endl;
										outputFile << "Straight tube Extremity2[2] = " << Extremity2[2] << endl;
									}

									// Get all of the tube connectors
									int ConnectorType = 0;
									CATListPtrCATV4iV4Element AllTubeConnectors;
									int iReturnAllTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, AllTubeConnectors);

									if (iReturnAllTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for all connectors failed" << endl;
									else if (iReturnAllTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for all connectors succeeded" << endl;
										int NumberOfAllConnectors = AllTubeConnectors.Size();
										outputFile << "Number of straight tube all connectors = " << NumberOfAllConnectors << endl;
										if (NumberOfAllConnectors)
										{
											for ( int i=1 ; i<=NumberOfAllConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (AllTubeConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!AllTubeConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the extremity connectors
									ConnectorType = 1;
									CATListPtrCATV4iV4Element ExtremityConnectors;
									int iReturnExtTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, ExtremityConnectors);

									if (iReturnExtTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for extremity connectors failed" << endl;
									else if (iReturnExtTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for extremity connectors succeeded" << endl;
										int NumberOfExtremityConnectors = ExtremityConnectors.Size();
										outputFile << "Number of straight tube extremity connectors = " << NumberOfExtremityConnectors <<endl;
										if (NumberOfExtremityConnectors)
										{
											for ( int i=1 ; i<=NumberOfExtremityConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (ExtremityConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!ExtremityConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the branch connectors
									ConnectorType = 2;
									CATListPtrCATV4iV4Element BranchConnectors;
									int iReturnBranchTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, BranchConnectors);

									if (iReturnBranchTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for branch connectors failed" << endl;
									else if (iReturnBranchTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for branch connectors succeeded" << endl;
										int NumberOfBranchConnectors = BranchConnectors.Size();
										outputFile << "Number of straight tube branch connectors = " << NumberOfBranchConnectors <<endl;
										if (NumberOfBranchConnectors)
										{
											for ( int i=1 ; i<=NumberOfBranchConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (BranchConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!BranchConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get the combined tube
									CATV4iV4Element* CombinedTube = CATV4iGetCombinedTub (element);
									outputFile << "CATV4iGetCombinedTub succeeded" << endl;
									if (CombinedTube)
									{
										outputFile << "Straight tube in combined tube =  " << CombinedTube->GetId() << endl;
									}
									else if (!CombinedTube) outputFile << "Straight tube not in combined tube " << endl;
                }

								// Elbow tube
								else if (TubingType == 2)
                {
									outputFile << "" << endl;
                  outputFile << "** ELBOW TUBE **  found " << endl;
									outputFile << "" << endl;

									// Get the tubing line Outside Diameter
									double Diameter = 0.0;
									double BendRadius = 0.0;
									double Angle = 0.0;
									double Extremity1[3];
									double Extremity2[3];
									double Center[3];
									double Udir[3];
									double Vdir[3];
									int iReturnElbowTubeData = CATV4iGetElbowTubeData (element, Diameter, BendRadius, Angle, Extremity1, 
																																		 Extremity2, Center, Udir, Vdir);

									if (iReturnElbowTubeData == -1) 
										outputFile << "CATV4iGetElbowTubeData failed" << endl;
									else if (iReturnElbowTubeData == 0)
									{
										outputFile << "CATV4iGetElbowTubeData succeeded" << endl;
										outputFile << "Elbow tube Diameter = " << Diameter << endl;
										outputFile << "Elbow tube BendRadius = " << BendRadius << endl;
										outputFile << "Elbow tube Angle = " << Angle << endl;
										outputFile << "Elbow tube Extremity1[0] = " << Extremity1[0] << endl;
										outputFile << "Elbow tube Extremity1[1] = " << Extremity1[1] << endl;
										outputFile << "Elbow tube Extremity1[2] = " << Extremity1[2] << endl;
										outputFile << "Elbow tube Extremity2[0] = " << Extremity2[0] << endl;
										outputFile << "Elbow tube Extremity2[1] = " << Extremity2[1] << endl;
										outputFile << "Elbow tube Extremity2[2] = " << Extremity2[2] << endl;
										outputFile << "Elbow tube Center[0] = " << Center[0] << endl;
										outputFile << "Elbow tube Center[1] = " << Center[1] << endl;
										outputFile << "Elbow tube Center[2] = " << Center[2] << endl;
										outputFile << "Elbow tube Udir[0] = " << Udir[0] << endl;
										outputFile << "Elbow tube Udir[1] = " << Udir[1] << endl;
										outputFile << "Elbow tube Udir[2] = " << Udir[2] << endl;
										outputFile << "Elbow tube Vdir[0] = " << Vdir[0] << endl;
										outputFile << "Elbow tube Vdir[1] = " << Vdir[1] << endl;
										outputFile << "Elbow tube Vdir[2] = " << Vdir[2] << endl;
									}

									// Get the geo data
									double GeoDiameter = 0.0;
									double GeoExtremity1[3];
									double GeoExtremity2[3];									
									int iReturnTubGeoData = CATV4iGetTubGeoData(element, GeoDiameter, GeoExtremity1, GeoExtremity2);
									if (iReturnTubGeoData == -1) 
										outputFile << "CATV4iGetTubGeoData failed" << endl;
									else if (iReturnTubGeoData == 0)
									{
										outputFile << "CATV4iGetTubGeoData succeeded" << endl;
										outputFile << "Elbow diameter = " << GeoDiameter << endl;
										outputFile << "Elbow Extremity1[0] = " << GeoExtremity1[0] << endl;
										outputFile << "Elbow Extremity1[1] = " << GeoExtremity1[1] << endl;
										outputFile << "Elbow Extremity1[2] = " << GeoExtremity1[2] << endl;
										outputFile << "Elbow Extremity2[0] = " << GeoExtremity2[0] << endl;
										outputFile << "Elbow Extremity2[1] = " << GeoExtremity2[1] << endl;
										outputFile << "Elbow Extremity2[2] = " << GeoExtremity2[2] << endl;
									}

									// Get all of the elbow connectors
									int ConnectorType = 0;
									CATListPtrCATV4iV4Element AllTubeConnectors;
									int iReturnAllTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, AllTubeConnectors);

									if (iReturnAllTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for all connectors failed" << endl;
									else if (iReturnAllTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for all connectors succeeded" << endl;
										int NumberOfAllConnectors = AllTubeConnectors.Size();
										outputFile << "Number of elbow all connectors = " << NumberOfAllConnectors << endl;
										if (NumberOfAllConnectors)
										{
											for ( int i=1 ; i<=NumberOfAllConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (AllTubeConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!AllTubeConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the extremity connectors
									ConnectorType = 1;
									CATListPtrCATV4iV4Element ExtremityConnectors;
									int iReturnExtTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, ExtremityConnectors);

									if (iReturnExtTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for extremity connectors failed" << endl;
									else if (iReturnExtTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for extremity connectors succeeded" << endl;
										int NumberOfExtremityConnectors = ExtremityConnectors.Size();
										outputFile << "Number of elbow extremity connectors = " << NumberOfExtremityConnectors <<endl;
										if (NumberOfExtremityConnectors)
										{
											for ( int i=1 ; i<=NumberOfExtremityConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (ExtremityConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!ExtremityConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the branch connectors
									ConnectorType = 2;
									CATListPtrCATV4iV4Element BranchConnectors;
									int iReturnBranchTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, BranchConnectors);

									if (iReturnBranchTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for branch connectors failed" << endl;
									else if (iReturnBranchTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for branch connectors succeeded" << endl;
										int NumberOfBranchConnectors = BranchConnectors.Size();
										outputFile << "Number of elbow branch connectors = " << NumberOfBranchConnectors <<endl;
										if (NumberOfBranchConnectors)
										{
											for ( int i=1 ; i<=NumberOfBranchConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (BranchConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!BranchConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get the combined tube
									CATV4iV4Element* CombinedTube = CATV4iGetCombinedTub (element);
									outputFile << "CATV4iGetCombinedTub succeeded" << endl;
									if (CombinedTube)
									{
										outputFile << "Elbow in combined tube =  " << CombinedTube->GetId() << endl;
									}
									else if (!CombinedTube) outputFile << "Elbow not in combined tube " << endl;
                }

								// Spline tube
								else if (TubingType == 3) 
                {
									outputFile << "" << endl;
                  outputFile << "** SPLINE TUBE ** found " << endl;
									outputFile << "" << endl;

									// Get the geo data
									double Diameter = 0.0;
									double Extremity1[3];
									double Extremity2[3];									
									int iReturnTubGeoData = CATV4iGetTubGeoData(element, Diameter, Extremity1, Extremity2);
									if (iReturnTubGeoData == -1) 
										outputFile << "CATV4iGetTubGeoData failed" << endl;
									else if (iReturnTubGeoData == 0)
									{
										outputFile << "CATV4iGetTubGeoData succeeded" << endl;
										outputFile << "Spline tube diameter = " << Diameter << endl;
										outputFile << "Spline tube Extremity1[0] = " << Extremity1[0] << endl;
										outputFile << "Spline tube Extremity1[1] = " << Extremity1[1] << endl;
										outputFile << "Spline tube Extremity1[2] = " << Extremity1[2] << endl;
										outputFile << "Spline tube Extremity2[0] = " << Extremity2[0] << endl;
										outputFile << "Spline tube Extremity2[1] = " << Extremity2[1] << endl;
										outputFile << "Spline tube Extremity2[2] = " << Extremity2[2] << endl;
									}

									// Get all of the spline tube connectors
									int ConnectorType = 0;
									CATListPtrCATV4iV4Element AllTubeConnectors;
									int iReturnAllTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, AllTubeConnectors);

									if (iReturnAllTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for all connectors failed" << endl;
									else if (iReturnAllTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for all connectors succeeded" << endl;
										int NumberOfAllConnectors = AllTubeConnectors.Size();
										outputFile << "Number of spline tube all connectors = " << NumberOfAllConnectors << endl;
										if (NumberOfAllConnectors)
										{
											for ( int i=1 ; i<=NumberOfAllConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (AllTubeConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!AllTubeConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the extremity connectors
									ConnectorType = 1;
									CATListPtrCATV4iV4Element ExtremityConnectors;
									int iReturnExtTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, ExtremityConnectors);

									if (iReturnExtTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for extremity connectors failed" << endl;
									else if (iReturnExtTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for extremity connectors succeeded" << endl;
										int NumberOfExtremityConnectors = ExtremityConnectors.Size();
										outputFile << "Number of spline tube extremity connectors = " << NumberOfExtremityConnectors <<endl;
										if (NumberOfExtremityConnectors)
										{
											for ( int i=1 ; i<=NumberOfExtremityConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (ExtremityConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!ExtremityConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the branch connectors
									ConnectorType = 2;
									CATListPtrCATV4iV4Element BranchConnectors;
									int iReturnBranchTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, BranchConnectors);

									if (iReturnBranchTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for branch connectors failed" << endl;
									else if (iReturnBranchTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for branch connectors succeeded" << endl;
										int NumberOfBranchConnectors = BranchConnectors.Size();
										outputFile << "Number of spline tube branch connectors = " << NumberOfBranchConnectors <<endl;
										if (NumberOfBranchConnectors)
										{
											for ( int i=1 ; i<=NumberOfBranchConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (BranchConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!BranchConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get the combined tube
									CATV4iV4Element* CombinedTube = CATV4iGetCombinedTub (element);
									outputFile << "CATV4iGetCombinedTub succeeded" << endl;
									if (CombinedTube)
									{
										outputFile << "Spline tube in combined tube =  " << CombinedTube->GetId() << endl;
									}
									else if (!CombinedTube) outputFile << "Spline tube not in combined tube " << endl;
                }

								// Combined tube
								else if (TubingType == 4) 
                {
									outputFile << "" << endl;
                  outputFile << "** COMBINED TUBE ** found " << endl;
									outputFile << "" << endl;

									outputFile << "Name of combined tube =  " << element->GetId() << endl;

									// Get the geo data
									double Diameter = 0.0;
									double Extremity1[3];
									double Extremity2[3];									
									int iReturnTubGeoData = CATV4iGetTubGeoData(element, Diameter, Extremity1, Extremity2);
									if (iReturnTubGeoData == -1) 
										outputFile << "CATV4iGetTubGeoData failed" << endl;
									else if (iReturnTubGeoData == 0)
									{
										outputFile << "CATV4iGetTubGeoData succeeded" << endl;
										outputFile << "Combined tube diameter = " << Diameter << endl;
										outputFile << "Combined tube Extremity1[0] = " << Extremity1[0] << endl;
										outputFile << "Combined tube Extremity1[1] = " << Extremity1[1] << endl;
										outputFile << "Combined tube Extremity1[2] = " << Extremity1[2] << endl;
										outputFile << "Combined tube Extremity2[0] = " << Extremity2[0] << endl;
										outputFile << "Combined tube Extremity2[1] = " << Extremity2[1] << endl;
										outputFile << "Combined tube Extremity2[2] = " << Extremity2[2] << endl;
									}

									// Get all of the combined tube connectors
									int ConnectorType = 0;
									CATListPtrCATV4iV4Element AllTubeConnectors;
									int iReturnAllTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, AllTubeConnectors);

									if (iReturnAllTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for all connectors failed" << endl;
									else if (iReturnAllTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for all connectors succeeded" << endl;
										int NumberOfAllConnectors = AllTubeConnectors.Size();
										outputFile << "Number of combined tube all connectors = " << NumberOfAllConnectors << endl;
										if (NumberOfAllConnectors)
										{
											for ( int i=1 ; i<=NumberOfAllConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (AllTubeConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!AllTubeConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the extremity connectors
									ConnectorType = 1;
									CATListPtrCATV4iV4Element ExtremityConnectors;
									int iReturnExtTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, ExtremityConnectors);

									if (iReturnExtTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for extremity connectors failed" << endl;
									else if (iReturnExtTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for extremity connectors succeeded" << endl;
										int NumberOfExtremityConnectors = ExtremityConnectors.Size();
										outputFile << "Number of combined tube extremity connectors = " << NumberOfExtremityConnectors <<endl;
										if (NumberOfExtremityConnectors)
										{
											for ( int i=1 ; i<=NumberOfExtremityConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (ExtremityConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!ExtremityConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the branch connectors
									ConnectorType = 2;
									CATListPtrCATV4iV4Element BranchConnectors;
									int iReturnBranchTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, BranchConnectors);

									if (iReturnBranchTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for branch connectors failed" << endl;
									else if (iReturnBranchTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for branch connectors succeeded" << endl;
										int NumberOfBranchConnectors = BranchConnectors.Size();
										outputFile << "Number of combined tube branch connectors = " << NumberOfBranchConnectors << endl;
										if (NumberOfBranchConnectors)
										{
											for ( int i=1 ; i<=NumberOfBranchConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (BranchConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!BranchConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}
                }

								// Bend segment
								else if (TubingType == 5) 
                {
									outputFile << "" << endl;
                  outputFile << "** BEND SEGMENT ** found " << endl;
									outputFile << "" << endl;

									// Get the geo data
									double Diameter = 0.0;
									double Extremity1[3];
									double Extremity2[3];									
									int iReturnTubGeoData = CATV4iGetTubGeoData(element, Diameter, Extremity1, Extremity2);
									if (iReturnTubGeoData == -1) 
										outputFile << "CATV4iGetTubGeoData failed" << endl;
									else if (iReturnTubGeoData == 0)
									{
										outputFile << "CATV4iGetTubGeoData succeeded" << endl;
										outputFile << "Bend diameter = " << Diameter << endl;
										outputFile << "Bend Extremity1[0] = " << Extremity1[0] << endl;
										outputFile << "Bend Extremity1[1] = " << Extremity1[1] << endl;
										outputFile << "Bend Extremity1[2] = " << Extremity1[2] << endl;
										outputFile << "Bend Extremity2[0] = " << Extremity2[0] << endl;
										outputFile << "Bend Extremity2[1] = " << Extremity2[1] << endl;
										outputFile << "Bend Extremity2[2] = " << Extremity2[2] << endl;
									}

									// Get all of the bend connectors
									int ConnectorType = 0;
									CATListPtrCATV4iV4Element AllTubeConnectors;
									int iReturnAllTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, AllTubeConnectors);

									if (iReturnAllTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for all connectors failed" << endl;
									else if (iReturnAllTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for all connectors succeeded" << endl;
										int NumberOfAllConnectors = AllTubeConnectors.Size();
										outputFile << "Number of bend all connectors = " << NumberOfAllConnectors << endl;
										if (NumberOfAllConnectors)
										{
											for ( int i=1 ; i<=NumberOfAllConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (AllTubeConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!AllTubeConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the extremity connectors
									ConnectorType = 1;
									CATListPtrCATV4iV4Element ExtremityConnectors;
									int iReturnExtTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, ExtremityConnectors);

									if (iReturnExtTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for extremity connectors failed" << endl;
									else if (iReturnExtTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for extremity connectors succeeded" << endl;
										int NumberOfExtremityConnectors = ExtremityConnectors.Size();
										outputFile << "Number of bend extremity connectors = " << NumberOfExtremityConnectors <<endl;
										if (NumberOfExtremityConnectors)
										{
											for ( int i=1 ; i<=NumberOfExtremityConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (ExtremityConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!ExtremityConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the branch connectors
									ConnectorType = 2;
									CATListPtrCATV4iV4Element BranchConnectors;
									int iReturnBranchTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, BranchConnectors);

									if (iReturnBranchTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for branch connectors failed" << endl;
									else if (iReturnBranchTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for branch connectors succeeded" << endl;
										int NumberOfBranchConnectors = BranchConnectors.Size();
										outputFile << "Number of bend branch connectors = " << NumberOfBranchConnectors <<endl;
										if (NumberOfBranchConnectors)
										{
											for ( int i=1 ; i<=NumberOfBranchConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (BranchConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!BranchConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get the combined tube
									CATV4iV4Element* CombinedTube = CATV4iGetCombinedTub (element);
									outputFile << "CATV4iGetCombinedTub succeeded" << endl;
									if (CombinedTube)
									{
										outputFile << "Bend in combined tube =  " << CombinedTube->GetId() << endl;
									}
									else if (!CombinedTube) outputFile << "Bend not in combined tube " << endl;
                }

								// Tubing line
								else if (TubingType == 6) 
                {
									outputFile << "" << endl;
                  outputFile << "** TUBING LINE ** found " << endl;
									outputFile << "" << endl;

									// Get the tubing line name
									CATUnicodeString TubingLineName = CATV4iGetTubLineName(element);
									if (TubingLineName != "")
									{
										outputFile << "CATV4iGetTubLineName succeeded" << endl;
										CATString TubingLineNameString = TubingLineName.ConvertToChar();
										outputFile << "Tubing line name = " << TubingLineNameString <<endl;
									}
									else if (TubingLineName == "")
									{
										outputFile << "CATV4iGetTubLineName failed" << endl;
										outputFile << "Tubing line name not found"<<endl;
									}

									// Get the tubing line Outside Diameter
									double OutsideDiameter = 0.0;
									int iReturnTubLineOD = CATV4iGetTubLineOD(element, OutsideDiameter);

									if (iReturnTubLineOD == -1) 
										outputFile << "CATV4iGetTubLineOD failed" << endl;
									else if (iReturnTubLineOD == 0)
									{
										outputFile << "CATV4iGetTubLineOD succeeded" << endl;
										outputFile << "Tubing line outside diameter = "<< OutsideDiameter <<endl;
									}
                }

								// Ditto
								else if (TubingType == 7) 
                {
									outputFile << "" << endl;
                  outputFile << "** DITTO ** found " << endl;
									outputFile << "" << endl;

									// Get all of the ditto connectors
									int ConnectorType = 0;
									CATListPtrCATV4iV4Element AllTubeConnectors;
									int iReturnAllTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, AllTubeConnectors);

									if (iReturnAllTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for all connectors failed" << endl;
									else if (iReturnAllTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for all connectors succeeded" << endl;
										int NumberOfAllConnectors = AllTubeConnectors.Size();
										outputFile << "Number of ditto all connectors = " << NumberOfAllConnectors << endl;
										if (NumberOfAllConnectors)
										{
											for ( int i=1 ; i<=NumberOfAllConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (AllTubeConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!AllTubeConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the extremity connectors
									ConnectorType = 1;
									CATListPtrCATV4iV4Element ExtremityConnectors;
									int iReturnExtTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, ExtremityConnectors);

									if (iReturnExtTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for extremity connectors failed" << endl;
									else if (iReturnExtTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for extremity connectors succeeded" << endl;
										int NumberOfExtremityConnectors = ExtremityConnectors.Size();
										outputFile << "Number of ditto extremity connectors = " << NumberOfExtremityConnectors <<endl;
										if (NumberOfExtremityConnectors)
										{
											for ( int i=1 ; i<=NumberOfExtremityConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (ExtremityConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!ExtremityConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get only the branch connectors
									ConnectorType = 2;
									CATListPtrCATV4iV4Element BranchConnectors;
									int iReturnBranchTubConnectors = CATV4iGetTubConnectors(element, ConnectorType, BranchConnectors);

									if (iReturnBranchTubConnectors == -1) 
										outputFile << "CATV4iGetTubConnectors for branch connectors failed" << endl;
									else if (iReturnBranchTubConnectors == 0)
									{
										outputFile << "CATV4iGetTubConnectors for branch connectors succeeded" << endl;
										int NumberOfBranchConnectors = BranchConnectors.Size();
										outputFile << "Number of ditto branch connectors = " << NumberOfBranchConnectors <<endl;
										if (NumberOfBranchConnectors)
										{
											for ( int i=1 ; i<=NumberOfBranchConnectors ; i++ )
											{
												outputFile << "Connector number = " << i << endl; 
												if (BranchConnectors[i])  outputFile << "Connector is OK" << endl; 
												if (!BranchConnectors[i]) outputFile << "Connector is NULL" << endl; 
											}
										}
									}

									// Get the combined tube
									CATV4iV4Element* CombinedTube = CATV4iGetCombinedTub (element);
									outputFile << "CATV4iGetCombinedTub succeeded" << endl;
									if (CombinedTube)
									{
										outputFile << "Ditto in combined tube =  " << CombinedTube->GetId() << endl;
									}
									else if (!CombinedTube) outputFile << "Ditto not in combined tube " << endl;
                }
              }
          
  // ---- Retrieves the next elements of the set
              if (! CATV4iGisels(setElem, element, nextElement, endEls, ier) )
              {
                if (element)
                {
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
  }
  else
  {
    outputFile << "*** Unable to retrieve the MASTER, ier=" <<ier<< endl;
    result =1;
  }

  outputFile.close();

  ::Delete_Session(sessionName) ;



  return result;
}
