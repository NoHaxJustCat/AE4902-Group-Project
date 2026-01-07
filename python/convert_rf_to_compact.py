#!/usr/bin/env python3
"""
Convert a scikit-learn RandomForestRegressor to compact Arduino PROGMEM format.

Usage:
    python convert_rf_to_compact.py model.pkl > random_forest_compact.h
    
Or in your training script:
    from convert_rf_to_compact import export_rf_to_header
    export_rf_to_header(model, "random_forest_compact.h", feature_names=["time", "cap_base", "temp", "i_mean"])
"""

import sys
import pickle
import numpy as np


def tree_to_nodes(tree, tree_idx):
    """Convert sklearn tree to flat node array format."""
    t = tree.tree_
    nodes = []
    
    def traverse(node_id, nodes_list):
        """Recursively convert tree nodes."""
        if t.children_left[node_id] == -1:  # Leaf
            # Leaf node: feature=-1, threshold=leaf_value
            leaf_value = t.value[node_id][0][0]
            nodes_list.append({
                'feature': -1,
                'threshold': float(leaf_value),
                'left': 0,
                'right': 0
            })
        else:
            # Internal node
            current_idx = len(nodes_list)
            nodes_list.append(None)  # Placeholder
            
            left_idx = len(nodes_list)
            traverse(t.children_left[node_id], nodes_list)
            
            right_idx = len(nodes_list) 
            traverse(t.children_right[node_id], nodes_list)
            
            # Fill in the placeholder
            nodes_list[current_idx] = {
                'feature': int(t.feature[node_id]),
                'threshold': float(t.threshold[node_id]),
                'left': left_idx,
                'right': right_idx
            }
    
    traverse(0, nodes)
    return nodes


def format_node(node):
    """Format a single node as C struct initializer."""
    return f"{{{node['feature']}, {node['threshold']:.6f}f, {node['left']}, {node['right']}}}"


def export_rf_to_header(model, output_path=None, feature_names=None):
    """
    Export RandomForestRegressor to compact header format.
    
    Args:
        model: sklearn RandomForestRegressor
        output_path: Output file path (None for stdout)
        feature_names: Optional list of feature names for comments
    """
    n_trees = len(model.estimators_)
    n_features = model.n_features_in_
    
    # Convert all trees
    all_trees = []
    for i, estimator in enumerate(model.estimators_):
        nodes = tree_to_nodes(estimator, i)
        all_trees.append(nodes)
    
    # Calculate total memory
    total_nodes = sum(len(t) for t in all_trees)
    mem_bytes = total_nodes * 10  # 10 bytes per node
    
    # Generate header
    lines = []
    lines.append("#pragma once")
    lines.append("#include <Arduino.h>")
    lines.append("#include <avr/pgmspace.h>")
    lines.append("")
    lines.append("// Compact Random Forest - Auto-generated")
    lines.append(f"// Trees: {n_trees}, Total nodes: {total_nodes}, PROGMEM: ~{mem_bytes} bytes")
    lines.append("")
    lines.append("struct TreeNode {")
    lines.append("    int8_t feature;      // -1 for leaf")
    lines.append("    float threshold;     // leaf value if feature == -1")
    lines.append("    int16_t left;")
    lines.append("    int16_t right;")
    lines.append("};")
    lines.append("")
    lines.append(f"#define RF_NUM_TREES {n_trees}")
    lines.append(f"#define RF_NUM_FEATURES {n_features}")
    lines.append("")
    
    # Feature names comment
    if feature_names:
        lines.append("// Features: " + ", ".join(f"[{i}]={n}" for i, n in enumerate(feature_names)))
        lines.append("")
    
    # Tree sizes
    lines.append(f"const uint16_t PROGMEM tree_sizes[RF_NUM_TREES] = {{{', '.join(str(len(t)) for t in all_trees)}}};")
    lines.append("")
    
    # Each tree's nodes
    for i, tree_nodes in enumerate(all_trees):
        lines.append(f"// Tree {i}: {len(tree_nodes)} nodes")
        lines.append(f"const TreeNode PROGMEM tree_{i}[] = {{")
        for j, node in enumerate(tree_nodes):
            comma = "," if j < len(tree_nodes) - 1 else ""
            feat_comment = ""
            if feature_names and node['feature'] >= 0:
                feat_comment = f"  // {feature_names[node['feature']]} <= {node['threshold']:.4f}"
            elif node['feature'] == -1:
                feat_comment = f"  // leaf = {node['threshold']:.4f}"
            lines.append(f"    {format_node(node)}{comma}{feat_comment}")
        lines.append("};")
        lines.append("")
    
    # Tree pointer array
    lines.append(f"const TreeNode* const PROGMEM trees[RF_NUM_TREES] = {{{', '.join(f'tree_{i}' for i in range(n_trees))}}};")
    lines.append("")
    
    # Traversal class
    lines.append("class RandomForestCompact {")
    lines.append("public:")
    lines.append("    float predict(float* x) {")
    lines.append("        float sum = 0.0f;")
    lines.append("        for (uint8_t t = 0; t < RF_NUM_TREES; t++) {")
    lines.append("            const TreeNode* tree = (const TreeNode*)pgm_read_ptr(&trees[t]);")
    lines.append("            uint16_t node_idx = 0;")
    lines.append("            while (true) {")
    lines.append("                TreeNode node;")
    lines.append("                memcpy_P(&node, &tree[node_idx], sizeof(TreeNode));")
    lines.append("                if (node.feature == -1) {")
    lines.append("                    sum += node.threshold;")
    lines.append("                    break;")
    lines.append("                }")
    lines.append("                node_idx = (x[node.feature] <= node.threshold) ? node.left : node.right;")
    lines.append("            }")
    lines.append("        }")
    lines.append("        return sum / RF_NUM_TREES;")
    lines.append("    }")
    lines.append("};")
    
    output = "\n".join(lines)
    
    if output_path:
        with open(output_path, 'w') as f:
            f.write(output)
        print(f"Wrote {output_path}: {n_trees} trees, {total_nodes} nodes, ~{mem_bytes} bytes PROGMEM", file=sys.stderr)
    else:
        print(output)
    
    return output


def main():
    if len(sys.argv) < 2:
        print("Usage: python convert_rf_to_compact.py <model.pkl> [output.h]", file=sys.stderr)
        print("       Converts sklearn RandomForestRegressor to compact Arduino format", file=sys.stderr)
        sys.exit(1)
    
    model_path = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) > 2 else None
    
    with open(model_path, 'rb') as f:
        model = pickle.load(f)
    
    # Try to get feature names if stored
    feature_names = None
    if hasattr(model, 'feature_names_in_'):
        feature_names = list(model.feature_names_in_)
    
    export_rf_to_header(model, output_path, feature_names)


if __name__ == "__main__":
    main()
