#!/usr/bin/env python3
"""
CATIA CAA V5 HTML转Markdown转换器 V4
简化版本 - 只做基本的文本提取和清理
"""
import os
import re
import json
from pathlib import Path
from datetime import datetime
from html.parser import HTMLParser

class SimpleHTMLToMarkdown(HTMLParser):
    def __init__(self):
        super().__init__()
        self.result = []
        self.skip_depth = 0
        self.in_pre = False
        self.code_lines = []
        self.code_lang = ''
        self.last_was_block = False
        
    def handle_starttag(self, tag, attrs):
        attrs_dict = dict(attrs)
        
        if tag in ('script', 'style'):
            self.skip_depth += 1
            return
        
        if tag == 'pre':
            self.in_pre = True
            self.code_lines = []
            classes = attrs_dict.get('class', '')
            if 'language-vbscript' in classes:
                self.code_lang = 'vbscript'
            elif 'language-cpp' in classes or 'language-c' in classes:
                self.code_lang = 'cpp'
            else:
                self.code_lang = ''
            return
        
        if tag in ('h1', 'h2', 'h3', 'h4', 'h5', 'h6'):
            level = int(tag[1])
            self.result.append('\n' + '#' * level + ' ')
            self.last_was_block = True
            return
        
        if tag == 'p':
            self.result.append('\n\n')
            self.last_was_block = True
            return
        
        if tag == 'br':
            self.result.append('\n')
            return
        
        if tag == 'hr':
            self.result.append('\n\n---\n\n')
            return
        
        if tag == 'a':
            self.result.append('[')
            return
        
        if tag == 'img':
            src = attrs_dict.get('src', '')
            alt = attrs_dict.get('alt', '')
            if src:
                self.result.append(f'![{alt}]({src})')
            return
        
        if tag == 'table':
            # 跳过表格，直接处理内容
            return
        
        if tag == 'tr':
            self.result.append('\n|')
            return
        
        if tag in ('td', 'th'):
            self.result.append('|')
            return
        
        if tag == 'ul':
            self.result.append('\n')
            return
        
        if tag == 'ol':
            self.result.append('\n')
            return
        
        if tag == 'li':
            self.result.append('\n- ')
            return
        
        if tag == 'code':
            if not self.in_pre:
                self.result.append('`')
            return
        
        if tag == 'strong' or tag == 'b':
            self.result.append('**')
            return
        
        if tag == 'em' or tag == 'i':
            self.result.append('*')
            return
        
        if tag == 'blockquote':
            self.result.append('\n> ')
            return
    
    def handle_endtag(self, tag):
        if tag in ('script', 'style'):
            if self.skip_depth > 0:
                self.skip_depth -= 1
            return
        
        if tag == 'pre':
            if self.code_lines:
                code_text = '\n'.join(self.code_lines)
                # 清理HTML标签
                code_text = re.sub(r'<FONT[^>]*>', '', code_text)
                code_text = re.sub(r'</FONT>', '', code_text)
                code_text = code_text.strip()
                if code_text:
                    self.result.append(f'\n```{self.code_lang}\n{code_text}\n```\n')
            self.in_pre = False
            self.code_lines = []
            self.code_lang = ''
            return
        
        if tag == 'a':
            self.result.append(']')
            return
        
        if tag == 'code':
            if not self.in_pre:
                self.result.append('`')
            return
        
        if tag == 'strong' or tag == 'b':
            self.result.append('**')
            return
        
        if tag == 'em' or tag == 'i':
            self.result.append('*')
            return
        
        if tag == 'blockquote':
            self.result.append('\n')
            return
    
    def handle_data(self, data):
        if self.skip_depth > 0:
            return
        
        if self.in_pre:
            self.code_lines.append(data)
            return
        
        self.result.append(data)
    
    def get_markdown(self):
        text = ''.join(self.result)
        
        # 清理HTML实体
        text = text.replace('&lt;', '<').replace('&gt;', '>').replace('&amp;', '&')
        text = text.replace('&quot;', '"').replace('&nbsp;', ' ')
        text = text.replace('&#39;', "'").replace('&#34;', '"')
        
        # 清理多余的空行
        text = re.sub(r'\n{3,}', '\n\n', text)
        
        # 清理无意义的表格行
        lines = text.split('\n')
        result = []
        for line in lines:
            stripped = line.strip()
            # 跳过无意义的表格行
            if stripped == '|':
                continue
            if re.match(r'^(\|?\s*[-=|]+\s*)+$', stripped):
                # 保留表头分隔符
                if '|' in stripped and '-' in stripped:
                    continue
            result.append(line)
        
        text = '\n'.join(result)
        
        # 清理多余空格
        text = re.sub(r' +', ' ', text)
        
        return text.strip()


