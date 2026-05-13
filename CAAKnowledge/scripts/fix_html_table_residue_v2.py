# -*- coding: utf-8 -*-
"""
进一步清理HTML表格残留
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_html_table_residue(md_file):
    """修复HTML表格残留"""
    content = md_file.read_text(encoding='utf-8')
    original = content
    
    # 更全面的表格清理
    # 1. 清理 |---|---| 类型
    content = re.sub(r'\n\|[-:]+\|[-:\s|]*\|\n', '\n', content)
    
    # 2. 清理行首的表格分隔行
    content = re.sub(r'^\|[-:]+\|[-:\s|]*\|\n', '', content, flags=re.MULTILINE)
    
    # 3. 清理 |---| 单独一行
    content = re.sub(r'\n\|[-]+\s*\|[-:\s]*\|\n', '\n', content)
    content = re.sub(r'^\|[-]+\s*\|[-:\s]*\|\n', '', content, flags=re.MULTILINE)
    
    # 4. 清理重复空行
    content = re.sub(r'\n{3,}', '\n\n', content)
    
    if content != original:
        md_file.write_text(content, encoding='utf-8')
        return True
    return False

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_files = len(md_files)
    fixed_count = 0
    
    print(f"Fixing remaining HTML table residue in {total_files} files...")
    
    for md_file in md_files:
        if fix_html_table_residue(md_file):
            fixed_count += 1
    
    print(f"[OK] Fixed {fixed_count}/{total_files} files")

if __name__ == '__main__':
    main()