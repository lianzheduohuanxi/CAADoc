#!/usr/bin/env python3
"""
CATIA CAA V5 HTML转Markdown转换器 V3
使用标准库html.parser，无外部依赖
"""
import os
import re
import json
from pathlib import Path
from datetime import datetime
from html.parser import HTMLParser

class MarkdownConverter(HTMLParser):
    def __init__(self):
        super().__init__()
        self.result = []
        self.in_table = False
        self.in_code = False
        self.in_pre = False
        self.table_rows = []
        self.current_row = []
        self.skip_next_colspan = 0
        
    def handle_starttag(self, tag, attrs):
        attrs_dict = dict(attrs)
        
        if tag == 'table':
            self.in_table = True
            self.table_rows = []
            return
        
        if tag == 'tr':
            self.current_row = []
            return
        
        if tag in ('td', 'th'):
            # 检查是否是图标列
            width = attrs_dict.get('width', '')
            if '7%' in str(width):
                self.skip_next_colspan = int(attrs_dict.get('colspan', 1))
                return
            
            cols = int(attrs_dict.get('colspan', 1))
            self.current_row.append(('cell', cols))
            return
        
        if tag == 'pre':
            self.in_pre = True
            self.code_lines = []
            return
        
        if tag == 'code':
            if self.in_pre:
                # 获取语言
                classes = attrs_dict.get('class', '')
                if 'language-vbscript' in classes:
                    self.code_lang = 'vbscript'
                elif 'language-cpp' in classes or 'language-c' in classes:
                    self.code_lang = 'cpp'
                else:
                    self.code_lang = ''
            return
    
    def handle_endtag(self, tag):
        if tag == 'table':
            self.in_table = False
            self._flush_table()
            return
        
        if tag == 'tr':
            if self.current_row:
                self.table_rows.append(self.current_row)
            self.current_row = []
            return
        
        if tag in ('td', 'th'):
            if self.skip_next_colspan > 0:
                self.skip_next_colspan -= 1
            return
        
        if tag == 'pre':
            self.in_pre = False
            self._flush_code()
            return
    
    def handle_data(self, data):
        data = data.strip()
        if not data:
            return
        
        if self.in_table:
            if self.current_row and not self.skip_next_colspan:
                last_item = self.current_row[-1]
                if isinstance(last_item, tuple):
                    if len(last_item) >= 3:
                        # Already has data, append
                        self.current_row[-1] = (last_item[0], last_item[1], last_item[2] + ' ' + data)
                    elif len(last_item) >= 2:
                        self.current_row[-1] = (last_item[0], last_item[1], data)
                else:
                    self.current_row[-1] = ('cell', 1, data)
            return
        
        if self.in_pre:
            self.code_lines.append(data)
            return
        
        self.result.append(data)
    
    def _flush_table(self):
        if not self.table_rows:
            return
        
        # 第一行作为表头
        headers = []
        for item in self.table_rows[0]:
            if len(item) >= 3:
                headers.append(item[2])
            elif len(item) >= 2:
                headers.append('')
        
        if not headers:
            return
        
        # 添加表头
        self.result.append('\n|' + '|'.join(headers) + '|\n')
        self.result.append('|' + '|'.join(['---'] * len(headers)) + '|\n')
        
        # 添加数据行
        for row in self.table_rows[1:]:
            cells = []
            for item in row:
                if len(item) >= 3:
                    cells.append(item[2].replace('|', '\\|'))
                else:
                    cells.append('')
            while len(cells) < len(headers):
                cells.append('')
            self.result.append('|' + '|'.join(cells[:len(headers)]) + '|\n')
        
        self.table_rows = []
    
    def _flush_code(self):
        if self.code_lines:
            code_text = '\n'.join(self.code_lines)
            # 清理HTML标签
            code_text = re.sub(r'<FONT[^>]*>', '', code_text)
            code_text = re.sub(r'</FONT>', '', code_text)
            code_text = code_text.replace('&lt;', '<').replace('&gt;', '>')
            code_text = code_text.strip()
            
            lang = getattr(self, 'code_lang', '')
            self.result.append(f'\n```{lang}\n{code_text}\n```\n')
            self.code_lines = []
            self.code_lang = ''
    
    def get_markdown(self):
        # 处理未关闭的标签
        if self.in_pre:
            self._flush_code()
        if self.in_table:
            self._flush_table()
        
        # 清理多余空行
        text = ' '.join(self.result)
        text = re.sub(r' +', ' ', text)
        text = re.sub(r'\n{3,}', '\n\n', text)
        return text.strip()


