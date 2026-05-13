---
module: "CAABehaviorInterfaces.edu"
category: "行为接口"
tier: "7"
status: "已完成"
---

# CAABehaviorInterfaces.edu — 行为接口

## 模块定位

CAABehaviorInterfaces 演示了 **CATIA 行为（Behavior）建模的 CAA 编程接口**。行为建模用于：
- 参数化行为定义
- 约束传播
- 设计意图捕获

**依赖关系**：基于 CAAKnowHow。

---

## 核心接口

### CATIBehavior — 行为接口

```cpp
class CATIBehavior : public CATBaseUnknown {
    // 获取行为参数
    virtual HRESULT GetParameters(CATLISTP(CATBaseUnknown) ** params) = 0;
    
    // 设置行为规则
    virtual HRESULT SetRule(CATICkeRule * rule) = 0;
    
    // 评估行为
    virtual HRESULT Evaluate() = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIBehavior 定义参数化行为**：捕获设计意图

2. **规则驱动**：使用知识工程规则定义行为

3. **与其他系统集成**：与分析、优化模块协同

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIBehavior.htm](../api-reference/interfaces/CATIBehavior.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
