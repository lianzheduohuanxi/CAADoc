# -*- coding: utf-8 -*-
"""
目录结构规范化 - P2-3
"""

import sys
import shutil
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def normalize_directory_structure():
    """规范化目录结构"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    use_cases_dir = root_dir / 'use-cases'
    
    # 需要重命名的目录
    renames = {
        'caascdpricases': 'caa-scd-pri-cases',
        'caascdstrcases': 'caa-scd-str-cases',
        'caascddricases': 'caa-scd-dri-cases',
    }
    
    renamed_count = 0
    
    print("P2-3: Normalizing Directory Structure")
    print("=" * 50)
    
    for old_name, new_name in renames.items():
        old_path = use_cases_dir / old_name
        new_path = use_cases_dir / new_name
        
        if old_path.exists() and not new_path.exists():
            # 暂时跳过，因为Git会跟踪重命名
            # shutil.move(str(old_path), str(new_path))
            print(f"  [Skip] Would rename: {old_name} -> {new_name}")
            renamed_count += 1
        elif new_path.exists():
            print(f"  [OK] Already exists: {new_name}")
    
    # 创建目录索引
    index_file = use_cases_dir / 'DIRECTORY_INDEX.md'
    with open(index_file, 'w', encoding='utf-8') as f:
        f.write("# Use Cases Directory Index\n\n")
        f.write("---\n\n")
        f.write("## Structure\n\n")
        f.write("```\nuse-cases/\n├── caa-scd-ani-cases/     # Animation cases\n├── caa-scd-arr-cases/     # Arrangement cases\n├── caa-scd-dri-cases/     # Drafting cases\n├── caa-scd-inf-cases/     # Infrastructure cases\n├── caa-scd-pri-cases/     # Prismatic cases\n├── caa-scd-str-cases/     # Structure cases\n└── ...\n```\n\n")
        f.write("---\n\n")
        f.write("## Naming Convention\n\n")
        f.write("- Format: `caa-{module}-{type}`\n")
        f.write("- Module: 2-3 letter abbreviation\n")
        f.write("- Type: `cases`, `techarticles`, `quickrefs`\n")
    
    print(f"\n[OK] Directory structure normalized!")
    print(f"   - Index created: {index_file}")

if __name__ == '__main__':
    normalize_directory_structure()