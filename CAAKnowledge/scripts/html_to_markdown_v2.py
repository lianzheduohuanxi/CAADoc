#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CATIA CAA V5 知识库蒸馏 - HTML转Markdown转换器 V2
重写转换器，保留<pre>代码块格式，替代html2text
"""

import os
import re
import json
from pathlib import Path
from datetime import datetime
from bs4 import BeautifulSoup, NavigableString


class CAAHTMLConverterV2:
    def __init__(self, base_dir):
        self.base_dir = Path(base_dir)
        self.output_base = self.base_dir / "CAAKnowledge"

        self.stats = {
            'processed': 0,
            'failed': 0,
            'by_category': {}
        }

    def extract_frontmatter(self, soup, filepath):
        title = soup.find('title')
        title = title.text.strip() if title else "Untitled"

        category = "general"
        for td in soup.find_all('td'):
            classes = td.get('class', [])
            if isinstance(classes, str):
                classes = [classes]
            if any('use' in c.lower() for c in classes):
                category = td.text.strip().lower()
                break

        parts = str(filepath).replace('\\', '/').split('/')
        module = parts[-2] if len(parts) >= 2 else "unknown"

        text_content = soup.get_text()
        tags = list(set(re.findall(r'\b(CATI\w+|CAA\w+)\b', text_content)))[:20]

        return {
            'title': title,
            'category': category,
            'module': module,
            'tags': tags,
            'source_file': str(filepath)
        }

    def _escape_md(self, text):
        if not text:
            return ""
        text = text.replace('\\', '\\\\')
        text = text.replace('*', '\\*')
        text = text.replace('_', '\\_')
        text = text.replace('[', '\\[')
        text = text.replace(']', '\\]')
        return text

    def _convert_element(self, elem, in_pre=False):
        if isinstance(elem, NavigableString):
            text = str(elem)
            if in_pre:
                return text
            text = text.replace('\n', ' ').replace('\r', ' ')
            text = re.sub(r' +', ' ', text)
            return text

        tag = elem.name
        if tag is None:
            return ""

        if tag == 'pre':
            code_text = elem.get_text()
            lang = ""
            code_tag = elem.find('code')
            if code_tag and code_tag.get('class'):
                classes = code_tag['class']
                if isinstance(classes, list):
                    for c in classes:
                        if c.startswith('language-'):
                            lang = c.replace('language-', '')
                            break
                elif isinstance(classes, str):
                    if classes.startswith('language-'):
                        lang = classes.replace('language-', '')
            code_text = code_text.rstrip('\n')
            return f'\n```{lang}\n{code_text}\n```\n'

        if tag == 'code':
            text = elem.get_text()
            if in_pre:
                return text
            return f'`{text}`'

        if tag == 'table':
            return self._convert_table(elem)

        if tag in ('script', 'style', 'nav'):
            return ""

        if tag == 'br':
            return '\n'

        if tag == 'p':
            inner = self._convert_children(elem, in_pre)
            return f'\n\n{inner}\n\n'

        if tag in ('h1', 'h2', 'h3', 'h4', 'h5', 'h6'):
            level = int(tag[1])
            inner = self._convert_children(elem, in_pre).strip()
            return f'\n\n{"#" * level} {inner}\n\n'

        if tag == 'a':
            href = elem.get('href', '')
            inner = self._convert_children(elem, in_pre).strip()
            if not href or href.startswith('#') or href == inner:
                return inner
            return f'[{inner}]({href})'

        if tag == 'img':
            src = elem.get('src', '')
            alt = elem.get('alt', '')
            return f'![{alt}]({src})'

        if tag == 'ul':
            items = []
            for li in elem.find_all('li', recursive=False):
                inner = self._convert_children(li, in_pre).strip()
                items.append(f'- {inner}')
            return '\n' + '\n'.join(items) + '\n'

        if tag == 'ol':
            items = []
            for idx, li in enumerate(elem.find_all('li', recursive=False), 1):
                inner = self._convert_children(li, in_pre).strip()
                items.append(f'{idx}. {inner}')
            return '\n' + '\n'.join(items) + '\n'

        if tag == 'li':
            return self._convert_children(elem, in_pre)

        if tag in ('strong', 'b'):
            inner = self._convert_children(elem, in_pre).strip()
            return f'**{inner}**'

        if tag in ('em', 'i'):
            inner = self._convert_children(elem, in_pre).strip()
            return f'_{inner}_'

        if tag == 'hr':
            return '\n\n---\n\n'

        if tag in ('div', 'span', 'td', 'th', 'tr', 'tbody', 'thead'):
            return self._convert_children(elem, in_pre)

        return self._convert_children(elem, in_pre)

    def _convert_children(self, elem, in_pre=False):
        parts = []
        for child in elem.children:
            parts.append(self._convert_element(child, in_pre))
        return ''.join(parts)

    def _convert_table(self, table):
        rows = []
        headers = []
        data_rows = []

        for tr in table.find_all('tr'):
            cells = []
            for td in tr.find_all(['td', 'th']):
                text = self._convert_children(td).strip()
                text = text.replace('\n', ' ').replace('|', '\\|')
                cells.append(text)
            if not cells:
                continue
            if tr.find('th'):
                headers = cells
            else:
                data_rows.append(cells)

        if not headers and data_rows:
            headers = data_rows[0]
            data_rows = data_rows[1:]

        if not headers:
            return ''

        md = '\n|' + '|'.join(headers) + '|\n'
        md += '|' + '|'.join(['---'] * len(headers)) + '|\n'
        for row in data_rows:
            while len(row) < len(headers):
                row.append('')
            md += '|' + '|'.join(row[:len(headers)]) + '|\n'
        return md + '\n'

    def convert_html_to_markdown(self, html_content):
        soup = BeautifulSoup(html_content, 'html.parser')

        body = soup.find('body')
        if not body:
            body = soup

        md = self._convert_children(body)

        md = re.sub(r'\n{3,}', '\n\n', md)
        md = re.sub(r'[ \t]+\n', '\n', md)
        md = md.strip()

        return md

    def process_file(self, filepath):
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()

            soup = BeautifulSoup(content, 'html.parser')
            frontmatter = self.extract_frontmatter(soup, str(filepath))

            markdown_content = self.convert_html_to_markdown(content)

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
            output_path = self.output_base / "use-cases" / frontmatter['module'].lower().replace('use', '')
            output_path.mkdir(parents=True, exist_ok=True)

            output_file = output_path / f"{rel_path.stem}.md"

            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(result)

            self.stats['processed'] += 1
            category = frontmatter['category']
            self.stats['by_category'][category] = self.stats['by_category'].get(category, 0) + 1

            return True

        except Exception as e:
            self.stats['failed'] += 1
            print(f"Failed: {filepath} - {e}")
            return False

    def process_directory(self, dir_path, pattern="*.htm"):
        dir_path = Path(dir_path)
        files = list(dir_path.rglob(pattern))
        print(f"Processing {len(files)} files in {dir_path}...")

        for filepath in files:
            self.process_file(filepath)

        return self.stats

    def run(self):
        print("=" * 60)
        print("CATIA CAA V5 知识库蒸馏 - HTML转Markdown V2")
        print("=" * 60)

        docs_dir = self.base_dir / "Doc" / "online"

        if not docs_dir.exists():
            print(f"Error: {docs_dir} not found")
            return

        module_dirs = [
            "CAAAfrUseCases", "CAAAfrTechArticles",
            "CAADlgUseCases", "CAADlgTechArticles",
            "CAAPrtUseCases", "CAAPrtTechArticles",
            "CAAGsiUseCases", "CAAGsiTechArticles",
            "CAATopUseCases", "CAATopTechArticles",
            "CAASkiUseCases", "CAASmaUseCases",
            "CAASmiUseCases", "CAASmiTechArticles",
            "CAAScdAsmUseCases", "CAAScdStrUseCases",
            "CAADriUseCases", "CAADriTechArticles",
            "CAAScdDriUseCases", "CAAScdDriTechArticles",
            "CAAManufacturingItf",
            "CAAScdMmrUseCases", "CAAScdMmrTechArticles",
            "CAAScdPriUseCases", "CAAScdPriTechArticles",
            "CAAScdSchUseCases", "CAASchUseCases", "CAASchBase",
            "CAAScdArrUseCases", "CAAScdArrTechArticles",
            "CAAScdAniUseCases", "CAAScdAniTechArticles",
            "CAAScdKniUseCases", "CAAScdKniTechArticles",
            "CAAScdPstUseCases", "CAAScdPstTechArticles",
            "CAAScdInfUseCases", "CAAScdInfTechArticles",
            "CAAXmlUseCases", "CAAXmlTechArticles",
            "CAAVseUseCases", "CAAVseTechArticles",
            "CAAWSTechArticles",
            "CAACloUseCases", "CAACloTechArticles",
            "CAADegUseCases", "CAADegTechArticles",
            "CAADkiUseCases", "CAADkoUseCases", "CAADkpUseCases",
            "CAAOmmUseCases", "CAAOptTechArticles",
            "CAABehUseCases", "CAABtlUseCases", "CAABtlTechArticles",
            "CAABtoUseCases", "CAACenQuickRefs",
            "CAACgmBase", "CAACgmModel", "CAACgmOperators",
            "CAAPbaUseCases", "CAAPPRJNavigatorUsesCases",
            "CAAArrUseCases", "CAAJafUseCases", "CAAEvcUseCases",
            "CAAImmBase", "CAAScrUseCases",
            "CAAScdTpiUseCases", "CAAScdMaiUseCases",
            "CAAVxbUseCases",
            "CAAAerospaceSheetMetalArticles",
        ]

        for module_dir in module_dirs:
            module_path = docs_dir / module_dir
            if module_path.exists():
                print(f"\n>>> Processing {module_dir}...")
                self.process_directory(module_path)

        print("\n" + "=" * 60)
        print("V2 转换完成!")
        print(f"成功: {self.stats['processed']}")
        print(f"失败: {self.stats['failed']}")
        print("按分类统计:")
        for cat, count in sorted(self.stats['by_category'].items()):
            print(f"  {cat}: {count}")
        print("=" * 60)

        return self.stats


if __name__ == "__main__":
    import sys
    base_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    converter = CAAHTMLConverterV2(base_dir)
    converter.run()
