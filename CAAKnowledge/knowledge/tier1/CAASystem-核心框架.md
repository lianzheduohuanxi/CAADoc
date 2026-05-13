---
module: "CAASystem.edu"
category: "CAA 核心框架"
tier: "1"
status: "已完成"
---

# CAASystem.edu — CAA 系统核心框架

## 模块定位

CAASystem 是整个 CAA 示例中最核心的系统框架。它定义了一个**简化版 CATIA 文档模型**：
一个文档（CAAGeometry Document）包含一组几何元素（点、线、圆、平面等），
每个元素通过接口暴露其行为和属性。

**不是 CATIA 的真实实现**，而是**教学用的最小化示例**，完整展示了 CAA 的：
- 接口定义（Interface）
- 组件实现（Component）
- 扩展模式（Extension + TIE）
- 通知机制（Notification）
- QueryInterface 导航

---

## 架构总览

```
┌─────────────────────────────────────────────────────┐
│                CAAGeometry Document                  │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐  │
│  │ CAASysPoint │  │ CAASysLine  │  │CAASysCircle │  │
│  │ CAAISysPoint│  │ CAAISysLine │  │CAAISysCircle│  │
│  │ CAAISysName │  │ CAAISysName │  │ CAAISysName │  │
│  │CAAISysColor │  │CAAISysColor │  │CAAISysColor │  │
│  └─────────────┘  └─────────────┘  └─────────────┘  │
│         ▲  CAAISysCollection 管理列表  ▲             │
│  ┌──────────────────────────────────────────────┐   │
│  │  CAAISysAccess — 容器关联                      │   │
│  │  CAAISysCollection — 对象集合管理              │   │
│  │  CAAISysGeomFactory — 几何工厂                 │   │
│  └──────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────┘
```

**三层结构**：
1. **访问层** — CAAISysAccess 将文档容器与对象关联
2. **集合层** — CAAISysCollection 管理对象列表 + 通知
3. **对象层** — 每个几何对象通过多个接口暴露不同侧面

---

## 核心接口详解

### 1. 容器关联 — CAAISysAccess

```
IID: IID_CAAISysAccess | 基类: CATBaseUnknown
```

```cpp
virtual HRESULT SetContainer(CATBaseUnknown * iContainer) = 0;
virtual HRESULT GetContainer(CATBaseUnknown ** oContainer) = 0;
```

**设计意图**：CAA 的 Component（组件）本身是无上下文的。SetContainer 将组件
"放入"某个文档容器，使 QueryInterface 能够在组件上查找容器实现的接口。
这是 CAA 中最核心的**组件-容器关联模式**。

### 2. 对象集合 — CAAISysCollection

```
IID: IID_CAAISysCollection | 基类: CATBaseUnknown | 5 个方法
```

```cpp
virtual HRESULT GetNumberOfObjects(int * oCount) = 0;
virtual HRESULT GetObject(int iRank, CATBaseUnknown ** oObject) = 0;
virtual HRESULT AddObject(CATBaseUnknown * iObject) = 0;
virtual HRESULT RemoveObject(CATBaseUnknown * iObject) = 0;
virtual HRESULT Empty() = 0;
```

**设计意图**：集合接口不关心对象的具体类型（全部作为 CATBaseUnknown* 处理）。
调用者通过 QueryInterface 在取出的对象上查询需要的接口。这是 CAA 的
**多态集合模式**——集合存储基类指针，行为通过接口查询获得。

**通知机制**：当集合变空/变非空/元素增减时，发送三类通知：
- `CAASysCollectionEmptyNotif` — 集合变空
- `CAASysCollectionFilledNotif` — 集合变非空
- `CAASysCollectionModifNotif` — 元素增加/移除

通知继承链：
```
CATNotification
  └─ CAASysCollectionNotification
       ├─ CAASysCollectionEmptyNotif
       ├─ CAASysCollectionFilledNotif
       └─ CAASysCollectionModifNotif
```

### 3. 几何工厂 — CAAISysGeomFactory

