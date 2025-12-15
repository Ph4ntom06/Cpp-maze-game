# C++ Maze Game

A terminal based maze game writen in C++ using ncurses.

# Description

The user watches the 2 characters(G and A) try to find their way to eachother. They can get trapped by randomly placed traps(T). They lose if, after 1000 moves they have not found eachother or, if they both get captured, or if the character with the key(K) gets trapped. Their only way of winning is finding eachother and escaping to the staircase(L)

# Features
- Random Maze
- Limited visibility for the 2 heroes
- Trap Mechanics
- Key and Exit mechanics
- Different movement algorithms for different circumstances

# How to compile
g++ *.cpp -lncurses -o game

# How to run 
./game map_name
