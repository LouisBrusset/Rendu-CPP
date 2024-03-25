#include <iostream>
#include "pile.hpp"

IntStack::IntStack() : size(100), stack(new int [ size ]), top(0) {}
IntStack::IntStack(const int s) : size(s), stack(new int [ size ]), top(0) {}
IntStack::IntStack(const IntStack& other) { this->size = other.size; }
IntStack::~IntStack() { std::cout << "Destructor" << std::endl; }

void IntStack::push(int i) {
    if (! isfull ()) {
        stack [top ] = i;
        ++ top;
    }
}
int IntStack::pop() {
    int var = 0;
    if (! isempty()) {
        var = stack[top-1];
        stack[top-1] = 0;
        --top;
    }
    return var;
}
bool IntStack::isempty() {
    return top == 0;
}
bool IntStack::isfull() {
    return top == size;
}
void IntStack::print() {
    std::cout << "[";
    for (int i = 0; i < size-1; i++) {
        std::cout << stack[i] << ",";
    }
    std::cout << stack[size-1] << "]" << std::endl;
}

std::ostream& operator<<(std::ostream &o, const IntStack& b) {
    o << b.size;
    return o;
}




/*
void IntStack::init() {
    top = 0;
    for (int i=0; i < 20; i++) {
        list[i] = 0;
    }
}
void IntStack::push(int a) {
    for (int i = 0; i < n; i++) {
        if (list[i] == 0) {
            list[i] = a;
            break;
        }
    }
}
int IntStack::pop() {
    int deleted = 0;
    for (int i = n-1; i >= 0; i--) {
        if (list[i] != 0) {
            deleted = list[i];
            list[i] = 0;
            break;
        }
    }
    return deleted;
}
void IntStack::print() {
    std::cout << "[";
    for (int i = 0; i < n-1; i++) {
        std::cout << list[i] << ",";
    }
    std::cout << list[n-1] << "]" << std::endl;
}
bool IntStack::isempty() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (list[i] == 0) {
            count++;
        }
    }
    return (count==n);
}
bool IntStack::isfull() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (list[i] != 0) {
            count++;
        }
    }
    return (count==n);
}
*/

