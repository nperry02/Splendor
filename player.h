/*
 * player.h
 * Written by: Nate Perry
 * Date created: 12/1/2022
 * Purpose: declare the methods for the player class
 *
 */

 #ifndef PLAYER_H
 #define PLAYER_H
#include <string>
#include <cstdlib>
#include <iostream>
#include "card.h"
using namespace std;

class Player{
public:
    //constructor
    Player();

    ~Player();

    //getter functions
    int getDiscount(int i);
    int getGemCount(int i);
    int totalPrestige();
    Card *getReserve(int i);

    //setter functions
    void addGemCount(int i, int number);
    void subGemCount(int i, int number);
    void setReserve(Card *c);
    void setReserveAt(Card *c, int i);
    void setDiscount(int i);
    void addPrestige(int i);

private:
    //private variables
    
    //discount of gems
    int discount[5];
    //amount of gems per color
    int amount[6];
    //prestige amount
    int prestige;
    Card *reserve[3];
};

#endif