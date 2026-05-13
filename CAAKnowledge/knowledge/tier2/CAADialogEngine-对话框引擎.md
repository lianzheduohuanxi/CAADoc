---
module: "CAADialogEngine.edu"
category: "CAA 对话框引擎 — 状态命令/Agent/CATISO/CATCSO/Palette/跨文档"
tier: "2"
status: "已完成"
---

# CAADialogEngine.edu — 对话框引擎

## 模块定位

CAADialogEngine 是 CAA 最核心的交互式编程框架，教授 CATIA 的**状态命令引擎（DialogEngine）**。它包含 3 个模块，30+ 个命令实现，覆盖了 CATIA 交互式建模的完整编程范式：

- **CATStateCommand** — 状态机命令架构
- **Dialog Agents** — 4 种交互代理（Indication/PathElement/Dialog/OtherDocument）
- **CATISO** — 临时交互对象（橡皮筋效果）
- **CATCSO** — 当前选中对象集（命令链式调用）
- **Palette** — 命令面板（Check Header + CATIAfrCmdPaletteOptions）
- **跨文档交互** — CATOtherDocumentAgent + CATMultiDocumentCommand
- **摄像机管理** — CATICamera + CATI3DCamera 视角操控
- **自定义通知** — 命令间通信

这是理解 CATIA 所有交互式命令（Part Design, Sketcher, Assembly 等）工作原理的必修框架。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        DialogEngine 核心架构                              │
│                                                                          │
│  CATStateCommand (状态命令基类)                                           │
│  ├── BuildGraph()  — 构建状态图（一生只调用一次）                          │
│  ├── Activate()    — 命令获得焦点                                        │
│  ├── Desactivate() — 命令失去焦点（共享命令抢走焦点）                      │
│  └── Cancel()      — 命令被取消（切换到独占命令）                         │
│                                                                          │
│  状态图（State Graph）：                                                  │
│                                                                          │
│   ┌──────────┐    Transition     ┌──────────┐    Transition              │
│   │  State1  │ ────────────────> │  State2  │ ────────────────> NULL     │
│   │  +Agent1 │    Condition      │  +Agent2 │    Action(CreateLine)      │
│   │  +Agent2 │    + Action       │          │                            │
│   └──────────┘                   └──────────┘                            │
│        │                              │                                  │
│        └────── Cancel ───────────────┘                                   │
│                                                                          │
│  Agent 类型：                                                             │
│  ├── CATIndicationAgent      — 屏幕位置指示                               │
│  ├── CATPathElementAgent     — 选择模型元素                                │
│  ├── CATDialogAgent          — 对话框事件响应                              │
│  └── CATOtherDocumentAgent   — 跨文档选择                                 │
│                                                                          │
│  临时视觉系统：                                                            │
│  ├── CATISO — 临时交互对象（在命令执行期间显示，Cancel/完成后清除）         │
│  └── CATCSO — 当前选中对象集（上一个命令的结果自动成为下一个命令的输入）    │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 核心知识

### 1. CATStateCommand — 状态命令基类

这是 DialogEngine 的核心，所有交互式命令都继承自它：

```cpp
class CAADegCreatePointCmd : public CATStateCommand {
    CmdDeclareResource(CAADegCreatePointCmd, CATStateCommand);
    // 或 CmdDeclareResourceFile(CAADegFileCmd, CAADegCreatePointCmd, CATStateCommand);

    CATStatusChangeRC Activate(CATCommand*, CATNotification*);
    CATStatusChangeRC Desactivate(CATCommand*, CATNotification*);
    CATStatusChangeRC Cancel(CATCommand*, CATNotification*);
    virtual void BuildGraph();  // 核心：构建状态图
};
```

**CATCreateClass 注册**（在 .cpp 中）：
```cpp
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreatePointCmd);
// 使命令可以通过类名字符串实例化，配合命令头部使用
```

**CATStateCommand vs CATCommand**：
- `CATStateCommand` — 有状态图，是 DialogEngine 框架的核心
- `CATCommand` — 简单命令，只有 Activate/Desactivate/Cancel，用于 Palette 按钮等

---

### 2. 状态图构建 — BuildGraph

BuildGraph 是 CATStateCommand 的灵魂方法，在命令首次激活时调用一次。它定义：

