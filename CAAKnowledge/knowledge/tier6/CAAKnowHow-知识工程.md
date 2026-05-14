---
module: "CAAKnowHow.edu"
category: "知识工程"
tier: "6"
status: "已完成"
---

# CAAKnowHow.edu — 知识工程

## 模块定位

CAAKnowHow 演示了 **CATIA 知识工程（Knowledge Engineering）模块的 CAA 编程接口**。知识工程用于：
- 规则定义和执行
- 参数化建模
- 公式和约束
- 知识库访问

**依赖关系**：基于 Tier 1 的 CAAObjectSpecsModeler，需要 CATICke* 接口。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────┐
│                   知识工程 (CAAKnowHow)                            │
├─────────────────────────────────────────────────────────────────┤
│  规则基 (Rule Base)                                             │
│  ├── CAARuleBase — 规则基定义                                   │
│  ├── CAAKhwUserFunctionLibrary — 用户函数库                     │
│  └── CAACommonFunction — 通用函数                              │
├─────────────────────────────────────────────────────────────────┤
│  用户函数 (User Functions)                                      │
│  ├── CAAConcatenateStringUserFunction — 字符串连接              │
│  ├── CAAFindAttributeRealUserFunction — 属性查找               │
│  └── CAAGenerateResultsUserFunction — 结果生成                  │
├─────────────────────────────────────────────────────────────────┤
│  规则应用 (Rule Application)                                    │
│  ├── CAARuleBaseApplication — 规则应用                         │
│  ├── CAAParametrizeRuleBase — 参数化规则基                    │
│  └── CAARuleBaseProtection — 规则保护                          │
└─────────────────────────────────────────────────────────────────┘
```

---

## 核心概念

### 知识工程的核心接口

```cpp
// 规则基接口
class CAACreationRuleBase : public CATBaseUnknown {
    // 创建规则
    virtual HRESULT CreateRule() = 0;
    
    // 应用规则
    virtual HRESULT ApplyRule() = 0;
};

// 用户函数基类
class CAAKhwUserFunctionLibrary : public CATBaseUnknown {
    // 执行用户函数
    virtual HRESULT Execute() = 0;
    
    // 获取参数
    virtual HRESULT GetParameters() = 0;
}
```

---

## 实现模式

### 用户函数实现

```cpp
// CAAConcatenateStringUserFunction.cpp
class CAAConcatenateStringUserFunction : public CATBaseUnknown {
    // 实现字符串连接逻辑
    HRESULT Execute() {
        // 获取输入参数
        // 连接字符串
        // 返回结果
    }
};
```

---

## 对 AI agent 的要点

1. **知识工程使用 CATICke* 系列接口**：CATICkeFunction、CATICkeParm 等

2. **规则用于自动化决策**：根据条件自动执行操作

3. **用户函数扩展知识能力**：可以自定义计算逻辑

4. **参数化实现设计意图复用**：同一规则应用于不同几何

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATICkeFunction.htm](../api-reference/interfaces/CATICkeFunction.htm)
- 完整方法签名: [api-reference/interfaces/CATICkeParm.htm](../api-reference/interfaces/CATICkeParm.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
