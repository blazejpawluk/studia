@echo off

REM Serwer
start "Game Server" cmd /k ^
  "cd /d %~dp0 && game\game_server.exe 127.0.0.1 4444"

@REM REM Klient
@REM start "Game Client" cmd /k ^
@REM   "cd /d %~dp0 && game\game_client.exe 127.0.0.1 4444 1 client"

@REM REM Losowy bot
@REM start "Random Bot Client" cmd /k ^
@REM   "cd /d %~dp0 && game\game_random_bot.exe 127.0.0.1 4444 2 client"

REM Bot
start "Bot Client1" cmd /k ^
  "cd /d %~dp0 && javac -d bin java\*.java && java -cp bin BotClient 127.0.0.1 4444 2 bot 7"

@REM REM Bot
@REM start "Bot Client2" cmd /k ^
@REM   "cd /d %~dp0 && javac -d bin java\*.java && java -cp bin BotClient 127.0.0.1 4444 2 bot 5"

REM Dawid
start "Bot Dawid" cmd /k ^
  "cd /d %~dp0 && game\dawid3.exe 127.0.0.1 4444 1 dawid 7"
