#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Bir düğüm başlatılır
TreeNode *init_node(GameState *gs) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        printf("[ERROR] Memory allocation failed for TreeNode.\n");
        exit(EXIT_FAILURE);
    }
    node->game_state = gs;
    node->num_children = -1; // Genişletilmedi
    node->children = NULL;
    return node;
}

// Ağacı verilen derinliğe kadar genişletir
TreeNode *init_tree(GameState *gs, int depth) {
    TreeNode *root = init_node(gs);
    for (int i = 1; i < depth; i++) { // Derinlik boyunca genişletme
        expand_tree(root);
    }
    return root;
}

// Ağacı serbest bırakır
void free_tree(TreeNode *root) {
    if (root == NULL) return;

    if (root->children != NULL) {
        for (int i = 0; i < root->num_children; i++) {
            free_tree(root->children[i]);
        }
    }

    free_game_state(root->game_state);
    free(root->children);
    free(root);
}

// Tüm yaprak düğümleri bir seviye genişletir
void expand_tree(TreeNode *root) {
    if (root == NULL) return;

    // Eğer düğüm genişletilmişse, çocukları genişlet
    if (root->children != NULL) {
        for (int i = 0; i < root->num_children; i++) {
            expand_tree(root->children[i]);
        }
    } else {
        // Eğer oyun bitmişse, genişletme yapılmaz
        if (get_game_status(root->game_state) != IN_PROGRESS) return;

        // Mevcut oyun durumuna göre hareketler belirlenir
        bool *moves = (bool *)malloc(sizeof(bool) * root->game_state->width);
        if (moves == NULL) {
            printf("[ERROR] Memory allocation failed for moves array.\n");
            return;
        }

        for (int i = 0; i < root->game_state->width; i++) {
            moves[i] = false; // Default olarak tüm hamleler geçersiz
        }

        root->num_children = available_moves(root->game_state, moves);
        if (root->num_children > 0) {
            root->children = (TreeNode **)malloc(sizeof(TreeNode *) * root->num_children);
            if (root->children == NULL) {
                printf("[ERROR] Memory allocation failed for children array.\n");
                free(moves);
                return;
            }

            for (int i = 0, j = 0; i < root->game_state->width; i++) {
                if (moves[i]) {
                    GameState *child_gs = make_move(root->game_state, i);
                    root->children[j++] = init_node(child_gs);
                }
            }
        } else {
            root->children = NULL;
            root->num_children = 0;
        }

        free(moves); // Bellek serbest bırakılır
    }
}

// Ağaçtaki toplam düğüm sayısını hesaplar
int node_count(TreeNode *root) {
    if (root == NULL) return 0;

    int count = 1; // Mevcut düğümü say
    if (root->children != NULL) {
        for (int i = 0; i < root->num_children; i++) {
            count += node_count(root->children[i]);
        }
    }
    return count;
}

// Ağacı debug için yazdırır (isteğe bağlı)
void print_tree(TreeNode *root, int level) {
    if (root == NULL) return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("Node (Children: %d)\n", root->num_children);

    for (int i = 0; i < root->num_children; i++) {
        print_tree(root->children[i], level + 1);
    }
}
