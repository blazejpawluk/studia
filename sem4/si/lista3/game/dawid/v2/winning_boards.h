#pragma once
#include "bitboards.hpp"

// szuka wszystkich 4 gdzie 3 są gracza, a 1 jest pusta
// jezeli to puste pole jest oznaczone jako zablokowane to je odblokowuje
inline int getWinCount(int player) {
    bitboard_t* player_board = (player == 1) ? &x_board : &o_board;
    bitboard_t* blocked_player = (player == 1) ? &blocked_x : &blocked_o;
    bitboard_t* blocked_enemy = (player == 1) ? &blocked_o : &blocked_x;

    int count = 0;
    int player_count, empty_count;
    for (int i = 0; i < 28; ++i) {
        bitboard_t mask = win_masks[i];
        player_count = __builtin_popcount(*player_board & mask);
        empty_count  = __builtin_popcount(empty_board & mask);
        if (player_count == 3 && empty_count == 1) {
            // // ma w sobie 1 na tym 1 pustym polu
            // bitboard_t empty_in_line = empty_board & mask;
            // // jeśli to pole jest zablokowane, odblokuj je
            // if (*blocked_player & empty_in_line) {
            //     // jezeli było zablokowane to je odblokowujemy
            //     *blocked_player &= ~empty_in_line;
            // }

            bitboard_t empty_in_line = empty_board & mask;
            // jeśli to pole jest zablokowane, dodaj 50
            // printf("forced win\n");
            // print_mask(empty_in_line);
            // print_mask(*blocked_enemy);
            if ((*blocked_enemy) & empty_in_line) {
                // printf("forced win2\n");
                // dla X mamy 1-1 = 0 => parzysty lepszy, bo nasz ruch
                // dla O mamy 2-1 = 1 => nieparzysty
                if(pawnCount % 2 == player-1) {
                    count += 50;
                } else {
                    count += 5;
                }
            }
            count++;
        }
    }
    return count;
}

// szuka wszystkich 4, gdzie 3 sa gracza 1 puste i zablokowane dla przeciwnika
// juz po sprawdzeniu w getWinCount(), czy przypadkiem przeciwnik nie moze tam wygrac
// uzywa tez pawnCount do sprawdzenia, czy to sytuacja, w której wygrywamy, czy jednak za wolno
//             O
// tzn.      X - X X
//             O
//             O
// jezeli nastepny ruch jest X, (pawnCount parzysty), to będzie to znaczenie lepsza ewaluacja dla X
// i symetrycznie
inline int getForcedWinCount(int player) {
    bitboard_t* player_board = (player == 1) ? &x_board : &o_board;
    bitboard_t* blocked_player = (player == 1) ? &blocked_x : &blocked_o;
    bitboard_t* blocked_enemy = (player == 1) ? &blocked_o : &blocked_x;
    int count = 0;
    for (int i = 0; i < 28; ++i) {
        bitboard_t mask = win_masks[i];
        int player_count = __builtin_popcount(*player_board & mask);
        int empty_count  = __builtin_popcount(empty_board & mask);
        if (player_count == 3 && empty_count == 1) {
            // znajdź puste pole w tej linii
            bitboard_t empty_in_line = empty_board & mask;
            // jeśli to pole jest zablokowane, dodaj 50
            // printf("forced win\n");
            // print_mask(empty_in_line);
            // print_mask(*blocked_enemy);
            if ((*blocked_enemy) & empty_in_line) {
                // printf("forced win2\n");
                // dla X mamy 1-1 = 0 => parzysty lepszy, bo nasz ruch
                // dla O mamy 2-1 = 1 => nieparzysty
                if(pawnCount % 2 == 1-player) {
                    count += 5;
                } else {
                    count += 1;
                }
            }
        }
    }
    return count;
} 


// dobra pozycja to też
// X b - X
// i
// X b b X
// więc będą premiowane
// podzielic przez 2 na koncu czy cos
// bo zwraca 2x wiecej sytuacji
// zeby moc premiowac 1 blok za pół
int getLesserWinCount(int player) {
    bitboard_t* player_board = (player == 1) ? &x_board : &o_board;
    bitboard_t* blocked_player = (player == 1) ? &blocked_x : &blocked_o;
    bitboard_t* blocked_enemy = (player == 1) ? &blocked_o : &blocked_x;
    int count = 0;
    int blockedCount = 0;
    for (int i = 0; i < 28; i++) {
        bitboard_t mask = win_masks[i];
        int player_count = __builtin_popcount(*player_board & mask);
        int empty_count  = __builtin_popcount(empty_board & mask);
        if (player_count == 2 && empty_count == 2) {
            // mozliwe jest
            // X - - X
            // X - X -
            // - X - X
            // X X - -
            // - X X - 
            // jezeli to sa te srodkowe
            // reczne sprawdzenie
            if ((board[win[i][1][0]][win[i][1][1]] == 0) && (board[win[i][2][0]][win[i][2][1]] == 0)) {
                blockedCount = 0;
                count += check_position(*blocked_enemy, win[i][1][0], win[i][1][1]);
                count += check_position(*blocked_enemy, win[i][2][0], win[i][2][1]);
                count+=2;
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