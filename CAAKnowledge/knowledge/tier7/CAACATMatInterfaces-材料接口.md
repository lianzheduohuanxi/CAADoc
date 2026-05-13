---
module: "CAACATMatInterfaces.edu"
category: "材料接口"
tier: "7"
status: "已完成"
---

# CAACATMatInterfaces.edu — CATIA 材料接口

## 模块定位

CAACATMatInterfaces 演示了 **CATIA 材料（Material）管理的 CAA 编程接口**。材料管理用于：
- 材料定义和编辑
- 材料库访问
- 材料应用

**依赖关系**：基于 CAAGeometricObjects。

---

## 核心接口

### CATIMaterial — 材料接口

```cpp
class CATIMaterial : public CATBaseUnknown {
    // 获取材料属性
    virtual HRESULT GetProperties(CATIMaterialProperties ** props) = 0;
    
    // 设置密度
    virtual HRESULT SetDensity(double density) = 0;
    
    // 获取密度
    virtual double GetDensity() = 0;
}
```

### CATIMaterialProperties — 材料属性

```cpp
class CATIMaterialProperties : public CATBaseUnknown {
    // 设置力学属性
    virtual HRESULT SetMechanical(double young, double poisson, double density) = 0;
    
    // 设置热属性
    virtual HRESULT SetThermal(double conductivity, double capacity) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIMaterial 定义材料**：密度、力学属性、热属性

2. **与分析的结合**：材料属性用于 FEA 分析

3. **材料库支持标准材料复用**：钢铁、铝、塑料等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIMaterial.htm](../api-reference/interfaces/CATIMaterial.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
