---
module: "CAAComponentsCatalogs.edu"
category: "组件目录"
tier: "7"
status: "已完成"
---

# CAAComponentsCatalogs.edu — 组件目录

## 模块定位

CAAComponentsCatalogs 演示了 **CATIA 组件目录（Components Catalogs）的 CAA 编程接口**。组件目录用于：
- 标准件库管理
- 组件分类和检索
- 目录发布

**依赖关系**：基于 CAAProductStructure。

---

## 核心接口

### CATICatalog — 目录接口

```cpp
class CATICatalog : public CATBaseUnknown {
    // 获取目录内容
    virtual HRESULT GetContent(CATLISTP(CATBaseUnknown) ** items) = 0;
    
    // 添加组件
    virtual HRESULT AddComponent(CATISpecObject * comp) = 0;
    
    // 检索组件
    virtual HRESULT Search(const CATUnicodeString & criteria, CATLISTP(CATBaseUnknown) ** results) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATICatalog 管理组件集合**：支持添加、删除、检索

2. **与知识工程的结合**：参数化组件定义

3. **分类检索**：按名称、类型、属性搜索

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATICatalog.htm](../api-reference/interfaces/CATICatalog.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
