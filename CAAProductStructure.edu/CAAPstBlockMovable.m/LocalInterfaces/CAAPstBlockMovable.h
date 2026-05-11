//
// Copyright DASSAULT SYSTEMES 2003
//
#ifndef CAAPstBlockMovable_H
#define CAAPstBlockMovable_H

class CATSession;
class CATDocument;
class CATUnicodeString;
class CATIProduct;
class CATIProduct_var;

class CAAPstBlockMovable {

public:
	//
	// Status codes returned
	//
	enum {
		S_Success= 0,
		S_Usage = 1,	// invalid number of arguments
		S_Session,	// failed to create a session
		S_OpenInput,	// failed to open input file
		S_RootProduct,	// failed to get root product
		S_RootCATIProduct, // failed to get CATIProduct on root product
		S_ParentNotFound, // failed to get parent of specified part
		S_PartNotFound,	// failed to find specified part
		S_ParentCATIBlockMovable, // failed to get CATIBlockMovable on parent
		S_PartCATIMovable, //  failed to get CATIMovable on part
		S_GetPosition,	// failed to get position
		S_SetPosition,	// failed to set position
		S_SaveOutput	//  failed to save output file
	};

	CAAPstBlockMovable();
	~CAAPstBlockMovable();
	
	// 
	// Main method
	//
	int Run (int argc, const char *argv[]);

private:
	// supporting data
	static const char *_sessionName;
	CATSession *_pSession;
	CATDocument *_pDocument;

	// Find the first part of a given name
	CATIProduct_var FindPart(CATUnicodeString& ipartName,
				 CATIProduct *ipiProductOnRoot);
	// clean up before exiting
	void CleanUp();

};

#endif
