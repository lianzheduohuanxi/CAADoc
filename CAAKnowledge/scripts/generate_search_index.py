# -*- coding: utf-8 -*-
"""
生成全文搜索索引 - P2-1
"""

import re
import sys
import json
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def extract_keywords(content):
    """提取关键词"""
    # 提取驼峰命名
    camel_case = re.findall(r'\b[A-Z][a-z]+(?:[A-Z][a-z]+)+\b', content)
    
    # 提取下划线命名
    snake_case = re.findall(r'\b[a-z]+_[a-z]+\b', content)
    
    # 提取常见关键词
    common_keywords = ['interface', 'method', 'parameter', 'return', 'CATIA', 'CAA']
    
    return list(set(camel_case + snake_case + common_keywords))[:20]

def extract_summary(content, max_length=300):
    """提取摘要"""
    # 移除frontmatter
    content = re.sub(r'^---.*?---\n', '', content, flags=re.DOTALL)
    
    # 移除代码块
    content = re.sub(r'```.*?```', '', content, flags=re.DOTALL)
    
    # 移除标题
    content = re.sub(r'^#+\s+', '', content, flags=re.MULTILINE)
    
    # 提取前几段
    paragraphs = content.split('\n\n')
    summary = paragraphs[0] if paragraphs else ''
    
    # 清理并截断
    summary = re.sub(r'\s+', ' ', summary).strip()
    if len(summary) > max_length:
        summary = summary[:max_length] + '...'
    
    return summary

def generate_search_index():
    """生成搜索索引"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    search_index = []
    
    print(f"P2-1: Generating Search Index")
    print("=" * 50)
    print(f"Processing {len(md_files)} files...")
    
    for md_file in md_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            
            # 提取标题
            title_match = re.search(r'^#\s+(.+)$', content, re.MULTILINE)
            title = title_match.group(1) if title_match else md_file.stem
            
            # 提取路径
            path = str(md_file.relative_to(root_dir))
            
            # 推断类型
            if 'api-reference' in path:
                doc_type = 'interface'
            elif 'quick-ref' in path:
                doc_type = 'quick-ref'
            elif 'use-case' in path:
                doc_type = 'use-case'
            elif 'tech-article' in path:
                doc_type = 'tech-article'
            else:
                doc_type = 'other'
            
            # 提取摘要和关键词
            summary = extract_summary(content)
            keywords = extract_keywords(content)
            
            search_index.append({
                'title': title,
                'path': path,
                'summary': summary,
                'keywords': keywords,
                'type': doc_type,
            })
        except Exception as e:
            print(f"  Warning: Error processing {md_file}: {e}")
    
    # 保存索引
    output_file = root_dir / 'data' / 'search-index.json'
    output_file.parent.mkdir(parents=True, exist_ok=True)
    
    index_data = {
        'total_docs': len(search_index),
        'index_fields': ['title', 'summary', 'keywords', 'content'],
        'generated_at': '2026-05-12',
        'documents': search_index
    }
    
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(index_data, f, indent=2, ensure_ascii=False)
    
    print(f"\n[OK] Search index generated!")
    print(f"   - Total documents: {len(search_index)}")
    print(f"   - Output: {output_file}")
    
    return search_index

if __name__ == '__main__':
    generate_search_index()