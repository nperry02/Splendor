/*
 * game.h
 * CS11 Splendor
 * card.cpp
 * Written by: Nate Perry
 * Date created: 12/1/2022
 * Purpose: declares the methods for the game class
 *
 */
 

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <fstream>
#include <string>
#include "termfuncs.h"
#include "card.h"
#include "vector.h"
#include "player.h"
using namespace std;

class Game {
  public:
    //constructor
    Game(string filename, string play_nobles);

    ~Game();

    //main gameplay
    void playGame();

    //utility functions
    string indexToColor(int index);

  private:
    //drawing functions
    void drawBoard();
    void drawNoble(int vpos, int hpos, Card *c);
    void drawPlayer(int vpos, int hpos, Player *p);
    void drawDeck(int vpos, int hpos, string type);
    void drawCard(int vpos, int hpos, Card *c);
    void drawGem(int vpos, int hpos, string color);
    void clearBoard();

    //created functions
    void createVectors(string filename);
    void setUpGrid();
    bool queryLoop(bool player1_turn);
    bool p2Query(bool player1_turn);
    bool p3Query(bool player1_turn);
    bool rQuery(bool player1_turn);
    bool bQuery(bool player1_turn);
    bool brQuery(bool player1_turn);
    bool buyCardTransaction(Card *c, Player *p);
    bool checkGemsAndWinner(bool player1_turn, int *winPoint);
    void takeTwoGems(Player *p, int gem);
    void takeThreeGems(Player *p, int trioC[3]);
    void reserveCard(Player *p, string typ, int plce);
    bool buyCard(Player *p, string typ, int plce);
    bool buyReserve(Player *p,  int plce);
    bool checkGemCount(Player *p, bool player1_turn);
    int getGemIndex(string g);

    static const int BOARD_HEIGHT = 41;
    static const int BOARD_WIDTH = 120;
    static const int CARD_WIDTH = 13;
    static const int CARD_HEIGHT = 8;
    static const int CARD_ROWS = 3;
    static const int CARD_COLS = 4;
    static const int NUM_NOBLES = 3;
    static const int GEMS = 6;

    //nobles activated true/false
    bool play_nobles;

    //cards in play
    Card *grid[CARD_ROWS][CARD_COLS];

    //display
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    string board_color[BOARD_HEIGHT][BOARD_WIDTH];

    //Gem colors in the game
    string colors[GEMS];

    int gem_bank[GEMS];

    //declares deck/vectors for each deck
    Vector mines;
    Vector transport;
    Vector vendors;
    Vector nobles;

    //declares the 2 player class
    Player player_1;
    Player player_2;
};

#endif
