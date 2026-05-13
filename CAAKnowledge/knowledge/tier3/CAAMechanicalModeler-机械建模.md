---
module: "CAAMechanicalModeler.edu"
category: "CAA 机械建模核心 — 自定义特征/DataExtension/CATIBuild/Provider/Catalog/AxisSystem"
tier: "3"
status: "已完成"
---

# CAAMechanicalModeler.edu — 机械建模核心

## 模块定位

CAAMechanicalModeler 是 CAA 机械建模框架的教学核心，包含 30 个模块。它展示了如何在 CATIA 中创建完整的自定义机械特征，覆盖从特征定义到 UI 交互的全栈开发：

- **CombinedCurve** — 完整的自定义机械特征：从接口定义到 Build 实现、工厂创建、Catalog 支持、UI 面板
- **CCDataExtension** — DataExtension 模式：在不修改特征的情况下扩展数据计算能力
- **Provider 模式** — UpdateProvider / NavigateProvider / ParmProvider / VisuProvider 四大提供者
- **Catalog 系统** — CATICatalogEnable / CATICatalogInstantiation / CATICatalogSynchronize
- **Mf3DBehavior** — 特征在 3D 中的行为定义（IsASolid/IsAShape/IsADatum）
- **AxisSystem** — 轴系创建、管理和 BRep 表示
- **MultiMeasure** — 非几何 MechanicalElement 示例

这是开发 CATIA 自定义机械特征功能的完整蓝图。

---

## 架构总览

```
┌──────────────────────────────────────────────────────────────────────────┐
│                      机械特征开发全栈架构                                  │
│                                                                           │
│  ┌─────────────────────────────────────────────────────────────────┐     │
│  │                    CombinedCurve (完整自定义特征)                  │     │
│  │                                                                  │     │
│  │  PublicInterface: CAAIMmrCombinedCurve                           │     │
│  │    ├── SetCurve/GetCurve(1..2)      — 两条输入曲线               │     │
│  │    ├── SetDirection/GetDirection(1..2) — 两个拉伸方向             │     │
│  │                                                                  │     │
│  │  实现层 (DataExtensions):                                        │     │
│  │    ├── CAAEMmrCombinedCurve          — 接口实现                   │     │
│  │    ├── CAAEMmrCombinedCurveBuild     — CATIBuild::Build()        │     │
│  │    ├── CAAEMmrCombCrvMf3DBehavior    — IsASolid/IsAShape/IsADatum│     │
│  │    ├── CAAEMmrCombinedCurveMechProp  — 机械属性                   │     │
│  │    ├── CAAEMmrCombCrvInputDescription — 输入描述                  │     │
│  │    └── CAAEMmrCombCrvCkeFeature      — 知识工程集成               │     │
│  │                                                                  │     │
│  │  工厂: CAAIMmrCombCrvFactory → CAAEMmrCombCrvFactory             │     │
│  │    └── CreateCombinedCurve(curve1, dir1, curve2, dir2) → result  │     │
│  │                                                                  │     │
│  │  Catalog:                                                        │     │
│  │    ├── CATICatalogEnable (启用)                                   │     │
│  │    ├── CATICatalogInstantiation (实例化)                          │     │
│  │    └── CATICatalogSynchronize (同步)                              │     │
│  │                                                                  │     │
│  │  UI:                                                             │     │
│  │    ├── CAAMmrCombCrvPanelStCmd  — 面板状态命令                   │     │
│  │    ├── CAAMmrCombinedCurveDlg   — 对话框                          │     │
│  │    ├── CAAEMmrCombinedCurveEdit — 编辑属性                        │     │
│  │    └── CAAEMmrCombineCurveReplace — 替换操作                      │     │
│  └─────────────────────────────────────────────────────────────────┘     │
│                                                                           │
│  ┌─────────────────────────────────────────────────────────────────┐     │
│  │             CCDataExtension (特征扩展计算模式)                     │     │
│  │                                                                  │     │
│  │  扩展计算 CombinedCurve 的长度，结果存储在 Length 参数中           │     │
│  │                                                                  │     │
│  │  CATIInit 容器初始化 → 注册 Provider                              │     │
│  │    ├── CAAMmrUpdateProvForExtCont     — 更新提供者                │     │
│  │    ├── CAAMmrParmProvForExtCont       — 参数提供者                │     │
│  │    ├── CAAMmrNavigateProvForExtCont   — 导航提供者                │     │
│  │    └── CAAMmrVisuProvForExtCont       — 可视化提供者              │     │
│  └─────────────────────────────────────────────────────────────────┘     │
└──────────────────────────────────────────────────────────────────────────┘
```

