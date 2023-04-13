#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "card.hpp"
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H
#include <string>

namespace ariel{}

class Player{
    std::string name;
    vector <Card> taken;
    vector <Card> stack;
    int rate_win;

public:
    int get_rate_win() const;
    void set_rate_win();
    Player(std::string name);
    int stacksize() const;
    int cardesTaken() const;
    string get_name() const;
    void add_to_stack(Card & temp);
    void add_to_taken(Card & temp);
    void print_taken()const;
    Card& pop();

};
#endif
