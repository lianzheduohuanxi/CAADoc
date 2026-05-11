// COPYRIGHT Dassault Systemes 2007

#include <CATDialog.h>
#include <CATUnicodeString.h>
#include <CATListOfCATUnicodeString.h>
#include <CATListOfCATBaseUnknown.h>
#include <CATString.h>
#include <CATDlgTableView.h>

#include <SampleVariantModel.h>
#include <SampleRow.h>

#define NO_TRACES_FILL

#ifdef TRACES_FILL
#include <iostream.h>
#endif

#include <CATDlgFrame.h>
extern CATDlgFrame *SampleFrameButtons;

#include  <TIE_CATIDlgTableViewModel.h>
TIE_CATIDlgTableViewModel(SampleVariantModel);

CATImplementClass(SampleVariantModel,
                  Implementation,
                  CATExtIDlgTableViewModel,
                  CATNull );

SampleVariantModel::SampleVariantModel():CATExtIDlgTableViewModel()
{
}

SampleVariantModel::~SampleVariantModel()
{
}

HRESULT SampleVariantModel::GetUpdateEvent(CATCallbackEvent * oUpdateEvent)
{
  return S_OK;
}

HRESULT SampleVariantModel::GetEventPublisher(CATBaseUnknown ** oTableModelEventPublisher)
{
  return S_OK;
}

HRESULT SampleVariantModel::GetLabel(CATBaseUnknown_var &iLine, const CATString &iColumnID, CATUnicodeString &oLabel)
{
  // SCA : column name format : VC.... with .... 0001 -> 1000
  int ColIndex = 0;
  char *colName = (char*)iColumnID.ConvertToChar();
  sscanf(colName+2,"%d", &ColIndex);

#ifdef TRACES_FILL
  cout << "SampleVariantModel::GetLabel(" << iLine << ", " << iColumnID << ", " << ColIndex << ")" << endl;
#endif

  oLabel = "VC ?";

  SampleRow *pRow= GetSampleRow(iLine);
  if (!pRow)
    return E_FAIL;

  if (pRow && pRow->Size() >= ColIndex && ColIndex >= 1)
    oLabel = pRow->_datas[ColIndex];

  //if (SampleFrameButtons && (ColIndex == 1 || ColIndex == 3 || ColIndex == 5 || ColIndex == 7))
  //  oLabel = SampleFrameButtons->GetTitle();

  return S_OK;
}

HRESULT SampleVariantModel::SetLabel(CATBaseUnknown_var &iLine, const CATString &iColumnID, const CATUnicodeString &iLabel)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::SetLabel - Column ID = " << iColumnID << endl;
  cout << "SampleVariantModel::SetLabel - Label     = " << iLabel.ConvertToChar() << endl;
#endif

  //Replace, in the row, the new value of the data
  int ColIndex = 0;
  char *colName = (char*)iColumnID.ConvertToChar();
  sscanf(colName+2,"%d", &ColIndex);

  SampleRow *pRow= GetSampleRow(iLine);
  if (pRow && pRow->Size() >= ColIndex && ColIndex >= 1)
    pRow->_datas[ColIndex] = iLabel;

  return S_OK;
}

HRESULT SampleVariantModel::IsEditable(CATBaseUnknown_var& iLine, const CATString& iColumnID, CATBoolean & oEditable)
{
  oEditable = TRUE;
  return S_OK;
}

HRESULT SampleVariantModel::GetIcon(CATBaseUnknown_var iLine, const CATString &iColumnID, CATUnicodeString & oIcon)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::GetIcon(" << iLine << ", " << iColumnID << ")" << endl;
#endif

  CATUnicodeString foo("");
#ifdef TRACES_FILL
  cout << " = ''" << endl;
#endif

  oIcon = foo;

  return S_OK;
}

HRESULT SampleVariantModel::GetStyle(CATBaseUnknown_var iLine, const CATString &iColumnID, CATDlgTableStyle &oStyle)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::GetStyle(" << iLine << ", " << iColumnID << ")" << endl;
#endif
  oStyle = CATDlgTableCellNormal | CATDlgTableCenterJustify;
  int ColIndex = 0;
  char *colName = (char*)iColumnID.ConvertToChar();
  sscanf(colName+2,"%d", &ColIndex);
  if (ColIndex % 2 == 0)
        oStyle = CATDlgTableCellCustom | CATDlgTableCenterJustify;
  if (iColumnID == "VC3")
        oStyle = CATDlgTableCellCustom;
  return S_OK;
}

HRESULT SampleVariantModel::GetLineCount(int & oLineCount)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::GetLineCount() = " << _SampleRows.Size() << endl;
#endif
  oLineCount = _SampleRows.Size();
  return S_OK;
}

HRESULT SampleVariantModel::GetLines(int iStart, int iCount, CATListOfCATBaseUnknown_var &oNodes)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::GetLines(" << iStart << ", " << iCount << ")" << endl;
#endif
  oNodes.RemoveAll();

  for (int i=0; i<iCount; i++)
  {
#ifdef TRACES_FILL
  cout << "  _SampleRows[" << i+iStart+1 << "] = " << _SampleRows[i+iStart+1] << endl;
#endif
     oNodes.Append(_SampleRows[i+iStart+1]);
  }
  return S_OK;
}