---

## 核心知识

### 1. CombinedCurve — 完整的自定义机械特征

CombinedCurve 是 CAA 机械建模教程中展示自定义机械特征开发的最完整案例。它定义了一个"两条曲线的拉伸曲面相交"特征。

**1.1 特征概念**

```
CombinedCurve = Extrusion(Curve1, Direction1) ∩ Extrusion(Curve2, Direction2)
```

即：将两条曲线各自沿方向拉伸成曲面，两个曲面的交线就是 CombinedCurve。

**1.2 PublicInterface 定义**

```cpp
// CAAIMmrCombinedCurve — 公开接口
class CAAIMmrCombinedCurve : public CATBaseUnknown {
    CATDeclareInterface;
public:
    virtual HRESULT SetCurve(int iNum, CATISpecObject *ipCurve) = 0;
    virtual HRESULT GetCurve(int iNum, CATISpecObject **opCurve) = 0;
    virtual HRESULT SetDirection(int iNum, CATISpecObject *ipDirection) = 0;
    virtual HRESULT GetDirection(int iNum, CATISpecObject **opDirection) = 0;
};
```

**1.3 接口实现 — 属性读写模式**

```cpp
// CAAEMmrCombinedCurve — DataExtension on "CombinedCurve"
CATImplementClass(CAAEMmrCombinedCurve, DataExtension, CATBaseUnknown, CombinedCurve);
TIE_CAAIMmrCombinedCurve(CAAEMmrCombinedCurve);

HRESULT SetCurve(int iNum, CATISpecObject *ipiSpecOnCurve) {
    CATISpecAttrAccess *piAccess = ...;
    CATISpecAttrKey *piKey = piAccess->GetAttrKey(iNum==1 ? "Curve1" : "Curve2");

    // 关键：如果输入是 BRep 特征且没有 Father，自动聚合
    CATIMfBRep *pIMfBRep = NULL;
    rc = spiSpecOnCurve->QueryInterface(IID_CATIMfBRep, (void**)&pIMfBRep);
    if (SUCCEEDED(rc)) {
        CATISpecObject *pFather = spiSpecOnCurve->GetFather();
        if (NULL == pFather) {
            // 无 Father → 需要聚合到 CombinedCurve 下
            CATIDescendants *pIDescendants = NULL;
            QueryInterface(IID_CATIDescendants, (void**)&pIDescendants);
            pIDescendants->Append(spiSpecOnCurve);
        } else {
            // 已有 Father → 不允许（特征只能有一个父）
            rc = E_FAIL;
        }
    }

    piAccess->SetSpecObject(piKey, spiSpecOnCurve);
    return rc;
}
```

**1.4 工厂模式**

```cpp
// CAAIMmrCombCrvFactory — 创建 CombinedCurve 的工厂接口
class CAAIMmrCombCrvFactory : public CATBaseUnknown {
    CATDeclareInterface;
public:
    virtual HRESULT CreateCombinedCurve(
        CATISpecObject *ipCurve1, CATISpecObject *ipDirection1,
        CATISpecObject *ipCurve2, CATISpecObject *ipDirection2,
        CATISpecObject **opCombinedCurve) = 0;
};
```

**1.5 CATIBuild — 特征重新计算**

