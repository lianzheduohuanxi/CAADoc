---
title: "Untitled"
category: "use-case"
module: "CAAVseUseCases"
tags: ["CAAVPMSTEPExchanges", "CATImplementClass", "CAAEDkoUserExitVersionToUpdate", "CAADocUseCases", "CAAVPMDesktopObjects", "CAADocRunSample", "CAADkoImplementUE", "CATIAVPMObjectVersion", "CATIVPMObjectVersion", "CAAEDkoUserExitOrderVersioning", "CATIVpmAttribute", "CAADocStyleSheets"]
source_file: "Doc/online/CAAVseUseCases/CAAVseImplementUE.htm"
converted: "2026-05-11T11:06:33.034245"
---

# 3D PLM PPR Hub Open Gateway
 
 
## PDM Object Hub
 
 
### []Customizing Import Components
 *Implementing VPMIExOrderVersioning and VPMIExVersionToUpdate*
 
 
 |Use Case
 

---

 
 
### Abstract
 

This article discusses the CAADkoImplementUE use case and explains how
 to implement the User Exits used in the import tool.
 

 
- [**What You Will Learn With This Use Case**]
 
- [**The CAADkoImplementUE Use Case**]
 

 
- [What Does CAADkoImplementUE Do]
 
- [How to Launch CAADkoImplementUE]
 
- [Where to Find the CAADkoImplementUE Code]
 
 
- [**Step-by-Step**]
 
- [**References**]
 
- [**In Short**]
 
 
 

---

### []What You Will Learn With This Use Case

This use case is intended to help you to implement the methods declared in
the VPMIExOderVersioning and VPMIExVersionToUpdate User Exits.

[[Top]]

### []The CAADkoImplementUE Use Case

CAADkoImplementUE is a use case of the CAAVPMDesktopObjects.edu framework
that illustrates how to implement the VPMIExOderVersioning and
VPMIExVersionToUpdate User Exits used in the import tools. There are called in
some Mergers (see the ENOVIA V5 documentation for Merger definition) to
customize the behavior for a given existing Object Version (can it be updated,
which is the next version, ... ). 

[[Top]]

#### []What Does CAADkoImplementUE Do

CAADkoImplementUE enables the customer to implement the methods of both User
Exits in order to get the information needed in the import tool. The behavior of
the import tool will depend on this information.

[[Top]]

#### []How to Launch CAADkoImplementUE

To launch CAADkoImplementUE, you will need to:

 
- Set up the build time environment, then compile CAADkoImplementUE.m module
 along with its prerequisites
 
- Set up the run time environment

This is described in [[1]].

Then, successively import two different versions of the same part, either by
using the Supply Chain management CATlet in the ENOVIA LCA client, or by using
the batch IEnovIn.

[[Top]]

#### []Where to Find the CAADkoImplementUE Code

The CAADkoImplementUE use case is located in the CAADkoImplementUE.m module
of the CAAVPMDesktopObjects.edu framework:

 
 |Windows
 |`InstallRootDirectory\CAAVPMSTEPExchanges.edu\CAADkoImplementUE.m`
 
 
 |Unix
 |`InstallRootDirectory/CAAVPMSTEPExchanges.edu/CAADkoImplementUE.m`
 

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

[[Top]]

### []Step-by-Step

There are three logical steps in CAADkoImplementUE:

 
- [Implementing the VPMIExOrderVersioning Interface]
 
- [Implementing the VPMIExVersionToUpdate Interface]
 
- [Updating the Interface Dictionary]

We now comment each of those sections by looking at the code.

[[Top]]

#### []Implementing the VPMIExOrderVersioning Interface

*VPMIExOrderVersioning* must be implemented by *UEOrderVersion* to
be called dynamically by the import tool. This is done in a code extension class
of *UEOrderVersion* named *CAAEDkoUserExitOrderVersioning* whose
header file is the following:

 
 ****
```
#include "CATBaseUnknown.h"
class CATUnicodeString;

class CAAEDkoUserExitOrderVersioning : public CATBaseUnknown
{
 CATDeclareClass;
 public:
 
 CAAEDkoUserExitOrderVersioning();
 virtual ~CAAEDkoUserExitOrderVersioning();

 HRESULT 
IsBeforeThan
( const CATUnicodeString & iVersion1,
 const CATUnicodeString & iVersion2 );

 private:

 CAAEDkoUserExitOrderVersioning(const CAAEDkoUserExitOrderVersioning & iObjectToCopy);
 CAAEDkoUserExitOrderVersioning & operator = (const CAAEDkoUserExitOrderVersioning & iObjectToCopy);
};
```

 
 

The *CAAEDkoUserExitOrderVersioning* extension class derives from *CATBaseUnknown*.
The `CATDeclareClass` macro declares that the class *CAAEDkoUserExitOrderVersioning*
belongs to a component. The class has a constructor and a destructor, and
declares the method `IsBeforeThan` of the *VPMIExOrderVersioning*
interface. Note that the copy constructor and the assignment operator are set as
private. This is very important for extensions. Since extensions must never be
directly instantiated by client applications, this prevents the compiler from
creating the copy constructor and the assignment operator as public without you
know. They are not implemented in the source file.

