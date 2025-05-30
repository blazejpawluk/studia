// int getBlockCount(int player) {
//     int count = 0;
//     // dla x, 1-1=0 => fałsz => blocked_x
//     bitboard_t* blocked = (player==1) ? &blocked_o : &blocked_x;
//     for (int i = 0; i < 48; i++) {
//         if(board[lose[i][0][0]][lose[i][0][1]] == player) {
//             if((board[lose[i][1][0]][lose[i][1][1]] == 0) &&
//                 (board[lose[i][2][0]][lose[i][2][1]] == player)) {
//                 count+= !is_blocked(*blocked, lose[i][1][0], lose[i][1][1]);
//                 set_blocked(*blocked, lose[i][1][0], lose[i][1][1]);
//             } else if((board[lose[i][1][0]][lose[i][1][1]] == player) &&
//                     (board[lose[i][2][0]][lose[i][2][1]] == 0)) {
//                 count+= !is_blocked(*blocked, lose[i][2][0], lose[i][2][1]);
//                 set_blocked(*blocked, lose[i][2][0], lose[i][2][1]);
//             }
//         } else {
//             if((board[lose[i][0][0]][lose[i][0][1]] == 0) &&
//             (board[lose[i][1][0]][lose[i][1][1]] == player) &&
//             (board[lose[i][2][0]][lose[i][2][1]] == player)) {
//                 count+= !is_blocked(*blocked, lose[i][0][0], lose[i][0][1]);
//                 set_blocked(*blocked, lose[i][0][0], lose[i][0][1]);
//             }
//         }
//     }
//     return count;
// }
// 48 * 2 * 2 * 3 operacji we najgorszym przypadku a w średnim w zasadzie 48 * 3
int old_getBlockCount(int player) {
    int count = 0;
    for (int i = 0; i < 48; i++) {
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