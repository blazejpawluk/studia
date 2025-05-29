#!/usr/bin/env bash

# serwer
gnome-terminal -- bash -c '
  cd "$(dirname "$0")"
  ./game/game_server 127.0.0.1 4444
  exec bash
'

# klient
gnome-terminal -- bash -c '
  cd "$(dirname "$0")"
  ./game/game_client 127.0.0.1 4444 1 client
  exec bash
'
# lsoowy bot
gnome-terminal -- bash -c '
  # katalog docelowy na .class
  mkdir -p bin
  # kompilacja
  javac -d bin java/*.java
  # uruchomienie
  java -cp bin BotClient 127.0.0.1 4444 2 bot 5
  exec bash
'