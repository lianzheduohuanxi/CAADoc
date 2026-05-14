---
module: "CAADraftingInterfaces.edu"
category: "工程图接口"
tier: "6"
status: "已完成"
---

# CAADraftingInterfaces.edu — 工程图接口

## 模块定位

CAADraftingInterfaces 演示了 **CATIA 工程图（Drafting）模块的 CAA 编程接口**。工程图模块用于：
- 创建工程图视图
- 添加尺寸标注
- 添加注释和符号
- 生成图纸和标题栏

**依赖关系**：基于 Tier 1 的 CAAApplicationFrame，需要 CATIDrw* 接口。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────┐
│                   工程图接口 (CAADraftingInterfaces)                │
├─────────────────────────────────────────────────────────────────┤
│  工程图 Addin                                                    │
│  └── CAADrwAddin — 创建工程图命令                               │
├─────────────────────────────────────────────────────────────────┤
│  视图操作 (View Operations)                                       │
│  ├── CAADrwCreateViewFrom3D — 从 3D 创建视图                    │
│  ├── CAADrwCreateSectionFromPlane — 创建剖视图                   │
│  └── CAADrwCreateSectionFrom3DSketch — 从 3D 草图创建剖视图     │
├─────────────────────────────────────────────────────────────────┤
│  标注操作 (Annotation Operations)                                │
│  ├── CAADrwCreateDim — 创建尺寸                                │
│  ├── CAADrwDimDressup — 尺寸装饰                              │
│  ├── CAADrwCreateDimSyst — 创建尺寸系统                        │
│  └── CAADrwCallout — 创建引出标注                             │
├─────────────────────────────────────────────────────────────────┤
│  其他操作 (Other Operations)                                      │
│  ├── CAADrwCenterLine — 中心线                                │
│  ├── CAADrwCoordinates — 坐标标注                              │
│  ├── CAADrwCreatePattern — 创建阵列                            │
│  └── CAADrwTitleBlock — 标题栏                               │
└─────────────────────────────────────────────────────────────────┘
```

---

## 核心接口

### CATIDrwView — 工程图视图

```cpp
// 创建投影视图
class CAADrwCreateViewFrom3D : public CATStateCommand {
    void BuildGraph();
    CATBoolean CreateView(void *);
}
```

### CATIDrwDim — 尺寸

```cpp
// 创建尺寸
class CAADrwCreateDim : public CATStateCommand {
    void BuildGraph();
    CATBoolean CreateDimension(void *);
}
```

### CATIDrwAnnotation — 注释

```cpp
// 创建注释
class CAADrwCallout : public CATStateCommand {
    // 引出标注
}
```

---

## 实现模式

### 创建工程图视图

```cpp
CATBoolean CAADrwCreateViewFrom3D::CreateView(void *) {
    // 1. 获取选中的 3D 几何
    // 2. 创建投影
    // 3. 添加到图纸
    return TRUE;
}
```

### 创建尺寸

```cpp
CATBoolean CAADrwCreateDim::CreateDimension(void *) {
    // 1. 选择要标注的几何元素
    // 2. 确定尺寸类型（线性、角度、直径等）
    // 3. 创建尺寸对象
    // 4. 设置样式和公差
    return TRUE;
}
```

---

## 对 AI agent 的要点

1. **工程图使用 CATIDrw* 系列接口**：CATIDrwView、CATIDrwDim 等

2. **视图类型**：
   - 投影视图（Projection View）
   - 剖视图（Section View）
   - 局部视图（Detail View）
   - 等轴测视图（Isometric View）

3. **尺寸类型**：
   - 线性尺寸（Linear）
   - 角度尺寸（Angular）
   - 直径尺寸（Diameter）
   - 半径尺寸（Radius）

4. **图纸布局**：视图放置、比例调整、视图对齐

5. **注释符号**：表面粗糙度、焊接符号、基准符号等

6. **样式管理**：字体、高度、公差等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIDrwView.htm](../api-reference/interfaces/CATIDrwView.htm)
- 完整方法签名: [api-reference/interfaces/CATIDrwDim.htm](../api-reference/interfaces/CATIDrwDim.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
