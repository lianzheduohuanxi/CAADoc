# Troubleshooting Guide

Common issues and solutions for CATIA CAA development.

## Compiler Errors

### C1010 - Fatal Error: Cannot open include file

**Cause**: Missing header file or incorrect include path

**Solution**:
- Verify the header file exists in the specified path
- Check `Imakefile.mk` for correct `DEP_CPPFLAGS` settings
- Ensure `include` directories are properly configured

### C2065/C2066 - Undeclared Identifier

**Cause**: Missing declaration or incorrect case

**Solution**:
- Check interface inheritance (QueryInterface may return E_NOINTERFACE)
- Verify method signatures match header definitions
- Ensure proper namespace usage

---

## Linker Errors

### LNK2001 - Unresolved External Symbol

**Cause**: Implementation not found or incorrect library linking

**Solution**:
- Verify TIE (To Implement an Extension) macros are correctly placed
- Check `Imakefile.mk` for correct `LINK_WITH` libraries
- Ensure component registration is complete

### LNK2019 - Unresolved External Symbol in Function

**Cause**: Method implementation missing or signature mismatch

**Solution**:
- Verify all methods are implemented
- Check COM aggregation and delegation patterns
- Ensure interface GUIDs are correctly defined

---

## Runtime Errors

### E_NOINTERFACE (0x80004002)

**Cause**: QueryInterface failed for requested interface

**Solution**:
- Verify interface is exposed in QueryInterface implementation
- Check interface inheritance chain
- Ensure TIE bindings are correctly registered

### CAT_E_NOTIMPLEMENTED (0x80004001)

**Cause**: Method not implemented

**Solution**:
- Implement the method or return appropriate error code
- Check if method is optional in interface

---

## Common Patterns

### Correct QueryInterface Implementation

```cpp
HRESULT MyClass::QueryInterface(REFIID iid, void** ppv)
{
    if (iid == IID_IUnknown)
    {
        *ppv = (IUnknown*)this;
    }
    else if (iid == IID_MyInterface)
    {
        *ppv = (MyInterface*)this;
    }
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    ((IUnknown*)(*ppv))->AddRef();
    return S_OK;
}
```

### TIE Macro Usage

```cpp
#include "TIE_CATIObject.h"
TIE_CATIObject(MyClass)
```

---

## Related Topics

- [Development Environment Setup](../quick-refs/development-env.md)
- [Common Patterns](../quick-refs/common-patterns.md)
- [Interface Hierarchy](../quick-refs/interface-hierarchy.md)