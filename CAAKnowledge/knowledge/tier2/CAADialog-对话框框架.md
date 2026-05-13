---
module: "CAADialog.edu"
category: "CAA 对话框框架 — 窗口/控件/状态命令/MVC/Observer/进程间通信"
tier: "2"
status: "已完成"
---

# CAADialog.edu — 对话框框架

## 模块定位

CAADialog 是 CAA 最丰富的交互式应用教程框架，包含 11 个 .m 模块。它系统性地覆盖了 CATIA 对话框开发的全栈技能：

- **窗口体系**：CATDlgDocument → CATDlgDialog 的继承和使用
- **控件体系**：Label, PushButton, Combo, Spinner, Editor, SelectorList, RadioButton 等
- **布局系统**：CATDlgGridLayout（表格布局）和 Attachment（吸附布局）
- **回调机制**：AddAnalyseNotificationCB 的事件-回调绑定
- **MVC 模式**：Model → Controller → View 的完整实现
- **Observer 模式**：CATCallbackManager 事件发布-订阅
- **状态命令**：CATCommand 的生命周期（Activate/Desactivate/Cancel）
- **进程间通信**：Bulletin Board Message（BB Message）系统
- **设置持久化**：CATSettingRepository 的读写

这个模块是开发 CATIA 交互式功能的必修课。

---

## 架构总览

```
┌──────────────────────────────────────────────────────────────────────┐
│                     CATInteractiveApplication                         │
│                              │                                        │
│                  ┌───────────┼───────────┐                            │
│                  │           │           │                            │
│          HelloApplication  Burger      Demo                           │
│              │              │           │                              │
│         ┌────┴────┐    ┌───┴───┐   ┌───┴────┐                        │
│      Window    Command  Model  View  Window  Dialogs                  │
│     (Document)         (Data) (UI)          (More/Frame/Radio)        │
│                                                                        │
│  ┌─────────────────────────────────────────────────────┐              │
│  │               SendReceive (MVC+Observer)              │              │
│  │  Model ──notify──> Container ──notify──> ViewScreen  │              │
│  │  (data)           (观察者)            (状态命令)      │              │
│  └─────────────────────────────────────────────────────┘              │
│                                                                        │
│  ┌─────────────────────────────────────────────────────┐              │
│  │             BB Message (进程间通信)                   │              │
│  │  BBSender ──CATICommMsg──> BBReceiver               │              │
│  │  (发送端)                   (接收端)                  │              │
│  │  CATIMessageReceiver ← TIE ← CAADlgBBEditorMessageHandler          │
│  └─────────────────────────────────────────────────────┘              │
│                                                                        │
│  ┌─────────────────────────────────────────────────────┐              │
│  │          OnIdle (空闲时间处理)                        │              │
│  │  CAADlgObject ──Modification()──> CATCallbackManager │              │
│  │                                ──DispatchCallbacks──>│              │
│  └─────────────────────────────────────────────────────┘              │
└──────────────────────────────────────────────────────────────────────┘
```

---

## 核心知识

### 1. 窗口的继承体系

CATIA 对话框有两类窗口基类：

| 基类 | 用途 | 创建方式 |
|------|------|---------|
| **CATDlgDocument** | 主应用程序窗口（文档级） | 构造时传入 `CATInteractiveApplication*` |
| **CATDlgDialog** | 子对话框（模态/非模态） | 构造时传入父 `CATDialog*` |

**继承关系**：
```
CATDlgDialog → CATDialog → CATDlgContainer → CATCommand
CATDlgDocument → CATDialog → CATDlgContainer → CATCommand
```

**CATDlgDocument（主窗口）**：
```cpp
// CAADlgHelloWindow.h
class CAADlgHelloWindow : public CATDlgDocument {
    DeclareResource(CAADlgHelloWindow, CATDlgDocument)  // NLS 资源声明
public:
    CAADlgHelloWindow(CATInteractiveApplication * iParentCommand);
    void Build();  // 控件构造在此方法中进行
};
```

**CATDlgDialog（子对话框）**：
```cpp
// CAADlgMoreButtonDlg.h
class CAADlgMoreButtonDlg : public CATDlgDialog {
public:
    CAADlgMoreButtonDlg(CATDialog * pParentDlg);
    void Build();
};
```