1. **Agent** — 用户交互的代理对象
2. **State** — 命令的一个阶段
3. **Transition** — 状态之间的转换（条件 + 动作）

**2.1 创建 Agent**

```cpp
// CATIndicationAgent — 屏幕位置指示（点击空白处）
_daIndication = new CATIndicationAgent("Indication");
// 投影平面：默认为垂直于视线的平面

// CATPathElementAgent — 选择模型元素（点击已有几何体）
_daPathElementCornerPoint = new CATPathElementAgent("daCornerPointId");
_daPathElementCornerPoint->AddElementType(IID_CAAISysPoint);  // 过滤：只选择 Point
_daPathElementCornerPoint->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);
// PSO = Pre-Select Object (预选择高亮)
// HSO = Highlight Selected Object (选中高亮)
// Prevaluation = 鼠标移动时触发求值

// CATOtherDocumentAgent — 跨文档选择
_daSelectionCircle = new CATOtherDocumentAgent("daCircleId");
_daSelectionCircle->AddElementType(IID_CAAISysCircle);
```

**2.2 创建 State**

```cpp
// 初始状态（继承自 CATStateCommand）
CATDialogState *stCornerPoint = GetInitialState("stCornerPointId");
stCornerPoint->AddDialogAgent(_daPathElementCornerPoint);

// 后续状态
CATDialogState *stWidthPoint = AddDialogState("stWidthPointId");
stWidthPoint->AddDialogAgent(_daPathElementWidthPoint);

// CATPanelState — 带对话框的状态
CATPanelState *stState = new CATPanelState(this, "GetPointId", _pPointEditor);
stState->AddDialogAgent(_daIndication);
```

**2.3 创建 Transition**

```cpp
// 基本转换：从 State1 到 State2
AddTransition(
    stStartState,               // 源状态
    stEndState,                 // 目标状态（NULL = 命令结束）
    AndCondition(               // 复合条件
        IsOutputSetCondition(_daIndication),  // Agent 有输出
        Condition((ConditionMethod)&MyCmd::CheckData)  // 自定义条件
    ),
    Action((ActionMethod)&MyCmd::ProcessData)  // 动作
);

// 自循环转换（橡皮筋效果）
AddTransition(
    stState,
    stState,                    // 目标 = 源 = 自循环
    IsLastModifiedAgentCondition(_daIndication),  // Agent 上次被修改
    Action((ActionMethod)&MyCmd::UpdatePreview)
);

// 自定义 Apply/OK 转换
CATCustomizableTransition* pApply = stState->GetApplyTransition();
pApply->SetCondition(Condition((ActionMethod)&MyCmd::CheckPoint));
pApply->SetAction(Action((ActionMethod)&MyCmd::CreateByBox));
```

**转换的语法要素**：

| 要素 | 方法 | 说明 |
|------|------|------|
| 源状态 | 第一个参数 | State 指针 |
| 目标状态 | 第二个参数 | NULL = 命令结束 |
| 条件 | `IsOutputSetCondition` / `AndCondition` / `Condition` | 布尔值，TRUE 才触发 |
| 动作 | `Action` | CATBoolean 返回值的方法 |
| 复合条件 | `AndCondition(a, b)` | 所有条件都满足才触发 |
| Agent 条件 | `IsOutputSetCondition(agent)` | Agent 有输出值 |
| Agent 修改 | `IsLastModifiedAgentCondition(agent)` | Agent 值被修改（用于橡皮筋） |

---

### 3. 状态命令生命周期

```
创建 ──> BuildGraph ──> Activate ──> [状态1] ──> [状态2] ──> NULL
                            │                      │
                      Desactivate              Cancel
                      (共享命令抢焦点)         (独占命令抢焦点/命令结束)
                            │                      │
                            └── Activate(Resume) ──┘
```

**Activate 两种模式**：
```cpp
CATStatusChangeRC Activate(CATCommand*, CATNotification* iNotif) {
    if (iNotif->GetType() == CATStateActivateNotification::Begin) {
        // 命令从头开始
    } else if (iNotif->GetType() == CATStateActivateNotification::Resume) {
        // 从暂停状态恢复（共享命令执行完返回）
    }
    return CATStatusChangeRCCompleted;
}
```

---

### 4. Agent 行为设置

**4.1 CATPathElementAgent 行为标志**

