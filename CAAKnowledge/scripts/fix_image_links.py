"""
创建占位符图片并修复图片链接
"""
import os
import re
from pathlib import Path

# 创建占位符SVG图片
SVG_PLACEHOLDER = '''<svg xmlns="http://www.w3.org/2000/svg" width="400" height="300" viewBox="0 0 400 300">
  <rect fill="#f0f0f0" width="400" height="300"/>
  <text x="50%" y="50%" text-anchor="middle" fill="#999" font-family="Arial" font-size="14">
    {filename}
  </text>
  <text x="50%" y="60%" text-anchor="middle" fill="#ccc" font-family="Arial" font-size="10">
    Image Placeholder
  </text>
</svg>'''

def create_placeholder_images():
    """创建assets/images目录和占位符图片"""
    assets_dir = Path('assets/images')
    assets_dir.mkdir(parents=True, exist_ok=True)
    
    # 创建README说明文件
    readme = '''# 图片占位符目录

此目录包含知识库中引用的图片占位符。

由于原始图片未包含在知识库中，这里提供占位符SVG图片用于文档渲染测试。

## 占位符图片列表

如需完整图片，请参考CATIA CAA官方示例代码。
'''
    (assets_dir / 'README.md').write_text(readme, encoding='utf-8')
    
    # 创建通用占位符
    common_images = {
        'placeholder.gif': SVG_PLACEHOLDER.format(filename='[Image Placeholder]'),
        'warning.gif': SVG_PLACEHOLDER.format(filename='[Warning Icon]'),
    }
    
    for filename, content in common_images.items():
        (assets_dir / filename).write_text(content, encoding='utf-8')
    
    print(f'Created {assets_dir} with placeholder images')
    return assets_dir

def fix_image_links():
    """修复文档中的图片链接"""
    fixed_count = 0
    
    for md_file in list(Path('.').rglob('*.md')):
        try:
            content = md_file.read_text(encoding='utf-8', errors='ignore')
        except:
            continue
        
        original = content
        
        # 修复 ./assets/images/ 链接
        content = re.sub(
            r'!\[\]\(./assets/images/([^)]+)\)',
            r'![image](../../assets/images/\1)',
            content
        )
        
        # 修复 images/ 相对链接为正确路径
        if 'use-cases/' in str(md_file):
            content = re.sub(
                r'!\[([^\]]*)\]\(images/([^)]+)\)',
                r'![image](./images/\2)',
                content
            )
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f'Fixed image links in {fixed_count} files')
    return fixed_count

def create_image_index():
    """创建图片索引"""
    image_list = {}
    
    for md_file in list(Path('.').rglob('*.md')):
        try:
            content = md_file.read_text(encoding='utf-8', errors='ignore')
        except:
            continue
        
        img_pattern = re.compile(r'!\[([^\]]*)\]\(([^)]+)\)')
        for match in img_pattern.finditer(content):
            alt, url = match.groups()
            if url not in image_list:
                image_list[url] = []
            image_list[url].append(str(md_file.relative_to('.')))
    
    # 保存索引
    import json
    index_file = Path('data/image-index.json')
    with open(index_file, 'w', encoding='utf-8') as f:
        json.dump({
            'total': len(image_list),
            'images': image_list,
            'generated_at': '2026-05-12'
        }, f, indent=2, ensure_ascii=False)
    
    print(f'Created image index with {len(image_list)} images')
    return len(image_list)

if __name__ == '__main__':
    print('=== Fixing Image Links ===\n')
    
    # 1. 创建占位符目录
    create_placeholder_images()
    
    # 2. 修复图片链接
    fix_image_links()
    
    # 3. 创建图片索引
    create_image_index()
    
    print('\nDone!')
