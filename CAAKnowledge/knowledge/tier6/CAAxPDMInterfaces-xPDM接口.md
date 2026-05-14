---
module: "CAAxPDMInterfaces.edu"
category: "xPDM 接口"
tier: "6"
status: "已完成"
---

# CAAxPDMInterfaces.edu — xPDM 接口

## 模块定位

CAAxPDMInterfaces 演示了 **CATIA xPDM（扩展产品数据管理）模块的 CAA 编程接口**。xPDM 用于：
- PDM 系统集成
- 文档管理
- 版本控制
- 配置管理

**依赖关系**：基于 CAAProductStructure，需要 CATIPLM* 接口。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────┐
│                   xPDM 接口 (CAAxPDMInterfaces)                      │
├─────────────────────────────────────────────────────────────────┤
│  xPDM Addin                                                     │
│  └── CAAxPDMWbAddin — xPDM 工作台 Addin                        │
├─────────────────────────────────────────────────────────────────┤
│  xPDM 操作                                                      │
│  ├── CAAxPDMLogicalPhysic — 逻辑到物理转换                    │
│  ├── CAAxPDMPdmAccess — PDM 访问                             │
│  └── CAAxPDMV5Access — V5 访问                               │
├─────────────────────────────────────────────────────────────────┤
│  PDM 命令                                                       │
│  ├── CAAxPDMLogicalPhysicCmd — 逻辑物理转换命令               │
│  ├── CAAxPDMDocumnetCmd — 文档命令                           │
│  └── CAAxPDMOpenCmd — 打开命令                               │
└─────────────────────────────────────────────────────────────────┘
```

---

## 核心接口

### CATIxPDMAddin — xPDM Addin

```cpp
class CAAxPDMWbAddin : public CATBaseUnknown {
    void CreateCommands();
    CATCmdContainer * CreateToolbars();
}
```

### PDM 访问接口

```cpp
// 访问 PDM 系统
class CAAxPDMPdmAccess : public CATBaseUnknown {
    // 连接到 PDM
    virtual HRESULT Connect(const CATUnicodeString & server) = 0;
    
    // 获取文档
    virtual HRESULT GetDocument(const CATUnicodeString & id, CATDocument ** doc) = 0;
    
    // 保存到 PDM
    virtual HRESULT SaveToPDM() = 0;
}
```

---

## 对 AI agent 的要点

1. **xPDM 是 PDM 系统的 CAA 抽象层**：支持多种 PDM 系统

2. **CATIPLM* 系列接口是核心**：CATIPLMEntity、CATIPLMRecordDescriptor 等

3. **逻辑-物理转换**是 xPDM 的核心功能：将逻辑设计转换为物理实现

4. **版本控制**：支持文档的版本历史和变更管理

5. **配置管理**：管理产品的不同配置变体

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIPLMEntity.htm](../api-reference/interfaces/CATIPLMEntity.htm)
- 完整方法签名: [api-reference/interfaces/CATIPLMRecordDescriptor.htm](../api-reference/interfaces/CATIPLMRecordDescriptor.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
