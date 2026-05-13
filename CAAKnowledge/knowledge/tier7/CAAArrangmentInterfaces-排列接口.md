---
module: "CAAArrangmentInterfaces.edu"
category: "排列接口"
tier: "7"
status: "已完成"
---

# CAAArrangmentInterfaces.edu — 排列接口

## 模块定位

CAAArrangmentInterfaces 演示了 **CATIA 排列（Arrangement）功能的 CAA 编程接口**。排列功能用于：
- 装配排列管理
- 配置切换
- 变体管理

**依赖关系**：基于 CAAProductStructure。

---

## 核心接口

### CATIArrangement — 排列接口

```cpp
class CATIArrangement : public CATBaseUnknown {
    // 获取排列名称
    virtual CATBSTR GetName() = 0;
    
    // 获取当前激活的排列
    virtual HRESULT GetActiveArrangement(CATIArrangement ** arr) = 0;
    
    // 设置激活排列
    virtual HRESULT SetActiveArrangement(CATIArrangement * arr) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIArrangement 管理产品配置变体**：支持多配置

2. **快速切换**：不同排列代表不同的装配状态

3. **与 E5i 集成**：支持 PDM 中的变体管理

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIArrangement.htm](../api-reference/interfaces/CATIArrangement.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
