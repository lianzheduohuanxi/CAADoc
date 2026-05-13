#!/usr/bin/env python3
"""P2: 重建搜索索引 + 交叉引用增强。"""

import os
import re
import json

KB_DIR = "/workspace/CAAKnowledge"
SEARCH_INDEX = os.path.join(KB_DIR, "data", "search-index.json")
CROSS_REF_FILE = os.path.join(KB_DIR, "data", "cross_references.json")


def extract_title(content):
    m = re.search(r'title:\s*"(.+?)"', content[:500])
    if m:
        return m.group(1)
    m = re.search(r'^#\s+(.+)$', content[:500], re.MULTILINE)
    if m:
        return m.group(1).strip()
    return ""


def extract_keywords(content):
    """Extract CAA API names and key terms from document content."""
    keywords = set()

    # CATI* / CAAI* interface names
    for m in re.finditer(r'\b(CATI\w+|CAAI\w+|CAA\w+)\b', content):
        kw = m.group(1)
        if len(kw) > 4 and not kw.startswith('CAAKnowledge'):
            keywords.add(kw)

    # HRESULT method names
    for m in re.finditer(r'(?:virtual\s+)?(?:static\s+)?HRESULT\s+(\w+)', content):
        keywords.add(m.group(1))

    # Framework names
    for m in re.finditer(r'(?:ApplicationFrame|System|Mathematics|ObjectModelerBase|ObjectSpecsModeler|Visualization|MechanicalModeler|ProductStructure|Knowledgeware|Manufacturing|Dialog|LiteralFeatures|ElecHarness|ElecFlattening|V5V6)\w*', content):
        keywords.add(m.group(0))

    # CAA concepts
    for kw in ['QueryInterface', 'TIE', 'CATImplementInterface', 'CATDeclareInterface',
               'CATDeclareClass', 'CATBaseUnknown', 'S_OK', 'E_FAIL', 'AddRef', 'Release',
               'workbench', 'command', 'addin', 'toolbar', 'dialog', 'feature',
               'container', 'document', 'session', 'part', 'product', 'sketch']:
        if kw.lower() in content.lower():
            keywords.add(kw)

    return list(keywords)[:30]


def extract_summary(content):
    """Extract first meaningful paragraph after frontmatter."""
    # Skip frontmatter
    body = content
    if content.startswith('---'):
        parts = content.split('---', 2)
        if len(parts) >= 3:
            body = parts[2]

    lines = body.strip().split('\n')
    summary_lines = []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith('#'):
            continue
        if stripped.startswith('>'):
            summary_lines.append(stripped[1:].strip())
        elif stripped and not stripped.startswith('```') and not stripped.startswith('|'):
            summary_lines.append(stripped)
        if len(' '.join(summary_lines)) > 200:
            break

    summary = ' '.join(summary_lines)[:300]
    return summary


def build_search_index():
    documents = []
    keyword_index = {}

    search_dirs = [
        ("api-reference/interfaces", "interface"),
        ("use-cases", "use-case"),
        ("quick-refs", "quick-ref"),
        ("troubleshooting", "troubleshooting"),
    ]

    exclude_patterns = [r'报告', r'执行', r'审查', r'检查', r'缺陷', r'计划', r'状态']

    for search_dir, doc_type in search_dirs:
        full_dir = os.path.join(KB_DIR, search_dir)
        if not os.path.exists(full_dir):
            continue

        for root, dirs, files in os.walk(full_dir):
            for fname in files:
                if not fname.endswith('.md'):
                    continue

                # Exclude report files
                if any(re.search(pat, fname) for pat in exclude_patterns):
                    continue

                fpath = os.path.join(root, fname)
                try:
                    with open(fpath, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                except Exception:
                    continue

                rel_path = os.path.relpath(fpath, KB_DIR)
                title = extract_title(content) or fname[:-3]
                keywords = extract_keywords(content)
                summary = extract_summary(content)

                doc_entry = {
                    "title": title,
                    "type": doc_type,
                    "path": rel_path,
                    "keywords": keywords,
                    "summary": summary
                }
                documents.append(doc_entry)

                for kw in keywords:
                    if kw not in keyword_index:
                        keyword_index[kw] = []
                    keyword_index[kw].append(rel_path)

    output = {
        "version": "2.0",
        "total_docs": len(documents),
        "documents": documents,
        "keyword_index": keyword_index
    }

    os.makedirs(os.path.dirname(SEARCH_INDEX), exist_ok=True)
    with open(SEARCH_INDEX, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2, ensure_ascii=False)

    print(f"Search index: {len(documents)} documents, {len(keyword_index)} keywords")
    print(f"Output: {SEARCH_INDEX}")


def build_cross_references():
    """Build bidirectional cross-references between interfaces and use-cases."""
    xrefs = {}

    # Scan use-cases for interface references
    use_cases_dir = os.path.join(KB_DIR, "use-cases")
    if os.path.exists(use_cases_dir):
        for root, dirs, files in os.walk(use_cases_dir):
            for fname in files:
                if not fname.endswith('.md'):
                    continue
                fpath = os.path.join(root, fname)
                try:
                    with open(fpath, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                except Exception:
                    continue

                # Find CATI*/CAAI* references
                ifaces = set()
                for m in re.finditer(r'\b((?:CATI|CAAI)\w+)\b', content):
                    name = m.group(1)
                    if len(name) > 6 and not name.startswith('CAAKnowledge'):
                        ifaces.add(name)

                if ifaces:
                    rel_path = os.path.relpath(fpath, KB_DIR)
                    for iface in ifaces:
                        if iface not in xrefs:
                            xrefs[iface] = []
                        if rel_path not in xrefs[iface]:
                            xrefs[iface].append(rel_path)

    with open(CROSS_REF_FILE, 'w', encoding='utf-8') as f:
        json.dump({"version": "1.0", "total_interfaces": len(xrefs), "references": xrefs}, f, indent=2, ensure_ascii=False)

    print(f"Cross-references: {len(xrefs)} interfaces linked to use-cases")
    print(f"Output: {CROSS_REF_FILE}")


def main():
    build_search_index()
    print()
    build_cross_references()


if __name__ == "__main__":
    main()