#pragma once
#include "board.h"

int getWinCount(int player) {
    int count = 0;
    for (int i = 0; i < 28; i++) {
        if ((board[win[i][0][0]][win[i][0][1]] == player) && (board[win[i][3][0]][win[i][3][1]] == player)){
            if((board[win[i][1][0]][win[i][1][1]] == 0) && (board[win[i][2][0]][win[i][2][1]] == player)) {
                count++;
            } else if((board[win[i][1][0]][win[i][1][1]] == player) && (board[win[i][2][0]][win[i][2][1]] == 0)) {
                count++;
            }
        }
    }
    return count;
}

// int getForcedWinCount(int player) {
//     int count = 0;
//     // dla x=1 1-1=0 => fałsz => drugi => blocked_o
//     bitboard_t* blocked = (player==1) ? &blocked_x : &blocked_o;
//     for (int i = 0; i < 28; i++) {
//         if ((board[win[i][0][0]][win[i][0][1]] == player) && (board[win[i][3][0]][win[i][3][1]] == player)){
//             if((board[win[i][1][0]][win[i][1][1]] == 0) && (board[win[i][2][0]][win[i][2][1]] == player)) {
//                 count += is_blocked(*blocked, win[i][1][0], win[i][1][1]) * 50;
//                 count++;
//             } else if((board[win[i][1][0]][win[i][1][1]] == player) && (board[win[i][2][0]][win[i][2][1]] == 0)) {
//                 count += is_blocked(*blocked, win[i][2][0], win[i][2][1]) * 50;
//                 count++;
//             }
//         }
//     }
//     return count;
// }


int getLesserWinCount(int player) {
    int count = 0;
    for (int i = 0; i < 28; i++) {
        if ( (board[win[i][0][0]][win[i][0][1]] == player) && 
            (board[win[i][1][0]][win[i][1][1]] == 0) &&
            (board[win[i][2][0]][win[i][2][1]] == 0) &&
            (board[win[i][3][0]][win[i][3][1]] == player) ) {
            count++;
        }
    }
    return count;
}


int getTriangles(int player) {
    int count = 0;
    int ok = 0;
    int down;
    int right;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] == player) {
                ok = 0;
                down = i + 2;
                right = j + 2;
                if(down > 4 || right > 4) {
                    continue;
                }
                if((board[down][j] == player)) {
                    ok++;
                }
                if((board[i][right] == player)) {
                    ok++;
                }
                if((board[down][right] == player)) {
                    ok++;
                }
                if(ok == 2) count++;
                if(ok == 3) count+=2;
            }
        }
    }
    return count;
}

int getNiceCorners(int player) {
    int counter = 0;
    counter += board[1][0] == player;
    counter += board[0][1] == player;

    counter += board[1][4] == player;
    counter += board[0][3] == player;
    
    counter += board[3][0] == player;
    counter += board[4][1] == player;

    counter += board[3][4] == player;
    counter += board[4][3] == player;
    return counter;
}

// zwraca ile linii zablokował player
// np. X - O O -
int getBlockedLanes(int player) {
    int counter = 0;
    for(int i=0;i<12;i++) {
        if(board[fives[i][0][0]][fives[i][0][1]] == player) {
            // 0 1 2 3 4
            // X - O O -
            counter += board[fives[i][2][0]][fives[i][2][1]] == (3 - player) &&
                        board[fives[i][3][0]][fives[i][3][1]] == (3 - player) && 
                        board[fives[i][1][0]][fives[i][1][1]] == 0 &&
                        board[fives[i][4][0]][fives[i][4][1]] == 0;
        } else if(board[fives[i][4][0]][fives[i][4][1]] == player) {
            // 0 1 2 3 4
            // - O O - X
            counter += board[fives[i][1][0]][fives[i][1][1]] == (3 - player) &&
                        board[fives[i][2][0]][fives[i][2][1]] == (3 - player) && 
                        board[fives[i][0][0]][fives[i][0][1]] == 0 &&
                        board[fives[i][3][0]][fives[i][3][1]] == 0;
        }
    }
    return counter;
}

/*
winCount:
        if ( (board[win[i][0][0]][win[i][0][1]] == player) &&
            (board[win[i][1][0]][win[i][1][1]] == 0) &&
            (board[win[i][2][0]][win[i][2][1]] == player) &&
            (board[win[i][3][0]][win[i][3][1]] == player) ) {
            count++;
        } else if ( (board[win[i][0][0]][win[i][0][1]] == player) &&
            (board[win[i][1][0]][win[i][1][1]] == player) &&
            (board[win[i][2][0]][win[i][2][1]] == 0) &&
            (board[win[i][3][0]][win[i][3][1]] == player) ) {
            count++;
        }
*/