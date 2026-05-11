// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract:
//  ---------
//
//  Batch program which manipulates dates and times through CATTime class
//	and spans through CATTimeSpan class.
//  
//  Illustrates :   
//	   1 - Creating a Timestamp
//	   2 - Retrieving the Hours from the Timestamp
//	   3 - Creating a Duration
//     4 - Adding two Durations
//     5 - Retrieving the Total Number of Hours from a Duration
//     6 - Substracting a Duration from a Timestamp
//     7 - Comparing Two Durations
//
//=============================================================================
//  How to launch:
//  -------------
//
//  Type:
//    CAASysTime  
//  
//  The different traces of the sample appear on the standard output.
//
//  Return Code:
//			0 : OK
//			1 : Invalid CATTime object 
//			2 : Invalid CATTimeSpan object 
//
//=============================================================================
 
// System Framework
#include "CATTime.h"		// To declare CATTime class which represents a time and a date
#include "CATTimeSpan.h"	// To declare CATTimeSpan class which represents a span
#include "CATUnicodeString.h"   // To convert CATTime and CATTimeSpan values to strings

// C++ standard library
#include <iostream.h>			

int main()
{

  cout << "The sample CAASysTime begins ..."<< endl << endl ;

  //CATTime display format
  //	%A: to retrieve the name of the day   
  //	%d: to retrieve the day  
  //	%B: to retrieve the month
  //	%Y: to retrieve the year
  //	%H: to retrieve the hour
  //	%M: to retrieve the minutes
  //	%S: to retrieve the seconds
  //		ex: Thursday, 20 November 1997 16:23:15.
  //
  CATUnicodeString   iMyFormatTime = " % %A, %d %B %Y %H:%M:%S. %";

  //CATTimeSpan display format
  //	%D: to retrieve the number of days 
  //	%H: to retrieve the number of hours 
  //	%M: to retrieve the number of minutes 
  //	%S: to retrieve the number of seconds 
  //		ex: 12 days 21:57:41 	
  //
  CATUnicodeString   iMyFormatTimeSpan = " % %D days %H hours %M minutes %S seconds %";

  //to retrieve the value converted to string
  //
  CATUnicodeString   theReturnedString; 

  //---------------------------------------------------------------------------
  // 1 - Creating a Timestamp
  //---------------------------------------------------------------------------
  cout << "Creation of a CATTime object from the date and the time--\n";

  // The date is 11/20/1997 at 16h23mn15s
  int iYear		= 1997;		
  int iMonth	= 11;		
  int iDay		= 20;		
  int iHour		= 16;		
  int iMin		= 23;	
  int iSec		= 15;	

  // builds the CATTime object from these values
  CATTime MyTime1( iYear, iMonth, iDay, iHour, iMin, iSec);
  if ( 1 == MyTime1.GetStatus() )
  {
    // if MyTime1 is a valid CATTime object, converts its value to a string 
    cout << "The date and time of MyTime1 are: ";
    CATUnicodeString Date = MyTime1.ConvertToString( iMyFormatTime );
    cout << Date.ConvertToChar() << endl << endl;
  }
  else
  {
    cout << "MyTime1 is an invalid CATTime object";
    return 1;
  }

  //---------------------------------------------------------------------------
  // 2 - Retrieving the Hours from the Timestamp
  //---------------------------------------------------------------------------
  cout << "Gets the hour of MyTime1---------------------------------\n";

  // gets the hour of MyTime1
  int hour = MyTime1.GetHour();
  if ( -1 != hour )
  {
    cout << "The hour of MyTime1 is: " << hour << endl<<endl;
  }else
  {
    cout << "MyTime1 is an invalid hours ";
    return 1;
  }

  //---------------------------------------------------------------------------
  // 3 - Creating a Duration
  //---------------------------------------------------------------------------
  cout << "Creation of MyTimeSpan1 from its values :--------------\n";

  // a span time of: 9 Days , 16 hours , 45 minutes and 54 seconds 
  long iDays	= 9;			
  int iHours	= 16;		
  int iMins		= 45;	
  int iSecs		= 54;		

  // builds the CATTimeSpan object from these values
  CATTimeSpan MyTimeSpan1 ( iDays, iHours, iMins, iSecs );	
 
  if ( 1 == MyTimeSpan1.GetStatus() )
  { 
     cout << "The value of MyTimeSpan1 is " << endl;
     CATUnicodeString Duration = MyTimeSpan1.ConvertToString( iMyFormatTimeSpan);
     cout << Duration.ConvertToChar() << endl << endl;
  }
  else
  {
    cout << " Can't create MyTimeSpan1 from its components" << endl << endl;
    return 2;
  }

  //---------------------------------------------------------------------------
  // 4 - Adding two Durations
  //---------------------------------------------------------------------------	
  cout << "Adds MyTimeSpan2 to MyTimeSpan1---------------------------" << endl ;

  // builds a new CATTimeSpan object named MyTimeSpan2 
  // a span time of: 3 Days , 5 hours , 11 minutes and 47 seconds 
  //
  CATTimeSpan MyTimeSpan2 ( 3, 5, 11, 47 );	

  if ( 1 == MyTimeSpan2.GetStatus() )
  {
    // if MyTimeSpan1 is a valid CATTimeSpan object, converts its value to a string
    cout << "The value of MyTimeSpan2 is " << endl;
    CATUnicodeString Duration = MyTimeSpan2.ConvertToString( iMyFormatTimeSpan );
    cout << Duration.ConvertToChar() << endl << endl;

    //adds MyTimeSpan2 to MyTimeSpan1
    MyTimeSpan1 += MyTimeSpan2 ;

    // display the result
    cout << "The new value of MyTimeSpan1 is " << endl;
    CATUnicodeString CumulativeDuration = MyTimeSpan1.ConvertToString( iMyFormatTimeSpan );
    cout << CumulativeDuration.ConvertToChar() << endl << endl;
  }
  else
  {
    cout << "Can't add MyTimeSpan2 to MyTimeSpan1" << endl << endl;
    return 2;
  }

  //---------------------------------------------------------------------------
  // 5 - Retrieving the Total Number of Hours from a Duration
  //---------------------------------------------------------------------------
  cout << "Gets the total number of hours from MyTimeSpan1-----------" << endl;
  int span = MyTimeSpan1.GetTotalHours();
  cout << "The total number of hours is " << span << " (= 24*12 + 21)" << endl<< endl;
  
  //---------------------------------------------------------------------------
  // 6 - Substracting a Duration from a Timestamp
  //---------------------------------------------------------------------------
  cout << "Subtracts MyTimeSpan1 to MyTime1----------------------"<< endl;
  MyTime1 -= MyTimeSpan1;

  if ( 1 == MyTime1.GetStatus() )
  {
    // if MyTimeSpan1 is a valid CATTimeSpan object, converts its value to a string
    CATUnicodeString NewDate = MyTime1.ConvertToString( iMyFormatTime );
    cout << "The new date and time of MyTime1 are: " << NewDate.ConvertToChar() << endl << endl;
  }
  else
  {
    cout << "Can't subtracts the last result to MyTime1" << endl;
    return 1;
  }

  //---------------------------------------------------------------------------
  // 7 - Comparing Two Durations	
  //---------------------------------------------------------------------------
  cout << "Comparisons between MyTime1 and MyTime2:-----------------" << endl;  

  // builds a new CATTime object named MyTime2
  // The date is 07/14/2000 at 15h41mn32s
  CATTime MyTime2( 2000, 7, 14, 15, 41, 32);
  
  if (  1 == MyTime2.GetStatus() )
  {
    // if MyTime2 is a valid CATTime object, converts its value to a string 
    cout << "The date and time of MyTime2 are: ";
    CATUnicodeString Date2 = MyTime2.ConvertToString( iMyFormatTime );
    cout << Date2.ConvertToChar() << endl << endl;

    // tests the expression MyTime2 < MyTime1
    if ( MyTime2 < MyTime1 )
      cout << "MyTime2 <  MyTime1 is TRUE." << endl<< endl;
    else
      cout << "MyTime2 <  MyTime1 is FALSE." << endl<< endl;
  }
  else
  {
    cout << "MyTime2 is an invalid CATTime object" << endl;
    return 1;
  }

  cout << "The sample CAASysTime is finish  ..."<< endl << endl ;

  return 0;
}
