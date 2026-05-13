#!/usr/bin/env python3
"""P0-1 v3: 全面提取接口/类方法签名。
- 纯虚方法 (virtual ... = 0)
- 普通虚方法 (virtual ... ;)
- 非虚 public 方法
- 静态方法
"""

import os
import re
import json

WORKSPACE = "/workspace"
OUTPUT = "/workspace/CAAKnowledge/data/interface_methods.json"


def normalize_spaces(s):
    return re.sub(r'\s+', ' ', s).strip()


def extract_class_description(lines, class_decl_line_idx):
    desc_lines = []
    in_abstract = False
    for i in range(max(0, class_decl_line_idx - 80), class_decl_line_idx):
        line = lines[i].strip()
        if re.match(r'//\s*Abstract\s+of\s+the\s+class', line, re.IGNORECASE):
            in_abstract = True
            continue
        if in_abstract:
            if line.startswith('//') and not re.match(r'//[=\-]{3,}', line):
                cleaned = re.sub(r'^//\s*-*\s*', '', line).strip()
                if cleaned:
                    desc_lines.append(cleaned)
            elif not line.startswith('//'):
                break
    if not desc_lines:
        for i in range(max(0, class_decl_line_idx - 80), class_decl_line_idx):
            line = lines[i].strip()
            if re.search(r'ABSTRACT', line, re.IGNORECASE) and not line.startswith('//=='):
                in_abstract = True
                continue
            if in_abstract:
                if line.startswith('//') and not re.match(r'//[=\-]{3,}', line):
                    cleaned = re.sub(r'^//\s*-*\s*', '', line).strip()
                    if cleaned and 'ABSTRACT' not in cleaned:
                        desc_lines.append(cleaned)
                elif not line.startswith('//'):
                    break
    return ' '.join(desc_lines) if desc_lines else ""


def extract_method_comment(lines, method_line_idx):
    comments = []
    for i in range(method_line_idx - 1, max(0, method_line_idx - 15), -1):
        line = lines[i].strip()
        if line.startswith('/**') or line.startswith('/*'):
            inner = re.sub(r'/\*\*?\s*', '', line)
            inner = re.sub(r'\s*\*/$', '', inner)
            inner = re.sub(r'^\s*\*\s*', '', inner)
            if inner.strip():
                comments.append(inner.strip())
        elif line.startswith('*') and not line.startswith('*/'):
            inner = re.sub(r'^\s*\*\s*', '', line).strip()
            if inner:
                comments.append(inner)
        elif line.startswith('//') and not re.match(r'//[=\-]{3,}', line):
            cleaned = re.sub(r'^//\s*', '', line).strip()
            if cleaned:
                comments.append(cleaned)
        elif not line.startswith('//') and line:
            break
    return ' '.join(reversed(comments)) if comments else ""


def find_class_body(lines):
    class_decl_line = -1
    for i, line in enumerate(lines):
        stripped = line.strip()
        if re.match(r'class\s+ExportedBy\w+\s+\w+', stripped):
            class_decl_line = i
            break
        elif re.match(r'class\s+\w+\s*:', stripped) and 'public' in stripped:
            class_decl_line = i
            break
        elif re.match(r'class\s+\w+\s*$', stripped):
            class_decl_line = i
            break

    if class_decl_line < 0:
        return -1, -1, -1

    brace_count = 0
    body_start = -1
    body_end = -1

    for i in range(class_decl_line, len(lines)):
        line = lines[i]
        brace_count += line.count('{') - line.count('}')
        if body_start < 0 and '{' in line:
            body_start = i + 1
        if body_start >= 0 and brace_count == 0 and '};' in line:
            body_end = i
            break

    if body_start < 0 or body_end < 0:
        return class_decl_line, -1, -1

    return class_decl_line, body_start, body_end


def find_access_sections(lines, body_start, body_end):
    """Find the public: section within class body."""
    public_start = body_start
    public_end = body_end

    for i in range(body_start, body_end):
        stripped = lines[i].strip()
        if stripped in ('public:', 'public :'):
            public_start = i + 1
            break

    for i in range(public_start, body_end):
        stripped = lines[i].strip()
        if stripped in ('private:', 'private :', 'protected:', 'protected :'):
            public_end = i
            break

    return public_start, public_end


