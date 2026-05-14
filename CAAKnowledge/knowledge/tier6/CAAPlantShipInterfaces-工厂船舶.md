---
module: "CAAPlantShipInterfaces.edu"
category: "工厂船舶接口"
tier: "6"
status: "已完成"
---

# CAAPlantShipInterfaces.edu — 工厂船舶接口

## 模块定位

CAAPlantShipInterfaces 演示了 **CATIA 工厂/船舶（Plant/Ship）模块的 CAA 编程接口**。工厂/船舶模块用于：
- 大型设施布局
- 管道设计
- 结构设计
- 设备布置

**依赖关系**：基于 CAAProductStructure 和 CAAV5V6ObjectSpecsModeler。

---

## 核心接口

### 工厂/船舶接口

```cpp
// 工厂/船舶相关的接口
class CATIPlantLayout {
    // 获取布局
    virtual HRESULT GetLayout(CATISpecObject ** layout) = 0;
    
    // 添加设备
    virtual HRESULT AddEquipment(CATISpecObject * equip) = 0;
    
    // 创建管道
    virtual HRESULT CreatePipe(CATISpecObject * start, CATISpecObject * end) = 0;
}
```

### CATIStructure — 结构接口

```cpp
// 结构相关的接口
class CATIStructure {
    // 获取结构成员
    virtual HRESULT GetMembers(CATLISTP(CATBaseUnknown) ** members) = 0;
    
    // 添加梁
    virtual HRESULT AddBeam(CATISpecObject * profile, const CATMathPoint & start, const CATMathPoint & end) = 0;
}
```

---

## 对 AI agent 的要点

1. **工厂/船舶模块处理大型项目**：需要性能优化

2. **布局管理**：设备、管道的空间布局

3. **CATIStructure 用于结构建模**：梁、柱、板等结构件

4. **管道设计**：起点终点、弯管、阀门等

5. **与制造的关联**：结构件可用于加工

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIPlantLayout.htm](../api-reference/interfaces/CATIPlantLayout.htm)
- 完整方法签名: [api-reference/interfaces/CATIStructure.htm](../api-reference/interfaces/CATIStructure.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
