# CAABasicTopoOpe — 基础拓扑操作

**模块**: CAABasicTopoOpe.edu | **层级**: Tier 7 | **规模**: 4 个文件（3 个 .cpp + 1 个 XML）

---

## 模块定位

CAABasicTopoOpe 演示 CATIA CGM **BasicTopologicalOpe** 框架的核心能力——将几何对象包装为拓扑体（Body），并使用拓扑算子进行操作。包含三个独立的批处理程序：
1. 在线段上计算点位置
2. 将曲线转换为 NURBS
3. 将曲面转换为 NURBS

---

## 架构概览

```
CAABasicTopoOpe.edu/
├── IdentityCard/
│   └── IdentityCard.xml      依赖: Mathematics, GeometricObjects,
│                                 NewTopologicalObjects, TopologicalOperators,
│                                 BasicTopologicalOpe, System
├── CAATopComputePointOnWire.m/src/
│   └── CAATopComputePointOnWire.cpp   在线段上计算点
├── CAATopCrvToNurbs.m/src/
│   └── CAATopCrvToNurbs.cpp           曲线 → NURBS
└── CAATopSurToNurbs.m/src/
    └── CAATopSurToNurbs.cpp           曲面 → NURBS
```

> 该项目没有任何头文件（.h），所有代码均为批处理 main 函数。

---

## 三个算子详解

### 1. CATComputePointOnWire — 线上定点

**功能**: 在线段（Wire）的指定参数位置处计算数学点，并创建可视化的笛卡尔坐标点。

**完整流程**:

```
步骤 1: 创建几何工厂 (CATCreateCGMContainer)
步骤 2: 创建 Wire
  ├── 创建几何圆 (CATGeoFactory::CreateCircle)
  │     radius=80, plane=YZ, angle=[π/2, 3π/2]
  ├── 定义 CATCrvLimits（曲线参数范围）和 CATOrientation（方向=正向）
  └── CATCreateTopWire(piGeomFactory, &topdata, 1, curves, limits, orients)
       → Run() → GetResult() → CATBody (拓扑体)
步骤 3: 创建线上定点算子
  └── CATCreateComputePointOnWire(piGeomFactory, &topdata,
        pWireBody, 0.5)   // 参数 0.5 = 线段中点
       → Run() → GetMathPoint(oPointOnWire)
步骤 4: 创建笛卡尔坐标点 (CreateCartesianPoint)
步骤 5: 清理（delete 算子, Release 配置）
步骤 6: 可选 — 保存为 .NCGM 文件
```

**关键 API**:
```cpp
// 创建 Wire 算子
CATTopWire *pWire1 = CATCreateTopWire(piGeomFactory, &topdata,
    1, ListOfCurves, CurLim, Orient);
pWire1->Run();
CATBody *pWireBody = pWire1->GetResult();

// 创建线上定点算子（参数 0.5 = 中点）
CATComputePointOnWire *pPointOnWire = CATCreateComputePointOnWire(
    piGeomFactory, &topdata, pWireBody, 0.5);
pPointOnWire->Run();

CATMathPoint oPointOnWire;
pPointOnWire->GetMathPoint(oPointOnWire);

// 创建可视化点
CATCartesianPoint *piCP1 = piGeomFactory->CreateCartesianPoint(oPointOnWire);
```

---

### 2. CATTopCrvToNurbsCrvOperator — 曲线转 NURBS

**功能**: 从 4 个控制点创建样条曲线（Spline），再将其转换为 NURBS 曲线。

**完整流程**:

```
步骤 1: 创建几何工厂
步骤 2: 创建 4 个拓扑点
  ├── CATCreateTopPointXYZ: (-20,0,0), (-20,5,0), (-10,5,0), (-10,0,0)
  └── 每个返回 CATBody*
步骤 3: 创建样条曲线体
  └── CATCreateTopSpline(piGeomFactory, &topdata, 4, aPoints)
       → CATBody* piSplineBody
步骤 4: 扫描拓扑域
  ├── GetNbDomains() → 验证 = 1
  ├── GetDomain(1) → CATDomain*
  └── GetAllCells(list, 1) → 获取所有 Edge（验证 = 1）
步骤 5: 创建 NURBS 转换算子
  └── CATCreateTopCrvToNurbsCrvOperator(piGeomFactory, &topdata,
        piSplineBody, listCells[1])
  ├── 调参: SetMaxDegree(2), SetMaxArcs(1),
  │          SetRationalAbility(0), Set3DOutputDimension(TRUE)
  ├── Run() → GetResult() → CATBody* pBody1
  └── delete 算子
步骤 6: 清理点体 (Remove with RemoveDependancies)
步骤 7: 可选保存 .NCGM
```

