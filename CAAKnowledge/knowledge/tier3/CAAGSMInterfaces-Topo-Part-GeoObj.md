---
module: "CAAGSMInterfaces.edu / CAATopologicalOperators.edu / CAAPartInterfaces.edu / CAAGeometricObjects.edu"
category: "CAA 曲面/拓扑/Part/几何 — GSD服务/Build生命周期/拓扑日志/几何属性"
tier: "3"
status: "已完成"
---

# CAAGSMInterfaces / CAATopologicalOperators / CAAPartInterfaces / CAAGeometricObjects

## 模块定位

这四个项目分别展示了 CAA 建模中四个不同层次的 API 使用模式：

| 项目 | 层次 | 教学内容 |
|------|------|---------|
| **CAAGSMInterfaces** | GSD 曲面 | 14 种曲面创建/操作 API 的批量封装 |
| **CAATopologicalOperators** | 拓扑操作 | 拓扑日志（Journal）的遍历、检查和可视化 |
| **CAAPartInterfaces** | Part 特征 | CATIBuild 的完整实现：BuildShape → ProcReport → Boolean → Store |
| **CAAGeometricObjects** | 几何属性 | 几何工厂中的属性创建和管理 |

它们共同构成了"从曲面 API 调用 → 拓扑操作 → Part 特征 Build 实现 → 几何属性管理"的完整建模知识链。

---

## 一、CAAGSMInterfaces.edu — GSD 曲面接口

### 核心架构

```
CAAGsiServices（服务封装类）
  ├── CreatePrism(profile, direction, start, end)    — 拉伸
  ├── CreateRevol(profile, axis, angle1, angle2)      — 旋转
  ├── CreateSweep(profile, guide)                     — 扫掠
  ├── CreateLoft(sections, guides, spine)             — 放样
  ├── CreateFill(closureProfiles, support)            — 填充
  ├── CreateBlendCorner(support1, support2)           — 圆角
  ├── CreateOffset(support, offset, side)             — 偏移
  ├── CreateSewSurface(listOfBodies, tolerance)       — 缝合
  ├── CreateJoin(listOfBodies)                        — 接合
  ├── CreateSplit(bodyToSplit, cuttingBody)           — 分割
  ├── CreateBoundary(body, limits)                    — 边界
  ├── CreateSymmetry(body, reference)                 — 对称
  ├── CreateCloseSurface(body)                        — 封闭曲面
  └── CreateLawDistProj(bodyToProject, support)       — 法则投影

CAAGsiServicesBody（Body 级操作）
  └── CreateJoin(listOfBodies)                        — 接合多个 Body

CAAGsiServicesJournal（日志管理）
  └── ManageResult + Journal 同步

CAAGsiUserTools（用户工具）
  └── GetGSMTool(pFeature) → 返回 GSM 工具的 ISpecObject

CAAGsiToolkit（工具集）
  └── 辅助函数
```

### 关键接口

| 接口 | 用途 |
|------|------|
| **CATIGSMFactory** | GSM 曲面工厂（创建 Prism/Revol/Sweep/Loft 等） |
| **CATISpecObject** | 特征的 ISpecObject 句柄 |
| **CATBody** | 几何 Body（结果几何） |
| **CATIMfProcReport** | 过程化报告 |

### 典型使用模式

```cpp
// 1. 获取 GSM 工厂
CATIGSMFactory *piGSMFactory = ...;  // 从 Part 容器获取

// 2. 创建输入几何（Profile 曲线）
CATISpecObject *pProfile = ...;
CATISpecObject *pDirection = ...;

// 3. 创建 Prism（拉伸）
CATISpecObject *pPrism = piGSMFactory->CreatePrism(
    pProfile, pDirection, 0.0, 50.0);

// 4. 获取结果 Body
CATIGeometricalElement *pGeom = ...;
CATBody *pResultBody = pGeom->GetBodyResult();
```

---

## 二、CAATopologicalOperators.edu — 拓扑操作

### 核心概念：拓扑日志（Journal）

