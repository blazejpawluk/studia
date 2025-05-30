#pragma once

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stdarg.h>

#include "./winning_boards.h"
#include "./blocking_boards.h"

std::unordered_map<long long,int> globalEval = std::unordered_map<long long,int>{};

long long g_evals = 0;

static const int INF = 2000000;
// static const int INF_win = 999999; //zmienione, bo zeby nie przegrywac powinnismy preferowac, ze przeciwnik przegra niz wygrac
// static const int INF_lose = 1000001;

// przy zamianie uważać w kodzie na >=
static const int INF_win = 999999; //zmienione, bo zeby nie przegrywac powinnismy preferowac, ze przeciwnik przegra niz wygrac
static const int INF_lose = 1000001;


int debugLevel = 0;
int debug_hash_minimax = 0;
int debug_hash_eval = 0;


// nie poddawac sie

// minimax visited states - 5
void debugPrint(int level, int depth, const char* message, ...) {
    if (level > debugLevel) return;

    for(int i=0;i<depth;i++) {
        printf("\t");
    }

    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);
}

// kazda wartosc z tablicy na 2 bitach, bo mamy tylko 0, 1, 2  00 01 10 i ew. 11 na cos
// 25 miejsc na 2 bitach kazde to 50 bitow, wiec uzywamy 64 i zostaje 14 bitow na cos
long long hashBoard() {
    long long hash = 0;
    for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++) {
            hash = hash << 2;
            hash += board[i][j] & 0x3;
        }
    }
    return hash;
}

// ewaluacja jest zawsze dla X
int evaluateBoard(long long precalculatedHash) {
    auto tt = globalEval.find(precalculatedHash);
    if(tt != globalEval.end()) {
        return globalEval[precalculatedHash];
    }

    int eval = 0;
    if (winCheck(1)) return  INF_win;        // X wygrał
    if (winCheck(2)) return -INF_win;        // O wygrał
    if (loseCheck(1)) return -INF_lose;        // X przegrał
    if (loseCheck(2)) return INF_lose;        // O przegrał
// korzystac z innych ewaluacji jak jest wiecej
    // za kazde własne samo-blokowanie    [] X X []
    // old_getBlockCount - stare z bugiem, poniewaz zmieniałem nowa na bruk buga
    eval -= old_getBlockCount(1) * 15;
    
    // za kazde samo-blokowanie przeciwnika
    eval += old_getBlockCount(2) * 15;

    // za każdą możliwość ułożenia 4 z 1 brakiem
    eval += getWinCount(1) * 50;
    
    // za każdą możliwość przeciwnika ułożenia 4 z 1 brakiem 
    eval -= getWinCount(2) * 50;

    // za kazde X - - X w różnych konfiguracjach
    eval += getLesserWinCount(1) * 10;
    eval -= getLesserWinCount(2) * 10;

    globalEval[precalculatedHash] = eval;
    return eval;
}


struct Move { int i = -1, j = -1, hint; };

struct Result {
    int value;
    int depth;
    Move move;
    Result(int v = 0, Move m = Move(), int depth = 0) : value(v), move(m), depth(depth) {}
};


