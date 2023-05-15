#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"
#include "card.hpp"
using namespace std;

namespace ariel{}

#ifndef GAME_H
#define GAME_H

#include "player.hpp"

class Game {
    Player *player_1;   
    Player *player_2;   
    int mount_of_draws; // Total number of draws
    int draw_rate;      // In some rounds there was a draw
    int num_Turns;      // Total number of turns played
    vector<string> turns;   // Vector containing string representation of each round 
    string winner;      

private:


    void set_winner();  

    // Checks which card wins and moves the cards accordingly
    int Which_card_win(Card & card1,Card & card2,vector<Card>& pile,string & str);

    // Shuffle the cards before dealing
    vector<Card> shuffle();

    // Deals cards to players at the start of the game
    void deal_cards_start(vector <Card>& pile);

    // Deals cards to players when the last round ends in a draw
    void deal_cards_end_draw(vector <Card>& pile);

    // When a player wins a round the cards are passed to him
    void add_pile_to_player(vector <Card>& pile,Player *player);

public:

    Game(Player & player_a, Player & player_b);
    

    // Convert the rund information to string
    void rund_to_string(string &str,Card & card_a,Card& card_b,Player* winner);


    // Print the string representation of the last round played
    void printLastTurn() const;

    // Play the game until a winner is determined
    void playAll();
    
    
    int get_num_turns() const;
    

    int get_mount_of_draws() const;
    
    
    void playTurn();
    

    void printWiner() const;


    void printLog() const;

    // Print game statistics
    void printStats() const;
};

#endif