拓扑操作（Boolean、Fillet、Draft 等）会生成 **Journal**，记录了输入几何和输出几何之间的映射关系：

```
原始 Body ──Boolean──> 结果 Body
   │                      │
   Face1 ──────────────> Face1'
   Face2 ──────────────> Face2' (modified)
   Face3 ──────────────> Face3' + Face4' (split)
   Face5 ──────────────> (deleted)
```

Journal 条目记录了这种映射，对下游操作（标注、约束）至关重要。

### 核心 API

**CATCGMJournalList — 拓扑日志列表**：
```cpp
class CATCGMJournalList {
    CATCGMJournal *GetFirst();          // 获取第一个条目
    CATCGMJournal *GetNext(previous);   // 获取下一个条目
    int Size();                         // 条目数量
};

class CATCGMJournal {
    CATCGMJournal::Type Type;           // 创建/修改/删除
    CATCell *pInputCell;                // 输入 Cell
    CATCell *pOutputCell;               // 输出 Cell
    CATCell *pSupportCell;              // 支撑 Cell
};
```

**CAATopDumpJournal — 打印日志内容**：
```cpp
// 全局函数
ExportedByCAATopDumpJournal 
int CAATopDumpJournal(CATCGMJournalList *iJournal);

// 遍历每个条目，根据 Type 输出对应信息
// Type = Creation → "Creation of cell <output> from cell <input>"
// Type = Modification → "Modification of cell <input> into cell <output>"
// Type = Deletion → "Deletion of cell <input>"
```

**CAATopCheckJournal — 验证日志一致性**：
```cpp
ExportedByCAATopCheckJournal
int CAATopCheckJournal(CATCGMJournalList *iJournal);

// 验证规则：
// 1. 输入 Cell 必须在原始 Body 中存在
// 2. 输出 Cell 必须在结果 Body 中存在
// 3. 不应有孤立的 Cell
```

### 使用模式

```cpp
// 1. 执行拓扑操作
CATDynBoolean *pBoolOp = CATDynCreateBoolean(piGeomFactory, pTopData, body1, body2, CATBoolUnion);

// 2. 获取 Journal
CATCGMJournalList *pJournal = pBoolOp->GetJournal();

// 3. 检查 Journal
CAATopCheckJournal(pJournal);

// 4. 打印 Journal
CAATopDumpJournal(pJournal);

// 5. 删除操作
pBoolOp->Delete();
```

---

## 三、CAAPartInterfaces.edu — Part 特征 Build 生命周期

### CATIBuild 的完整 7 步流程

这是 CAAPriBuildUserPad 展示的 **CATIBuild::Build()** 标准实现模式：

```
Step 0: BuildShape()     — 调用 CATIBuildShape 创建特征的基础几何
Step 1: UnsetUpdateError — 清除上一次更新的错误标记
Step 2: 获取数据          — ResultIN (上一个特征的 Body)、ResultOUT (当前特征的输出)
Step 3: CreateProcReport — 创建过程化报告
Step 4: 运行拓扑操作       — 如 Boolean Union
Step 5: StoreProcReport   — 存储过程化报告
Step 6: 清理              — 删除临时数据
Step 7: 错误处理          — CATTry/CATCatch 捕获并设置 UpdateError
```

