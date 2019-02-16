//
// Created by peter on 01/02/19.
//

#ifndef TEXTTEMPLATE_NFA_H
#define TEXTTEMPLATE_NFA_H

#include <bits/stdc++.h>

#include "State.h"
#include "Transition.h"
#include "print.h"

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"

namespace automata {

    typedef std::set<State> States;
    typedef std::unordered_map<Transition, States> Transitions;
    typedef std::unordered_map<State, Transitions> TransitionsMap;

    class Result {
    public:
        States states;
        bool success = false;
        int position = -1;

        void print() const {
            std::string result = this->success ? "Success" : "Failure";
            std::cout << result << ": ";

            for (const auto &s : this->states) {
                std::cout << s.getId() << " ";
            } std::cout << std::endl;
        }
    };

    class NFA {
    public:
        NFA() = default;

        explicit NFA(const StringSet &alphabet) {
            this->alphabet = alphabet;
        }

        Result run(std::string input);
        void epsilonClosureMove(States &current);

        void addTransition(const State &from, const Transition &transition, const State &to);

        void addState(const State &state);

        void printStates(const States &states) const;
        void print() const;

        inline int getNOfStates() const {
            return this->nOfStates;
        }

        static int levenshtein(const std::string &w1, const std::string &w2);

    private:
        int nOfStates = 0;
        TransitionsMap map;

        States starts;
        States finals;

        StringSet alphabet;
    };
}

#endif //TEXTTEMPLATE_NFA_H