```cpp
virtual HRESULT CreatePoint(double x, y, z, CATISysPoint ** oPoint) = 0;
virtual HRESULT CreateLine(double x1, y1, z1, x2, y2, z2, CATISysLine **) = 0;
virtual HRESULT CreateCircle(double cx, cy, cz, r, CATISysCircle **) = 0;
virtual HRESULT CreatePlane(double ox, oy, oz, CATISysPlane **) = 0;
virtual HRESULT CreateCuboid(double ox, oy, oz, CATISysCuboid **) = 0;
virtual HRESULT CreateCylinder(double ox, oy, oz, CATISysCylinder **) = 0;
virtual HRESULT CreateEllipse(double cx, cy, cz, ... CATISysEllipse **) = 0;
virtual HRESULT CreatePolyline(int n, CATMathPoint *, CATISysPolyline **) = 0;
```

**设计意图**：Factory 接口抽象了对象创建，隐藏具体实现类（如 CAASysPoint）。
调用者只依赖接口（CAAISysPoint），不依赖实现类。这是 CAA 的**工厂模式**。

### 4. 几何元素接口族

每个几何元素定义了独立的接口，全部继承 CATBaseUnknown：

| 接口 | 核心方法 |
|------|------|
| CAAISysPoint | GetCoord / SetCoord (3D坐标) |
| CAAISysLine | GetStartPoint / GetEndPoint / SetStartPoint / SetEndPoint |
| CAAISysCircle | GetCenter / SetCenter / GetRadius / SetRadius / GetPlanar |
| CAAISysPlane | GetOrigin / SetOrigin / GetFirstAxis / SetFirstAxis / GetSecondAxis / SetSecondAxis |
| CAAISysCuboid | GetOrigin / SetOrigin / GetX/Y/Z / SetX/Y/Z |
| CAAISysCylinder | GetOrigin / SetOrigin / GetFirst/SecondAxis / GetRadius / SetRadius |
| CAAISysEllipse | GetOrigin / SetOrigin / GetMajor/Minor / GetRatio / SetRatio |
| CAAISysPolyline | GetListPoint / SetListPoint / GetCloseStatus / SetCloseStatus |

**命名约定**：所有接口以 `CAAI` 前缀命名（CAA Interface），实现类以 `CAASys` 前缀。

### 5. 可视化属性 — 多接口叠加

一个几何对象可以同时实现多个属性接口：

```
CAASysPoint (组件)
  ├─ CAAISysPoint           ← 几何数据
  ├─ CAAISysName             ← 名称
  ├─ CAAISysColorProperties  ← RGB 颜色
  ├─ CAAISysPointProperties  ← 标记类型 (Dot/Cross/Plus/Star)
  └─ CAAISysTextureProperties ← 纹理（金属/粗糙度）
```

这是 CAA 的核心设计思想——**一个对象通过多个接口暴露不同侧面**，
而非单一继承树。调用者通过 QueryInterface 按需获取。

### 6. QueryInterface 导航 — CAAISysInterface

```cpp
virtual HRESULT SetNextObject(CATBaseUnknown *) = 0;
virtual HRESULT GetNextObject(CATBaseUnknown **) = 0;
```

在容器中实现，允许遍历集合中的所有对象并逐个查询接口。

---

## 实现模式

### 组件实现（Component）

```cpp
// CAASysPoint.h — 头文件
class CAASysPoint : public CATBaseUnknown {
    CATDeclareClass;  // 声明为 CAA 类
public:
    CAASysPoint();
    virtual ~CAASysPoint();
};

// CAASysPoint.cpp — 实现文件
CATImplementClass(CAASysPoint, Implementation, CATBaseUnknown, CATNull);
```

`CATImplementClass` 注册该类为**组件主类**（Implementation），CATNull 表示无扩展。

### 扩展实现（Extension + TIE）

