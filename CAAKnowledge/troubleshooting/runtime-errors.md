---
category: use-case
title: "CAA运行时错误排查指南"
type: "troubleshooting"
verified: true
---
category: use-case

# CAA运行时错误排查指南

> 以下错误模式从 CAA .edu 源码中的错误处理代码提取。

## E_FAIL 返回值

**源码验证**: .edu 中最常见的错误返回。

```cpp
// 源码: CAAEAfrCollection.cpp
if (NULL == _pListe) return E_FAIL;
if ((0 == oCount) || (NULL == _pListe)) return E_FAIL;
if (NULL == oObject) return E_FAIL;
```

**排查**:
1. 检查传入指针是否为 `NULL`
2. 使用 `SUCCEEDED(hr)` 宏检查返回值（需 `#include "CATErrorDef.h"`）
3. 逐行检查哪个调用返回了 `E_FAIL`

## SUCCEEDED / FAILED 宏使用

**源码验证**: `.edu` 中使用 `CATErrorDef.h` 提供 `SUCCEEDED` 宏。

```cpp
// 源码: CAAAfrGetMRUManager.cpp
#include "CATErrorDef.h"  // for SUCCEEDED macro

HRESULT hr = GetMRUManager(&pManager);
if (SUCCEEDED(hr)) {
  // 成功
}
```

**注意**: CAA 中使用标准 COM 的 `SUCCEEDED`/`FAILED` 宏，不是自定义宏。

## NULL 指针防护

**源码验证**: .edu 中广泛使用的防护模式。

```cpp
// 源码: CAAAfrBoundingElementCmd.cpp
if (NULL == _pContainer) return E_FAIL;

// 标准CAA防护模式:
if (NULL != pEditor) {
  CATDocument * pDoc = pEditor->GetDocument(#);
}
```

## CATTry / CATCatch 异常处理

**源码验证**: `CAAStmServices.cpp` 等文件中使用。

```cpp
// 源码: CAAStmServices.cpp
#include "CATError.h"

CATTry
{
  // 可能抛出异常的操作
}
CATCatch(CATMfErrUpdate, error)
{
  // 特定错误处理
}
CATCatch(CATError, error)
{
  // 通用错误处理
}
```

## 常见运行时问题

### 1. 工作台不显示

**可能原因**:
- `CreateWorkbench` 未在 Addin 中注册
- `CreateCommands` 未添加命令头
- Addin 未通过 `CATIAfrGeneralWksAddin` 等注册

### 2. 命令不响应

**可能原因**:
- `Activate` 方法未正确重写
- 未调用 `RequestStatusChange(CATCmdMsgAbortSent)` 结束命令

### 3. 组件无法实例化

**可能原因**:
- `CATImplementClass` 参数错误
- TIE 文件中引用的头文件不匹配
- 未在 `CAADocument` 中注册组件

---
category: use-case
