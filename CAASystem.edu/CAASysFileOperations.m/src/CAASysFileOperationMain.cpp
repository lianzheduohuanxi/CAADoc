// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract:
//  ---------
//
//  Batch showing the use of CATString, CATMsgCatalog and 
//  CATUnicodeString in CATIA.
//
//  Illustrates:
//
//     1- Verifying the type of machine on which are we running 
//     2- Creating a Directory Path
//     3- Creating a Directory 
//     4- Creating Files 
//     5- Scanning a Directory
//     6- Closing  a Directory
//     
//=============================================================================
//  How to launch:
//  -------------
//
//  Type:
//    CAASysFileOperations WorkingDirectory  DirectoryName
//  
//  The different traces of the sample appear on the standard output.
//
//  Return Code:
//     0 : OK
//     -1: bad entry argument 
//     -2: Platform no supported
//     -4: Pb to create the directory 
//     -6: Cannot open the directory
//     -7: Pb in reading the directory
//     -8: Can't close the directory
//
//=============================================================================

// System
#include "CATLib.h"	  // header file for the files operations


// C++ Standard Library
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc , char* argv[])
{
  cout << endl;
  cout << "CAASysFileOperations Begins ..."<< endl << endl ;

  char * WrkDir=NULL, *DirName = NULL;
  
  if ( 3 != argc )
  {
      cout << " Usage: " << argv [0] ;
      cout<<" Working Directory + Directory Name to create \n";
      exit (-1);
  }
  else
  {
      WrkDir  =  argv [1] ;
      DirName =  argv[2];
  }

  // ----------------------------------------------------------------
  // 1 - Verifying the type of machine on which  are we running 
  // ----------------------------------------------------------------
  
  unsigned short Platform=0;
  unsigned short OS=0;
  
  OS = ::CATGetOperatingSystem( &Platform);
  
  if ( CATWindowsPlatform == Platform )
    cout << "Windows Platform and ";
  else
    cout << "Unix  Platform and ";
    
  switch (OS)
  {
    case CATOsAIX :
      cout << " Operating System is AIX \n";
      break;
    case CATOsSOLARIS :
      cout << " Operating System is SOLARIS \n";
      break;
    case CATOsIRIX :
      cout << " Operating System is IRIX \n";
      break;
    case CATOsHPUX :
      cout <<" Operating System is HPUX \n";
      break;
    case CATOsWindowsNT :
      cout << " Operating System is WindowsNT\n";
      break;
    case CATOsWindows95 :
      cout << " Operating System is Windows95\n";
      break;
    case  CATOsWindows98 :
      cout << " Operating System is Windows98\n ";
      break;
    case CATUnknownOS :
      cout<< " Operating System is Unknown\n ";
      break;
    default:
      cout << "Error: Unknown platform!\n";
      exit (-2);
      break;
  }

  cout << endl;

  // ------------------------------------
  // 2 - Creation  a Directory Path 
  // ------------------------------------
  
  // Creation of the Directory: DirName in the Working Directory: WrkDir
  // Warning:  Path must be allocated by the caller....
  char Path[1024];
  ::CATMakePath ( WrkDir, DirName, Path); 
  

  // ----------------------------------------------
  // 3 - Creating a directory
  // ----------------------------------------------       
         
  CATLibStatus status = ::CATCreateDirectory (Path);
  if ( CATLibError == status)
  {
    cout << " Can't create " << Path <<endl;
    exit (-4);
  }else
  {
    cout << "The Directory: " << Path << " is creating " << endl << endl;
  }
  

  // ----------------------------------------------
  // 4 - Creating Files in a directory
  // ----------------------------------------------     

  for ( int i=0; i< 10; i++)
  {
      char name[14];
      sprintf ( name, "FILE%x", i);
      char FilePath[1024];
          
      ::CATMakePath ( Path, name, FilePath); 
      
      // empty file created in write and binary mode
      FILE* fd = fopen ( FilePath, "w+b");
      fclose (fd);
	  
  }
      
  // ----------------------------------------------
  // 5 - Scanning a directory
  // ----------------------------------------------      

  // handle on the Directory  defined in CATLib.h
  CATDirectory Dir;
  status = ::CATOpenDirectory (Path, &Dir);
      
  if ( CATLibError == status)
  {
     cout << " Can't open directory " << Path << endl;
     exit (-6);
  }
      
  // EndOfDir=1 indicates that the end of the directory has been reached
  int EndOfDir=0;
  status = CATLibSuccess ;
  CATDirectoryEntry Entry;
  
  cout << "Listing of the Directory:  " << Path << endl;
  
  while (( EndOfDir !=1) && ( CATLibSuccess == status))
  {
     status= ::CATReadDirectory ( &Dir, &Entry, &EndOfDir);
     
     if (( CATLibError == status ) && ( EndOfDir !=1))
     {
        cout << " Can't read next entry in " << Path << endl;
        exit (-7);
     }

     // name of the current file
     cout <<  Entry.name << endl;
  }

  // ----------------------------------------------
  // 6 - Closing a directory
  // ----------------------------------------------      
      
  status = ::CATCloseDirectory (&Dir);
  if ( CATLibError == status )
  {
     cout << " Can't close the directory " << Path << endl;
     exit (-8);
  }

  cout << endl;
  cout << " CAASysFileOperations is finished."<< endl ;
  
  return 0;
     
}
