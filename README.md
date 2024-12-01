# CPPJaipur
Implementation of the boardgame [Jaipur](https://store.asmodee.com/products/jaipur) in C++
as a programming exercise

## Author
Chase E. Stewart
written starting 11/29/2024

## Usage

### Compilation
```shell
$ make
g++ -Werror -Wall -std=c++20 -I. main.cpp cards.cpp gameboard.cpp tokens.cpp player.cpp stateMachine.cpp  -o cppjaipur
$
```

### Playing the Game
```shell
$ ./cppjaipur
```
