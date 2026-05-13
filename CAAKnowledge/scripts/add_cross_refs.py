"""
为接口文档添加交叉引用
"""
import re
import json
from pathlib import Path

def add_cross_references():
    """为接口文档添加相关用例引用"""
    
    # 读取接口列表
    interfaces_dir = Path('api-reference/interfaces')
    interfaces = list(interfaces_dir.glob('*.md'))
    
    # 构建用例索引 (文件名 -> 接口名映射)
    usecase_index = {}
    
    for uc_file in list(Path('use-cases').rglob('*.md')):
        content = uc_file.read_text(encoding='utf-8', errors='ignore')
        
        # 提取文件名中的接口名
        stem = uc_file.stem
        
        if stem not in usecase_index:
            usecase_index[stem] = {
                'file': str(uc_file.relative_to('.')),
                'path': uc_file,
                'references': []
            }
        
        # 在内容中查找接口引用
        for iface_file in interfaces:
            iface_name = iface_file.stem
            if iface_name in content and iface_name not in usecase_index[stem]['references']:
                usecase_index[stem]['references'].append(iface_name)
    
    # 为每个接口添加交叉引用
    added_count = 0
    
    for iface_file in interfaces:
        content = iface_file.read_text(encoding='utf-8', errors='ignore')
        iface_name = iface_file.stem
        
        # 检查是否已有交叉引用
        if '## Related Use Cases' in content or '## 相关用例' in content:
            continue
        
        # 查找相关用例
        related_usecases = []
        for stem, info in usecase_index.items():
            if iface_name in info['references']:
                related_usecases.append({
                    'name': stem,
                    'path': info['file']
                })
        
        if related_usecases:
            # 添加交叉引用章节
            ref_section = '\n\n## Related Use Cases\n\n'
            ref_section += 'This interface is used in the following use cases:\n\n'
            
            for uc in related_usecases[:10]:  # 最多10个
                # 转换反斜杠为正斜杠
                rel_path = uc['path'].replace('\\', '/')
                ref_section += '- [{}]({})\n'.format(uc['name'], rel_path)
            
            # 追加到文件
            content = content.rstrip() + ref_section
            iface_file.write_text(content, encoding='utf-8')
            added_count += 1
    
    print(f'Added cross-references to {added_count} interfaces')
    return added_count

def add_useful_sections():
    """为空接口添加有用信息章节"""
    
    interfaces_dir = Path('api-reference/interfaces')
    interfaces = list(interfaces_dir.glob('*.md'))
    
    enhanced_count = 0
    
    for iface_file in interfaces:
        content = iface_file.read_text(encoding='utf-8', errors='ignore')
        
        # 检查是否为空接口(没有方法说明)
        if '## Methods' not in content and '## 方法' not in content:
            # 检查是否已添加说明
            if '## Interface Notes' not in content:
                # 从文件名推断模块
                iface_name = iface_file.stem
                module = iface_name[:3]  # 如CAA, CAT等
                
                note_section = '''

## Interface Notes

This interface is part of the **{}** module.

**Status**: This interface document is a template. Please refer to the official API documentation for more information.

**Related Resources**:
- [Quick References](../quick-refs/)
- [Interface Hierarchy](../quick-refs/interface-hierarchy.md)
'''.format(module)
                content = content.rstrip() + note_section
                iface_file.write_text(content, encoding='utf-8')
                enhanced_count += 1
    
    print(f'Enhanced {enhanced_count} empty interfaces')
    return enhanced_count

if __name__ == '__main__':
    print('=== Adding Cross-References ===\n')
    
    added_refs = add_cross_references()
    print()
    
    enhanced = add_useful_sections()
    print()
    
    print('Done! Added {} cross-references, enhanced {} interfaces'.format(added_refs, enhanced))