HRESULT SampleVariantModel::GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  CATDlgTableStyle cellStyle = iStyle & (CATDlgTableCellOK | CATDlgTableCellNormal | CATDlgTableCellWarning | CATDlgTableCellError | CATDlgTableCellCustom);
  switch (cellStyle)
  {
    case CATDlgTableCellOK:
        ioRed = 0;
        ioGreen = 127;
        ioBlue = 0;
        ioAlpha = 255;
    break;
    case CATDlgTableCellNormal:
        ioRed = 0;
        ioGreen = 127;
        ioBlue = 0;
        ioAlpha = 255;
    break;
    case CATDlgTableCellWarning:
        ioRed = 127;
        ioGreen = 127;
        ioBlue = 0;
        ioAlpha = 255;
    break;
    case CATDlgTableCellError:
        ioRed = 127;
        ioGreen = 0;
        ioBlue = 0;
        ioAlpha = 255;
    break;
    // SCA : Customisation sur les colonnes paires
    case CATDlgTableCellCustom:
        ioRed = 0;
        ioGreen = 127;
        ioBlue = 127;
        ioAlpha = 255;
    break;
    default:
        ioRed = 0;
        ioGreen = 0;
        ioBlue = 0;
        ioAlpha = 255;
    break;
  }

  return S_OK;
}

HRESULT SampleVariantModel::GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  CATDlgTableStyle cellStyle = iStyle & (CATDlgTableCellOK | CATDlgTableCellNormal | CATDlgTableCellWarning | CATDlgTableCellError | CATDlgTableCellCustom);
  switch (cellStyle)
  {
    case CATDlgTableCellOK:
        ioRed = 127;
        ioGreen = 0;
        ioBlue = 0;
        ioAlpha = 255;
    break;
    case CATDlgTableCellNormal:
        ioRed = 0;
        ioGreen = 0;
        ioBlue = 0;
        ioAlpha = 255;
    break;
    case CATDlgTableCellWarning:
        ioRed = 0;
        ioGreen = 127;
        ioBlue = 127;
        ioAlpha = 255;
    break;
    case CATDlgTableCellError:
        ioRed = 0;
        ioGreen = 0;
        ioBlue = 127;
        ioAlpha = 255;
    break;
    case CATDlgTableCellCustom:
        ioRed = 50;
        ioGreen = 50;
        ioBlue = 0;
        ioAlpha = 50;
    break;
    default:
        ioRed = 0;
        ioGreen = 0;
        ioBlue = 0;
        ioAlpha = 255;
    break;
  }

  return S_OK;
}

HRESULT SampleVariantModel::GetBorderColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  return E_FAIL;
}

HRESULT SampleVariantModel::GetTextColor(CATBaseUnknown_var iLine, const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  if (iColumnID == "VC3")
  {
    ioRed = 0;
    ioGreen = 255;
    ioBlue = 0;
    ioAlpha = 255;
    return S_OK;
  }

  return E_FAIL;
}

HRESULT SampleVariantModel::GetBackgroundColor(CATBaseUnknown_var iLine , const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  if (iColumnID == "VC3")
  {
    ioRed = 0;
    ioGreen = 0;
    ioBlue = 127;
    ioAlpha = 255;
    return S_OK;
  }

  return E_FAIL;
}

void SampleVariantModel::Sort(const CATString &iColumnID, int iReverse)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::Sort(" << iColumnID << ", " << iReverse << ")" << endl;
#endif
}

void SampleVariantModel::HighlightColumn(const CATString &iColumnID)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::HighlightColumn(" << iColumnID << ")" << endl;
#endif
}

void SampleVariantModel::FillTheColumns(int iNbRows, int iNbVars)
{
#ifdef TRACES_FILL
  cout << "SampleVariantModel::FillTheColumns(" << iNbRows << ", " << iNbVars << ")" << endl;
#endif
  if (iNbRows <= 0 || _SampleRows.Size() > 0) return;

  CATListOfCATUnicodeString aRow(iNbVars);
  CATUnicodeString row;
  CATUnicodeString col;

  // SCA : C'est evolutif ;-)
  SampleRow **tabrows = new SampleRow *[iNbRows];
  for (int i=0; i<iNbRows; i++)
  {
    tabrows[i] = new SampleRow(i);
    aRow.RemoveAll();
    for (int j=0; j<iNbVars; j++)
    {
      row.BuildFromNum(i);
      col.BuildFromNum(j);
      // VCj
      aRow.Append(row+"VC"+col);
    }
    tabrows[i]->SetDatas(aRow);
    _SampleRows.Append(tabrows[i]);
  }

  // SCA : MLK
  delete [] tabrows;
  tabrows = NULL;

#ifdef TRACES_FILL
  cout << "  number of lines = _SampleRows.Size() = " << _SampleRows.Size() << endl;
#endif
}

SampleRow *SampleVariantModel::GetSampleRow(CATBaseUnknown_var iNode)
{
   CATBaseUnknown *ptr= (CATBaseUnknown*)iNode;
   if (ptr && ptr->IsAKindOf(SampleRow::ClassName()))
      return (SampleRow*)ptr;
   return NULL;
}

int SampleVariantModel::GetRowId(CATBaseUnknown_var iLine)
{
  SampleRow *pRow = GetSampleRow(iLine);
  if (!pRow)
    return -1;
  return pRow->_id;
}


