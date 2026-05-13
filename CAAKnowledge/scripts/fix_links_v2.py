# -*- coding: utf-8 -*-
"""
全面修复失效链接
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_general_links():
    """修复通用链接问题"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    fixed_count = 0
    
    print("Fixing general link issues...")
    
    # 占位符和示例链接
    placeholders = [
        '{base_name}.md',
        '../{uc.path}',
        '../use-cases/xxx.md',
        '../use-cases/yyy.md',
        'from.md',
    ]
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        for placeholder in placeholders:
            content = re.sub(rf'\[([^\]]+)\]\([^)]*{re.escape(placeholder)}[^)]*\)', '', content)
        
        # 修复反斜杠为正斜杠
        content = content.replace('\\', '/')
        
        # 清理空链接
        content = re.sub(r'\]\(\s*\)', '](#)', content)
        content = re.sub(r'\]\(\s*#\s*\)', '](#)', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} files")
    return fixed_count

def fix_interface_references():
    """修复接口文档中的继承链接"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    fixed_count = 0
    
    print("Fixing interface inheritance links...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 提取接口名
        interface_name = md_file.stem
        
        # 查找基类引用模式 **[CATIXxx]** 或 *CATIXxx*
        base_patterns = [
            (r'\*\*((?:CATI|CAA)[A-Z][a-zA-Z0-9]+)\*\*', f']({interface_name}.md)'),
            (r'\*((?:CATI|CAA)[A-Z][a-zA-Z0-9]+)\*', f']({interface_name}.md)'),
        ]
        
        # 删除无用的继承信息引用行
        content = re.sub(r'\*\*接口继承\*\*.*?(?=\n|$)', '', content)
        content = re.sub(r'-\s+\*\*.*?from\.md.*', '', content)
        
        # 清理空行
        content = re.sub(r'\n{3,}', '\n\n', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} interface files")
    return fixed_count

def fix_cross_reference_section():
    """修复交叉引用部分"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    fixed_count = 0
    
    print("Fixing cross-reference sections...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 清理 Related Use Cases 部分的无用链接
        if '## Related Use Cases' in content:
            # 移除只引用接口而没有实际用例的情况
            lines = content.split('\n')
            new_lines = []
            skip_next = False
            
            for i, line in enumerate(lines):
                if '## Related Use Cases' in line:
                    new_lines.append(line)
                    skip_next = True
                elif skip_next and line.strip().startswith('- **接口继承**'):
                    continue  # 跳过无用的接口继承行
                elif skip_next and '*from.md' in line:
                    continue  # 跳过空的from.md链接
                else:
                    new_lines.append(line)
                    skip_next = False
            
            content = '\n'.join(new_lines)
        
        # 清理空链接
        content = re.sub(r'\]\([^)]*\.md\)\s*\n\s*\*from\.md', '', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} files")
    return fixed_count

def main():
    print("=" * 60)
    print("Comprehensive Link Fix")
    print("=" * 60)
    
    fix_general_links()
    fix_interface_references()
    fix_cross_reference_section()
    
    print("\n[OK] All links fixed!")

if __name__ == '__main__':
    main()