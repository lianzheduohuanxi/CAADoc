---
module: "CAAV5V6ObjectSpecsModeler / CAASketcherInterfaces / CAAFreeFormOperators / CAAElecFlatteningItf / CAAElecHarnessItf"
category: "CAA V5V6 OSM / 草图 / 自由曲面 / 电气展平 / 电气线束"
tier: "3-6"
status: "已完成"
---

# CAAV5V6ObjectSpecsModeler / Sketcher / FreeForm / ElecFlattening / ElecHarness

---

## 一、CAAV5V6ObjectSpecsModeler.edu — V5/V6 OSM 扩展

### 模块定位

CAAV5V6ObjectSpecsModeler 是 CAAObjectSpecsModeler 的 V5/V6 双版本扩展，展示了 V5 和 V6 在特征行为自定义方面的差异。

### 核心知识

**1. CATFmFeatureCustomizationAdaptor — V6 的行为定制基类**

V5 使用 `CATBaseUnknown` 作为 DataExtension 基类，V6 使用 `CATFmFeatureCustomizationAdaptor`：

```cpp
// V6 的 BehaviorCustomization 继承自 CATFmFeatureCustomizationAdaptor
class CAAEV5V6OsmBehaviorCustomizationAdd : public CATFmFeatureCustomizationAdaptor {
    CATDeclareClass;
public:
    virtual HRESULT Build();  // 只需实现 Build
};

// V5 版本使用 CATBaseUnknown + TIE_CATIBuild
// V6 版本使用 CATFmFeatureCustomizationAdaptor + TIE_CATIFmFeatureBehaviorCustomization
```

**2. BehaviorCustomizationAdd — Sum = First + Second**

```cpp
// CAAOsmAdd 的 Build：Sum = First + Second
HRESULT CAAEV5V6OsmBehaviorCustomizationAdd::Build() {
    CATISpecAttrAccess *piAccess = ...;
    CATISpecAttrKey *piKeyFirst = piAccess->GetAttrKey("First");
    CATISpecAttrKey *piKeySecond = piAccess->GetAttrKey("Second");
    CATISpecAttrKey *piKeySum = piAccess->GetAttrKey("Sum");
    
    int f = piAccess->GetInteger(piKeyFirst);
    int s = piAccess->GetInteger(piKeySecond);
    piAccess->SetInteger(piKeySum, f + s);
}
```

**3. BehaviorCustomizationSquare — Square = Num²**

```cpp
// CAAOsmSquare 的 Build：Square = Num²
HRESULT CAAEV5V6OsmBehaviorCustomizationSquare::Build() {
    int n = piAccess->GetInteger(piKeyNum);
    piAccess->SetInteger(piKeySquare, n * n);
}
```

**4. Extension Illustration 服务**

```cpp
// V5 版本
int CAAV5V6OsmIllustrateExtensions(
    const char *pExtensionsCatalog1Name,
    const char *pExtensionsCatalog2Name,
    const char *pFeatureCatalogName,
    const char *pDocumentStorageName);

// V6 版本（额外参数：环境、仓库）
int CAAV5V6FmExtIllustrateExtensions(
    const char *pExtensionsCatalog1Name,
    const char *pExtensionsCatalog2Name,
    const char *pFeatureCatalogName,
    CATString iEnvToUse,
    CATString iRepository);
```

### 关键对比

| 方面 | V5 (CAAObjectSpecsModeler) | V6 (CAAV5V6ObjectSpecsModeler) |
|------|---------------------------|-------------------------------|
| 基类 | `CATBaseUnknown` | `CATFmFeatureCustomizationAdaptor` |
| Build 接口 | `CATIBuild` via TIE | `CATIFmFeatureBehaviorCustomization` via TIE |
| 会话 | `Create_Session` | `CAAAdpCreateSession` (PLM) |

---

## 二、CAASketcherInterfaces.edu — 草图接口

### 状态

仅包含 `IdentityCard.h` 和 `CAASkiBasicGeometries.m/Imakefile.mk`，无源代码文件。这是一个**框架定义项目**（接口声明），实际实现在 CATIA 平台内部。

### 教学内容（推断）

根据命名 `CAASkiBasicGeometries`（Sketcher Basic Geometries），该项目应该涵盖：
- 草图中的基本几何体（Point, Line, Circle, Arc, Spline）的创建 API
- `CATISketch` / `CATI2DWFFactory` 等草图接口的使用

---

## 三、CAAFreeFormOperators.edu — 自由曲面操作

### 状态

仅包含 3 个 `.m` 模块的 `Imakefile.mk`，无源代码。这是一个**框架定义项目**。

### 模块列表

| 模块 | 推断教学内容 |
|------|------------|
| **CAACrvFittingToNurbsCrv** | 曲线拟合到 NURBS |
| **CAAFrfInDegree** | NURBS 升阶（增加控制点） |
| **CAASurFittingToNurbsSur** | 曲面拟合到 NURBS |

### 核心 API（推断）

- `CATNurbsCurve` / `CATNurbsSurface` — NURBS 曲线/曲面
- `CATFrFittingToNurbsCrv` — 曲线拟合算子
- `CATFrFittingToNurbsSur` — 曲面拟合算子
- `CATFrFIncreaseDegree` — 升阶算子

---

## 四、CAAElecFlatteningItf.edu — 电气展平

### 模块定位

电气线束展平（Flattening）接口，用于将 3D 线束展平为 2D 制造图纸。

