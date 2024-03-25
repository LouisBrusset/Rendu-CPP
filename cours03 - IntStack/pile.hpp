// file pile.hpp
# ifndef PILE_HPP_
# define PILE_HPP_
# include <iostream>

class IntStack {
protected:
    int* stack;
    int size, top;
public:
    IntStack();
    IntStack(int s);
    IntStack(const IntStack& other);
    ~ IntStack();

    void push(int i);
    int pop();
    bool isempty();
    bool isfull();
    void print();
    friend std::ostream& operator<<(std::ostream &o, const IntStack& b);
};

# endif







/*
void push ( int i) {
    if (! isfull ()) {
    stack [top ] = i; top +=1;
    } }
int pop () { if (! isempty ()) return stack [-- top ]; }
bool isempty () { return top == 0; }
bool isfull () { return top == size ; }
*/
