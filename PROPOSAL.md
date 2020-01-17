# Poker: A Multiplayer Game

### Team Members
* Jackson Zou
* Jeff Lin
* Jun Tao Lei

### Class Period 4

### Broad Description
This is a multiplayer poker game that can be played between players on the same network. The poker will be based on Texas hold’em, but may not necessarily adhere to its entire ruleset. Players can bet with virtual currency, and each player will start with a predetermined minimum amount.

### Dependencies
None

---

## Proposal

### Statement
The premise of this project is to create a multiplayer poker game that can be played between players on the same network. The host server will be run on the computer of the player that initializes a session of poker, and every player will connect to that host. The poker will be based on Texas hold’em, but may not necessarily adhere to its entire ruleset. Players can bet with virtual currency, and each player will start with a predetermined minimum amount. 

### Key Concepts
* Networking
* Processes
* Semaphores
* Pipes

### Technical Design
Each instance on a player’s machine will have a poker game instance, a segment of shared memory, and a network communication program. These programs will be forked by a parent program. The user will interact with a poker game through the game instance. After the user completes his/her turn, the game instance will write the user’s move to the network communication program through a pipe. The network communication program will talk to the array of clients connected based on their index on the array through sockets. After this, the network communication program will send an indicator to tell one of the clients to send back the move of the user on that client. The client will write to the client’s game instance to allow that player to make his/her move through a pipe. After the player makes his move, the game state will move up to the network communication program like the host. Then, the network communication program will send its game state to the server, which will send it to all the other clients connected. Then, the server will indicate to the next client to make his/her move based on the next index, or back to player 1 as it cycles back. This will happen until all players have made their moves. This cycle continues until a player has won, at which point the server will send a message to all its clients that the game has ended and terminate all existing connections to that server. Each client can also have the option to disconnect during the game session. After the client disconnects or terminates, a kill signal will be sent to the game instance to end the process. 

### Algorithms/Data Structures
The program will utilize an array to organize the client sockets connected to the server. The server and the client communicates in a first-in-first-out manner to some extent. There will be a fd_set of socket descriptors to be used in combination with select(). A pseudo-random number generator algorithm will be used to generate a pseudo-random sequence of poker cards to be used in the game as it can be fast to generate but may reproduce a similar sequence due to the seed used. Selection sort can be used to sort poker hands by suit and rank. A linked list of card structs can be used to keep track of a hand in order that the player receives it.

### Gameplay/Game Interface
1. Possible Moves (may be limited based on game state)
    * Check - Pass if unopened for bets 
    * Raise/Call - Increase the current bet or match another player’s bet 
    * Fold - Give up the hand and current pot
2. Cards 
    * Players will only be able to see their own two cards and the cards on the field
    * Game will determine the hand’s strength 
3. Gameplay
    * During turn: (read/write)
      ```
      All possible moves available to player will be shown 
      They will pick one of the possible moves
      Semaphores will be used here
      ```
    * Not during turn: (read only)
      ```
      Opponents moves will be shown
      They can view their own hand and pot by typing in command
      ```
 
### Roles
* Jackson Zou - Inter Process Communication for Each Game Client
* Jeff Lin - Game Logic/User Interface for Texas Hold’em Lite
* Jun Tao Lei - Networking Between Clients

### Timetable (TENTATIVE)
1. Game Logic/User Interface for Texas Hold’em Lite (Due 01/(08-10)/20)
    * Finalize the game design choice
    * Use terminal text
    * Emit game state
2. Inter Process Communication for Each Game Client (Due 01/(10-13)/20)
    * Wait for update on shared memory
    * Consume said update
    * Package data
3. Networking Between Clients (Due 01/(10-13)/20)
    * Take packaged data
    * Send to each client
    * Emit message to the next player
4. Debug for the previous three parts (Due 01/17/20)


