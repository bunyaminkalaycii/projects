// DO NOT MODIFY eval_game_state FUNCTION
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "connect4.h"
#include "game_bot.h"

// Returns the evaluation for the given game state
// Assigns 1000 if player 1 wins currently, -1000 if player 2 wins currently, 0 if draw, and a value between -1000 and 1000 otherwise
// Already implemented for you, do not change it
void eval_game_state(GameState *gs)
{
    GameStatus status = get_game_status(gs);
    if (status == PLAYER_1_WIN)
    {
        gs->evaluation = 1000;
        return;
    }
    else if (status == PLAYER_2_WIN)
    {
        gs->evaluation = -1000;
        return;
    }
    else if (status == DRAW)
    {
        gs->evaluation = 0;
        return;
    }

    // Count the number of 3s in a row
    int player_1_3 = 0;
    int player_2_3 = 0;

    // Count the number of 2s in a row with an extra space around
    int player_1_2 = 0;
    int player_2_2 = 0;

    // Check horizontal
    for (int i = 0; i < gs->height; i++)
    {
        for (int j = 0; j <= gs->width - 3; j++)
        {
            int index = i * gs->width + j;

            int x_count = (gs->board[index] == 'X') + (gs->board[index + 1] == 'X') + (gs->board[index + 2] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + 1] == 'O') + (gs->board[index + 2] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + 1] == '_') + (gs->board[index + 2] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    // Check vertical
    for (int i = 0; i <= gs->height - 3; i++)
    {
        for (int j = 0; j < gs->width; j++)
        {
            int index = i * gs->width + j;
            // if (gs->board[index] != '_' &&
            //     gs->board[index] == gs->board[index + gs->width] &&
            //     gs->board[index] == gs->board[index + 2 * gs->width])
            // {
            //     if (gs->board[index] == 'X')
            //         player_1_3++;
            //     else
            //         player_2_3++;
            // }

            int x_count = (gs->board[index] == 'X') + (gs->board[index + gs->width] == 'X') + (gs->board[index + 2 * gs->width] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + gs->width] == 'O') + (gs->board[index + 2 * gs->width] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + gs->width] == '_') + (gs->board[index + 2 * gs->width] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int i = 0; i <= gs->height - 3; i++)
    {
        for (int j = 0; j <= gs->width - 3; j++)
        {
            int index = i * gs->width + j;
            // if (gs->board[index] != '_' &&
            //     gs->board[index] == gs->board[index + gs->width + 1] &&
            //     gs->board[index] == gs->board[index + 2 * gs->width + 2])
            // {
            //     if (gs->board[index] == 'X')
            //         player_1_3++;
            //     else
            //         player_2_3++;
            // }

            int x_count = (gs->board[index] == 'X') + (gs->board[index + gs->width + 1] == 'X') + (gs->board[index + 2 * gs->width + 2] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + gs->width + 1] == 'O') + (gs->board[index + 2 * gs->width + 2] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + gs->width + 1] == '_') + (gs->board[index + 2 * gs->width + 2] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int i = 0; i <= gs->height - 4; i++)
    {
        for (int j = gs->width - 1; j >= 2; j--)
        {
            int index = i * gs->width + j;
            // if (gs->board[index] != '_' &&
            //     gs->board[index] == gs->board[index + gs->width - 1] &&
            //     gs->board[index] == gs->board[index + 2 * gs->width - 2])
            // {
            //     if (gs->board[index] == 'X')
            //         player_1_3++;
            //     else
            //         player_2_3++;
            // }

            int x_count = (gs->board[index] == 'X') + (gs->board[index + gs->width - 1] == 'X') + (gs->board[index + 2 * gs->width - 2] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + gs->width - 1] == 'O') + (gs->board[index + 2 * gs->width - 2] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + gs->width - 1] == '_') + (gs->board[index + 2 * gs->width - 2] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    gs->evaluation = 10 * (player_1_3 - player_2_3) + 3 * (player_1_2 - player_2_2);
}

// First calls the eval_game_tree function then returns the best move for the player using minimax algorithm
// Returns the index of the best move among the children of the root, not among the all moves
int best_move(TreeNode* root){
    eval_game_tree(root);
    int eval = 0;
    if(root->game_state->next_turn){ //1'ken min
        eval = get_min(root);
    } else { //0'ken max
        eval = get_max(root);
    }
    int bestie;
    for(int i = 0; i < root->num_children; i++){
        if(eval == root->children[i]->game_state->evaluation){
            bestie = i;
            break;
        }
    }
    return bestie;
}

// Part of the minimax algorithm
// (Do not call this function directly, it supposed to be called by best_move function)
int get_max(TreeNode* node){
    if(node->children == NULL){
        return node->game_state->evaluation;
    }
    int max_value = -1001;
    for (int i = 0; i < node->num_children; i++) {
        int child_value = get_min(node->children[i]);
        if (child_value > max_value) {
            max_value = child_value;
        }
    }
    node->game_state->evaluation = max_value;
    return max_value;
}

// Part of the minimax algorithm
// (Do not call this function directly, it supposed to be called by best_move function)
int get_min(TreeNode* node){
    if(node->children == NULL){
        return node->game_state->evaluation;
    }
    int min_value = 1001;
    for(int i = 0; i < node->num_children; i++){
        int child_value = get_max(node->children[i]);
        if(child_value < min_value){
            min_value = child_value;
        }
    }
    node->game_state->evaluation = min_value;
    return min_value;
}

// Given a root node, evaluate all the leaf nodes using eval_game_state function
void eval_game_tree(TreeNode *root){
    if (root->children != NULL){
        for(int i = 0; i < root->num_children; i++){
            eval_game_tree(root->children[i]);
        }
    } else {
    eval_game_state(root->game_state);
    }
}