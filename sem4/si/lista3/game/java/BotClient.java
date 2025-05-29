import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class BotClient {
    public static void main(String[] args) {
        Socket serverSocket;
        BufferedReader in;
        PrintWriter out;

        String serverMessage;
        String playerMessage;
        boolean endGame;
        int player, msg, move;
        int depth;  // głębokość przeszukiwania bota

        if (args.length != 5) {
            System.out.println("Wrong number of arguments");
            System.out.println("Usage: java BotClient <server_ip> <server_port> <player_number> <secret> <depth>");
            System.exit(-1);
        }

        try {
            // Parametry połączenia
            String serverIp = args[0];
            int serverPort = Integer.parseInt(args[1]);
            player = Integer.parseInt(args[2]);
            String secret = args[3];
            depth = Integer.parseInt(args[4]);

            // Ustanowienie połączenia z serwerem
            serverSocket = new Socket(serverIp, serverPort);
            System.out.println("Socket created and connected successfully");

            in = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));
            out = new PrintWriter(serverSocket.getOutputStream(), true);

            // Odbiór powitalnego komunikatu
            char[] buffer = new char[16];
            int r = in.read(buffer);
            serverMessage = new String(buffer, 0, r).trim();

            // Wysyłanie numeru gracza i sekretu
            playerMessage = player + " " + secret;
            out.print(playerMessage);
            out.flush();

            // Inicjalizacja planszy
            Board.setBoard();
            endGame = false;

            // Pętla gry
            while (!endGame) {
                // Odbiór wiadomości od serwera
                r = in.read(buffer);
                serverMessage = new String(buffer, 0, r).trim();
                msg = Integer.parseInt(serverMessage);
                move = msg % 100;
                msg = msg / 100;

                // Jeżeli przeciwnik wykonał ruch
                if (move != 0) {
                    Board.setMove(move, 3 - player);
                }

                // Nasza tura lub kontynuacja gry
                if (msg == 0 || msg == 6) {
                    // Wywołanie Bot.move z głębokością
                    move = Bot.move(player, depth);
                    Board.setMove(move, player);

                    // Wysyłanie ruchu
                    playerMessage = Integer.toString(move);
                    out.print(playerMessage);
                    out.flush();
                } else {
                    // Koniec gry
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

            // Zamknięcie połączenia
            serverSocket.close();

        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
            System.exit(-1);
        }
    }
}
