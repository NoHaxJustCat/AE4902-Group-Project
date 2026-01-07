#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>

// Compact Random Forest stored in PROGMEM
// Each node: [feature_index (int8), threshold (float), left_child (int16), right_child (int16)]
// Leaf nodes have feature_index = -1, threshold = leaf_value

// Tree node structure (10 bytes per node vs ~50+ bytes of if-else code)
struct TreeNode {
    int8_t feature;      // -1 for leaf nodes
    float threshold;     // leaf value if feature == -1
    int16_t left;        // left child index
    int16_t right;       // right child index
};

// ============================================================================
// PLACEHOLDER DATA - Replace with output from convert_rf_to_compact.py
// ============================================================================
// This is a simple 3-tree model for demonstration. Run the Python converter
// on your actual sklearn model to generate the real data.

#define RF_NUM_TREES 3
#define RF_NUM_FEATURES 4

// Tree sizes (number of nodes in each tree)
const uint16_t PROGMEM tree_sizes[RF_NUM_TREES] = {7, 7, 7};

// Tree 0: Simple decision tree (7 nodes)
const TreeNode PROGMEM tree_0[] = {
    {2, 25.0f, 1, 4},      // node 0: if temp <= 25
    {0, 100.0f, 2, 3},     // node 1: if time <= 100
    {-1, 95.0f, 0, 0},     // node 2: leaf = 95%
    {-1, 85.0f, 0, 0},     // node 3: leaf = 85%
    {1, 50.0f, 5, 6},      // node 4: if capacity_base <= 50
    {-1, 40.0f, 0, 0},     // node 5: leaf = 40%
    {-1, 70.0f, 0, 0},     // node 6: leaf = 70%
};

// Tree 1
const TreeNode PROGMEM tree_1[] = {
    {3, 1.5f, 1, 4},       // node 0: if i_mean <= 1.5
    {1, 60.0f, 2, 3},      // node 1: if capacity_base <= 60
    {-1, 55.0f, 0, 0},     // node 2: leaf
    {-1, 75.0f, 0, 0},     // node 3: leaf
    {2, 30.0f, 5, 6},      // node 4: if temp <= 30
    {-1, 50.0f, 0, 0},     // node 5: leaf
    {-1, 35.0f, 0, 0},     // node 6: leaf
};

// Tree 2
const TreeNode PROGMEM tree_2[] = {
    {1, 70.0f, 1, 4},      // node 0: if capacity_base <= 70
    {0, 200.0f, 2, 3},     // node 1: if time <= 200
    {-1, 65.0f, 0, 0},     // node 2: leaf
    {-1, 50.0f, 0, 0},     // node 3: leaf
    {3, 2.0f, 5, 6},       // node 4: if i_mean <= 2.0
    {-1, 80.0f, 0, 0},     // node 5: leaf
    {-1, 60.0f, 0, 0},     // node 6: leaf
};

// Array of tree pointers
const TreeNode* const PROGMEM trees[RF_NUM_TREES] = {tree_0, tree_1, tree_2};

// ============================================================================
// Compact traversal function (~100 bytes of code vs 67KB)
// ============================================================================

class RandomForestCompact {
public:
    float predict(float* x) {
        float sum = 0.0f;
        
        for (uint8_t t = 0; t < RF_NUM_TREES; t++) {
            // Get tree pointer from PROGMEM
            const TreeNode* tree = (const TreeNode*)pgm_read_ptr(&trees[t]);
            uint16_t node_idx = 0;
            
            // Traverse until leaf
            while (true) {
                // Read node from PROGMEM
                TreeNode node;
                memcpy_P(&node, &tree[node_idx], sizeof(TreeNode));
                
                // Leaf node?
                if (node.feature == -1) {
                    sum += node.threshold;  // threshold holds leaf value
                    break;
                }
                
                // Branch based on feature comparison
                if (x[node.feature] <= node.threshold) {
                    node_idx = node.left;
                } else {
                    node_idx = node.right;
                }
            }
        }
        
        return sum / RF_NUM_TREES;
    }
};
