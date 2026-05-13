# -*- coding: utf-8 -*-
"""
构建完整接口继承树 - P1-3
"""

import re
import sys
from pathlib import Path
import json

sys.stdout.reconfigure(encoding='utf-8')

def extract_inheritance_from_interface(content):
    """从接口文档提取继承关系"""
    patterns = [
        r'继承自\s+\*\*([A-Z][A-Za-z0-9]+)\*\*',
        r'extends\s+([A-Z][A-Za-z0-9]+)',
        r'inherits\s+([A-Z][A-Za-z0-9]+)',
        r'→\s+([A-Z][A-Za-z0-9]+)\s*[\|`]',
        r'Base Interface[:\s]+([A-Z][A-Za-z0-9]+)',
    ]
    
    for pattern in patterns:
        match = re.search(pattern, content, re.IGNORECASE)
        if match:
            return match.group(1)
    
    return None

def build_inheritance_tree():
    """构建完整继承树"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    # 基础接口映射
    base_interfaces = {
        'CATBaseUnknown': None,
        'CATIInterface': 'CATBaseUnknown',
        'CATIAlias': 'CATBaseUnknown',
        'CATIObject': 'CATBaseUnknown',
        'CATIDispatch': 'CATBaseUnknown',
    }
    
    inheritance_tree = {}
    
    # 从文档中提取
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        base = extract_inheritance_from_interface(content)
        
        if base:
            interface_name = md_file.stem
            inheritance_tree[interface_name] = base
    
    return inheritance_tree

def trace_to_root(interface_name, inheritance_tree, visited=None):
    """追溯到CATBaseUnknown"""
    if visited is None:
        visited = []
    
    if interface_name in visited:
        return visited
    
    visited.append(interface_name)
    
    base = inheritance_tree.get(interface_name)
    if base and base != 'CATBaseUnknown':
        return trace_to_root(base, inheritance_tree, visited)
    
    return visited

def main():
    print("P1-3: Building Full Interface Inheritance Tree")
    print("=" * 50)
    
    inheritance_tree = build_inheritance_tree()
    
    # 构建完整继承路径
    full_paths = {}
    for interface in inheritance_tree:
        path = trace_to_root(interface, inheritance_tree)
        full_paths[interface] = path
    
    # 保存结果
    output_file = Path(r'C:\Luxshare\CAADoc\CAAKnowledge\quick-refs\interface-hierarchy-full.json')
    
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump({
            'total_interfaces': len(full_paths),
            'inheritance_tree': inheritance_tree,
            'full_paths': full_paths
        }, f, indent=2, ensure_ascii=False)
    
    # 生成Markdown版本
    md_file = Path(r'C:\Luxshare\CAADoc\CAAKnowledge\quick-refs\interface-hierarchy-full.md')
    with open(md_file, 'w', encoding='utf-8') as f:
        f.write("# Interface Hierarchy (Full)\n\n")
        f.write(f"Total interfaces: {len(full_paths)}\n\n")
        f.write("---\n\n")
        f.write("## Inheritance Paths\n\n")
        
        for interface, path in sorted(full_paths.items()):
            path_str = " → ".join([f"`{p}`" for p in path])
            f.write(f"- **{interface}**: {path_str}\n")
    
    print(f"[OK] Inheritance tree built: {len(full_paths)} interfaces")
    print(f"JSON output: {output_file}")
    print(f"MD output: {md_file}")

if __name__ == '__main__':
    main()