def extract_methods_from_body(lines, body_start, body_end):
    methods = []
    public_start, public_end = find_access_sections(lines, body_start, body_end)

    # Join multi-line declarations
    body_text = '\n'.join(lines[public_start:public_end])
    body_text = re.sub(r',\s*\n\s*', ', ', body_text)
    body_text = re.sub(r'\(\s*\n\s*', '(', body_text)

    # Pattern 1: virtual ... = 0; (pure virtual)
    pure_pattern = re.compile(
        r'virtual\s+([\w\s*&<>:]+?)\s+(\w+)\s*\(([^)]*)\)\s*(const)?\s*=\s*0\s*;',
        re.MULTILINE
    )

    # Pattern 2: virtual ... ; (non-pure virtual)
    vmethod_pattern = re.compile(
        r'virtual\s+([\w\s*&<>:]+?)\s+(\w+)\s*\(([^)]*)\)\s*(const)?\s*;',
        re.MULTILINE
    )

    # Pattern 3: static HRESULT Method(params);
    static_pattern = re.compile(
        r'static\s+([\w\s*&<>:]+?)\s+(\w+)\s*\(([^)]*)\)\s*;',
        re.MULTILINE
    )

    # Pattern 4: HRESULT/int/void Method(params); (non-virtual, non-static, CAA-style)
    method_pattern = re.compile(
        r'(?:^|\n)\s*(HRESULT|void|int|CATBoolean|CATUnicodeString)\s+(\w+)\s*\(([^)]*)\)\s*(const)?\s*;',
        re.MULTILINE
    )

    seen = set()

    # Pure virtual methods (highest priority)
    for match in pure_pattern.finditer(body_text):
        method_name = match.group(2)
        if method_name.startswith('~'):
            continue
        key = (method_name, match.group(3).strip())
        if key in seen:
            continue
        seen.add(key)

        params = parse_params(match.group(3).strip())
        comment = find_comment(lines, public_start, public_end, method_name)

        methods.append({
            "name": method_name,
            "return_type": normalize_spaces(match.group(1)),
            "params": params,
            "const": bool(match.group(4)),
            "virtual": True,
            "pure_virtual": True,
            "static": False,
            "comment": comment
        })

    # Non-pure virtual methods
    for match in vmethod_pattern.finditer(body_text):
        method_name = match.group(2)
        if method_name.startswith('~'):
            continue
        key = (method_name, match.group(3).strip())
        if key in seen:
            continue
        seen.add(key)

        params = parse_params(match.group(3).strip())
        comment = find_comment(lines, public_start, public_end, method_name)

        methods.append({
            "name": method_name,
            "return_type": normalize_spaces(match.group(1)),
            "params": params,
            "const": bool(match.group(4)),
            "virtual": True,
            "pure_virtual": False,
            "static": False,
            "comment": comment
        })

    # Static methods
    for match in static_pattern.finditer(body_text):
        method_name = match.group(2)
        if method_name.startswith('~'):
            continue
        key = (method_name, match.group(3).strip())
        if key in seen:
            continue
        seen.add(key)

        params = parse_params(match.group(3).strip())
        comment = find_comment(lines, public_start, public_end, method_name)

        methods.append({
            "name": method_name,
            "return_type": normalize_spaces(match.group(1)),
            "params": params,
            "const": False,
            "pure_virtual": False,
            "static": True,
            "comment": comment
        })

    # Regular public methods (catch remaining)
    for match in method_pattern.finditer(body_text):
        method_name = match.group(2)
        if method_name.startswith('~'):
            continue
        key = (method_name, match.group(3).strip())
        if key in seen:
            continue
        seen.add(key)

        params = parse_params(match.group(3).strip())
        comment = find_comment(lines, public_start, public_end, method_name)

        methods.append({
            "name": method_name,
            "return_type": normalize_spaces(match.group(1)),
            "params": params,
            "const": bool(match.group(4)),
            "pure_virtual": False,
            "static": False,
            "comment": comment
        })

    return methods


def parse_params(params_str):
    params = []
    if not params_str or params_str == 'void':
        return params
    for param in params_str.split(','):
        param = normalize_spaces(param)
        if not param:
            continue
        parts = param.rsplit(None, 1)
        param_name = ""
        param_type = param
        if len(parts) >= 2:
            param_type = ' '.join(parts[:-1])
            param_name = parts[-1]
        params.append({"type": param_type, "name": param_name})
    return params


def find_comment(lines, body_start, body_end, method_name):
    for i in range(body_start, body_end):
        if method_name in lines[i] and ('virtual' in lines[i] or 'static' in lines[i] or 'HRESULT' in lines[i]):
            return extract_method_comment(lines, i)
    return ""