**完整代码结构**：
```cpp
HRESULT CAAPriEBuild::Build() {
    // === 声明指针（在 Try/Catch 中使用的必须在外部声明）===
    CATIUpdateError *piUpdateErrorOnThis = NULL;
    CATIMfProcReport *piProcReport = NULL;
    CATGeoFactory *piGeomFactory = NULL;
    CATDynBoolean *pOperatorBool = NULL;

    rc = QueryInterface(IID_CATIUpdateError, (void**)&piUpdateErrorOnThis);

    CATTry {
        // === Step 0: 创建特征形状 ===
        CATIBuildShape *piBuildShape = NULL;
        rc = QueryInterface(IID_CATIBuildShape, (void**)&piBuildShape);
        int val = piBuildShape->BuildShape();  // 可以抛出错误
        piBuildShape->Release();

        // === Step 1: 清除更新错误 ===
        piUpdateErrorOnThis->UnsetUpdateError();

        // === Step 2: 获取数据 ===
        CATIShapeFeatureBody *pIShapeFeatureBody = NULL;
        rc = QueryInterface(IID_CATIShapeFeatureBody, (void**)&pIShapeFeatureBody);

        // 获取 ResultIN（前驱特征的 Body）
        CATListValCATBaseUnknown_var *pListBodyIn = pIShapeFeatureBody->GetBodyIN("CATBody");

        // 获取 ResultOUT 并清除旧数据
        CATISpecObject_var spResultOUT = pIShapeFeatureBody->GetResultOUT();
        CATIGeometricalElement *pGeomResultOUT = ...;
        pGeomResultOUT->DeleteScope();

        // 获取 Body
        CATBody *pBodyResultIN = ...;
        CATBody *pBodyResultOUT = ...;

        // 获取几何工厂
        CATIContainerOfDocument *pCont = ...;
        piGeomFactory = pCont->GetGeometryContainer();

        // === Step 3: 创建 Procedural Report ===
        piProcReport = ...;
        CATListPtrCATISpecAttribute listKeys;
        piProcReport->CreateProcReport(pListBodyIn, listKeys, BOOL_UNION);

        // 获取拓扑日志
        CATCGMJournalList *pJournal = piProcReport->GetCGMJournalList();

        // === Step 4: 运行拓扑操作 ===
        CATSoftwareConfiguration *pSoftConfig = new CATSoftwareConfiguration();
        CATTopData TopData(*pSoftConfig);
        pOperatorBool = CATDynCreateBoolean(piGeomFactory, &TopData,
            pBodyResultIN, pBodyResultOUT, CATBoolUnion);
        pOperatorBool->Run();

        // === Step 5: 存储 Procedural Report ===
        CATBody *pResultBody = pOperatorBool->GetResult();
        piProcReport->StoreProcReport(pResultBody, CATMfBRepDefs::NoCopy, BOOL_UNION);

        // === Step 6: 清理 ===
        pOperatorBool->Delete();
        delete pSoftConfig;

    } CATCatch(CATMfErrUpdate, pError) {
        // === Step 7a: 处理 MechanicalModeler 错误 ===
        piUpdateErrorOnThis->SetUpdateError(pError);
        rc = E_FAIL;
    } CATCatch(CATError, pError) {
        // === Step 7b: 处理其他错误 ===
        CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
        pErrorToThrow->SetDiagnostic(pError->GetNLSMessage());
        piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);
        rc = E_FAIL;
    }
    CATEndTry

    piUpdateErrorOnThis->Release();
    return rc;
}
```

### 关键接口

| 接口 | 用途 |
|------|------|
| **CATIBuildShape** | `BuildShape()` 创建特征的基本形状 |
| **CATIShapeFeatureBody** | `GetBodyIN()` / `GetResultOUT()` / `SetResultOUT()` |
| **CATIMfProcReport** | `CreateProcReport` / `GetCGMJournalList` / `StoreProcReport` |
| **CATIUpdateError** | `UnsetUpdateError` / `SetUpdateError` |
| **CATMfErrUpdate** | 机械建模错误对象 |
| **CATIGeometricalElement** | `DeleteScope()` 删除旧几何 |
| **CATDynBoolean** | `Run()` / `GetResult()` 布尔操作 |

---

## 四、CAAGeometricObjects.edu — 几何属性

### 核心概念

在 CATGeoFactory 中创建的几何对象（Point, Line, Circle, Body 等）可以携带**自定义属性**：

```
CATGeoFactory
  ├── CATPoint (属性: "Color"=Red, "Layer"=1)
  ├── CATLine (属性: "Style"=Dashed)
  └── CATBody
        ├── CATFace (属性: "Tolerance"=0.001)
        └── CATEdge (属性: "FilletRadius"=5.0)
```

### 属性管理接口

