import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.time.Instant;
import java.util.Random;

public class RandomBot {
    public static int randomMove(int player, Random generator) {
        int n = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (Board.board[i][j] == 0)
                    n++;
        n = generator.nextInt(n);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (Board.board[i][j] == 0) {
                    if (n == 0) {
                        return (i + 1) * 10 + (j + 1);
                    } else {
                        n--;
                    }
                }
            }
        }
        throw new IllegalStateException("No valid moves available");
    }

    public static void main(String[] args) {
        Socket serverSocket;
        BufferedReader in;
        PrintWriter out;

        String serverMessage;
        String playerMessage;
        boolean endGame;
        int player, msg, move;

        Random generator = new Random(Instant.now().toEpochMilli());

        if (args.length != 4) {
            System.out.println("Wrong number of arguments");
            System.out.println("Usage: java RandomBoot <server_ip> <server_port> <player_number> <secret>");
            System.exit(-1);
        }

        try {
            serverSocket = new Socket(args[0], Integer.parseInt(args[1]));
            System.out.println("Socket created and connected successfully");

            in = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));
            out = new PrintWriter(serverSocket.getOutputStream(), true);

            char[] buffer = new char[16];
            int r = in.read(buffer);
            serverMessage = new String(buffer, 0, r).trim();

            playerMessage = args[2] + " " + args[3];
            out.print(playerMessage);
            out.flush();

            Board.setBoard();
            endGame = false;
            player = Integer.parseInt(args[2]);

            while (!endGame) {
                r = in.read(buffer);
                serverMessage = new String(buffer, 0, r).trim();
                msg = Integer.parseInt(serverMessage);
                move = msg % 100;
                msg = msg / 100;

                if (move != 0) {
                    Board.setMove(move, 3 - player);
                }

                if (msg == 0 || msg == 6) {
                    move = randomMove(player, generator);
                    Board.setMove(move, player);

                    playerMessage = Integer.toString(move);
                    out.print(playerMessage);
                    out.flush();
                } else {
                    endGame = true;
                    switch (msg) {
                        case 1:
                            System.out.println("You won.");
                            break;
                        case 2:
                            System.out.println("You lost.");
                            break;
                        case 3:
                            System.out.println("Draw.");
                            break;
                        case 4:
                            System.out.println("You won. Opponent error.");
                            break;
                        case 5:
                            System.out.println("You lost. Your error.");
                            break;
                        default:
                            System.out.println("Game ended with code: " + msg);
                    }
                }
            }

            serverSocket.close();

        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(-1);
        }
    }
}
