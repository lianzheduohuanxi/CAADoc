---
module: "CAAV5V6MechanicalModeler.edu"
category: "CAA V5/V6 机械建模 — CATIFmFeatureBehaviorCustomization / ProceduralReport / PLM"
tier: "3"
status: "已完成"
---

# CAAV5V6MechanicalModeler.edu — V5/V6 机械建模

## 模块定位

CAAV5V6MechanicalModeler 是 CAAMechanicalModeler 的 V5/V6 双版本实现，通过条件编译 (`#ifdef CATIAR214`) 在同一套代码中支持 V5 和 V6 平台。它与 CAAMechanicalModeler 结构几乎相同（CombinedCurve、CCDataExtension、MultiMeasure、AxisSystem 等），但引入了 V6 平台的关键差异：

- **CATIFmFeatureBehaviorCustomization** — V6 的统一特征行为接口，替代 CATIBuild
- **Procedural Report** — V6 的过程化报告机制
- **PLM 会话** — V6 基于 PLM 的会话/文档管理
- **CATIMmiUseGeometricalElement** — V6 的几何元素访问接口
- **CATDeclareHandler** — V6 的 Handler 声明机制

---

## V5 vs V6 核心差异

### 1. Build 机制差异

| 方面 | V5 (CAAMechanicalModeler) | V6 (CAAV5V6MechanicalModeler) |
|------|--------------------------|-------------------------------|
| **Build 接口** | `CATIBuild::Build()` | `CATIFmFeatureBehaviorCustomization::Build()` |
| **实现注册** | `CATImplementClass(..., DataExtension, CATBaseUnknown, LateType)` | `CATImplementClass(..., DataExtension, CATIFmFeatureBehaviorCustomization, LateType)` |
| **BOA 注册** | 无需 | `CATImplementBOA(CATIFmFeatureBehaviorCustomization, ...)` |
| **字典注册** | `LateType CATIBuild libXxx` | `LateType CATIFmFeatureBehaviorCustomization libXxx` |

**V6 Behavior 接口额外方法**：
```cpp
class CATIFmFeatureBehaviorCustomization {
    virtual HRESULT Build() = 0;
    virtual HRESULT CanBeRemoved(CATBoolean &oDeletable) const;  // 可删除？
    virtual HRESULT BeforeRemove();                               // 删除前回调
    virtual HRESULT CcpRegisterAdditionalObjectsForCopy(...);     // CCP 复制附加对象
    virtual HRESULT CcpUpdate(...);                               // CCP 更新
    virtual HRESULT CcpPaste(...);                                // CCP 粘贴
    virtual HRESULT CcpRegisterAdditionalObjectsForRemove(...);   // CCP 删除附加对象
};
```

### 2. Procedural Report 差异

| 方面 | V5 | V6 |
|------|----|----|
| **接口** | `CATIMfProcReport` | `CATIMmiProcReport` |
| **CreateProcReport** | `CreateProcReport(list, keys, boolOp)` | `CreateProcReport(list, keys, boolOp)` |
| **GetCGMJournalList** | `GetCGMJournalList()` 直接返回 | `GetCGMJournalList(pList)` 输出参数 |
| **StoreProcReport** | `StoreProcReport(body, NoCopy, boolOp)` | `StoreProcReport(body, NoCopy, boolOp)` |
| **DeleteProcReport** | `DeleteProcReport()` | `DeleteProcReport()` |

### 3. 错误处理差异

| 方面 | V5 | V6 |
|------|----|----|
| **更新错误接口** | `CATIUpdateError` | `CATIMmiUpdateError` |
| **错误工厂** | `CATMfErrUpdate` 直接 new | `CATMmiExtendServicesFactory::CreateUpdateErrorAccess` |
| **创建错误** | `new CATMfErrUpdate()` | `piErrorAccess->CreateNewError(pError)` |
| **设置诊断** | `pError->SetDiagnostic(msg)` | `piErrorAccess->SetMmiDiagnostic(pError, msg)` |
| **关联错误** | `pUpdateError->SetUpdateError(pError)` | `spUpdateError->SetMmiUpdateError(pError)` |

### 4. 几何元素访问差异

| 方面 | V5 | V6 |
|------|----|----|
| **接口** | `CATIGeometricalElement` | `CATIMmiUseGeometricalElement` |
| **获取 Body** | `GetBodyResult()` | `GetBodyResult(CATBody_var&)` |
| **BRep 访问** | `CATIMfBRep` | `CATIMmiUseMfBRep` |
| **获取 Body** | `CreateBody(MfWithTemporaryBody)` | `GetBody(CATBody_var&)` |

### 5. 会话初始化差异

**V5**：
```cpp
HRESULT CAAV5V6MmrInitSession(char *iSessionName,
                              const CATUnicodeString& iStorageName,
                              CATDocument *&oNewDoc,
                              CATIMmiPrtContainer *&opContainer) {
    CATSession *pSession = NULL;
    Create_Session(iSessionName, pSession);         // 创建本地会话
    CATDocumentServices::OpenDocument(iStorageName, oNewDoc);  // 打开文档
    CATInit *pDocAsInit = NULL;
    oNewDoc->QueryInterface(IID_CATInit, (void**)&pDocAsInit);
    opContainer = (CATIMmiPrtContainer*)pDocAsInit->GetRootContainer("CATIPrtContainer");
}
```

