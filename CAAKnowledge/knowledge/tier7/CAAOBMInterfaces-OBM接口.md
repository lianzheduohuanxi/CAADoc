---
module: "CAAOBMInterfaces.edu"
category: "OBM 接口"
tier: "7"
status: "已完成"
---

# CAAOBMInterfaces.edu — OBM 接口

## 模块定位

CAAOBMInterfaces 演示了 **CATIA OBM（Object Based Modeling）的 CAA 编程接口**。OBM 用于：
- 基于对象的建模
- 对象行为定义
- 对象关系管理

**依赖关系**：基础框架。

---

## 核心接口

### CATIOBMObject — OBM 对象接口

```cpp
class CATIOBMObject : public CATBaseUnknown {
    // 获取对象类型
    virtual CATBSTR GetObjectType() = 0;
    
    // 获取属性
    virtual HRESULT GetAttribute(const CATUnicodeString & name, VARIANT & value) = 0;
    
    // 设置属性
    virtual HRESULT SetAttribute(const CATUnicodeString & name, const VARIANT & value) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIOBMObject 定义对象行为**：属性和行为封装

2. **面向对象设计**：继承和多态

3. **与其他模块集成**：支持复杂系统建模

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIOBMObject.htm](../api-reference/interfaces/CATIOBMObject.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
