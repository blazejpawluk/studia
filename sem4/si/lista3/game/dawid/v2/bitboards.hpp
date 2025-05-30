#pragma once
#include "../board.h"
#include <array>
#include <cstdint>
#include <cstdio>

typedef uint32_t bitboard_t;

bitboard_t x_board;
bitboard_t o_board;
bitboard_t empty_board;

bitboard_t blocked_x;
bitboard_t blocked_o;

int pawnCount;

void generate_all_masks();

void init_bitboards() {
    pawnCount = 0;
    x_board = 0u;
    o_board = 0u;
    empty_board = 0x1FFFFFFu;

    blocked_o = 0u;
    blocked_x = 0u;

    generate_all_masks();
}


inline void set_position(bitboard_t &bitboard, int i, int j) {
    bitboard |= (1u << (i * 5 + j));
}

inline void clear_position(bitboard_t &bitboard, int i, int j) {
    bitboard &= ~(1u << (i * 5 + j));
}

inline void reset_bitboard(bitboard_t &bitboard) {
    bitboard = 0u;
}

inline bool check_position(const bitboard_t &bitboard, int i, int j) {
    return bitboard & (1u << (i * 5 + j));
}

// ustawia playerowi ruch i 0 dla empty
// dodaje pionek
inline void setGlobalMove(int i, int j, int player) {
    set_position((player == 1) ? x_board : o_board, i, j);
    clear_position(empty_board, i, j);
    board[i][j] = player;
    pawnCount++;
}

// czysci pole dla x i o, oraz ustawia empty w tym miejscu
// odejmuje pionek
inline void undoGlobalMove(int i, int j) {
    clear_position(x_board, i, j);
    clear_position(o_board, i, j);
    set_position(empty_board, i, j);
    board[i][j] = 0;
    pawnCount--;
}

// zakładam, że masz już win[28][4][2], lose[48][3][2], fives[12][5][2] z board.h

bitboard_t win_masks[28];
bitboard_t lose_masks[48];
bitboard_t fives_masks[12];

void generate_all_masks() {
    // WIN
    for (int i = 0; i < 28; ++i) {
        bitboard_t mask = 0u;
        for (int j = 0; j < 4; ++j) {
            set_position(mask, win[i][j][0], win[i][j][1]);
        }
        win_masks[i] = mask;
    }
    // LOSE
    for (int i = 0; i < 48; ++i) {
        bitboard_t mask = 0u;
        for (int j = 0; j < 3; ++j) {
            set_position(mask, lose[i][j][0], lose[i][j][1]);
        }
        lose_masks[i] = mask;
    }
    // FIVES
    for (int i = 0; i < 12; ++i) {
        bitboard_t mask = 0u;
        for (int j = 0; j < 5; ++j) {
            set_position(mask, fives[i][j][0], fives[i][j][1]);
        }
        fives_masks[i] = mask;
    }
}

bool bit_winCheck(int player) {
    bitboard_t* player_board = (player == 1) ? &x_board : &o_board;
    for (int i = 0; i < 28; i++) {
        if ( (*player_board & win_masks[i]) == win_masks[i] ) {
            return true;
        }
    }
    return false;
}

bool bit_loseCheck(int player) {
    bitboard_t* player_board = (player == 1) ? &x_board : &o_board;
    for (int i = 0; i < 48; i++) {
        if ( (*player_board & lose_masks[i]) == lose_masks[i] ) {
            return true;
        }
    }
    return false;
}

// (opcjonalnie) Funkcja do wypisania masek w postaci binarnej
void print_mask(uint32_t mask) {
    for (int i = 0; i < 25; ++i) {
        printf("%c", (mask & (1u << i)) ? '1' : '0');
        if ((i + 1) % 5 == 0) printf("\n");
    }
    printf("\n");
}