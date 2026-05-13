---
module: "CAAFmoFuncModInterfaces.edu"
category: "功能建模接口"
tier: "7"
status: "已完成"
---

# CAAFmoFuncModInterfaces.edu — 功能建模接口

## 模块定位

CAAFmoFuncModInterfaces 演示了 **CATIA 功能建模（Functional Modeling）的 CAA 编程接口**。功能建模用于：
- 功能定义
- 行为建模
- 系统仿真

**依赖关系**：基于 CAAKnowHow。

---

## 核心接口

### CATIFuncModel — 功能模型接口

```cpp
class CATIFuncModel : public CATBaseUnknown {
    // 添加功能
    virtual HRESULT AddFunction(CATIFunction * func) = 0;
    
    // 连接功能
    virtual HRESULT ConnectFunction(CATIFunction * from, CATIFunction * to) = 0;
    
    // 仿真
    virtual HRESULT Simulate() = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIFuncModel 定义系统功能**：顶层设计

2. **功能连接**：定义功能之间的依赖关系

3. **系统仿真**：验证功能行为

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIFuncModel.htm](../api-reference/interfaces/CATIFuncModel.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
