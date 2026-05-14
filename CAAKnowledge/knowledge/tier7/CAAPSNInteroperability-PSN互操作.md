---
module: "CAAPSNInteroperability.edu"
category: "PSN 互操作"
tier: "7"
status: "已完成"
---

# CAAPSNInteroperability.edu — PSN 互操作性

## 模块定位

CAAPSNInteroperability 演示了 **CATIA PSN（Platform Simulation）互操作性的 CAA 编程接口**。PSN 互操作用于：
- 多学科仿真集成
- 数据格式转换
- 仿真结果交换

**依赖关系**：基于 CAAAnalysisInterfaces。

---

## 核心接口

### CATIPSNInterop — PSN 互操作接口

```cpp
class CATIPSNInterop : public CATBaseUnknown {
    // 导入仿真数据
    virtual HRESULT ImportData(const CATUnicodeString & format, const CATUnicodeString & path) = 0;
    
    // 导出仿真数据
    virtual HRESULT ExportData(const CATUnicodeString & format, const CATUnicodeString & path) = 0;
    
    // 转换格式
    virtual HRESULT Convert(CATIPSNData * input, CATIPSNData ** output) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIPSNInterop 支持多学科数据交换**：结构、流体、热等

2. **格式转换**：支持多种仿真格式

3. **集成工作流**：多学科协同仿真

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIPSNInterop.htm](../api-reference/interfaces/CATIPSNInterop.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
