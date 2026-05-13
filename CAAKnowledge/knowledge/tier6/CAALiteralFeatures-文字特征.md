# CAALiteralFeatures — 知识工程 / Literal Features

**模块**: CAALiteralFeatures.edu | **层级**: Tier 6 | **规模**: 14 个头文件 + 36 个 .cpp

---

## 模块定位

CAALiteralFeatures 是 CAA 知识工程（Knowledge Engineering）最全面的教学模块，覆盖 CATIA 的参数系统、公式/规则/检查、设计表、用户自定义函数、知识集成、参数事件、求值器等完整能力。

---

## 架构概览

```
CAALiteralFeatures.edu/
├── PublicInterfaces/          (3个) — 公共 API
│   ├── CAALifBasis.h          DLL 导出宏
│   ├── CAALifReturnCodes.h    返回码枚举（12个错误码）
│   └── CAALifServices.h       Session/Document/Container 管理
├── ProtectedInterfaces/       (4个) — 内部扩展点
│   ├── CAALifCreateExt.h      CATICreateInstance 实现（工厂）
│   ├── CAALifDicoLibrary.h    用户函数库注册
│   ├── CAALifEval.h           用户函数求值器 _caalifeval0
│   └── CAALifMyVisitor.h      参数遍历 Visitor
├── PrivateInterfaces/         (6个) — 实现级接口
│   ├── CAAExtensionForMeasure.h     Valuator 适配器
│   ├── CAAILifMyFeatureEvents.h    参数事件回调接口
│   ├── CAAIMyFeatureEvents.h       参数事件接口（另一种导出方式）
│   ├── CAALifMyFeatureEventsExt.h  事件扩展（带计数器）
│   ├── CAALifValuatorFeatureDef.h  Valuator 特征工厂
│   └── CAAMyFeatureEventsExt.h     事件扩展（静态计数器）
└── 13个 .m 子模块（共36个.cpp）
```

---

## 核心接口与类

### 1. CAALifServices（公共入口）

负责 Session 创建/销毁、Document 打开/关闭、Container 管理。

```cpp
class CAALifServices {
    HRESULT CreateSession(char *sessionName, CATSession *&pSession);
    HRESULT OpenDocument(const CATUnicodeString &path, CATDocument *&pDoc);
    HRESULT GetRootProduct(CATDocument *pDoc, CATIProduct *&piRoot);
    HRESULT Cleanup(CATDocument *pDoc, const char *sessionName);
};
```

**依赖**: System, ObjectModelerBase, ProductStructure

### 2. CAALifReturnCodes（返回码）

```cpp
enum CAALifReturnCodes {
    Success = 0,
    ErrorCreateSession = 1,
    ErrorOpenDocument = 2,
    ErrorGetRootProduct = 3,
    ErrorInitializeElecEnv = 4,
    ErrorRetrieveGeomBundle = 5,
    // ... 共 12 个错误码
};
```

### 3. CAALifDicoLibrary + CAALifEval（用户函数系统）

**注册用户函数** — CAALifDicoLibrary 实现 CATIAddLibrary::Add，注册 `CAAHypothenuse`：

```cpp
// CAALifDicoLibrary.cpp
HRESULT CAALifDicoLibrary::Add(CATIDictionary *piDico) {
    // 注册 CAAHypothenuse(A, B) = sqrt(A² + B²)
    // 绑定求值器 _caalifeval0
}
```

**求值器实现** — CAALifEval.cpp：

```cpp
// CAAHypothenuse 的求值逻辑
double result = sqrt(A * A + B * B);
```

**工厂创建** — CAALifCreateExt 实现 CATICreateInstance，动态创建 CAALifDicoLibrary：

```cpp
HRESULT CAALifCreateExt::CreateInstance(void **oPPV) {
    *oPPV = new CAALifDicoLibrary();
}
```

### 4. CAALifMyVisitor（参数遍历器）

