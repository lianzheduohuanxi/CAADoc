---
module: "CAADMAPSInterfaces.edu"
category: "DMAPS 接口"
tier: "7"
status: "已完成"
---

# CAADMAPSInterfaces.edu — DMAPS 接口

## 模块定位

CAADMAPSInterfaces 演示了 **CATIA DMAPS（Digital Mockup Advanced Product Structure）的 CAA 编程接口**。DMAPS 用于：
- 数字化样机装配
- 干涉检查
- 装配验证

**依赖关系**：基于 CAAProductStructure。

---

## 核心接口

### CATIDMAPS — DMAPS 接口

```cpp
class CATIDMAPS : public CATBaseUnknown {
    // 执行干涉检查
    virtual HRESULT CheckInterference(CATLISTP(CATBaseUnknown) ** results) = 0;
    
    // 获取装配序列
    virtual HRESULT GetAssemblySequence(CATLISTP(CATBaseUnknown) ** sequence) = 0;
    
    // 验证装配
    virtual HRESULT ValidateAssembly() = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIDMAPS 支持数字化样机**：减少物理原型

2. **干涉检查**：自动检测零件碰撞

3. **装配序列**：规划装配顺序

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIDMAPS.htm](../api-reference/interfaces/CATIDMAPS.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