```cpp
// CAAEMmrCombinedCurveBuild — DataExtension on "CombinedCurve"
CATImplementClass(CAAEMmrCombinedCurveBuild, DataExtension, CATBaseUnknown, CombinedCurve);
TIE_CATIBuild(CAAEMmrCombinedCurveBuild);

HRESULT Build() {
    // 1. 读取输入曲线和方向
    CAAIMmrCombinedCurve *pCombinedCurve = ...;
    pCombinedCurve->GetCurve(1, &pCurve1);
    pCombinedCurve->GetDirection(1, &pDir1);
    pCombinedCurve->GetCurve(2, &pCurve2);
    pCombinedCurve->GetDirection(2, &pDir2);

    // 2. 获取曲线的 BRep Body
    CATBody *bodyCurve1 = ...;  // QI CATIGeometricalElement → GetBodyResult
    CATBody *bodyCurve2 = ...;

    // 3. 创建拉伸曲面
    // Extrude(curve1, dir1) → bodySweep1
    // Extrude(curve2, dir2) → bodySweep2

    // 4. 计算交线
    // Intersect(bodySweep1, bodySweep2) → bodyIntersection

    // 5. 将结果 Body 绑定到特征
    CATIMfBRep *pMfBRep = ...;
    pMfBRep->SetBodyResult(bodyIntersection);
}
```

**字典注册**：
```
CombinedCurve  CAAIMmrCombinedCurve       libCAAMmrCombinedCurve
CombinedCurve  CATIBuild                  libCAAMmrCombinedCurve
CombinedCurve  CATIMf3DBehavior           libCAAMmrCombinedCurve
CATIContainerOfDocument  CAAIMmrCombCrvFactory  libCAAMmrCombinedCurve
```

---

### 2. CATIMf3DBehavior — 3D 行为定义

定义特征在 3D 视图中的角色：

```cpp
class CAAEMmrCombCrvMf3DBehavior : public CATBaseUnknown {
    CATDeclareClass;
public:
    virtual HRESULT IsASolid() const { return 0; }   // 不是实体
    virtual HRESULT IsAShape() const { return 0; }   // 不是面
    virtual HRESULT IsADatum() const { return 1; }   // 是基准（datum curve）
};
```

- `IsASolid` = 1：特征作为实体显示
- `IsAShape` = 1：特征作为曲面显示
- `IsADatum` = 1：特征作为基准几何（线框）

---

### 3. CCDataExtension — DataExtension 扩展计算模式

CCDataExtension 是一个**扩展**，附加到 CombinedCurve 上，自动计算其长度：

**3.1 接口定义**

```cpp
class CAAIMmrCCDataExtension : public CATBaseUnknown {
    CATDeclareInterface;
public:
    virtual HRESULT SetGeomFeature(const CATBaseUnknown *ipGeomFeature) = 0;
    virtual HRESULT GetGeomFeature(CATISpecObject **ioGeomFeature) = 0;
    virtual HRESULT AggregateParam(CATICkeParm_var ispParmToAggregate) = 0;
    virtual HRESULT GetValuatedParam(CATICkeParm_var &iospValuatedParm) = 0;
};
```

**3.2 CATIBuild 实现 — 计算长度**

```cpp
HRESULT CAAEMmrCCDataExtensionBuild::Build() {
    // 1. 清除上次的错误标记
    CATIUpdateError *pError = ...;
    pError->UnsetUpdateError();

    // 2. 获取被扩展的基础特征
    CATIOsmExtension *pExtension = ...;
    pExtension->QueryBaseObject(IID_CATISpecObject, (void**)&pBase);

    // 3. 获取 GeomFeature 的 Body
    CAAIMmrCCDataExtension *pCCDataExtension = ...;
    pCCDataExtension->GetGeomFeature(&pGeomFeature);

    // 优先 QI CATIGeometricalElement::GetBodyResult
    // 回退 CATIMfBRep::CreateBody(MfWithTemporaryBody)
    CATBody *pBody = ...;

    // 4. 使用 CATDynMassProperties3D 计算长度
    CATDynMassProperties3D *pDynMasOpe = CATDynCreateMassProperties3D(&TopData, pBody);
    double ComputedLength = pDynMasOpe->GetLength();

    // 5. 创建/更新 Length 参数
    // 首次 Build：创建 CATICkeParm 并聚合到 "Length" 属性
    // 后续 Build：直接 ValuateStored
    CATICkeParm_var spValuatedParm = ...;
    if (首次) {
        spValuatedParm = spParmFact->CreateLength("ComputedLength", 0);
        spParmStored->ValuateStored(ComputedLength);
        pCCDataExtension->AggregateParam(spValuatedParm);
        spValuatedParm->SetUserAccess(CATICkeParm::ReadOnly);  // 保护计算结果
    } else {
        spParmStored->ValuateStored(ComputedLength);
    }
}
```