**关键约定**：
- 构造函数中不做 UI 构建，只做成员变量初始化
- 所有控件创建和布局在 `Build()` 方法中完成
- `Build()` 由调用者在构造后显式调用

---

### 2. 控件体系

CAADialog 演示了以下控件类型：

| 控件类 | 功能 | 关键方法/属性 |
|--------|------|-------------|
| `CATDlgLabel` | 文本标签 | `SetIconName()` 设置背景图标 |
| `CATDlgPushButton` | 按钮 | `GetPushBActivateNotification()` 获取点击通知 |
| `CATDlgPushItem` | 菜单项 | `GetMenuIActivateNotification()` |
| `CATDlgCombo` | 下拉框 | `SetLine()`, `GetSelect()`, `GetComboSelectNotification()` |
| `CATDlgSpinner` | 数值微调器 | `SetMinMaxStep()`, `SetValue()`, `GetValue()` |
| `CATDlgEditor` | 文本编辑器 | `SetGridConstraints()` 布局 |
| `CATDlgSelectorList` | 选择列表 | `SetVisibleTextHeight()` |
| `CATDlgRadioButton` | 单选按钮 | 组内互斥 |
| `CATDlgFrame` | 容器框架 | `SetVisibility(CATDlgHide/CATDlgShow)` |
| `CATDlgBarMenu` / `CATDlgSubMenu` | 菜单栏/子菜单 | 层次嵌套 |

---

### 3. 布局系统

CATIA 对话框使用**两套布局机制**：

**3.1 Grid Layout（表格布局）**

```cpp
// Frame 指定为 GridLayout
CATDlgFrame * pFrame = new CATDlgFrame(parent, "FrameName", CATDlgGridLayout);

// 子控件设置网格约束
pLabel->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
// 参数：行、列、行跨度、列跨度、吸附方式
```

**3.2 Attachment Layout（吸附布局）**

```cpp
// 将控件吸附到父窗口的边
SetHorizontalAttachment(0, CATDlgTopOrLeft, pFrameCombo, NULL);
// 参数：偏移像素、吸附方向、控件、参考控件(NULL=父窗口)

// 动态替换吸附的控件
ResetAttachment(pOldFrame);
SetHorizontalAttachment(5, CATDlgTopOrLeft, pNewFrame, NULL);
```

**3.3 Attach4Sides（四边吸附）**

```cpp
Attach4Sides(pLabelBackground);  // 控件四边全部吸附到父窗口
```

---

### 4. 回调机制 — AddAnalyseNotificationCB

这是 CATIA 对话框的**核心事件绑定方法**：

```cpp
// 模板签名
AddAnalyseNotificationCB(
    CATCommand*   pObject,          // 被观察的对象（控件）
    CATNotification* pNotification, // 监听的通知类型
    CATCommandMethod pMethod,       // 回调成员函数指针
    CATCommandClientData pData      // 用户数据（通常 NULL）
);

// 实际使用示例
AddAnalyseNotificationCB(
    this,                                     // 监听自身
    GetWindCloseNotification(),               // 窗口关闭通知
    (CATCommandMethod)&CAADlgHelloWindow::Exit,  // 回调方法
    NULL);

AddAnalyseNotificationCB(
    pPushButton,
    pPushButton->GetPushBActivateNotification(),  // 按钮点击通知
    (CATCommandMethod)&CAADlgHelloWindow::OnButtonClick,
    NULL);
```

**常用通知类型**：

| 通知获取方法 | 触发时机 |
|-------------|---------|
| `GetWindCloseNotification()` | 窗口关闭 |
| `GetDiaOKNotification()` | 点击 OK 按钮 |
| `GetDiaCANCELNotification()` | 点击 Cancel 按钮 |
| `GetPushBActivateNotification()` | 按钮点击 |
| `GetMenuIActivateNotification()` | 菜单项激活 |
| `GetComboSelectNotification()` | Combo 选择变化 |

**回调方法签名**：
```cpp
void CallbackMethod(CATCommand* cmd, CATNotification* evt, CATCommandClientData data);
```

---

### 5. 状态命令 — CATCommand 生命周期

