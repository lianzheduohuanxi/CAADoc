// COPYRIGHT Dassault Systemes 2007

#include <CATDialog.h>
#include <CATUnicodeString.h>
#include <CATListOfCATUnicodeString.h>
#include <CATListOfCATBaseUnknown.h>
#include <CATString.h>

#include <CATIDlgTableViewModel.h>

#include <SampleViewModel.h>
#include <SampleRow.h>

#define NO_TRACES_FILL

#ifdef TRACES_FILL
#include <iostream.h>
#endif

#include  <TIE_CATIDlgTableViewModel.h>  
TIE_CATIDlgTableViewModel(SampleViewModel);  

CATImplementClass(SampleViewModel,
                  Implementation,
                  CATExtIDlgTableViewModel,
                  CATNull );

SampleViewModel::SampleViewModel():CATExtIDlgTableViewModel()
{
}

SampleViewModel::~SampleViewModel()
{
}

HRESULT SampleViewModel::GetUpdateEvent(CATCallbackEvent * oUpdateEvent)
{
  return S_OK;
}

HRESULT SampleViewModel::GetEventPublisher(CATBaseUnknown ** oTableModelEventPublisher)
{
  return S_OK;
}

HRESULT SampleViewModel::GetLabel(CATBaseUnknown_var &iLine, const CATString &iColumnID, CATUnicodeString &oLabel)
{
  oLabel = "";

  // SCA : Column with icon
  if (iColumnID == "Col02")
    return S_OK;

  oLabel = "ERR";

  // SCA : column name format : Col.. with .. 01 -> 10
  int ColIndex = -1;
  char *colName = (char*)iColumnID.ConvertToChar();
  sscanf(colName+3, "%d", &ColIndex);

  SampleRow *pRow= GetSampleRow(iLine);
  if (!pRow)
    return E_FAIL;

#ifdef TRACES_FILL
cout << "SampleViewModel::GetLabel(" << iLine << ", " << iColumnID
     << ", " << ColIndex << ", " << pRow->Size() << ")" << endl;
#endif

if (pRow && pRow->Size() >= 1 && pRow->Size() >= ColIndex && ColIndex >= 1)
    oLabel = pRow->_datas[ColIndex];

#ifdef TRACES_FILL
  cout << "SampleViewModel::GetLabel - Label     = " << oLabel.ConvertToChar() << endl;
#endif

  return S_OK;
}

HRESULT SampleViewModel::SetLabel(CATBaseUnknown_var &iLine, const CATString &iColumnID, const CATUnicodeString &iLabel)
{
#ifdef TRACES_FILL
  cout << "SampleViewModel::SetLabel - Column ID = " << iColumnID << endl;
  cout << "SampleViewModel::SetLabel - Label     = " << iLabel.ConvertToChar() << endl;
#endif

  return S_OK;
}

/*
HRESULT SampleViewModel::IsEditable(CATBaseUnknown_var &iLine, const CATString &iColumnID, CATBoolean &oEditable)
{
  oEditable = FALSE;
  return S_OK;
}*/

HRESULT SampleViewModel::GetIcon(CATBaseUnknown_var iLine, const CATString &iColumnID, CATUnicodeString & oIcon)
{
#ifdef TRACES_FILL
  cout << "SampleViewModel::GetIcon(" << iLine << ", " << iColumnID << ")" << endl;
#endif

  CATUnicodeString foo("");
#ifdef TRACES_FILL
  cout << " = ''" << endl;
#endif

  oIcon = foo;

  return S_OK;
}

HRESULT SampleViewModel::GetStyle(CATBaseUnknown_var iLine, const CATString &iColumnID, CATDlgTableStyle &oStyle)
{
#ifdef TRACES_FILL
cout << "SampleViewModel::GetStyle(" << iLine << ", " << iColumnID << ")" << endl;
#endif
  oStyle = CATDlgTableCellNormal | CATDlgTableLeftJustify;

  SampleRow *pRow= GetSampleRow(iLine);
  if (!pRow)
    return E_FAIL;

  if (iColumnID.Compare("Col01") == 0)
  {
    oStyle = CATDlgTableRightJustify|CATDlgTableCellWarning;
    return S_OK;
  }

  CATUnicodeString oLabel;
  GetLabel(iLine, iColumnID, oLabel);

  if (oLabel == "")
  {
    oStyle = CATDlgTableCellError;
    return S_OK;
  }

  if (oLabel == "?")
  {
    oStyle = CATDlgTableCenterJustify|CATDlgTableCellWarning;
    return S_OK;
  }

  return S_OK;
}

