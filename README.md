# NFA

A nondeterministic finite automaton (NFA), or nondeterministic finite state machine, does not need to obey these restrictions. In particular, every DFA is also an NFA. Sometimes the term NFA is used in a narrower sense, referring to a NFA that is not a DFA, but not in this article. 

Full NFA implementation in C++. Supports epsilon closures, Any transitions and Any-except-{} transitions.

## Simple example
```C++
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
```

## Levenshtein distance

Source code for automatic creation of Levenshtein NFA for calculating distance between two words is in NFA::levenshtein.
