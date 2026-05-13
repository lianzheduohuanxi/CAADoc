---
module: "CAAVisualization.edu"
category: "CAA 可视化管线 — Model/Visu 分离 + CATVisManager"
tier: "1"
status: "已完成"
---

# CAAVisualization.edu — 可视化管线

## 模块定位

CAAVisualization 展示了 CAA 的**可视化架构核心**：将数据模型（Model）与图形表现（Visu）彻底分离，通过 CATVisManager 在渲染时将两者桥接起来。

本模块包含**两套可视化框架**：
1. **CAAVisBasics** — 基础级：直接加载 CGR 文件渲染，无模型/可视分离
2. **CAAVisManager** — 管理器级：完整的 Model/Visu 分离架构，通过接口和扩展实现

**与 CAASystem 的关系**：CAAEVisVisuRootObject 是连接 CAASystem 数据模型（几何元素）与可视化管线的桥梁——遍历 CAAISysCollection 中的对象，通过 CATVisManager 逐个生成图形表现。

---

## 架构总览

```
┌──────────────────────────────────────────────────────────────┐
│                    CATVisManager                              │
│  BuildRep(ModelIdentificator) → CAT3DRep                     │
│      │                                                        │
│      │  对每个组件查找 CATI3DGeoVisu 扩展                       │
│      ▼                                                        │
│  ┌──────────────────────────────────────────────────────┐    │
│  │             Visu 扩展层 (CATExtIVisu)                  │    │
│  │                                                        │    │
│  │  CAAEVis3DGeoVisuForCGRObject::BuildRep()             │    │
│  │  CAAEVis3DGeoVisuForCuboid::BuildRep()                │    │
│  │  CAAEVis3DGeoVisuForSphere::BuildRep()                │    │
│  │  CAAEVisVisuRootObject::BuildRep() ← 遍历 CAASystem    │    │
│  └──────────────────────────────────────────────────────┘    │
│      │                                                        │
│      │  QueryInterface 读取 Model 数据                         │
│      ▼                                                        │
│  ┌──────────────────────────────────────────────────────┐    │
│  │              Model 接口层 (ProtectedInterfaces)        │    │
│  │                                                        │    │
│  │  CAAIVisModelObject — 父子树 (8 methods)               │    │
│  │  CAAIVisModelCGRObject — CGR 文件 (2 methods)          │    │
│  │  CAAIVisModelCuboid — 8 顶点 (2 methods)               │    │
│  │  CAAIVisModelSphere — 球心+半径 (4 methods)            │    │
│  │  CAAIVisModelSetOfObject — 类型标记 (empty)            │    │
│  └──────────────────────────────────────────────────────┘    │
│      │                                                        │
│      │  数据来源                                              │
│      ▼                                                        │
│  ┌──────────────────────────────────────────────────────┐    │
│  │              组件层 (Components)                       │    │
│  │  CAAVisModelCGRObject, CAAVisModelCuboid,              │    │
│  │  CAAVisModelSphere, ...                                │    │
│  └──────────────────────────────────────────────────────┘    │
└──────────────────────────────────────────────────────────────┘
```

**关键设计**：Model 接口定义「有什么数据」，Visu 扩展定义「怎么画」。
同一个 Model 可以有多个 Visu 实现（如 2D 符号图和 3D 实体渲染）。

---

## 两套可视化框架对比

| | CAAVisBasics | CAAVisManager |
|---|---|---|
| **复杂度** | 低 — 教学入门 | 高 — 生产级模式 |
| **Model/Visu 分离** | ❌ 直接操作 Rep | ✅ 接口分离 |
| **扩展机制** | 无 | DataExtension + TIE |
| **Application 基类** | CATInteractiveApplication | CATInteractiveApplication |
| **Document 基类** | CATBaseUnknown | CATBaseUnknown |
| **View** | CATDlgDialog + CATNavigation3DViewer | CAAVisManagerWindow + CATNavigation3DViewer |
| **典型用途** | 快速加载 CGR 文件 | 构建可扩展的模型树 |

---

## 核心接口详解

### 1. Model 层 — CAAIVisModelObject

```
基类: CATBaseUnknown | 8 个方法
```

