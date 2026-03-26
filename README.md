# Pokerface

**Version:** v2024.06.10
**© 2024 PretendGINEERS. All Rights Reserved.**

A networked, multi-client Texas Hold'em poker game written in **C**, built around a **client–server architecture** using **POSIX TCP/IP sockets** and **POSIX threads (pthreads)**. The server manages concurrent client sessions and authoritative game state, while the client delivers an interactive GUI-based interface.

---

## Authors

| Name |
|---|
| Mharlo Borromeo |
| Jack Lu |
| Calvin Nguyen |
| Mervin Nguyen |
| Peter Nguyen |
| Derek Tang |

**Last Modified:** December 22, 2025

---

## Architecture Overview

Pokerface is split into two independently compiled binaries communicating over TCP/IP:

```
+-----------------+        TCP/IP        +--------------------------+
|  pokerclient    | <------------------> |      pokerserver         |
|  (GUI layer)    |                      |  (game engine + state)   |
+-----------------+                      +--------------------------+
                                                   |
                                         pthread per client session
                                                   |
                                        +----------+-----------+
                                        |  Shared game state   |
                                        |  (mutex-protected)   |
                                        +----------------------+
```

**Server** — Accepts incoming client connections on a designated port, spawns a `pthread` per session, and maintains authoritative game state across all connected players. Synchronizes shared state (hand evaluation, pot, player turns) using mutex locks to prevent race conditions under concurrent access.

**Client** — Connects to the server via TCP, sends player actions (fold, call, raise), and renders game state through a GUI-based interface. Receives server-pushed state updates and reflects them in real time.

---

## Key Technical Areas

- **Socket Programming** — Full-duplex TCP communication using POSIX `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, and `recv()` syscalls
- **Multithreading** — `pthread_create()` per client connection with `pthread_mutex_t` synchronization for shared game state
- **Game State Machine** — Server-side FSM managing betting rounds (pre-flop, flop, turn, river, showdown), player action validation, and pot management
- **Hand Evaluation Engine** — C-based card ranking logic covering all standard hand rankings
- **GUI Client** — Interactive client interface decoupled from game logic via message-passing over the socket layer
- **Unit & System Testing** — Modular test coverage for game logic, connection handling, and state transitions

---

## Build & Installation

> **Note:** Follow the full setup steps in the `INSTALL` file before building.

```bash
# Extract archive
gtar -xvf Poker_Beta.tar.gz

# Build all targets (server + client)
make all
```

All compiled binaries are output to `bin/`.

---

## Running the Application

### Start the Server

```bash
./bin/pokerserver <port>
```

Valid port range: **10080–10089**

```bash
# Example
./bin/pokerserver 10080
```

### Connect a Client

```bash
./bin/pokerclient <hostname> <port>
```

```bash
# Example — connect to local server
./bin/pokerclient localhost 10080

# Example — connect to remote server
./bin/pokerclient 192.168.1.10 10080
```

Multiple clients can connect concurrently — the server spawns a new thread per connection.

---

## Project Structure

```
├── src/
│   ├── client.c
│   ├── client.h
│   ├── constants.h
│   ├── gamelogic.c
│   ├── gamelogic.h
│   ├── gui.c
│   ├── gui.h
│   ├── gui_images/
│   │   ├── CGM_BG.jpeg
│   │   ├── CMM_BG.jpeg
│   │   ├── PokerIcon.png
│   │   └── playing_cards/
│   │       └── [card images...]
│   ├── pokerclient.c
│   ├── pokerclient_core.c
│   ├── pokerclient_core.h
│   ├── pokerserver.c
│   ├── pokerserver_core.c
│   ├── pokerserver_core.h
│   ├── server.c
│   ├── server.h
│   ├── structures.h
│   ├── unit_test_client.c
│   ├── unit_test_gamelogic.c
│   ├── unit_test_gui.c
│   └── unit_test_server.c
├── bin/
│   ├── gui_images/
│   │   ├── CGM_BG.jpeg
│   │   ├── CMM_BG.jpeg
│   │   ├── PokerIcon.png
│   │   └── playing_cards/
│   │       └── [card images...]
│   ├── pokerclient
│   ├── pokerserver
│   └── unit_test_gui
├── doc/
│   ├── Poker_SoftwareSpec.pdf
│   └── Poker_UserManual.pdf
├── Makefile
├── INSTALL
├── README.md
└── COPYRIGHT
```

---

## Protocol

Client–server communication uses a structured message protocol over TCP. Messages encode player actions and server-pushed state updates, keeping the client stateless and the server the single source of truth for all game state.

---

## Known Limitations / Future Work

- Thread-per-connection model does not scale beyond dozens of concurrent clients; an event-driven model (`epoll`/`select`) would be more appropriate at scale
- No TLS, all communication is plaintext over TCP; suitable for LAN/localhost environments only
- Reconnection on dropped connections is not currently supported




