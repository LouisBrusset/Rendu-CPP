#include <iostream>
#include "pile.hpp"


int main () {
    IntStack myStack(10);
    // calls IntStack :: InsStack ()
    int integer;
    bool test;

    myStack.push(1);
    myStack.print();
    test = myStack.isempty();
    std::cout << "test = " << test << std::endl;
    test = myStack.isfull();
    std::cout << "test = " << test << std::endl;
    myStack.push(2);
    myStack.print();
    integer = myStack.pop();
    std::cout << "integer = " << integer << std::endl;
    myStack.print();
    integer = myStack.pop();
    std::cout << "integer = " << integer << std::endl;
    myStack.print();
    test = myStack.isempty();
    std::cout << "test = " << test << std::endl;
    test = myStack.isfull();
    std::cout << "test = " << test << std::endl;
}