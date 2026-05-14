---
module: "CAACATIAV4Interfaces.edu"
category: "CATIA V4 接口"
tier: "7"
status: "已完成"
---

# CAACATIAV4Interfaces.edu — CATIA V4 接口

## 模块定位

CAACATIAV4Interfaces 演示了 **CATIA 与 V4 版本兼容的 CAA 编程接口**。V4 兼容性用于：
- V4 数据导入
- V4 格式转换
- 历史数据复用

**依赖关系**：基础框架。

---

## 核心接口

### CATIV4Import — V4 导入接口

```cpp
class CATIV4Import : public CATBaseUnknown {
    // 导入 V4 模型
    virtual HRESULT ImportV4Model(const CATUnicodeString & path) = 0;
    
    // 获取转换选项
    virtual HRESULT GetConversionOptions(CATIV4Options ** options) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIV4Import 处理 V4 数据迁移**：保留历史投资

2. **转换选项**：控制 V4 到 V5/V6 的转换行为

3. **数据完整性**：确保转换过程中数据不丢失

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIV4Import.htm](../api-reference/interfaces/CATIV4Import.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
