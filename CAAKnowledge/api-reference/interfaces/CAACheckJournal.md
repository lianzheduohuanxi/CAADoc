---
title: "CAACheckJournal"
type: "PublicInterface"
module: "CAATopologicalOperators"
base: ""
method_count: 2
source_file: "CAATopologicalOperators.edu/PublicInterfaces/CAACheckJournal.h"
---

# CAACheckJournal

**基类**: 无 | **模块**: CAATopologicalOperators | **方法数**: 2

## 依赖

- `CAATopCheckJournal.h`
- `CATTopOperator.h`

## 公共方法

### CAAAddInputBody

```cpp
int CAAAddInputBody(CATBody * iInputBody, CAATopCheckJournalType copyNoCopy) ;
```

| 参数 | 类型 |
|------|------|
| iInputBody | `CATBody *` |
| copyNoCopy | `CAATopCheckJournalType` |


### CAACheck

```cpp
int CAACheck() ;
```

Destructor


---

**源文件**: `CAATopologicalOperators.edu/PublicInterfaces/CAACheckJournal.h`
