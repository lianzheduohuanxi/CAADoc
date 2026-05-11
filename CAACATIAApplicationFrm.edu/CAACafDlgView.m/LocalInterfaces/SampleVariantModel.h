// COPYRIGHT Dassault Systemes 2007

#ifndef SampleVariantModel_H
#define SampleVariantModel_H

#include <CATExtIDlgTableViewModel.h>
#include <CATIDlgTableViewModel.h>
#include <SampleRow.h>

/**
 * SampleVariantModel. Implement List model interfaces.
 * This class link the view with the application model.
 **/
class SampleVariantModel: public CATExtIDlgTableViewModel
{
  CATDeclareClass;

  public:
  /**
   * Constructor
   **/
  SampleVariantModel( void );
  /**
   * Destructor
   **/
  virtual ~SampleVariantModel( void );

  // CATIDlgTableViewModel implementation
  virtual HRESULT GetUpdateEvent(CATCallbackEvent * oUpdateEvent);
  virtual HRESULT GetEventPublisher(CATBaseUnknown ** oTableModelEventPublisher);
  virtual HRESULT GetLabel(CATBaseUnknown_var & iLine, const CATString & iColumnID, CATUnicodeString & oLabel); 
  virtual HRESULT SetLabel(CATBaseUnknown_var & iLine, const CATString &iColumnID, const CATUnicodeString& iLabel);
  virtual HRESULT IsEditable(CATBaseUnknown_var & iLine, const CATString& iColumnID, CATBoolean & oEditable);
  virtual HRESULT GetIcon(CATBaseUnknown_var iLine , const CATString &iColumnID, CATUnicodeString & oIcon);
  virtual HRESULT GetStyle(CATBaseUnknown_var iLine, const CATString &iColumnID, CATDlgTableStyle & oStyle);
  virtual HRESULT GetLineCount(int & oLineCount);
  virtual HRESULT GetLines(int iStart, int iCount, CATListOfCATBaseUnknown_var & oLines);
  virtual HRESULT GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha);
  virtual HRESULT GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha);
  virtual HRESULT GetBorderColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha);
  virtual HRESULT GetTextColor(CATBaseUnknown_var iLine, const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha);
  virtual HRESULT GetBackgroundColor(CATBaseUnknown_var iLine , const CATString &iColumnID, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha);
  virtual void Sort(const CATString &iColumn, int iReverse);
  virtual void HighlightColumn(const CATString &iColumnID);

  // Remplissage
  void FillTheColumns(int iNbRows, int iNbVars);

  // Utilitaire
  static int GetRowId(CATBaseUnknown_var iItem);

private:

  static SampleRow *GetSampleRow(CATBaseUnknown_var iLine);
  
  // SCA : La structure de donnees
  CATListOfCATBaseUnknown_var _SampleRows;

};
#endif
