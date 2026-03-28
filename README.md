# 🃏 Poker-GameCPP

A comprehensive Poker (Texas Hold'em) game written in C++. This project is built on a client-server architecture, allowing for multiplayer network gameplay. It currently features a command-line interface (CLI), with plans to implement a graphical user interface (GUI) using OpenGL in the future.

⚠️ **Project Status: Work in Progress (WIP)**
This project is currently in early development. The current setup supports exactly **2 players** locally connecting and playing via the text-based console interface.

---

## ✨ Key Features (Current State)
* **Client-Server Architecture**: Separation of game logic (server) and user interface (client).
* **Network Communication**: Uses TCP sockets handled by the `Boost.Asio` library.
* **Data Serialization**: Network messages and game states are serialized to JSON format using `nlohmann/json`.
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

Build the entire solution (Build -> Build Solution). This will compile the static library, the server, and the client projects.

### 3. Run the Game
Due to the network architecture, you must start the applications in the correct order:

Run the PokerServerCPP application. The server will start listening on port 1234 and wait for players.

Run the first instance of PokerClientCPP.

Run the second instance of PokerClientCPP.

Once the server detects 2 connected players, it will automatically start the game, allocate the starting chips (1000 chips per player), and broadcast the table state to the clients.

## 🗺️ Roadmap
- Replace the console interface with a graphical interface using OpenGL.
- Support a dynamic number of players (e.g., 2 to 8 players at a single table).
- Improve handling of network disconnections and errors.
