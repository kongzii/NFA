//
// Created by peter on 02/02/19.
//

#ifndef TEXTTEMPLATE_STATE_H
#define TEXTTEMPLATE_STATE_H

#include <bits/stdc++.h>

namespace automata {

    enum stateType { Start, Final, None };

    class State {
    public:
        int memory;

        State() = default;

        explicit State(int id) {
            this->id = id;
        }

        State(int id, stateType type) {
            this->id = id;
            this->type = type;
        }

        State copy() const {
            State copied(this->getId(), this->getType());
            return copied;
        }

        int getId() const {
            return this->id;
        }

        stateType getType() const {
            return this->type;
        }

        bool isFinal() const {
            return this->type == Final;
        }

        void setFinal() {
            this->type = Final;
        }

        bool isStart() const {
            return this->type == Start;
        }

        void setStart() {
            this->type = Start;
        }

        const int hash() const {
            return this->id;
        }

        const bool operator==(const State &other) const {
            return this->id == other.id;
        }

        const bool operator<(const State &other) const {
            return this->id < other.id;
        }

    private:
        int id = -1;
        stateType type = None;
    };
}

namespace std {
    template<>
    struct hash<automata::State> {
        size_t
        operator()(const automata::State &obj) const {
            return hash<int>()(obj.hash());
        }
    };
}

#endif //TEXTTEMPLATE_STATE_H