对话框窗口继承了 CATCommand，因此拥有命令状态机：

```
                RequestStatusChange(CATCommandMsgRequestExclusiveMode)
                ──────────────────────────────────────────────────────
                                    │
                                    ▼
     ┌──────────────────────────────────────────────────────────┐
     │                    CATCommand 状态机                      │
     │                                                          │
     │  ┌─────────┐    Activate()    ┌─────────┐                │
     │  │  Idle   │ ───────────────> │  Active │                │
     │  │         │ <─────────────── │         │                │
     │  └─────────┘   Desactivate()  └─────────┘                │
     │       │                              │                    │
     │       └──────── Cancel() ────────────┘                    │
     │                                                          │
     │  AnalyseNotification() — 在 Active 状态拦截通知           │
     │  WantedFocus() — 请求获取焦点                            │
     └──────────────────────────────────────────────────────────┘
```

**CAADlgViewScreen 状态命令实现**：
```cpp
// Activate: 获取焦点时调用
CATStatusChangeRC CAADlgViewScreen::Activate(CATCommand*, CATNotification*) {
    // 开始交互操作（如等待用户选择）
    return CATStatusChangeRCCompleted;
}

// Desactivate: 失去焦点时调用
CATStatusChangeRC CAADlgViewScreen::Desactivate(CATCommand*, CATNotification*) {
    // 结束交互操作
    return CATStatusChangeRCCompleted;
}

// AnalyseNotification: 在 Active 状态下拦截通知
CATNotifPropagationMode CAADlgViewScreen::AnalyseNotification(
    CATCommand* iSending, CATNotification* iReceive) {
    // 根据通知类型决定是处理还是传播
    // CATNotifPropagationMode = 处理 | 传播 | 销毁
}

// WantedFocus: 请求获取焦点
void CAADlgViewScreen::WantedFocus() {
    // 例如：用户点击了某个区域，ViewScreen 想要获取焦点
}
```

**对话框也支持状态命令接口**：
```cpp
// CAADlgFrameReplaceDlg 实现了 Activate/Desactivate/Cancel
CATStatusChangeRC CAADlgFrameReplaceDlg::Activate(CATCommand*, CATNotification*) {
    SetVisibility(CATDlgShow);
    return CATStatusChangeRCCompleted;
}

CATStatusChangeRC CAADlgFrameReplaceDlg::Desactivate(CATCommand*, CATNotification*) {
    SetVisibility(CATDlgHide);
    return CATStatusChangeRCCompleted;
}

CATStatusChangeRC CAADlgFrameReplaceDlg::Cancel(CATCommand*, CATNotification*) {
    SetVisibility(CATDlgHide);
    RequestDelayedDestruction();  // 延迟销毁自身
    return CATStatusChangeRCCompleted;
}
```

---

### 6. MVC 模式 — Burger 示例

CAADlgBurger 展示了经典的 MVC 模式：

```
     ┌──────────────┐
     │   Model      │  ← 数据层：持有业务数据（面包、肉、酱料等）
     │ (CAADlgBurger)│
     └──────┬───────┘
            │ 读取/修改
     ┌──────▼───────┐
     │  Controller  │  ← 控制层：CAADlgBurgerApplication
     │  (Application)│     创建 Model 和 Window
     └──────┬───────┘
            │ 创建
     ┌──────▼───────┐
     │    View      │  ← 视图层：CAADlgBurgerWindow
     │  (Window)    │     显示数据，响应用户操作
     └──────────────┘
```

```cpp
// Controller 创建 Model 和 View
void CAADlgBurgerApplication::BeginApplication() {
    // 1. 创建数据模型
    _pModel = new CAADlgBurger();
    
    // 2. 创建视图窗口（传入 Model 和 Controller）
    _pWindow = new CAADlgBurgerWindow(this, _pModel);
    _pWindow->Build();
    _pWindow->SetVisibility(CATDlgShow);
}

// View 从 Model 读取数据并展示
void CAADlgBurgerWindow::Build() {
    // 读取 Model 数据
    int nbBread = _pModel->GetBreadNumber();
    // 根据数据创建控件...
}
```

---

### 7. Observer 模式 — CATCallbackManager