def extract_class_name(lines):
    for line in lines:
        stripped = line.strip()
        m = re.search(r'class\s+ExportedBy\w+\s+(\w+)', stripped)
        if m:
            return m.group(1)
        m = re.search(r'class\s+(\w+)\s*:', stripped)
        if m:
            return m.group(1)
    return ""


def extract_base_class(lines):
    for line in lines:
        m = re.search(r'class\s+(?:\w+\s+)?\w+\s*:\s*public\s+(\w+)', line)
        if m:
            return m.group(1)
    return ""


def extract_includes(lines):
    includes = []
    for line in lines:
        stripped = line.strip()
        if stripped.startswith('#include'):
            m = re.match(r'#include\s+[<"]([^>"]+)[>"]', stripped)
            if m:
                includes.append(m.group(1))
    return includes


def extract_module(filepath):
    m = re.search(r'/([^/]+)\.edu/', filepath)
    if m:
        return m.group(1)
    return ""


def extract_interface_type(filepath):
    if '/PublicInterfaces/' in filepath:
        return 'PublicInterface'
    elif '/ProtectedInterfaces/' in filepath:
        return 'ProtectedInterface'
    elif '/LocalInterfaces/' in filepath:
        return 'LocalClass'
    return 'Unknown'


def parse_header_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except Exception:
        return None

    lines = content.split('\n')
    class_name = extract_class_name(lines)
    if not class_name:
        return None

    class_decl_line, body_start, body_end = find_class_body(lines)

    base_class = extract_base_class(lines)
    module = extract_module(filepath)
    itype = extract_interface_type(filepath)
    description = extract_class_description(lines, class_decl_line if class_decl_line >= 0 else 0)
    includes = extract_includes(lines)

    if body_start < 0 or body_end < 0:
        return {
            "name": class_name, "base": base_class, "module": module,
            "type": itype, "description": description, "includes": includes,
            "methods": [], "method_count": 0,
            "source_file": os.path.relpath(filepath, WORKSPACE)
        }

    methods = extract_methods_from_body(lines, body_start, body_end)

    return {
        "name": class_name, "base": base_class, "module": module,
        "type": itype, "description": description, "includes": includes,
        "methods": methods, "method_count": len(methods),
        "source_file": os.path.relpath(filepath, WORKSPACE)
    }


def main():
    interfaces = {}
    stats = {"total_files": 0, "with_methods": 0, "total_methods": 0, "empty": 0, "skipped": 0}

    for root, dirs, files in os.walk(WORKSPACE):
        if '.edu' not in root:
            continue
        has_iface_dir = any(d in root.split(os.sep) for d in
                            ["PublicInterfaces", "ProtectedInterfaces", "LocalInterfaces"])
        if not has_iface_dir:
            continue
        for fname in files:
            if not fname.endswith('.h'):
                continue
            fpath = os.path.join(root, fname)
            result = parse_header_file(fpath)
            if result is None:
                stats["skipped"] += 1
                continue

            stats["total_files"] += 1
            name = result["name"]
            if name in interfaces:
                existing = interfaces[name]
                if result["type"] == "PublicInterface" and existing["type"] != "PublicInterface":
                    interfaces[name] = result
                elif result["type"] == "ProtectedInterface" and existing["type"] == "LocalClass":
                    interfaces[name] = result
            else:
                interfaces[name] = result

            if result["method_count"] > 0:
                stats["with_methods"] += 1
                stats["total_methods"] += result["method_count"]
            else:
                stats["empty"] += 1

    method_index = {}
    for name, data in interfaces.items():
        for m in data["methods"]:
            mname = m["name"]
            if mname not in method_index:
                method_index[mname] = []
            method_index[mname].append(name)

    output = {
        "version": "3.0",
        "stats": stats,
        "interfaces": interfaces,
        "method_index": method_index
    }

    os.makedirs(os.path.dirname(OUTPUT), exist_ok=True)
    with open(OUTPUT, 'w', encoding='utf-8') as f:
        json.dump(output, f, indent=2, ensure_ascii=False)

    print(f"Total files parsed: {stats['total_files']}")
    print(f"Interfaces/classes with methods: {stats['with_methods']}")
    print(f"Empty (no methods found): {stats['empty']}")
    print(f"Total methods extracted: {stats['total_methods']}")
    print(f"Skipped (no class found): {stats['skipped']}")
    print(f"Method index entries: {len(method_index)}")
    print(f"Output: {OUTPUT}")


if __name__ == "__main__":
    main()