```cpp
virtual list<CATBaseUnknown> *GetChildren() = 0;
virtual list<CATBaseUnknown> *GetParents()  = 0;
virtual HRESULT GetType(char ** oType)       = 0;
virtual HRESULT SetType(const char * iType)  = 0;
virtual HRESULT AddChild(CATBaseUnknown *)   = 0;
virtual HRESULT RemChild(CATBaseUnknown *)   = 0;
virtual HRESULT AddParent(CATBaseUnknown *)  = 0;
virtual HRESULT RemParent(CATBaseUnknown *)  = 0;
```

**设计意图**：定义一个**所有权树**（ownership tree）。每个可视化对象可以有多个父节点和子节点，构成一个 DAG（有向无环图）。这是 CAA 中表示装配关系的标准模式。

实现类 `CAAEVisModelObject` 内部维护两个 `list<CATBaseUnknown>`：
- `_Parents` — 父节点列表
- `_Children` — 子节点列表

### 2. Model 层 — 几何类型接口

| 接口 | 方法 | 数据 |
|------|------|------|
| CAAIVisModelCGRObject | GetCGRRep, ReadCGRFile | CAT3DRep（从 CGR 文件加载） |
| CAAIVisModelCuboid | GetVertices, SetVertices | float[24]（8 顶点 × 3 坐标） |
| CAAIVisModelSphere | SetCenter/GetCenter, SetRadius/GetRadius | CATMathPointf + float |
| CAAIVisModelSetOfObject | (空接口) | 类型标记：一组对象 |

### 3. Visu 层 — CATI3DGeoVisu 接口

这是 CAA 框架级接口（定义在 Visualization 框架中，非本模块）：

```cpp
virtual CATRep * GetRep();       // 获取已缓存的 Rep
virtual CATRep * BuildRep();     // 从头构建 Rep
virtual void UnreferenceRep();   // 释放 Rep 引用
```

**CATExtIVisu 适配器**：框架提供的基类，已实现 GetRep 和 UnreferenceRep。
扩展只需覆盖 BuildRep()。

### 4. Visu 层 — 专用可视化接口

| 接口 | 基类 | 方法 | 用途 |
|------|------|------|------|
| CAAIVis2DGraphVisu | CATIVisu | GetPositioningMatrix, IncrementPositioningMatrix | 2D 符号图（灰框+名称） |
| CAAIVisHistogramChartVisu | CATIVisu | (空接口) | 柱状图标记 |
| CAAIVisTextModel | CATBaseUnknown | SetGraphicRepresentation | 文本模型 |
| CAAIVisWireBox | CATBaseUnknown | SetDimBox/GetDimBox, SetCenterBox/GetCenterBox | 线框盒（用于裁剪） |

### 5. 对象类型枚举 — CAAVisObjectType

```cpp
typedef enum _CAAVisObjectType {
   CAAVisSurfacicRep,    // 曲面表示
   CAAVisUnknownObject   // 未知类型
} CAAVisObjectType;
```

---

## 关键实现模式

### 模式 1: CATExtIVisu 扩展 — 为组件添加可视化

```cpp
// CAAEVis3DGeoVisuForCuboid.h
class CAAEVis3DGeoVisuForCuboid : public CATExtIVisu {
    CATDeclareClass;
    CATRep * BuildRep();  // 唯一需要覆盖的方法
};

// CAAEVis3DGeoVisuForCuboid.cpp
TIE_CATI3DGeoVisu(CAAEVis3DGeoVisuForCuboid);
CATImplementClass(CAAEVis3DGeoVisuForCuboid,
    DataExtension,         // ← 扩展类型
    CATBaseUnknown,
    CAAVisModelCuboid);    // ← 扩展目标组件

// interface dictionary:
// CAAVisModelCuboid  CATI3DGeoVisu  libCAAVisManagerImpl
```

`BuildRep()` 实现：通过 QueryInterface 读取组件的 Model 接口数据，构造 CAT3DRep。

### 模式 2: 多目标扩展 — CATBeginImplementClass + CATAddClassExtension

```cpp
// CAAEVisVisuRootObject.cpp — 同时扩展两个组件
CATBeginImplementClass(CAAEVisVisuRootObject,
    DataExtension, CATBaseUnknown, CAASysGeomRootObj);
CATAddClassExtension(CAASysSampRootObj);
CATEndImplementClass(CAAEVisVisuRootObject);
```

