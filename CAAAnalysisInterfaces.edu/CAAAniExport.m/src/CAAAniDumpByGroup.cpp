// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//  Abstract of the Use Case:
//  ------------------------
//  This Use Case illustrates how to explore a CATAnalysis document in order 
//  to create an exported file. The format of this file is not DASSAULT SYSTEMES 
//  proprietary and could be change at any time. 
//=============================================================================
//
//  Main Methods:
//  ------------
//  CAAAniDumpByGroup Dump characcollector attached to group of entities 
//                    This is for Material, Local Axis , properties.. 
//
//  Input Argument:
//  --------------
//  CATAnalysisExplicitModel   * iExplicitModel  : Pointer on the CATAnalysisExplicitModel.
//  int                          iMax Collect    : Size of next array.
//  CATAnalysisCharacCollector **iListCollector  : Array of returned CC pointer
//  CATAnalysisCharacCollector * iGpePerElementCollector : CC pointer that allow to retreive the 
//                                Groupe number associated to a list of FE
//
//  Return Errors:
//  -------------
//  1 - HRESULT S_OK is every thing is OK E_FAIL Otherwhise.
//
//=============================================================================
//  CAAAniDumpByFEentity Dump characcollector attached to entities 
//                       This is for Load, Solution Sets .. 
//                       It is quite the same as the previous one be values are directly 
//                       attached to FE and not by using intermediate notion of group.
//
//  Input Argument:
//  --------------
//  CATAnalysisExplicitModel   * iExplicitModel  : Pointer on the CATAnalysisExplicitModel.
//  int                          iMax Collect    : Size of next array.
//  CATAnalysisCharacCollector **iListCollector  : Array of returned CC pointer
//
//  Return Errors:
//  -------------
//  1 - HRESULT S_OK is every thing is OK E_FAIL Otherwhise.
//
//=============================================================================
//=============================================================================
//  Keep positions in the array ListCollector for specific physical types:
//  ListCollector[0] = List of physical type per gpe or property / Materials ....
//  ListCollector[1] = List of user Number per gpe or property / Materials ....
//  GpePerElementCollector = List of sequential Number of the group per element
//	GpePerElementCollector -> GetValues(Values) Values[element[i]] = Gpe Number
//=============================================================================
#include "CATString.h"                      // Management of CATString

#include "CAAAniExport.h"                   // Local includes of the sample
#include "CATAnalysisCharacCollector.h"    //  Charac-collector object
#include "CATAnalysisExplicitSet.h"        //  Method on CATAnalysisExplicitSet
#include "CATAnalysisExplicitEntity.h"     //  Method on CATAnalysisExplicitEntity
#include "CATISamExplicit.h"               //  Get implementation of Sam Explicit
#include "CATICharacCollector.h"           //  Get implementation of CATICharacCollector
#include "CATAnalysisExplicitRulesData.h"  //  Method on CATAnalysisExplicitRulesData