The source file of *CAAEDkoUserExitOrderVersioning* is as follows:

 
 ************
```
// Local Framework 
#include "CAAEDkoUserExitOrderVersioning.h"

// System Framework 
#include "CATUnicodeString.h" // Type of object versions

CATImplementClass(CAAEDkoUserExitOrderVersioning,
 CodeExtension,
 CATBaseUnknown,
 UEOrderVersion);

#include "TIE_VPMIExUEOrderVersioning.h"
TIE_VPMIExUEOrderVersioning(CAAEDkoUserExitOrderVersioning);

CAAEDkoUserExitOrderVersioning::CAAEDkoUserExitOrderVersioning() {}
CAAEDkoUserExitOrderVersioning::~CAAEDkoUserExitOrderVersioning() {}

//-----------------------------------------------------------------------------

HRESULT CAAEDkoUserExitOrderVersioning::
IsBeforeThan
(
 const CATUnicodeString & iVersion1,
 const CATUnicodeString & iVersion2)
{
 HRESULT hr = S_OK; 

 if(iVersion1>iVersion2)
 hr = S_FALSE;

 return hr;
}
```

 
 

The `CATImplementClass` macro declares that the *CAAEDkoUserExitOrderVersioning*
class is code extension class, thanks to the `CodeExtension` keyword,
and that it extends the component whose type is *UEOrderVersion*. The third
parameter must always be set to *CATBaseUnknown*, makes no sense, and is
unused for extensions. The *CAAEDkoUserExitOrderVersioning* class states
that it implements the *VPMIExOrderVersioning* interface thanks to the `TIE_VPMIExUEOrderVersioning`
macro.

The `IsBeforeThan` method compares the object versions. `iVersion1`
is the version of the released object, and `iVersion2` is the one of
the currently imported object. If the version of the released object object is
greater than the one of the imported object, the import must not take place, and
`IsBeforeThan` returns `S_FALSE`. Otherwise, the import
can take place.

[[Top]]

#### []Implementing the VPMIExVersionToUpdate Interface

*VPMIExVersionToUpdate* must be implemented by *UEVersionToUpdate*
to be called dynamically by the import tool. This is done in a code extension
class of *UEVersionToUpdate* named *CAAEDkoUserExitVersionToUpdate*
whose header file is the following:

 
 
```
// System framework
#include "CATBaseUnknown.h"
class CATUnicodeString;

// VPMInterfaces framework
class CATIAVPMObjectVersion;

class CAAEDkoUserExitVersionToUpdate : public CATBaseUnknown
{
 // Used in conjunction with CATImplementClass in the .cpp file
 CATDeclareClass;

 public: 

 CAAEDkoUserExitVersionToUpdate();
 virtual ~CAAEDkoUserExitVersionToUpdate();

 HRESULT RightToUpdate(const CATIAVPMObjectVersion* iObjectVersion);
 HRESULT GenerateTheNextV_Version(const CATUnicodeString iCurrentV_Version,
 const int iCurrentV_order,
 CATUnicodeString & oNextV_Version);

 private:

 CAAEDkoUserExitVersionToUpdate(const CAAEDkoUserExitVersionToUpdate & iObjectToCopy);
 CAAEDkoUserExitVersionToUpdate & operator = (const CAAEDkoUserExitVersionToUpdate & iObjectToCopy);
};
```

 
 

The *CAAEDkoUserExitVersionToUpdate* extension class derives from *CATBaseUnknown*.
The `CATDeclareClass` macro declares that the class *CAAEDkoUserExitVersionToUpdate*
belongs to a component. The class has a constructor and a destructor, and
declares the two methods `RightToUpdate` and `GenerateTheNextV_Version`
of the *VPMIExVersionToUpdate* interface. Note that the copy constructor
and the assignment operator are set as private. This is very important for
extensions. Since extensions must never be directly instantiated by client
applications, this prevents the compiler from creating the copy constructor and
the assignment operator as public without you know. They are not implemented in
the source file.

The source file of *CAAEDkoUserExitVersionToUpdate* is as follows:

 
 
```
// Local Framework 
#include "CAAEDkoUserExitVersionToUpdate.h"

// System Framework 
#include "CATUnicodeString.h" // To be used for object new version generation

// VPMInterfaces framework
#include "CATIVpmAttribute.h" // To retrieve the object attributes
#include "CATIAVPMObjectVersion.h" // To retrieve the object version

CATImplementClass(CAAEDkoUserExitVersionToUpdate,
 CodeExtension,
 CATBaseUnknown,
 UEVersionToUpdate);

#include "TIE_VPMIExUEVersionToUpdate.h"
TIE_VPMIExUEVersionToUpdate(CAAEDkoUserExitVersionToUpdate);

CAAEDkoUserExitVersionToUpdate::CAAEDkoUserExitVersionToUpdate() {}
CAAEDkoUserExitVersionToUpdate::~CAAEDkoUserExitVersionToUpdate() {}
...
```

 
 

