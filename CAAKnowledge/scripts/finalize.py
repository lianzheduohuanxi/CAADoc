#!/usr/bin/env python3
"""P3: 创建统一入口 + 最终验证。"""

import os
import json
import re

KB_DIR = "/workspace/CAAKnowledge"


def create_knowledge_index():
    """Create the unified entry point for AI agent."""
    stats = {}

    # Count interface docs
    api_dir = os.path.join(KB_DIR, "api-reference", "interfaces")
    iface_count = len([f for f in os.listdir(api_dir) if f.endswith('.md')]) if os.path.exists(api_dir) else 0
    stats["interfaces"] = iface_count

    # Count use-case docs
    uc_count = 0
    uc_dir = os.path.join(KB_DIR, "use-cases")
    if os.path.exists(uc_dir):
        for root, dirs, files in os.walk(uc_dir):
            uc_count += len([f for f in files if f.endswith('.md')])
    stats["use_cases"] = uc_count

    # Count quick-refs
    qr_dir = os.path.join(KB_DIR, "quick-refs")
    qr_count = len([f for f in os.listdir(qr_dir) if f.endswith('.md')]) if os.path.exists(qr_dir) else 0
    stats["quick_refs"] = qr_count

    # Count troubleshooting
    ts_dir = os.path.join(KB_DIR, "troubleshooting")
    ts_count = len([f for f in os.listdir(ts_dir) if f.endswith('.md')]) if os.path.exists(ts_dir) else 0
    stats["troubleshooting"] = ts_count

    # Method stats from knowledge_base.json
    kb_file = os.path.join(KB_DIR, "data", "knowledge_base.json")
    if os.path.exists(kb_file):
        with open(kb_file) as f:
            kb = json.load(f)
        stats["interfaces_with_methods"] = sum(1 for v in kb.get('interfaces', {}).values() if v.get('method_count', 0) > 0)
        stats["total_methods"] = sum(v.get('method_count', 0) for v in kb.get('interfaces', {}).values())
        stats["method_index_entries"] = len(kb.get('method_index', {}))
    else:
        stats["interfaces_with_methods"] = 0
        stats["total_methods"] = 0
        stats["method_index_entries"] = 0

    # Cross-ref stats
    cr_file = os.path.join(KB_DIR, "data", "cross_references.json")
    if os.path.exists(cr_file):
        with open(cr_file) as f:
            cr = json.load(f)
        stats["cross_referenced_interfaces"] = len(cr.get('references', {}))
    else:
        stats["cross_referenced_interfaces"] = 0

    # Search index stats
    si_file = os.path.join(KB_DIR, "data", "search-index.json")
    if os.path.exists(si_file):
        with open(si_file) as f:
            si = json.load(f)
        stats["indexed_documents"] = si.get('total_docs', 0)
        stats["indexed_keywords"] = len(si.get('keyword_index', {}))
    else:
        stats["indexed_documents"] = 0
        stats["indexed_keywords"] = 0

    index = {
        "name": "CATIA CAA V5 Knowledge Base",
        "version": "2.0",
        "updated": "2026-05-13",
        "stats": stats,
        "query_guides": {
            "find_interface": {
                "description": "查询接口方法签名",
                "path": "api-reference/interfaces/{INTERFACE_NAME}.md",
                "example": "api-reference/interfaces/CAAISysAccess.md"
            },
            "find_method": {
                "description": "反向查找：哪些接口包含某个方法",
                "path": "data/knowledge_base.json → method_index",
                "example": "method_index['SetContainer'] → ['CAAISysAccess']"
            },
            "search_by_keyword": {
                "description": "按关键词搜索文档",
                "path": "data/search-index.json → keyword_index",
                "example": "keyword_index['workbench'] → [相关文档列表]"
            },
            "find_usecase": {
                "description": "查找使用案例文档",
                "path": "use-cases/{MODULE}/{DOC_NAME}.md",
                "example": "use-cases/caaafrcases/CAAAfrSampleWorkbench.md"
            },
            "cross_reference": {
                "description": "查找接口在哪些用例中被使用",
                "path": "data/cross_references.json",
                "example": "references['CAAISysAccess'] → [用例列表]"
            },
            "troubleshoot": {
                "description": "查找编译/运行时错误解决方案",
                "path": "troubleshooting/{TYPE}-errors.md",
                "example": "troubleshooting/compiler-errors.md"
            },
            "quick_patterns": {
                "description": "常见 CAA 编程模式",
                "path": "quick-refs/common-patterns.md"
            }
        }
    }

    index_path = os.path.join(KB_DIR, "knowledge-index.json")
    with open(index_path, 'w', encoding='utf-8') as f:
        json.dump(index, f, indent=2, ensure_ascii=False)

    print(f"Unified index: {index_path}")
    return stats


