# 🃏 Poker-GameCPP

A comprehensive Poker (Texas Hold'em) game written in C++. This project is built on a client-server architecture, allowing for multiplayer network gameplay. It currently features a command-line interface (CLI), with plans to implement a graphical user interface (GUI) using OpenGL in the future.

⚠️ **Project Status: Work in Progress (WIP)**
This project is currently in active development. The current setup supports playing via the text-based console interface.

---

## ✨ Key Features (Current State)
* **Game Modes**: 
  * **Singleplayer**: Play offline against up to 3 computer-controlled bots.
  * **Multiplayer**: Host your own server or join an existing one over the network.
* **Interactive Console Menu**: Easily configure your game sessions (set custom nicknames, starting chips, number of players/bots and port).
* **Client-Server Architecture**: Separation of game logic (server) and user interface (client). The client application can spin up a server internally on a separate thread when hosting a game.
* **Network Communication**: Uses TCP sockets handled by the `Boost.Asio` library.
* **Data Serialization**: Network game states are serialized to JSON format using `nlohmann/json`.
* **Texas Hold'em Engine**: Full poker game logic, including deck shuffling, card dealing, betting rounds, and winning hand evaluation.

---

## 🛠 Requirements & Dependencies
To compile and run this project, you will need:
* A compiler that supports **C++20**.
* **Visual Studio** (the project uses `.sln` and `.vcxproj` files).
* External libraries (included as Git submodules):
  * [Boost](https://www.boost.org/) (specifically the Asio module)
  * [nlohmann/json](https://github.com/nlohmann/json)

---

## 🚀 Getting Started (Build & Run)

### 1. Clone the Repository
Since this project uses external libraries as submodules, you must clone the repository with the `--recursive` flag:
```
git clone --recursive https://github.com/iSheek/Poker-GameCPP
```
(If you have already cloned the project without this flag, run git submodule update --init --recursive inside the project directory).

### 2. Build the Project
Open the PokerGameCPP.sln file in Visual Studio.

Select your desired configuration (e.g., Debug or Release / x64).

Build the entire solution (Build -> Build Solution). This will compile everything needed.

### 3. Run the Game
You will be greeted by an interactive menu where you can choose:
- Start Singleplayer: Play offline against bots.
- Start Multiplayer (Host): Starts a local server on your specified port and connects you to it automatically. Other players can then join using your IP address.
- Join Multiplayer: Connect to a friend's hosted game by entering their IP address and port.

## 🗺️ Roadmap
- Replace the console interface with a graphical interface using OpenGL.
- Support a bigger number of players.
- Improve handling of network disconnections and errors.