class CAAHTMLConverterV3:
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
        # 提取标题
        title_match = re.search(r'<TITLE>([^<]+)</TITLE>', soup_text)
        title = title_match.group(1).strip() if title_match else "Untitled"
        
        # 从路径提取模块
        parts = str(filepath).replace('\\', '/').split('/')
        module = parts[-2] if len(parts) >= 2 else "unknown"
        
        # 推断category
        category = self.infer_category(module, title)
        
        # 提取标签
        tags = list(set(re.findall(r'\b(CATI\w+|CAA\w+)\b', soup_text)))[:20]
        
        return {
            'title': title,
            'category': category,
            'module': module,
            'tags': tags,
            'source_file': f"Doc/online/{module}/{Path(filepath).name}"
        }

    def simple_convert(self, html_content):
        """简化的HTML转Markdown转换"""
        # 移除脚本和样式
        html_content = re.sub(r'<script[^>]*>.*?</script>', '', html_content, flags=re.DOTALL | re.IGNORECASE)
        html_content = re.sub(r'<style[^>]*>.*?</style>', '', html_content, flags=re.DOTALL | re.IGNORECASE)
        html_content = re.sub(r'<noscript[^>]*>.*?</noscript>', '', html_content, flags=re.DOTALL | re.IGNORECASE)
        
        # 提取body内容
        body_match = re.search(r'<body[^>]*>(.*?)</body>', html_content, re.DOTALL | re.IGNORECASE)
        if body_match:
            body = body_match.group(1)
        else:
            body = html_content
        
        # 使用HTMLParser
        parser = MarkdownConverter()
        parser.feed(body)
        md = parser.get_markdown()
        
        # 额外的清理
        md = self.clean_html_elements(md)
        
        return md

    def clean_html_elements(self, text):
        """清理剩余的HTML元素"""
        # 移除所有HTML标签
        text = re.sub(r'<[^>]+>', '', text)
        
        # 解码HTML实体
        text = text.replace('&lt;', '<').replace('&gt;', '>').replace('&amp;', '&')
        text = text.replace('&quot;', '"').replace('&nbsp;', ' ')
        text = text.replace('&#39;', "'").replace('&copy;', '(c)')
        
        # 清理多余的空行
        text = re.sub(r'\n{3,}', '\n\n', text)
        
        return text.strip()

    def process_file(self, filepath):
        """处理单个HTML文件"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()

            frontmatter = self.extract_frontmatter(content, str(filepath))
            markdown_content = self.simple_convert(content)

            # 生成frontmatter
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

            # 输出路径
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
        print("CATIA CAA V5 HTML转Markdown V3 (重新生成)")
        print("=" * 60)

        docs_dir = self.base_dir / "Doc" / "online"
        if not docs_dir.exists():
            print(f"Error: {docs_dir} not found")
            return

        # 扫描主要模块
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

        total_files = 0
        for module_dir in module_dirs:
            module_path = docs_dir / module_dir
            if module_path.exists():
                files = list(module_path.glob("*.htm"))
                total_files += len(files)
                print(f">>> {module_dir}: {len(files)} files")

        print(f"\nTotal: {total_files} files to process")
        
        for module_dir in module_dirs:
            module_path = docs_dir / module_dir
            if module_path.exists():
                print(f"Processing {module_dir}...")
                for htm_file in module_path.glob("*.htm"):
                    self.process_file(htm_file)

        print(f"\nProcessed: {self.stats['processed']}, Failed: {self.stats['failed']}")
        print("=" * 60)

if __name__ == "__main__":
    import sys
    base_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    converter = CAAHTMLConverterV3(base_dir)
    converter.run()