继承自 CATVisitorAdapter，遍历参数树并打印每个参数名称：

```cpp
class CAALifMyVisitor : public CATVisitorAdapter {
    HRESULT Visit(const CATBaseUnknown_var &iObject);
    // 通过 QI 获取 CATIParmPublisher，遍历子参数
};
```

### 5. CAAILifMyFeatureEvents（参数事件）

参数变更/可视化/删除的事件回调接口：

```cpp
class CAAILifMyFeatureEvents : public CATBaseUnknown {
    virtual HRESULT OnParameterChanged(CATBaseUnknown *iParam);
    virtual HRESULT OnVisualizationChanged(CATBaseUnknown *iParam);
    virtual HRESULT OnDeleted(CATBaseUnknown *iParam);
};
```

### 6. CAAExtensionForMeasure（Valuator 适配器）

继承 CATParmValuatorAdapter，根据输入参数的奇偶性计算输出：

```cpp
// CAAExtensionForMeasure.cpp
// 实现 CATIParmValuator: 读取输入参数，计算输出值
// 输入为偶数 → 输出 = 输入 * 2
// 输入为奇数 → 输出 = 输入 * 3
```

---

## 子模块详解（13个 .m 模块）

### CAALifBasis.m（基础服务层）
| 文件 | 功能 |
|------|------|
| CAALifCreateExt.cpp | CATICreateInstance 工厂实现 |
| CAALifDicoLibrary.cpp | CATIAddLibrary::Add，注册 CAAHypothenuse |
| CAALifEval.cpp | 用户函数求值器（sqrt(A²+B²)） |
| CAALifMyPublisher.cpp | CATIParmPublisher 实现（子特征增删查） |
| CAALifMyVisitor.cpp | CATIVisitor::Visit，遍历参数 |
| CAALifServices.cpp | Session/Document/Container 生命周期 |

### CAALifGettingStarted.m（入门）
- **CAALifGettingStarted.cpp**: 创建参数与公式的最简示例 — 圆柱体积 `PI*R²*L`

### CAALifParameters.m（参数管理）
| 文件 | 功能 |
|------|------|
| CAALifParametersPersistent.cpp | 持久化参数：Integer/Real/String/Boolean/Length/Angle/Volume |
| CAALifParametersVolatile.cpp | Volatile 参数（含枚举类型） |
| CAALifParametersMani.cpp | 微调器 Manipulator 创建与范围约束 |
| CAALifParametersRights.cpp | 参数访问权限管理（ReadOnly 等） |

### CAALifRelations.m（关系）
| 文件 | 功能 |
|------|------|
| CAALifFormula.cpp | 公式创建与修改（字符串提取 `a1.Extract(0,6)`） |
| CAALifRuleCheck.cpp | Rule 与 Check 的创建 |
| CAALifRelationMain.cpp | 关系测试入口 |

### CAALifExpressions.m（表达式）
| 文件 | 功能 |
|------|------|
| CAALifExpressionVolatile.cpp | Volatile 表达式创建与求值（Program/Constraint/Functional） |
| CAALifExpressionMain.cpp | 表达式测试入口 |

### CAALifDesignTable.m（设计表）
| 文件 | 功能 |
|------|------|
| CAALifDesignTableAccess.cpp | 设计表访问（关联、列名、单元格值） |
| CAALifDesignTableCreate.cpp | 设计表创建与关联管理 |
| CAALifDesignTableMain.cpp | 设计表主程序 |

### CAALifIntegrateKnowledge.m（知识集成）
| 文件 | 功能 |
|------|------|
| CAALifAddLibrary.cpp | CATIAddTypeLibrary：注册 Screw/Bolt 用户类型和 EvaluateScrewVolume 函数 |
| CAALifAddLibraryExt.cpp | CATICreateInstance 扩展 |
| CAALifInstanceScrewExt.cpp | CATIInstance 实现，管理 Screw 实例属性读写 |