**3.3 错误处理模式**

```cpp
// 使用 CATTry/CATCatch 宏处理异常
CATTry {
    // 核心计算逻辑
}
CATCatch(CATMfErrUpdate, pUpdateError) {
    // 捕获 MechanicalModeler 更新错误
    CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    pErrorToThrow->SetDiagnostic(pUpdateError->GetDiagnostic());
    Flush(pUpdateError);
    piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);
    CATThrow(pErrorToThrow);  // 重新抛出
}
CATCatch(CATError, pError) {
    CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    pErrorToThrow->SetDiagnostic(pError->GetNLSMessage());
    Flush(pError);
    piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);
    CATThrow(pErrorToThrow);
}
CATEndTry
```

---

### 4. Provider 模式 — CATIInit 容器初始化

当 ApplicativeContainer 被创建时，通过 CATIInit 注册 Provider：

```cpp
// CAAEMmrDataExtensionContInit — DataExtension on CATInit for "CAAMmrDataExtensionCont"
CATImplementClass(CAAEMmrDataExtensionContInit, DataExtension, CATInit, CAAMmrDataExtensionCont);
CATImplementBOA(CATInit, CAAEMmrDataExtensionContInit);

void CAAEMmrDataExtensionContInit::Init(CATBoolean iDestroyExistingData) {
    // 1. 获取文档的 CATIProviders 管理器
    CATDocument *pDoc = ...;
    CATIProviders *piProvidersManager = NULL;
    pDoc->QueryInterface(IID_CATIProviders, (void**)&piProvidersManager);

    // 2. 注册四个 Provider
    piProvidersManager->AddProvider(CATIUpdateProvider::ClassId(), new CAAMmrUpdateProvForExtCont());
    piProvidersManager->AddProvider(CATIParmProvider::ClassId(), new CAAMmrParmProvForExtCont());
    piProvidersManager->AddProvider(CATINavigateProvider::ClassId(), new CAAMmrNavigateProvForExtCont());
    piProvidersManager->AddProvider(CATI3DVisuProvider::ClassId(), new CAAMmrVisuProvForExtCont());

    // 3. 列出容器中所有已存在的扩展特征
    // 并重新连接 ModelEvent（文档重新打开时需要）
    CATListPtrCATBaseUnknown *pMemberList = ...;
    for (int i = 1; i <= pMemberList->Size(); i++) {
        CATBaseUnknown *pMember = (*pMemberList)[i];
        CATIOsmExtension_var spExtension = pMember;
        CATBaseUnknown *pBaseFeature = NULL;
        spExtension->QueryBaseObject(IID_CATBaseUnknown, (void**)&pBaseFeature);
        CATIModelEvents_var spModelEvent = pBaseFeature;
        spModelEvent->ConnectTo(pMember);
    }
}
```

**四种 Provider 的职责**：

| Provider | ClassId | 职责 |
|----------|---------|------|
| UpdateProvider | `CATIUpdateProvider::ClassId()` | 扩展特征的更新（Build） |
| ParmProvider | `CATIParmProvider::ClassId()` | 参数发布 |
| NavigateProvider | `CATINavigateProvider::ClassId()` | 特征树导航 |
| VisuProvider | `CATI3DVisuProvider::ClassId()` | 3D 可视化 |

---

### 5. Catalog 系统

**5.1 CATICatalogEnable — 启用 Catalog 支持**

```cpp
// CAAEMmrCatalogEnableForCombCrv — 实现 CATICatalogEnable
CATImplementClass(CAAEMmrCatalogEnableForCombCrv, DataExtension, CATBaseUnknown, CombinedCurve);
TIE_CATICatalogEnable(CAAEMmrCatalogEnableForCombCrv);
// 使 CombinedCurve 类型可被存入 Catalog
```

**5.2 CATICatalogInstantiation — 从 Catalog 实例化**