```cpp
// CAAESysCreateInstanceForSurface.cpp
#include "TIE_CATICreateInstance.h"
TIE_CATICreateInstance(CAAESysCreateInstanceForSurface);  // 绑定接口

CATImplementClass(CAAESysCreateInstanceForSurface,
    CodeExtension,          // ← 扩展类型
    CATBaseUnknown,
    CAASysSurface);         // ← 扩展目标：CAASysSurface 组件

// 实现接口方法
HRESULT CAAESysCreateInstanceForSurface::CreateInstance(void ** oppv) {
    CAASysSurface * pt = new CAASysSurface();
    *oppv = (void *)pt;
    return S_OK;
}
```

**关键理解**：
- `CodeExtension` 表示该类是其他组件的**扩展**，不独立存在
- `TIE_XXX(ClassName)` 宏将接口方法委托给该类
- 需要在 interface dictionary 中声明：`CAASysSurface CATICreateInstance libXXX`
- 当 QueryInterface 在 CAASysSurface 上查询 CATICreateInstance 时，框架返回此扩展

---

## 组件基础设施

| 文件 | 作用 |
|------|------|
| CAASysGeoModelInf.h | 定义 `ExportedByCAASysGeoModelInf` 导出宏（dllimport/dllexport） |
| CAASysGeoModelComp.h | 定义 `ExportedByCAASysGeoModelComp` 导出宏 |
| CAASysComponentInt.h | 定义 `ExportedByCAASysComponentInt` 导出宏 |
| CAASysComponentCLSID.h | 声明 `CLSID_CAASysComponent`（用于 CATCreateInstance） |

每个组件库有独立的导出宏，控制符号的导入/导出。

---

## 关键设计模式

| 模式 | CAA 实现 | 示例 |
|------|------|------|
| 接口隔离 | 每个行为独立接口 | CAAISysPoint + CAAISysColorProperties 分离 |
| 工厂模式 | Factory 接口隐藏实现 | CAAISysGeomFactory::CreatePoint |
| 组件-容器 | SetContainer 建立关联 | CAAISysAccess::SetContainer |
| 多态集合 | 集合存 CATBaseUnknown* | CAAISysCollection::AddObject |
| 观察者 | Notification 子类化 | CAASysCollectionEmptyNotif |
| 扩展-TIE | CodeExtension + TIE 宏 | CAAESysCreateInstanceForSurface |
| QueryInterface | 运行时接口查询 | CAAISysInterface 遍历集合 |

---

## 对 AI agent 的意义

agent 可以从 CAASystem.edu 学到 CAA 最基础的编程范式：

1. **如何定义接口** — `CATDeclareInterface` + `ExportedBy` + `extern IID`
2. **如何实现组件** — `CATImplementClass(..., Implementation, ...)`
3. **如何实现扩展** — `CATImplementClass(..., CodeExtension, ...)` + `TIE_XXX`
4. **如何创建对象** — Factory 接口而非直接 new
5. **如何管理集合** — CATBaseUnknown* 多态集合 + QueryInterface
6. **如何发送通知** — CATNotification 子类化
7. **导出宏模式** — `ExportedByXXX` 控制 dllimport/dllexport

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CAAISysAccess.htm](../api-reference/interfaces/CAAISysAccess.htm)
- 完整方法签名: [api-reference/interfaces/CAAISysCollection.htm](../api-reference/interfaces/CAAISysCollection.htm)
- 完整方法签名: [api-reference/interfaces/CAAISysGeomFactory.htm](../api-reference/interfaces/CAAISysGeomFactory.htm)
- 完整方法签名: [api-reference/interfaces/CAAISysPoint.htm](../api-reference/interfaces/CAAISysPoint.htm)
- 完整方法签名: [api-reference/interfaces/CAAISysLine.htm](../api-reference/interfaces/CAAISysLine.htm)
- 完整方法签名: [api-reference/interfaces/CAAISysCircle.htm](../api-reference/interfaces/CAAISysCircle.htm)
- 完整方法签名: [api-reference/interfaces/CAAISysPlane.htm](../api-reference/interfaces/CAAISysPlane.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/](../use-cases/)
