//============================================================================================
// COPYRIGHT Dassault Systemes 2004
//============================================================================================
// CAAStmServices.h
// Header definition of CAAStmServices
//============================================================================================
//
// Usage notes:
//
//  This class exposes services to create or modify Aerospace Sheet Metal Features.
//  This class can be used to write various batch managing Aerospace Sheet Metal Features. 
//
//============================================================================================
//
#include "CAAStmServices.h"
#include "CAAStmInputData.h"

#include "CATIStmWeb.h"
#include "CATIStmFlangeSurf.h"
#include "CATIStmJoggle.h"
#include "CATIStmCharacteristicCurves.h"

#include "CATIAlias.h"

#include "CATICkeParm.h"
#include "CATIParmAsStored.h"
#include "CATCkeGlobalFunctions.h"
#include "CATIParmDictionary.h"
#include "CATICkeUnit.h"
#include "CATIDescendants.h"
#include "CATMfErrUpdate.h"
#include "CATError.h"

#include "CATGetEnvValue.h"
#include "CATStdIO.h"

#include "iostream.h"

// ---------------------------------------------------------------------------------------------
CAAStmServices::CAAStmServices()
  {
  }
 
// ---------------------------------------------------------------------------------------------
CAAStmServices::~CAAStmServices()
  {
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::ReadInputFile (const CATUnicodeString &    iFilePath, 
                                       CATListOfCATUnicodeString & oLines)
  {
  HRESULT rc = E_FAIL;
  oLines.RemoveAll();

  unsigned int Desc = 0;

  CATUnicodeString FilePath=iFilePath;
  
  rc = CATFOpen (&FilePath, "r", &Desc);
  
  if(SUCCEEDED(rc))
    {
    int SizeBuff = 256;
    char Buffer [256];

    while (S_FALSE == CATFEof(Desc))
      {
      rc = CATFGets (Buffer, SizeBuff, Desc);

      if(SUCCEEDED(rc))
        {        
        CATUnicodeString strLine(Buffer);
        strLine = strLine.Strip (CATUnicodeString::CATStripModeTrailing, '\n');
        strLine = strLine.Strip (CATUnicodeString::CATStripModeTrailing, ' ');
        int Length = strLine.GetLengthInChar();
        if(Length > 0)
          {
          CATUnicodeString Line(Buffer, Length);
          oLines.Append(Line);
          }
        }
      }
    rc = CATFClose (Desc);

    if(FAILED(rc))
      {
      cout << endl;
      cout << "(ReadInputFile) Error : File" << iFilePath.ConvertToChar() << "can not be closed." << endl;
      cout << endl;
      }
    }
  else
    {
    cout << endl;
    cout << "(ReadInputFile) Error : File" << iFilePath.ConvertToChar() << "can not be opened." << endl;
    cout << endl;
    }
  
  int NbLines = oLines.Size();

  if(NbLines > 0)
    {
    // Si on est en Mode ODT : on complete les Paths vers les Parts
    
    if(CATGetEnvValue("CAA_ODT_CONTEXT", NULL) == CATLibSuccess)
      {
      cout << endl;
      cout << "(ReadInputFile) ===> CAA_ODT_CONTEXT." << endl;
      cout << endl;

		  char * InPath = NULL;
		  CATLibStatus status1 = CATGetEnvValue("CAA_ODT_IN", &InPath);
		  
      char * OutPath = NULL;
		  CATLibStatus status2 = CATGetEnvValue("CAA_ODT_OUT", &OutPath);
        
      char * OSName = NULL;
		  CATLibStatus status3 = CATGetEnvValue("CAA_ODT_OS", &OSName);
        
      if((status1 == CATLibSuccess) && (status2 == CATLibSuccess) && (status3 == CATLibSuccess))
        {
        CATUnicodeString Separator  = "";

        CATUnicodeString strPathIn  = InPath;
        CATUnicodeString strPathOut = OutPath;
        CATUnicodeString strOSName  = OSName;

        CATUnicodeString PrevPathIn("");
        CATUnicodeString PrevPathOut("");

        boolean ReadPathIn  = FALSE;
        boolean ReadPathOut = FALSE;
        int NumLineIn       = 0;
        int NumLineOut      = 0;
        int i = 1;
        for(; i <= NbLines; i++)
          {
          if(oLines[i] == "INPUT:")
            ReadPathIn = TRUE;
          else if(oLines[i] == "OUTPUT:")
            ReadPathOut = TRUE;
          else
            {
            if(ReadPathIn)
              {
              NumLineIn  = i;
              PrevPathIn = oLines[i];
              ReadPathIn = FALSE;
              }
            else if(ReadPathOut)
              {
              NumLineOut  = i;
              PrevPathOut = oLines[i];
              ReadPathOut = FALSE;
              }
            }
          }
        
        if(NumLineIn > 0)
          {
          CATUnicodeString NewPathIn("");

          if(strOSName == "Windows_NT")
            Separator = "\\";
          else
            Separator = "/";
            
          CATListOfCATUnicodeString TmpLines;
          for(i = 1; i <= NbLines; i++)
            {
            TmpLines.Append(oLines[i]);
            }
          
          oLines.RemoveAll();
        
          for(i = 1; i <= NbLines; i++)
            {
            if(i == NumLineIn)
              {
              NewPathIn = strPathIn + Separator + TmpLines[i];
              oLines.Append(NewPathIn);
              }
            else
              oLines.Append(TmpLines[i]);
            }
          rc = S_OK;
          }
        
        if(NumLineOut > 0)
          {
          CATUnicodeString NewPathOut("");

          if(strOSName == "Windows_NT")
            Separator = "\\";
          else
            Separator = "/";
            
          CATListOfCATUnicodeString TmpLines;
          for(i = 1; i <= NbLines; i++)
            {
            TmpLines.Append(oLines[i]);
            }
          
          oLines.RemoveAll();
        
          for(i = 1; i <= NbLines; i++)
            {
            if(i == NumLineOut)
              {
              NewPathOut = strPathOut + Separator + TmpLines[i];
              oLines.Append(NewPathOut);
              }
            else
              oLines.Append(TmpLines[i]);
            }
          }
        }
      if(NULL != InPath)
        {
        free(InPath);
        InPath = NULL;
        }
      if(NULL != OutPath)
        {
        free(OutPath);
        OutPath = NULL;
        }
      if(NULL != OSName)
        {
        free(OSName);
        OSName = NULL;
        }
      }
    else
      rc = S_OK;
    }
  else
    rc = E_FAIL;

  return rc;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::AnalyseWebInputData (const CATUnicodeString & InputDataFilePath,
                                             CAAStmInputData &        CAAInputWeb)
  {
  // The aim of this method is :
  //   Retrieve the Web input data from a ".txt" file   

  HRESULT rc = E_FAIL;

  CATListOfCATUnicodeString FileLines;
  CATListOfCATUnicodeString WebLimitNames;

  // Lecture du fichier de donnees :
  rc = ReadInputFile (InputDataFilePath, FileLines);

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(AnalyseWebInputData) ERROR : Read File Input data has failed." << endl;
    cout << endl;
    return rc;
    }

  int NbLines = FileLines.Size();
  if(NbLines > 0)
    {
    // Available Keys :
    CATUnicodeString InputPartKey  ("INPUT:");
    CATUnicodeString OutputPartKey ("OUTPUT:");
    CATUnicodeString LengthUnitKey ("LENGTHUNIT:");
    CATUnicodeString DisplayKey    ("DISPLAY:");
    CATUnicodeString SupportKey    ("SUPPORT:");
    CATUnicodeString BoundaryKey   ("BOUNDARY:");
    CATUnicodeString MatOrientKey  ("MATERIALORIENT:");

    CATUnicodeString ReadLine   ("");
    CATUnicodeString DataToRead ("");
    CATBoolean       OK = TRUE;
    CATOrientation   Positive = CATOrientationPositive;
    CATOrientation   Negative = CATOrientationNegative;
    for(int i = 1; i <= NbLines; i++)
      {
      ReadLine = FileLines[i];

      if((ReadLine != "") && (ReadLine != " "))
        {
        if(ReadLine == InputPartKey)
          DataToRead = InputPartKey;
        else if(ReadLine == OutputPartKey)
          DataToRead = OutputPartKey;
        else if(ReadLine == LengthUnitKey)
          DataToRead = LengthUnitKey;
        else if(ReadLine == SupportKey)
          {
          CAAInputWeb.SetSupportGeomToSet(OK);
          DataToRead                        = SupportKey;
          }
        else if(ReadLine == BoundaryKey)
          {
          CAAInputWeb.SetBoundaryToSet(OK);
          DataToRead                        = BoundaryKey;
          }
        else if(ReadLine == MatOrientKey)
          {
          CAAInputWeb.SetMaterialOrientToSet(OK);
          DataToRead                        = MatOrientKey;
          }
        else if(ReadLine == DisplayKey)
          CAAInputWeb.SetDisplay(OK);
        else
          {
          if(DataToRead == InputPartKey)
            CAAInputWeb.SetInputPartPath(ReadLine);
          else if(DataToRead == OutputPartKey)
            CAAInputWeb.SetOutputPartPath(ReadLine);
          else if(DataToRead == LengthUnitKey)
            CAAInputWeb.SetLengthUnit(ReadLine);
          else if(DataToRead == SupportKey)
            CAAInputWeb.SetSupportGeomName(ReadLine);
          else if(DataToRead == BoundaryKey)
            WebLimitNames.Append(ReadLine);
          else if(DataToRead == MatOrientKey)
            {
            if(ReadLine == "+")
              CAAInputWeb.SetMaterialOrient(Positive);
            else if(ReadLine == "-")
              CAAInputWeb.SetMaterialOrient(Negative);
            }
          }
        }
      }
    int NbLims = WebLimitNames.Size();
    if(NbLims > 0)
      CAAInputWeb.SetLimitsGeomNameList(WebLimitNames);
    }
  else
    {
    cout << endl;
    cout << "(AnalyseWebInputData) ERROR : Read File Input data has failed." << endl;
    cout << endl;
    return rc;
    }

  // Traces :

  cout << endl;
  cout << "(AnalyseWebInputData) " << endl;
  cout << endl;
  cout << "      InputPartPath  : " << CAAInputWeb.GetInputPartPath().ConvertToChar() << endl;
  cout << endl;
  if(CAAInputWeb.GetDisplay())
    {
    cout << "      Display " << endl;
    cout << endl;
    }
  else
    {
    cout << "      OutputPartPath : " << CAAInputWeb.GetOutputPartPath().ConvertToChar() << endl;
    cout << endl;
    }
  cout << "      Length Unit    : " << CAAInputWeb.GetLengthUnit().ConvertToChar() << endl;
  cout << endl;

  if(CAAInputWeb.GetSupportGeomToSet())
    {
    cout << endl;     
    cout << "    ==> Support is to set " << endl;
    cout << endl;     
    cout << "      SupportGeomName  : " << CAAInputWeb.GetSupportGeomName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputWeb.GetBoundaryToSet())
    {
    CATListOfCATUnicodeString WebLimitTraces;
    WebLimitTraces = CAAInputWeb.GetLimitsGeomNameList();

    cout << endl;     
    cout << "    ==> Boundary is to set " << endl;
    cout << endl;
    for(int iLim = 1; iLim <= WebLimitTraces.Size(); iLim++)
      {
      cout << endl;     
      cout << "      Limit Name  : " << WebLimitTraces[iLim].ConvertToChar() << endl;
      cout << endl;
      }
    }
  
  if(CAAInputWeb.GetMaterialOrientToSet())
    {
    cout << endl;     
    cout << "    ==> Material orientation is to set " << endl;
    cout << endl;
    if(CAAInputWeb.GetMaterialOrient() == CATOrientationPositive)
      {
      cout << endl;     
      cout << "      MaterialOrient : CATOrientationPositive" << endl;
      cout << endl;
      }
    else if(CAAInputWeb.GetMaterialOrient() == CATOrientationNegative)
      {
      cout << endl;     
      cout << "      MaterialOrient : CATOrientationNegative" << endl;
      cout << endl;
      }
    }

  return S_OK;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::AnalyseSurfacicFlangeInputData (const CATUnicodeString &  InputDataFilePath,
                                                        CAAStmInputData &         CAAInputFlg)
  {
  // The aim of this method is :
  //   Retrieve the Surfacic Flange input data from a ".txt" file
  HRESULT rc  = E_FAIL;
  CATBoolean OK = TRUE;
  CATOrientation   Positive = CATOrientationPositive;
  CATOrientation   Negative = CATOrientationNegative;
  CATListOfCATUnicodeString FileLines;

  // Lecture du fichier de donnees :
  rc = ReadInputFile (InputDataFilePath, FileLines);

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(AnalyseSurfacicFlangeInputData) ERROR : Read File Input data has failed." << endl;
    cout << endl;
    return rc;
    }

  int NbLines = FileLines.Size();
  if(NbLines > 0)
    {
    // Available Keys :
    CATUnicodeString InputPartKey        ("INPUT:");
    CATUnicodeString OutputPartKey       ("OUTPUT:");
    CATUnicodeString LengthUnitKey       ("LENGTHUNIT:");
    CATUnicodeString ModifNameKey        ("MODIFNAME:");
    CATUnicodeString DisplayKey          ("DISPLAY:");

    CATUnicodeString BaseFeatureKey      ("BASEFEATURE:");
    CATUnicodeString BaseRadiusTypeKey   ("BASERADIUSTYPE:");
    CATUnicodeString BaseRadiusValueKey  ("BASERADIUS:");
    
    CATUnicodeString SuppTypeKey         ("SUPPTYPE:");
    CATUnicodeString SuppGeomKey         ("SUPPGEOM:");
    CATUnicodeString SuppLengthKey       ("SUPPLENGTH:");
    CATUnicodeString SuppApproxKey       ("SUPPAPPROX:");
    
    CATUnicodeString EOPTypeKey          ("EOPTYPE:");
    CATUnicodeString EOPGeomKey          ("EOPGEOM:");
    CATUnicodeString EOPLengthKey        ("EOPLENGTH:");
    
    CATUnicodeString BaseFeatOrientKey   ("BASEFEATUREORIENT:");
    CATUnicodeString FlangeSurfOrientKey ("FLANGESURFORIENT:");
    CATUnicodeString MaterialOrientKey   ("MATERIALORIENT:");
    
    CATUnicodeString Side1TypeKey        ("SIDE1TYPE:");
    CATUnicodeString Side1GeomKey        ("SIDE1GEOM:");
    CATUnicodeString Corner1TypeKey      ("CORNER1TYPE:");
    CATUnicodeString Corner1RadiusKey    ("CORNER1RADIUS:");
    
    CATUnicodeString Side2TypeKey        ("SIDE2TYPE:");
    CATUnicodeString Side2GeomKey        ("SIDE2GEOM:");
    CATUnicodeString Corner2TypeKey      ("CORNER2TYPE:");
    CATUnicodeString Corner2RadiusKey    ("CORNER2RADIUS:");
    
    CATUnicodeString ProcessTypeKey      ("PROCESSTYPE:");
    CATUnicodeString K_FactorKey         ("K_FACTOR:");
    
    CATUnicodeString CompensJoggleKey     ("COMPENSJOGGLE:");
    CATUnicodeString CompensSide1TypeKey  ("COMPENSSIDE1TYPE:");
    CATUnicodeString CompensSide1ValueKey ("COMPENSSIDE1VALUE:");
    CATUnicodeString CompensSide2TypeKey  ("COMPENSSIDE2TYPE:");
    CATUnicodeString CompensSide2ValueKey ("COMPENSSIDE2VALUE:");

    CATUnicodeString ReadLine   ("");
    CATUnicodeString DataToRead ("");
    double           Val = 0.;
    for(int i = 1; i <= NbLines; i++)
      {
      ReadLine = FileLines[i];

      if((ReadLine != "") && (ReadLine != " "))
        {
        if(ReadLine == InputPartKey)
          DataToRead = InputPartKey;
        else if(ReadLine == OutputPartKey)
          DataToRead = OutputPartKey;
        else if(ReadLine == LengthUnitKey)
          DataToRead = LengthUnitKey;
        else if(ReadLine == ModifNameKey)
          {
          CAAInputFlg.SetModifFlange(OK);
          DataToRead = ModifNameKey;
          }
        else if(ReadLine == DisplayKey)
          CAAInputFlg.SetDisplay(OK);
        else if(ReadLine == BaseFeatureKey)
          {
          CAAInputFlg.SetBaseFeatureToSet(OK);
          DataToRead = BaseFeatureKey;
          }
        else if(ReadLine == BaseRadiusTypeKey)
          {
          CAAInputFlg.SetBaseRadiusTypeToSet(OK);
          DataToRead = BaseRadiusTypeKey;
          }
        else if(ReadLine == BaseRadiusValueKey)
          {
          CAAInputFlg.SetBaseRadiusValueToSet(OK);
          DataToRead = BaseRadiusValueKey;
          }
        else if(ReadLine == SuppTypeKey)
          {
          CAAInputFlg.SetSupportTypeToSet(OK);
          DataToRead = SuppTypeKey;
          }
        else if(ReadLine == SuppGeomKey)
          {
          CAAInputFlg.SetSupportGeomToSet(OK);
          DataToRead = SuppGeomKey;
          }
        else if(ReadLine == SuppLengthKey)
          {
          CAAInputFlg.SetSupportLengthToSet(OK);
          DataToRead = SuppLengthKey;
          }
        else if(ReadLine == SuppApproxKey)
          {
          CAAInputFlg.SetSupportApproxToSet(OK);
          DataToRead = SuppApproxKey;
          }
        else if(ReadLine == EOPTypeKey)
          {
          CAAInputFlg.SetEOPTypeToSet(OK);
          DataToRead = EOPTypeKey;
          }
        else if(ReadLine == EOPGeomKey)
          {
          CAAInputFlg.SetEOPGeomToSet(OK);
          DataToRead = EOPGeomKey;
          }
        else if(ReadLine == EOPLengthKey)
          {
          CAAInputFlg.SetEOPLengthToSet(OK);
          DataToRead = EOPLengthKey;
          }
        else if(ReadLine == BaseFeatOrientKey)
          {
          CAAInputFlg.SetBaseFeatureOrientToSet(OK);
          DataToRead = BaseFeatOrientKey;
          }
        else if(ReadLine == FlangeSurfOrientKey)
          {
          CAAInputFlg.SetFlangeSurfOrientToSet(OK);
          DataToRead = FlangeSurfOrientKey;
          }
        else if(ReadLine == MaterialOrientKey)
          {
          CAAInputFlg.SetMaterialOrientToSet(OK);
          DataToRead = MaterialOrientKey;
          }
        else if(ReadLine == Side1TypeKey)
          {
          CAAInputFlg.SetSide1TypeToSet(OK);
          DataToRead = Side1TypeKey;
          }
        else if(ReadLine == Side1GeomKey)
          {
          CAAInputFlg.SetSide1GeomToSet(OK);
          DataToRead = Side1GeomKey;
          }
        else if(ReadLine == Corner1TypeKey)
          {
          CAAInputFlg.SetCorner1TypeToSet(OK);
          DataToRead = Corner1TypeKey;
          }
        else if(ReadLine == Corner1RadiusKey)
          {
          CAAInputFlg.SetCorner1RadiusToSet(OK);
          DataToRead = Corner1RadiusKey;
          }
        else if(ReadLine == Side2TypeKey)
          {
          CAAInputFlg.SetSide2TypeToSet(OK);
          DataToRead = Side2TypeKey;
          }
        else if(ReadLine == Side2GeomKey)
          {
          CAAInputFlg.SetSide2GeomToSet(OK);
          DataToRead = Side2GeomKey;
          }
        else if(ReadLine == Corner2TypeKey)
          {
          CAAInputFlg.SetCorner2TypeToSet(OK);
          DataToRead = Corner2TypeKey;
          }
        else if(ReadLine == Corner2RadiusKey)
          {
          CAAInputFlg.SetCorner2RadiusToSet(OK);
          DataToRead = Corner2RadiusKey;
          }
        else if(ReadLine == ProcessTypeKey)
          {
          CAAInputFlg.SetProcessTypeToSet(OK);
          DataToRead = ProcessTypeKey;
          }
        else if(ReadLine == K_FactorKey)
          {
          CAAInputFlg.SetK_FactorToSet(OK);
          DataToRead = K_FactorKey;
          }
        else if(ReadLine == CompensJoggleKey)
          {
          CAAInputFlg.SetCompensJoggleTypeToSet(OK);
          DataToRead = CompensJoggleKey;
          }
        else if(ReadLine == CompensSide1TypeKey)
          {
          CAAInputFlg.SetCompensSide1TypeToSet(OK);
          DataToRead = CompensSide1TypeKey;
          }
        else if(ReadLine == CompensSide1ValueKey)
          {
          CAAInputFlg.SetCompensSide1ValueToSet(OK);
          DataToRead = CompensSide1ValueKey;
          }
        else if(ReadLine == CompensSide2TypeKey)
          {
          CAAInputFlg.SetCompensSide2TypeToSet(OK);
          DataToRead = CompensSide2TypeKey;
          }     
        else if(ReadLine == CompensSide2ValueKey)
          {
          CAAInputFlg.SetCompensSide2ValueToSet(OK);
          DataToRead = CompensSide2ValueKey;
          }
        else
          {
          if(DataToRead == InputPartKey)
            CAAInputFlg.SetInputPartPath(ReadLine);
          else if(DataToRead == OutputPartKey)
            CAAInputFlg.SetOutputPartPath(ReadLine);
          else if(DataToRead == LengthUnitKey)
            CAAInputFlg.SetLengthUnit(ReadLine);
          else if(DataToRead == ModifNameKey)
            CAAInputFlg.SetModifFlangeName(ReadLine);
          else if(DataToRead == BaseFeatureKey)
            CAAInputFlg.SetBaseFeatureName(ReadLine);
          else if(DataToRead == BaseRadiusTypeKey)
            CAAInputFlg.SetBaseRadiusTypeName(ReadLine);
          else if(DataToRead == BaseRadiusValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetBaseRadiusValue(Val);
            }
          else if(DataToRead == SuppTypeKey)
            CAAInputFlg.SetSupportTypeName(ReadLine);
          else if(DataToRead == SuppGeomKey)
            CAAInputFlg.SetSupportGeomName(ReadLine);
          else if(DataToRead == SuppLengthKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetSupportLengthValue(Val);
            }
          else if(DataToRead == SuppApproxKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetSupportApproxValue(Val);
            }
          else if(DataToRead == EOPTypeKey)
            CAAInputFlg.SetEOPTypeName(ReadLine);
          else if(DataToRead == EOPGeomKey)
            CAAInputFlg.SetEOPGeomName(ReadLine);
          else if(DataToRead == EOPLengthKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetEOPLengthValue(Val);
            }
          else if(DataToRead == BaseFeatOrientKey)
            {
            if(ReadLine == "+")
              CAAInputFlg.SetBaseFeatureOrient(Positive);
            else if(ReadLine == "-")
              CAAInputFlg.SetBaseFeatureOrient(Negative);
            }
          else if(DataToRead == FlangeSurfOrientKey)
            {
            if(ReadLine == "+")
              CAAInputFlg.SetFlangeSurfOrient(Positive);
            else if(ReadLine == "-")
              CAAInputFlg.SetFlangeSurfOrient(Negative);
            }
          else if(DataToRead == MaterialOrientKey)
            {
            if(ReadLine == "+")
              CAAInputFlg.SetMaterialOrient(Positive);
            else if(ReadLine == "-")
              CAAInputFlg.SetMaterialOrient(Negative);
            }
          else if(DataToRead == Side1TypeKey)
            CAAInputFlg.SetSide1TypeName(ReadLine);
          else if(DataToRead == Side1GeomKey)
            CAAInputFlg.SetSide1GeomName(ReadLine);
          else if(DataToRead == Corner1TypeKey)
            CAAInputFlg.SetCorner1TypeName(ReadLine);
          else if(DataToRead == Corner1RadiusKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetCorner1RadiusValue(Val);
            }
          else if(DataToRead == Side2TypeKey)
            CAAInputFlg.SetSide2TypeName(ReadLine);
          else if(DataToRead == Side2GeomKey)
            CAAInputFlg.SetSide2GeomName(ReadLine);
          else if(DataToRead == Corner2TypeKey)
            CAAInputFlg.SetCorner2TypeName(ReadLine);
          else if(DataToRead == Corner2RadiusKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetCorner2RadiusValue(Val);
            }
          else if(DataToRead == ProcessTypeKey)
            CAAInputFlg.SetProcessTypeName(ReadLine);
          else if(DataToRead == K_FactorKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetK_FactorValue(Val);
            }
          else if(DataToRead == CompensJoggleKey)
            CAAInputFlg.SetCompensJoggleTypeName(ReadLine);
          else if(DataToRead == CompensSide1TypeKey)
            CAAInputFlg.SetCompensSide1TypeName(ReadLine);
          else if(DataToRead == CompensSide1ValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetCompensSide1Value(Val);
            }
          else if(DataToRead == CompensSide2TypeKey)
            CAAInputFlg.SetCompensSide2TypeName(ReadLine);
          else if(DataToRead == CompensSide2ValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputFlg.SetCompensSide2Value(Val);
            }
          }
        }
      }
    }
  else
    {
    cout << endl;
    cout << "(AnalyseSurfacicFlangeInputData) ERROR : Read File Input data has failed." << endl;
    cout << endl;
    return rc;
    }
  
  // Traces :
  cout << endl;
  cout << "(AnalyseSurfacicFlangeInputData) " << endl;
  cout << endl;
  cout << "      InputPartPath  : " << CAAInputFlg.GetInputPartPath().ConvertToChar() << endl;
  cout << endl;
  if(CAAInputFlg.GetDisplay())
    {
    cout << "      Display " << endl;
    cout << endl;
    }
  else
    {
    cout << "      OutputPartPath : " << CAAInputFlg.GetOutputPartPath().ConvertToChar() << endl;
    cout << endl;
    }
  cout << "      Length Unit    : " << CAAInputFlg.GetLengthUnit().ConvertToChar() << endl;
  cout << endl;

  if(CAAInputFlg.GetModifFlange())
    {
    cout << endl;     
    cout << "    ==> Surfacic Flange a modifier " << endl;
    cout << endl;
    cout << "      Name  : " << CAAInputFlg.GetModifFlangeName().ConvertToChar() << endl;
    cout << endl;
    }
  
  if(CAAInputFlg.GetBaseFeatureToSet())
    {
    cout << endl;     
    cout << "    ==> Base Feature is to set " << endl;
    cout << endl;
    cout << "      Base Feature Name  : " << CAAInputFlg.GetBaseFeatureName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetBaseRadiusTypeToSet()) 
    {
    cout << endl;     
    cout << "    ==> Radius Type is to set " << endl;
    cout << endl;
    cout << "       Radius Type : " << CAAInputFlg.GetBaseRadiusTypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetBaseRadiusValueToSet())
    {
    cout << endl;     
    cout << "    ==> Radius value is to set " << endl;
    cout << endl;
    cout << "      Radius value : " << CAAInputFlg.GetBaseRadiusValue() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetSupportTypeToSet())
    {
    cout << endl;     
    cout << "    ==> Support type is to set " << endl;
    cout << endl;
    cout << "      Support type : " << CAAInputFlg.GetSupportTypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetSupportGeomToSet())
    {
    cout << endl;     
    cout << "    ==> Support geometry is to set " << endl;
    cout << endl;
    cout << "      Support geometry : " << CAAInputFlg.GetSupportGeomName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetSupportLengthToSet())
    {
    cout << endl;     
    cout << "    ==> Support Length is to set " << endl;
    cout << endl;
    cout << "      Support Length : " << CAAInputFlg.GetSupportLengthValue() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetSupportApproxToSet())
    {
    cout << endl;     
    cout << "    ==> Support Approximation Length is to set " << endl;
    cout << endl;
    cout << "      Support Approximation Length  : " << CAAInputFlg.GetSupportApproxValue() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetEOPTypeToSet())
    {
    cout << endl;     
    cout << "    ==> EOP type is to set " << endl;
    cout << endl;
    cout << "      EOP type  : " << CAAInputFlg.GetEOPTypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetEOPGeomToSet())
    {
    cout << endl;     
    cout << "    ==> EOP geometry is to set " << endl;
    cout << endl;
    cout << "      EOP geometry  : " << CAAInputFlg.GetEOPGeomName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetEOPLengthToSet())
    {
    cout << endl;     
    cout << "    ==> EOP Length is to set " << endl;
    cout << endl;
    cout << "      EOP Length   : " << CAAInputFlg.GetEOPLengthValue() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetBaseFeatureOrientToSet())
    {
    cout << endl;     
    cout << "    ==> Base Feature orientation is to set " << endl;
    cout << endl;
    if(CAAInputFlg.GetBaseFeatureOrient() == CATOrientationPositive)
      {
      cout << endl;     
      cout << "      Base Feature Orientation : CATOrientationPositive" << endl;
      cout << endl;
      }
    else if(CAAInputFlg.GetBaseFeatureOrient() == CATOrientationNegative)
      {
      cout << endl;     
      cout << "      Base Feature Orientation : CATOrientationNegative" << endl;
      cout << endl;
      }
    }

  if(CAAInputFlg.GetFlangeSurfOrientToSet())
    {
    cout << endl;     
    cout << "    ==> FlangeSurf Orientation is to set " << endl;
    cout << endl;
    if(CAAInputFlg.GetFlangeSurfOrient() == CATOrientationPositive)
      {
      cout << endl;     
      cout << "      FlangeSurf Orientation : CATOrientationPositive" << endl;
      cout << endl;
      }
    else if(CAAInputFlg.GetFlangeSurfOrient() == CATOrientationNegative)
      {
      cout << endl;     
      cout << "      FlangeSurfOrient : CATOrientationNegative" << endl;
      cout << endl;
      }
    }

  if(CAAInputFlg.GetMaterialOrientToSet())
    {
    cout << endl;     
    cout << "    ==> Material Orientation is to set " << endl;
    cout << endl;
    if(CAAInputFlg.GetMaterialOrient() == CATOrientationPositive)
      {
      cout << endl;     
      cout << "      Material Orientation : CATOrientationPositive" << endl;
      cout << endl;
      }
    else if(CAAInputFlg.GetMaterialOrient() == CATOrientationNegative)
      {
      cout << endl;     
      cout << "      Material Orientation : CATOrientationNegative" << endl;
      cout << endl;
      }
    }

  if(CAAInputFlg.GetSide1TypeToSet())
    {
    cout << endl;     
    cout << "    ==> Side 1 type is to set " << endl;
    cout << endl;
    cout << "      Side 1 type  : " << CAAInputFlg.GetSide1TypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetSide1GeomToSet())
    {
    cout << endl;     
    cout << "    ==> Side 1 geometry is to set " << endl;
    cout << endl;
    cout << "      Side 1 geometry  : " << CAAInputFlg.GetSide1GeomName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetCorner1TypeToSet())
    {
    cout << endl;     
    cout << "    ==> Side 1 Corner type is to set " << endl;
    cout << endl;
    cout << "      Side 1 Corner type  : " << CAAInputFlg.GetCorner1TypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetCorner1RadiusToSet())
    {
    cout << endl;     
    cout << "    ==> Side 1 Corner Radius is to set " << endl;
    cout << endl;
    cout << "      Side 1 Corner Radius  : " << CAAInputFlg.GetCorner1RadiusValue() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetSide2TypeToSet())
    {
    cout << endl;     
    cout << "    ==> Side 2 type is to set " << endl;
    cout << endl;
    cout << "      Side 2 type  : " << CAAInputFlg.GetSide2TypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetSide2GeomToSet())
    {
    cout << endl;     
    cout << "    ==> Side 2 geometry is to set " << endl;
    cout << endl;
    cout << "      Side 2 geometry  : " << CAAInputFlg.GetSide2GeomName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetCorner2TypeToSet())
    {
    cout << endl;     
    cout << "    ==> Side 2 Corner type is to set " << endl;
    cout << endl;
    cout << "      Side 2 Corner type  : " << CAAInputFlg.GetCorner2TypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetCorner2RadiusToSet())
    {
    cout << endl;     
    cout << "    ==> Side 2 Corner Radius is to set " << endl;
    cout << endl;
    cout << "      Side 2 Corner Radius  : " << CAAInputFlg.GetCorner2RadiusValue() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetProcessTypeToSet())
    {
    cout << endl;     
    cout << "    ==> Process Type is to set " << endl;
    cout << endl;
    cout << "      Process Type : " << CAAInputFlg.GetProcessTypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetK_FactorToSet())
    {
    cout << endl;     
    cout << "    ==> K_Factor is to set " << endl;
    cout << endl;
    cout << "      K_Factor  : " << CAAInputFlg.GetK_FactorValue() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetCompensJoggleTypeToSet())
    {
    cout << endl;     
    cout << "    ==> Joggle Compensation is to set " << endl;
    cout << endl;
    cout << "      Joggle Compensation  : " << CAAInputFlg.GetCompensJoggleTypeName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputFlg.GetCompensSide1TypeToSet())
    {
    cout << endl;     
    cout << "    ==> Side 1 Compensation Type is to set " << endl;
    cout << endl;
    cout << "      Side 1 Compensation Type : " << CAAInputFlg.GetCompensSide1TypeName().ConvertToChar() << endl;
    cout << endl;
    }
  
  if(CAAInputFlg.GetCompensSide1ValueToSet())
    {
    cout << endl;     
    cout << "    ==> Side 1 Compensation Value is to set " << endl;
    cout << endl;
    cout << "      Side 1 Compensation Value : " << CAAInputFlg.GetCompensSide1Value() << endl;
    cout << endl;
    }
  
  if(CAAInputFlg.GetCompensSide2TypeToSet())
    {
    cout << endl;     
    cout << "    ==> Side 2 Compensation Type is to set " << endl;
    cout << endl;
    cout << "      Side 2 Compensation Type : " << CAAInputFlg.GetCompensSide2TypeName().ConvertToChar() << endl;
    cout << endl;
    }
  
  if(CAAInputFlg.GetCompensSide2ValueToSet())
    {
    cout << endl;     
    cout << "    ==> Side 2 Compensation Value is to set " << endl;
    cout << endl;
    cout << "      Side 2 Compensation Value : " << CAAInputFlg.GetCompensSide2Value() << endl;
    cout << endl;
    }

  return S_OK;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::AnalyseJoggleInputData (const CATUnicodeString &  InputDataFilePath,
                                                CAAStmInputData &         CAAInputJoggle)
  {
  // The aim of this method is :
  //   Retrieve the Joggle input data from a ".txt" file
  HRESULT rc  = E_FAIL;
  
  CATListOfCATUnicodeString FileLines;

  // Lecture du fichier de donnees :
  rc = ReadInputFile (InputDataFilePath, FileLines);

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(AnalyseJoggleInputData) ERROR : Read File Input data has failed." << endl;
    cout << endl;
    return rc;
    }
  
  double Val = 0.;
  CATBoolean OK = TRUE;
  CATOrientation   Positive = CATOrientationPositive;
  CATOrientation   Negative = CATOrientationNegative;
  int NbLines = FileLines.Size();
  if(NbLines > 0)
    {
    // Available Keys :
    CATUnicodeString InputPartKey        ("INPUT:");
    CATUnicodeString OutputPartKey       ("OUTPUT:");
    CATUnicodeString LengthUnitKey       ("LENGTHUNIT:");
    CATUnicodeString ModifNameKey        ("MODIFNAME:");
    CATUnicodeString DisplayKey          ("DISPLAY:");

    CATUnicodeString SupportGeomKey      ("SUPPORT:");
    CATUnicodeString PlaneGeomKey        ("PLANE:");
    
    CATUnicodeString DepthValueKey       ("DEPTH:");
    CATUnicodeString DepthOrientKey      ("DEPTHORIENT:");
    
    CATUnicodeString RunoutValueKey      ("RUNOUT:");
    CATUnicodeString RunoutOrientKey     ("RUNOUTORIENT:");

    CATUnicodeString ClearanceValueKey   ("CLEARANCE:");

    CATUnicodeString StartRadiusValueKey ("STARTRADIUS:");
    CATUnicodeString EndRadiusValueKey   ("ENDRADIUS:");

    CATUnicodeString ReadLine   ("");
    CATUnicodeString DataToRead ("");
    
    for(int i = 1; i <= NbLines; i++)
      {
      ReadLine = FileLines[i];

      if((ReadLine != "") && (ReadLine != " "))
        {
        if(ReadLine == InputPartKey)
          DataToRead = InputPartKey;
        else if(ReadLine == OutputPartKey)
          DataToRead = OutputPartKey;
        else if(ReadLine == LengthUnitKey)
          DataToRead = LengthUnitKey;
        else if(ReadLine == ModifNameKey)
          {
          CAAInputJoggle.SetModifJoggle(OK);
          DataToRead = ModifNameKey;
          }
        else if(ReadLine == DisplayKey)
          CAAInputJoggle.SetDisplay(OK);
        else if(ReadLine == SupportGeomKey)
          {
          CAAInputJoggle.SetSupportGeomToSet(OK);
          DataToRead = SupportGeomKey;
          }
        else if(ReadLine == PlaneGeomKey)
          {
          CAAInputJoggle.SetPlaneGeomToSet(OK);
          DataToRead = PlaneGeomKey;
          }
        else if(ReadLine == DepthValueKey)
          {
          CAAInputJoggle.SetDepthValueToSet(OK);
          DataToRead = DepthValueKey;
          }
        else if(ReadLine == DepthOrientKey)
          {
          CAAInputJoggle.SetDepthOrientToSet(OK);
          DataToRead = DepthOrientKey;
          }
        else if(ReadLine == RunoutValueKey)
          {
          CAAInputJoggle.SetRunoutValueToSet(OK);
          DataToRead = RunoutValueKey;
          }
        else if(ReadLine == RunoutOrientKey)
          {
          CAAInputJoggle.SetRunoutOrientToSet(OK);
          DataToRead = RunoutOrientKey;
          }
        else if(ReadLine == ClearanceValueKey)
          {
          CAAInputJoggle.SetClearanceValueToSet(OK);
          DataToRead = ClearanceValueKey;
          }
        else if(ReadLine == StartRadiusValueKey)
          {
          CAAInputJoggle.SetStartRadiusValueToSet(OK);
          DataToRead = StartRadiusValueKey;
          }
        else if(ReadLine == EndRadiusValueKey)
          {
          CAAInputJoggle.SetEndRadiusValueToSet(OK);
          DataToRead = EndRadiusValueKey;
          }
        else
          {
          if(DataToRead == InputPartKey)
            CAAInputJoggle.SetInputPartPath(ReadLine);
          else if(DataToRead == OutputPartKey)
            CAAInputJoggle.SetOutputPartPath(ReadLine);
          else if(DataToRead == LengthUnitKey)
            CAAInputJoggle.SetLengthUnit(ReadLine);
          else if(DataToRead == ModifNameKey)
            CAAInputJoggle.SetModifJoggleName(ReadLine);
          else if(DataToRead == SupportGeomKey)
            CAAInputJoggle.SetSupportGeomName(ReadLine);
          else if(DataToRead == PlaneGeomKey)
            CAAInputJoggle.SetPlaneGeomName(ReadLine);
          else if(DataToRead == DepthValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputJoggle.SetDepthValue(Val);
            }
          else if(DataToRead == DepthOrientKey)
            {
            if(ReadLine == "+")
              CAAInputJoggle.SetDepthOrient(Positive);
            else if(ReadLine == "-")
              CAAInputJoggle.SetDepthOrient(Negative);
            }
          else if(DataToRead == RunoutValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputJoggle.SetRunoutValue(Val);
            }
          else if(DataToRead == RunoutOrientKey)
            {
            if(ReadLine == "+")
              CAAInputJoggle.SetRunoutOrient(Positive);
            else if(ReadLine == "-")
              CAAInputJoggle.SetRunoutOrient(Negative);
            }
          else if(DataToRead == ClearanceValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputJoggle.SetClearanceValue(Val);
            }
          else if(DataToRead == StartRadiusValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputJoggle.SetStartRadiusValue(Val);
            }
          else if(DataToRead == EndRadiusValueKey)
            {
            ReadLine.ConvertToNum(&Val);
            CAAInputJoggle.SetEndRadiusValue(Val);
            }
          }
        }
      }
    }
  else
    {
    cout << endl;
    cout << "(AnalyseJoggleInputData) ERROR : Read File Input data has failed." << endl;
    cout << endl;
    return rc;
    }
  
  // Traces :
  cout << endl;
  cout << "(AnalyseJoggleInputData) " << endl;
  cout << endl;
  cout << "      InputPartPath  : " << CAAInputJoggle.GetInputPartPath().ConvertToChar() << endl;
  if(CAAInputJoggle.GetDisplay())
    {
    cout << "      Display " << endl;
    cout << endl;
    }
  else
    {
    cout << endl;
    cout << "      OutputPartPath : " << CAAInputJoggle.GetOutputPartPath().ConvertToChar() << endl;
    cout << endl;
    }
  cout << "      Length Unit    : " << CAAInputJoggle.GetLengthUnit().ConvertToChar() << endl;
  cout << endl;
  
  if(CAAInputJoggle.GetModifJoggle())
    {
    cout << endl;     
    cout << "    ==> Joggle a modifier " << endl;
    cout << endl;
    cout << "      Name  : " << CAAInputJoggle.GetModifJoggleName().ConvertToChar() << endl;
    cout << endl;
    }
  
  if(CAAInputJoggle.GetSupportGeomToSet())
    {
    cout << endl;     
    cout << "    ==> Support geometry is to set " << endl;
    cout << endl;
    cout << "      Support Name  : " << CAAInputJoggle.GetSupportGeomName().ConvertToChar() << endl;
    cout << endl;
    }

  if(CAAInputJoggle.GetPlaneGeomToSet())
    {
    cout << endl;     
    cout << "    ==> Joggle Plane geometry is to set " << endl;
    cout << endl;
    cout << "      Joggle Plane  : " << CAAInputJoggle.GetPlaneGeomName().ConvertToChar() << endl;
    cout << endl;
    }
  
  if(CAAInputJoggle.GetDepthValueToSet())
    {
    cout << endl;     
    cout << "    ==> Depth Value is to set " << endl;
    cout << endl;
    cout << "      Depth Value  : " << CAAInputJoggle.GetDepthValue() << endl;
    cout << endl;
    }

  if(CAAInputJoggle.GetDepthOrientToSet())
    {
    cout << endl;     
    cout << "    ==> Depth Orientation is to set " << endl;
    cout << endl;
    if(CAAInputJoggle.GetDepthOrient() == CATOrientationPositive)
      {
      cout << endl;     
      cout << "      Depth Orientation : CATOrientationPositive" << endl;
      cout << endl;
      }
    else if(CAAInputJoggle.GetDepthOrient() == CATOrientationNegative)
      {
      cout << endl;     
      cout << "      Depth Orientation : CATOrientationNegative" << endl;
      cout << endl;
      }
    }

  if(CAAInputJoggle.GetRunoutValueToSet())
    {
    cout << endl;     
    cout << "    ==> Runout Value is to set " << endl;
    cout << endl;
    cout << "      Runout Value  : " << CAAInputJoggle.GetRunoutValue() << endl;
    cout << endl;
    }

  if(CAAInputJoggle.GetRunoutOrientToSet())
    {
    cout << endl;     
    cout << "    ==> Runout Orientation is to set " << endl;
    cout << endl;
    if(CAAInputJoggle.GetRunoutOrient() == CATOrientationPositive)
      {
      cout << endl;     
      cout << "      Runout Orientation : CATOrientationPositive" << endl;
      cout << endl;
      }
    else if(CAAInputJoggle.GetRunoutOrient() == CATOrientationNegative)
      {
      cout << endl;     
      cout << "      Runout Orientation : CATOrientationNegative" << endl;
      cout << endl;
      }
    }
  
  if(CAAInputJoggle.GetClearanceValueToSet())
    {
    cout << endl;     
    cout << "    ==> Clearance Value is to set " << endl;
    cout << endl;
    cout << "      Clearance Value  : " << CAAInputJoggle.GetClearanceValue() << endl;
    cout << endl;
    }
    
  if(CAAInputJoggle.GetStartRadiusValueToSet())
    {
    cout << endl;     
    cout << "    ==> Start Radius Value is to set " << endl;
    cout << endl;
    cout << "      Start Radius Value  : " << CAAInputJoggle.GetStartRadiusValue() << endl;
    cout << endl;
    }

  if(CAAInputJoggle.GetEndRadiusValueToSet())
    {
    cout << endl;     
    cout << "    ==> End Radius Value is to set " << endl;
    cout << endl;
    cout << "      End Radius Value  : " << CAAInputJoggle.GetEndRadiusValue() << endl;
    cout << endl;
    }

  return S_OK;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::FindWeb (const CATISpecObject_var & ispPrtPartSpec,
                                 CATISpecObject **          opiWebSpec)
  {
  // The aim of this method is 
  //   Find the Web in the Part.
  CATUnicodeString ErrorMsg("");
  
  HRESULT rc = E_FAIL;
  
  if(NULL_var != ispPrtPartSpec)
    {
    CATLISTV(CATISpecObject_var) SpecsList;
  
    CATIDescendants * pPartAsDescendant = NULL;
  
    rc = ispPrtPartSpec -> QueryInterface(IID_CATIDescendants, (void**)& pPartAsDescendant) ;
    
	  if(SUCCEEDED(rc))
      {        
      pPartAsDescendant -> GetAllChildren(CATIStmWeb::ClassName(), SpecsList);
            
			int NbSpecs = SpecsList.Size();
			if(NbSpecs == 1)
			  {
        CATISpecObject_var spCurrentSpec = SpecsList[1];
        
        if(NULL_var != spCurrentSpec)
          rc = spCurrentSpec -> QueryInterface(IID_CATISpecObject, (void **) opiWebSpec);
        else
          rc = E_FAIL;
			  }
      else
        rc = E_FAIL;
      
      pPartAsDescendant -> Release();
      pPartAsDescendant = NULL;
      }
    }

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(FindWeb) ERROR : " << ErrorMsg.ConvertToChar() << endl;
    cout << endl;
    }
  return rc;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::FindFeatureInSpecTree (const CATISpecObject_var & ispPrtPartSpec,
                                               const CATUnicodeString &   iSpecName, 
                                               CATISpecObject **          opiSpec)
  {
  // The aim of this method is :
  //   Searching a spec by its Name in a Part document
  CATUnicodeString ErrorMsg("");
  (*opiSpec) = NULL;

  HRESULT rc = E_FAIL;
                
  cout << endl;
  cout << "(FindFeatureInSpecTree) Recherche de : " << iSpecName.ConvertToChar() << endl;
  cout << endl;
  
  if(NULL_var != ispPrtPartSpec)
    {
    CATLISTV(CATISpecObject_var) SpecsList;
  
    CATIDescendants * pPartAsDescendant = NULL;

    rc = ispPrtPartSpec -> QueryInterface(IID_CATIDescendants, (void**)& pPartAsDescendant) ;
    
	  if(SUCCEEDED(rc))
      {        
      pPartAsDescendant -> GetAllChildren(CATISpecObject::ClassName(), SpecsList);
            
			int NbSpecs = SpecsList.Size();
      int NumSpec = 0;

			if(NbSpecs > 0)
			  {
        for(int iSpec = 1; (iSpec <= NbSpecs) && (NumSpec == 0); iSpec++)
          {
          CATISpecObject_var spCurrentSpec = SpecsList[iSpec];
          
          if(NULL_var != spCurrentSpec)
            {
            CATIAlias * piAsAlias = NULL;
           
            rc = spCurrentSpec -> QueryInterface(IID_CATIAlias, (void**)& piAsAlias) ;
    
	          if(SUCCEEDED(rc))
              {
              CATUnicodeString strAlias = piAsAlias -> GetAlias();
              if(strAlias == iSpecName)
                NumSpec = iSpec;

              piAsAlias -> Release();
              piAsAlias = NULL;
              }
            }
          }
        
        if(NumSpec > 0)
          {
          CATISpecObject_var spFoundSpec;
          CATISpecObject_var spSpec = SpecsList[NumSpec];
        
          if(NULL_var != spSpec)
            {
            CATUnicodeString strSpec = spSpec -> GetType();

            if(strSpec != "CATSHM_FeatForTopoStorage")
              spFoundSpec = spSpec;
            else
              {
              CATISpecObject_var hFatherSpec = spSpec -> GetFather();
              if(NULL_var != hFatherSpec)
                {
                hFatherSpec -> Release();
                spFoundSpec = hFatherSpec;
                }
              }

            if(NULL_var != spFoundSpec)
              {
              rc = spFoundSpec -> QueryInterface(IID_CATISpecObject, (void **) opiSpec);

              if(SUCCEEDED(rc))
                {
                strSpec = spFoundSpec -> GetType();
                  
                cout << endl;
                cout << "(FindFeatureInSpecTree) Found Spec : " << strSpec.ConvertToChar() << endl;
                cout << endl;
                }
              }
            }
          else
            rc = E_FAIL;
          }
        else
          rc = E_FAIL;
			  }
      else
        rc = E_FAIL;
      
      pPartAsDescendant -> Release();
      pPartAsDescendant = NULL;
      }
    }

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(FindFeatureInSpecTree) ERROR : " << ErrorMsg.ConvertToChar() << endl;
    cout << endl;
    }
  return rc;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::FindFeaturesInSpecTree (const CATISpecObject_var &        ispPrtPartSpec,
                                                const CATListOfCATUnicodeString & iSpecNamesList,
                                                CATLISTP(CATISpecObject) &        oSpecsList)
  {
  // The aim of this method is :
  //   Searching a set of specs in a Part document
  CATUnicodeString ErrorMsg("");
  oSpecsList.RemoveAll();
  HRESULT rc = E_FAIL;
  int NbSpecNames = iSpecNamesList.Size();

  if(NbSpecNames > 0)
    {
    rc = S_OK;

    for(int iSpec = 1; (iSpec <= NbSpecNames) && (SUCCEEDED(rc)); iSpec++)
      {
      CATISpecObject * piFoundSpec = NULL;

      rc = FindFeatureInSpecTree (ispPrtPartSpec, iSpecNamesList[iSpec], &piFoundSpec);

      if(SUCCEEDED(rc))
        oSpecsList.Append(piFoundSpec);
      else
        {
        cout << endl;
        cout << "(SearchSpecifications) ERROR : Spec : " << iSpecNamesList[iSpec].ConvertToChar() << " NOT found." << endl;
        cout << endl;
        }
      }
    }
  else
    {
    ErrorMsg = "NbSpecNames == 0";
    }

  if(FAILED(rc))
    {
    cout << endl;
    cout << "(SearchSpecifications) ERROR : " << ErrorMsg.ConvertToChar() << endl;
    cout << endl;
    }
  return rc;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::Update (CATISpecObject * ipiSpec)
  { 
  // The aim of this method is 
  //   Updating a Feature and catching the error if any.
  CATUnicodeString ErrorMsg("");

  HRESULT rc = E_FAIL; 
  if(NULL != ipiSpec) 
    {
    CATTry 
      {	 
      ipiSpec -> Update();
        
      rc = S_OK;
      }
        
    CATCatch(CATMfErrUpdate, error)	
      {
      if(NULL != error)
        {
        ErrorMsg = error -> GetDiagnostic(); 
        ::Flush(error);
        }
      rc = E_FAIL; 
      }

    CATCatch(CATError, error)
      {
      if(NULL != error)
        {
        ErrorMsg = error -> GetMessageText();
        ::Flush(error);
        }
      rc = E_FAIL; 
      }
        
    CATEndTry;
    }
  else
    {
    ErrorMsg = "The Feature to update is NULL.";
    }
  
  if(FAILED(rc))
    {
    cout << endl;
    cout << "(Update) ERROR : " << ErrorMsg.ConvertToChar() << endl;
    cout << endl;
    }
  
  return rc ; 
  } 

// ---------------------------------------------------------------------------------------------
double CAAStmServices::ConvertLengthToMKS (const CATUnicodeString & iLengthUnitName,
                                           const double &           iValueToConvert)
  {
  double MKSVal = 0.;
  if(iLengthUnitName == "mm")
    MKSVal = 0.001 * iValueToConvert;
  else if(iLengthUnitName == "in")
    MKSVal = 0.0254 * iValueToConvert;
  
  return MKSVal;
  }

// ---------------------------------------------------------------------------------------------
HRESULT CAAStmServices::Display (CATISpecObject * ipiSpec)
  {
  HRESULT rc = E_FAIL; 
  
  if(NULL != ipiSpec) 
    {
    CATIStmWeb *         piStmWeb        = NULL;
    CATIStmFlangeSurf *  piStmFlangeSurf = NULL;
    CATIStmJoggle *      piStmJoggle     = NULL;
    
    CATIAlias_var        spAlias;
    CATIParmAsStored_var spStored;
    CATUnicodeString     Name("");
    double               Val = 0.;
    CATUnicodeString     LengthUnitName("");
    CATUnicodeString     AngleUnitName ("");

    // Retrieve the current Length unit and the current Angle unit :
    CATIParmDictionary_var spParmDic = CATCkeGlobalFunctions::GetParmDictionary();
    if(NULL_var != spParmDic)
      {
      CATICkeUnit_var spLengthUnit = spParmDic -> GetLengthType();
      CATICkeUnit_var spAngleUnit  = spParmDic -> GetAngleType();
      if(NULL_var != spLengthUnit) LengthUnitName = spLengthUnit -> Symbol();
      if(NULL_var != spAngleUnit)  AngleUnitName  = spAngleUnit  -> Symbol();
      }

    rc = ipiSpec -> QueryInterface (IID_CATIStmWeb, (void **)& piStmWeb);
    
    if(NULL != piStmWeb)
      {
      cout << endl;
      cout << endl;
      cout << " ============== " << endl;
      cout << "  Web entries : " << endl;
      cout << " ============== " << endl;
      cout << endl;
      cout << endl;
      spAlias = ipiSpec;
      if(NULL_var != spAlias)
        {
        Name = spAlias -> GetAlias();
        
        cout << " Web Name : " << Name.ConvertToChar() << endl;
        cout << endl;
        }
      else
        rc = E_FAIL;

      if(SUCCEEDED(rc))
        {
			  // Support :
			  CATISpecObject * piSupportSpec = NULL;

			  rc = piStmWeb -> GetSupport (&piSupportSpec);
      
			  if(SUCCEEDED(rc) && (NULL != piSupportSpec))
          {
				  spAlias = piSupportSpec;
				  if(NULL_var != spAlias)
            {
						Name = spAlias -> GetAlias();
                
						cout << endl;
						cout << " Web Get Support : " << Name.ConvertToChar() << endl;
						cout << endl;
            }
				  piSupportSpec -> Release();
				  piSupportSpec = NULL;
          }
			  else 
          {
				  cout <<" Error of the method CATIStmWeb->GetSupport"<<endl;
          }
        }
      
      if(SUCCEEDED(rc))
        {
        // Boundary :
        CATLISTP(CATISpecObject) LimitsSpecList;
        CATListOfInt             ViewTypeList;

        rc = piStmWeb -> GetBoundaryElements (LimitsSpecList, ViewTypeList);

        if(SUCCEEDED(rc))
          {
          cout << endl;
          cout << " Boundary : " << endl;
          cout << endl;
          
          CATISpecObject * piLimitSpec = NULL;

          for(int i = 1; i <= LimitsSpecList.Size(); i++)
            {
            piLimitSpec = LimitsSpecList[i];
            if(NULL != piLimitSpec)
              {
              spAlias = piLimitSpec;
              if(NULL_var != spAlias)
                {
                Name = spAlias -> GetAlias();
                
                cout << "   - " << Name.ConvertToChar() << endl;
                }
              piLimitSpec -> Release();
              piLimitSpec = NULL;
              }
            }
          cout << endl;
          }
        }
            
      if(SUCCEEDED(rc))
        {
        // Material Orientation :
        CATOrientation MaterialOrient;

        rc = piStmWeb -> GetMaterialOrient (MaterialOrient);

        if(SUCCEEDED(rc))
          {
          if(MaterialOrient == CATOrientationPositive)
            {
            cout << endl;
            cout << " Material orientation : Positive" << endl;
            cout << endl;
            }
          else if(MaterialOrient == CATOrientationNegative)
            {
            cout << endl;
            cout << " Material orientation : Negative" << endl;
            cout << endl;
            }
          }
        }

      if(SUCCEEDED(rc))
        {
        // Joggles :
        CATLISTP(CATISpecObject) ListJoggleSpecs;
        
        rc = piStmWeb -> GetJoggles (ListJoggleSpecs);
        
        if(SUCCEEDED(rc))
          {
          int NbJoggles = ListJoggleSpecs.Size();
          if(NbJoggles > 0)
            {
            cout << endl;
            cout << " Joggle(s) : " << endl;
            cout << endl;
            
            CATISpecObject * piJoggleSpec = NULL;
            
            for(int i = 1; i <= NbJoggles; i++)
              {
              piJoggleSpec = ListJoggleSpecs[i];
              if(NULL != piJoggleSpec)
                {
                spAlias = piJoggleSpec;
                if(NULL_var != spAlias)
                  {
                  Name = spAlias -> GetAlias();
                  
                  cout << "    - " << Name.ConvertToChar() << endl;
                  }
                piJoggleSpec -> Release();
                piJoggleSpec = NULL;
                }
              }
            }
          }
        }
      }
    else
      {
      rc = ipiSpec -> QueryInterface (IID_CATIStmFlangeSurf, (void **)& piStmFlangeSurf);
    
      if(NULL != piStmFlangeSurf)
        {
        cout << endl;
        cout << endl;
        cout << " ========================== " << endl;
        cout << "  Surfacic Flange entries : "  << endl;
        cout << " ========================== " << endl;
        cout << endl;
        cout << endl;
        spAlias = ipiSpec;
        if(NULL_var != spAlias)
          {
          Name = spAlias -> GetAlias();
        
          cout << " Surfacic Flange Name : " << Name.ConvertToChar() << endl;
          cout << endl;
          }
        else
         rc = E_FAIL;

        if(SUCCEEDED(rc))
          {
          // Base Feature :
          CATISpecObject * piBaseFeatureSpec = NULL;

          rc = piStmFlangeSurf -> GetBaseFeature (&piBaseFeatureSpec);
      
          if(SUCCEEDED(rc) && (NULL != piBaseFeatureSpec))
            {
            spAlias = piBaseFeatureSpec;
            if(NULL_var != spAlias)
              {
              Name = spAlias -> GetAlias();
                
              cout << endl;
              cout << " Base Feature : " << Name.ConvertToChar() << endl;
              cout << endl;
              }
            piBaseFeatureSpec -> Release();
            piBaseFeatureSpec = NULL;
            }
          }

        if(SUCCEEDED(rc))
          {
          // Bend Radius :
          CATUnicodeString RadiusType("");

          rc = piStmFlangeSurf -> GetBendRadiusType (RadiusType);

          if(SUCCEEDED(rc))
            {
            CATICkeParm * piBendRadius = NULL;

            rc = piStmFlangeSurf -> GetBendRadiusValue (&piBendRadius);
                      
            if(SUCCEEDED(rc) && (NULL != piBendRadius))
              {
              spStored = piBendRadius;
              if(NULL_var != spStored)
                {
                Val = spStored -> ValueStored();
                
                cout << endl;
                cout << " Bend Radius : Type  : " << RadiusType.ConvertToChar() << endl;
                cout << endl;
                cout << "               Value : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
                cout << endl;
                }
              piBendRadius -> Release();
              piBendRadius = NULL;
              }
            }
          }

        if(SUCCEEDED(rc))
          {
          // Support :
          CATUnicodeString SupportType("");

          rc = piStmFlangeSurf -> GetSupportType (SupportType);

          if(SUCCEEDED(rc))
            {
            CATISpecObject * piSupportSpec = NULL;

            rc = piStmFlangeSurf -> GetSupport (&piSupportSpec);
      
            if(SUCCEEDED(rc) && (NULL != piSupportSpec))
              {
              spAlias = piSupportSpec;
              if(NULL_var != spAlias)
                {
                double ValLength = 0.;
                double ValAngle  = 0.;
                double ValApprox = 0.;

                CATICkeParm * piLengthParm = NULL;

                rc = piStmFlangeSurf -> GetSupportLength (&piLengthParm);
            
                if(SUCCEEDED(rc) && (NULL != piLengthParm))
                  {
                  spStored = piLengthParm;
                  if(NULL_var != spStored) ValLength = spStored -> ValueStored();

                  piLengthParm -> Release();
                  piLengthParm = NULL;
                  }

                if(SUCCEEDED(rc))
                  {
                  if(SupportType == "Angle")
                    {
                    CATICkeParm * piAngleParm = NULL;
                    
                    rc = piStmFlangeSurf -> GetSupportAngle (&piAngleParm);
                                    
                    if(SUCCEEDED(rc) && (NULL != piAngleParm))
                      {
                      spStored = piAngleParm;
                      if(NULL_var != spStored) ValLength = spStored -> ValueStored();

                      piAngleParm -> Release();
                      piAngleParm = NULL;
                      }
                    }
                  }
                
                if(SUCCEEDED(rc))
                  {
                  if(SupportType == "Approximation")
                    {
                    CATICkeParm * piApproxParm = NULL;
                    
                    rc = piStmFlangeSurf -> GetSupportApproxLength (&piApproxParm);
                                    
                    if(SUCCEEDED(rc) && (NULL != piApproxParm))
                      {
                      spStored = piApproxParm;
                      if(NULL_var != spStored) ValApprox = spStored -> ValueStored();

                      piApproxParm -> Release();
                      piApproxParm = NULL;
                      }
                    }
                  }

                                
                if(SUCCEEDED(rc))
                  {
                  Name = spAlias -> GetAlias();
                
                  cout << endl;
                  cout << " Support : Type     : " << SupportType.ConvertToChar() << endl;
                  cout << endl;
                  cout << "           Geometry : " << Name.ConvertToChar() << endl;
                  cout << endl;
                  cout << "           Length   : " << ValLength << " " << LengthUnitName.ConvertToChar() << endl;
                  if(SupportType == "Angle")
                    {
                    cout << endl;
                    cout << "           Angle    : " << ValAngle << " " << AngleUnitName.ConvertToChar() << endl;
                    }
                  if(SupportType == "Approximation")
                    {
                    cout << endl;
                    cout << "           Approx Length : " << ValApprox << " " << LengthUnitName.ConvertToChar() << endl;
                    }
                  cout << endl;
                  }
                }
              piSupportSpec -> Release();
              piSupportSpec = NULL;
              }
            }
          }
        
        if(SUCCEEDED(rc))
          {
          // EOP :
          CATUnicodeString EOPType("");

          rc = piStmFlangeSurf -> GetEOPType (EOPType);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " Edge of Part : Type   : " << EOPType.ConvertToChar() << endl;
            cout << endl;
    
            if(EOPType == "Length From OML")
              {
              CATICkeParm * piLengthParm = NULL;

              rc = piStmFlangeSurf -> GetEOPLength (&piLengthParm);
            
              if(SUCCEEDED(rc) && (NULL != piLengthParm))
                {
                spStored = piLengthParm;
                if(NULL_var != spStored) Val = spStored -> ValueStored();

                cout << "                Value  : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
                cout << endl;
                
                piLengthParm -> Release();
                piLengthParm = NULL;
                }
              }
            else
              {
              CATLISTP(CATISpecObject) LimitsSpecList;

              rc = piStmFlangeSurf -> GetEOPElements (LimitsSpecList);

              if(SUCCEEDED(rc))
                {
                cout << endl;
                cout << " Element(s) : " << endl;
                cout << endl;
          
                CATISpecObject * piLimitSpec = NULL;

                for(int i = 1; i <= LimitsSpecList.Size(); i++)
                  {
                  piLimitSpec = LimitsSpecList[i];
                  if(NULL != piLimitSpec)
                    {
                    spAlias = piLimitSpec;
                    if(NULL_var != spAlias)
                      {
                      Name = spAlias -> GetAlias();
                
                      cout << "   - " << Name.ConvertToChar() << endl;
                      }
                    piLimitSpec -> Release();
                    piLimitSpec = NULL;
                    }
                  }
                cout << endl;
                }
              }
            }
          }
      
        if(SUCCEEDED(rc))
          {
          // Base Feature Orientation :
          CATOrientation BaseFeatureOrient;

          rc = piStmFlangeSurf -> GetBaseFeatureOrient (BaseFeatureOrient);

          if(SUCCEEDED(rc))
            {
            if(BaseFeatureOrient == CATOrientationPositive)
              {
              cout << endl;
              cout << " Base Feature orientation : Positive" << endl;
              cout << endl;
              }
            else if(BaseFeatureOrient == CATOrientationNegative)
              {
              cout << endl;
              cout << " Base Feature orientation : Negative" << endl;
              cout << endl;
              }
            }
          } 
        
        if(SUCCEEDED(rc))
          {
          // Flange Orientation :
          CATOrientation FlangeOrient;

          rc = piStmFlangeSurf -> GetFlangeOrient (FlangeOrient);

          if(SUCCEEDED(rc))
            {
            if(FlangeOrient == CATOrientationPositive)
              {
              cout << endl;
              cout << " Flange orientation : Positive" << endl;
              cout << endl;
              }
            else if(FlangeOrient == CATOrientationNegative)
              {
              cout << endl;
              cout << " Flange orientation : Negative" << endl;
              cout << endl;
              }
            }
          } 

        if(SUCCEEDED(rc))
          {
          // Material Orientation :
          CATOrientation MaterialOrient;

          rc = piStmFlangeSurf -> GetMaterialOrient (MaterialOrient);

          if(SUCCEEDED(rc))
            {
            if(MaterialOrient == CATOrientationPositive)
              {
              cout << endl;
              cout << " Material orientation : Positive" << endl;
              cout << endl;
              }
            else if(MaterialOrient == CATOrientationNegative)
              {
              cout << endl;
              cout << " Material orientation : Negative" << endl;
              cout << endl;
              }
            }
          } 

        if(SUCCEEDED(rc))
          {
          // Side 1
          CATUnicodeString Side1Type("");

          rc = piStmFlangeSurf -> GetSide1Type (Side1Type);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " Side 1 : "  << endl;
            cout << endl;
            cout << "          Type : " << Side1Type.ConvertToChar() << endl;
            cout << endl;

            if((Side1Type == "Element FD") || (Side1Type == "Element FP"))
              {
              CATLISTP(CATISpecObject) LimitsSpecList;

              rc = piStmFlangeSurf -> GetSide1Elements (LimitsSpecList);

              if(SUCCEEDED(rc))
                {
                cout << endl;
                cout << "          Element(s) : " << endl;
                cout << endl;
          
                CATISpecObject * piLimitSpec = NULL;

                for(int i = 1; i <= LimitsSpecList.Size(); i++)
                  {
                  piLimitSpec = LimitsSpecList[i];
                  if(NULL != piLimitSpec)
                    {
                    spAlias = piLimitSpec;
                    if(NULL_var != spAlias)
                      {
                      Name = spAlias -> GetAlias();

                      cout << "               - " << Name.ConvertToChar() << endl;
                      }
                    piLimitSpec -> Release();
                    piLimitSpec = NULL;
                    }
                  }
                cout << endl;
                }
              }
          
            CATUnicodeString DressUpType("");

            rc = piStmFlangeSurf -> GetSide1DressUpType (DressUpType);

            if(SUCCEEDED(rc))
              {
              if(DressUpType == "Corner")
                {
                CATICkeParm * piCornerRadiusParm = NULL;

                rc = piStmFlangeSurf -> GetSide1CornerRadius (&piCornerRadiusParm);
            
                if(SUCCEEDED(rc) && (NULL != piCornerRadiusParm))
                  {
                  spStored = piCornerRadiusParm;
                  if(NULL_var != spStored) Val = spStored -> ValueStored();
              
                  cout << endl;
                  cout << "          Corner : Radius : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
                  cout << endl;
                  
                  piCornerRadiusParm -> Release();
                  piCornerRadiusParm = NULL;
                  }
                }
              }
            
            CATUnicodeString CompensationType("");

            rc = piStmFlangeSurf -> GetSide1CompensationType (CompensationType);

            if(SUCCEEDED(rc))
              {
              if(CompensationType != "None")
                {
                cout << endl;
                cout << "          Compensation : Type  : " << CompensationType.ConvertToChar() << endl;
                cout << endl;

                if(CompensationType == "Angle")
                  {
                  rc = piStmFlangeSurf -> GetSide1CompensationValue (Val);

                  if(SUCCEEDED(rc))
                    {
                    cout << "                         Value : " << Val << " " << AngleUnitName.ConvertToChar() << endl;
                    cout << endl;
                    }
                  }
                else if(CompensationType == "Length")
                  {
                  rc = piStmFlangeSurf -> GetSide1CompensationValue (Val);

                  if(SUCCEEDED(rc))
                    {
                    cout << "                         Value : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
                    cout << endl;
                    }
                  }
                }
              }
            }
          }

        if(SUCCEEDED(rc))
          {
          // Side 2
          CATUnicodeString Side2Type("");

          rc = piStmFlangeSurf -> GetSide2Type (Side2Type);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " Side 2 : "  << endl;
            cout << endl;
            cout << "          Type : " << Side2Type.ConvertToChar() << endl;
            cout << endl;

            if((Side2Type == "Element FD") || (Side2Type == "Element FP"))
              {
              CATLISTP(CATISpecObject) LimitsSpecList;

              rc = piStmFlangeSurf -> GetSide2Elements (LimitsSpecList);

              if(SUCCEEDED(rc))
                {
                cout << endl;
                cout << "          Element(s) : " << endl;
                cout << endl;
          
                CATISpecObject * piLimitSpec = NULL;

                for(int i = 1; i <= LimitsSpecList.Size(); i++)
                  {
                  piLimitSpec = LimitsSpecList[i];
                  if(NULL != piLimitSpec)
                    {
                    spAlias = piLimitSpec;
                    if(NULL_var != spAlias)
                      {
                      Name = spAlias -> GetAlias();

                      cout << "               - " << Name.ConvertToChar() << endl;
                      }
                    piLimitSpec -> Release();
                    piLimitSpec = NULL;
                    }
                  }
                cout << endl;
                }
              }
          
            CATUnicodeString DressUpType("");

            rc = piStmFlangeSurf -> GetSide2DressUpType (DressUpType);

            if(SUCCEEDED(rc))
              {
              if(DressUpType == "Corner")
                {
                CATICkeParm * piCornerRadiusParm = NULL;

                rc = piStmFlangeSurf -> GetSide2CornerRadius (&piCornerRadiusParm);
            
                if(SUCCEEDED(rc) && (NULL != piCornerRadiusParm))
                  {
                  spStored = piCornerRadiusParm;
                  if(NULL_var != spStored) Val = spStored -> ValueStored();
              
                  cout << endl;
                  cout << "          Corner : Radius : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
                  cout << endl;
                  
                  piCornerRadiusParm -> Release();
                  piCornerRadiusParm = NULL;
                  }
                }
              }
            
            CATUnicodeString CompensationType("");

            rc = piStmFlangeSurf -> GetSide2CompensationType (CompensationType);

            if(SUCCEEDED(rc))
              {
              if(CompensationType != "None")
                {
                cout << endl;
                cout << "          Compensation : Type  : " << CompensationType.ConvertToChar() << endl;
                cout << endl;

                if(CompensationType == "Angle")
                  {
                  rc = piStmFlangeSurf -> GetSide2CompensationValue (Val);

                  if(SUCCEEDED(rc))
                    {
                    cout << "                         Value : " << Val << " " << AngleUnitName.ConvertToChar() << endl;
                    cout << endl;
                    }
                  }
                else if(CompensationType == "Length")
                  {
                  rc = piStmFlangeSurf -> GetSide2CompensationValue (Val);

                  if(SUCCEEDED(rc))
                    {
                    cout << "                         Value : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
                    cout << endl;
                    }
                  }
                }
              }
            }
          }

        if(SUCCEEDED(rc))
          {
          // K_Factor :
          CATICkeParm * piKFactorParm = NULL;
                    
          rc = piStmFlangeSurf -> GetKFactor (&piKFactorParm);
                                    
          if(SUCCEEDED(rc) && (NULL != piKFactorParm))
            {
            spStored = piKFactorParm;
            if(NULL_var != spStored) Val = spStored -> ValueStored();
              
            cout << endl;
            cout << " K_Factor : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
            cout << endl;
        
            piKFactorParm -> Release();
            piKFactorParm = NULL;
            }
          }

        if(SUCCEEDED(rc))
          {
          // Manufacturing Process :
          CATUnicodeString ManufProcType("");

          rc = piStmFlangeSurf -> GetManufacturingProcessType (ManufProcType);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " Manufacturing Process : " << ManufProcType.ConvertToChar() << endl;
            cout << endl;
            }
          }
        
        if(SUCCEEDED(rc))
          {
          // Joggles :
          CATLISTP(CATISpecObject) ListJoggleSpecs;

          rc = piStmFlangeSurf -> GetJoggles (ListJoggleSpecs);

          if(SUCCEEDED(rc))
            {
            int NbJoggles = ListJoggleSpecs.Size();
            if(NbJoggles > 0)
              {
              cout << endl;
              cout << " Joggle(s) : " << endl;
              cout << endl;

              CATISpecObject * piJoggleSpec = NULL;

              for(int i = 1; i <= NbJoggles; i++)
                {
                piJoggleSpec = ListJoggleSpecs[i];
                if(NULL != piJoggleSpec)
                  {
                  spAlias = piJoggleSpec;
                  if(NULL_var != spAlias)
                    {
                    Name = spAlias -> GetAlias();

                    cout << "    - " << Name.ConvertToChar() << endl;
                    }
                  piJoggleSpec -> Release();
                  piJoggleSpec = NULL;
                  }
                }
              }
            }
          }
        
        if(SUCCEEDED(rc))
          {
          // Joggle Compensation :
          CATUnicodeString CompJoggleType("");

          rc = piStmFlangeSurf -> GetJoggleCompensation (CompJoggleType);

          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " Joggle Compensation : " << CompJoggleType.ConvertToChar() << endl;
            cout << endl;
            }
          }
              
        // Characteristic Curves :
        CATIStmCharacteristicCurves * piStmCharacteristicCurves = NULL;

        rc = ipiSpec -> QueryInterface (IID_CATIStmCharacteristicCurves, (void **)& piStmCharacteristicCurves);
    
        if(SUCCEEDED(rc))
          {
          CATUnicodeString          ViewTypeFolded("MfDefault3DView");
          CATListOfCATUnicodeString ListFoldedCurves;

          rc = piStmCharacteristicCurves -> GetAvailableCharacteristicCurveTypes (ViewTypeFolded, ListFoldedCurves);
        
          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " Available Characteristic Curves : Folded view : " << endl;
            cout << endl;
            for(int i = 1; i <= ListFoldedCurves.Size(); i++)
              {
              cout << " - " << ListFoldedCurves[i].ConvertToChar() << endl;
              }
            cout << endl;
            }
          
          CATUnicodeString          ViewTypeUnfolded("MfUnfoldedView");
          CATListOfCATUnicodeString ListUnfoldedCurves;

          rc = piStmCharacteristicCurves -> GetAvailableCharacteristicCurveTypes (ViewTypeUnfolded, ListUnfoldedCurves);
        
          if(SUCCEEDED(rc))
            {
            cout << endl;
            cout << " Available Characteristic Curves : Unfolded view : " << endl;
            cout << endl;
            for(int i = 1; i <= ListUnfoldedCurves.Size(); i++)
              {
              cout << " - " << ListUnfoldedCurves[i].ConvertToChar() << endl;
              }
            cout << endl;
            }
          
          piStmCharacteristicCurves -> Release();
          piStmCharacteristicCurves = NULL;
          }
        }
      else
        {
        rc = ipiSpec -> QueryInterface(IID_CATIStmJoggle, (void **)& piStmJoggle);
    
        if(NULL != piStmJoggle)
          {
          cout << endl;
          cout << endl;
          cout << " ================= " << endl;
          cout << "  Joggle entries : " << endl;
          cout << " ================= " << endl;
          cout << endl;
          cout << endl;
          spAlias = ipiSpec;
          if(NULL_var != spAlias)
            {
            Name = spAlias -> GetAlias();
        
            cout << " Joggle Name : " << Name.ConvertToChar() << endl;
            cout << endl;
            }
          else
            rc = E_FAIL;

          if(SUCCEEDED(rc))
            {
            // Support :
            CATISpecObject * piSupportSpec = NULL;

            rc = piStmJoggle -> GetSupport (&piSupportSpec);
      
            if(SUCCEEDED(rc) && (NULL != piSupportSpec))
              {
              spAlias = piSupportSpec;
              if(NULL_var != spAlias)
                {
                Name = spAlias -> GetAlias();
                
                cout << endl;
                cout << " Support  : " << Name.ConvertToChar() << endl;
                cout << endl;
                }
              piSupportSpec -> Release();
              piSupportSpec = NULL;
              }
            }

          if(SUCCEEDED(rc))
            {
            // Plane :
            CATISpecObject * piPlaneSpec = NULL;

            rc = piStmJoggle -> GetPlane (&piPlaneSpec);
      
            if(SUCCEEDED(rc) && (NULL != piPlaneSpec))
              {
              spAlias = piPlaneSpec;
              if(NULL_var != spAlias)
                {
                Name = spAlias -> GetAlias();
                
                cout << endl;
                cout << " Plane    : " << Name.ConvertToChar() << endl;
                cout << endl;
                }
              piPlaneSpec -> Release();
              piPlaneSpec = NULL;
              }
            }

          if(SUCCEEDED(rc))
            {
            // Depth :
            CATICkeParm * piDepthParm = NULL;
                    
            rc = piStmJoggle -> GetDepth (&piDepthParm);
                                    
            if(SUCCEEDED(rc) && (NULL != piDepthParm))
              {
              spStored = piDepthParm;
              if(NULL_var != spStored) Val = spStored -> ValueStored();
              
              cout << endl;
              cout << " Depth    : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
              cout << endl;
        
              piDepthParm -> Release();
              piDepthParm = NULL;
              }
            }
        
          if(SUCCEEDED(rc))
            {
            // Depth Orientation :
            CATOrientation DepthOrient;

            rc = piStmJoggle -> GetDepthOrient (DepthOrient);

            if(SUCCEEDED(rc))
              {
              if(DepthOrient == CATOrientationPositive)
                {
                cout << endl;
                cout << " Depth orientation : Positive" << endl;
                cout << endl;
                }
              else if(DepthOrient == CATOrientationNegative)
                {
                cout << endl;
                cout << " Depth orientation : Negative" << endl;
                cout << endl;
                }
              }
            } 

          if(SUCCEEDED(rc))
            {
            // Runout :
            CATICkeParm * piRunoutParm = NULL;
                    
            rc = piStmJoggle -> GetRunout (&piRunoutParm);
                                    
            if(SUCCEEDED(rc) && (NULL != piRunoutParm))
              {
              spStored = piRunoutParm;
              if(NULL_var != spStored) Val = spStored -> ValueStored();
              
              cout << endl;
              cout << " Runout   : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
              cout << endl;
        
              piRunoutParm -> Release();
              piRunoutParm = NULL;
              }
            }
          
          if(SUCCEEDED(rc))
            {
            // Runout Orientation :
            CATOrientation RunoutOrient;

            rc = piStmJoggle -> GetRunoutOrient (RunoutOrient);

            if(SUCCEEDED(rc))
              {
              if(RunoutOrient == CATOrientationPositive)
                {
                cout << endl;
                cout << " Runout orientation : Positive" << endl;
                cout << endl;
                }
              else if(RunoutOrient == CATOrientationNegative)
                {
                cout << endl;
                cout << " Runout orientation : Negative" << endl;
                cout << endl;
                }
              }
            } 
           
          if(SUCCEEDED(rc))
            {         
            // Start Radius :
            CATICkeParm * piStartRadiusParm = NULL;
                    
            rc = piStmJoggle -> GetStartRadius (&piStartRadiusParm);
                                    
            if(SUCCEEDED(rc) && (NULL != piStartRadiusParm))
              {
              spStored = piStartRadiusParm;
              if(NULL_var != spStored) Val = spStored -> ValueStored();
              
              cout << endl;
              cout << " Start Radius : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
              cout << endl;
        
              piStartRadiusParm -> Release();
              piStartRadiusParm = NULL;
              }
            }

          if(SUCCEEDED(rc))
            {         
            // End Radius :
            CATICkeParm * piEndRadiusParm = NULL;
                    
            rc = piStmJoggle -> GetEndRadius (&piEndRadiusParm);
                                    
            if(SUCCEEDED(rc) && (NULL != piEndRadiusParm))
              {
              spStored = piEndRadiusParm;
              if(NULL_var != spStored) Val = spStored -> ValueStored();
              
              cout << endl;
              cout << " End Radius   : " << Val << " " << LengthUnitName.ConvertToChar() << endl;
              cout << endl;
        
              piEndRadiusParm -> Release();
              piEndRadiusParm = NULL;
              }
            }
          }
        else
          {
          cout << endl;
          cout << "(Display) ERROR : invalid Feature Type." << endl;
          cout << endl;
          }
        }
      }
    
    if(NULL != piStmWeb)
      {
      piStmWeb -> Release();
      piStmWeb = NULL;
      }
    if(NULL != piStmFlangeSurf)
      {
      piStmFlangeSurf -> Release();
      piStmFlangeSurf = NULL;
      }
    if(NULL != piStmJoggle)
      {
      piStmJoggle -> Release();
      piStmJoggle = NULL;
      }

    rc = S_OK;
    }
  else
    {
    cout << endl;
    cout << "(Display) ERROR : the Feature to display is NULL." << endl;
    cout << endl;
    }

  return rc;
  }






