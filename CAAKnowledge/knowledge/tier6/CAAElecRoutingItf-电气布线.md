# CAAElecRoutingItf — 电气布线接口

**模块**: CAAElecRoutingItf.edu | **层级**: Tier 6 | **规模**: 8 个文件（2 个头文件 + 6 个 .cpp）

---

## 模块定位

CAAElecRoutingItf 是 CATIA 电气布线（Electrical Routing）框架的教学模块，演示了电气线束网络中的数据导航：过滤条件管理、线束段内导线列表、导线端点设备查询、以及线束段物理属性计算。

---

## 架构概览

```
CAAElecRoutingItf.edu/
├── IdentityCard/
│   └── IdentityCard.h          依赖: System, Mathematics, ObjectModelerBase,
│                                   ProductStructure, ElectricalInterfaces,
│                                   ElecRoutingItf, ObjectSpecsModeler,
│                                   KnowledgeInterfaces, ProductStructureInterfaces
├── CAAEwrCriteria.m/
│   ├── LocalInterfaces/
│   │   └── CAAUipFilteringCriteriaExt.h   过滤条件管理类
│   └── src/
│       └── CAAUipFilteringCriteriaExt.cpp 实现: ListSystems/ListCriteria/ListWires
├── CAAEwrFilter.m/
│   └── src/CAAEwrFilter.cpp               批处理: 过滤 Session 并保存
├── CAAEwrGetExtremitesOfWire.m/
│   └── src/CAAEwrGetExtremitesOfWire.cpp  批处理: 查询导线端点设备
├── CAAEwrListWiresInBundleSegment.m/
│   └── src/CAAEwrListWiresInBundleSegment.cpp  批处理: 列出线束段内导线
└── CAAEwrRoutingImpl.m/
    ├── LocalInterfaces/
    │   └── CAAEwrUipBundleSegmentExt.h    线束段物理属性计算
    └── src/
        └── CAAEwrUipBundleSegmentExt.cpp  实现: ComputeDiameter/ComputeBendRadius
```

> 该项目没有 PublicInterfaces/ProtectedInterfaces/PrivateInterfaces 目录，使用 LocalInterfaces 模式。

---

## 核心接口与类

### 1. CAAUipFilteringCriteriaExt（过滤条件管理）

**绑定接口**: CATIEleUipFilteringCriteria, CATIEleUipSystems

```cpp
class CAAUipFilteringCriteriaExt : public CATBaseUnknown {
    // 列出可用系统（返回 "SAMPLE"）
    HRESULT ListSystems(CATListValCATUnicodeString *& oListOfSystems);

    // 列出可用过滤条件（返回 "FULL", "CRIT1", "CRIT2"）
    HRESULT ListCriteria(const CATListValCATUnicodeString *iListOfSystems,
                         CATListValCATUnicodeString *& oListOfCriteria);

    // 按系统和条件列出导线（Wire1~Wire7，不同条件返回不同子集）
    HRESULT ListWires(const CATListValCATUnicodeString *iListOfSystems,
                      const CATListValCATUnicodeString *iListOfCriteria,
                      CATListValCATUnicodeString *& oListOfWires);
};
```

**TIE 绑定**:
```cpp
TIE_CATIEleUipFilteringCriteria(CAAUipFilteringCriteriaExt);
TIE_CATIEleUipSystems(CAAUipFilteringCriteriaExt);
CATImplementClass(CAAUipFilteringCriteriaExt, DataExtension,
                  CATBaseUnknown, CATElecSoftwareOpennessImpl);
```

### 2. CAAEwrUipBundleSegmentExt（线束段物理属性）

**绑定接口**: CATIEwrUipBundleSegment

```cpp
class CAAEwrUipBundleSegmentExt : public CATBaseUnknown {
    // 根据内部导线直径计算线束段直径
    // 算法: 总面积 = Σ(π * d² / 4), 结果 = sqrt(总面积 * 4 / π)
    HRESULT ComputeDiameter(const CATListOfDouble iListOfWireDiameters,
                            double & oBundleSegmentDiameter);

    // 根据内部导线弯曲半径计算线束段弯曲半径
    // 算法: 取所有导线弯曲半径的最大值
    HRESULT ComputeBendRadius(const CATListOfDouble iListOfWireBendRadius,
                              double & oBundleSegmentBendRadius);
};
```

**TIE 绑定**:
```cpp
TIE_CATIEwrUipBundleSegment(CAAEwrUipBundleSegmentExt);
CATBeginImplementClass(CAAEwrUipBundleSegmentExt, CodeExtension,
                       CATBaseUnknown, ElecBundleSegmentE);
CATAddClassExtension(ElecBundleSegmentC);
CATEndImplementClass(CAAEwrUipBundleSegmentExt);
```

---

