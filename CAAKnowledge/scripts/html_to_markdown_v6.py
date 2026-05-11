#!/usr/bin/env python3
"""
CATIA CAA V5 HTML转Markdown转换器 V6
正确处理CAA文档的特殊HTML结构：
- 布局表格：图标列(7%) + 内容列
- 代码表格：<TABLE CLASS="code"> + <PRE>
"""
import re
import json
from pathlib import Path
from datetime import datetime
from html.parser import HTMLParser

class CAAHTMLParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.result = []
        self.skip_depth = 0
        self.skip_icon_cols = True
        
        # 表格状态
        self.in_table = False
        self.in_tr = False
        self.in_td = False
        self.in_icon_col = False
        self.td_count = 0
        self.td_content = []
        
        # 代码块状态
        self.in_code_table = False
        self.in_pre = False
        self.code_buffer = []
        self.code_lang = ''
        
        # 文本缓冲
        self.current_text = []
        
    def handle_starttag(self, tag, attrs):
        attrs_dict = dict(attrs)
        
        if tag in ('script', 'style', 'noscript', 'head', 'html', 'meta', 'link'):
            self.skip_depth += 1
            return
        
        if tag == 'body':
            return
        
        if tag == 'table':
            table_class = attrs_dict.get('class', '').lower()
            if 'code' in table_class:
                self.in_code_table = True
                self.code_buffer = []
            else:
                self.in_table = True
                self.td_count = 0
                self.skip_icon_cols = True
            return
        
        if tag == 'tr':
            self.in_tr = True
            self.td_count = 0
            self.td_content = []
            return
        
        if tag in ('td', 'th'):
            self.in_td = True
            width = attrs_dict.get('width', '')
            
            # 检测图标列 (7%宽度)
            if '7%' in str(width):
                self.in_icon_col = True
            else:
                self.in_icon_col = False
            
            self.current_text = []
            return
        
        if tag == 'pre':
            self.in_pre = True
            self.code_buffer = []
            # 检测语言
            code_elem = None
            for attr_name, attr_val in attrs:
                if attr_name == 'class':
                    if 'vbscript' in attr_val.lower():
                        self.code_lang = 'vbscript'
                    elif 'cpp' in attr_val.lower() or 'c++' in attr_val.lower():
                        self.code_lang = 'cpp'
                    else:
                        self.code_lang = ''
                    break
            return
        
        if tag == 'code':
            if self.in_pre:
                for attr_name, attr_val in attrs:
                    if attr_name == 'class':
                        if 'vbscript' in attr_val.lower():
                            self.code_lang = 'vbscript'
                        break
            return
        
        if tag == 'br':
            if self.in_pre:
                self.code_buffer.append('\n')
            elif self.in_td and not self.in_icon_col:
                self.current_text.append(' ')
            return
        
        if tag == 'hr':
            self.result.append('\n\n---\n\n')
            return
        
        if tag == 'p':
            if not self.in_code_table and not self.in_pre:
                self.result.append('\n\n')
            return
        
        if tag in ('h1', 'h2', 'h3', 'h4', 'h5', 'h6'):
            level = int(tag[1])
            self.result.append('\n\n' + '#' * level + ' ')
            return
        
        if tag == 'a':
            self.current_text.append('[')
            return
        
        if tag == 'img':
            src = attrs_dict.get('src', '')
            alt = attrs_dict.get('alt', '')
            if not self.in_icon_col:
                self.current_text.append(f'![{alt}]({src})')
            return
        
        if tag == 'li':
            self.result.append('\n- ')
            return
        
        if tag == 'ol':
            self.result.append('\n')
            return
        
        if tag == 'strong' or tag == 'b':
            self.current_text.append('**')
            return
        
        if tag == 'em' or tag == 'i':
            self.current_text.append('*')
            return
    
    def handle_endtag(self, tag):
        if tag in ('script', 'style', 'noscript', 'head', 'html'):
            if self.skip_depth > 0:
                self.skip_depth -= 1
            return
        
        if tag == 'body':
            return
        
        if tag == 'table':
            if self.in_code_table:
                # 输出代码块
                if self.code_buffer:
                    code_text = ''.join(self.code_buffer)
                    code_text = re.sub(r'<FONT[^>]*>', '', code_text)
                    code_text = re.sub(r'</FONT>', '', code_text)
                    code_text = code_text.strip()
                    if code_text:
                        self.result.append(f'\n```{self.code_lang}\n{code_text}\n```\n\n')
                self.in_code_table = False
            else:
                self.in_table = False
            return
        
        if tag == 'tr':
            self.in_tr = False
            # 输出内容列的文本
            if not self.in_code_table:
                text = ''.join(self.td_content).strip()
                if text:
                    self.result.append(text)
            self.td_content = []
            return
        
        if tag in ('td', 'th'):
            self.in_td = False
            # 收集单元格文本
            if not self.in_icon_col and not self.in_code_table:
                text = ''.join(self.current_text).strip()
                if text:
                    self.td_content.append(text)
                    self.td_content.append(' ')
            self.current_text = []
            self.in_icon_col = False
            return
        
        if tag == 'pre':
            self.in_pre = False
            # 收集代码
            code_text = ''.join(self.code_buffer)
            code_text = re.sub(r'<FONT[^>]*>', '', code_text)
            code_text = re.sub(r'</FONT>', '', code_text)
            code_text = code_text.strip()
            if code_text:
                if self.in_code_table:
                    self.code_buffer.append(code_text)
                else:
                    self.result.append(f'\n```{self.code_lang}\n{code_text}\n```\n\n')
            self.code_buffer = []
            self.code_lang = ''
            return
        
        if tag == 'code':
            return
        
        if tag == 'a':
            self.current_text.append(']')
            return
        
        if tag == 'strong' or tag == 'b':
            self.current_text.append('**')
            return
        
        if tag == 'em' or tag == 'i':
            self.current_text.append('*')
            return
    
    def handle_data(self, data):
        if self.skip_depth > 0:
            return
        
        if self.in_pre:
            self.code_buffer.append(data)
            return
        
        if self.in_td:
            if not self.in_icon_col:
                self.current_text.append(data)
            return
        
        self.result.append(data)
    
    def get_markdown(self):
        text = ''.join(self.result)
        
        # 清理HTML实体
        text = text.replace('&lt;', '<').replace('&gt;', '>').replace('&amp;', '&')
        text = text.replace('&quot;', '"').replace('&nbsp;', ' ')
        text = text.replace('&#39;', "'").replace('&#34;', '"')
        text = text.replace('&#9;', '\t')
        
        # 清理多余空行
        text = re.sub(r'\n{3,}', '\n\n', text)
        
        # 清理无意义的表格分隔符
        lines = text.split('\n')
        result = []
        for line in lines:
            stripped = line.strip()
            # 跳过无意义的表格行
            if stripped == '|':
                continue
            if re.match(r'^\|?\s*[-=]+\s*\|', stripped):
                continue
            result.append(line)
        
        text = '\n'.join(result)
        
        return text.strip()


class CAAHTMLConverterV6:
    def __init__(self, base_dir):
        self.base_dir = Path(base_dir)
        self.output_base = self.base_dir / "CAAKnowledge"
        self.stats = {'processed': 0, 'failed': 0}

    def infer_category(self, module, title):
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

    def extract_frontmatter(self, html_content, filepath):
        title_match = re.search(r'<TITLE>([^<]+)</TITLE>', html_content)
        title = title_match.group(1).strip() if title_match else "Untitled"
        
        parts = str(filepath).replace('\\', '/').split('/')
        module = parts[-2] if len(parts) >= 2 else "unknown"
        
        category = self.infer_category(module, title)
        tags = list(set(re.findall(r'\b(CATI\w+|CAA\w+)\b', html_content)))[:20]
        
        return {
            'title': title,
            'category': category,
            'module': module,
            'tags': tags,
            'source_file': f"Doc/online/{module}/{Path(filepath).name}"
        }

    def convert(self, html_content):
        parser = CAAHTMLParser()
        parser.feed(html_content)
        return parser.get_markdown()

    def process_file(self, filepath):
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
        print("=" * 60)
        print("CATIA CAA V5 HTML转Markdown V6")
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
    converter = CAAHTMLConverterV6(base_dir)
    converter.run()
