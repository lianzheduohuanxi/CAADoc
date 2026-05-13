---
module: "CAAElecDeviceItf.edu"
category: "电气设备接口"
tier: "6"
status: "已完成"
---

# CAAElecDeviceItf.edu — 电气设备接口

## 模块定位

CAAElecDeviceItf 演示了 **CATIA 电气设备（Electrical Device）模块的 CAA 编程接口**。电气设备用于：
- 电气元件建模
- 设备连接定义
- 电气特性管理

**依赖关系**：基于 Tier 3 的 CAAGSMInterfaces。

---

## 核心接口

### 电气设备接口

```cpp
// 电气设备相关的接口
class CATIElecDevice {
    // 获取设备类型
    virtual CATBSTR GetDeviceType() = 0;
    
    // 获取连接点
    virtual HRESULT GetConnectionPoints(CATLISTP(CATBaseUnknown) ** points) = 0;
    
    // 设置电气特性
    virtual HRESULT SetElectricalCharacteristics() = 0;
}
```

---

## 对 AI agent 的要点

1. **电气设备是线束设计的基础**：定义元件和连接

2. **连接点（Connection Points）**是关键：定义电气连接的位置

3. **CATIElecDevice 接口管理设备属性**：类型、规格等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIElecDevice.htm](../api-reference/interfaces/CATIElecDevice.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
