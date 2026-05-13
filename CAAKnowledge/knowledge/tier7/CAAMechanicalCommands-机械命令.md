---
module: "CAAMechanicalCommands.edu"
category: "机械命令"
tier: "7"
status: "已完成"
---

# CAAMechanicalCommands.edu — 机械命令

## 模块定位

CAAMechanicalCommands 演示了 **CATIA 机械设计常用命令的 CAA 编程接口**。机械命令包括：
- 测量工具
- 分析工具
- 转换工具

**依赖关系**：基于 Tier 3 的机械建模模块。

---

## 核心组件

### 测量命令

```cpp
class CAAMechanicalMeasureCmd : public CATStateCommand {
    void BuildGraph();
    CATBoolean Measure(void *);
}
```

### 分析命令

```cpp
class CAAMechanicalAnalyzeCmd : public CATStateCommand {
    void BuildGraph();
    CATBoolean Analyze(void *);
}
```

---

## 对 AI agent 的要点

1. **机械命令使用 CATStateCommand**：用户交互式测量和分析

2. **测量类型**：距离、角度、半径等

3. **分析结果**：用于设计验证

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIMeasure.htm](../api-reference/interfaces/CATIMeasure.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