| 接口/类 | 用途 |
|---------|------|
| **CAAGobAttributeManagement** | 属性管理器（创建、查询、修改、删除属性） |
| **CATCGMJournalList** | 用于记录属性修改的日志 |
| **CATUnicodeString** | 属性值的类型 |

### 属性操作流程

```cpp
// 1. 在 CATGeoFactory 中创建几何对象
CATGeoFactory *pFactory = ...;
CATPoint *pPoint = pFactory->CreatePoint(10.0, 20.0, 30.0);

// 2. 创建属性管理器
CAAGobAttributeManagement attrMgr;

// 3. 为几何对象添加属性
attrMgr.AddAttribute(pPoint, "Color", "Red");
attrMgr.AddAttribute(pPoint, "Layer", "1");

// 4. 查询属性
CATUnicodeString color;
attrMgr.GetAttribute(pPoint, "Color", color);  // "Red"

// 5. 修改属性
attrMgr.ModifyAttribute(pPoint, "Color", "Blue");

// 6. 删除属性
attrMgr.RemoveAttribute(pPoint, "Layer");
```

---

## 关键接口速查

| 框架 | 接口/类 | 用途 |
|------|---------|------|
| GSD | **CATIGSMFactory** | 创建 14 种曲面特征 |
| GSD | **CAAGsiServices** | 14 种曲面的封装服务 |
| Topo | **CATCGMJournalList** | 拓扑日志列表 |
| Topo | **CATCGMJournal** | 单个日志条目（Type/Input/Output/Support） |
| Topo | **CAATopDumpJournal** | 打印日志内容 |
| Topo | **CAATopCheckJournal** | 验证日志一致性 |
| Part | **CATIBuildShape** | 创建特征形状 |
| Part | **CATIShapeFeatureBody** | BodyIN/ResultOUT 管理 |
| Part | **CATIMfProcReport** | 过程化报告 |
| Part | **CATIUpdateError** | 更新错误管理 |
| Part | **CATDynBoolean** | 布尔操作 |
| Part | **CATSoftwareConfiguration** | 拓扑操作配置 |
| GeoObj | **CAAGobAttributeManagement** | 几何属性管理 |
| GeoObj | **CATGeoFactory** | 几何对象工厂 |

---

## 设计模式总结

1. **服务封装模式**（GSD）：`CAAGsiServices` 将 14 种曲面 API 封装为统一的服务类，简化调用

2. **Journal 遍历模式**（Topo）：`GetFirst() → GetNext()` 迭代器模式遍历日志条目，按 Type 分类处理

3. **Build 7 步标准模式**（Part）：BuildShape → UnsetError → GetData → CreateProcReport → RunOp → StoreProcReport → Clean

4. **CATTry/CATCatch 错误处理**（Part）：分层捕获 CATMfErrUpdate 和 CATError，统一设置 UpdateError

5. **属性标签模式**（GeoObj）：为几何对象附加键值对属性，支持增删改查

---

## AI Agent 学习要点

1. **GSM 曲面创建统一通过 CATIGSMFactory**，14 种曲面类型各有对应的 Create 方法

2. **拓扑日志是过程化建模的核心**——每个拓扑操作生成 Journal，下游操作通过 Journal 找到对应的 Cell 映射

3. **BuildShape() 和 Build() 是两个层次**：BuildShape 创建形状几何，Build 管理 ProcReport 和拓扑操作

4. **ResultIN/ResultOUT 模式**：`GetBodyIN()` 获取前驱特征的 Body，`GetResultOUT()` 获取/设置当前特征的输出特征

5. **ProcReport 必须在拓扑操作前后配对使用**：`CreateProcReport` 在操作前，`StoreProcReport` 在操作后

6. **DeleteScope() 清除旧几何**：在重新计算前必须调用，否则旧几何会残留

7. **CATCGMJournal 的 Type 有三种**：Creation（新 Cell 从旧 Cell 创建）、Modification（旧 Cell 被修改）、Deletion（旧 Cell 被删除）