---
module: "CAAProductStructureE5i.edu"
category: "产品结构 E5i 集成"
tier: "4"
status: "已完成"
---

# CAAProductStructureE5i.edu — 产品结构 E5i 集成

## 模块定位

CAAProductStructureE5i 演示了 **CATIA 与 ENOVIA V5 的集成**（即 E5i 集成）。它展示了：
- ENOVIA V5 保存命令的实现
- PDM 保存功能
- 提交和回滚事务
- V5 集成工具栏

**依赖关系**：基于 CAAProductStructure 和 CAAProductStructureUI。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────┐
│                   ENOVIA V5 集成 (CAAProductStructureE5i)         │
├─────────────────────────────────────────────────────────────────┤
│  CAAEnoviaV5SaveToPDMCmd                                        │
│  ├── BuildGraph() — 构建状态图                                  │
│  ├── OnOKSelected() — 执行 PDM 保存                            │
│  └── 通知面板 (CATDlgNotify)                                    │
├─────────────────────────────────────────────────────────────────┤
│  CAAEV5CommitAndRollback                                        │
│  ├── Commit — 提交更改                                          │
│  └── Rollback — 回滚更改                                        │
├─────────────────────────────────────────────────────────────────┤
│  CAACV5EV5IntegrationToolbar                                     │
│  ├── 创建 ENOVIA 工具栏                                         │
│  └── 保存、签出等命令                                           │
└─────────────────────────────────────────────────────────────────┘
```

---

## 核心类详解

### 1. CAAEnoviaV5SaveToPDMCmd — PDM 保存命令

```cpp
class CAAEnoviaV5SaveToPDMCmd : public CATStateCommand {
    DeclareResource(CAAEnoviaV5SaveToPDMCmd, CATStateCommand)
    
    // 状态命令生命周期
    virtual void BuildGraph();
    virtual CATStatusChangeRC Activate(CATCommand *iFromClient, CATNotification *iEvtDat);
    virtual CATStatusChangeRC Desactivate(CATCommand *iFromClient, CATNotification *iEvtDat);
    virtual CATStatusChangeRC Cancel(CATCommand *iFromClient, CATNotification *iEvtDat);
    
    // 动作
    CATBoolean OnOKSelected(void *data);
    
private:
    // 服务方法
    HRESULT EditDocument(CATDocument *pToBeEditedDoc);
    HRESULT GetDocumentRootProdRef(CATDocument *ipDoc, CATIProduct_var &ohRefProd);
    HRESULT InsertDocument(CATDocument* ipDocFather, CATDocument* ipDocSon, CATIProduct_var &ohInstProd);
    HRESULT ComputeDataPath(CATUnicodeString &iDocName, int iDocFuturVaultMode, CATUnicodeString &oDocPath);
    
    // UI 组件
    CATDlgNotify *_pEV5SaveDlgNfy;       // 通知面板
    CATDialogAgent *_pCancelNfyAgent;   // 取消代理
    CATDialogAgent *_pOKNfyAgent;        // 确定代理
};
```

**设计意图**：使用 CATStateCommand 实现 PDM 保存流程，包括选择文件、设置元数据、提交到 ENOVIA 等步骤。

### 2. CAAEV5CommitAndRollback — 事务管理

```cpp
class CAAEV5CommitAndRollback : public CATBaseUnknown {
    // 提交更改到 ENOVIA
    HRESULT Commit();
    
    // 回滚更改
    HRESULT Rollback();
};
```

**设计意图**：封装 ENOVIA V5 的事务操作，确保数据一致性。

### 3. CAACV5EV5IntegrationToolbar — 集成工具栏

```cpp
class CAACV5EV5IntegrationToolbar : public CATBaseUnknown {
    // 创建 ENOVIA 相关的工具栏
    CATCmdContainer * CreateToolbar();
};
```

---

## 实现模式

### 1. 状态命令模式

```cpp
void CAAEnoviaV5SaveToPDMCmd::BuildGraph() {
    // 创建通知面板
    _pEV5SaveDlgNfy = new CATDlgNotify(
        GetTopWindow(), 
        "EV5SaveNotify");
    
    // 创建代理
    _pCancelNfyAgent = new CATDialogAgent("CancelAgent");
    _pOKNfyAgent = new CATDialogAgent("OKAgent");
    
    // 添加到状态
    AddDialogAgent(_pCancelNfyAgent);
    AddDialogAgent(_pOKNfyAgent);
    
    // 创建状态转换
    AddTransition(
        NULL, IsOutputSetCondition(_pOKNfyAgent),
        Action((ActionMethod)&CAAEnoviaV5SaveToPDMCmd::OnOKSelected));
}
```

### 2. ENOVIA 集成模式

```cpp
// 获取文档根产品
HRESULT CAAEnoviaV5SaveToPDMCmd::GetDocumentRootProdRef(
    CATDocument *ipDoc, 
    CATIProduct_var &ohRefProd) {
    
    // QueryInterface 获取 CATInit
    CATInit *pInit = NULL;
    HRESULT rc = ipDoc->QueryInterface(IID_CATInit, (void**)&pInit);
    
    if (SUCCEEDED(rc)) {
        // 获取根容器
        CATBaseUnknown *pRoot = pInit->GetRootContainer("CATIContainer");
        
        // 查询 CATIProduct
        if (pRoot) {
            rc = pRoot->QueryInterface(
                IID_CATIProduct, 
                (void**)&ohRefProd);
            pRoot->Release();
        }
        pInit->Release();
    }
    
    return rc;
}
```

---

## 关键设计模式

| 模式 | CAA 实现 | 示例 |
|------|------|------|
| 状态命令 | CATStateCommand | CAAEnoviaV5SaveToPDMCmd |
| 通知面板 | CATDlgNotify | 保存确认对话框 |
| 事务管理 | Commit/Rollback | 更改的原子性 |
| ENOVIA 集成 | CATIProduct + ENOVIA API | PDM 保存 |

---

## 对 AI agent 的要点

1. **ENOVIA V5 集成使用 CATIProduct 接口**：所有操作都通过产品对象进行

2. **PDM 保存流程**：
   - 显示通知面板让用户确认
   - 获取文档根产品
   - 计算数据路径
   - 提交到 ENOVIA

3. **事务管理确保数据一致性**：Commit 成功后更改永久化，Rollback 撤销所有更改

4. **CATDlgNotify 用于显示信息面板**：在执行操作前向用户确认

5. **CATDialogAgent 用于处理用户的 OK/Cancel 选择**

6. **ENOVIA 工具栏整合了常用的 PDM 操作**：保存、签出、签入等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATStateCommand.htm](../api-reference/interfaces/CATStateCommand.htm)
- 完整方法签名: [api-reference/interfaces/CATIProduct.htm](../api-reference/interfaces/CATIProduct.htm)
- 完整方法签名: [api-reference/interfaces/CATDialogAgent.htm](../api-reference/interfaces/CATDialogAgent.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/](../use-cases/)
