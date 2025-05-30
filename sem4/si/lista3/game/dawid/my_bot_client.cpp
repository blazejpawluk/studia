/****************************
Maciej Gębala (CC BY-NC 4.0)
Random Boot ver. 0.2
2025-04-13
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
// ******************************
// #include <unistd.h>
// #include <arpa/inet.h>

#ifdef _WIN32
#  include <winsock2.h>
#  include <ws2tcpip.h>
#  define close(sock) closesocket(sock)
#else
#  include <arpa/inet.h>
#  include <unistd.h>
#endif
// ******************************
#include <unordered_map>

#include "board.h"
#include "eval.hpp"


int main(int argc, char *argv[]) {
  // ******************************
  #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
      fprintf(stderr, "WSAStartup failed\n");
      return -1;
    }
  #endif
  // ******************************

  int server_socket;
  struct sockaddr_in server_addr;
  char server_message[16], player_message[16];

  bool end_game;
  int player, msg, move, depth;
  int currentTurn = 0;
  std::unordered_map<long long, int> transpositionTable;

  if ( argc != 6 ) {
    printf("Wrong number of arguments\n");
    return -1;
  }

  // Create socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if ( server_socket < 0 ) {
    printf("Unable to create socket\n");
    return -1;
  }
  printf("Socket created successfully\n");

  // Set port and IP the same as server-side
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // Send connection request to server
  if ( connect(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 ) {
    printf("Unable to connect\n");
    return -1;
  }
  printf("Connected with server successfully\n");

  // Receive the server message
  memset(server_message, '\0', sizeof(server_message));
  if ( recv(server_socket, server_message, sizeof(server_message), 0) < 0 ) {
    printf("Error while receiving server's message\n");
    return -1;
  }

  memset(player_message, '\0', sizeof(player_message));
  snprintf(player_message, sizeof(player_message), "%s %s", argv[3], argv[4]);
  // Send the message to server
  if ( send(server_socket, player_message, strlen(player_message), 0) < 0 ) {
    printf("Unable to send message\n");
    return -1;
  }

  setBoard();
  end_game = false;
  sscanf(argv[3], "%d", &player);
  depth = atoi(argv[5]);

  while ( !end_game ) {
    memset(server_message, '\0', sizeof(server_message));
    if ( recv(server_socket, server_message, sizeof(server_message), 0) < 0 ) {
      printf("Error while receiving server's message\n");
      return -1;
    }
    sscanf(server_message, "%d", &msg);
    move = msg%100;
    msg = msg/100;
    if ( move != 0 ) {
      setMove(move, 3-player);
      currentTurn++;
    }
    if ( (msg == 0) || (msg == 6) ) {
      printBoard();
      // printf("eval before: %d\n", evaluateBoard());
      
      if(currentTurn < 0) {
        // 53 - 1 | kolko - 2 | 21 - 3
        int moves[10] = {54, 0, 21, 0, 54};
        move = moves[currentTurn];
        setMove(move, player);
        currentTurn++;
      } else {
        transpositionTable = std::unordered_map<long long, int>{};
        Result r = minimax(depth, 2-player, -INF, INF, transpositionTable, depth);
        board[r.move.i][r.move.j] = player;
        // printf("eval of this board %d\n", evaluateBoard());
        printf("eval of minimax; eval = %d in %d moves from now | (9...9 - X win) (10...01 - O loss)\n", r.value, depth - r.depth);
        move = (r.move.i+1)*10 + r.move.j+1;
        currentTurn++;
      }

      memset(player_message, '\0', sizeof(player_message));
      snprintf(player_message, sizeof(player_message), "%d", move);
      if ( send(server_socket, player_message, strlen(player_message), 0) < 0 ) {
        printf("Unable to send message\n");
        return -1;
      }
     } else {
       end_game = true;
       switch ( msg ) {
         case 1 : printf("You won.\n"); break;
         case 2 : printf("You lost.\n"); break;
         case 3 : printf("Draw.\n"); break;
         case 4 : printf("You won. Opponent error.\n"); break;
         case 5 : printf("You lost. Your error.\n"); break;
      }
    }
  }

  // Close socket
  close(server_socket);

  #ifdef _WIN32
    WSACleanup();
  #endif

  return 0;
}