def run_validation():
    """Run final validation and produce availability report."""
    results = {
        "checks": [],
        "overall_score": 0
    }

    # Check 1: Interface doc method coverage
    kb_file = os.path.join(KB_DIR, "data", "knowledge_base.json")
    with open(kb_file) as f:
        kb = json.load(f)
    interfaces = kb.get('interfaces', {})
    total_ifaces = len(interfaces)
    with_methods = sum(1 for v in interfaces.values() if v.get('method_count', 0) > 0)
    score1 = min(100, with_methods / max(total_ifaces, 1) * 100)
    results["checks"].append({
        "name": "接口方法签名覆盖率",
        "value": f"{with_methods}/{total_ifaces} ({score1:.0f}%)",
        "score": score1,
        "pass": score1 >= 70
    })

    # Check 2: Frontmatter correctness
    uc_dir = os.path.join(KB_DIR, "use-cases")
    total_uc = 0
    bad_fm = 0
    if os.path.exists(uc_dir):
        for root, dirs, files in os.walk(uc_dir):
            for f in files:
                if f.endswith('.md'):
                    total_uc += 1
                    fpath = os.path.join(root, f)
                    with open(fpath, errors='ignore') as fh:
                        head = fh.read(50)
                    if head.startswith('---\n```vbscript'):
                        bad_fm += 1
    fm_ok = total_uc - bad_fm
    score2 = min(100, fm_ok / max(total_uc, 1) * 100)
    results["checks"].append({
        "name": "Use-Case frontmatter 正确率",
        "value": f"{fm_ok}/{total_uc} ({score2:.0f}%)",
        "score": score2,
        "pass": score2 >= 90
    })

    # Check 3: Search index coverage
    si_file = os.path.join(KB_DIR, "data", "search-index.json")
    if os.path.exists(si_file):
        with open(si_file) as f:
            si = json.load(f)
        # Check no report files in index
        report_files = sum(1 for d in si.get('documents', []) if any(
            rp in d.get('path', '') for rp in ['报告', '执行', '审查', '检查', '缺陷', '计划']
        ))
        score3 = 100 if report_files == 0 else max(0, 100 - report_files * 5)
        results["checks"].append({
            "name": "搜索索引纯度（无报告文件）",
            "value": f"{report_files} 个报告文件残留",
            "score": score3,
            "pass": score3 >= 80
        })

    # Check 4: Cross-reference coverage
    cr_file = os.path.join(KB_DIR, "data", "cross_references.json")
    if os.path.exists(cr_file):
        with open(cr_file) as f:
            cr = json.load(f)
        cr_count = len(cr.get('references', {}))
        score4 = min(100, cr_count / max(total_ifaces, 1) * 100)
        results["checks"].append({
            "name": "交叉引用覆盖率",
            "value": f"{cr_count}/{total_ifaces} 接口关联用例",
            "score": score4,
            "pass": score4 >= 60
        })

    # Check 5: Code fence balance
    unbalanced = 0
    if os.path.exists(uc_dir):
        for root, dirs, files in os.walk(uc_dir):
            for f in files:
                if f.endswith('.md'):
                    fpath = os.path.join(root, f)
                    with open(fpath, errors='ignore') as fh:
                        content = fh.read()
                    fences = [l.strip() for l in content.split('\n') if l.strip().startswith('```')]
                    if len(fences) % 2 != 0:
                        unbalanced += 1
    score5 = min(100, max(0, 100 - (unbalanced / max(total_uc, 1) * 100)))
    results["checks"].append({
        "name": "代码围栏配对",
        "value": f"{unbalanced}/{total_uc} 不平衡",
        "score": score5,
        "pass": score5 >= 95
    })

    scores = [c["score"] for c in results["checks"]]
    results["overall_score"] = sum(scores) / len(scores) if scores else 0

    validation_path = os.path.join(KB_DIR, "data", "validation_report.json")
    with open(validation_path, 'w', encoding='utf-8') as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    print(f"\n=== 验证报告 ===")
    for check in results["checks"]:
        status = "PASS" if check["pass"] else "FAIL"
        print(f"  [{status}] {check['name']}: {check['value']}")
    print(f"\n综合可用性评分: {results['overall_score']:.0f}/100")
    print(f"报告: {validation_path}")

    return results


def main():
    stats = create_knowledge_index()
    print(f"\n知识库统计:")
    for k, v in stats.items():
        print(f"  {k}: {v}")

    print()
    validation = run_validation()


if __name__ == "__main__":
    main()