CAADialog 展示了两种通知/观察者机制：

**7.1 CAADlgObject → CATCallbackManager（OnIdle 模块）**

```cpp
// 发布者：CAADlgObject
class CAADlgObject : public CATBaseUnknown {
public:
    void Modification() {
        // 获取回调管理器
        CATCallbackManager* pCBManager = ::GetDefaultCallbackManager(this);
        if (pCBManager) {
            // 创建通知对象
            CAADlgModifNotification* pNotification = new CAADlgModifNotification();
            // 分发通知给所有订阅者
            pCBManager->DispatchCallbacks(pNotification, this);
            pNotification->Release();
        }
    }
};

// 通知类：继承自 CATNotification
class CAADlgModifNotification : public CATNotification {
    CATDeclareClass;
    // 可以携带额外数据
};
```

**7.2 Model → Container → ViewScreen（SendReceive 模块）**

```
CAADlgModel ──AddNotification──> CAADlgContainer ──AddNotification──> CAADlgViewScreen
  (数据源)                          (观察者/转发器)                    (最终消费者)
```

```cpp
// 订阅链
CAADlgModel* pModel = new CAADlgModel();
CAADlgContainer* pContainer = new CAADlgContainer();

// Container 订阅 Model
pModel->AddNotification(pContainer);

// ViewScreen 订阅 Container
pContainer->AddNotification(pViewScreen);

// Model 发生变化时：
pModel->ModifyElement(elementIndex, newValue);
// → 通知 Container → 通知 ViewScreen → ViewScreen 更新显示
```

**通知接口**：
```cpp
class CAADlgAddNotification {
public:
    virtual void AddNotification(CATBaseUnknown* iObject) = 0;
    virtual void RemoveNotification(CATBaseUnknown* iObject) = 0;
};
```

---

### 8. 进程间通信 — Bulletin Board Message

BB Message 系统实现了**跨应用程序/跨窗口的消息传递**：

**8.1 消息定义（CAADlgBBEditorMessage）**

```cpp
// PrivateInterfaces/CAADlgBBMessageInt.h — 消息内容接口
class CAAIDlgDataRequest : public CATBaseUnknown {
    CATDeclareInterface;
public:
    virtual HRESULT GetData(char** opData) = 0;
    virtual HRESULT SetData(char* ipData) = 0;
};

// CAADlgBBEditorMessage — 消息组件
// 实现 CATICommMsg（系统消息接口）和 CAAIDlgDataRequest（自定义数据接口）
class CAADlgBBEditorMessage : public CATBaseUnknown {
    CATDeclareClass;
public:
    // CATICommMsg 相关方法
    HRESULT GetMessageClass(char** opClass);
    HRESULT GetMessageType(char** opType);
    // CAAIDlgDataRequest 方法
    HRESULT GetData(char** opData);
    HRESULT SetData(char* ipData);
};
```

**8.2 消息创建工厂**

```cpp
// CAAEDlgCreateInstanceForEditorMessage
// 工厂类负责创建 BB Message 实例
CATImplementClass(CAAEDlgCreateInstanceForEditorMessage, Implementation, CATBaseUnknown, CATNull);
TIE_CATICreateInstance(CAAEDlgCreateInstanceForEditorMessage);

HRESULT CAAEDlgCreateInstanceForEditorMessage::CreateInstance(void** opInstance) {
    CAADlgBBEditorMessage* pMessage = new CAADlgBBEditorMessage();
    *opInstance = (void*)pMessage;
    return S_OK;
}
```

**8.3 消息接收端（BBReceiver）**

```cpp
// CAADlgBBEditorMessageHandler — 实现 CATIMessageReceiver
TIE_CATIMessageReceiver(CAADlgBBEditorMessageHandler);
CATImplementClass(CAADlgBBEditorMessageHandler, Implementation, CATBaseUnknown, CATNull);

void CAADlgBBEditorMessageHandler::HandleMessage(CATICommMsg* iMessage) {
    // 1. 从消息中提取数据
    CAAIDlgDataRequest* pIRequest = NULL;
    iMessage->QueryInterface(IID_CAAIDlgDataRequest, (void**)&pIRequest);
    
    char* Text = NULL;
    pIRequest->GetData(&Text);
    pIRequest->Release();
    
    // 2. 通过 CATCallbackManager 二次分发
    CATCallbackManager* pCBManager = ::GetDefaultCallbackManager(this);
    CAADlgBBMessageNotification* pNotification = new CAADlgBBMessageNotification(Text);
    pCBManager->DispatchCallbacks(pNotification, this);
    pNotification->Release();
    
    delete[] Text;
}
```

