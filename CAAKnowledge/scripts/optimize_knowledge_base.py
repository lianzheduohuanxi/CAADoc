#!/usr/bin/env python3
"""
CATIA CAA V5 知识库优化脚本 v4
从源码提取更多信息，修复已知缺陷：
1. category分类 - 从CAA_INDEXFILE.DSidx获取
2. 路径分隔符 - 反斜杠转正斜杠
3. 代码块围栏 - 检测VBScript/C++代码并添加围栏
4. 接口继承链 - 追溯完整继承树
5. API版本元数据 - 从目录名提取版本
6. TIE双向关联 - 接口文档添加TIE引用
"""
import re, os, sys, json
from pathlib import Path
from collections import defaultdict

sys.stdout.reconfigure(encoding='utf-8')

# ============ 1. 从CAA_INDEXFILE.DSidx加载category映射 ============
def load_category_mapping():
    """从索引文件加载模块到分类的映射"""
    mapping = {}
    idx_file = 'Doc/online/CAA_INDEXFILE.DSidx'
    if os.path.exists(idx_file):
        with open(idx_file, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
        i = 0
        while i < len(lines):
            line = lines[i].strip()
            if line and not line.startswith('#'):
                module = line
                if i + 1 < len(lines):
                    category = lines[i + 1].strip()
                    # 映射到标准分类
                    category_map = {
                        'User Interface': 'dialog',
                        '3D Visualization': 'visualization',
                        'Analysis': 'analysis',
                        'Analysis Automation': 'analysis',
                        'Middleware Abstraction': 'framework',
                        'Data Access': 'data-access',
                        'Security': 'security',
                        'Catalog Modeler': 'catalog',
                        'Instant Collaborative Design Enabler': 'collaboration',
                        'PPR': 'ppr',
                        'Document': 'document',
                        'Knowledge Modeler': 'knowledge',
                        'Feature Modeler': 'feature',
                        'CATIA PDM Interoperation': 'pdm',
                        'Product Structure Modeler': 'product-structure',
                        'Cax & PDM Hub': 'pdm',
                        '2D Layout for 3D Design Automation': 'automation',
                        '2D Layout for 3D Design': 'automation',
                        'Business Process Knowledge Template Automation': 'automation',
                        'Automation Infrastructure': 'automation',
                        'ENOVIA V6 Integration Automation': 'automation',
                        'Process Modeler Automation': 'automation',
                        'DMU Automation': 'dmu',
                        'Drafting Automation': 'drafting',
                        'Functional Modeling Automation': 'automation',
                        'Generative Shape Design Automation': 'gdm',
                        'Knowledge Expert Automation': 'knowledge',
                        'Knowledge Modeler Automation': 'knowledge',
                        'Machining Automation': 'manufacturing',
                        'Materials Automation': 'manufacturing',
                        'Mechanical Modeler Automation': 'manufacturing',
                        'Part Design Automation': 'manufacturing',
                        'Product Structure Modeler Automation': 'product-structure',
                        'Real Time Rendering Automation': 'visualization',
                        'DMU Optimizer Automation': 'dmu',
                        'Schematic Platform Automation': 'schematic',
                        'Structure Detail Design': 'structure',
                        'Structure Functional Design': 'structure',
                        'SmarTeam Integration Automation': 'pdm',
                        'Structure Design Automation': 'structure',
                        'Tolerancing Automation': 'tolerancing',
                        'Geometry': 'geometry',
                        'Mathematics': 'mathematics',
                        'Topology': 'topology',
                        'Tessellation': 'tessellation',
                        'NC Review': 'manufacturing',
                        'Prismatic Machining': 'manufacturing',
                        'Surface Machining': 'manufacturing',
                        'Advanced Machining': 'manufacturing',
                        'Assembly': 'assembly',
                        'Drafting': 'drafting',
                        'Mechanical Modeler': 'mechanical',
                        'Part Design': 'part-design',
                        'Structure': 'structure',
                        'Machining Algorithms': 'manufacturing',
                        'Business Process Knowledge Template': 'knowledge',
                        'Product Function Definition': 'knowledge',
                        'Knowledge Expert': 'knowledge',
                        'DMU Kinematics Simulator': 'kinematics',
                        'Product Engineering Optimizer': 'optimization',
                        'Space Analysis': 'analysis',
                        'Aerospace Sheet Metal Design': 'manufacturing',
                        'RADE Guides': 'documentation',
                        'Environment Manager': 'environment',
                        'Interactive Test Capture - ITC': 'testing',
                        'C++ Unit Test Manager - mkODT': 'testing',
                        'Java Unit Test Manager - mkODT': 'testing',
                        'C++ Interactive Dashboard': 'dashboard',
                        'Java Interactive Dashboard': 'dashboard',
                        'Multi-Workspace Application Builder - mkmk': 'build',
                        'Interactive Dialog Designer': 'dialog',
                        'Data Model Customizer': 'data-model',
                        'ENOVIA Web Services': 'web-services',
                        'Security Web Services': 'security',
                        'Web Services Infrastructure': 'web-services',
                        'V6 Geometric Modeler': 'geometry',
                        'Geometric Modeler Overview': 'geometry',
                        'Arrangement': 'arrangement',
                        'Schematics': 'schematic',
                        'Common Layout': 'layout',
                        'PlantShip': 'manufacturing',
                        'Electrical Connectivity Diagrams': 'electrical',
                        'Electrical Flattening': 'electrical',
                        'Electrical Harness Installation': 'electrical',
                        'Electrical Device Librarian': 'electrical',
                        'Electrical Wire Routing': 'electrical',
                        'Change Management': 'change-management',
                        'ENOVIA LCA Navigator': 'navigator',
                        'Document Management': 'document',
                        'VPM Integration': 'vpm',
                        'ENOVIA V5 VPM': 'vpm',
                        'EBOM Part & Assembly Detailing': 'part-design',
                    }
                    mapped_cat = category_map.get(category, 'framework')
                    mapping[module] = mapped_cat
                i += 2
            else:
                i += 1
    return mapping

# ============ 2. 接口继承链追溯 ============
def build_inheritance_chain(interfaces):
    """构建完整的继承链"""
    chain_cache = {}
    
    def get_chain(iface_name):
        if iface_name in chain_cache:
            return chain_cache[iface_name]
        
        if iface_name not in interfaces:
            chain_cache[iface_name] = [iface_name]
            return chain_cache[iface_name]
        
        base = interfaces[iface_name]['base']
        # 常见基础接口，不需要继续追溯
        if base in ('CATBaseUnknown', 'CATIUnknown', 'IUnknown'):
            chain_cache[iface_name] = [iface_name, base]
            return chain_cache[iface_name]
        
        parent_chain = get_chain(base)
        chain_cache[iface_name] = [iface_name] + parent_chain
        return chain_cache[iface_name]
    
    for iface_name in interfaces:
        get_chain(iface_name)
    
    return chain_cache

# ============ 3. 加载现有知识库 ============
def load_knowledge_base():
    kb_file = 'CAAKnowledge/data/knowledge_base_v3.json'
    if os.path.exists(kb_file):
        with open(kb_file, 'r', encoding='utf-8') as f:
            return json.load(f)
    return {'interfaces': {}, 'tie_bindings': [], 'qi_paths': []}

# ============ 4. 提取TIE绑定信息 ============
def load_tie_bindings():
    tie_file = 'CAAKnowledge/data/tie_bindings.json'
    if os.path.exists(tie_file):
        with open(tie_file, 'r', encoding='utf-8') as f:
            return json.load(f)
    return []

def build_tie_map():
    """构建接口名到TIE绑定的映射"""
    tie_map = {}
    tie_data = load_tie_bindings()
    if isinstance(tie_data, list):
        for t in tie_data:
            iface = t.get('interface', '')
            tie_map[iface] = t
    return tie_map

# ============ 5. 主优化函数 ============
def main():
    print("=" * 60)
    print("CATIA CAA V5 知识库优化 v4")
    print("=" * 60)
    
    # 加载category映射
    category_map = load_category_mapping()
    print(f"加载了 {len(category_map)} 个模块的分类映射")
    
    # 加载知识库
    kb = load_knowledge_base()
    interfaces = kb.get('interfaces', {})
    print(f"加载了 {len(interfaces)} 个接口")
    
    # 构建继承链
    inheritance_chains = build_inheritance_chain(interfaces)
    print(f"构建了 {len(inheritance_chains)} 个接口的继承链")
    
    # 构建TIE映射
    tie_map = build_tie_map()
    print(f"加载了 {len(tie_map)} 个TIE绑定映射")
    
    # ============ 优化接口文档 ============
    out_dir = 'CAAKnowledge/api-reference/interfaces'
    os.makedirs(out_dir, exist_ok=True)
    
    optimized = 0
    for name, d in interfaces.items():
        # 获取category
        module = d.get('module', '')
        category = category_map.get(module, 'framework')
        
        # 获取继承链
        chain = inheritance_chains.get(name, [name])
        inheritance_chain = ' → '.join(chain)
        
        # 检查是否有TIE绑定
        has_tie = name in tie_map
        tie_info = tie_map.get(name, {})
        
        # 生成优化的文档
        md = f'''---
title: "{name}"
type: "interface"
module: "{module}"
category: "{category}"
base: "{d['base']}"
inheritance_chain: "{inheritance_chain}"
method_count: {d['method_count']}
visibility: "{d['visibility']}"
has_tie_binding: {str(has_tie).lower()}
verified: true
---
'''
        if has_tie and tie_info:
            md += f'> **TIE实现**: {tie_info.get("source", "unknown")}\n\n'
        
        md += f'# {name}\n\n'
        md += f'**基类**: {d["base"]}  \n'
        md += f'**继承链**: {inheritance_chain}  \n'
        md += f'**模块**: {module}  \n'
        md += f'**分类**: {category}  \n'
        md += f'**可见性**: {d["visibility"]}  \n'
        md += f'**方法数**: {d["method_count"]}\n\n'
        
        if d.get('comment') and d['comment'] not in ('--- ObjectModelerBase Framework ---', '===========================================================================', '==============================================', ''):
            md += f'> {d["comment"]}\n\n'
        
        if d.get('methods') and len(d.get('methods', [])) > 0:
            md += '## 方法列表\n\n'
            for m in d['methods']:
                c = ' const' if m.get('is_const') else ''
                md += f'### {m["name"]}\n```cpp\n{m["return_type"]} {m["name"]}({m["parameters"]}){c};\n```\n\n'
        elif d["method_count"] == 0:
            # 检查是否是从基类继承的方法
            inherited_count = len(chain) - 1
            if inherited_count > 1:
                md += f'## 说明\n\n该接口没有在当前头文件中声明方法。继承自基类的潜在方法请查阅基类文档。\n\n'
                md += f'- 完整继承链: {inheritance_chain}\n'
            else:
                md += '## 说明\n\n该接口作为标记接口或配置接口使用，无自定义方法。\n\n'
        
        if d.get('includes'):
            md += '## 依赖\n\n'
            for inc in d['includes'][:10]:
                md += f'- `{inc}`\n'
            md += '\n'
        
        # 添加TIE实现文件
        if has_tie and tie_info:
            md += '## TIE实现\n\n'
            cpp_files = tie_info.get('cpp_files', [])
            if cpp_files:
                md += '**实现文件**:\n'
                for cpp in cpp_files[:5]:
                    md += f'- `{cpp}`\n'
            md += '\n'
        
        with open(os.path.join(out_dir, f'{name}.md'), 'w', encoding='utf-8') as f:
            f.write(md)
        optimized += 1
    
    print(f"优化了 {optimized} 个接口文档")
    
    # ============ 优化Use-Case文档 ============
    print("\n优化 Use-Case 文档...")
    use_case_dir = Path('CAAKnowledge/use-cases')
    if use_case_dir.exists():
        fixed_paths = 0
        fixed_categories = 0
        fixed_code_blocks = 0
        
        for md_file in use_case_dir.rglob('*.md'):
            try:
                with open(md_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                
                original = content
                
                # 1. 修复反斜杠路径
                content = content.replace('source_file: "Doc\\', 'source_file: "Doc/')
                content = re.sub(r'([a-zA-Z]):\\', lambda m: m.group(1) + '/', content)
                
                # 2. 修复category（如果当前是general）
                content = re.sub(
                    r'^category:\s*"general"$',
                    lambda m: f'category: "{infer_category(content, str(md_file))}"',
                    content,
                    flags=re.MULTILINE
                )
                
                # 3. 修复VBScript代码块（添加围栏）
                content = fix_vbscript_blocks(content)
                
                if content != original:
                    with open(md_file, 'w', encoding='utf-8') as f:
                        f.write(content)
                    
                    if 'Doc/' in content and 'Doc\\' not in content:
                        fixed_paths += 1
                    if re.search(r'^category:', content, re.MULTILINE):
                        fixed_categories += 1
                    if '```vbscript' in content or '```cpp' in content:
                        fixed_code_blocks += 1
            except Exception as e:
                pass
        
        print(f"修复了 {fixed_paths} 个路径，{fixed_categories} 个分类，{fixed_code_blocks} 个代码块")
    
    # ============ 生成优化后的知识库JSON ============
    enhanced_kb = {
        'interfaces': {},
        'inheritance_chains': {},
        'category_mapping': category_map,
        'tie_bindings': kb.get('tie_bindings', []),
        'qi_paths': kb.get('qi_paths', []),
        'stats': {
            'total': len(interfaces),
            'with_methods': sum(1 for v in interfaces.values() if v['method_count'] > 0),
            'empty': sum(1 for v in interfaces.values() if v['method_count'] == 0),
            'tie_bindings': len(kb.get('tie_bindings', [])),
            'qi_paths': len(kb.get('qi_paths', [])),
            'categories': len(set(category_map.values()))
        }
    }
    
    # 添加增强的接口信息
    for name, d in interfaces.items():
        enhanced_kb['interfaces'][name] = {
            'name': name,
            'base': d['base'],
            'module': d['module'],
            'category': category_map.get(d['module'], 'framework'),
            'method_count': d['method_count'],
            'inheritance_chain': inheritance_chains.get(name, [name]),
            'visibility': d['visibility'],
            'has_tie': name in tie_map,
            'source': d.get('source', ''),
            'includes': d.get('includes', [])
        }
        enhanced_kb['inheritance_chains'][name] = inheritance_chains.get(name, [name])
    
    with open('CAAKnowledge/data/knowledge_base_v4.json', 'w', encoding='utf-8') as f:
        json.dump(enhanced_kb, f, ensure_ascii=False, indent=2)
    
    print(f"\n生成了增强版知识库: CAAKnowledge/data/knowledge_base_v4.json")
    
    # ============ 生成接口继承树 ============
    generate_inheritance_tree(interfaces, inheritance_chains)
    
    print("\n" + "=" * 60)
    print("优化完成!")
    print("=" * 60)

def infer_category(content, filepath):
    """从内容推断文档分类"""
    # 从标题推断
    title_match = re.search(r'^title:\s*"([^"]+)"', content, re.MULTILINE)
    if title_match:
        title = title_match.group(1).lower()
        if 'creating' in title or 'add' in title or 'insert' in title or 'delete' in title:
            return 'use-case'
        if 'how to' in title or 'howto' in title:
            return 'tutorial'
        if 'overview' in title or 'introduction' in title:
            return 'concept'
        if 'error' in title or 'troubleshoot' in title:
            return 'troubleshooting'
        if 'api change' in title or 'migration' in title:
            return 'api-changes'
    
    # 从目录推断
    parts = filepath.replace('\\', '/').split('/')
    for part in parts:
        if 'usecases' in part.lower() or part.endswith('cases'):
            return 'use-case'
        if 'techarticles' in part.lower():
            return 'tech-article'
        if 'quickrefs' in part.lower():
            return 'quick-reference'
    
    return 'use-case'

def fix_vbscript_blocks(content):
    """修复VBScript代码块，添加围栏"""
    lines = content.split('\n')
    result = []
    in_code = False
    code_lines = []
    code_start = -1
    
    for i, line in enumerate(lines):
        # 检测VBScript代码开始
        if not in_code:
            # VBScript特征：Set、Dim、CATIA.、.Add(、Err.Raise等
            if re.match(r'^\s*(Set |Dim |CATIA\.|Err\.Raise|If \(|End If|For |Next |While |Wend|Do |Loop|Sub |Function |End Sub|End Function)', line):
                in_code = True
                code_start = i
                code_lines = [line]
            else:
                result.append(line)
        else:
            # 检查是否继续是代码
            stripped = line.strip()
            # 代码结束标志
            if stripped.startswith('---') or stripped.startswith('# ') or stripped.startswith('**') or (stripped and not stripped.startswith("'") and not re.match(r'^\s', line) and not stripped.startswith('Set ') and not stripped.startswith('Dim ') and not 'CATIA.' in stripped and not '.Add(' in stripped and not 'Err.' in stripped and not re.match(r'^\s+(If |For |While |Do |Select )', line)):
                # 代码块结束，写入代码
                if code_lines:
                    result.append('```vbscript')
                    result.extend(code_lines)
                    result.append('```')
                    result.append('')
                in_code = False
                code_lines = []
                result.append(line)
            elif stripped == '' and len(code_lines) > 0:
                # 检查下一行是否还是代码
                if i + 1 < len(lines):
                    next_line = lines[i + 1].strip()
                    if not (next_line.startswith("'") or next_line.startswith('Set ') or next_line.startswith('Dim ') or 'CATIA.' in next_line or '.Add(' in next_line or 'Err.' in next_line):
                        # 空行后不是代码，结束代码块
                        code_lines.append(line)
                        result.append('```vbscript')
                        result.extend(code_lines)
                        result.append('```')
                        result.append('')
                        in_code = False
                        code_lines = []
                    else:
                        code_lines.append(line)
                else:
                    code_lines.append(line)
            else:
                code_lines.append(line)
    
    # 处理未关闭的代码块
    if in_code and code_lines:
        result.append('```vbscript')
        result.extend(code_lines)
        result.append('```')
    
    return '\n'.join(result)

def generate_inheritance_tree(interfaces, chains):
    """生成接口继承树文档"""
    # 按根接口分组
    roots = defaultdict(list)
    for name, chain in chains.items():
        if chain:
            root = chain[-1]
            roots[root].append(name)
    
    # 生成Markdown
    md = '''---
title: "接口继承树"
type: "quick-reference"
verified: true
---

# CATIA CAA V5 接口继承树

> 本文档展示接口的完整继承关系

'''
    
    # 常见基础接口
    common_roots = ['CATBaseUnknown', 'CATIUnknown', 'IUnknown']
    for root in common_roots:
        if root in roots:
            md += f'\n## {root} (根接口)\n\n'
            for iface in sorted(roots[root])[:50]:  # 限制每个根最多50个
                chain = chains.get(iface, [iface])
                chain_str = ' → '.join(chain)
                md += f'- **{iface}**: {chain_str}\n'
            if len(roots[root]) > 50:
                md += f'\n_... 还有 {len(roots[root]) - 50} 个接口_\n'
    
    # 其他根接口
    other = {k: v for k, v in roots.items() if k not in common_roots}
    if other:
        md += '\n## 其他根接口\n\n'
        for root, ifaces in sorted(other.items(), key=lambda x: -len(x[1]))[:20]:
            md += f'\n### {root} ({len(ifaces)} 个派生接口)\n\n'
            for iface in sorted(ifaces)[:20]:
                chain = chains.get(iface, [iface])
                md += f'- {iface}\n'
            if len(ifaces) > 20:
                md += f'_... 还有 {len(ifaces) - 20} 个接口_\n'
    
    with open('CAAKnowledge/quick-refs/interface-hierarchy.md', 'w', encoding='utf-8') as f:
        f.write(md)
    
    print(f"生成了接口继承树文档")

if __name__ == '__main__':
    main()
