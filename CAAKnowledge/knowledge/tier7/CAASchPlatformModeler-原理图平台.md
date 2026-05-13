---
module: "CAASchPlatformModeler.edu"
category: "原理图平台建模器"
tier: "7"
status: "已完成"
---

# CAASchPlatformModeler.edu — 原理图平台建模器

## 模块定位

CAASchPlatformModeler 演示了 **CATIA 原理图平台（Schematic Platform）的 CAA 编程接口**。原理图平台用于：
- 系统原理图设计
- 符号库管理
- 连线定义

**依赖关系**：基于 CAAElecSchematicItf。

---

## 核心接口

### CATISchPlatform — 原理图平台接口

```cpp
class CATISchPlatform : public CATBaseUnknown {
    // 创建符号实例
    virtual HRESULT CreateSymbolInstance(CATISpecObject * symbol, const CATMathPoint2D & pos) = 0;
    
    // 创建连线
    virtual HRESULT CreateConnection(CATISpecObject * from, CATISpecObject * to) = 0;
    
    // 获取平台内容
    virtual HRESULT GetContent(CATLISTP(CATBaseUnknown) ** items) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATISchPlatform 管理电气/系统原理图**：符号和连线

2. **符号库集成**：标准符号复用

3. **与其他工程模块集成**：生成制造数据

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATISchPlatform.htm](../api-reference/interfaces/CATISchPlatform.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
