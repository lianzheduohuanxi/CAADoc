#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CATIA CAA V5 知识库蒸馏 - HTML转Markdown转换器
将官方在线文档的HTML文件转换为结构化的Markdown文档
"""

import os
import re
import json
from pathlib import Path
from datetime import datetime
from bs4 import BeautifulSoup
import html2text

class CAAHTMLConverter:
    def __init__(self, base_dir):
        self.base_dir = Path(base_dir)
        self.output_base = self.base_dir / "CAAKnowledge"
        self.h = html2text.HTML2Text()
        self.h.body_width = 0  # 不换行
        self.h.ignore_links = False
        self.h.ignore_images = False
        self.h.ignore_emphasis = False
        self.h.unicode_snob = True
        
        # 统计信息
        self.stats = {
            'processed': 0,
            'failed': 0,
            'by_category': {}
        }
        
    def extract_frontmatter(self, soup, filepath):
        """从HTML中提取元数据"""
        title = soup.find('title')
        title = title.text if title else "Untitled"
        
        # 提取h1和h2
        h1 = soup.find('h1')
        h2 = soup.find('h2')
        h3_elem = soup.find('h3')
        
        # 尝试从表格中提取分类
        category = "general"
        for td in soup.find_all('td'):
            if td.get('class') and 'use' in ' '.join(td.get('class', [])):
                category = td.text.strip().lower()
                break
        
        # 从路径提取模块名
        module = str(filepath).split('/')[-2] if '/' in str(filepath) else str(filepath).split('\\')[-2] if '\\' in str(filepath) else "unknown"
        
        # 提取标签（接口名、类名等）
        tags = []
        text_content = soup.get_text()
        cat_interfaces = re.findall(r'CATI\w+', text_content)
        caa_interfaces = re.findall(r'CAA\w+', text_content)
        tags = list(set(cat_interfaces + caa_interfaces))[:20]  # 限制标签数量
        
        return {
            'title': title,
            'category': category,
            'module': module,
            'tags': tags,
            'source_file': filepath
        }
    
    def extract_code_blocks(self, soup):
        """提取代码块"""
        codes = []
        
        # 查找pre和code标签
        for pre in soup.find_all('pre'):
            code = pre.get_text(strip=True)
            if len(code) > 10:  # 过滤太短的代码
                codes.append(code)
        
        return codes
    
    def extract_api_references(self, soup):
        """提取API引用"""
        apis = []
        text_content = soup.get_text()
        
        # 匹配CATI*, CAA*, CATPublic*, CATBaseUnknown等
        interface_pattern = r'\b(CATI\w+|CAA\w+|CATPublic\w+|CATBaseUnknown|CATDocument|CATSession|CATContainer|CATElement)\b'
        matches = re.findall(interface_pattern, text_content)
        apis = list(set(matches))
        
        return apis
    
    def convert_html_to_markdown(self, html_content):
        """HTML转Markdown"""
        return self.h.handle(html_content)
    
    def process_file(self, filepath):
        """处理单个HTML文件"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            soup = BeautifulSoup(content, 'html.parser')
            
            # 提取元数据
            frontmatter = self.extract_frontmatter(soup, filepath)
            
            # 转换内容
            markdown_content = self.convert_html_to_markdown(content)
            
            # 生成带frontmatter的文档
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
            
            # 生成输出路径
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
        """处理目录下的所有HTML文件"""
        dir_path = Path(dir_path)
        files = list(dir_path.rglob(pattern))
        print(f"Processing {len(files)} files in {dir_path}...")
        
        for filepath in files:
            self.process_file(filepath)
        
        return self.stats

    def run(self):
        """运行转换"""
        print("=" * 60)
        print("CATIA CAA V5 知识库蒸馏 - HTML转Markdown")
        print("=" * 60)
        
        docs_dir = self.base_dir / "Doc" / "online"
        
        if not docs_dir.exists():
            print(f"Error: {docs_dir} not found")
            return
        
        # 处理主要模块目录
        module_dirs = [
            "CAAAfrUseCases",
            "CAAAfrTechArticles", 
            "CAADlgUseCases",
            "CAADlgTechArticles",
            "CAAPrtUseCases",
            "CAAPrtTechArticles",
            "CAAGsiUseCases",
            "CAAGsiTechArticles",
            "CAATopUseCases",
            "CAATopTechArticles",
            "CAASkiUseCases",
            "CAASmaUseCases",
            "CAASmiUseCases",
            "CAASmiTechArticles",
            "CAAScdAsmUseCases",
            "CAAScdStrUseCases",
            "CAADriUseCases",
            "CAADriTechArticles",
            "CAAScdDriUseCases",
            "CAAScdDriTechArticles",
            "CAAManufacturingItf",
            "CAAScdMmrUseCases",
            "CAAScdMmrTechArticles",
            "CAAScdPriUseCases",
            "CAAScdPriTechArticles",
            "CAAScdSchUseCases",
            "CAASchUseCases",
            "CAASchBase",
            "CAAScdArrUseCases",
            "CAAScdArrTechArticles",
            "CAAScdAniUseCases",
            "CAAScdAniTechArticles",
            "CAAScdKniUseCases",
            "CAAScdKniTechArticles",
            "CAAScdPstUseCases",
            "CAAScdPstTechArticles",
            "CAAScdInfUseCases",
            "CAAScdInfTechArticles",
        ]
        
        for module_dir in module_dirs:
            module_path = docs_dir / module_dir
            if module_path.exists():
                print(f"\n>>> Processing {module_dir}...")
                self.process_directory(module_path)
        
        # 打印统计
        print("\n" + "=" * 60)
        print("转换完成!")
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
    converter = CAAHTMLConverter(base_dir)
    converter.run()