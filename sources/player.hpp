#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "card.hpp"
#include <vector>
namespace ariel{}

#ifndef PLAYER_H
#define PLAYER_H



class Player{
    std::string name;
    vector<Card> taken; // vector of cards taken by the player
    vector<Card> stack; // vector of cards currently in the player's stack
    int rate_win; // win rate of the player
public:
    Player(std::string name);

    int get_rate_win() const;
    int stacksize() const;
    int cardesTaken() const;
    string get_name() const;

    // print player's taken cards
    void print_taken() const;

    // pop top card from stack
    Card& pop();

    // set win rate
    void set_rate_win();

    // add card to stack
    void add_to_stack(Card& temp);

    // add card to taken
    void add_to_taken(Card& temp);
};


#endif
