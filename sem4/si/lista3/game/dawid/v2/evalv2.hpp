#pragma once

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stdarg.h>

#include "winning_boards.h"
#include "blocking_boards.h"


// 6 do 3 przegrał z blokowaniem linii bez rogów
// 
std::unordered_map<long long,int> globalEval = std::unordered_map<long long,int>{};

/*
    Zmiany od v1:
    1. nieaktualne, bo a. (Alfa-beta dopiero od 2 w dół, może uda się odnaleźć lepsze szybciej)
        a. w zasadzie obawiam się że do tego wystarczy beta < alfa, więc zmiana może być do usunięcia
            i. ponieważ gdy beta < alfa, to nie będzie ucinać równych, czyli może znajdzie szybszą wygraną
    2. Nowe pola:
        a. rogi za 2 pkt
        b. blokowanie całej linii xd za 5 dodatkowych (do 2*samo-blokowanie punktów)
        c. Sprawdzenie "do przodu", czy mamy jakąś wygrywającą możliwość, a przeciwnik ma to pole zablokowane!
            i. za 50 * 50 punktow xd
    3. Naprawienie błędu rejestrowania niektórych zablokowanych pól podwójnie
    4. Zmiana wybierania wartości na podstawie głębokości
        a. nie powinniśmy patrzeć na ujemny dodatni, tylko na to czy poprawia poprzedni ruch, czy też nie
        b. dodam tak samo handlowanie tego co niżej (najszybsza metoda na wygrana, zamiast INF_LOSE > INF_WIN)
    
    TODO:
    4. Znajdowanie najszybszej metody na wygrana, zamiast znajdowanie zawsze INF_LOSE, bo teraz wyjdzie
                INF_lose za 7 tur > INF_win za 2 tury
        a ja bym wolał, żeby tutaj była jednak głębokość wzięta pod uwagę!
    5. Być może zmiana myślenia po którejś (15?) turze, ale w zasadzie nie wiem, czy to aż taki dobry pomysł w sumie
*/

long long g_evals = 0;
long long turn = 0;
int lastMoveValue = 0;

static const int INF = 2000000;
// static const int INF_win = 999999; //zmienione, bo zeby nie przegrywac powinnismy preferowac, ze przeciwnik przegra niz wygrac
// static const int INF_lose = 1000001;


