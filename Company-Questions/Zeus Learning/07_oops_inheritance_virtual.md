// Q7 [MEDIUM - 3/4 marks] Inheritance + OOP output prediction
// ROUND CONTEXT: "Code snippets based on inheritance and OOP concepts".
// PAPER PATTERN: give classes with virtual/non-virtual, ask output.
// RULES TO MEMORISE:
//  1. Base pointer + VIRTUAL fn -> DERIVED version runs (runtime polymorphism).
//  2. Base pointer + NON-virtual fn -> BASE version runs (compile-time binding).
//  3. Virtual destructor needed when deleting derived via base pointer.
//  4. Private members are NOT inherited-accessible; use protected/public.
// PREDICT OUTPUT below BEFORE running: answers in comments.
#include <bits/stdc++.h>
using namespace std;

class Animal {
public:
    virtual void speak() { cout << "Animal speaks\n"; } // virtual -> override wins
    void move() { cout << "Animal moves\n"; }           // non-virtual -> base wins
    virtual ~Animal() {}
};
class Dog : public Animal {
public:
    void speak() override { cout << "Dog barks\n"; }
    void move() { cout << "Dog runs\n"; } // hides base move() (no virtual)
};
class Shape {
public:
    virtual double area() = 0; // pure virtual -> abstract class, cannot instantiate
    virtual ~Shape() {}
};
class Circle : public Shape {
    double r; public: Circle(double r): r(r) {}
    double area() override { return 3.14159 * r * r; }
};
class Rect : public Shape {
    double w,h; public: Rect(double w,double h): w(w), h(h) {}
    double area() override { return w * h; }
};

int main() {
    Animal* p = new Dog();
    p->speak(); // Dog barks   (virtual dispatch)
    p->move();  // Animal moves (NOT virtual -> base version!)
    delete p;
    vector<unique_ptr<Shape>> v;
    v.push_back(make_unique<Circle>(2)); // area ~12.566
    v.push_back(make_unique<Rect>(3,4)); // area 12
    for (auto &s : v) cout << "area=" << s->area() << '\n';
    return 0;
}
