# Poker: A Multiplayer Game

### Team Members
* Jackson Zou
* Jeff Lin
* Jun Tao Lei

### Class Period 4

### Broad Description
This is a multiplayer poker game that can be played between players on the same network. The poker will be based on Blackjack, but may not necessarily adhere to its entire ruleset. All players are dealt with a new card each turn until the players either reach 21 or bust. All players win if the house(the host player) loses, and the last player standing will win. 

### Dependencies
* N/A

### Instructions
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
   
### Known Bugs
* A minor memory leak happens if the user choose to run the program as the host. We can't figure where the leak is from as we are pretty sure that we close all heap memory that we declare. We suspect that the memory leak when used between functions or that there is a pointer within a double or triple pointer that may not be freed.

### Statement
The premise of this project is to create a multiplayer poker game that can be played between players on the same network. The host server will be run on the computer of the player that initializes a session of poker, and every player will connect to that host. The poker will be based on Texas hold’em, but may not necessarily adhere to its entire ruleset. Players can bet with virtual currency, and each player will start with a predetermined minimum amount. 

### Key Concepts
* Networking
* Working with files
* Allocating memory
* Processes

### Technical Design
Each instance on a player’s machine be either a server or client. These programs will be forked by a parent program. The user will interact with a poker game through the game instance. After the user completes his/her turn, the program will talk to the array of clients connected based on their index on the array through sockets. After this, the client will write to the client’s game instance to allow that player to make his/her move. After the player makes his move, the program will send its game state to the server, which will send it to all the other clients connected. Then, the server will indicate to the next client to make his/her move based on the next index, or back to player 1 as it cycles back. This will happen until all players have made their moves. This cycle continues until a player has won, at which point the server will send a message to all its clients that the game has ended and terminate all existing connections to that server. Each client can also have the option to disconnect during the game session. 

### Algorithms/Data Structures
The program will utilize an array to organize the client sockets connected to the server. The server and the client communicates in a first-in-first-out manner to some extent. There will be a fd_set of socket descriptors to be used in combination with select(). The random sequence of cards can be generated with shuffling. 

### Gameplay/Game Interface
1. Possible Moves (may be limited based on game state)
    * Continue
    * Fold - Give up the hand and current pot
2. Cards 
    * Players will only be able to see all cards for the current turn.
3. Gameplay
    * During turn: Can either fold or continue
    * Not during turn: Cannot make any moves
 
### Roles
* Jackson Zou - Memory Allocation
* Jeff Lin - Game Logic/User Interface for Blackjack
* Jun Tao Lei - Networking Between Clients

### Timetable (TENTATIVE)
1. Game Logic/User Interface for Blackjack (Due 01/(08-10)/20)
    * Finalize the game design choice
    * Use terminal text
    * Emit game state
2. Memory Allocation (Due 01/(10-13)/20)
    * Player Heap Memory
    * Card Heap Memory
3. Networking Between Clients (Due 01/(10-13)/20)
    * Take packaged data
    * Send to each client
    * Emit message to the next player
4. Debug for the previous three parts (Due 01/17/20)