```cpp
// CAAEMmrCatalogInstantiationForCombCrv
HRESULT RunInstantiationCmd(...) {
    // 1. 验证当前 UI 活动对象是否是 MechanicalPart
    CATIPartRequest *pInt = NULL;
    rc = pLeaf->QueryInterface(IID_CATIPartRequest, (void**)&pInt);

    // 2. 验证 Catalog 条目类型是 Feature
    CATICatalogDescription *pDesc = ...;
    pDesc->GetDescriptionType(ComponentType);
    if (ComponentType == CATICatalogDescription::CATCatalogFeature) {
        // 3. 通过字符串名称创建命令
        newCommand = CATCreateExternalObject("CAAMmrCombCrvPanelStCmd", NULL,
                                             "CAAMmrCombinedCurveUI", NULL);
    }
}
```

**5.3 CATICatalogSynchronize — 同步**

当 Catalog 条目更新时，同步已实例化的特征：
```cpp
CATImplementClass(CAAEMmrCatalogSynchronizeForCombCrv, DataExtension, CATBaseUnknown, CombinedCurve);
TIE_CATICatalogSynchronize(CAAEMmrCatalogSynchronizeForCombCrv);
```

**字典注册**：
```
CombinedCurve  CATICatalogEnable         libCAAMmrCatalogCombCrv
CombinedCurve  CATICatalogInstantiation  libCAAMmrCatalogCombCrv
CombinedCurve  CATICatalogSynchronize    libCAAMmrCatalogCombCrv
```

---

### 6. MultiMeasure — 非几何 MechanicalElement

展示从 `MechanicalElement`（非 `GeometricalElement`）派生的自定义特征：

```cpp
// CAAIMmrMultiMeasure
class CAAIMmrMultiMeasure : public CATBaseUnknown {
    CATDeclareInterface;
public:
    virtual HRESULT SetInputGeomFeature(CATBaseUnknown *ipGeomFeature) = 0;
    virtual HRESULT GetGeomFeature(CATISpecObject **ioGeomFeature) = 0;
    virtual HRESULT GetLengthParameter(CATICkeParm_var &oLengthParm) = 0;
    virtual HRESULT GetWetAreaParameter(CATICkeParm_var &oWetAreaParm) = 0;
    virtual HRESULT GetVolumeParameter(CATICkeParm_var &oVolumeParm) = 0;
};
```

**工厂接口**：
```cpp
class CAAIMmrMultiMeasureAndMeasureSetFactory : public CATBaseUnknown {
    CATDeclareInterface;
public:
    virtual HRESULT CreateMmrMultiMeasure(
        CATBaseUnknown *ipGeometricalElementToMesure,
        CATISpecObject **opMultiMeasureInstance) = 0;
    virtual HRESULT CreateMmrMeasureSet(
        CATISpecObject **opMeasureSetInstance) = 0;
};
```

**字典注册**：
```
CATIContainerOfDocument  CAAIMmrMultiMeasureAndMeasureSetFactory  libCAAMmrMultiMeasureAndMeasureSet
CAAMmrMultiMeasure       CAAIMmrMultiMeasure                      libCAAMmrMultiMeasureAndMeasureSet
CAAMmrMultiMeasure       CATIBuild                                libCAAMmrMultiMeasureAndMeasureSet
```

**关键点**：MultiMeasure 是 `MechanicalElement` 的子类型（非 `GeometricalElement`），因此没有几何 Body，只有参数。它必须被聚合到 `MeasureSet`（派生自 `MechanicalSet`）中。

---

### 7. AxisSystem — 轴系管理

**7.1 轴系创建**

```cpp
// CAAMmrRetrieveCornerAndVectorsFromPad
// 从 Pad 特征中获取角点和方向向量，用于创建轴系
class CAAMmrRetrieveCornerAndVectorsFromPad {
    // 1. 获取 Pad 的 BRep Body
    // 2. 从 Body 中提取角点坐标
    // 3. 计算方向向量
    // 4. 调用 CATIMfAxisSystemManager 创建轴系
};
```

**7.2 轴系的 BRep 表示**

```cpp
// CAAMmrTestBRep — 获取轴系的 BRep 表示
// 轴系本身没有 BRep，但有可视化表示
// 通过 CATIMfAxisSystemManager 获取坐标轴的三条线段
```

