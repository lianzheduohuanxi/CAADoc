---
module: "CAASPAInterfaces.edu"
category: "SPA 接口"
tier: "7"
status: "已完成"
---

# CAASPAInterfaces.edu — SPA 接口

## 模块定位

CAASPAInterfaces 演示了 **CATIA SPA（Scientific Prototype Analysis）接口的 CAA 编程接口**。SPA 用于：
- 科学原型分析
- 数据处理算法
- 可视化分析

**依赖关系**：基础框架。

---

## 核心接口

### CATISPAData — SPA 数据接口

```cpp
class CATISPAData : public CATBaseUnknown {
    // 获取数据点
    virtual HRESULT GetDataPoints(CATLISTP(CATMathPoint) ** points) = 0;
    
    // 设置数据
    virtual HRESULT SetDataPoints(CATLISTP(CATMathPoint) * points) = 0;
    
    // 分析
    virtual HRESULT Analyze(CATISPAAnalysis ** result) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATISPAData 管理科学数据**：点集、曲线、曲面

2. **分析方法**：插值、拟合、变换

3. **与可视化集成**：图形化展示分析结果

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATISPAData.htm](../api-reference/interfaces/CATISPAData.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
