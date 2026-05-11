#!/usr/bin/env python3
"""
CATIA CAA V5 HTML转Markdown - 简单可靠版本
使用正则表达式直接提取关键内容
"""
import re
import json
from pathlib import Path
from datetime import datetime

def simple_convert(html_content):
    """简单可靠的HTML转Markdown"""
    
    # 移除脚本和样式
    html_content = re.sub(r'<script[^>]*>.*?</script>', '', html_content, flags=re.DOTALL | re.IGNORECASE)
    html_content = re.sub(r'<style[^>]*>.*?</style>', '', html_content, flags=re.DOTALL | re.IGNORECASE)
    
    # 提取body
    body_match = re.search(r'<body[^>]*>(.*?)</body>', html_content, re.DOTALL | re.IGNORECASE)
    if body_match:
        content = body_match.group(1)
    else:
        content = html_content
    
    # 处理代码块 - 提取所有<pre>标签内的内容
    code_blocks = []
    for pre_match in re.finditer(r'<pre[^>]*>(.*?)</pre>', content, re.DOTALL | re.IGNORECASE):
        code_text = pre_match.group(1)
        # 清理HTML标签
        code_text = re.sub(r'<[^>]+>', '', code_text)
        code_text = code_text.strip()
        if code_text:
            code_blocks.append(code_text)
    
    # 移除代码表格部分，避免重复
    content = re.sub(r'<table[^>]*class="code"[^>]*>.*?</table>', '___CODE_BLOCKS___', content, flags=re.DOTALL | re.IGNORECASE)
    content = re.sub(r'<table[^>]*class="Code"[^>]*>.*?</table>', '___CODE_BLOCKS___', content, flags=re.DOTALL | re.IGNORECASE)
    
    # 移除其他表格
    content = re.sub(r'<table[^>]*>.*?</table>', '', content, flags=re.DOTALL | re.IGNORECASE)
    
    # 移除图标列 (<td width="7%">及其内容)
    content = re.sub(r'<td[^>]*width="7%"[^>]*>.*?</td>', '', content, flags=re.DOTALL | re.IGNORECASE)
    
    # 清理剩余HTML标签
    content = re.sub(r'<br[^>]*>', '\n', content, flags=re.IGNORECASE)
    content = re.sub(r'<hr[^>]*>', '\n\n---\n\n', content, flags=re.IGNORECASE)
    content = re.sub(r'<p[^>]*>', '\n\n', content, flags=re.IGNORECASE)
    content = re.sub(r'</p>', '', content, flags=re.IGNORECASE)
    content = re.sub(r'<h([1-6])[^>]*>', lambda m: '\n\n' + '#' * int(m.group(1)) + ' ', content, flags=re.IGNORECASE)
    content = re.sub(r'</h[1-6]>', '', content, flags=re.IGNORECASE)
    content = re.sub(r'<a[^>]*href="([^"]*)"[^>]*>([^<]*)</a>', r'[\2](\1)', content, flags=re.IGNORECASE)
    content = re.sub(r'<a[^>]*>([^<]*)</a>', r'\1', content, flags=re.IGNORECASE)
    content = re.sub(r'<img[^>]*src="([^"]*)"[^>]*alt="([^"]*)"[^>]*>', r'![\2](\1)', content, flags=re.IGNORECASE)
    content = re.sub(r'<img[^>]*alt="([^"]*)"[^>]*src="([^"]*)"[^>]*>', r'![\1](\2)', content, flags=re.IGNORECASE)
    content = re.sub(r'<img[^>]*src="([^"]*)"[^>]*>', r'![](\1)', content, flags=re.IGNORECASE)
    content = re.sub(r'<li[^>]*>', '\n- ', content, flags=re.IGNORECASE)
    content = re.sub(r'</li>', '', content, flags=re.IGNORECASE)
    content = re.sub(r'<strong[^>]*>', '**', content, flags=re.IGNORECASE)
    content = re.sub(r'</strong>', '**', content, flags=re.IGNORECASE)
    content = re.sub(r'<b[^>]*>', '**', content, flags=re.IGNORECASE)
    content = re.sub(r'</b>', '**', content, flags=re.IGNORECASE)
    content = re.sub(r'<i[^>]*>', '*', content, flags=re.IGNORECASE)
    content = re.sub(r'</i>', '*', content, flags=re.IGNORECASE)
    content = re.sub(r'<em[^>]*>', '*', content, flags=re.IGNORECASE)
    content = re.sub(r'</em>', '*', content, flags=re.IGNORECASE)
    content = re.sub(r'<code[^>]*>', '`', content, flags=re.IGNORECASE)
    content = re.sub(r'</code>', '`', content, flags=re.IGNORECASE)
    content = re.sub(r'<tr[^>]*>', '', content, flags=re.IGNORECASE)
    content = re.sub(r'</tr>', '', content, flags=re.IGNORECASE)
    content = re.sub(r'<td[^>]*>', '|', content, flags=re.IGNORECASE)
    content = re.sub(r'</td>', '', content, flags=re.IGNORECASE)
    content = re.sub(r'<th[^>]*>', '|', content, flags=re.IGNORECASE)
    content = re.sub(r'</th>', '', content, flags=re.IGNORECASE)
    
    # 移除所有剩余HTML标签
    content = re.sub(r'<[^>]+>', '', content)
    
    # 替换代码块标记
    if code_blocks:
        code_md = '\n\n'.join([f'```vbscript\n{cb}\n```' for cb in code_blocks])
        content = content.replace('___CODE_BLOCKS___', '\n\n' + code_md + '\n\n')
    else:
        content = content.replace('___CODE_BLOCKS___', '')
    
    # 解码HTML实体
    content = content.replace('&lt;', '<').replace('&gt;', '>').replace('&amp;', '&')
    content = content.replace('&quot;', '"').replace('&nbsp;', ' ')
    content = content.replace('&#39;', "'").replace('&#34;', '"')
    content = content.replace('&#9;', '\t')
    
    # 清理多余空行
    content = re.sub(r'\n{3,}', '\n\n', content)
    
    return content.strip()


