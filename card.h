/*
 * card.h
 * Written by: Nate Perry
 * Date created: 12/1/2022
 * Purpose: declare the methods for the Card class
 *
 */

 #ifndef CARD_H
 #define CARD_H
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

class Card {
public:

    //constructor
    Card(int prestige, string discount, int w, int r, int p, int b, int g);

    ~Card();


    // Getters
    string getGemColor();
    int getDiscountIndex();
    int getPrestige();
    int getPrice(int g);

private:
    //private variables
    //price of each gem
    int cost[5];
    //prestige of card
    int prestige;
    //the color of gem discount
    string discount;
};

#endif