**7.3 轴系管理**

```cpp
// CAAMmrTestManagement — 演示轴系的查询和操作
// 遍历文档中的轴系，修改属性，删除等
```

---

### 8. BRep 扫描服务

```cpp
// CAAMmrBRepScanServices — 遍历 Body 的拓扑结构
// 演示 CATCell 遍历模式：
// Body → Domain → Shell → Face → Loop → Edge → Vertex
```

---

### 9. Inter/Intra Part Copy — 零件间复制

```cpp
// CAAMmrInterIntraPartCopy
// 1. 从源 Part 中查找特征
// 2. 使用 CATIPartRequest 创建副本
// 3. 将副本粘贴到目标 Part 的容器中
```

---

### 10. Freeze/Unfreeze — 特征冻结

```cpp
// CAAMmrPartWksFreezeUnfreezeCmd
// 通过 CATIMfFreezeServices 实现特征的冻结/解冻
// 冻结特征在 Update 时不会重新计算
```

---

## 关键接口速查

| 接口/类 | 关键方法 | 用途 |
|---------|---------|------|
| **CAAIMmrCombinedCurve** | `SetCurve/GetCurve`, `SetDirection/GetDirection` | 自定义特征接口 |
| **CAAIMmrCombCrvFactory** | `CreateCombinedCurve` | 特征创建工厂 |
| **CATIBuild** | `Build` | 特征重新计算 |
| **CATIMf3DBehavior** | `IsASolid`, `IsAShape`, `IsADatum` | 3D 行为定义 |
| **CAAIMmrCCDataExtension** | `SetGeomFeature`, `GetGeomFeature`, `AggregateParam`, `GetValuatedParam` | 扩展数据接口 |
| **CATIInit** | `Init`, `GetRootContainer` | 容器初始化 |
| **CATIProviders** | `AddProvider` | Provider 注册 |
| **CATIUpdateError** | `SetUpdateError`, `UnsetUpdateError` | 更新错误管理 |
| **CATICatalogEnable** | (启用标志) | Catalog 支持 |
| **CATICatalogInstantiation** | `RunInstantiationCmd` | Catalog 实例化 |
| **CATICatalogSynchronize** | (同步方法) | Catalog 同步 |
| **CATIMfBRep** | `GetBodyResult`, `CreateBody`, `SetBodyResult` | 特征的 BRep 访问 |
| **CATIGeometricalElement** | `GetBodyResult` | 几何元素 Body |
| **CATIDescendants** | `Append` | 子特征聚合 |
| **CATDynMassProperties3D** | `GetLength`, `GetWetArea`, `GetVolume` | 质量属性计算 |
| **CATMfErrUpdate** | `SetDiagnostic`, `SetAssociatedFeature`, `AddSickFeature` | 更新错误 |
| **CATIMfAxisSystemManager** | (轴系 CRUD) | 轴系管理 |
| **CATIMfFreezeServices** | (冻结/解冻) | 特征冻结 |

---

## 30 个 Use Case 模块对照

### CombinedCurve 全栈模块

| 模块 | 教学内容 |
|------|---------|
| **CAAMmrCombinedCurve** | 核心接口实现 + CATIBuild + Mf3DBehavior + MechProp + InputDescription + CkeFeature |
| **CAAMmrCombinedCurveAddIn** | Workbench Addin 注册 CombinedCurve 命令 |
| **CAAMmrCombinedCurveUI** | CATPanelState + 对话框 + 编辑属性 + 右键菜单 |
| **CAAMmrCombinedCurveReplace** | 特征替换（用新特征替换已有特征） |
| **CAAMmrCombinedCurveSample** | CombinedCurve 的编程使用示例 |

### CCDataExtension 模块

| 模块 | 教学内容 |
|------|---------|
| **CAAMmrCCDataExtension** | 接口实现 + Build + 工厂 + Visu + ParmPublisher + ModelEvent + ContInit |
| **CAAMmrCCDataExtensionUI** | 状态命令 + NavigateObject + NavFilter |
| **CAAMmrEduRscCNext** | 字典文件 + 资源文件 + 图标 |

### Catalog 模块

