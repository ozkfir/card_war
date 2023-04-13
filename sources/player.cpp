#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "player.hpp"
using namespace std;


Player::Player(string name1):name(name1),rate_win(0){
}
void Player::print_taken()const{
   for (int i = 0; i < taken.size(); ++i)
      cout << taken[(std::size_t)i].get_card()<<", ";
   cout<<" "<<endl;
}
int Player::get_rate_win()const{
    return rate_win;
}
void Player::set_rate_win(){
    rate_win++;
}
int Player::stacksize()const{
    return stack.size();
}
int Player::cardesTaken()const{
    return taken.size();
}
string Player::get_name()const{
    return name;
}
void Player::add_to_stack(Card & t){
    this->stack.push_back(t);
}
void Player::add_to_taken(Card &t) {
    this->taken.push_back(t);
}
Card& Player::pop(){
    Card & card=stack.back();
    stack.pop_back();
    return card;
}


