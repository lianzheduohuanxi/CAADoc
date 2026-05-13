# -*- coding: utf-8 -*-
"""
修复 source_file 扩展名 - 将 .md 改为 .htm
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_source_file_ext(content):
    """修复source_file字段中的.md扩展名为.htm"""
    # 匹配 source_file: xxx.md 或 "source_file": "xxx.md"
    content = re.sub(r'(source_file["\s:]+)([^*"]+\.)(md["\s,]*)', r'\1\2htm\3', content)
    content = re.sub(r"('source_file'\\s*:\\s*')([^']+)(\\.)(md)(')", r"\1\2\3htm\5", content)
    return content

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_files = len(md_files)
    modified_count = 0
    
    print(f"Starting to fix source_file extensions in {total_files} files...")
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        
        # 检查是否有需要修复的扩展名
        if re.search(r'source_file["\s:]+[^"]+\.md', content):
            fixed = fix_source_file_ext(content)
            if fixed != content:
                md_file.write_text(fixed, encoding='utf-8')
                modified_count += 1
                print(f"  Fixed: {md_file.relative_to(root_dir)}")
    
    print(f"[OK] Source file extension fix completed!")
    print(f"   - Modified: {modified_count}/{total_files}")

if __name__ == '__main__':
    main()