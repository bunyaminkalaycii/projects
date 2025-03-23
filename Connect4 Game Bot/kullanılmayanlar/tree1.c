#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//A node for generic tree
// typedef struct TreeNode
// {
//     int num_children;           // Number of children (-1 if it is not yet known, 0 if it is a terminal node i.e. board is full)
//     GameState *game_state;
//     struct TreeNode **children; // Array of child nodes
// } TreeNode;

// Given a game state, return a tree node

TreeNode *init_node(GameState *gs){
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->num_children = -1;
    node->children = NULL;
    node->game_state = gs;
    return node;
}

// Given a game state, construct the tree up to the given depth using the available moves for each node
// Returns the root node
// You can assume that depth >= 2
TreeNode *init_tree(GameState *gs, int depth){
    TreeNode* newTree = init_node(gs);
    for(int i = 1; i < depth; i++){
        expand_tree(newTree);
    }
    return newTree;
}

// Frees the tree
void free_tree(TreeNode *root){
    if (root==NULL) return;
    if(root->children != NULL){
        for(int i = 0; i < root->num_children; i++){
            free_tree(root->children[i]);
        }
    }
    free_game_state(root->game_state);
    free(root->children);
    free(root);
}

// Expand all leaf nodes of the tree by one level
void expand_tree(TreeNode *root){
    TreeNode* ptr = root;
    if (ptr->children != NULL) {
        for(int i = 0; i < ptr->num_children; i++){
            expand_tree(ptr->children[i]);
        }
    } else {
        if(get_game_status(root->game_state) != IN_PROGRESS)
            return;
        bool* moves = (bool*)malloc(sizeof(bool)*ptr->game_state->width);
        if (moves == NULL) {
            printf("Memory allocation failed for moves array!\n");
            return;
        }
        for (int i = 0; i < ptr->game_state->width; i++){
            moves[i]= false;
        }
        ptr->num_children = available_moves(ptr->game_state, moves);
        ptr->children = (TreeNode**)malloc(sizeof(TreeNode*)*ptr->num_children);
        if (ptr->children == NULL) {
            printf("Memory allocation failed for children array!\n");
            free(moves);
            return;
        }
        for(int i = 0, j = 0; i < ptr->game_state->width; i++){
            if(moves[i]){
                ptr->children[j] = init_node(make_move(ptr->game_state, i));
                j++;
            }
        }
        free(moves);
    }
}

// Count the number of nodes in the tree 
int node_count(TreeNode *root){
    int count = 1;
    if(root->children != NULL){
        for(int i = 0; i < root->num_children; i++){
            count += node_count(root->children[i]);
        }
    }
    return count;
}

// Print the tree for debugging purposes (optional)
// void print_tree(TreeNode *root, int level) {
//     if (root == NULL) return;

//     // Mevcut düğümü yazdır
//     for (int i = 0; i < level; i++) printf("  "); // Seviyeye göre girinti
//     printf("Node at level %d: %p\n", level, (void *)root);

//     // Çocukları yazdır
//     if (root->children != NULL) {
//         for (int i = 0; i < root->num_children; i++) {
//             print_tree(root->children[i], level + 1);
//         }
//     }
// }
