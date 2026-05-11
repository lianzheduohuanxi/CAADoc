// COPYRIGHT DASSAULT SYSTEMES 2000


// System framework
#include "CAASysLineSetting.h"	  // header file of the current class
#include "CATSettingRepository.h" // Settings 
#include "CATUnicodeString.h"	  // CATUnicodeString 

//---------------------------------------------------------------------------------
// Initialization of static pointer on CATSettingRepository

CATSettingRepository *CAASysLineSetting::_pSetting = NULL;

//---------------------------------------------------------------------------------

CAASysLineSetting::CAASysLineSetting()
{
}

//---------------------------------------------------------------------------------

CAASysLineSetting::~CAASysLineSetting()
{
  // Releasing the CATSettingRepository
  if ( NULL != _pSetting)
  {
     _pSetting->Release();
     _pSetting= NULL;
  }
}

//---------------------------------------------------------------------------------

HRESULT CAASysLineSetting::Init()
{
  HRESULT rc = S_OK ;

  if ( NULL ==_pSetting )
  {
     //-------------------------------------------------------------------
     // Creation of the unique instance of the class CATSettingRepository 
     // named "CAASysLineSetting" constructed from the file 
     // CAASysLineSetting.CATSettings if exists else constructed empty.
     // ------------------------------------------------------------------
      _pSetting= CATSettingRepository::GetRepository( "CAASysLineSetting");
      if ( NULL != _pSetting )
      { // Null occurs if no more place in memory 
     

     //---------------------------------------------------------------------------
     // Reading or initialization of the attributes defining the properties 
     // of a line :
     //   - its Thickness of type int
     //   - ts  Color     of type array of 3 int
     //   - its linetype  of type CATUnicodeString
     //------------------------------------------------------------------------
  
         long status= 0;

         // hardcoded default value used for initialization of the attribute 
         //
         int Thickness=1; 
         status = _pSetting->ReadSetting ( "Thickness", &Thickness);
         if ( 1 != status )
         {
   	     rc = E_FAIL;
         }
      
         if ( SUCCEEDED(rc) )
         {
            // hardcoded default value for the attribute "Name"
            //
            CATUnicodeString Name ("Solid");
            status= _pSetting->ReadSetting ( "Name", &Name);
            if ( 1 != status )
            {
   	       rc = E_FAIL;
            }
         }

         if ( SUCCEEDED(rc) )
         {
            // hardcoded default value for 3 int
            //
            int  Color[] ={255,0,0};
            status= _pSetting->ReadSetting ( "Color", Color, 3);
            //if ( 3 != status)
	    if ( 0>= status)
            {
               return E_FAIL;
            }
        }

      }else 
      {
         rc= E_FAIL;
      }
  }
  
  return rc ;
}

//---------------------------------------------------------------------------

HRESULT CAASysLineSetting::SetThickness ( int iThickness )
{
  HRESULT rc =S_OK;
  
  if (NULL == _pSetting)
  {
    rc = Init();
  }
  
  if (SUCCEEDED(rc))
  {
      // Write an int
      long status= _pSetting->WriteSetting ( "Thickness", &iThickness);

      if ( 1 != status )
      {
         // error in the Write operation
	     rc = E_FAIL ;
      }
  }

  return rc ;

}

//---------------------------------------------------------------------------

HRESULT CAASysLineSetting::GetThickness (int *oThickness )
{

  HRESULT rc = S_OK ;
  
  if (NULL ==_pSetting)
  {
    rc = Init();
  }

  if ( SUCCEEDED(rc) )
  {
     // Always use the default value to initialize the object before reading
     *oThickness  = 1;

     // read an int 
     long status = _pSetting ->ReadSetting ("Thickness",oThickness);
  
     if ( 1 != status )
     { 
       // pbme is the Read operation
       rc = E_FAIL;
     }
  }

  return rc ;
}

//---------------------------------------------------------------------------

HRESULT CAASysLineSetting::SetColor ( int iRed, int iGreen, int iBlue)
{
  HRESULT rc = S_OK;

  if ( NULL == _pSetting )
  {
     rc=Init();
  }

  if (SUCCEEDED(rc))
  {
      int tab[3];
      tab[0] = iRed;
      tab[1] = iGreen;
      tab[2] = iBlue;
      
      // write 3 int
      long status= _pSetting->WriteSetting ( "Color", tab, 3);
      if ( 1 != status)
      {
         // error in the Write operation
         rc = E_FAIL ;
      }

  }

  return rc;
}

//---------------------------------------------------------------------------

HRESULT CAASysLineSetting::GetColor (int *oRed, int *oGreen, int *oBlue)
{
  HRESULT rc = S_OK;
  
  if (NULL == _pSetting)
  {
    rc = Init();
  }

  if ( SUCCEEDED(rc) )
  {
     int Color[] = {255,0,0};

     // Read 3 int
     long ReadCount = _pSetting ->ReadSetting ("Color", Color, 3);

     if ( 3 != ReadCount ) 
     {
       // ReadSetting returns the number of elements of the attribute
       rc = E_FAIL ;
     }
     else
     {
        *oRed   = Color[0] ;
        *oGreen = Color[1] ;
        *oBlue  = Color[2] ;
     }
  }

  return rc;

}

//---------------------------------------------------------------------------

HRESULT CAASysLineSetting::SetName ( CATUnicodeString* iName)
{
  HRESULT rc = E_FAIL ;

  if ( NULL !=  iName )
  {
     if ( NULL == _pSetting)
     {
        rc = Init();
     }else
     {
        rc = S_OK ;
     }

     if ( SUCCEEDED(rc) )
     {
         // write a CATUnicodeString
         long status= _pSetting->WriteSetting ( "Name", iName);
         
         if (1 != status)
         {
            // pb in the Write operation
            rc = E_FAIL ;
         }
     }
  }

  return rc;
}

//---------------------------------------------------------------------------

HRESULT CAASysLineSetting::GetName (CATUnicodeString *oName)
{
  HRESULT rc =E_FAIL;

  if ( NULL != oName )
  {
     if ( NULL == _pSetting )
     {
       rc = Init();
     }else
     {
       rc = S_OK ;
     }

     if ( SUCCEEDED(rc) )
     {
        *oName ="Solid";
        long status = _pSetting ->ReadSetting ("Name",oName);
        if ( 1 != status ) 
        {
          // pb in the read operation
          rc = E_FAIL ;
        }
     }
  }

  return rc ;
  
}

//---------------------------------------------------------------------------

HRESULT  CAASysLineSetting::Save()
{
  HRESULT rc =S_OK;

  if (NULL ==_pSetting)
  {
    rc = Init();
  }

  if (SUCCEEDED(rc))
  {
     rc = _pSetting->SaveRepository();
  }

  return rc ;
}

//---------------------------------------------------------------------------

HRESULT  CAASysLineSetting::Commit()
{
  HRESULT rc =S_OK;

  if (NULL ==_pSetting)
  {
     rc = Init();
  }

  if (SUCCEEDED(rc))
  {
     rc = _pSetting->Commit() ;
  }

  return rc ;
}

//---------------------------------------------------------------------------

HRESULT  CAASysLineSetting::Rollback()
{
  HRESULT rc =S_OK;

  if (NULL ==_pSetting)
  {
    rc = Init();
  }

  if (SUCCEEDED(rc))
  {
     rc = _pSetting->Rollback();
  }

  return rc ;
}
