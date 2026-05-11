// COPYRIGHT Dassault Systemes 2007

#ifndef SampleColViewModel_H
#define SampleColViewModel_H

#include <CATExtIDlgTableViewColumnModel.h>
#include <SampleViewController.h>

#include <CATListOfCATString.h>
#include <CATListOfCATUnicodeString.h>
#include <CATListOfInt.h>

/**
 * SampleColViewModel. Model for set of columns: names, width...
 **/
class SampleColViewModel: public CATExtIDlgTableViewColumnModel
{
    CATDeclareClass;

public:
    /**
     * Constructor
     **/
    SampleColViewModel( void );
    /**
     * Destructor
     **/
    virtual ~SampleColViewModel( void );

    void SetController(SampleViewController* iControl);

    HRESULT SetOrderedColumns( const CATListOfCATString &iColumns );

    HRESULT GetOrderedColumns( CATListOfCATString &oColumns );

    HRESULT GetLabel( const CATString & iColumn, CATUnicodeString & oLabel );

    HRESULT GetStyle( const CATString & iColumn, CATDlgTableStyle & oStyle);
 
    HRESULT GetWidth( const CATString &iColumn, int & oWidth );

    HRESULT SetWidth( const CATString &iColumn, int iWidth );

    void SetSortDefinition( const CATString &iColumn, int iReverse= 0 );

    void GetSortDefinition( CATString &oColumn, int &oReverse );

    HRESULT SetVisibility( const CATString & iColumn, CATDlgTableStyle iStyle);

    HRESULT GetBackgroundColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha);

    HRESULT GetTextColor(CATDlgTableStyle iStyle, unsigned int & ioRed, unsigned int & ioGreen, unsigned int & ioBlue, unsigned int & ioAlpha);

    void DefineTheColumns(int iNbCols);

private:
        
    int getColumnIndex(const CATString &iColumnID);

    SampleViewController* _Control;
    CATListOfCATString _ColumnIDs;
    CATListOfCATUnicodeString _ColumnTitles;
    CATListOfInt _ColumnWidths;
};

#endif
