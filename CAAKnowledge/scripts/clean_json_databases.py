# -*- coding: utf-8 -*-
"""
JSON知识库清理 - P2-4
"""

import sys
import json
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def clean_json_databases():
    """清理JSON知识库"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    data_dir = root_dir / 'data'
    
    json_files = list(data_dir.glob('*.json'))
    
    print("P2-4: Cleaning JSON Databases")
    print("=" * 50)
    print(f"Found {len(json_files)} JSON files")
    
    kept_files = []
    
    all_data = {
        'interfaces': [],
        'use_cases': [],
        'qi_paths': [],
        'tie_bindings': [],
        'metadata': {
            'generated_at': '2026-05-12',
            'version': 'v2.0'
        }
    }
    
    for json_file in sorted(json_files):
        if json_file.name == 'search-index.json':
            kept_files.append(f"{json_file.name} (kept for search)")
            continue
        
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
            
            if isinstance(data, dict):
                if 'interfaces' in data and isinstance(data['interfaces'], list):
                    all_data['interfaces'].extend(data['interfaces'])
                if 'use_cases' in data and isinstance(data['use_cases'], list):
                    all_data['use_cases'].extend(data['use_cases'])
                if 'qi_paths' in data and isinstance(data['qi_paths'], list):
                    all_data['qi_paths'].extend(data['qi_paths'])
                if 'tie_bindings' in data and isinstance(data['tie_bindings'], list):
                    all_data['tie_bindings'].extend(data['tie_bindings'])
            
            kept_files.append(f"{json_file.name} (processed)")
                
        except Exception as e:
            print(f"  Warning: Error reading {json_file}: {e}")
    
    # 保存合并后的知识库
    output_file = data_dir / 'knowledge_base_consolidated.json'
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(all_data, f, indent=2, ensure_ascii=False)
    
    print(f"\n[OK] JSON databases cleaned!")
    print(f"   - Processed files: {len(kept_files)}")
    print(f"   - Consolidated: {output_file}")

if __name__ == '__main__':
    clean_json_databases()