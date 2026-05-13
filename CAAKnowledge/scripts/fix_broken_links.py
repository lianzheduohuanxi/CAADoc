# -*- coding: utf-8 -*-
"""
修复失效的路径链接
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_broken_links():
    """修复失效链接"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    fixed_count = 0
    link_fixes = {
        'troubleshooting/compiler-errors.md': 'troubleshooting.md',
        'troubleshooting/linker-errors.md': 'troubleshooting.md',
        'troubleshooting/runtime-errors.md': 'troubleshooting.md',
        '../data/knowledge_base.json': './data/knowledge_base_consolidated.json',
        '../api-reference/interfaces/from.md': '',  # 删除无效链接
        '{base_name}.md': '',  # 删除占位符
        '../{uc.path}': '',  # 删除占位符
        '../use-cases/xxx.md': '',  # 删除占位符
        '../use-cases/yyy.md': '',  # 删除占位符
    }
    
    print("Fixing broken links...")
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 修复链接
        for old_link, new_link in link_fixes.items():
            content = content.replace(f'({old_link})', f'({new_link})')
            content = content.replace(f'({old_link}\n', f'({new_link})\n')
        
        # 删除无效的../from.md引用
        content = re.sub(r'\[([^\]]+)\]\([^)]*/from\.md\)', '', content)
        
        # 删除空链接
        content = re.sub(r'\(\s*\)', '(#)', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"Fixed {fixed_count} files")

def fix_cross_reference_links():
    """修复交叉引用中的失效链接"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    fixed_count = 0
    
    print("\nFixing cross-reference links...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 检查Related Use Cases部分
        if '## Related Use Cases' in content:
            # 移除失效的接口引用链接
            content = re.sub(r'\*\*接口继承\*\*.*?(?=\n\n|\n##|$)', '', content)
            
            # 移除空的from.md链接
            content = re.sub(r'\*\*from\.md\*\*.*?(?=\n\n|\n##|$)', '', content)
            
            # 清理空行
            content = re.sub(r'\n{3,}', '\n\n', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"Fixed {fixed_count} interface files")

def normalize_interface_paths():
    """标准化接口文档中的路径"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    fixed_count = 0
    
    print("\nNormalizing interface document paths...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 标准化 ../api-reference/interfaces/ 为 ./ 或相对路径
        content = content.replace(
            '../api-reference/interfaces/',
            './'
        )
        
        # 修复相对路径
        content = re.sub(r'\]\(\./', '](', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"Normalized {fixed_count} interface files")

def main():
    print("=" * 60)
    print("Fixing Broken Links")
    print("=" * 60)
    
    fix_broken_links()
    fix_cross_reference_links()
    normalize_interface_paths()
    
    print("\n[OK] All broken links fixed!")

if __name__ == '__main__':
    main()