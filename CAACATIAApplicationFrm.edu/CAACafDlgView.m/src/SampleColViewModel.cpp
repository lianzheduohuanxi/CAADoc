// COPYRIGHT Dassault Systemes 2007

#include <SampleColViewModel.h>
#include <SampleViewController.h>
#include <CATString.h>
#include <CATUnicodeString.h>

#include  <TIE_CATIDlgTableViewColumnModel.h>  
TIE_CATIDlgTableViewColumnModel(SampleColViewModel);  

CATImplementClass( SampleColViewModel,
                   Implementation,
                   CATExtIDlgTableViewColumnModel,
                   CATNull );

SampleColViewModel::SampleColViewModel():CATExtIDlgTableViewColumnModel()
{
  _Control = NULL;
}

SampleColViewModel::~SampleColViewModel()
{
  _Control = NULL;
}

void SampleColViewModel::SetController(SampleViewController *iControl)
{
  _Control = iControl;
}

HRESULT SampleColViewModel::SetOrderedColumns(const CATListOfCATString &iColumnIDs)
{
  return S_OK;
}

HRESULT SampleColViewModel::GetOrderedColumns(CATListOfCATString &oColumnIDs)
{
  for (int i = 1; i <= _ColumnIDs.Size(); i++)
    oColumnIDs.Append(_ColumnIDs[i]);

  return S_OK;
}

HRESULT SampleColViewModel::GetLabel(const CATString &iColumnID, CATUnicodeString &oLabel)
{
  oLabel = "ERR";

  int ColIndex = getColumnIndex(iColumnID);
  if (ColIndex < 0)
    return E_FAIL;

  oLabel = _ColumnTitles[ColIndex];

  return S_OK;
}

HRESULT SampleColViewModel::GetStyle(const CATString &iColumnID, CATDlgTableStyle &oStyle)
{
  oStyle = CATDlgTableCellNormal | CATDlgTableCenterJustify;
  return S_OK;
}
 
HRESULT SampleColViewModel::GetWidth(const CATString &iColumnID, int &oWidth)
{
  oWidth = -1;

  int ColIndex = getColumnIndex(iColumnID);
  if (ColIndex < 0)
    return E_FAIL;

  oWidth = _ColumnWidths[ColIndex];

  return S_OK;
}

HRESULT SampleColViewModel::SetWidth(const CATString &iColumnID, int iWidth)
{
  int ColIndex = getColumnIndex(iColumnID);
  if (ColIndex < 0)
    return E_FAIL;

  _ColumnWidths[ColIndex] = iWidth;

  return S_OK;
}

void SampleColViewModel::SetSortDefinition(const CATString &iColumnID, int iReverse)
{
  if (_Control)
    _Control->HighlightColumn(iColumnID);
}

void SampleColViewModel::GetSortDefinition(CATString &oColumn, int &oReverse)
{
}

HRESULT SampleColViewModel::SetVisibility(const CATString &iColumn, CATDlgTableStyle iStyle)
{
  return S_OK;
}

HRESULT SampleColViewModel::GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  return S_OK;
}

HRESULT SampleColViewModel::GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  return S_OK;
}

void SampleColViewModel::DefineTheColumns(int iNbCols)
{
  CATString colID = "Col01"; _ColumnIDs.Append(colID);
  CATUnicodeString colTitle = "Oper"; _ColumnTitles.Append(colTitle);
  int colWidth = 75; _ColumnWidths.Append(colWidth);

  if (iNbCols >= 10)
  {
    colID = "Col02"; _ColumnIDs.Append(colID);
    colID = "Col03"; _ColumnIDs.Append(colID);
    colID = "Col04"; _ColumnIDs.Append(colID);
    colID = "Col05"; _ColumnIDs.Append(colID);
    colID = "Col06"; _ColumnIDs.Append(colID);
    colID = "Col07"; _ColumnIDs.Append(colID);
    colID = "Col08"; _ColumnIDs.Append(colID);
    colID = "Col09"; _ColumnIDs.Append(colID);
    colID = "Col10"; _ColumnIDs.Append(colID);

    colTitle = "+"; _ColumnTitles.Append(colTitle);
    colTitle = "Level"; _ColumnTitles.Append(colTitle);
    colTitle = "Part No"; _ColumnTitles.Append(colTitle);
    colTitle = "Vers"; _ColumnTitles.Append(colTitle);
    colTitle = "Part Name"; _ColumnTitles.Append(colTitle);
    colTitle = "3D"; _ColumnTitles.Append(colTitle);
    colTitle = "3D Rev"; _ColumnTitles.Append(colTitle);
    colTitle = "2D"; _ColumnTitles.Append(colTitle);
    colTitle = "2D Rev"; _ColumnTitles.Append(colTitle);

    colWidth = 25; _ColumnWidths.Append(colWidth);
    colWidth = 75; _ColumnWidths.Append(colWidth);
    colWidth = 50; _ColumnWidths.Append(colWidth);
    colWidth = 50; _ColumnWidths.Append(colWidth);
    colWidth = 75; _ColumnWidths.Append(colWidth);
    colWidth = 30; _ColumnWidths.Append(colWidth);
    colWidth = 75; _ColumnWidths.Append(colWidth);
    colWidth = 30; _ColumnWidths.Append(colWidth);
    colWidth = 75; _ColumnWidths.Append(colWidth);
  }
}

// Private
int SampleColViewModel::getColumnIndex(const CATString &iColumnID)
{
  // SCA : column name format : Colxx with xx 01 -> 10
  int ColIndex = -1;
  char *colName = (char*)iColumnID.ConvertToChar();
  sscanf(colName+3, "%d", &ColIndex);

  if (ColIndex <= 0 || ColIndex > _ColumnWidths.Size())
    ColIndex = -1;

  return ColIndex;
}
