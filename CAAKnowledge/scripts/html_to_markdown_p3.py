#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CATIA CAA V5 知识库蒸馏 - Phase 4: P3模块HTML文档转换
Math, PDM, XML Parser, Batch, KnowHow 等扩展模块
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
        self.h.body_width = 0
        self.h.ignore_links = False
        self.h.ignore_images = False
        self.h.ignore_emphasis = False
        self.h.unicode_snob = True
        
        self.stats = {
            'processed': 0,
            'failed': 0,
            'by_category': {}
        }
        
    def extract_frontmatter(self, soup, filepath):
        title = soup.find('title')
        title = title.text if title else "Untitled"
        
        category = "general"
        for td in soup.find_all('td'):
            if td.get('class') and 'use' in ' '.join(td.get('class', [])):
                category = td.text.strip().lower()
                break
        
        module = str(filepath).split('/')[-2] if '/' in str(filepath) else str(filepath).split('\\')[-2] if '\\' in str(filepath) else "unknown"
        
        text_content = soup.get_text()
        tags = list(set(re.findall(r'\b(CATI\w+|CAA\w+)\b', text_content)))[:20]
        
        return {
            'title': title,
            'category': category,
            'module': module,
            'tags': tags,
            'source_file': str(filepath)
        }
    
    def convert_html_to_markdown(self, html_content):
        return self.h.handle(html_content)
    
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
        print("CATIA CAA V5 知识库蒸馏 - Phase 4: P3扩展模块")
        print("=" * 60)
        
        docs_dir = self.base_dir / "Doc" / "online"
        
        if not docs_dir.exists():
            print(f"Error: {docs_dir} not found")
            return
        
        # P3 扩展模块目录
        module_dirs = [
            # Advanced Mathematics & Optimization
            "CAAAdvancedMathematics.edu",
            "CAAOptimizationInterfaces.edu",
            # PDM & Collaboration
            "CAAxPDMInterfaces.edu",
            "CAACATPDMReconcile.edu",
            "CAACollabDesignItf.edu",
            "CAAPLMSecUseCases",
            # XML & Data
            "CAAXMLParser.edu",
            "CAAXmlUseCases",
            "CAAXmlTechArticles",
            # Batch Processing
            "CAABatchInfrastructure.edu",
            "CAABatUseCases",
            "CAABatTechArticles",
            # V4 Integration
            "CAACATIAV4Interfaces.edu",
            "CAAV4iUseCases",
            "CAAV4iBase",
            # Advanced Topological Operations
            "CAAAdvancedTopologicalOpe.edu",
            "CAATobUseCases",
            "CAATobTechArticles",
            # Knowledge Engineering
            "CAAKnowHow.edu",
            "CAADkiUseCases",
            "CAADkiBase",
            "CAADkoUseCases",
            "CAADkpUseCases",
            # Optimization
            "CAAOmmUseCases",
            "CAAOptTechArticles",
            # Others
            "CAABtlUseCases",
            "CAABtlTechArticles",
            "CAABtoUseCases",
            "CAACenQuickRefs",
            "CAACgmBase",
            "CAACgmModel",
            "CAACgmOperators",
            "CAACloUseCases",
            "CAACloTechArticles",
            "CAADegUseCases",
            "CAADegTechArticles",
            # Workflow
            "CAABehUseCases",
            "CAABehBase",
            "CAABtlQuickRefs",
            # API Changes History
            "CAACenAPIChanges",
            "CAACenAPIChangesR10",
            "CAACenAPIChangesR11",
            "CAACenAPIChangesR12",
            "CAACenAPIChangesR13",
            "CAACenAPIChangesR14",
            "CAACenAPIChangesR15",
            "CAACenAPIChangesR16",
            "CAACenAPIChangesR17",
            "CAACenAPIChangesR18",
            "CAACenAPIChangesR19",
            "CAACenAPIChangesR20",
            "CAACenAPIChangesR21",
            "CAACenAPIChangesR22",
            "CAACenAPIChangesR23",
            "CAACenAPIChangesR24",
            "CAACenAPIChangesR25",
            "CAACenAPIChangesR26",
            "CAACenAPIChangesR27",
            "CAACenAPIChangesR7",
            "CAACenAPIChangesR8",
            "CAACenAPIChangesR9",
        ]
        
        for module_dir in module_dirs:
            module_path = docs_dir / module_dir
            if module_path.exists():
                print(f"\n>>> Processing {module_dir}...")
                self.process_directory(module_path)
        
        print("\n" + "=" * 60)
        print("Phase 4 HTML转换完成!")
        print(f"成功: {self.stats['processed']}")
        print(f"失败: {self.stats['failed']}")
        print("=" * 60)
        
        return self.stats


if __name__ == "__main__":
    import sys
    base_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    converter = CAAHTMLConverter(base_dir)
    converter.run()