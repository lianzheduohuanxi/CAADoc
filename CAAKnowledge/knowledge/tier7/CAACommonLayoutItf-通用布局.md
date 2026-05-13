---
module: "CAACommonLayoutItf.edu"
category: "通用布局接口"
tier: "7"
status: "已完成"
---

# CAACommonLayoutItf.edu — 通用布局接口

## 模块定位

CAACommonLayoutItf 演示了 **CATIA 通用布局（Common Layout）的 CAA 编程接口**。通用布局用于：
- 2D 布局定义
- 布局元素管理
- 布局规则

**依赖关系**：基础框架。

---

## 核心接口

### CATILayout — 布局接口

```cpp
class CATILayout : public CATBaseUnknown {
    // 添加布局元素
    virtual HRESULT AddElement(CATISpecObject * elem, const CATMathPoint2D & pos) = 0;
    
    // 获取元素位置
    virtual HRESULT GetElementPosition(CATISpecObject * elem, CATMathPoint2D & pos) = 0;
    
    // 更新布局
    virtual HRESULT Update() = 0;
}
```

---

## 对 AI agent 的要点

1. **CATILayout 管理 2D 布局**：支持元素定位

2. **布局规则**：定义元素放置规则

3. **与其他模块集成**：支持工程图、装配等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATILayout.htm](../api-reference/interfaces/CATILayout.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