// W TRANSPOSITION MATRIX GLEBOKOSC MA ZNACZENIE
// BO MOZE SIE OKAZAC ZE JAKAS POZYCJA BYLA WOLNIEJ ALBO SZYBCIEJ?
Result minimax(int depth,
            bool maxPlayer,
            int alpha,
            int beta,
            std::unordered_map<long long,int>& tt,
            int maxDepth) {
    long long hash = hashBoard();
    int eval = evaluateBoard(hash);
    if (depth == 0) return Result{eval, Move{}, 0};

    // 1) sprawdzenie w transposition table
    auto it = tt.find(hash);
    if (it != tt.end()) {
        debug_hash_minimax++;
        return Result{it->second, Move{}, depth};
    }

    
    if(eval <= -INF_win|| eval >= INF_win) return Result{eval, Move{-1, -1, eval}, depth};
    // //     // 2) warunki terminalne: zwycięstwo/przegrana/pusty poziom
    // if (winCheck(1)) return  Result{ INF_win, Move{-1, -2, 0}, depth};         // X wygrał
    // if (winCheck(2)) return  Result{-INF_win, Move{-2, -2, 0}, depth};         // O wygrał
    // if (loseCheck(1)) return  Result{-INF_lose, Move{-3, -2, 0}, depth};       // X przegrał
    // if (loseCheck(2)) return Result{ INF_lose, Move{-4, -2, 0}, depth};        // O przegrał
    
    debugPrint(5, depth, "=============================================================\n", depth, hash);
    debugPrint(5, depth, "Minimax stwierdzil ze: v=d d=%d hash=%llo\n", depth, hash);
    if(debugLevel == 5) printBoard(depth);

    int player = maxPlayer ? 1 : 2;
    int bestValue = maxPlayer ? -INF-5 : INF+5;
    int bestDepth = -INF;
    Move bestMove;

    // 3) wygeneruj wszystkie możliwe ruchy
    std::vector<Move> moves;
    moves.reserve(25);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == 0) {
                moves.push_back({i, j, 0});
            }
        }
    }

    // 4) dla lepszego porządku ruchów – podaj „hint” z tabeli (jeśli istnieje)
    for (auto &m : moves) {
        board[m.i][m.j] = player;
        long long h2 = hashBoard();
        auto it2 = tt.find(h2);
        if (it2 != tt.end()) {
            m.hint = it2->second;
        } else {
            m.hint = evaluateBoard(h2);
        }
        board[m.i][m.j] = 0;
        // jezeli nastepny ruch jest na pewno wygrywajacy to go zwracamy
        if(maxPlayer && m.hint == INF_win) {
            if(depth == maxDepth) 
            {
                // a dzieki temu zawsze znajdował insta wina jezeli potrzeba
                debugPrint(3, depth, "\nX found insta-win\n");
            }
            return Result(m.hint, m, depth);
        } else if(!maxPlayer && m.hint == -INF_win) {
            if(depth == maxDepth)
            {
                // dzieki temu bot bedzie zawsze blokowal
                debugPrint(3, depth, "\nO found insta-win\n");
            }
            debugPrint(2, maxDepth-depth, "Left by O-insta-win\n");
            return Result(m.hint, m, depth);
        }
    }
    // sortowanie według „hint” (maksymalizujący od dużych, minimalizujący od małych)
    if (maxPlayer) {
        std::sort(moves.begin(), moves.end(),
                  [](auto &a, auto &b){ return a.hint > b.hint; });
    } else {
        std::sort(moves.begin(), moves.end(),
                  [](auto &a, auto &b){ return a.hint < b.hint; });
    }

    int temp = 0;
    for (auto &m : moves) {
        temp++;
        debugPrint(5, depth, "moves: %d h=%d ", (m.i+1)*10+m.j+1, m.hint);
        if(temp % 5 == 0) debugPrint(5, depth, "\n");
    }
    debugPrint(5, depth, "\n");
    for (auto &m : moves) {
        board[m.i][m.j] = player;
        // if(depth > maxDepth-1) {
            debugPrint(2, maxDepth-depth, "%c calculating if other moved: %d at current bestValue=%d bestDepth=%d\n", maxPlayer ? 'X' : 'O', m.i*10+m.j+11, bestValue, bestDepth);
        // }
        Result r = minimax(depth - 1, !maxPlayer, alpha, beta, tt, maxDepth);
        board[m.i][m.j] = 0;

        if (maxPlayer) {
            if (r.value > bestValue) {
                bestValue = r.value;
                bestMove = m;
                bestDepth = r.depth;
            } else if(r.value == bestValue) {
                // jezeli mamy lepiej dla O to chcemy go opóźnić
                // zał, że maxDepth=5
                // np.   -15 na głębokości 3 (za 2 tury)  ** - chcemy wybrać to, wolniej przegrywamy (3 < 4)
                // np.   -15 na głębokości 4 (za 1 ture)
                // ale jezeli jest lepiej dla X to
                // np.   15 na głębokości 3 (za 2 tury)  
                // np.   15 na głębokości 4 (za 1 ture)   ** - chcemy wybrać to, szybciej jest nam lepiej (4 > 3)
                // wiec dla ujemnych wartości szukamy min(depth), a dodatnich max(depth)
                if(r.value < 0) {
                    if(r.depth < bestDepth) {
                        // wolniej - głębiej
                        debugPrint(2, maxDepth-depth, "X best changed by depthMin %d %d%d %d prev=%d %d\n", r.value, (r.move.i+1), r.move.j+1, r.depth, bestMove.i*10+bestMove.j+11, bestDepth);
                        bestDepth = r.depth;
                        bestValue = r.value;
                        bestMove = m;
                    }
                } else if(r.depth > bestDepth) {
                    bestDepth = r.depth;
                    bestValue = r.value;
                    bestMove = m;
                    debugPrint(2, maxDepth-depth, "X best changed by depthMax %d %d%d %d\n", r.value, (r.move.i+1), r.move.j+1, r.depth);
                }
            }
            alpha = std::max(alpha, bestValue);
        } else {
            if (r.value < bestValue) {
                bestValue = r.value;
                bestMove = m;
                bestDepth = r.depth;
            } else if(r.value == bestValue) {
                // lustrzane odbicie tego na górze
                if(r.value > 0) {
                    if(r.depth < bestDepth) {
                        bestDepth = r.depth;
                        bestValue = r.value;
                        bestMove = m;
                        debugPrint(2, maxDepth-depth, "O best changed by depthMax %d %d%d %d\n", r.value, (r.move.i+1), r.move.j+1, r.depth);
                    }
                } else if(r.depth > bestDepth) {
                    bestDepth = r.depth;
                    bestValue = r.value;
                    bestMove = m;
                    debugPrint(2, maxDepth-depth, "O best changed by depthMin %d %d%d %d\n", r.value, (r.move.i+1), r.move.j+1, r.depth);
                }
            }
            beta = std::min(beta, bestValue);
        }
        if(depth < maxDepth-2) {
            if (beta < alpha) {
                debugPrint(2, maxDepth-depth, "O best pruned by alfa=%d beta=%d value=%d %d%d %d\n", alpha, beta, r.value, (r.move.i+1), r.move.j+1, r.depth);
                break;
            }
        }
    }

    // 6) zapamiętaj w tabeli i zwróć wynik
    tt[hash] = bestValue;
    // if(depth > maxDepth-2)
    {
        debugPrint(2, maxDepth-depth, "%c chose: %d %d at bestDepth=%d\n", maxPlayer ? 'X' : 'O', bestValue, bestMove.i*10+bestMove.j+11, bestDepth);
    }
    return Result{bestValue, bestMove, bestDepth};
}