---
module: "CAASecuritySSOCClient.edu"
category: "SSO 安全客户端"
tier: "7"
status: "已完成"
---

# CAASecuritySSOCClient.edu — SSO 安全客户端

## 模块定位

CAASecuritySSOCClient 演示了 **CATIA SSO（Single Sign-On）安全客户端的 CAA 编程接口**。SSO 安全用于：
- 单点登录认证
- 权限管理
- 加密通信

**依赖关系**：基础框架。

---

## 核心接口

### CATISecurity — 安全接口

```cpp
class CATISecurity : public CATBaseUnknown {
    // 登录
    virtual HRESULT Login(const CATUnicodeString & user, const CATUnicodeString & password) = 0;
    
    // 登出
    virtual HRESULT Logout() = 0;
    
    // 检查权限
    virtual HRESULT CheckPermission(const CATUnicodeString & resource) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATISecurity 管理用户认证**：单点登录

2. **权限控制**：基于角色的访问控制

3. **与企业系统集成**：与 LDAP、Active Directory 集成

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATISecurity.htm](../api-reference/interfaces/CATISecurity.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