```cpp
// 基本选择 + 高亮
_daPathElement->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);

// 多选模式（AnalysisNumericCmd 使用）
_daMultiAcquisitionSelModes->SetBehavior(
    CATDlgEngMultiAcquisitionSelModes |  // 多选模式（每次点击添加）
    CATDlgEngWithPrevaluation
);

_daMultiAcquisitionCtrl->SetBehavior(
    CATDlgEngMultiAcquisitionCtrl |      // Ctrl 多选
    CATDlgEngWithPrevaluation
);

_daMultiAcquisitionUserCtrl->SetBehavior(
    CATDlgEngMultiAcquisitionUserCtrl |  // 用户控制多选
    CATDlgEngWithPrevaluation
);
```

**4.2 CATIndicationAgent 行为标志**

```cpp
// 预求值时接受（鼠标移动时更新）
_daIndication->SetBehavior(CATDlgEngAcceptOnPrevaluate | CATDlgEngWithPrevaluation);

// 带 Undo 支持
_daIndication->SetBehavior(CATDlgEngWithUndo);
```

**4.3 CATIndicationAgent 投影平面**

```cpp
// 默认：垂直于当前视线的平面（自动）
_daIndication = new CATIndicationAgent("Id");

// 显式设置投影平面（CreateBox 使用）
CATMathPlane ProjectionPlane(OriginPoint, Normal);
_daIndicationDepthPoint->SetMathPlane(ProjectionPlane);
```

---

### 5. CATISO — 临时交互对象系统

CATISO 用于在命令执行期间显示临时几何体（橡皮筋效果），在 Cancel 或命令完成时清除：

```cpp
// 获取 ISO
CATFrmEditor* editor = GetEditor();
CATISO* _pISO = editor->GetISO();

// 添加临时对象
_pISO->AddElement(piTempPoint);
_pISO->AddElement(piTempLine);

// 更新临时对象（橡皮筋效果）
piTempPoint->SetCoord(x, y, z);
_pISO->UpdateElement(piTempPoint);    // 更新显示
piTempLine->SetEndPoint(newEndPoint);
_pISO->UpdateElement(piTempLine);

// Cancel 时清除
_pISO->RemoveElement(piTempPoint);
piTempPoint->Release();
```

**典型用法 — CreateCircle 橡皮筋**：
```cpp
// CreateCircleCenter：创建临时中心点 + 0 半径临时圆
_piTemporaryPoint = ...;
_pISO->AddElement(_piTemporaryPoint);
_piTemporaryCircle = ...;
_pISO->AddElement(_piTemporaryCircle);

// UpdateCircle：鼠标移动时更新临时圆的半径
_Radius = distance(mousePos, _CircleCenter);
_piTemporaryCircle->SetRadius(_Radius);
_pISO->UpdateElement(_piTemporaryCircle);

// NewCircle：清除临时对象，创建最终圆
_pISO->RemoveElement(_piTemporaryCircle);
_pISO->RemoveElement(_piTemporaryPoint);
// 创建最终圆...
```

**CATISO 关键方法**：
| 方法 | 说明 |
|------|------|
| `AddElement(obj)` | 添加临时对象（自动 AddRef） |
| `RemoveElement(obj)` | 移除临时对象 |
| `UpdateElement(obj)` | 更新临时对象显示 |

---

### 6. CATCSO — 当前选中对象集

CATCSO（Current Set of Objects）实现命令间的**链式调用**——上一个命令的结果自动成为下一个命令的输入：

```cpp
// 命令创建对象后，将对象放入 CSO（CreateBox 示例）
CATFrmEditor* pEditor = GetEditor();
CATCSO* pCso = pEditor->GetCSO();

CATPathElement RootPath = pEditor->GetUIActiveObject();
CATPathElement* pPathBox = new CATPathElement(RootPath);
pPathBox->AddChildElement(piSysBox);
pCso->AddElement(pPathBox);    // AddElement 内部 AddRef
pPathBox->Release();

// 下一个命令通过 AddCSOClient 订阅 CSO（CreateRectangle 示例）
// 在 BuildGraph 中：
stState->AddCSOClient();  // 命令启动时自动从 CSO 获取对象

// 如果命令不使用 CSO 作为输入，需要在 Activate 中清空 CSO
CATCSO* pCso = pEditor->GetCSO();
pCso->Empty();  // CreatePointCmd、CreateBoxCmd 使用此模式
```