The `CATImplementClass` macro declares that the *CAAEDkoUserExitVersionToUpdate*
class is code extension class, thanks to the `CodeExtension` keyword,
and that it extends the component whose type is *UEVersionToUpdate* . The
third parameter must always be set to *CATBaseUnknown*, makes no sense, and
is unused for extensions. The *CAAEDkoUserExitVersionToUpdate* class states
that it implements the *VPMIExVersionToUpdate* interface thanks to the `TIE_VPMIExUEVersionToUpdate`
macro.

The `RightToUpdate` method analyzes whether a given *CATIAVPMObjectVersion*
object can be updated or not. In this use case, the criterion is the status of
this object. If this status is Released, the object cannot be updated.
Otherwise, it can be updated.

 
 ********
```
...
HRESULT CAAEDkoUserExitVersionToUpdate::
RightToUpdate
(const CATIAVPMObjectVersion * iObjectVersion)
{
 HRESULT hr = S_OK; 

 // Get the attributes
 CATIVpmAttribute * piVpmAttributeOnObject = NULL;
 hr = iObjectVersion->QueryInterface(IID_CATIVpmAttribute,
 (void **) &piVpmAttributeOnObject);
 if (SUCCEEDED(hr) && NULL != piVpmAttributeOnObject)
 {
 CORBAAny oValue;
 // Get the status
 hr = piVpmAttributeOnObject->
GetValue
("V_status", oValue);
 piVpmAttributeOnObject->Release();
 piVpmAttributeOnObject = NULL;
 if (SUCCEEDED(hr))
 {
 CATUnicodeString Status;
 CATBoolean rc = oValue >> Status;
 if (CATTrue == rc)
 {
 CATUnicodeString StatusRel("Released");

 // If status = Released -> S_FALSE
 if(Status.Compare(StatusRel)==2)
 {
 hr = S_FALSE;
 }
 else
 {
 hr = S_OK;
 }
 }
 else
 {
 hr = E_FAIL;
 }
 }
 else
 {
 hr = E_ABORT;
 }
 }
 return hr;
}
...
```

 
 

The `RightToUpdate` method first retrieves a pointer to *CATIVpmAttribute*
from the object passed as argument using a *CATIVPMObjectVersion* pointer.
It then calls the `GetValue` method of *CATIVpmAttribute* to
retrieve the value of the `V_status` attribute. The retrieved value
is then converted as *CATUnicodeString* instance, compared to `Released`.
If `V_status` compares with `Released`, `RightToUpdate`
returns `S_FALSE`. Otherwise, the import can take place.

The `GenerateTheNextV_Version` method is as follows:

 
 ****
```
...
HRESULT CAAEDkoUserExitVersionToUpdate::
GenerateTheNextV_Version
(
 const CATUnicodeString iCurrentV_Version,
 const int iCurrentV_order,
 CATUnicodeString & oNextV_Version)
{
 HRESULT hr = S_OK; 

 const CATUnicodeString NextVB("--B");
 const CATUnicodeString NextVC("--C");

 if (iCurrentV_order == 1 && iCurrentV_Version.Compare("--A")==2)
 oNextV_Version = NextVB;
 else if (iCurrentV_order == 2 && iCurrentV_Version.Compare("--B")==2)
 oNextV_Version = NextVC;
 else
 hr = E_ABORT;

 return hr;
}
```

 
 

The `GenerateTheNextV_Version` method returns the next Version
from the current Version and the current Order.

[[Top]]

#### []Updating the Interface Dictionary

 
 
```
UEOrderVersion VPMIExUEOrderVersioning libCAADkoImplementUE
UEVersionToUpdate VPMIExUEVersionToUpdate libCAADkoImplementUE
```

 
 

The interface dictionary declares that the *UEOrderVersion* component
implements the *VPMIExUEOrderVersioning* interface and that the code to
load into memory to use these interfaces is located in the libCAADkoImplementUE
shared library or DLL, and that *UEVersionToUpdate* implements *VPMIExUEVersionToUpdate* 
in the same shared library or DLL. Note that the component name is used to refer
to the component in the interface dictionary, and never the extension class
names. Note also that the shared library or DLL to associate with the
component/interface pair is the one that contains the code created by the call
to the TIE macro (This is generally the same library than the one that contains
the interface implementation code, since the TIE macro is usually included in
the extension class source file.) This is because when a client asks a component
for an interface pointer, the TIE class is instantiated first, and it either
retrieves the existing instance of the appropriate extension class, or otherwise
instantiates it.

[[Top]]

---

### []In Short

This article provides an example on how to implement both User Exits called
by the import tool.

[[Top]]

---

### []References

 
 |[1]
 |[Building
 and Launching a CAA V5 Use Case]
 
 
 |[[Top]]
 

---

### []History

 
 |Version: **1** [May 2001]
 |Document created
 
 
 |[[Top]]
 

---

*Copyright 2001, Dassault Systmes. All rights reserved.*