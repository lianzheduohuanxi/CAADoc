# -*- coding: utf-8 -*-
"""
处理无效图片路径 - P1-5
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_image_paths():
    """修复图片路径"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    fixed_count = 0
    
    print("P1-5: Fixing Invalid Image Paths")
    print("=" * 50)
    
    # 图片路径映射
    image_mappings = {
        '../CAAScrBase/images/': './assets/images/',
        '../../doc/': '../',
    }
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 修复路径映射
        for old_path, new_path in image_mappings.items():
            content = content.replace(old_path, new_path)
        
        # 将.htm链接转换为.md
        content = re.sub(r'\.htm(["\)\]])', r'.md\1', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    # 创建assets/images目录作为占位符
    assets_dir = root_dir / 'assets' / 'images'
    assets_dir.mkdir(parents=True, exist_ok=True)
    
    readme = assets_dir / 'README.md'
    readme.write_text(
        "# Image Assets\n\n"
        "This directory contains image assets for the CAA documentation.\n\n"
        "## Placeholder\n\n"
        "Image files will be stored here after download from original sources.\n",
        encoding='utf-8'
    )
    
    print(f"[OK] Image path fix completed!")
    print(f"   - Fixed files: {fixed_count}")
    print(f"   - Assets directory: {assets_dir}")

if __name__ == '__main__':
    fix_image_paths()