**消息字典注册**：
```
# CAADialog.edu.dico
CAADlgBBEditorMessage  CATICommMsg  libCAADlgBBMessage
CAADlgBBEditorMessageHandler  CATIMessageReceiver  libCAADlgBBReceiver
```

**通信流程**：
```
Sender 应用                          Receiver 应用
    │                                     │
    │ 创建 CAADlgBBEditorMessage          │
    │ 设置消息数据                         │
    │                                     │
    │ ──── CATICommMsg ───────────────>   │
    │                                     │
    │                              HandleMessage()
    │                              提取数据
    │                              二次分发 (CATCallbackManager)
    │                                     │
    │                              UI 更新 / 响应
```

---

### 9. 设置持久化 — CATSettingRepository

用于在会话之间保存/恢复对话框状态：

```cpp
// 获取设置仓库
_pSettingFrameReplace = CATSettingRepository::GetRepository("CAADlgFrameReplaceDlg");

// 读取保存的值
double X = 0.0f;
_pSettingFrameReplace->ReadSetting("XCoord", &X);

// 写入新值
double XVal = _pSpinnerX->GetValue();
_pSettingFrameReplace->WriteSetting("XCoord", &XVal);

// 持久化到磁盘
_pSettingFrameReplace->SaveRepository();
```

---

### 10. 对话框高级模式

**10.1 更多/更少按钮（MoreButton）**

通过 `SetVerticalAttachment` 动态显示/隐藏按钮组：
```cpp
// 初始状态：隐藏额外按钮
SetVerticalAttachment(0, CATDlgTopOrLeft, _pButton3, NULL);
_pButton3->SetVisibility(CATDlgHide);

// 点击 More 按钮：显示额外按钮
ResetAttachment(_pButton3);
SetVerticalAttachment(0, CATDlgBottomOrRight, _pButton3, NULL);
_pButton3->SetVisibility(CATDlgShow);
```

**10.2 框架替换（FrameReplace）**

通过 Combo 选择切换可见的 Frame：
```cpp
void CAADlgFrameReplaceDlg::OnComboSelectNotification(CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    int NewSelection = _pComboPointType->GetSelect();
    
    // 隐藏旧 Frame
    ResetAttachment(_pListFrame[_CurrentSelection]);
    _pListFrame[_CurrentSelection]->SetVisibility(CATDlgHide);
    
    // 显示新 Frame
    SetHorizontalAttachment(5, CATDlgTopOrLeft, _pListFrame[NewSelection], NULL);
    _pListFrame[NewSelection]->SetVisibility(CATDlgShow);
    
    _CurrentSelection = NewSelection;
}
```

---

## 关键接口速查

| 接口/类 | 关键方法 | 用途 |
|---------|---------|------|
| **CATDlgDocument** | 构造(Application*), Build() | 主窗口基类 |
| **CATDlgDialog** | 构造(CATDialog*), Build(), `RequestDelayedDestruction()` | 子对话框基类 |
| **CATCommand** | `Activate`, `Desactivate`, `Cancel`, `AnalyseNotification`, `WantedFocus`, `RequestStatusChange` | 状态命令 |
| **CATCallbackManager** | `DispatchCallbacks` | 回调分发 |
| **CATNotification** | (基类，可继承扩展) | 通知基类 |
| **CATSettingRepository** | `GetRepository`, `ReadSetting`, `WriteSetting`, `SaveRepository` | 设置持久化 |
| **CATICommMsg** | `GetMessageClass`, `GetMessageType` | 进程间消息接口 |
| **CATIMessageReceiver** | `HandleMessage` | 消息接收回调 |
| **CATICreateInstance** | `CreateInstance` | 消息工厂接口 |
| **CATInteractiveApplication** | `BeginApplication`, `Destroy` | 交互式应用基类 |