**CSO 使用模式对比**：
| 模式 | 示例命令 | Activate 行为 |
|------|---------|--------------|
| 使用 CSO | CreateRectangleCmd, CreateCircleCmd | 不清空 CSO，通过 AddCSOClient 订阅 |
| 不使用 CSO | CreatePointCmd, CreateBoxCmd | `pCso->Empty()` 清空 CSO |

---

### 7. Palette / Check Header — 命令面板

CreateBoxCmd 演示了 Palette 系统的完整用法：

**7.1 实现 CATIAfrCmdPaletteOptions 接口**

```cpp
// 字典注册
// CAADegCreateBoxCmd  CATIAfrCmdPaletteOptions libCAADegGeoCommands

TIE_CATIAfrCmdPaletteOptions(CAADegCreateBoxCmd);

// 两个虚方法
virtual CATLISTP(CATCommandHeader) GetPaletteStateOptions();
virtual CATLISTP(CATCommandHeader) GetPaletteOptions();
```

**7.2 GetPaletteStateOptions — 按状态显示选项**

```cpp
CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteStateOptions() {
    CATLISTP(CATCommandHeader) PaletteStateOptions;
    CATDialogState* pCurrentState = GetCurrentState();
    CATString StateName = pCurrentState->GetResourceID();

    if (!strcmp("stWidthPointId", StateName)) {
        // Width 状态：显示 3 个选项
        AppendHeader(PaletteStateOptions, "CAADegTwoPointsBoxHdr");   // 立方体
        AppendHeader(PaletteStateOptions, "CAADegThreePointsBoxHdr"); // 等宽深
        AppendHeader(PaletteStateOptions, "CAADegFourPointsBoxHdr");  // 全自定义
    } else if (!strcmp("stDepthPointId", StateName)) {
        // Depth 状态：只显示 2 个选项
        AppendHeader(PaletteStateOptions, "CAADegThreePointsBoxHdr");
        AppendHeader(PaletteStateOptions, "CAADegFourPointsBoxHdr");
    }
    return PaletteStateOptions;
}
```

**7.3 GetPaletteOptions — 始终显示的选项**

```cpp
CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteOptions() {
    CATLISTP(CATCommandHeader) PaletteOptions;
    AppendHeader(PaletteOptions, "CAADegOriginBoxHdr");  // 始终显示
    return PaletteOptions;
}
```

**7.4 Check Header 的创建和配置**

```cpp
// 1. 声明命令头部类
MacDeclareHeader(CAADegCreateBoxPaletteHeader);

// 2. 创建 Check Header 访问器
CATAfrCheckHeaderAccessor* _pTwoPointsCmdHdr = new CATAfrCheckHeaderAccessor("CAADegTwoPointsBoxHdr");

// 3. 首次创建时配置
if (NULL == pCmd) {  // 头部尚未存在
    _pTwoPointsCmdHdr->SetCheck(TRUE, FALSE);  // 默认选中

    // 创建 Check 状态的命令头部
    new CAADegCreateBoxPaletteHeader(
        "CAADegTwoPointsBoxCheckHdr",     // 头部名称
        "CAADegGeoCommands",              // 模块名
        "CAADegBoxPaletteChoiceCmd",      // 启动的命令类
        (void*)1                          // 参数：1 = TwoPoints
    );

    // 创建 Uncheck 状态的命令头部
    new CAADegCreateBoxPaletteHeader(
        "CAADegTwoPointsBoxUncheckHdr",
        "CAADegGeoCommands",
        "CAADegBoxPaletteChoiceCmd",
        (void*)1
    );

    _pTwoPointsCmdHdr->SetCheckCommand("CAADegTwoPointsBoxCheckHdr");
    _pTwoPointsCmdHdr->SetUncheckCommand("CAADegTwoPointsBoxUncheckHdr");
    _pTwoPointsCmdHdr->SetResourceFile("CAADegCreateBoxPaletteHeader");
}
```

**7.5 通知机制 — Radio Button 效果**

