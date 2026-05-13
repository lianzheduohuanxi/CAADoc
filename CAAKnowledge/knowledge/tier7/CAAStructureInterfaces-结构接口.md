---
module: "CAAStructureInterfaces.edu"
category: "结构接口"
tier: "7"
status: "已完成"
---

# CAAStructureInterfaces.edu — 结构接口

## 模块定位

CAAStructureInterfaces 演示了 **CATIA 结构设计（Structure Design）的 CAA 编程接口**。结构设计用于：
- 梁柱结构创建
- 结构件布置
- 结构分析

**依赖关系**：基于 CAAGSMInterfaces。

---

## 核心接口

### CATIStructure — 结构接口

```cpp
class CATIStructure : public CATBaseUnknown {
    // 创建梁
    virtual HRESULT CreateBeam(CATISpecObject * profile, const CATMathPoint & start, const CATMathPoint & end) = 0;
    
    // 创建柱
    virtual HRESULT CreateColumn(CATISpecObject * profile, const CATMathPoint & pos, double height) = 0;
    
    // 创建板
    virtual HRESULT CreatePlate(CATISpecObject * surface, double thickness) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIStructure 用于建筑/土木结构**：梁、柱、板

2. **截面库**：标准型钢截面

3. **与分析和制造集成**：结构分析和加工

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIStructure.htm](../api-reference/interfaces/CATIStructure.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
