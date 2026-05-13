---
module: "CAASimulationInterfaces.edu"
category: "仿真接口"
tier: "7"
status: "已完成"
---

# CAASimulationInterfaces.edu — 仿真接口

## 模块定位

CAASimulationInterfaces 演示了 **CATIA 仿真（Simulation）的 CAA 编程接口**。仿真接口用于：
- 仿真工作台控制
- 仿真流程管理
- 结果后处理

**依赖关系**：基于 CAAAnalysisInterfaces。

---

## 核心接口

### CATISimulation — 仿真接口

```cpp
class CATISimulation : public CATBaseUnknown {
    // 创建仿真
    virtual HRESULT CreateSimulation(CATISpecObject * model, CATISimulation ** sim) = 0;
    
    // 执行仿真
    virtual HRESULT Compute() = 0;
    
    // 获取结果
    virtual HRESULT GetResults(CATISimulationResults ** results) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATISimulation 管理仿真生命周期**：创建、执行、后处理

2. **与分析与优化集成**：形成完整设计验证流程

3. **结果可视化**：图形化展示仿真结果

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATISimulation.htm](../api-reference/interfaces/CATISimulation.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
