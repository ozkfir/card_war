#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string.h>
using namespace std;

#ifndef CARD_H
#define CARD_H
class Card{
string kind;
int num;
public:
    Card(string str,int num);
    string get_kind() const;
    int get_num() const;
    string get_card() const;
};
#endif
