
#include "card.hpp"


Card::Card(string str,int n):kind(str),num(n){}

string Card::get_kind()const{
    return kind;
}
int Card::get_num()const{
    return num;
}
string Card::get_card() const{
    string tnum=to_string(this->num);
    switch (num) {
        case 1:
            tnum="Ace";
            break;
        case 2:
            tnum="Two";
            break;
        case 3:
            tnum="Three";
            break;
        case 4:
            tnum="Four";
            break;
        case 5:
            tnum="Five";
            break;
        case 6:
            tnum="Six";
            break;
        case 7:
            tnum="Seven";
            break;
        case 8:
            tnum="Eight";
            break;
        case 9:
            tnum="Nine";
            break;
        case 10:
            tnum="Ten";
            break;
        case 11:
            tnum="Jack";
            break;
        case 12:
            tnum="Queen";
            break;
        case 13:
            tnum="King";
    }

    return tnum+" of "+kind;
}