| 模块 | 教学内容 |
|------|---------|
| **CAAMmrCatalogCombCrv** | CATICatalogEnable + CATICatalogInstantiation + CATICatalogSynchronize |
| **CAAMmrCatalogProductAddin** | Catalog Product Addin |
| **CAAMmrCatalogUI** | Catalog Browser 对话框 |

### 其他模块

| 模块 | 教学内容 |
|------|---------|
| **CAAMmrMultiMeasureAndMeasureSet** | 非几何 MechanicalElement + 工厂 + Build + Visu + Replace |
| **CAAMmrMultiMeasureAndMeasureSetAddIn** | MultiMeasure Addin |
| **CAAMmrMultiMeasureAndMeasureSetUI** | 状态命令 + Edit + SelectShow |
| **CAAMmrAxisSystemCreation** | 轴系创建 |
| **CAAMmrAxisSystemManagement** | 轴系管理 |
| **CAAMmrAxisSystemBRep** | 轴系 BRep 表示 |
| **CAAMmrBRepScanServices** | Body 拓扑遍历 |
| **CAAMmrFeatureTopoBRep** | 特征的拓扑 BRep 访问 |
| **CAAMmrInterIntraPartCopy** | 零件间/零件内复制 |
| **CAAMmrApplicativeImport** | 带 ClientId 的导入 |
| **CAAMmrApplicativeAttributes** | 应用属性 |
| **CAAMmrPartBodyRequest** | Part Body 请求 |
| **CAAMmrFreezeInternalCopy** | 冻结/解冻内部副本 |
| **CAAMmrUseCreateDatumMode** | Datum 模式创建 |
| **CAAMmrUtilities** | 工具函数（GetGeometry, GetPartFromProduct） |
| **CAAMmrCommands** | 显示模式设置命令 |
| **CAAMmrPartWksAddin** | Part Workbench Addin |
| **CAAMmrDebugPrtWksAddin** | Debug Part Workbench Addin |
| **CAAMmrSettingsAddIn** | 设置 Addin |

---

## 设计模式总结

1. **DataExtension 分层模式**：一个特征类型（如 CombinedCurve）可以有多个 DataExtension，每个实现一个接口——接口实现、Build、Mf3DBehavior、MechProp 等各司其职

2. **Factory 模式**：通过 `CATIContainerOfDocument` 扩展工厂接口，将工厂绑定到文档容器上

3. **CATIInit Provider 模式**：容器创建时自动注册四种 Provider，使扩展特征能参与更新、参数发布、导航和可视化

4. **CATIBuild 错误处理**：使用 `CATTry/CATCatch` 宏 + `CATMfErrUpdate` + `CATIUpdateError::SetUpdateError` 的标准错误处理链

5. **Body 获取双路径**：优先 `CATIGeometricalElement::GetBodyResult`，回退 `CATIMfBRep::CreateBody(MfWithTemporaryBody)`

6. **Catalog 三接口**：`CATICatalogEnable`（启用）、`CATICatalogInstantiation`（实例化）、`CATICatalogSynchronize`（同步）

7. **BRep 特征自动聚合**：当 SetCurve 的输入是 BRep 特征且无 Father 时，自动调用 `CATIDescendants::Append` 聚合

---

## AI Agent 学习要点

1. **自定义机械特征需要至少实现三个 DataExtension**：接口实现、CATIBuild、CATIMf3DBehavior

2. **CATIBuild 是特征更新的唯一入口**，每次 `Update()` 调用都会触发。必须正确处理首次计算和重新计算的差异

3. **BRep 特征（如 Pad）必须被聚合到父特征下**，通过 `CATIDescendants::Append` 或 `CATIMfBRep::Aggregate`

4. **Provider 模式是扩展特征的基础设施**——没有 Provider，扩展特征将无法在特征树中显示或更新

5. **错误报告使用 CATMfErrUpdate + CATThrow** 抛出，系统会自动处理 Update 循环中的错误传播

6. **Catalog 支持需要三个接口**：Enable（可被存入）、Instantiation（可被创建）、Synchronize（可被更新）

7. **非几何特征（如 MultiMeasure）派生自 MechanicalElement**，不实现 CATIGeometricalElement，只能有参数没有 Body