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
    int mount_of_draws;
    int draw_rate;
    int num_Turns;
    vector<string> turns;
    string winner;
private:
    void set_winner();

    int how_big(Card & card1,Card & card2,vector<Card>& pile,string & str);

    vector<Card> shuffle();

    void deal_cards_start(vector <Card>& pile);
    void deal_cards(vector <Card>& pile);

    void add_pile(vector <Card>& pile,Player *player);




public:
    void rund_to_string(string &str,Card & card_a,Card& card_b,Player* winner);
    Game(Player & player_a, Player & player_b);

    void playTurn();

    void printLastTurn()const;

    void playAll();

    void printWiner()const;

    void printLog()const;

    void printStats()const;
    };
#endif