## 批处理程序详解

### CAAEwrFilter — Session 过滤与保存

**流程**:
1. 创建 Session，打开 CATProduct
2. 获取 Root Product
3. 初始化电气环境（`CATIEleDocServices::Initialize`）
4. 通过 `CATIEwrFilter::Filter` 按 CRIT1 条件过滤 Session（只保留匹配的 BundleSegment 和 Device）
5. 调用 `CATIAProduct::Update` 刷新
6. 遍历所有文档，SaveAs 到输出目录

**核心代码**:
```cpp
CATIEwrFilter *pFilter = NULL;
piRootProduct->QueryInterface(IID_CATIEwrFilter, (void**)&pFilter);

CATListValCATUnicodeString *iListOfSystems = new CATListValCATUnicodeString();
CATListValCATUnicodeString *iListOfCriteria = new CATListValCATUnicodeString();
iListOfSystems->Append(CATUnicodeString("SAMPLE"));
iListOfCriteria->Append(CATUnicodeString("CRIT1"));

pFilter->Filter(iListOfSystems, iListOfCriteria,
                ElecFilterBundleSegment | ElecFilterDevice);
```

### CAAEwrGetExtremitesOfWire — 导线端点设备查询

**流程**:
1. 创建 Session，打开 CATProduct
2. 初始化电气环境
3. 遍历 Root Product 的子节点，通过 `CATIElecAttrAccess::GetElecType` 找到 ElecBundle
4. 在 ElecBundle 下通过 `GetAllChildren(CATIEwrWire::ClassName())` 获取所有导线
5. 对每条导线调用 `CATIEwrWire::GetExtremities`，获取两端连接的 Device Instance 和 Connection Point

**核心 API**:
```cpp
CATIEwrWire_var hWire;
CATBaseUnknown *pFirstDeviceInst, *pFirstCnctPt;
CATBaseUnknown *pSecondDeviceInst, *pSecondCnctPt;

hWire->GetExtremities(pFirstDeviceInst, pFirstCnctPt,
                      pSecondDeviceInst, pSecondCnctPt);
// pFirstDeviceInst  = 导线第一端连接的设备实例
// pSecondDeviceInst = 导线第二端连接的设备实例
```

### CAAEwrListWiresInBundleSegment — 线束段导线列表

**流程**:
1. 创建 Session，打开 CATProduct
2. 初始化电气环境
3. 遍历 Root Product → 找到 GeometricalBundle（通过 CATIElecAttrAccess 检查类型 "ElecGeoBundle"）
4. 在 GeometricalBundle 下通过 CATIParmPublisher 获取所有 CATIInstance
5. 通过 CATITypeDictionary 获取 BundleSegment 类型
6. 筛选出 Ref_Des = "Bundle Segment.2" 的 BundleSegment
7. 通过 `CATIEwrRouteSegment::ListConductors` 列出通过该段的所有导线

**核心 API**:
```cpp
CATIEwrRouteSegment *piEwrRouteSegment;
piBNSInstance->QueryInterface(IID_CATIEwrRouteSegment, (void**)&piEwrRouteSegment);

CATListValCATBaseUnknown_var *pListConductors = NULL;
piEwrRouteSegment->ListConductors(pListConductors);
// pListConductors 包含通过该线束段的所有导线
```

---

## 关键接口总结

| 接口 | 来源框架 | 用途 |
|------|----------|------|
| CATIEleDocServices | ElectricalInterfaces | 初始化电气文档环境 |
| CATIElecAttrAccess | ElecAttrAccess | 读取电气属性（类型、Ref_Des） |
| CATIEwrFilter | ElecRoutingItf | 按条件过滤 Session |
| CATIEwrWire | ElecRoutingItf | 获取导线端点设备/连接点 |
| CATIEwrRouteSegment | ElecRoutingItf | 列出线束段内的导线 |
| CATIEwrUipBundleSegment | ElecRoutingItf | 计算线束段物理属性（直径/弯曲半径） |
| CATIEleUipFilteringCriteria | ElecRoutingItf | 过滤条件管理 |
| CATIEleUipSystems | ElecRoutingItf | 系统列表管理 |

---

## 依赖关系

```
System → Mathematics → ObjectModelerBase → ProductStructure
  → ElectricalInterfaces → ElecRoutingItf → ObjectSpecsModeler
  → KnowledgeInterfaces → ProductStructureInterfaces
```

---

## 总结

CAAElecRoutingItf 展示了 CATIA 电气布线框架的核心导航能力：从 Session 级别的条件过滤，到 BundleSegment 级别的导线列表查询，再到单根导线级别的端点设备追溯，以及线束段的物理属性计算。它使用的是 CAA 的 DataExtension/CodeExtension 模式，通过 TIE 宏将实现类绑定到框架接口。