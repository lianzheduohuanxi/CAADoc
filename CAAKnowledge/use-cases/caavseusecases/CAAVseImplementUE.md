---
title: "Untitled"
category: "use-case"
module: "CAAVseUseCases"
tags: ["CAADkoImplementUE", "CATImplementClass", "CAAEDkoUserExitOrderVersioning", "CAADocStyleSheets", "CAAEDkoUserExitVersionToUpdate", "CATIVpmAttribute", "CAADocRunSample", "CATIVPMObjectVersion", "CAADocUseCases", "CAAVPMDesktopObjects", "CATIAVPMObjectVersion", "CAAVPMSTEPExchanges"]
source_file: "Doc/online/CAAVseUseCases/CAAVseImplementUE.htmmd"
converted: "2026-05-11T11:27:02.799516"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to help you to implement the methods declared in
the VPMIExOderVersioning and VPMIExVersionToUpdate User Exits.

[Top]

### The CAADkoImplementUE Use Case

CAADkoImplementUE is a use case of the CAAVPMDesktopObjects.edu framework
that illustrates how to implement the VPMIExOderVersioning and
VPMIExVersionToUpdate User Exits used in the import tools. There are called in
some Mergers (see the ENOVIA V5 documentation for Merger definition) to
customize the behavior for a given existing Object Version (can it be updated,
which is the next version, ... ). 

[Top]

#### What Does CAADkoImplementUE Do

CAADkoImplementUE enables the customer to implement the methods of both User
Exits in order to get the information needed in the import tool. The behavior of
the import tool will depend on this information.

[Top]

#### How to Launch CAADkoImplementUE

To launch CAADkoImplementUE, you will need to:

  
```vbscript
- Set up the build time environment, then compile CAADkoImplementUE.m module
    along with its prerequisites
```
  
```vbscript
- Set up the run time environment

```

This is described in [1].

Then, successively import two different versions of the same part, either by
using the Supply Chain management CATlet in the ENOVIA LCA client, or by using
the batch IEnovIn.

[Top]

#### Where to Find the CAADkoImplementUE Code

The CAADkoImplementUE use case is located in the CAADkoImplementUE.m module
of the CAAVPMDesktopObjects.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM
is installed.

[Top]

### Step-by-Step

There are three logical steps in CAADkoImplementUE:

  
- Implementing the VPMIExOrderVersioning Interface
  
- Implementing the VPMIExVersionToUpdate Interface
  
- Updating the Interface Dictionary

We now comment each of those sections by looking at the code.

[Top]

#### Implementing the VPMIExOrderVersioning Interface

*VPMIExOrderVersioning* must be implemented by *UEOrderVersion* to
be called dynamically by the import tool. This is done in a code extension class
of *UEOrderVersion* named *CAAEDkoUserExitOrderVersioning* whose
header file is the following:

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

[Top]

#### Implementing the VPMIExVersionToUpdate Interface

*VPMIExVersionToUpdate* must be implemented by *UEVersionToUpdate*
to be called dynamically by the import tool. This is done in a code extension
class of *UEVersionToUpdate* named *CAAEDkoUserExitVersionToUpdate*
whose header file is the following:

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

The `RightToUpdate` method first retrieves a pointer to *CATIVpmAttribute*
from the object passed as argument using a *CATIVPMObjectVersion* pointer.
It then calls the `GetValue` method of *CATIVpmAttribute* to
retrieve the value of the `V_status` attribute. The retrieved value
is then converted as *CATUnicodeString* instance, compared to `Released`.
If `V_status` compares with `Released`, `RightToUpdate`
returns `S_FALSE`. Otherwise, the import can take place.

The `GenerateTheNextV_Version` method is as follows:

The `GenerateTheNextV_Version` method returns the next Version
from the current Version and the current Order.

[Top]

#### Updating the Interface Dictionary

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

[Top]

---

### In Short

This article provides an example on how to implement both User Exits called
by the import tool.

[Top]

---

### References

---

### History

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```cpp
#include &quot;CATBaseUnknown.h&quot;
class CATUnicodeString;

class CAAEDkoUserExitOrderVersioning : public CATBaseUnknown
{
  CATDeclareClass;
  public:
  
    CAAEDkoUserExitOrderVersioning(#);
    virtual ~CAAEDkoUserExitOrderVersioning(#);

    HRESULT IsBeforeThan( const CATUnicodeString &amp; iVersion1,
                          const CATUnicodeString &amp; iVersion2 );

  private:

    CAAEDkoUserExitOrderVersioning(const CAAEDkoUserExitOrderVersioning &amp; iObjectToCopy);
    CAAEDkoUserExitOrderVersioning &amp; operator = (const CAAEDkoUserExitOrderVersioning &amp; iObjectToCopy);
};
```