class CAAHTMLConverterV4:
    def __init__(self, base_dir):
        self.base_dir = Path(base_dir)
        self.output_base = self.base_dir / "CAAKnowledge"
        self.stats = {'processed': 0, 'failed': 0}

    def infer_category(self, module, title):
        """推断文档分类"""
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

    def extract_frontmatter(self, soup_text, filepath):
        """从HTML提取元数据"""
        title_match = re.search(r'<TITLE>([^<]+)</TITLE>', soup_text)
        title = title_match.group(1).strip() if title_match else "Untitled"
        
        parts = str(filepath).replace('\\', '/').split('/')
        module = parts[-2] if len(parts) >= 2 else "unknown"
        
        category = self.infer_category(module, title)
        tags = list(set(re.findall(r'\b(CATI\w+|CAA\w+)\b', soup_text)))[:20]
        
        return {
            'title': title,
            'category': category,
            'module': module,
            'tags': tags,
            'source_file': f"Doc/online/{module}/{Path(filepath).name}"
        }

    def convert(self, html_content):
        """转换HTML到Markdown"""
        # 移除脚本和样式
        html_content = re.sub(r'<script[^>]*>.*?</script>', '', html_content, flags=re.DOTALL | re.IGNORECASE)
        html_content = re.sub(r'<style[^>]*>.*?</style>', '', html_content, flags=re.DOTALL | re.IGNORECASE)
        
        # 提取body
        body_match = re.search(r'<body[^>]*>(.*?)</body>', html_content, re.DOTALL | re.IGNORECASE)
        if body_match:
            body = body_match.group(1)
        else:
            body = html_content
        
        # 转换
        parser = SimpleHTMLToMarkdown()
        parser.feed(body)
        md = parser.get_markdown()
        
        return md

    def process_file(self, filepath):
        """处理单个HTML文件"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()

            frontmatter = self.extract_frontmatter(content, str(filepath))
            markdown_content = self.convert(content)

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

            rel_path = Path(filepath).relative_to(self.base_dir / "Doc" / "online")
            module = frontmatter['module']
            output_path = self.output_base / "use-cases" / module.lower()
            output_path.mkdir(parents=True, exist_ok=True)
            output_file = output_path / f"{rel_path.stem}.md"

            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(result)

            self.stats['processed'] += 1
            return True

        except Exception as e:
            self.stats['failed'] += 1
            print(f"Failed: {filepath} - {e}")
            return False

    def run(self):
        """运行转换"""
        print("=" * 60)
        print("CATIA CAA V5 HTML转Markdown V4 (简化版)")
        print("=" * 60)

        docs_dir = self.base_dir / "Doc" / "online"
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

        for module_dir in module_dirs:
            module_path = docs_dir / module_dir
            if module_path.exists():
                print(f">>> Processing {module_dir}...")
                for htm_file in module_path.glob("*.htm"):
                    self.process_file(htm_file)

        print(f"\nProcessed: {self.stats['processed']}, Failed: {self.stats['failed']}")
        print("=" * 60)

if __name__ == "__main__":
    import sys
    base_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    converter = CAAHTMLConverterV4(base_dir)
    converter.run()
