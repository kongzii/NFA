# NFA

A nondeterministic finite automaton (NFA), or nondeterministic finite state machine.

Full NFA implementation in C++. Supports epsilon closures, Any transitions and Any-except-{} transitions.

## Simple example

Finds "abc" in the string.

```C++
int main() {
    // Create NFA with a, b, c, d as input alphabet
    automata::NFA simple({"a", "b", "c", "d"}); 
    
    // Add states
    automata::State state1(1, automata::Start);
    automata::State state2(2);
    automata::State state3(3);
    automata::State state4(4, automata::Final);
    
    // Create transition edges states
    automata::Transition transA({"a"});
    automata::Transition transB({"b"});
    automata::Transition transC({"c"});
    
    // Add transitions from state-to-state
    simple.addTransition(state1, transA, state2);
    simple.addTransition(state2, transB, state3);
    simple.addTransition(state3, transC, state4);
    
    // "Any" transition allows to find sequence anywhere inside input string
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

More difficult example, that creates NFA for Levenshtein distance and returns distance between two words. Source code is in NFA::levenshtein.

```C++
int main() {
    std::string str1 = "kongzii";
    std::string str2 = "jung";

    std::cout << automata::NFA::levenshtein(str1, str2) << std::endl;
}
```