### 模块列表

| 模块 | 推断教学内容 |
|------|------------|
| **CAAEhfFlattenManager** | 展平管理器 |
| **CAAEhfFlattenManagerExtract** | 展平结果提取 |
| **CAAEhfFlatteningParameters** | 展平参数 |
| **CAAEhfFlatteningParametersCreate** | 展平参数创建 |
| **CAAEhfGreenLineMechPartAndSupportInBNS** | 绿线（机械件+支撑在 BNS 中） |
| **CAAEhfUIPArrangeJunction** | 节点排列 UI |

### 核心接口

**CAAEhfUIPArrangeJunction — 节点方向排列**：
```cpp
class CAAEhfUIPArrangeJunction : public CATBaseUnknown {
    CATDeclareClass;
public:
    // 在展平平面上，为每个 Bundle Segment 端点检索用户方向
    HRESULT RetrieveUserDirection(
        const CATListPtrCATBaseUnknown & iListOfBundleSegmentExtremity,
        const CATMathPlane             & iFlatteningPlane,
        CATLISTP(CATMathVector)        & ioListOfDirections);
};
```

**关键概念**：
- **Bundle Segment**：线束段
- **Flattening Plane**：展平平面（2D 投影面）
- **Green Line**：展平图中的绿色参考线（机械件与支撑对齐）
- **BNS**：Branch Node System（分支节点系统）
- **Junction**：线束节点（连接点）

---

## 五、CAAElecHarnessItf.edu — 电气线束

### 模块定位

电气线束接口，定义线束物理属性计算和几何模型。

### 核心知识

**1. CATIEhiFLEX — 等效弹性模量计算**

```cpp
class CAAGetFLEXEquivalentModulusExt : public CATBaseUnknown {
    CATDeclareClass;
public:
    // 计算 Bundle Segment 的等效弹性模量
    HRESULT GetFLEXEquivalentModulus(
        CATListValCATBaseUnknown_var * ipListOfWireWireGroup,        // 线/线组列表
        CATListValCATBaseUnknown_var * ipOrderedListOfProtectionReference, // 保护层列表
        CATListValCATBaseUnknown_var * ipInternalSpliceReferenceList,     // 内部接头列表
        CATEhiProfileType              iProfile,                      // 截面类型
        double                         iProfileLength1,               // 截面长轴 (mm)
        double                         iProfileLength2,               // 截面短轴 (mm)
        int                            iBundleSegmentFlexibility,     // 柔韧性
        double                       & oYoungModulusEquivalent,       // 等效杨氏模量 (N/m²)
        double                       & oEquivalentRatioToBend,        // 等效弯曲比
        double                       & oEquivalentRatioToTwist);      // 等效扭转比
};
```

**计算公式（推断）**：
```
E_eq = f(Σ(E_i * A_i), profile_type, L1, L2, flexibility)
RatioToBend = g(E_eq, profile_geometry)
RatioToTwist = h(E_eq, profile_geometry)
```

**2. 模块列表**

| 模块 | 教学内容 |
|------|---------|
| **CAAEhiBundleSegment** | 基本 Bundle Segment |
| **CAAEhiCreateBranchableBundleSegment** | 可分支 Bundle Segment |
| **CAAEhiCreateMultiBranchableBundleSegment** | 多分支 Bundle Segment |
| **CAAEhiFLEXComputeBundleSegment** | 弹性计算 |
| **CAAEhiFLEXImpl** | 弹性计算实现（CAAGetFLEXEquivalentModulusExt） |
| **CAAEhiGeoBundle** | 几何 Bundle |
| **CAAEhiMultiBundleSegment** | 多 Bundle Segment |
| **CAAEhiNetwork** | 网络拓扑 |
| **CAAEhiProtection** | 保护层 |
| **CAAEhiCreateAndManageProtection** | 保护层创建管理 |
| **CAAEhiCreateAndManageSupport** | 支撑创建管理 |

### 线束层次模型

```
Network (网络)
  └── BundleSegment (线束段)
        ├── Profile: 截面形状和尺寸 (L1 x L2)
        ├── Flexibility: 柔韧性等级
        ├── Wire(s) / WireGroup(s): 包含的导线/导线组
        ├── Protection(s): 保护层（有序列表，从内到外）
        └── Internal Splice(s): 内部接头
             │
             等效弹性模量计算
             ├── YoungModulusEquivalent (等效杨氏模量)
             ├── EquivalentRatioToBend (等效弯曲比)
             └── EquivalentRatioToTwist (等效扭转比)
```

---

## AI Agent 学习要点

1. **V5→V6 迁移的核心变化**：基类从 `CATBaseUnknown` 变为 `CATFmFeatureCustomizationAdaptor`，接口从 `CATIBuild` 变为 `CATIFmFeatureBehaviorCustomization`

2. **电气展平的核心是平面投影**：`CATMathPlane` 定义展平平面，`CATMathVector` 表示方向

3. **线束弹性模量是复合计算**：输入包括导线列表、保护层列表、截面尺寸、柔韧性——输出等效杨氏模量、弯曲比、扭转比

4. **CAAV5V6FmExtIllustrateExtensions 比 V5 版本多了 iEnvToUse 和 iRepository 参数**——反映了 V6 的 PLM 环境需求

5. **Sketcher 和 FreeForm 是接口框架项目**——实际实现在 CATIA 平台内部，.edu 项目仅提供教学接口声明