### CAALifEvents.m（事件）
| 文件 | 功能 |
|------|------|
| CAALifEventsMain.cpp | 参数事件订阅与回调测试 |
| CAALifMyFeatureEventsExt.cpp | 实现 CAAILifMyFeatureEvents（变更/可视化/删除） |

### CAALifValuator.m（求值器）
| 文件 | 功能 |
|------|------|
| CAAExtensionForMeasure.cpp | CATIParmValuator 实现（奇偶判断输出） |
| CAALifValuatorFeatureDef.cpp | Valuator 特征工厂（Startup、实例化、输入/输出属性） |
| CAALifValuatorMain.cpp | Valuator 测试（创建→更新→验证） |

### CAALifParameterSet.m（参数集）
- **CAALifParameterSetMain.cpp**: 加载 Part，遍历参数集，在 Pad 下创建新参数集

### CAALifPublish.m（发布）
- **CAALifPublishMain.cpp**: 特征实例化、参数聚合、Visitor 遍历

### CAALifParamFrame.m / CAALifParameterEditor.m（交互式 UI）
| 文件 | 功能 |
|------|------|
| CAALifApplication.cpp / CAALifApplication2.cpp | 交互式应用入口 |
| CAALifWindow.cpp | 参数框架窗口：参数/公式/微调器 + 事件订阅 |
| CAALifWindow2.cpp | 使用 CATIParameterEditor 自定义编辑参数 |

### CAALifUserFunctions.m（用户函数）
- **CAALifUserFunctionsMain.cpp**: 加载包、列出函数、创建 CAAHypothenuse 公式

---

## 关键设计模式

### 1. 工厂模式（CATICreateInstance）
CAALifCreateExt 实现 CATICreateInstance，根据请求类型动态创建 CAALifDicoLibrary 或其他对象。

### 2. Visitor 模式
CAALifMyVisitor 继承 CATVisitorAdapter，遍历特征树的参数节点。

### 3. Publisher/Subscriber 事件模式
- CAALifMyPublisher 实现 CATIParmPublisher（管理子特征）
- CAAILifMyFeatureEvents 订阅参数变更/可视化/删除事件

### 4. Valuator 模式
CAAExtensionForMeasure 继承 CATParmValuatorAdapter，根据输入参数动态计算输出值。

### 5. TIE 绑定模式
大量使用 `TIE_XXX` 宏将实现类绑定到接口（如 CATIAddLibrary, CATICreateInstance, CATIParmPublisher）。

---

## 依赖关系

```
System → ObjectModelerBase → ProductStructure → KnowledgeInterfaces
  → ObjectSpecsModeler → MecModInterfaces → Mathematics → Dialog
  → Visualization → LiteralFeatures
```

---

## 使用场景

| 场景 | 对应模块 |
|------|----------|
| 创建参数（Integer/Real/String/Length/Angle/Volume） | CAALifParameters.m |
| 创建公式（参数间关系） | CAALifRelations.m / CAALifGettingStarted.m |
| 创建 Rule/Check | CAALifRelations.m |
| 注册用户自定义函数（如 CAAHypothenuse） | CAALifBasis.m |
| 注册用户自定义类型（如 Screw/Bolt） | CAALifIntegrateKnowledge.m |
| 创建和使用设计表 | CAALifDesignTable.m |
| 监听参数变更事件 | CAALifEvents.m |
| 自定义参数编辑器 | CAALifParameterEditor.m |
| Valuator（动态计算特征输出） | CAALifValuator.m |
| 表达式（Program/Constraint/Functional） | CAALifExpressions.m |
| 参数集管理 | CAALifParameterSet.m |

---

## 总结

CAALiteralFeatures 是 CAA 知识工程最完整的教学模块，覆盖了 CATIA 参数化设计的全部能力。它展示了从基础参数创建到高级知识集成（用户类型注册、Valuator 特征工厂、表达式求值）的完整层次，是理解 CATIA Knowledgeware 架构的最佳入口。