```cpp
// BuildGraph 中订阅自定义通知
AddAnalyseNotificationCB(NULL, "CAADegBoxCreationChoiceNotification",
    (CATCommandMethod)&CAADegCreateBoxCmd::BoxCreationChoiceChange, NULL);

// 回调中实现 Radio Button
void BoxCreationChoiceChange(CATCommand*, CATNotification* iNotif, CATCommandClientData) {
    CAADegBoxCreationChoiceNotification* pNotif = (CAADegBoxCreationChoiceNotification*)iNotif;
    int value;
    pNotif->GetChoice(value);

    if (value == 1) {
        _pTwoPointsCmdHdr->SetCheck(TRUE, FALSE);
        _pThreePointsCmdHdr->SetCheck(FALSE, FALSE);
        _pFourPointsCmdHdr->SetCheck(FALSE, FALSE);
    } // ... value 2, 3 同理
    _CurrentBoxCreationTypeChoice = value;
}
```

---

### 8. 跨文档交互

CAADialogEngine 演示了两种跨文档选择模式：

**8.1 CATOtherDocumentAgent（CreateCylinder1Cmd）**

```cpp
// 在另一个文档中选择 Circle
CATOtherDocumentAgent* _daSelectionCircle = new CATOtherDocumentAgent("daCircleId");
_daSelectionCircle->AddElementType(IID_CAAISysCircle);

// 当前文档中选择 Line
CATPathElementAgent* _daSelectionLine = new CATPathElementAgent("daLineId");
_daSelectionLine->AddElementType(IID_CAAISysLine);

// 两者放在同一个 State 中
CATDialogState* stState = GetInitialState("stId");
stState->AddDialogAgent(_daSelectionLine);
stState->AddDialogAgent(_daSelectionCircle);
// 用户可以任意顺序选择两个 Agent 的值
```

**8.2 CATMultiDocumentCommand（CreateCylinder2Cmd）**

```cpp
// CAADegSampleMultiDocumentCommand 继承 CATMultiDocumentCommand
class CAADegSampleMultiDocumentCommand : public CATMultiDocumentCommand {
    CATPathElementAgent _AcquisitionAgent;  // 作为成员变量

    CATBoolean SelectionDone(void*);  // 选择完成回调
};

// SelectionDone 中，将选中值传递给 CATOtherDocumentAgent
CATBoolean SelectionDone(void*) {
    CATPathElement* path = _AcquisitionAgent.GetValue();
    CATOtherDocumentAgent* pAgent = GetOtherDocumentAgent();
    pAgent->SetValue(path);  // 跨文档传递值
    return TRUE;
}
```

---

### 9. 摄像机管理

CreateBoxCmd 和 CreateCircleCmd 演示了视角操控：

```cpp
// 保存当前视角
CATFrmLayout* pLayout = CATFrmLayout::GetCurrentLayout();
CATFrmWindow* pWindow = pLayout->GetCurrentWindow();
_piCamera = pWindow->GetCurrentCamera();  // 保存

// 创建新视角
CATI3DCamera* pi3DCamera = ...;
pi3DCamera->SetOrigin(OriginPoint);        // 设置原点
pi3DCamera->SetZenith(DirectionUp);        // 设置上方向
pi3DCamera->SetDirection(DirectionSight);  // 设置视线方向
pWindow->SetCurrentCamera(pi3DCamera);     // 应用新视角

// Cancel 时恢复原始视角
pWindow->SetCurrentCamera(_piCamera);
_piCamera->Release();
```

---

### 10. 自定义通知 — 命令间通信

```cpp
// 1. 定义通知类（继承 CATNotification）
class CAADegBoxCreationChoiceNotification : public CATNotification {
    CATDeclareClass;
public:
    HRESULT GetChoice(int& oChoiceValue);
    HRESULT SetChoice(int iChoiceValue);
private:
    int _ChoiceValue;
};

// 2. 发送方：Palette 按钮命令
CAADegBoxPaletteChoiceCmd::CAADegBoxPaletteChoiceCmd(void* iArg) {
    int choice = CATPtrToINT32(iArg);
    CAADegBoxCreationChoiceNotification* pNotif = new CAADegBoxCreationChoiceNotification();
    pNotif->SetChoice(choice);
    SendNotification(GetFather(), pNotif);  // 向上发送通知
    pNotif->Release();
    RequestDelayedDestruction();  // 通知发送后命令自动销毁
}

// 3. 接收方：CreateBoxCmd 在 BuildGraph 中订阅
AddAnalyseNotificationCB(NULL, "CAADegBoxCreationChoiceNotification",
    (CATCommandMethod)&CAADegCreateBoxCmd::BoxCreationChoiceChange, NULL);
```

