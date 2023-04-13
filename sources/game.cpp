#include <iostream>
#include "game.hpp"
#include <sys/time.h>
using namespace std;


using std::cout; using std::endl;

Game::Game(Player & p1,Player &p2):player_1(&p1),player_2(&p2),draw_rate(0),mount_of_draws(0),winner("still playing"),num_Turns(0),turns(){
    vector <Card> pile=shuffle();
    deal_cards_start(pile);
}


int Game::how_big(Card & t1,Card & t2,vector<Card>& pile,string &str){
    int a=t1.get_num();
    int b=t2.get_num();
    if(a==b){
        mount_of_draws++;
        rund_to_string(str,t1,t2,player_1);
        if(player_1->stacksize()==0){
            deal_cards(pile);
            return 0;
        }
        return 1;
    }
    if((a==1 && b==2)||(b==1 && a!=2)||(a!=1 && a<b))
    {
        add_pile(pile,player_2);
        rund_to_string(str,t1,t2,player_2);
        player_2->set_rate_win();
    }
    else
    {
        add_pile(pile,player_1);
        rund_to_string(str,t1,t2,player_1);
        player_1->set_rate_win();
    }
    return 0;
}
void Game::playTurn(){
    if(player_1==player_2){ throw std::invalid_argument("game nid two players");}
    if(player_1->stacksize()==0){throw std::invalid_argument("the game is over");}
    Card & t1=player_1->pop();
    Card & t2=player_2->pop();
    vector<Card> pile;
    string str="";
    int tmount_of_draws=mount_of_draws;
    pile.push_back(t1);
    pile.push_back(t2);
    while (how_big(t1,t2,pile,str))
    {
        if(player_1->stacksize()==0){
            break;}
            pile.push_back(player_1->pop());
            pile.push_back(player_2->pop());

            if(player_1->stacksize()==0){
                deal_cards(pile);
                break;
            }
            t1=player_1->pop();
            t2=player_2->pop();
            pile.push_back(t1);
            pile.push_back(t2);

    }
    turns.push_back(str);
    if(tmount_of_draws<mount_of_draws)
        draw_rate++;
    if(player_1->stacksize()==0)
        set_winner();
    num_Turns++;
}

void Game::rund_to_string(string &str,Card & a,Card& b,Player* winner){
    string t;
    if(a.get_num()==b.get_num())
        t="draw. ";
    else
        t=winner->get_name()+" won\n\n";
    str.append(" ");
    str.append(player_1->get_name());
    str.append(" played ");
    str.append(a.get_card());
    str.append(" ");
    str.append(player_2->get_name());
    str.append(" played ");
    str.append(b.get_card());
    str.append(".");
    str.append(t);

}

void Game::add_pile(vector <Card>& pile,Player *player){
    for (int i = 0; i <pile.size() ; i++)
        player->add_to_taken(pile[(std::size_t)i]);
}



void Game::deal_cards_start(vector <Card>& pile){
    for (int i = 0; i <(pile.size()/2); i++) {
        player_1->add_to_stack(pile[(std::size_t)(2*i)]);
        player_2->add_to_stack(pile[(std::size_t)((2*i)+1)]);
    }
}
void Game::deal_cards(vector <Card>& pile){
    for (int i = 0; i <(pile.size()/2); i++) {
        player_1->add_to_taken(pile[(std::size_t)(2*i)]);
        player_2->add_to_taken(pile[(std::size_t)((2*i)+1)]);
    }
}
void Game::playAll(){
    while (player_1->stacksize()>0)
        this->playTurn();
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

void Game::printLog()const{
    for (auto i = turns.begin(); i != turns.end(); i++)
        cout << *i << " ";
}
void Game::printStats()const{
    cout<<" "<<endl;
    cout<<player_1->get_name()<<endl;
    cout<<"card won-"<<player_1->cardesTaken()<<endl;
    player_1->print_taken();
    cout<<"Wins in percentages "<<((player_1->get_rate_win())*100/num_Turns)<<endl;
    cout<<" "<<endl;
    cout<<player_2->get_name()<<endl;
    cout<<"card won-"<<player_2->cardesTaken()<<endl;
    player_2->print_taken();
    cout<<"Wins in percentages "<<((player_2->get_rate_win()*100)/num_Turns)<<endl;
    cout<<" "<<endl;
    cout<<"General statistics:"<<endl;
    cout<<"draw_rate "<<draw_rate<<",mount_of_draws "<<mount_of_draws<<",num_of_turns "<<num_Turns<<endl;
}

void Game::printLastTurn()const{
    cout << turns.size() << endl;
    if(turns.size()>0) {
        cout << turns.back() << endl;
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
