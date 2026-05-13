# -*- coding: utf-8 -*-
"""
修复HTML表格残留 |---|--- 分隔符
"""

import re
import sys
from pathlib import Path

# 设置stdout编码为utf-8
sys.stdout.reconfigure(encoding='utf-8')

def fix_tables(md_file):
    """修复Markdown文件中的HTML表格残留"""
    content = md_file.read_text(encoding='utf-8')
    
    # 1. 删除孤立的表格分隔行
    content = re.sub(r'\n\|---\s*---+\|\n', '\n', content)
    
    # 2. 删除行首的表格分隔行
    content = re.sub(r'^\|---\s*---+\|\n', '', content, flags=re.MULTILINE)
    
    # 3. 清理图标列 |![...]| 模式
    content = re.sub(r'\n\|!\[[^\]]*\]\([^)]+\)\n', '\n', content)
    
    # 4. 清理纯分隔符行
    content = re.sub(r'\n\|[-:]+\|[-:\s|]*\|\n', '\n', content)
    
    # 5. 合并多余的空行
    content = re.sub(r'\n{3,}', '\n\n', content)
    
    return content

def main():
    # 明确指定根目录
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_files = len(md_files)
    modified_count = 0
    total_fixes = 0
    
    print(f"开始修复 {total_files} 个Markdown文件...")
    
    for md_file in md_files:
        original = md_file.read_text(encoding='utf-8')
        fixed = fix_tables(md_file)
        
        if fixed != original:
            md_file.write_text(fixed, encoding='utf-8')
            fixes = original.count('|---|') + original.count('|---|---')
            total_fixes += fixes
            modified_count += 1
            print(f"  Fixed: {md_file.relative_to(root_dir)}")
    
    print(f"[OK] Fix completed!")
    print(f"   - Modified: {modified_count}/{total_files}")
    print(f"   - Total fixes: {total_fixes}")

if __name__ == '__main__':
    main()
