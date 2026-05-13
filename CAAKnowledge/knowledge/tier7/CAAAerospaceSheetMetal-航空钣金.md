# CAAAerospaceSheetMetal — 航空钣金设计

**模块**: CAAAerospaceSheetMetal.edu | **层级**: Tier 7 | **规模**: 9 个文件（~7,300 行代码）

---

## 模块定位

CAAAerospaceSheetMetal 是 CATIA 航空钣金设计（Aerospace Sheet Metal Design）框架的教学模块，展示了三种航空钣金特征的完整批处理操作：**Web**（腹板）、**SurfacicFlange**（曲面翻边）、**Joggle**（错位/台阶）。同时提供了共享的输入数据模型（CAAStmInputData）和服务层（CAAStmServices）。

---

## 架构概览

```
CAAAerospaceSheetMetal.edu/
├── IdentityCard/
│   └── IdentityCard.xml              依赖: CATSmaInterfaces, KnowledgeInterfaces,
│                                         MecModInterfaces, Mathematics, System 等
├── PublicInterfaces/
│   ├── CAAStmExportedBy.h            DLL 导出宏
│   ├── CAAStmInputData.h             (390行) 输入数据类：存储所有钣金特征参数
│   └── CAAStmServices.h              (144行) 服务类：管理特征的读写操作
├── CAAStmWeb.m/src/
│   └── CAAStmWeb.cpp                 (583行) Web 批处理
├── CAAStmSurfacicFlange.m/src/
│   └── CAAStmSurfacicFlange.cpp      (1402行) SurfacicFlange 批处理
├── CAAStmJoggle.m/src/
│   └── CAAStmJoggle.cpp              (795行) Joggle 批处理
├── CAAStmServices.m/src/
│   ├── CAAStmInputData.cpp           (1216行) 输入数据实现
│   └── CAAStmServices.cpp            (2764行) 服务层实现
└── Data.d/                           测试数据（Joggle/, SurfacicFlange/, Web/）
```

> 该项目无 ProtectedInterfaces/PrivateInterfaces 目录。

---

## 核心类详解

### 1. CAAStmInputData — 输入数据模型

集中管理三种钣金特征的所有参数，使用大量的 Get/Set 方法对。

**通用参数**:
| 参数 | 类型 | 说明 |
|------|------|------|
| PartPath | CATUnicodeString | Part 文档路径 |
| GeomFactory | CATGeoFactory* | 几何工厂指针 |
| FeatureName | CATUnicodeString | 特征名称 |

**Web 专用参数**:
| 参数 | 说明 |
|------|------|
| Support | 支持面 |
| Boundary | 边界元素 |
| MaterialOrient | 材料方向 |
| OffsetDirection | 偏移方向 |
| Thickness | 厚度 |

**SurfacicFlange 专用参数**:
| 参数 | 说明 |
|------|------|
| BaseFeature | 基础特征 |
| Support | 支持面 |
| BendRadius | 弯曲半径 |
| Angle | 翻边角度 |
| Side1/Side2 | 双面控制 |
| EOP (End Of Part) | 特征终点 |
| Compensation | 补偿 |
| UnfoldRef | 展开参考 |

**Joggle 专用参数**:
| 参数 | 说明 |
|------|------|
| Support | 支持面 |
| Plane | 台阶平面 |
| Depth | 深度 |
| Runout | 退刀 |
| Clearance | 间隙 |
| StartRadius / EndRadius | 起始/结束半径 |
| StartAngle / EndAngle | 起始/结束角度 |

---

### 2. CAAStmServices — 服务层

提供钣金特征的完整生命周期管理。

**核心方法**:
```
ReadInputFile()      — 读取配置文件，解析 Web/Flange/Joggle 输入参数
FindFeature()        — 在 Part 中查找指定特征
CreateWeb()          — 创建 Web 特征
CreateSurfacicFlange() — 创建 SurfacicFlange 特征
CreateJoggle()       — 创建 Joggle 特征
Update()             — 更新特征
DisplayEntries()     — 显示特征条目（调试用）
ConvertUnits()       — 单位转换（mm ↔ inch）
```