// przy zamianie uważać w kodzie na >=
static const int INF_win = 999999; //zmienione, bo zeby nie przegrywac powinnismy preferowac, ze przeciwnik przegra niz wygrac
static const int INF_lose = 1000001;
static const int INF_any = 900000;


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
    int debug_last_eval = 0;
    if (bit_winCheck(1)) return  INF_win;        // X wygrał
    if (bit_winCheck(2)) return -INF_win;        // O wygrał
    if (bit_loseCheck(1)) return -INF_lose;        // X przegrał
    if (bit_loseCheck(2)) return INF_lose;        // O przegrał
    
    reset_bitboard(blocked_o);
    reset_bitboard(blocked_x);
    
    // korzystac z innych ewaluacji jak jest wiecej
    // za kazde własne samo-blokowanie    [] X X []
    eval -= getBlockCount(1) * 45;
    debugPrint(10, 0, "x blocked %d\n", eval);
    debug_last_eval = eval;
    
    // za kazde samo-blokowanie przeciwnika
    eval += getBlockCount(2) * 45;
    debugPrint(10, 0, "o blocked %d\n", eval-debug_last_eval);
    debug_last_eval = eval;
    
    // za każdą możliwość ułożenia 4 z 1 brakiem
    eval += getWinCount(1) * 55;
    debugPrint(10, 0, "x win %d\n", eval-debug_last_eval);
    debug_last_eval = eval;
    
    // za każdą możliwość przeciwnika ułożenia 4 z 1 brakiem 
    eval -= getWinCount(2) * 55;
    debugPrint(10, 0, "o win %d\n", eval-debug_last_eval);
    debug_last_eval = eval;

    // // za każdą możliwość ułożenia 4 z 1 brakiem
    // eval += getForcedWinCount(1) * 100;
    // debugPrint(10, 0, "x forced win %d\n", eval-debug_last_eval);
    // debug_last_eval = eval;
    
    // // za każdą możliwość przeciwnika ułożenia 4 z 1 brakiem 
    // eval -= getForcedWinCount(2) * 100;
    // debugPrint(10, 0, "o forced win %d\n", eval-debug_last_eval);
    // debug_last_eval = eval;

    // za kazde X - - X w różnych konfiguracjach
    eval += getLesserWinCount(1) * 10 / 2; // pomniejszone bo zwraca wiecej
    debugPrint(10, 0, "x lesserwin %d\n", eval-debug_last_eval);
    debug_last_eval = eval;
    eval -= getLesserWinCount(2) * 10 / 2;
    debugPrint(10, 0, "o lesserwin %d\n", eval-debug_last_eval);
    debug_last_eval = eval;

    eval += getNiceCorners(1) * 2; // byc moze doprowadzi do głupich rozpoczęć!
    eval -= getNiceCorners(2) * 2;

    eval += getBlockedLanes(1) * 10;
    eval -= getBlockedLanes(2) * 10;

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
// Nie aktualizuje sam sobie wartości najlepszego poprzedniego ruchu
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
    // if (bit_winCheck(1)) return  Result{ INF_win, Move{-1, -2, 0}, depth};         // X wygrał
    // if (bit_winCheck(2)) return  Result{-INF_win, Move{-2, -2, 0}, depth};         // O wygrał
    // if (bit_loseCheck(1)) return  Result{-INF_lose, Move{-3, -2, 0}, depth};       // X przegrał
    // if (bit_loseCheck(2)) return Result{ INF_lose, Move{-4, -2, 0}, depth};        // O przegrał
    
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
        setGlobalMove(m.i, m.j, player);
        long long h2 = hashBoard();
        auto it2 = tt.find(h2);
        if (it2 != tt.end()) {
            m.hint = it2->second;
        } else {
            m.hint = evaluateBoard(h2);
        }
        undoGlobalMove(m.i, m.j);
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
        setGlobalMove(m.i, m.j, player);
        // if(depth > maxDepth-1) {
            debugPrint(2, maxDepth-depth, "%c calculating if other moved: %d at current bestValue=%d bestDepth=%d\n", maxPlayer ? 'X' : 'O', m.i*10+m.j+11, bestValue, bestDepth);
        // }
        Result r = minimax(depth - 1, !maxPlayer, alpha, beta, tt, maxDepth);
        undoGlobalMove(m.i, m.j);

        if(r.value == INF_win || r.value == INF_lose) r.value = INF_any;
        if(r.value == -INF_win || r.value == -INF_lose) r.value = -INF_any;

        if (maxPlayer) {
            if (r.value > bestValue) {
                bestValue = r.value;
                bestMove = m;
                bestDepth = r.depth;
            } else if(r.value == bestValue) {
                // jeżeli pogarszamy swoją sytuację, chcemy to zrobić jak najwolniej
                // jeżeli ją polepszamy => jak najszybciej
                if(lastMoveValue > bestValue) {
                    if(r.depth < bestDepth) {
                        // opóźniamy przegrywanie
                        // wolniej - głębiej
                        debugPrint(2, maxDepth-depth, "X best changed by depthMin %d %d%d %d prev=%d %d\n", r.value, (r.move.i+1), r.move.j+1, r.depth, bestMove.i*10+bestMove.j+11, bestDepth);
                        bestDepth = r.depth;
                        bestValue = r.value;
                        bestMove = m;
                    }
                } else if(r.depth > bestDepth) {
                    // przyspieszamy wygrywanie i remisowanie z poprzednim ruchem
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
                if(lastMoveValue < bestValue) {
                    // nasz poprzedni ruch był mniejszy (lepszy dla O) niż ten najlepszy do tej pory - spowalniamy przegrywanie
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
        if (beta < alpha) {
            debugPrint(2, maxDepth-depth, "O best pruned by alfa=%d beta=%d value=%d %d%d %d\n", alpha, beta, r.value, (r.move.i+1), r.move.j+1, r.depth);
            break;
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