//
#include "CATSamDimension.h"               //  CATSamDimesion stored inside the CC
HRESULT CAAAniDumpByGroup(FILE*  File,CATAnalysisExplicitModel *ExplicitModel,int MaxCollect,
					const CATAnalysisCharacCollector ** ListCollector,
					const CATAnalysisCharacCollector *GpePerElementCollector)
{
	HRESULT hr= S_OK;
	char                         Ligne[1024];
//==========================================================================
	int  i,j,k,ip;
	const char         *charPtr = NULL ;
	const short        *shortPtr = NULL ;
	const int          *intPtr = NULL ;
	const float        *floatPtr = NULL ;
	const double       *doublePtr = NULL ;
	const void         **voidPtr = NULL ;
	const char* Entities = NULL;
	int NbDimensions,NbEntities,NumOccurrence;
	CATSamPhysicalType    PhysicalType,PhyTypNumb, EntityPhysicalType;
	CATSamCharacVersion  Version;
	CATString          Position,Apply,Unit ;
	const CATSamDimension*         Dimensions  = NULL;
 	const CATSamDimension*         EntDimens = NULL ;
    const CATSamDimension* const * DimensionPointers = NULL ; 
	const char* Name = NULL ;
	int NbValues   = 0,SizeValues = 0, NbSupport;
	const void* const * ValuePointers = NULL;
	const CATAnalysisCharacCollector * TheCC = ListCollector[0];

  // Retrieve RulesData
  if (!ExplicitModel)  return E_FAIL;
  const CATAnalysisExplicitRulesData *aRulesData = NULL;
  aRulesData = ExplicitModel->GetRulesData();
  if (!aRulesData)  return E_FAIL;

//==========================================================================
	aRulesData -> GetPhysicalTypeNumber("PHYSICAL_TYPE",PhyTypNumb);
// In this sample, GpePerElement Collector is only used for element properties.
//==========================================================================
	if (GpePerElementCollector)
	{
		// Retrieve the definition of the CC. this means:
		// - PhysicalType
		// - Unit string
		// - Version
		// - Position string (Apply)
		// - Occurrence number
		hr = GpePerElementCollector -> GetDefinition(PhysicalType,Unit,Version,Apply,NumOccurrence,EntityPhysicalType);
		if (!SUCCEEDED(hr))  return E_FAIL;
		// Retrieve the number of apply (in this case for properties it gives the
		// number of element of the model.
		hr = GpePerElementCollector -> GetNbEntities(NbSupport);
		if (!SUCCEEDED(hr))  return E_FAIL;
//		cout <<"      CAAAniDumpByGroup NbSupport "<< NbSupport <<  Apply<<endl;
	}
//==========================================================================
// Take the first CC to retreive the number of entities (here it means groups)
//==========================================================================
	NbEntities = 0;
	if (TheCC) hr = TheCC -> GetNbEntities(NbEntities);
	if (!SUCCEEDED(hr))  return E_FAIL;
	cout <<"      CAAAniDumpByGroup NbEntities "<< NbEntities << "MaxCollect" <<MaxCollect<<endl;
//==========================================================================
// Scan for one of the Groups and for each the CC the attached values.
//==========================================================================
	for (i = 0 ; i < NbEntities ; i++) 
	{
		ip = 0;
		for (k = 0 ; k < MaxCollect ; k++) 
		{
			TheCC = ListCollector[k];
			if (!TheCC) continue ;
   		// Retrieve the definition of the CC. this means:
			TheCC -> GetDefinition(PhysicalType,Unit,Version,Position,NumOccurrence,EntityPhysicalType);
      // Convert Physical type into Name (CATString)
			aRulesData->GetPhysicalTypeName(PhysicalType,Name);
			cout <<"      CAAAniDumpByGroup PHYSICAl type "<< Name << (const char*) Position <<endl;
      // Retrieve the Bit array that inform if Groups have values
      Entities = NULL;
			hr = TheCC -> GetEntities(Entities);	
			if (!SUCCEEDED(hr))  return E_FAIL;

			if (Entities[i]) // There is values
			{
        // Retrieve the Dimension object of the CC
        Dimensions = NULL;
        DimensionPointers = NULL;
				hr = TheCC -> GetDimensions(NbDimensions,Dimensions,DimensionPointers);
				if (!SUCCEEDED(hr))  return E_FAIL;
        // Is there a Dimension Object per entitie or a global one ...
        EntDimens = NULL; 
        if (DimensionPointers)	EntDimens = DimensionPointers[i] ;
        else                    EntDimens = Dimensions ;
        // Dump ?
        //		EntDimens -> Dump();
        // Finally, we can acces the values by having the pointers...
        ValuePointers = NULL;
        hr = TheCC ->GetValues(NbValues,SizeValues,ValuePointers);
        if (!SUCCEEDED(hr))  return E_FAIL;
        // Do we have values for the entity [i]
				if (!ValuePointers[i]) continue;
//======================================================================================
        // Launch the dump according to the Value type
        switch (Version.ValueType)
				{
				case CATSamValueCharacter :
				charPtr = (const char *) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
					ip += sprintf (Ligne+ip,"%s",charPtr[j]);
				Ligne [ip] = ' ';
				ip ++;
		        break ;
				case CATSamValueShort :
				shortPtr = (const short *) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
					ip += sprintf (Ligne+ip,"%5d",shortPtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
				break ;
				case CATSamValueInteger :
				intPtr = (const int *) ValuePointers[i] ;
			// Dump as physical string values
				if (PhysicalType == PhyTypNumb)
				{
					CATUnicodeString oString;
					aRulesData->GetPhysicalTypeName((CATSamPhysicalType) (intPtr[0]), oString);
					ip += sprintf (Ligne+ip,"%s",(const char *) oString);
					Ligne [ip] = ' ';
					ip ++;
				}
				else
				{
					for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
					{
						ip += sprintf (Ligne+ip,"%8d",intPtr[j]);
						Ligne [ip] = ' ';
						ip ++;
					}
				}
				break ;
	            case CATSamValueReal :
		        floatPtr = (const float *) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
					ip += sprintf (Ligne+ip,"%E",floatPtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
	            break ;
	            case CATSamValueDouble :
	            doublePtr = (const double *) ValuePointers[i] ;
			    for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
					ip += sprintf (Ligne+ip,"%E",doublePtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
				break ;
	            case CATSamValuePointer  :
		        case CATSamValueNode     :
			    case CATSamValueElement  :
				case CATSamValueMaterial :
				case CATSamValueAxis     :
				case CATSamValueProperty :
				case CATSamValueRestraint:
				case CATSamValueLoad     :
				case CATSamValueMass     :
				voidPtr = (const void **) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
 					ip += sprintf (Ligne+ip,"%08X",voidPtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
				break ;
				case CATSamValueComplex :
				case CATSamValueComplexDouble :
				default :
					cout << "invalid value type" ;
				}
			}
		}
//======================================================================================
// Close the dump
		ip += sprintf (Ligne+ip,"\n");
		fwrite ((char *)Ligne,sizeof(char),strlen(Ligne),File);
//======================================================================================
// 	if (GpePerElementCollector) means that some FE entities have que group number 
//  under printing as reference group. So, Let's print the Entity number.
//  For this collector Using Dimension is not usefull (One value per entity)
//======================================================================================
		if (GpePerElementCollector)
		{
      Entities = NULL;
      hr = GpePerElementCollector -> GetEntities(Entities);	
			if (!SUCCEEDED(hr))  return E_FAIL;
      // Quality of the list (NODE/ELEMENT/FACE ....)
			ip = sprintf (Ligne,"%s ",(const char *) Apply);
      // In this case Values are number (Sequential)
      ValuePointers = NULL;
      hr = GpePerElementCollector ->GetValues(NbValues,SizeValues,ValuePointers);
			for (j = 0 ; j < NbSupport ; j++)
			{
				if (Entities[j]) // There is a groupe for Element j
				{
					if (ValuePointers[j]) // There is a groupe number for Element j
					{
						intPtr = (const int *) ValuePointers[j] ;
						if (intPtr[0] == i) // Gpe number is equal to the group under printing.
						{
	 						ip += sprintf (Ligne+ip,"%6d",j);
							Ligne [ip] = ' ';
							ip ++;
						}
					}
				}
		// Continuation Line
				if ((ip+10) > 132 || (j+1) == NbSupport)
				{
					ip += sprintf (Ligne+ip,"\n");
					fwrite ((char *)Ligne,sizeof(char),ip+1,File);
					ip = 0;
					if ((j+1) != NbSupport) { Ligne[ip] = '&'; ip = 1;}
				}
			}
		}
	}
	return hr;
}
//==========================================================================
// This method is for direct output based on Finite Elements
HRESULT CAAAniDumpByFEentity(FILE*  File,CATAnalysisExplicitModel *ExplicitModel,
							 int MaxCollect,const CATAnalysisCharacCollector ** ListCollector)
//==========================================================================
{
	HRESULT hr= S_OK;
	char                         Ligne[1024];
	int  i,j,k,ip;
	const char         *charPtr = NULL ;
	const short        *shortPtr = NULL ;
	const int          *intPtr = NULL ;
	const float        *floatPtr = NULL ;
	const double       *doublePtr = NULL ;
	const void         **voidPtr = NULL ;
	const char* Entities = NULL;
	int NbDimensions,NbEntities;
	CATSamPhysicalType    PhysicalType,PhyTypNumb,EntityPhysicalType;
	CATString            Unit,Position;
	CATSamCharacVersion  Version;
	int                   NumOccurrence,NbValues=0,SizeValues=0,LFac=0;
	const CATSamDimension*         Dimensions  = NULL;
 	const CATSamDimension*         EntDimens = NULL ;
    const CATSamDimension* const * DimensionPointers = NULL ; 
	const char* Name = NULL ;
	const void* const * ValuePointers  = NULL;
	const CATAnalysisCharacCollector * TheCC = NULL;

  // Retrieve RulesData
  if (!ExplicitModel)  return E_FAIL;
  const CATAnalysisExplicitRulesData *aRulesData = NULL;
  aRulesData = ExplicitModel->GetRulesData();
  if (!aRulesData)  return E_FAIL;

  aRulesData -> GetPhysicalTypeNumber("PHYSICAL_TYPE",PhyTypNumb);

//==========================================================================
//
	for (k = 0 ; k < MaxCollect ; k++) 
	{
		ip = 0;
		LFac = 0;
		TheCC = ListCollector[k];
		if (!TheCC) continue ;
		hr = TheCC -> GetNbEntities(NbEntities);
		cout <<"      CAAAniDumpByFEentity NbEntities "<< NbEntities << "MaxCollect" <<MaxCollect<<endl;
		if (!SUCCEEDED(hr))  return E_FAIL;
//
		TheCC -> GetDefinition(PhysicalType,Unit,Version,Position,NumOccurrence,EntityPhysicalType);
		if (Position.Compare("FACE") == 0 || Position.Compare("EDGE")==0 ) LFac=1;
		aRulesData->GetPhysicalTypeName(PhysicalType,Name);
    Entities = NULL;
		hr = TheCC -> GetEntities(Entities);	
		if (!SUCCEEDED(hr))  return E_FAIL;
		ip  = sprintf (Ligne,"%s ",Name);
		ip += sprintf (Ligne+ip,"\n");
		fwrite ((char *)Ligne,sizeof(char),ip+1,File);

		for (i = 0 ; i < NbEntities ; i++) 
		{
			if (Entities[i])
			{
        Dimensions = NULL;
        DimensionPointers = NULL;
				hr = TheCC -> GetDimensions(NbDimensions,Dimensions,DimensionPointers);
				if (!SUCCEEDED(hr))  return E_FAIL;
				ip = sprintf (Ligne,"%s  ",(const char*) Position);

		        if (DimensionPointers)	EntDimens = DimensionPointers[i] ;
		        else                    EntDimens = Dimensions ;
        ValuePointers = NULL;
				hr = TheCC ->GetValues(NbValues,SizeValues,ValuePointers);
				if (!SUCCEEDED(hr))  return E_FAIL;

				if (!ValuePointers[i]) continue;
// Finite Element / Node Number
				ip += sprintf (Ligne+ip,"%6d ",i);
				if (LFac)
				{
					const int* NumFac = EntDimens->GetPositions();
					for (j = 0 ; j < EntDimens->GetNbPositions() ; j++)
						ip += sprintf (Ligne+ip,"F%3d ",NumFac[j]);
				}
//
		        switch (Version.ValueType)
				{
				case CATSamValueCharacter :
				charPtr = (const char *) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
					ip += sprintf (Ligne+ip,"%s",charPtr[j]);
				Ligne [ip] = ' ';
				ip ++;
		        break ;
				case CATSamValueShort :
				shortPtr = (const short *) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
					ip += sprintf (Ligne+ip,"%5d",shortPtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
				break ;
				case CATSamValueInteger :
				intPtr = (const int *) ValuePointers[i] ;
				if (PhysicalType == PhyTypNumb)
				{
					CATUnicodeString oString;
					aRulesData->GetPhysicalTypeName((CATSamPhysicalType) (intPtr[0]), oString);
					ip += sprintf (Ligne+ip,"%s",(const char *) oString);
					Ligne [ip] = ' ';
					ip ++;

				}
				else
				{
					for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
					{
						ip += sprintf (Ligne+ip,"%8d",intPtr[j]);
						Ligne [ip] = ' ';
						ip ++;
					}
				}
				break ;
	            case CATSamValueReal :
		        floatPtr = (const float *) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
					ip += sprintf (Ligne+ip,"%E",floatPtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
	            break ;
	            case CATSamValueDouble :
	            doublePtr = (const double *) ValuePointers[i] ;
			    for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
					ip += sprintf (Ligne+ip,"%E",doublePtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
				break ;
	            case CATSamValuePointer  :
		        case CATSamValueNode     :
			    case CATSamValueElement  :
				case CATSamValueMaterial :
				case CATSamValueAxis     :
				case CATSamValueProperty :
				case CATSamValueRestraint:
				case CATSamValueLoad     :
				case CATSamValueMass     :
				voidPtr = (const void **) ValuePointers[i] ;
				for (j = 0 ; j < EntDimens->GetNbValues() ; j++)
				{
 					ip += sprintf (Ligne+ip,"%08X",voidPtr[j]);
					Ligne [ip] = ' ';
					ip ++;
				}
				break ;
				case CATSamValueComplex :
				case CATSamValueComplexDouble :
				default :
					cout << "invalid value type" ;
				}
			}
			if (Entities[i])
			{
				ip += sprintf (Ligne+ip,"\n");
				fwrite ((char *)Ligne,sizeof(char),ip+1,File);
			}
		}
	}
	return hr;
}