---

## 批处理程序详解

### CAAStmWeb — Web（腹板）

**流程**:
1. 创建 Session，打开 Part 文档
2. 创建或检索 Web 特征
3. 设置 Web 参数：
   - **Support** — 腹板所在的参考平面/曲面
   - **Boundary** — 腹板的边界轮廓
   - **MaterialOrient** — 材料方向（决定厚度方向）
4. 调用 Update 计算
5. 保存 Part

**核心操作**:
```cpp
// 创建 Web
CATISmaWeb *piWeb;
CATISmaFactory *piFactory;
piFactory->CreateWeb(support, boundary, &piWeb);

// 设置参数
piWeb->SetSupport(support);
piWeb->SetBoundary(boundary);
piWeb->SetMaterialOrient(materialDir);
piWeb->Update();
```

### CAAStmSurfacicFlange — 曲面翻边

这是最复杂的批处理程序（1402 行），支持完整的翻边参数配置。

**流程**:
1. 创建 Session，打开 Part
2. 检索或创建 SurfacicFlange 特征
3. 设置全套参数：
   - **BaseFeature** — 翻边的基体特征（如 Web）
   - **Support** — 翻边依附的曲面
   - **BendRadius** — 弯曲半径
   - **Angle** — 翻边角度
   - **Side1/Side2** — 两侧分别控制（方向、长度、补偿等）
   - **EOP** — 特征终点（如到曲面、到平面等终止条件）
   - **Compensation** — 展开补偿
   - **UnfoldRef** — 展开参考
4. Update 计算
5. 保存

**参数模式** — 每个参数通过 Set 方法配置，支持 Side1/Side2 独立设置:

```
Side1: Direction(沿曲面法向) + Length(翻边长度) + Compensation(补偿值)
Side2: Direction(沿曲面法向) + Length(翻边长度) + Compensation(补偿值)
```

### CAAStmJoggle — 错位/台阶

**流程**:
1. 创建 Session，打开 Part
2. 创建或修改 Joggle 特征
3. 设置参数：
   - **Support** — 台阶所在的支持面
   - **Plane** — 台阶的参考平面（定义台阶位置和方向）
   - **Depth** — 台阶深度
   - **Runout** — 退刀长度
   - **Clearance** — 间隙
   - **StartRadius / EndRadius** — 台阶两端的过渡半径
   - **StartAngle / EndAngle** — 台阶两端的角度
4. Update
5. 保存

**Joggle 几何含义**:

```
   ┌─────────────────┐
   │                 │  ← StartRadius
   │    ┌──────┐     │
   │    │Depth │     │  ← Plane 位置
   │    └──────┘     │
   │                 │  ← EndRadius
   └─────────────────┘
   ←── Runout ──→← Clearance →
```

---

## 关键接口总结

| 接口 | 框架 | 用途 |
|------|------|------|
| CATISmaFactory | CATSmaInterfaces | 钣金特征工厂（CreateWeb/CreateFlange/CreateJoggle） |
| CATISmaWeb | CATSmaInterfaces | Web 特征接口 |
| CATISmaSurfacicFlange | CATSmaInterfaces | 曲面翻边特征接口 |
| CATISmaJoggle | CATSmaInterfaces | Joggle 特征接口 |
| CATISmaServices | CATSmaInterfaces | 钣金通用服务 |

---

## 依赖关系

```
CATSmaInterfaces → KnowledgeInterfaces → MecModInterfaces
  → ObjectSpecsModeler → ProductStructure → Mathematics
  → GeometricObjects → NewTopologicalObjects → System
```

---

## 总结

CAAAerospaceSheetMetal 展示了 CATIA 航空钣金设计的三个核心特征类型。CAAStmInputData 作为统一的数据传输对象（DTO），将复杂的参数配置集中管理；CAAStmServices 封装了特征查找、创建、更新等操作。SurfacicFlange 是最复杂的特征，涉及双面独立控制、EOP 终止条件、展开补偿等多种高级参数。