---

## 11 个 Use Case 模块对照

| 模块 (.m) | 核心教学内容 | 关键技术点 |
|-----------|------------|----------|
| **CAADlgHelloApplication** | 最简单的对话框 | Document + PushButton + NLS + AddAnalyseNotificationCB |
| **CAADlgBurger** | MVC 模式 | Model-Controller-View 分离、数据驱动 UI |
| **CAADlgDialogDemonstrator** | 各种对话框类型 | RadioButton/MoreButton/FrameReplace、Combo 驱动 Frame 切换、Setting 持久化 |
| **CAADlgSendReceive** | MVC + Observer | Model→Container→ViewScreen 通知链、AddNotification 接口、状态命令生命周期 |
| **CAADlgOnIdle** | 空闲时间处理 | CATCallbackManager 发布-订阅、CAADlgModifNotification 自定义通知 |
| **CAADlgBBMessage** | BB 消息定义 | CATICommMsg 实现、CAAIDlgDataRequest 数据接口、CATICreateInstance 工厂 |
| **CAADlgBBMessageInt** | 消息接口定义 | CAAIDlgDataRequest 接口声明、IID 定义 |
| **CAADlgBBSender** | BB 消息发送 | 创建消息、设置数据、发送 |
| **CAADlgBBReceiver** | BB 消息接收 | CATIMessageReceiver 实现、HandleMessage、二次分发 |
| **CAADlgInteractiveApp** | 交互式应用 | CATInteractiveApplication 的完整生命周期 |
| **CAABasicAuthenticationPanel** | 认证面板 | 登录对话框示例 |

---

## 设计模式总结

1. **Build 模式**：构造函数不做 UI 构建，`Build()` 集中创建所有控件——这是 CATIA 对话框开发的铁律

2. **NLS 资源模式**：`DeclareResource(ClassName, BaseClass)` 声明 NLS 目录，所有可见文本通过 `CATMsgCatalog::BuildMessage` 获取，实现国际化

3. **MVC 分离**：Model（数据）、Controller（Application/Command）、View（Window）三层解耦，通过回调通信

4. **通知回调模式**：`AddAnalyseNotificationCB(pObject, pNotification, pMethod, pData)` — 事件驱动的 UI 交互

5. **Observer 通知链**：`Model → Container → ViewScreen` 的多级观察者，AddNotification/RemoveNotification 管理订阅

6. **CATCallbackManager 分发**：`DispatchCallbacks(pNotification, pSender)` — 中心化的回调管理，支持多个订阅者

7. **FrameReplace 模式**：通过 Combo 选择 + `ResetAttachment`/`SetVisibility` 实现对话框布局的动态切换

8. **BB Message 工厂**：`CATICreateInstance` 工厂 + `.dico` 字典注册 — 通过类型名称动态创建消息实例

---

## AI Agent 学习要点

1. **所有对话框的创建流程**：`new Widget(parent, "id")` → `Build()` → `SetVisibility(CATDlgShow)`。构造时不创建子控件。

2. **布局只有两种方式**：`CATDlgGridLayout`（表格，用 `SetGridConstraints`）和 Attachment（吸附，用 `SetHorizontalAttachment`/`SetVerticalAttachment`）。

3. **事件绑定使用 `AddAnalyseNotificationCB`**，回调签名为 `void(CATCommand*, CATNotification*, CATCommandClientData)`。

4. **窗口销毁使用 `RequestDelayedDestruction()`**，不要直接 `delete`——CATIA 内部管理对象生命周期。

5. **状态命令（CATCommand）有三个生命周期回调**：`Activate`（获取焦点）、`Desactivate`（失去焦点）、`Cancel`（取消）。

6. **进程间通信的核心链**：定义消息接口（如 `CAAIDlgDataRequest`）→ 实现消息组件 → 注册工厂（`CATICreateInstance`）→ 注册字典 → 接收端实现 `CATIMessageReceiver` → `HandleMessage` 处理。

7. **BB Message 接收端有两层分发**：`HandleMessage` 接收 CATICommMsg → 通过 CATCallbackManager 进行二次分发到本地订阅者。