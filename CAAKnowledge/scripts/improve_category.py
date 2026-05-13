# -*- coding: utf-8 -*-
"""
改善Category分类准确性 - P1-4
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

# 分类规则
CATEGORY_KEYWORDS = {
    'use-case': ['use case', '用例', 'how to', 'sample', '示例', '案例'],
    'concept': ['overview', 'introduction', '概述', '介绍', 'what is'],
    'tutorial': ['getting started', 'tutorial', '教程', '入门', 'guide'],
    'api-reference': ['interface', 'api', '方法', 'method', '参数', 'parameter'],
    'troubleshooting': ['troubleshooting', 'faq', 'error', '问题', '故障'],
    'tech-article': ['technical article', 'whitepaper', '技术文章', '深入'],
}

def infer_category_from_title(title):
    """从标题推断分类"""
    title_lower = title.lower()
    
    for category, keywords in CATEGORY_KEYWORDS.items():
        for kw in keywords:
            if kw in title_lower:
                return category
    
    return 'use-case'  # 默认分类

def infer_category_from_path(path):
    """从路径推断分类"""
    path_str = str(path).lower()
    
    if 'tech-article' in path_str or 'techarticle' in path_str:
        return 'tech-article'
    if 'quick-ref' in path_str:
        return 'quick-ref'
    if 'api-reference' in path_str:
        return 'api-reference'
    if 'use-case' in path_str:
        return 'use-case'
    
    return None

def improve_category(doc_path):
    """改善文档分类"""
    content = doc_path.read_text(encoding='utf-8')
    
    # 提取标题
    title_match = re.search(r'^#\s+(.+)$', content, re.MULTILINE)
    if not title_match:
        return None
    
    title = title_match.group(1)
    
    # 从路径推断
    path_category = infer_category_from_path(doc_path)
    
    # 从标题推断
    title_category = infer_category_from_title(title)
    
    # 优先使用路径分类
    category = path_category or title_category
    
    # 更新frontmatter
    if 'category:' in content.lower():
        # 更新现有category
        content = re.sub(
            r'(category:\s*)(\S+)',
            rf'\1{category}',
            content,
            flags=re.IGNORECASE
        )
    else:
        # 添加category到frontmatter
        if '---' in content:
            content = re.sub(
                r'^---\n',
                f'---\ncategory: {category}\n',
                content,
                flags=re.MULTILINE
            )
    
    return category, content

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_files = len(md_files)
    improved_count = 0
    category_stats = {}
    
    print(f"P1-4: Improving Category Classification")
    print("=" * 50)
    print(f"Processing {total_files} files...")
    
    for md_file in md_files:
        result = improve_category(md_file)
        
        if result:
            category, content = result
            md_file.write_text(content, encoding='utf-8')
            improved_count += 1
            
            category_stats[category] = category_stats.get(category, 0) + 1
    
    print(f"\n[OK] Category improvement completed!")
    print(f"   - Improved: {improved_count}/{total_files}")
    print(f"\nCategory distribution:")
    for cat, count in sorted(category_stats.items()):
        print(f"   - {cat}: {count}")

if __name__ == '__main__':
    main()