#!/usr/bin/env python3
"""P0-2 + P0-3: 从 interface_methods.json 重生成接口 .md 文档并更新 knowledge_base.json"""

import json
import os

DATA_DIR = "/workspace/CAAKnowledge/data"
API_DIR = "/workspace/CAAKnowledge/api-reference/interfaces"
METHODS_FILE = os.path.join(DATA_DIR, "interface_methods.json")
KB_FILE = os.path.join(DATA_DIR, "knowledge_base.json")


def load_methods():
    with open(METHODS_FILE) as f:
        return json.load(f)


def load_existing_kb():
    if os.path.exists(KB_FILE):
        with open(KB_FILE) as f:
            return json.load(f)
    return {"version": "1.0", "interfaces": {}}


def generate_method_table(method):
    """Generate a markdown table row for method params."""
    lines = []
    lines.append(f"### {method['name']}")
    lines.append("")
    sig_parts = []
    if method.get('static'):
        sig_parts.append('static')
    if method.get('virtual', False) or method.get('pure_virtual', False):
        sig_parts.append('virtual')
    sig_parts.append(method['return_type'])
    sig_parts.append(f"{method['name']}(")
    params_str = ', '.join(f"{p['type']} {p['name']}" for p in method.get('params', []))
    sig_parts.append(f"{params_str})")
    if method.get('const'):
        sig_parts.append('const')
    if method.get('pure_virtual'):
        sig_parts.append('= 0')
    sig_parts.append(';')
    signature = ' '.join(sig_parts).replace('( ', '(').replace(' )', ')')
    lines.append(f"```cpp")
    lines.append(signature)
    lines.append(f"```")
    lines.append("")

    if method.get('comment'):
        lines.append(f"{method['comment']}")
        lines.append("")

    if method.get('params'):
        lines.append("| 参数 | 类型 |")
        lines.append("|------|------|")
        for p in method['params']:
            lines.append(f"| {p['name']} | `{p['type']}` |")
        lines.append("")

    if method.get('pure_virtual'):
        lines.append("**返回值**: `S_OK` 成功, `E_FAIL` 失败")
    lines.append("")

    return '\n'.join(lines)


def generate_interface_md(name, info):
    """Generate a complete interface markdown document."""
    lines = []
    lines.append("---")
    lines.append(f"title: \"{name}\"")
    lines.append(f"type: \"{info['type']}\"")
    lines.append(f"module: \"{info.get('module', '')}\"")
    lines.append(f"base: \"{info.get('base', '')}\"")
    lines.append(f"method_count: {info['method_count']}")
    lines.append(f"source_file: \"{info.get('source_file', '')}\"")
    lines.append("---")
    lines.append("")
    lines.append(f"# {name}")
    lines.append("")

    if info.get('description'):
        lines.append(f"> {info['description']}")
        lines.append("")

    base = info.get('base', '')
    module = info.get('module', '')
    mc = info['method_count']
    lines.append(f"**基类**: {base if base else '无'} | **模块**: {module} | **方法数**: {mc}")
    lines.append("")

    if info.get('includes'):
        lines.append("## 依赖")
        lines.append("")
        for inc in info['includes']:
            lines.append(f"- `{inc}`")
        lines.append("")

    if info.get('methods'):
        pure = [m for m in info['methods'] if m.get('pure_virtual')]
        vmethods = [m for m in info['methods'] if m.get('virtual', False) and not m.get('pure_virtual')]
        static = [m for m in info['methods'] if m.get('static')]
        regular = [m for m in info['methods'] if not m.get('virtual', False) and not m.get('static') and not m.get('pure_virtual')]

        if pure:
            lines.append("## 纯虚方法 (接口契约)")
            lines.append("")
            for m in pure:
                lines.append(generate_method_table(m))

        if vmethods:
            lines.append("## 虚方法")
            lines.append("")
            for m in vmethods:
                lines.append(generate_method_table(m))

        if static:
            lines.append("## 静态方法")
            lines.append("")
            for m in static:
                lines.append(generate_method_table(m))

        if regular:
            lines.append("## 公共方法")
            lines.append("")
            for m in regular:
                lines.append(generate_method_table(m))

    if info.get('source_file'):
        lines.append("---")
        lines.append("")
        lines.append(f"**源文件**: `{info['source_file']}`")

    return '\n'.join(lines) + '\n'


def main():
    data = load_methods()
    interfaces = data['interfaces']
    method_index = data['method_index']

    os.makedirs(API_DIR, exist_ok=True)

    generated = 0
    skipped = 0

    for name, info in interfaces.items():
        fpath = os.path.join(API_DIR, f"{name}.md")
        md_content = generate_interface_md(name, info)
        with open(fpath, 'w', encoding='utf-8') as f:
            f.write(md_content)
        generated += 1

    # Also check for existing template files that have no source match
    existing = set(os.listdir(API_DIR))
    for fname in existing:
        if fname.endswith('.md'):
            name = fname[:-3]
            if name not in interfaces:
                # Keep existing template but mark as no-source
                pass

    # Update knowledge_base.json
    kb = load_existing_kb()
    kb['version'] = '2.0'
    kb['stats'] = data['stats']

    kb_interfaces = {}
    for name, info in interfaces.items():
        kb_interfaces[name] = {
            "name": name,
            "base": info.get('base', ''),
            "module": info.get('module', ''),
            "type": info.get('type', ''),
            "description": info.get('description', ''),
            "method_count": info['method_count'],
            "methods": info.get('methods', []),
            "source_file": info.get('source_file', ''),
            "has_tie": False,
            "inheritance_chain": [info.get('base', '')] if info.get('base') else []
        }
    kb['interfaces'] = kb_interfaces
    kb['method_index'] = method_index

    with open(KB_FILE, 'w', encoding='utf-8') as f:
        json.dump(kb, f, indent=2, ensure_ascii=False)

    print(f"Interface .md docs generated: {generated}")
    print(f"knowledge_base.json updated: {len(kb_interfaces)} interfaces, {len(method_index)} method index entries")
    print(f"Output dir: {API_DIR}")
    print(f"KB file: {KB_FILE}")


if __name__ == "__main__":
    main()