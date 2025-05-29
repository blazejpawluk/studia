@echo off

REM 1) Serwer
start "Game Server" cmd /k ^
  "cd /d %~dp0 && game\game_server.exe 127.0.0.1 4444"

REM 2) Klient
start "Game Client" cmd /k ^
  "cd /d %~dp0 && game\game_client.exe 127.0.0.1 4444 2 client"

@REM REM 2) Losowy bot
@REM start "Random Bot Client" cmd /k ^
@REM   "cd /d %~dp0 && game\game_random_bot.exe 127.0.0.1 4444 2 client"

REM 3) Bot
start "Bot Client" cmd /k ^
  "cd /d %~dp0 && javac -d bin java\*.java && java -cp bin BotClient 127.0.0.1 4444 1 bot 5"