**设计意图**：同一个可视化扩展可以附加到多个不同类型的组件上，实现代码复用。

### 模式 3: CATVisManager 渲染管线

CAAEVisVisuRootObject::BuildRep 展示了完整的渲染管线：

```
1. QueryInterface(IID_CAAISysAccess) → GetContainer()
2. QueryInterface(IID_CAAISysCollection) → 遍历对象
3. 对每个对象: CATVisManager::GetVisManager() → BuildRep(Ident)
4. 收集子 Rep → 加入 BagRep → 返回
```

**CATModelIdentificator**：封装了组件指针的标识符，CATVisManager 用它查找对应的 Visu 扩展。

### 模式 4: 文档/视图/编辑器分离

```
CAAVisManagerDocument ──→ CAAVisManagerWindow (View)
                      └─→ CAAVisManagerEditor  (Controller)
                      └─→ _pRootContainer      (Model)
```

Application → 管理多个 Document → 每个 Document 有一个 Window → Window 内有 Viewer。

---

## 通知系统

CAAVisBasics 定义了丰富的通知类型，全部继承 CATNotification：

| 通知类 | 触发时机 |
|------|------|
| CAAVisBaseCreateObjectNotification | 创建可视化对象 |
| CAAVisBaseExitNotification | 退出应用 |
| CAAVisBaseInsertNotification | 插入模型 |
| CAAVisBaseManipulatorNotification | 操作器事件 |
| CAAVisBaseModifyViewpointNotification | 修改视点 |
| CAAVisBaseNewViewpointNotification | 新视点 |
| CAAVisBaseOpenNotification | 打开文档 |
| CAAVisBaseReframeNotification | 重新取景 |
| CAAVisBaseRenderBENotification | 渲染包围盒 |

通知通过 CATCommand 的 callback 机制传递，Application 在 AnalyseNotification 中分发。

---

## 与 CAASystem + CAAApplicationFrame 的关系

三个 Tier 1 模块构成完整的 CAA 应用骨架：

```
CAAApplicationFrame (UI 框架)
  └─ Workshop → Workbench → Addin → Command
       │
       │ 命令操作对象
       ▼
CAASystem (数据模型)
  └─ CAAISysCollection → CAAISysPoint/Line/...
       │
       │ QueryInterface 读取数据
       ▼
CAAVisualization (可视化)
  └─ CAAEVisVisuRootObject::BuildRep()
       │
       │ 遍历 Collection → BuildRep 每个对象
       ▼
  CATVisManager → CATNavigation3DViewer (屏幕渲染)
```

---

## 关键设计模式

| 模式 | CAA 实现 | 示例 |
|------|------|------|
| Model/Visu 分离 | 数据接口 + Visu 扩展分离 | CAAIVisModelCuboid + CAAEVis3DGeoVisuForCuboid |
| CATExtIVisu 适配器 | 框架基类简化 Visu 实现 | 只需覆盖 BuildRep() |
| 多目标扩展 | CATAddClassExtension | 同一个 Visu 扩展附加到多个组件 |
| 所有权树 | list<CATBaseUnknown> 父子关系 | CAAIVisModelObject |
| VisManager 桥接 | BuildRep(Ident) 按需渲染 | CATVisManager::BuildRep |
| 文档/视图/编辑器 | MVC 分离 | Document/Window/Editor |
| Application 基类 | CATInteractiveApplication | 自动管理事件循环 |

---

## 对 AI agent 的要点

1. **CAA 可视化的核心模式**：Model 接口定义数据 + Visu 扩展定义渲染 = CATVisManager 桥接
2. **CATExtIVisu 是标准适配器**：所有 3D 可视化扩展继承它，只覆盖 BuildRep()
3. **BuildRep 的典型实现**：QueryInterface 读 Model → 构造 CAT3DRep → 返回
4. **CATVisManager::BuildRep(Ident)** 是渲染入口，Ident 封装了组件指针
5. **多目标扩展**：CATBeginImplementClass + CATAddClassExtension + CATEndImplementClass
6. **所有权树**：CAAIVisModelObject 的 AddChild/RemChild 构建装配关系
7. **两个框架层次**：Basics 用于入门（直接 Rep 操作），Manager 用于生产（接口分离）
8. **通知传递**：Application::AnalyseNotification 接收所有子对象事件并分发