**NURBS 转换参数**:
| 参数 | 值 | 含义 |
|------|-----|------|
| MaxDegree | 2 | NURBS 曲线最大阶数 |
| MaxArcs | 1 | 最大弧段数（=1 表示单段 NURBS） |
| RationalAbility | 0 | 不使用有理 NURBS（权重=1） |
| 3DOutputDimension | TRUE | 输出 3D NURBS |

**拓扑域扫描**:
```cpp
CATLONG32 nbDomain = piSplineBody->GetNbDomains();     // 期望 = 1
CATDomain *piDomain1 = piSplineBody->GetDomain(1);

CATLISTP(CATCell) listCells;
piDomain1->GetAllCells(listCells, 1);  // dim=1 → 获取 Edge
int nbEdges = listCells.Size();        // 样条曲线 = 1 条 Edge
```

---

### 3. CATTopSurToNurbsSurOperator — 曲面转 NURBS

**功能**: 从样条曲线创建棱柱体（Prism），再将其表面转换为 NURBS 曲面。

**完整流程**:

```
步骤 1: 创建几何工厂
步骤 2: 创建几何体
  ├── 4 个拓扑点 → CATCreateTopPointXYZ
  ├── 样条曲线体 → CATCreateTopSpline
  └── 棱柱体 → CATCreateTopPrism(piGeomFactory, &topdata,
              piSplineBody, &zDir(0,0,1), startOffset=10, endOffset=30)
       → Run() → GetResult() → CATBody* pPrismBody
步骤 3: 获取所有面
  └── pPrismBody->GetAllCells(listCells, 2)  // dim=2 → Face
步骤 4: 创建 NURBS 曲面转换算子
  └── CATCreateTopSurToNurbsSurOperator(piGeomFactory, &topdata,
        pPrismBody, listCells[1])
  ├── 调参: SetMaxDegreeU(2), SetMaxDegreeV(2),
  │          SetMaxArcsU(1), SetMaxArcsV(1), SetRationalAbility(0)
  ├── Run() → GetResult() → CATBody*
  └── delete
步骤 5: 清理
```

**Prism 参数**:
```cpp
CATMathDirection zDir(0., 0., 1.);  // 拉伸方向 = Z 轴
double startOffset = 10.;           // 起始偏移
double endOffset = 30.;             // 结束偏移
// Prism 从 Z=10 拉伸到 Z=30
```

**NURBS 曲面参数**:
| 参数 | 值 | 含义 |
|------|-----|------|
| MaxDegreeU | 2 | U 方向最大阶数 |
| MaxDegreeV | 2 | V 方向最大阶数 |
| MaxArcsU | 1 | U 方向弧段数 |
| MaxArcsV | 1 | V 方向弧段数 |
| RationalAbility | 0 | 非有理 |

---

## 通用模式

所有三个程序共享以下模式：

### 几何工厂生命周期
```cpp
CATGeoFactory* piGeomFactory = CATCreateCGMContainer();
// ... 操作 ...
CATCloseCGMContainer(piGeomFactory);
```

### 软件配置
```cpp
CATSoftwareConfiguration *pConfig = new CATSoftwareConfiguration();
CATTopData topdata(pConfig);
// ... 使用 topdata 创建算子 ...
pConfig->Release();
```

### 拓扑算子生命周期
```cpp
CATTopXXX *pOp = CATCreateTopXXX(piGeomFactory, &topdata, ...);
pOp->Run();
CATBody *pResult = pOp->GetResult();
// ... 使用结果 ...
delete pOp;
pOp = NULL;
```

### .NCGM 文件保存（可选）
```cpp
if (toStore) {
    ofstream filetowrite(pFileName, ios::binary);
    CATSaveCGMContainer(piGeomFactory, filetowrite);
    filetowrite.close();
}
```

---

## 依赖关系

```
Mathematics → GeometricObjects → NewTopologicalObjects
  → TopologicalOperators → BasicTopologicalOpe → System
```

---

## 总结

CAABasicTopoOpe 是理解 CGM 拓扑操作范式的入门模块。三个程序层层递进：
1. **ComputePointOnWire** — 最简单的算子使用（创建 Wire → 计算点）
2. **CrvToNurbs** — 引入拓扑域扫描（GetDomain/GetAllCells）和参数调优
3. **SurToNurbs** — 组合多个算子（Spline → Prism → NURBS），展示算子链式组合

关键要点：
- 所有几何操作都在 CATGeoFactory 容器中进行
- CATTopData 封装软件配置和日志
- 拓扑算子遵循 Create → Run → GetResult → Delete 生命周期
- 拓扑体通过 GetDomain/GetAllCells 进行层级扫描