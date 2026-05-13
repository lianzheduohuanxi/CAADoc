# -*- coding: utf-8 -*-
"""
修复相对路径引用
- 转换 .htm 链接为 .md
- 重映射失效的图片路径
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

# 路径映射配置
PATH_MAPPINGS = {
    '../CAAScrBase/images/': './assets/images/',
    '../CAAScdAniTechArticles/': '../use-cases/caascdaniusecases/',
    '../../doc/': '../',
}

# 需要修复的文件类型
MARKDOWN_EXTS = {'.md', '.md.txt'}

def fix_paths(content, md_path):
    """修复文件中的路径引用"""
    original = content
    
    # 1. 修复路径映射
    for old_path, new_path in PATH_MAPPINGS.items():
        content = content.replace(old_path, new_path)
    
    # 2. 将 .htm 链接转换为 .md
    content = re.sub(r'\.htm(["\)\]])', r'.md\1', content)
    content = re.sub(r'\.HTM(["\)\]])', r'.md\1', content)
    
    # 3. 清理相对路径中的 ../
    # 如果文档在 api-reference 目录,调整链接
    if 'api-reference' in str(md_path):
        # 修复指向 use-cases 的链接
        content = re.sub(r'\]\(\.\./(?!(use-cases|quick-refs))', '](', content)
    
    return content

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_files = len(md_files)
    modified_count = 0
    total_fixes = 0
    
    print(f"Starting to fix paths in {total_files} Markdown files...")
    
    for md_file in md_files:
        original = md_file.read_text(encoding='utf-8')
        fixed = fix_paths(original, md_file)
        
        if fixed != original:
            # 统计修复数量
            htm_count = len(re.findall(r'\.htm["\)\]]', original))
            md_file.write_text(fixed, encoding='utf-8')
            total_fixes += htm_count
            modified_count += 1
            print(f"  Fixed: {md_file.relative_to(root_dir)}")
    
    print(f"[OK] Path fix completed!")
    print(f"   - Modified: {modified_count}/{total_files}")
    print(f"   - Total path fixes: {total_fixes}")

if __name__ == '__main__':
    main()