**V6**：
```cpp
HRESULT CAAV5V6MmrInitSession(const char *iRepository, const char *iServer,
                              const char *iUser, const char *iPassword,
                              const char *iRole, const char *iStrPLMType,
                              const CATUnicodeString& iPLM_ExternalIDValue,
                              const CATUnicodeString& iV_versionValue,
                              CATOmbLifeCycleRootsBag &iBag,
                              CATIMmiPrtContainer *&opContainer) {
    CAAAdpCreateSession(iRepository, iServer, iUser, iPassword, iRole);  // PLM 会话
    CATIPLMComponent *piPLMComponent = NULL;
    CAAOpenPLMComponent(iStrPLMType, iPLM_ExternalIDValue, iV_versionValue,
                        IID_CATIPLMComponent, (void**)&piPLMComponent, iBag, TRUE);
    // 切换到编辑模式
    spLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
    // 检索容器
    spRepRef->RetrieveApplicativeContainer("CATPrtCont", IID_CATIMmiPrtContainer,
                                           (void**)&opContainer);
}
```

### 6. Handler 机制差异

V6 在 PublicInterface 声明末尾添加 `CATDeclareHandler`：
```cpp
// V5: 仅 CATDeclareInterface
class CAAIMmrCombinedCurve : public CATBaseUnknown {
    CATDeclareInterface;
    // ...
};

// V6: CATDeclareInterface + CATDeclareHandler
class CAAIV5V6ExtMmrCombinedCurve : public CATBaseUnknown {
    CATDeclareInterface;
    // ...
};
CATDeclareHandler(CAAIV5V6ExtMmrCombinedCurve, CATBaseUnknown);
```

### 7. 条件编译模式

```cpp
#ifdef CATIAR214
// V6 only
#include "CATIMmiProcReport.h"
CATIMmiProcReport_var spProcReport = NULL_var;
#else
// V5 only
#include "CATIMfProcReport.h"
CATIMfProcReport_var spProcReport = NULL_var;
#endif
```

---

## 模块结构对照

CAAV5V6MechanicalModeler 包含与 CAAMechanicalModeler 几乎相同的 30+ 模块，前缀从 `CAAMmr` 变为 `CAAV5V6ExtMmr` 或 `CAAV5V6Mmr`：

| V5 模块 | V6 对应模块 | 差异 |
|---------|-----------|------|
| CAAMmrCombinedCurve | CAAV5V6ExtMmrCombinedCurve | +Behavior (CATIFmFeatureBehaviorCustomization) |
| CAAMmrCCDataExtension | CAAV5V6ExtMmrCCDataExtension | +Behavior, +V6 错误处理 |
| CAAMmrMultiMeasureAndMeasureSet | CAAV5V6ExtMmrMultiMeasure | +Behavior, +NavigateObject, +ParmPublisher |
| CAAMmrAxisSystemCreation | CAAV5V6MmrAxisSystemCreation | 基本相同 |
| CAAMmrUtilities | CAAV5V6MmrUtilities | +InitSession (PLM/V5 双版本) |

---

## 关键接口速查

| 接口/类 | V5 版本 | V6 版本 |
|---------|--------|--------|
| **Build 接口** | `CATIBuild` | `CATIFmFeatureBehaviorCustomization` |
| **几何元素** | `CATIGeometricalElement` | `CATIMmiUseGeometricalElement` |
| **BRep** | `CATIMfBRep` | `CATIMmiUseMfBRep` |
| **过程报告** | `CATIMfProcReport` | `CATIMmiProcReport` |
| **更新错误** | `CATIUpdateError` | `CATIMmiUpdateError` |
| **错误访问** | `new CATMfErrUpdate()` | `CATMmiExtendServicesFactory::CreateUpdateErrorAccess` |
| **算法配置** | `CATMmrAlgoConfigServices` | `CATMmiAlgoConfigServices` via `CATMmiExtendServicesFactory` |
| **特征接口** | `CATIMmiMechanicalFeature` | 相同 |
| **机械属性** | `CATIMechanicalProperties` | 相同 |
| **Handler** | 无需 | `CATDeclareHandler(Interface, Base)` |

---

## AI Agent 学习要点

1. **V6 用 CATIFmFeatureBehaviorCustomization 统一替代了 CATIBuild**，同时增加了 CCP（Cut/Copy/Paste）生命周期管理

2. **V6 的错误处理通过工厂模式创建**（`CATMmiExtendServicesFactory::CreateUpdateErrorAccess`），而非直接 new

3. **V6 使用 PLM 会话管理**，需要 Repository/Server/User/Password/PLMType/ExternalID 等参数，而非简单的文件名

4. **条件编译标识符是 `CATIAR214`**，用于区分 V6 和 V5 代码路径

5. **V6 的几何元素访问使用 `CATIMmiUseGeometricalElement::GetBodyResult(var&)`**，输出参数是 `CATBody_var` 引用而非返回指针

6. **CATDeclareHandler 是 V6 的 Handler 注册宏**，位于接口声明之后，用于支持基于 Handler 的接口分发