// Q8 [MEDIUM - related] Constructor/destructor order, slicing, diamond
// WHY: natural follow-up to Q7; Zeus-style "what is printed?" questions.
// RULES:
//  1. Construction: BASE first, then DERIVED. Destruction: reverse.
//  2. Object slicing: Derived d; Base b = d; -> derived part cut off, no polymorphism.
//  3. Diamond (D inherits B,C; both inherit A): use `virtual` inheritance to get ONE A.
// PREDICT OUTPUT before compiling - answers inline.
#include <bits/stdc++.h>
using namespace std;

struct Base {
    Base() { cout << "Base ctor\n"; }
    virtual ~Base() { cout << "Base dtor\n"; }
    virtual void who() { cout << "Base\n"; }
};
struct Derived : public Base {
    Derived() { cout << "Derived ctor\n"; }
    ~Derived() override { cout << "Derived dtor\n"; }
    void who() override { cout << "Derived\n"; }
};
// Diamond with virtual inheritance -> single A
struct A { int x = 1; };
struct B : virtual public A {};
struct C : virtual public A {};
struct D : public B, public C {}; // d.x unambiguous (=1); without virtual -> ambiguous

int main() {
    cout << "--- scoped Derived ---\n";
    { Derived d; } // prints: Base ctor / Derived ctor / Derived dtor / Base dtor
    cout << "--- slicing ---\n";
    Derived dd; Base b = dd; // slicing: copies only Base part
    b.who();  // "Base" (object is truly Base now, no virtual dispatch to Derived)
    cout << "--- base ptr ---\n";
    Base* p = new Derived(); p->who(); delete p; // Derived (virtual) + both dtors
    D d2; cout << "diamond x=" << d2.x << " (1, compiles due to virtual)\n";
    return 0;
}
