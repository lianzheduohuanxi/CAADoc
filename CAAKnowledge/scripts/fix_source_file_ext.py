#!/usr/bin/env python3
"""
CATIA CAA V5 知识库修复脚本 - 修复 source_file 扩展名
将错误的 .md 扩展名改回 .htm
"""
import re
from pathlib import Path

def fix_source_file_ext():
    """修复 source_file 扩展名"""
    use_case_dir = Path('CAAKnowledge/use-cases')
    if not use_case_dir.exists():
        print(f"目录不存在: {use_case_dir}")
        return 0
    
    fixed = 0
    for md_file in use_case_dir.rglob('*.md'):
        try:
            with open(md_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            # 检查是否有错误的 .md 扩展名
            if 'source_file:' in content:
                new_content = re.sub(
                    r'source_file:\s*"([^"]*)\.md"',
                    lambda m: f'source_file: "{m.group(1)}.htm"',
                    content
                )
                
                if new_content != content:
                    with open(md_file, 'w', encoding='utf-8') as f:
                        f.write(new_content)
                    fixed += 1
                    
        except Exception as e:
            print(f"Error processing {md_file}: {e}")
    
    print(f"修复了 {fixed} 个文件的 source_file 扩展名")
    return fixed

def main():
    print("=" * 60)
    print("修复 source_file 扩展名")
    print("=" * 60)
    fix_source_file_ext()
    print("=" * 60)

if __name__ == '__main__':
    main()
