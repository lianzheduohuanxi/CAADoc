# CAAGeometricOperators — 几何操作符

**模块**: CAAGeometricOperators.edu | **层级**: Tier 7 | **规模**: 3 个文件（1 个 .cpp + 1 个 Imakefile + 1 个 XML）

---

## 模块定位

CAAGeometricOperators 是最精简的教学模块之一，仅包含**一个批处理程序**，演示 CATIA CGM **几何求交算子**（CATIntersectionCrvSur）的 BASIC 和 ADVANCED 两种使用模式。

---

## 架构概览

```
CAAGeometricOperators.edu/
├── IdentityCard/
│   └── IdentityCard.xml        依赖: Mathematics, AdvancedMathematics,
│                                   GeometricObjects, GeometricOperators, System
├── CAAGopIntersect.m/
│   ├── Imakefile.mk            链接: JS0GROUP, CATMathematics, CATMathStream,
│   │                               CATCGMGeoMath, CATGeometricObjects,
│   │                               CATGeometricOperators
│   └── src/
│       └── CAAGopIntersect.cpp  (270行) 曲线-曲面求交
```

> 该项目没有任何头文件。

---

## 核心算子：CATIntersectionCrvSur

**功能**: 计算一条曲线与一个曲面的所有交点。

**全局创建函数**:
```cpp
CATIntersectionCrvSur *pIntOp = CATCreateIntersection(
    piGeomFactory,     // 几何工厂
    pConfig,           // 软件配置
    piLine,            // 曲线
    piCylinder,        // 曲面
    mode               // BASIC 或 ADVANCED
);
```

---

## 两种模式对比

### BASIC 模式

**特点**: 创建即运行，无需显式调用 Run()。

```cpp
CATIntersectionCrvSur *pIntOp = CATCreateIntersection(
    piGeomFactory, pConfig, piLine, piCylinder, BASIC);

// 直接获取结果 — 算子已自动运行
CATLONG32 nbPoints = pIntOp->GetNumberOfPoints();
```

**结果遍历**（迭代器模式）:
```cpp
pIntOp->BeginningPoint();  // 初始化迭代器
while (TRUE == pIntOp->NextPoint()) {
    CATCartesianPoint* piPoint = pIntOp->GetCartesianPoint();
    double x, y, z;
    piPoint->GetCoord(x, y, z);
    cout << "X= " << x << " Y= " << y << " Z= " << z << endl;
    piGeomFactory->Remove(piPoint);  // 不保留，立即删除
}
```

**适用场景**: 一次性求交，不需要修改输入或多次运行。

---

### ADVANCED 模式

**特点**: 创建后需要显式 Run()，支持参数调优、多次运行、修改输入。

**步骤 1: 创建**
```cpp
pIntOp = CATCreateIntersection(piGeomFactory, pConfig,
    piLine, piCylinder, ADVANCED);
```

**步骤 2: 设置曲线范围限制**
```cpp
CATCrvParam startParam, endParam;
piLine->GetParam(CATMathO, startParam);                // 原点参数
piLine->GetParam(CATMathPoint(35., 35., 0.), endParam); // (35,35,0) 参数
CATCrvLimits crvLimits(startParam, endParam);
pIntOp->SetLimits(crvLimits);  // 只在线段 [Origin, (35,35,0)] 内求交
```

**步骤 3: 运行**
```cpp
pIntOp->Run();
```

**步骤 4: 修改输入并再次运行**
```cpp
// 创建新曲线（从圆柱面上的点沿 Z 轴方向）
CATMathPoint MP(0., radius, 0.);       // 圆柱面上的点
CATMathVector k(0., 0., 1.);           // Z 轴方向
CATLine *piNewLine = piGeomFactory->CreateLine(MP, k);

pIntOp->SetCurve(piNewLine);  // 替换曲线
pIntOp->Run();                // 再次运行

// 获取新结果
CATLONG32 nbCurves = pIntOp->GetNumberOfCurves();
// 此时可能返回 0 个点（不相交）但 1 条曲线（相切）
```

**适用场景**: 需要反复调整输入参数、多次求交、精细控制求交范围。

---

## 测试几何体

### 直线
```cpp
CATLine *piLine = piGeomFactory->CreateLine(
    CATMathO,                    // 通过原点 (0,0,0)
    CATMathVector(1., 1., 0.)    // 方向 (1,1,0) — 在 XY 平面 45° 方向
);
```

### 圆柱面
```cpp
CATCylinder *piCylinder = piGeomFactory->CreateCylinder(
    CATMathOIJK,       // 轴 = Z 轴（标准坐标系）
    10.,               // 半径 = 10
    -50., 50.,         // 轴范围 [-50, 50]
    0., CAT2PI         // 角度范围 [0, 2π] — 完整圆柱
);
```

**几何关系**: 直线 `y=x`（在 XY 平面）与圆柱 `x²+y²=100` 相交于两个点：
- `(-7.071, -7.071, 0)` 即 `(-10/√2, -10/√2, 0)`
- `(7.071, 7.071, 0)` 即 `(10/√2, 10/√2, 0)`

---

## 预期输出

```
Basic case: Number of intersection points: 2
 X= -7.07107 Y= -7.07107 Z= 0
 X= 7.07107 Y= 7.07107 Z= 0
Advanced mode: Number of intersection points: 1
 X= 7.07107 Y= 7.07107 Z= 0
Advanced mode with another run: Number of intersection points: 0
Advanced mode with another run: Number of intersection curves: 1
```

---

## 算子生命周期对比

| 阶段 | BASIC | ADVANCED |
|------|-------|----------|
| 创建 | `CATCreateIntersection(..., BASIC)` | `CATCreateIntersection(..., ADVANCED)` |
| 运行 | 自动（创建时） | 显式 `Run()` |
| 设置限制 | 不支持 | `SetLimits()` |
| 修改输入 | 不支持 | `SetCurve()` |
| 多次运行 | 不支持 | 支持 |
| 获取结果 | 创建后即可 | Run() 之后 |
| 删除 | `delete` | `delete` |

---

## 结果类型

| 方法 | 返回 | 说明 |
|------|------|------|
| GetNumberOfPoints() | CATLONG32 | 交点数量 |
| GetNumberOfCurves() | CATLONG32 | 交线数量（如相切时） |
| GetCartesianPoint() | CATCartesianPoint* | 获取当前交点 |
| BeginningPoint() / NextPoint() | void / CATBoolean | 点迭代器 |

---

## 依赖关系

```
Mathematics → AdvancedMathematics → GeometricObjects → GeometricOperators → System
```

---

## 构建配置

```makefile
BUILT_OBJECT_TYPE=LOAD MODULE
LINK_WITH = \
  JS0GROUP \
  CATMathematics \
  CATMathStream \
  CATCGMGeoMath \
  CATGeometricObjects \
  CATGeometricOperators
```

---

## 总结

CAAGeometricOperators 是最精简的 CAA 教学模块，用 270 行代码清晰展示了 CGM 几何求交算子的两种使用范式：
- **BASIC 模式** — 简单直接，适合一次性求交
- **ADVANCED 模式** — 灵活强大，支持参数限制、输入修改、多次运行

关键设计模式：
1. **工厂函数** `CATCreateIntersection` 统一创建入口
2. **迭代器模式** `BeginningPoint/NextPoint/GetCartesianPoint` 遍历结果
3. **策略模式** BASIC/ADVANCED 决定算子行为
4. **RAII 风格** delete 算子释放资源