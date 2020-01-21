# Help

### Run Instructions
0. Clone the repository and change into the project directory.
   ```bash
   git clone https://github.com/jacksonzou123/poker.git
   cd poker
   ```
1. Compile with make
   ```bash
   make
   ```
2. Run the program as the host. Enter the player name as instructed. Connect any clients before typing "finish setup".
   ```bash
   ./Poker server 8000 ?
   ```
3. Run the program as the client. This command assumes the client is started on the same machine on the network. Enter the player name as instructed.
   ```bash
   ./Poker client 8000 127.0.0.1
   ```
4. Type "finish setup" into the host program.
5. Play the game! Type fold or quit to exit the program. Type c or continue to end your turn. The host or client will block until it is that player's turn

### Command Line Construction
* Usage: <server|client> <port> <CLIENT_ONLY:hostname>
  * <server|client>
    * User should input server or client as the second argument after ./Poker.
    * The option represents whether the user want to select server or client as their game instance.
  * <port>
    * This is the port that the user wants to connect or host the server on.
  * <CLIENT_ONLY:hostname>
    * This argument represents the hostname of the server (i.e. the IP address of the server).
    * This is not necessary for hosting.
