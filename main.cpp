#include <iostream>

#include "Automata/NFA.h"

int main() {
    // abc in string
    automata::NFA simple({"a", "b", "c", "d"});

    automata::State state1(1, automata::Start);
    automata::State state2(2);
    automata::State state3(3);
    automata::State state4(4, automata::Final);

    automata::Transition transA({"a"});
    automata::Transition transB({"b"});
    automata::Transition transC({"c"});

    simple.addTransition(state1, transA, state2);
    simple.addTransition(state2, transB, state3);
    simple.addTransition(state3, transC, state4);

    automata::Transition transAny({"any0"}, automata::AcceptAny);
    simple.addTransition(state1, transAny, state1);

    simple.print();

    std::string input = "bcdcdabc";

    auto test = simple.run(input);

    if (test.success) {
        std::cout << "HURRAY" << std::endl;
    }
}