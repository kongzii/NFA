//
// Created by peter on 01/02/19.
//

#include "NFA.h"

namespace automata {

    void NFA::epsilonClosureMove(automata::States &current) {
        int moves = 1;
        States checked;

        while (moves-- > 0) {
            /*
             * After epsilon transition, there can be new ones
             * So loop until no new states are added
             */

            for (const auto &state : current) {
                if (checked.count(state)) {
                    continue;
                }

                checked.insert(state);

                for (const auto &transition : this->map.at(state)) {
                    if (transition.first.isEpsilonClosure()) {
                        current.insert(transition.second.begin(), transition.second.end());
                        ++moves;
                    }
                }
            }
        }
    }

    Result NFA::run(std::string input) {

        States current = this->starts;
        this->epsilonClosureMove(current);

        States next;

        int position = -1;

        for (const auto &c_char : input) {
            next.clear();

            std::string c_string(1, c_char);

            if (!this->alphabet.empty() && !this->alphabet.count(c_string)) {
                std::__throw_invalid_argument("Input symbol not in alphabet");
            }

            bool moved = false;

            for (const auto &state : current) {

                for (const auto &transition : this->map.at(state)) {

                    if (transition.first.match(c_string)) {
                        next.insert(transition.second.begin(), transition.second.end());

                        if (transition.first.isNormal()) {
                            moved = true;
                        }
                    }

                }

            }

            if (!moved) {
                position++;
            }

            current = next;
            this->epsilonClosureMove(current);
        }

        Result result;
        result.position = position;

        for (const auto &state : current) {
            if (state.isFinal()) {
                result.states.insert(state);
                result.success = true;
            }
        }

        return result;
    }

    void NFA::addTransition(const State &from, const Transition &transition,
                            const State &to) {
        if (!this->map.count(from)) {
            this->addState(from);
        }

        if (!this->map.count(to)) {
            this->addState(to);
        }

        this->map.at(from)[transition].insert(to);
    }

    void NFA::addState(const State &state) {
        if (this->map.count(state)) {
            std::__throw_invalid_argument("State already in NFA");
        }

        this->nOfStates++;
        this->map[state];

        if (state.isStart()) {
            this->starts.insert(state);
        }

        if (state.isFinal()) {
            this->finals.insert(state);
        }
    }

    void NFA::printStates(const States &states) const {
        for (const auto &state : states) {
            std::cout << state.getId() << " , ";
        } std::cout << std::endl;
    }

    int NFA::levenshtein(const std::string &word1, const std::string &word2) {
        /*
         * Construction word has to be longer than test word
         */

        const std::string word = word1.length() > word2.length() ? word1 : word2;

        std::vector<std::vector<int> > matrix(
                word.length() + 1,
                std::vector<int>(word.length() + 1, -1));

        // Initialize matrix as in paska09.pdf, slide 21

        int id = 0;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = i; j < matrix.at(i).size(); j++) {
                matrix.at(i).at(j) = id++;
            }
        }

        NFA nfa;

        // Create transitions

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = i; j < matrix.at(i).size(); j++) {
                int toId = matrix.at(i).at(j);

                if (toId < 1) {
                    continue;
                }

                std::string letter (1, word.at(j - 1));

                State toState(toId);

                if (j == word.length()) {
                    toState.setFinal();
                    toState.memory = i; // i-th row = distance from word
                }

                nfa.addState(toState);

                int onLeftId = matrix.at(i).at(j - 1);
                if (onLeftId != -1) {
                    // From Left
                    State onLeftState(onLeftId);

                    if (onLeftId == 0) {
                        onLeftState.setStart();
                    }

                    Transition transitionLeft({letter});
                    nfa.addTransition(onLeftState, transitionLeft, toState);
                }

                if (i > 0) {
                    // From Top
                    int atTopId = matrix.at(i - 1).at(j);
                    State atTopState(atTopId);

                    Transition transitionAnyTop({"anyTop" + std::to_string(atTopId)}, AcceptAny);
                    if (!toState.isFinal()) {
                        std::string nextLetter (1, word.at(j));
                        transitionAnyTop.addExcluded(nextLetter);
                    }

                    nfa.addTransition(atTopState, transitionAnyTop, toState);

                    // From LeftTop

                    int atTopLeftId = matrix.at(i - 1).at(j - 1);
                    State atTopLeftState(atTopLeftId);

                    Transition transitionAnyTopLeft({"anyTopLeft" + std::to_string(atTopLeftId)}, AcceptAny, {letter});
                    Transition epsilon({"eps"}, EpsilonClosure);

                    nfa.addTransition(atTopLeftState, transitionAnyTopLeft, toState);
                    nfa.addTransition(atTopLeftState, epsilon, toState);
                }
            }
        }

        auto result = nfa.run(word1.length() > word2.length() ? word2 : word1);

        return (*result.states.begin()).memory;
    }

    void NFA::print() const {
        for (const auto &row : this->map) {
            std::cout << row.first.getId() << ": ";

            for (const auto &transition : row.second) {
                for (const auto &state : transition.second) {
                    std::cout << "[ {";

                    for (const auto &v : transition.first.getValues()) {
                        std::cout << v << ", ";
                    }

                    std::cout << "} -> " << state.getId() << " ], ";
                }
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;

        std::cout << "Start states: ";
        this->printStates(this->starts);

        std::cout << "Final states: ";
        this->printStates(this->finals);

        std::cout << std::endl;
    }

}