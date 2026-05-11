// COPYRIGHT Dassault Systemes 2007

#include <SampleColVariantModel.h>
#include <SampleViewController.h>
#include <CATString.h>
#include <CATUnicodeString.h>

#include  <TIE_CATIDlgTableViewColumnModel.h>  
TIE_CATIDlgTableViewColumnModel(SampleColVariantModel);  

CATImplementClass( SampleColVariantModel,
                   Implementation,
                   CATExtIDlgTableViewColumnModel,
                   CATNull );

SampleColVariantModel::SampleColVariantModel():CATExtIDlgTableViewColumnModel()
{
  _Control = NULL;
}

SampleColVariantModel::~SampleColVariantModel()
{
  _Control = NULL;
}

void SampleColVariantModel::SetController(SampleViewController *iControl)
{
  _Control = iControl;
}

HRESULT SampleColVariantModel::SetOrderedColumns(const CATListOfCATString &iColumnIDs)
{
  return S_OK;
}

HRESULT SampleColVariantModel::GetOrderedColumns(CATListOfCATString &oColumnIDs)
{
  for (int i = 1; i <= _ColumnIDs.Size(); i++)
    oColumnIDs.Append(_ColumnIDs[i]);

  return S_OK;
}

HRESULT SampleColVariantModel::GetLabel(const CATString &iColumnID, CATUnicodeString &oLabel)
{
  oLabel = "ERR";

  int ColIndex = getColumnIndex(iColumnID);
  if (ColIndex < 0)
    return E_FAIL;

  oLabel = _ColumnTitles[ColIndex];

  return S_OK;
}

HRESULT SampleColVariantModel::GetStyle(const CATString &iColumnID, CATDlgTableStyle &oStyle)
{
  oStyle = CATDlgTableCellNormal | CATDlgTableCenterJustify;
  return S_OK;
}
 
HRESULT SampleColVariantModel::GetWidth(const CATString &iColumnID, int &oWidth)
{
  oWidth = -1;

  int ColIndex = getColumnIndex(iColumnID);
  if (ColIndex < 0)
    return E_FAIL;

  oWidth = _ColumnWidths[ColIndex];

  return S_OK;
}

HRESULT SampleColVariantModel::SetWidth(const CATString &iColumnID, int iWidth)
{
  int ColIndex = getColumnIndex(iColumnID);
  if (ColIndex < 0)
    return E_FAIL;

  _ColumnWidths[ColIndex] = iWidth;

  return S_OK;
}

void SampleColVariantModel::SetSortDefinition(const CATString &iColumnID, int iReverse)
{
  if (_Control)
    _Control->HighlightColumn(iColumnID);
}

void SampleColVariantModel::GetSortDefinition(CATString &oColumnID, int &oReverse)
{
}

HRESULT SampleColVariantModel::SetVisibility(const CATString &iColumnID, CATDlgTableStyle iStyle)
{
  return S_OK;
}

HRESULT SampleColVariantModel::GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  return S_OK;
}

HRESULT SampleColVariantModel::GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha)
{
  return S_OK;
}

void SampleColVariantModel::DefineTheColumns(int iNbCols)
{
  int colWidth = 60;
  char buf[3];
  CATString colID = "Col01";
  CATUnicodeString colTitle = "Oper";

  for (int i=1; i<=iNbCols; i++)
  {
    sprintf ( &buf[0], "%d", i );
    buf[strlen(&buf[0])] = '\0';
    colID = "VC" + CATString ( buf );
    colTitle = CATUnicodeString("VC" + CATString ( buf ));
    _ColumnIDs.Append(colID);
    _ColumnTitles.Append(colTitle);
    _ColumnWidths.Append(colWidth);
  }
}

// Private
int SampleColVariantModel::getColumnIndex(const CATString &iColumnID)
{
  // SCA : column name format : VCxx with xx 01 -> N
  int ColIndex = -1;
  char *colName = (char*)iColumnID.ConvertToChar();
  sscanf(colName+2, "%d", &ColIndex);

  if (ColIndex <= 0 || ColIndex > _ColumnWidths.Size())
    ColIndex = -1;

  return ColIndex;
}
