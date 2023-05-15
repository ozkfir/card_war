#include <iostream>
#include "game.hpp"
#include <sys/time.h>
using namespace std;


using std::cout; using std::endl;

Game::Game(Player & p1,Player &p2):player_1(&p1),player_2(&p2),draw_rate(0),mount_of_draws(0),winner("still playing"),num_Turns(0),turns(){
    vector <Card> pile=shuffle();
    deal_cards_start(pile);
}

void Game::playTurn(){
    if(player_1==player_2){ throw std::invalid_argument("game nid two players");}
    if(player_1->stacksize()==0){throw std::invalid_argument("the game is over");}
    Card & t1=player_1->pop();
    Card & t2=player_2->pop();
    vector<Card> pile;
    string str="";
    int was_tie=0;
    pile.push_back(t1);
    pile.push_back(t2);
    while (Which_card_win(t1,t2,pile,str))
    {
        was_tie=1;
        if(player_1->stacksize()==0){
            break;}
        pile.push_back(player_1->pop());
        pile.push_back(player_2->pop());

        if(player_1->stacksize()==0){
            deal_cards_end_draw(pile);
            break;
        }
        t1=player_1->pop();
        t2=player_2->pop();
        pile.push_back(t1);
        pile.push_back(t2);

    }
    turns.push_back(str);
    if(was_tie)
        draw_rate++;
    if(player_1->stacksize()==0)
        set_winner();
    num_Turns++;
}



vector <Card> Game::shuffle()
{
    vector <Card> pile;
    for (int i = 1; i <=13 ; ++i) {
        Card card("spades",i);
        pile.push_back(card);
    }
    for (int i = 1; i <=13 ; ++i) {
        Card card("hearts",i);
        pile.push_back(card);
    }
    for (int i = 1; i <=13 ; ++i) {
        Card card("diamonds",i);
        pile.push_back(card);
    }
    for (int i = 1; i <=13 ; ++i) {
        Card card("clubs",i);
        pile.push_back(card);
    }
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    srand(time_now.tv_usec);
    for (int i=0; i<104 ;i++)
    {
        int j = rand() %52;
        swap(pile[(std::size_t)(i%52)], pile[(std::size_t)j]);
    }
    return pile;
}

int Game::Which_card_win(Card & t1,Card & t2,vector<Card>& pile,string &str){
    int a=t1.get_num();
    int b=t2.get_num();
    if(a==b){
        mount_of_draws++;
        rund_to_string(str,t1,t2,player_1);
        if(player_1->stacksize()==0){
            deal_cards_end_draw(pile);
            return 0;
        }
        return 1;
    }
    if((a==1 && b==2)||(b==1 && a!=2)||(a!=1 && a<b))
    {
        add_pile_to_player(pile,player_2);
        rund_to_string(str,t1,t2,player_2);
        player_2->set_rate_win();
    }
    else
    {
        add_pile_to_player(pile,player_1);
        rund_to_string(str,t1,t2,player_1);
        player_1->set_rate_win();
    }
    return 0;
}


void Game::add_pile_to_player(vector <Card>& pile,Player *player){
    for (int i = 0; i <pile.size() ; i++)
        player->add_to_taken(pile[(std::size_t)i]);
}



void Game::deal_cards_start(vector <Card>& pile){
    for (int i = 0; i <(pile.size()/2); i++) {
        player_1->add_to_stack(pile[(std::size_t)(2*i)]);
        player_2->add_to_stack(pile[(std::size_t)((2*i)+1)]);
    }
}
void Game::deal_cards_end_draw(vector <Card>& pile){
    for (int i = 0; i <(pile.size()/2); i++) {
        player_1->add_to_taken(pile[(std::size_t)(2*i)]);
        player_2->add_to_taken(pile[(std::size_t)((2*i)+1)]);
    }
}
void Game::playAll(){
    while (player_1->stacksize()>0)
        this->playTurn();
}

int Game::get_num_turns()const{
    return this->num_Turns;
}
int Game::get_mount_of_draws()const{
    return this->mount_of_draws;
}

void Game::printLog()const{
    cout<<endl;
    int j=1;
    for (auto i = turns.begin(); i != turns.end(); i++,j++)
        cout <<j<<"-"<< *i << " ";
}
void Game::printStats()const{
    cout << endl;
    cout<<"Game Stats"<<endl;
    cout<<endl;
    cout << "                          " << player_1->get_name() << "              " << player_2->get_name()<< endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "card won                  " << player_1->cardesTaken()<<  "                " << player_2->cardesTaken() << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "rate win                  " << player_1->get_rate_win() << "                " << player_2->get_rate_win() << endl;
    cout <<"------------------------------------------------------" <<endl;
    cout << "rate loss                 " << player_2->get_rate_win() << "                " << player_1->get_rate_win()<< endl;
    cout <<"------------------------------------------------------" <<endl;
    cout<< "Wins in percentages         " << ((player_1->get_rate_win())*100/num_Turns)<< "                " << ((player_2->get_rate_win()*100)/num_Turns)<< endl;
    cout <<"------------------------------------------------------" <<endl;
    cout<<endl;

    cout<<"General statistics:"<<endl;
    cout<<"mount_of_draws  "<<mount_of_draws<<endl;
    cout<<"num_of_turns    "<<num_Turns<<endl;
    cout<<"draw_rate       "<<draw_rate<<endl;
    cout<<"the winner is  "<<winner<<endl;
    cout<<endl;
    cout<<player_1->get_name()<<":"<<endl;
    cout<<endl;
    player_1->print_taken();
    cout<<endl;
    cout<<"----------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<player_2->get_name()<<":"<<endl;
    cout<<endl;
    player_2->print_taken();
    cout<<endl;
}

void Game::printLastTurn()const{
    cout << turns.size() <<"-";
    if(turns.size()>0) {
        cout << turns.back() ;
    }
}



void Game::printWiner() const{
    if(winner=="still playing"){ return;}
    if(winner=="The game ended in a draw")
    {cout<<" "<<endl;
        cout<<winner<<endl;}
    cout<<" "<<endl;
    cout<<"the winnner is "<<winner<<endl;
}


void Game::set_winner(){
    if(player_1->cardesTaken()==player_2->cardesTaken())
    {
        winner="The game ended in a draw";
    }
    else{
        if (player_1->cardesTaken()>player_2->cardesTaken())
        {
            winner=player_1->get_name();
        }
        else
        {
            winner=player_2->get_name();
        }
    }
}

void Game::rund_to_string(string &str,Card & a,Card& b,Player* winner){
    string t;
    if(a.get_num()==b.get_num())
        t="draw. ";
    else
        t=winner->get_name()+" won\n\n";
    str+=" "+player_1->get_name()+" played "+a.get_card()+" "+player_2->get_name()+" played "+b.get_card()+"."+t;
}