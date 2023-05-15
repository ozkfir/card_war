

#include <iostream>
using namespace std;
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"


#define NUMBER_GAMES 20


int main() {
//card class
    cout << endl;
    cout << endl;
    cout << "card class" << endl;
    cout << endl;
    cout << endl;

    // loop over card ranks and print card values
    for (int i = 1; i < 7; ++i) {
        Card card("diamonds", i);
        cout << card.get_card() << endl;
    }

    cout << endl;

    // loop over card ranks and print card num and kind
    for (int i = 7; i < 14; ++i) {
        Card card("diamonds", i);
        cout << card.get_num() << " of " << card.get_kind() << endl;
    }
    cout << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;

    //player & game classes
    cout << "player & game classes" << endl;
    cout << "Statistics of "<<NUMBER_GAMES<<" games" << endl;

    // initialize variables to store game statistics
    int Alice_win = 0;
    int Bob_win = 0;
    double avg_turns = 0;
    double A_avg_card = 0;
    double B_avg_card = 0;
    double A_avg_rate_win = 0;
    double B_avg_rate_win = 0;
    int A_max_taken = 0;
    int B_max_taken = 0;
    int A_min_taken = 70;
    int B_min_taken = 70;
    int mount_of_draws = 0;
    int game_end_tie = 0;
    int last_roud_ends_tie = 0;

// loop over NUMBER_GAMES games
    for (int i = 0; i < NUMBER_GAMES; ++i) {
        // create new players and game
        Player Alice("Alice");
        Player Bob("Bob");
        Game game(Alice, Bob);
        // play the game
        game.playAll();

        // update game statistics
        if (Alice.cardesTaken() > Bob.cardesTaken())
            Alice_win++;
        else {
            if (Alice.cardesTaken() < Bob.cardesTaken())
                Bob_win++;
            else
                game_end_tie++;
        }
        if (Alice.cardesTaken() > A_max_taken)
            A_max_taken = Alice.cardesTaken();

        if (Alice.cardesTaken() < A_min_taken)
            A_min_taken = Alice.cardesTaken();

        if (Bob.cardesTaken() > B_max_taken)
            B_max_taken = Bob.cardesTaken();

        if (Bob.cardesTaken() < B_min_taken)
            B_min_taken = Bob.cardesTaken();

        avg_turns += game.get_num_turns();
        A_avg_card += Alice.cardesTaken();
        B_avg_card += Bob.cardesTaken();
        A_avg_rate_win += Alice.get_rate_win();
        B_avg_rate_win += Bob.get_rate_win();
        last_roud_ends_tie+=game.get_num_turns()-Alice.get_rate_win()-Bob.get_rate_win();
        mount_of_draws+=game.get_mount_of_draws();
    }
    // calculate averages for game statistics
    avg_turns/=NUMBER_GAMES;
    A_avg_card/=NUMBER_GAMES;
    B_avg_card/=NUMBER_GAMES;
    A_avg_rate_win/=NUMBER_GAMES;
    B_avg_rate_win/=NUMBER_GAMES;

    // Print overall game statistics
    cout <<endl;
    cout << "                    " << "Alice" << "              " << "Bob" << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "avg_card        " << "     " << A_avg_card << "             " << B_avg_card << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "avg_rate_win    " << "     " << A_avg_rate_win << "             " << B_avg_rate_win << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "win             " << "     " << Alice_win << "                " << Bob_win << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "loss            " << "     " << Bob_win << "                " << Alice_win << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "max card taken  " << "     " << A_max_taken <<  "                " << B_max_taken << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "min card taken  " << "     " << A_min_taken << "                " << B_min_taken << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << endl;

    // Print additional game statistics
    cout<<"General statistics:"<<endl;
    cout << "avg_turns            " << avg_turns << endl;
    cout << "mount_of_draws       " << mount_of_draws << endl;
    cout << "game_end_tie         " << game_end_tie << endl;
    cout << "last_roud_ends_tie   " << last_roud_ends_tie << endl;
    cout << endl;


    cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" <<endl;
    cout << endl;

    // Create new players and game, play until one player's stack is empty, and print game log
    Player p1("Raz");
    Player p2("Shon");
    Game game(p1, p2);
    for (int i = 0; p1.stacksize() > 0; ++i) {
        game.playTurn();
    }
    cout<<"print the game:"<<endl;
    cout << endl;
    game.printLog();
    cout << endl;
    cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" <<endl;

    game.printStats();
    cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" <<endl;
    cout << endl;
    cout << "The last Turn:"<<endl;
    game.printLastTurn();
    cout << endl;
    cout << p1.get_name() << " cardesTaken:" << p1.cardesTaken() << endl;
    cout << p2.get_name() << " cardesTaken:" << p2.cardesTaken() << endl;

    game.printWiner();

}
