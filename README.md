![The logo of this project](data/Logo_Mental_Mahjong2.svg)

# Metal Mahjong 
This project is a Mahjong Game in C Raylib (still a work in progress). The object is too pratice C programming and to produce clear code (instead of the fastest one). This project is going to use the [mental poker](https://en.wikipedia.org/wiki/Mental_poker) algorithm to assure that no player can cheat and without any third party server.

# TODO (don't hesitate to contribute)
## Model of the Game (`model/`)
- [ ] don't crash when there is no more tile
- [x] remove the loaded of textures from `logic/tile.c` this should be in
visuals only
- [~] Write the logic of the game
    - [~] Yaku implementation
    - [ ] All the rules with tests
    - [ ] Complete game
    - [ ] Expert Program (AI) that computes probability
    - [ ] Trained AI from example games ...

## View (`view/`)
- [ ] Create an abstraction layer between the GUI and the code that does
something with it, to be able to test the GUI.
- [ ] Pretty print a game -> complete game in the terminal
- [ ] Client Side Rendering (Raylib)
- [ ] Try to compile with wasm

## Cryptographic(`crypto/`)
- [ ] Polynomial implementation (fast if possible)
- [ ] basic elgamal cryptographics primitive
- [ ] implement an idea of protocol to prepare the cards at the beggining

## Server-Client for Multiplayer(`client`)
- [ ] (De)Serialisation of message from the network.
- [~] write basic client for multiplayers
- [ ] use cryptographic primitive to have no server (only peer to peer)
- [ ] Test connection when the program is compiled with wasm
- [x] Implement basic server that connect people together.

## Controller of the game (manage view and model) (`controller/`)
- [x] basic game loop
- [ ] Handshake to define the map of tiles to cryptographic values
- [ ] Games logic in action with communication

## Put everything on a website(`website`)
- [ ] compile to wasm and make work a wasm executable compiled with wasm

# Dependency for Ubuntu
Here the different packages that have to be installed for the project to be
compiled. (This has been tested on Linux Mint for X11).
```
sudo apt-get install libxcursor-dev
sudo apt install libxrandr-dev
sudo apt-get install libxinerama-dev
sudo apt-get install libxi-dev
`perror("setsockopt(SO_REUSEADDR) failed");``
