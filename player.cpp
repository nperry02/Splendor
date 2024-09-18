/*
 * player.cpp
 * Written by: Nate Perry
 * Date created: 12/1/2022
 * Purpose: Implement the methods for the player class
 *
 */

#include "player.h"


//player constuctor
//initilizes everything 
Player::Player(){

    //inililizes the amount and discount of each gem
    for (int i = 0; i<6; i++){
        discount[i]=0;
        amount[i]=0;
    }
    //amount of prestige he has
    prestige = 0;

    //the reserve cards
    reserve[0] = nullptr;
    reserve[1] = nullptr;
    reserve[2] = nullptr;
}

Player::~Player() {
  for (int i = 0; i < 3; i++) {
    delete reserve[i];
  }
  //delete this->Player;
}

//discount getter
//input: the index of the gem
//returns the amount of discount for the input gem
int Player::getDiscount(int i){
    return discount[i];
}

//gem getter
//input: the index of the gem
//returns the amount of gems player of each a color
int Player::getGemCount(int i){
    return amount[i];
}

//prestige getter
//input none
//returns the amount of prestige the player has
int Player::totalPrestige(){
    return prestige;
}

//reserve getter
//input: index of the reverse card
//returns a pointer to that card 
Card *Player::getReserve(int i){
    return reserve[i];
    //return nullptr;
}

//addGetCount
//input: index of gem, amount of gems added
//adds amount of gems to gem index
void Player::addGemCount(int i, int number){
    amount[i]= amount[i] + number;
}

//subGetCount
//input: index of gem, amount of gems subtracted
//subs amount of gems to gem index
void Player::subGemCount(int i, int number){
    amount[i]= amount[i] - number;
}

//setReserve
//input: card pointer
//adds card pointer to reserve
void Player::setReserve(Card *c){
    for(int i = 0; i < 3; i++){
        if(reserve[i]==nullptr){
            reserve[i]=c;
            break;
        }
    }
}

//setReserveAt
//input: card pointer and index
//puts card into reserve at specified index
void Player::setReserveAt(Card *c, int i){
    reserve[i]=c;
}

//setDiscount
//input index of gem discounted
//adds a discount to specified gem
void Player::setDiscount(int i){
    discount[i]= discount[i]+1;
}

//addPrestige
//int number of prestige
//adds prestige to player
void Player::addPrestige(int i){
    prestige=prestige+i;
}
