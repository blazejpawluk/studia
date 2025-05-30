#pragma once
#include "bitboards.hpp"

// int getBlockCount(int player) {
//     int count = 0;
//     bitboard_t* blocked = (player==1) ? &blocked_o : &blocked_x;
//     for (int i = 0; i < 48; i++) {
//         if(board[lose[i][0][0]][lose[i][0][1]] == player) {
//             if((board[lose[i][1][0]][lose[i][1][1]] == 0) &&
//                 (board[lose[i][2][0]][lose[i][2][1]] == player)) {
//                 count+= !check_position(*blocked, lose[i][1][0], lose[i][1][1]);
//                 set_position(*blocked, lose[i][1][0], lose[i][1][1]);
//             } else if((board[lose[i][1][0]][lose[i][1][1]] == player) &&
//                     (board[lose[i][2][0]][lose[i][2][1]] == 0)) {
//                 count+= !check_position(*blocked, lose[i][2][0], lose[i][2][1]);
//                 set_position(*blocked, lose[i][2][0], lose[i][2][1]);
//             }
//         } else {
//             if((board[lose[i][0][0]][lose[i][0][1]] == 0) &&
//             (board[lose[i][1][0]][lose[i][1][1]] == player) &&
//             (board[lose[i][2][0]][lose[i][2][1]] == player)) {
//                 count+= !check_position(*blocked, lose[i][0][0], lose[i][0][1]);
//                 set_position(*blocked, lose[i][0][0], lose[i][0][1]);
//             }
//         }
//     }
//     return count;
// }

// zlicza zablokowane pola i ustawia je w blocked bitboardzie
inline int getBlockCount(int player) {
    bitboard_t* player_board = (player == 1) ? &x_board : &o_board;
    bitboard_t* blocked_player = (player == 1) ? &blocked_x : &blocked_o;
    bitboard_t mask;

    int count = 0;
    int player_count, empty_count;
    for (int i = 0; i < 48; i++) {
        mask = lose_masks[i];
        player_count = __builtin_popcount(*player_board & mask);
        empty_count  = __builtin_popcount(empty_board & mask);
        if (player_count == 2 && empty_count == 1) {
            // ma w sobie 1 na tym 1 pustym polu
            bitboard_t empty_in_line = empty_board & mask;
            // jeśli to pole nie jest zablokowane
            if (!(*blocked_player & empty_in_line)) {
                *blocked_player |= empty_in_line;
                count++;
                // printf("found blocked %d %d\n", lose[i][0][0], lose[i][0][1]);
            }
        }
    }
    return count;
}

/*
getBlockCount:
        if ((board[lose[i][0][0]][lose[i][0][1]] == 0) &&
             (board[lose[i][1][0]][lose[i][1][1]] == player) &&
             (board[lose[i][2][0]][lose[i][2][1]] == player)) {
            count++;
        } else if ((board[lose[i][0][0]][lose[i][0][1]] == player) &&
                (board[lose[i][1][0]][lose[i][1][1]] == 0) &&
                (board[lose[i][2][0]][lose[i][2][1]] == player)) {
            count++;
        } else if ((board[lose[i][0][0]][lose[i][0][1]] == player) &&
                (board[lose[i][1][0]][lose[i][1][1]] == player) &&
                (board[lose[i][2][0]][lose[i][2][1]] == 0)) {
            count++;
        }

*/