---
module: "CAAV5V6FeatureModelerExt.edu"
category: "V5V6 特征建模器扩展"
tier: "7"
status: "已完成"
---

# CAAV5V6FeatureModelerExt.edu — V5V6 特征建模器扩展

## 模块定位

CAAV5V6FeatureModelerExt 演示了 **CATIA V5 到 V6 特征建模器迁移的 CAA 编程接口**。V5V6 扩展用于：
- V5 特征兼容
- 特征转换
- 版本迁移

**依赖关系**：基于 CAAV5V6MechanicalModeler。

---

## 核心接口

### CATIV5V6Compatibility — V5V6 兼容接口

```cpp
class CATIV5V6Compatibility : public CATBaseUnknown {
    // 检测 V5 特征
    virtual HRESULT DetectV5Features(CATLISTP(CATBaseUnknown) ** features) = 0;
    
    // 转换为 V6 特征
    virtual HRESULT ConvertToV6(CATISpecObject * v5Feature, CATISpecObject ** v6Feature) = 0;
    
    // 批量迁移
    virtual HRESULT MigrateAll() = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIV5V6Compatibility 处理版本迁移**：V5 到 V6 的平滑过渡

2. **特征等价映射**：识别 V5 和 V6 的对应特征

3. **自动化迁移**：减少手工工作量

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIV5V6Compatibility.htm](../api-reference/interfaces/CATIV5V6Compatibility.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
