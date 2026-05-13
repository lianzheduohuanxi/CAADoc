---
module: "CAAElecSchematicItf.edu"
category: "电气原理图接口"
tier: "7"
status: "已完成"
---

# CAAElecSchematicItf.edu — 电气原理图接口

## 模块定位

CAAElecSchematicItf 演示了 **CATIA 电气原理图（Electrical Schematic）的 CAA 编程接口**。电气原理图用于：
- 电气回路设计
- 符号放置
- 连线生成

**依赖关系**：基于 CAAElecDeviceItf。

---

## 核心接口

### CATIElecSchematic — 原理图接口

```cpp
class CATIElecSchematic : public CATBaseUnknown {
    // 添加符号
    virtual HRESULT AddSymbol(CATISpecObject * symbol, const CATMathPoint2D & pos) = 0;
    
    // 创建连线
    virtual HRESULT CreateWire(CATISpecObject * start, CATISpecObject * end) = 0;
    
    // 生成报表
    virtual HRESULT GenerateReport(CATUnicodeString & report) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIElecSchematic 管理电气回路**：符号和连线

2. **符号库**：标准电气符号

3. **报表生成**：物料清单等文档

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIElecSchematic.htm](../api-reference/interfaces/CATIElecSchematic.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