def infer_category(module, title):
    module_lower = module.lower()
    title_lower = title.lower()
    
    if 'usecases' in module_lower or 'cases' in module_lower:
        if 'how to' in title_lower or 'tutorial' in title_lower:
            return 'tutorial'
        return 'use-case'
    if 'techarticles' in module_lower:
        return 'tech-article'
    if 'quickrefs' in module_lower:
        return 'quick-reference'
    if 'apichange' in module_lower:
        return 'api-changes'
    return 'use-case'


def extract_frontmatter(html_content, filepath):
    title_match = re.search(r'<TITLE>([^<]+)</TITLE>', html_content)
    title = title_match.group(1).strip() if title_match else "Untitled"
    
    parts = str(filepath).replace('\\', '/').split('/')
    module = parts[-2] if len(parts) >= 2 else "unknown"
    
    category = infer_category(module, title)
    tags = list(set(re.findall(r'\b(CATI\w+|CAA\w+)\b', html_content)))[:20]
    
    return {
        'title': title,
        'category': category,
        'module': module,
        'tags': tags,
        'source_file': f"Doc/online/{module}/{Path(filepath).name}"
    }


def process_file(filepath, base_dir, output_base):
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        
        frontmatter = extract_frontmatter(content, str(filepath))
        markdown_content = simple_convert(content)
        
        frontmatter_text = f'''---
title: "{frontmatter['title']}"
category: "{frontmatter['category']}"
module: "{frontmatter['module']}"
tags: {json.dumps(frontmatter['tags'], ensure_ascii=False)}
source_file: "{frontmatter['source_file']}"
converted: "{datetime.now().isoformat()}"
---

'''
        
        result = frontmatter_text + markdown_content
        
        rel_path = Path(filepath).relative_to(base_dir / "Doc" / "online")
        module = frontmatter['module']
        output_path = output_base / "use-cases" / module.lower()
        output_path.mkdir(parents=True, exist_ok=True)
        output_file = output_path / f"{rel_path.stem}.md"
        
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(result)
        
        return True
    
    except Exception as e:
        print(f"Failed: {filepath} - {e}")
        return False


def main():
    base_dir = Path('.')
    output_base = base_dir / "CAAKnowledge"
    
    print("=" * 60)
    print("CATIA CAA V5 HTML转Markdown (简单版)")
    print("=" * 60)
    
    docs_dir = base_dir / "Doc" / "online"
    if not docs_dir.exists():
        print(f"Error: {docs_dir} not found")
        return
    
    module_dirs = [
        "CAAScdAniUseCases", "CAAScdPstUseCases",
        "CAAScdStrUseCases", "CAAScdSchUseCases",
        "CAASchUseCases", "CAAScdArrUseCases",
        "CAAScdInfUseCases", "CAAScdKniUseCases",
        "CAAScdMmrUseCases", "CAAScdPriUseCases",
        "CAAScdDriUseCases", "CAASkiUseCases",
        "CAASmaUseCases", "CAASmiUseCases",
        "CAADlgUseCases", "CAAVseUseCases",
    ]
    
    processed = 0
    failed = 0
    
    for module_dir in module_dirs:
        module_path = docs_dir / module_dir
        if module_path.exists():
            print(f">>> Processing {module_dir}...")
            for htm_file in module_path.glob("*.htm"):
                if process_file(htm_file, base_dir, output_base):
                    processed += 1
                else:
                    failed += 1
    
    print(f"\nProcessed: {processed}, Failed: {failed}")
    print("=" * 60)


if __name__ == "__main__":
    main()