HRESULT SampleViewModel::GetLineCount(int & oLineCount)
{
#ifdef TRACES_FILL
  cout << "SampleViewModel::GetLineCount() = " << _SampleRows.Size() << endl;
#endif
  oLineCount = _SampleRows.Size();
  return S_OK;
}

HRESULT SampleViewModel::GetLines(int iStart, int iCount, CATListOfCATBaseUnknown_var &oNodes)
{
#ifdef TRACES_FILL
  cout << "SampleViewModel::GetLines(" << iStart << ", " << iCount << ")" << endl;
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

HRESULT SampleViewModel::GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
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
    case CATDlgTableCellCustom:
        ioRed = 0;
        ioGreen = 127;
        ioBlue = 0;
        ioAlpha = 255;
    break;
    default:
        ioRed = 0;
        ioGreen = 0;
        ioBlue = 127;
        ioAlpha = 255;
    break;
  }

  return S_OK;
}

HRESULT SampleViewModel::GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
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

HRESULT SampleViewModel::GetBorderColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  return E_FAIL;
}

HRESULT SampleViewModel::GetTextColor(CATBaseUnknown_var iLine, const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  if (iColumnID == "Col01" && (GetRowId(iLine) >= 3 && GetRowId(iLine) <= 8) )
  {
    ioRed = 0;
    ioGreen = 255;
    ioBlue = 0;
    ioAlpha = 255;
    return S_OK;
  }

  return E_FAIL;
}

HRESULT SampleViewModel::GetBackgroundColor(CATBaseUnknown_var iLine , const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  if (iColumnID == "Col01" && (GetRowId(iLine) >= 3 && GetRowId(iLine) <= 8) )
  {
    ioRed = 0;
    ioGreen = 0;
    ioBlue = 127;
    ioAlpha = 255;
    return S_OK;
  }

  return E_FAIL;
}

void SampleViewModel::Sort(const CATString &iColumnID, int iReverse)
{
#ifdef TRACES_FILL
  cout << "SampleViewModel::Sort(" << iColumnID << ", " << iReverse << ")" << endl;
#endif
}

void SampleViewModel::HighlightColumn(const CATString &iColumnID)
{
#ifdef TRACES_FILL
  cout << "SampleViewModel::HighlightColumn(" << iColumnID << ")" << endl;
#endif
}

void SampleViewModel::FillTheColumns(int iNbRows)
{
#ifdef TRACES_FILL
cout << "SampleViewModel::FillTheColumns(" << iNbRows << ")" << endl;
#endif
  if (iNbRows <= 0 || _SampleRows.Size() > 0) return;

  CATListOfCATUnicodeString aRow(10);
  CATUnicodeString foo;
  CATString label;

  CATUnicodeString LockedByMe("I_TreePlusMaxi");

  // SCA : C'est evolutif ;-)
  SampleRow **tabrows = new SampleRow *[iNbRows];
  for (int i=0; i<iNbRows; i++)
  {
    char buf[16];
    sprintf(&buf[0], "%d", i);
    buf[strlen(&buf[0])] = '\0';

    tabrows[i] = new SampleRow(i);
    aRow.RemoveAll();

    // Oper
    label = CATString(buf);
    aRow.Append(CATUnicodeString(label));
    // +
    aRow.Append(LockedByMe);
    // Level
    label = "Level " + CATString(buf);
    aRow.Append(CATUnicodeString(label));
    // Part No
    aRow.Append("?");
    // Ver
    label = CATString(buf);
    aRow.Append(CATUnicodeString(label));
    // Part Name
    foo = "XXPART-" + CATString(buf);
    aRow.Append(foo);
    // 3D
    aRow.Append("?");
    // 3D Rev
    aRow.Append("?");
    // 2D
    aRow.Append("?");
    // 2D Rev
    aRow.Append("?");

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

SampleRow *SampleViewModel::GetSampleRow(CATBaseUnknown_var iNode)
{
   CATBaseUnknown *ptr= (CATBaseUnknown*)iNode;
   if (ptr && ptr->IsAKindOf(SampleRow::ClassName()))
      return (SampleRow*)ptr;
   return NULL;
}

int SampleViewModel::GetRowId(CATBaseUnknown_var iLine)
{
  SampleRow *pRow = GetSampleRow(iLine);
  if (!pRow)
    return -1;
  return pRow->_id;
}