---

## 关键接口/类速查

| 类/接口 | 关键方法 | 用途 |
|---------|---------|------|
| **CATStateCommand** | `BuildGraph`, `Activate`, `Desactivate`, `Cancel`, `GetEditor`, `GetCurrentState` | 状态命令基类 |
| **CATIndicationAgent** | `GetValue`, `SetMathPlane`, `GetMathPlane`, `SetBehavior`, `InitializeAcquisition` | 屏幕位置代理 |
| **CATPathElementAgent** | `GetValue`, `AddElementType`, `SetBehavior` | 模型元素选择代理 |
| **CATDialogAgent** | 关联对话框事件 | 对话框事件代理 |
| **CATOtherDocumentAgent** | `AddElementType`, `SetValue` | 跨文档选择代理 |
| **CATDialogState** | `AddDialogAgent`, `AddCSOClient` | 状态节点 |
| **CATPanelState** | 构造(Cmd, Id, Dialog*), `AddDialogAgent` | 带对话框的状态 |
| **AddTransition** | (from, to, condition, action) | 添加状态转换 |
| **CATISO** | `AddElement`, `RemoveElement`, `UpdateElement` | 临时交互对象 |
| **CATCSO** | `AddElement`, `Empty` | 当前选中对象集 |
| **CATAfrCheckHeaderAccessor** | `SetCheck`, `IsChecked`, `SetCheckCommand`, `SetUncheckCommand`, `SetResourceFile` | Check Header 访问器 |
| **CATIAfrCmdPaletteOptions** | `GetPaletteStateOptions`, `GetPaletteOptions` | Palette 选项接口 |
| **CATMultiDocumentCommand** | `GetOtherDocumentAgent`, `SelectionDone` | 跨文档命令基类 |
| **CATICamera / CATI3DCamera** | `SetOrigin`, `SetZenith`, `SetDirection` | 摄像机操作 |
| **CATCreateClass** | (ClassName) | 注册命令可通过类名实例化 |
| **MacDeclareHeader** | (HeaderName) | 声明命令头部类 |

---

## 命令图谱（29 个命令分类）

### 基础创建命令（State Machine 入门）

| 命令 | Agent 类型 | 状态数 | 关键技术 |
|------|-----------|--------|---------|
| **CreatePointCmd** | IndicationAgent + CATPanelState | 1 | 最简单的状态命令 + 对话框 |
| **CreateLineCmd** | IndicationAgent（共用） | 2 | 多状态 + CATISO 临时点 + 同一 Agent 跨状态复用 |
| **CreateCircleCmd** | PathElementAgent + IndicationAgent×2 | 3 | CSO + ISO 橡皮筋 + 摄像机 |

### 高级创建命令（Palette + 多 Agent）

| 命令 | Agent 类型 | 状态数 | 关键技术 |
|------|-----------|--------|---------|
| **CreateBoxCmd** | PathElementAgent×2 + IndicationAgent×2 | 4 | Palette + CheckHeader + Camera + 分支转换 |
| **CreatePlaneCmd** | PathElementAgent + IndicationAgent | 2 | Agent 过滤 `AddElementType` |
| **CreateRectangleCmd** | PathElementAgent + IndicationAgent | 2 | CSO 链式调用 |
| **CreateTriangleCmd** | PathElementAgent + IndicationAgent×2 | 2 | 多 Agent 协同 |
| **CreatePolylineCmd** | IndicationAgent | 1 | 循环创建 + Agent 回收 |
| **CreateEllipseCmd** | PathElementAgent + 对话框 | 1 | RadiusEllipseEditor 专用对话框 |

### 跨文档命令

| 命令 | Agent 类型 | 关键技术 |
|------|-----------|---------|
| **CreateCylinder1Cmd** | PathElementAgent + OtherDocumentAgent | 跨文档选择 Circle |
| **CreateCylinder2Cmd** | PathElementAgent + OtherDocumentAgent | CATMultiDocumentCommand 子命令 |

### 分析命令（多选行为）