```cpp
// Local Framework 
#include &quot;CAAEDkoUserExitOrderVersioning.h&quot;

// System Framework 
#include &quot;CATUnicodeString.h&quot; // Type of object versions

CATImplementClass(CAAEDkoUserExitOrderVersioning,
                  CodeExtension,
                  CATBaseUnknown,
                  UEOrderVersion);

#include &quot;TIE_VPMIExUEOrderVersioning.h&quot;
TIE_VPMIExUEOrderVersioning(CAAEDkoUserExitOrderVersioning);

CAAEDkoUserExitOrderVersioning::CAAEDkoUserExitOrderVersioning(#) {}
CAAEDkoUserExitOrderVersioning::~CAAEDkoUserExitOrderVersioning(#) {}

//-----------------------------------------------------------------------------

HRESULT CAAEDkoUserExitOrderVersioning::IsBeforeThan(
                     const CATUnicodeString &amp; iVersion1,
                     const CATUnicodeString &amp; iVersion2)
{
  HRESULT hr = S_OK; 

  if(iVersion1&gt;iVersion2)
    hr = S_FALSE;

  return hr;
}
```

```cpp
// System framework
#include &quot;CATBaseUnknown.h&quot;
class CATUnicodeString;

// VPMInterfaces framework
class CATIAVPMObjectVersion;

class CAAEDkoUserExitVersionToUpdate : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public: 

    CAAEDkoUserExitVersionToUpdate(#);
    virtual ~CAAEDkoUserExitVersionToUpdate(#);

    HRESULT RightToUpdate(const CATIAVPMObjectVersion* iObjectVersion);
    HRESULT GenerateTheNextV_Version(const CATUnicodeString iCurrentV_Version,
                                     const int              iCurrentV_order,
                                     CATUnicodeString &amp;     oNextV_Version);

  private:

    CAAEDkoUserExitVersionToUpdate(const CAAEDkoUserExitVersionToUpdate &amp; iObjectToCopy);
    CAAEDkoUserExitVersionToUpdate &amp; operator = (const CAAEDkoUserExitVersionToUpdate &amp; iObjectToCopy);
};
```

```cpp
// Local Framework 
#include &quot;CAAEDkoUserExitVersionToUpdate.h&quot;

// System Framework 
#include &quot;CATUnicodeString.h&quot;       // To be used for object new version generation

// VPMInterfaces framework
#include &quot;CATIVpmAttribute.h&quot;      // To retrieve the object attributes
#include &quot;CATIAVPMObjectVersion.h&quot; // To retrieve the object version

CATImplementClass(CAAEDkoUserExitVersionToUpdate,
                  CodeExtension,
                  CATBaseUnknown,
                  UEVersionToUpdate);

#include &quot;TIE_VPMIExUEVersionToUpdate.h&quot;
TIE_VPMIExUEVersionToUpdate(CAAEDkoUserExitVersionToUpdate);

CAAEDkoUserExitVersionToUpdate::CAAEDkoUserExitVersionToUpdate(#) {}
CAAEDkoUserExitVersionToUpdate::~CAAEDkoUserExitVersionToUpdate(#) {}
...
```

```cpp
...
HRESULT CAAEDkoUserExitVersionToUpdate::RightToUpdate(const CATIAVPMObjectVersion * iObjectVersion)
{
  HRESULT hr = S_OK; 

  // Get the attributes
  CATIVpmAttribute * piVpmAttributeOnObject = NULL;
  hr = iObjectVersion-&gt;QueryInterface(IID_CATIVpmAttribute,
                                      (void **) &amp;piVpmAttributeOnObject);
  if (SUCCEEDED(hr) &amp;&amp; NULL != piVpmAttributeOnObject)
  {
    CORBAAny oValue;
    // Get the status
    hr = piVpmAttributeOnObject-&gt;GetValue(&quot;V_status&quot;, oValue);
    piVpmAttributeOnObject-&gt;Release(#);
    piVpmAttributeOnObject = NULL;
    if (SUCCEEDED(hr))
    {
      CATUnicodeString Status;
      CATBoolean rc = oValue &gt;&gt; Status;
      if (CATTrue == rc)
      {
        CATUnicodeString StatusRel(&quot;Released&quot;);

        // If status = Released -&gt; S_FALSE
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

```cpp
...
HRESULT CAAEDkoUserExitVersionToUpdate::GenerateTheNextV_Version(
                        const CATUnicodeString iCurrentV_Version,
                        const int              iCurrentV_order,
                        CATUnicodeString &amp; oNextV_Version)
{
  HRESULT hr = S_OK; 

  const CATUnicodeString NextVB(&quot;--B&quot;);
  const CATUnicodeString NextVC(&quot;--C&quot;);

  if      (iCurrentV_order == 1 &amp;&amp; iCurrentV_Version.Compare(&quot;--A&quot;)==2)
     oNextV_Version = NextVB;
  else if (iCurrentV_order == 2 &amp;&amp; iCurrentV_Version.Compare(&quot;--B&quot;)==2)
     oNextV_Version = NextVC;
  else
      hr = E_ABORT;

  return hr;
}
```

```vbscript
UEOrderVersion    VPMIExUEOrderVersioning libCAADkoImplementUE
UEVersionToUpdate VPMIExUEVersionToUpdate libCAADkoImplementUE
```