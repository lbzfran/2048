
# 2048 Game
https://github.com/user-attachments/assets/76e482db-043b-468f-922b-174be560db8c

A simple experimental clone of 2048 developed in C.

## Dependencies
* make
* gcc
* raylib (on linux distros)

## Install

To compile, run make:

`make`

To play, run the resulting source file:

`./2048`

or for windows:

`./2048.exe`

## Goals
Main goals:
* [x] finish logic side of 2048.
* [x] create an actual screen.

Once I get more practice with raylib, I will return to fix the
following things (or any more issues I might find):

* [ ] Automatic centering of the board
* [ ] Automatic resizing of the board depending on screen size
* [ ] Simple menu (main menu, pause)
* [ ] Timer
* [ ] Game Over, with restart available
* [ ] Adjustable difficulty (manual or automatically adapt to game state)

## Notes
I hacked a way to allow compilation in both windows and linux.

The goal was just to get some practice in creating visuals,
and I've largely succeeded, minus some potential tweaking and
optimizations.

