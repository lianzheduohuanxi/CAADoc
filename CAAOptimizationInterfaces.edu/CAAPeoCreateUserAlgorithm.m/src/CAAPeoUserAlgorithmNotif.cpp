#include "CAAPeoUserAlgorithmNotif.h"

CATImplementClass(CAAPeoUserAlgorithmNotif, Implementation, CATNotification, CATnull);

CAAPeoUserAlgorithmNotif::CAAPeoUserAlgorithmNotif(int iElapsedTime, int iCurrentUpdate, const CATUnicodeString& iComment)
{
	_comment = iComment;
	_elapsedTime = iElapsedTime;
	_currentUpdate = iCurrentUpdate;

}

CAAPeoUserAlgorithmNotif::~CAAPeoUserAlgorithmNotif()
{
}

//--

CATUnicodeString CAAPeoUserAlgorithmNotif::GetComment()
{
	return _comment;
}

HRESULT CAAPeoUserAlgorithmNotif::SetComment(const CATUnicodeString& iComment)
{
	_comment = iComment;
	return S_OK;
}

//--

int CAAPeoUserAlgorithmNotif::GetElapsedTime()
{
	return _elapsedTime;
}

HRESULT CAAPeoUserAlgorithmNotif::SetElapsedTime(int iElapsedTime)
{
	_elapsedTime = iElapsedTime;
	return S_OK;
}

//--

int CAAPeoUserAlgorithmNotif::GetCurrentUpdate()
{
	return _currentUpdate;
}

HRESULT CAAPeoUserAlgorithmNotif::SetCurrentUpdate(int iCurrentUpdate)
{
	_currentUpdate = iCurrentUpdate;
	return S_OK;
}

//--

