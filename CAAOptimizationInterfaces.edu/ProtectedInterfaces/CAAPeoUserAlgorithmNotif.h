// COPYRIGHT DASSAULT SYSTEMES  2002
//-----------------------------------------------------------------------------------------------------------------------
// ABSTRACT :
//			  Class used to update the stop dialog while running algo
//			  in interactive mode. This notification is sent during the
//			  algorithm run each time an update is done.
//-----------------------------------------------------------------------------------------------------------------------
#ifndef _CAAPeoUserAlgorithmNotif_
#define _CAAPeoUserAlgorithmNotif_
#include "CAAPeoCreateUserAlgorithm.h"

#include "CATNotification.h"
#include "CATUnicodeString.h"


class ExportedByCAAPeoCreateUserAlgorithm CAAPeoUserAlgorithmNotif : public CATNotification
{
	CATDeclareClass;

public:

	/*
	* Create the notification.
	* @param iComment
	*  comment held by the notification
	* @param iMaxTime
	*  The maximum time allowed for the algorithm run
	* @param iMaxUpdateNb
	* The maximum update number allowed for the algorithm run
	* @param iElapsedTime
	* The time elapsed between the algorithm start and the notification creation
	* @param iCurrentUpdate
	* The current algorithm update while creating this notification
	*/
	CAAPeoUserAlgorithmNotif(int iElapsedTime, int iCurrentUpdate, const CATUnicodeString& iComment = "");
	virtual ~CAAPeoUserAlgorithmNotif();

	CATUnicodeString GetComment();
	HRESULT SetComment(const CATUnicodeString& iComment);

	int GetElapsedTime();
	HRESULT SetElapsedTime(int iElapsedTime);

	int GetCurrentUpdate();
	HRESULT SetCurrentUpdate(int iCurrentUpdate);

private:

	CATUnicodeString _comment;
	int _elapsedTime;
	int _currentUpdate;

};

#endif