| 命令 | 关键技术 |
|------|---------|
| **AnalysisNumericCmd** | 3 种多选模式（SelModes/Ctrl/UserCtrl）+ 5 状态 + ChoiceBehaviorDlg |
| **AnalysisEltTypeCmd** | PathElementAgent 类型过滤 |
| **AnalysisLogCmd** | 分析结果显示 |

### 裁剪命令

| 命令 | 关键技术 |
|------|---------|
| **ClippingByBoxCmd** | 可视化裁剪 |
| **ClippingBySphereCmd** | 可视化裁剪 |

### Palette 辅助

| 命令 | 角色 |
|------|------|
| **BoxPaletteChoiceCmd** | Palette 按钮命令，发送 CAADegBoxCreationChoiceNotification |
| **BoxCreationChoiceNotification** | 自定义通知，携带 choice 值 |

### 辅助类

| 类 | 角色 |
|------|------|
| **PointEditor** | CATDlgDialog，X/Y/Z Spinner，配合 CATPanelState |
| **PointErrorBox** | CATDlgDialog，错误提示 |
| **RadiusEllipseEditor** | CATDlgDialog，U/V Spinner |
| **HstChartWndDlg** | CATDlgDialog，直方图窗口 |
| **ChoiceBehaviorDlg** | CATDlgDialog，多选行为选择 |
| **AnalysisNumericDlg** | CATDlgDialog，显示选中元素计数 |

---

## 设计模式总结

1. **状态图模式**：`BuildGraph()` 构建有向图，Agent=输入，Transition=条件+动作，NULL=终点

2. **Agent 复用模式**：同一个 Agent 可以添加到多个 State（CreateLineCmd），通过 `InitializeAcquisition()` 重置

3. **ISO 橡皮筋模式**：AddElement → 循环 UpdateElement → RemoveElement → 创建最终对象

4. **CSO 链式模式**：命令 A 创建对象 → 放入 CSO → 命令 B 通过 `AddCSOClient` 自动获取

5. **Palette 动态选项模式**：`GetPaletteStateOptions` 根据当前状态返回不同的 Check Header 列表

6. **Check Header Radio 模式**：多个 Check Header + 自定义通知 + BoxCreationChoiceChange 回调实现互斥选择

7. **跨文档 Agent 模式**：CATOtherDocumentAgent 允许用户在另一个文档中选择元素，无需切换命令

8. **Panel State 模式**：CATPanelState = State + DialogBox，用户可以通过对话框或屏幕交互

---

## AI Agent 学习要点

1. **所有 CATIA 交互式命令都是 CATStateCommand 的子类**。BuildGraph 定义状态图，Activate/Desactivate/Cancel 管理焦点。

2. **Agent 是用户输入的唯一入口**。4 种 Agent 覆盖所有交互场景：屏幕点击（Indication）、模型选择（PathElement）、对话框事件（DialogAgent）、跨文档选择（OtherDocument）。

3. **CATISO 用于临时视觉反馈**，命令结束时必须清理。UpdateElement 配合自循环 Transition 实现橡皮筋效果。

4. **CATCSO 实现命令链**：`AddCSOClient` 让命令自动获取上一个命令的结果。不使用的命令需要在 Activate 中 `Empty()`。

5. **Agent 必须调用 `InitializeAcquisition()` 才能在同一状态中重复使用**（CreatePointCmd 的 Apply 循环）。

6. **CATCreateClass 注册**是命令头部的必要条件，使命令可以通过字符串类名实例化。

7. **Check Header 需要在构造函数中通过 CATAfrCheckHeaderAccessor 配置**，包括 Check/Uncheck 命令和资源文件。

8. **跨文档 Agent 和本 Agent 可以放在同一个 State 中**，用户可任意顺序操作。

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATStateCommand.htm](../api-reference/interfaces/CATStateCommand.htm)
- 完整方法签名: [api-reference/interfaces/CATDialogAgent.htm](../api-reference/interfaces/CATDialogAgent.htm)
- 完整方法签名: [api-reference/interfaces/CATISO.htm](../api-reference/interfaces/CATISO.htm)
- 完整方法签名: [api-reference/interfaces/CATCSO.htm](../api-reference/interfaces/CATCSO.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/caadegusecases/](../use-cases/caadegusecases/)