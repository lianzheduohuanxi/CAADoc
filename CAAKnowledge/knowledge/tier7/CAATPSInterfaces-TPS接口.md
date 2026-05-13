---
module: "CAATPSInterfaces.edu"
category: "TPS 接口"
tier: "7"
status: "已完成"
---

# CAATPSInterfaces.edu — TPS 接口

## 模块定位

CAATPSInterfaces 演示了 **CATIA TPS（Technological Process Specification）接口的 CAA 编程接口**。TPS 用于：
- 工艺规程定义
- 工艺参数管理
- 工艺文件生成

**依赖关系**：基于 CAAManufacturingItf。

---

## 核心接口

### CATITPS — TPS 接口

```cpp
class CATITPS : public CATBaseUnknown {
    // 添加工序
    virtual HRESULT AddOperation(CATISpecObject * operation) = 0;
    
    // 获取工艺路线
    virtual HRESULT GetProcessPlan(CATLISTP(CATBaseUnknown) ** operations) = 0;
    
    // 生成工艺文件
    virtual HRESULT GenerateDocument(CATUnicodeString & path) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATITPS 管理制造工艺规程**：工序定义和排序

2. **工艺参数**：刀具、切削参数等

3. **文档生成**：工艺卡片、工序卡等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATITPS.htm](../api-reference/interfaces/CATITPS.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
