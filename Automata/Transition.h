//
// Created by peter on 02/02/19.
//

#ifndef TEXTTEMPLATE_TRANSITION_H
#define TEXTTEMPLATE_TRANSITION_H

#include <bits/stdc++.h>

namespace automata {

    enum transitionType { Normal, AcceptAny, EpsilonClosure };

    /*
     * Normal -> accepts symbols in values
     * AcceptAny -> accepts any symbol, except those in excluded set
     * EpsilonClosure -> move without any input
     */

    typedef std::set<std::string> StringSet;

    class Transition {
    public:
        explicit Transition(const StringSet &values) : Transition(values, Normal) {}

        Transition(const StringSet &values, transitionType type) : Transition(values, type, {}) {}

        Transition(const StringSet &values, transitionType type, const StringSet &excluded) {
            this->values = values;
            this->type = type;
            this->excluded = excluded;

            if (!this->isAcceptAny() && !this->excluded.empty()) {
                std::__throw_invalid_argument("Only AcceptAny Transition can has excluded values");
            }
        }

        const bool match(std::string r) const {
            if (this->isNormal() && this->getValues().count(r)) {
                return true;
            }

            if (this->isAcceptAny() && !this->getExcluded().count(r)) {
                return true;
            }

            return false;
        }

        const bool isNormal() const {
            return this->type == Normal;
        }

        const bool isAcceptAny() const {
            return this->type == AcceptAny;
        }

        const bool isEpsilonClosure() const {
            return this->type == EpsilonClosure;
        }

        const StringSet getValues() const {
            return this->values;
        }

        const StringSet getExcluded() const {
            return this->excluded;
        }

        void addExcluded(const std::string &symbol) {
            this->excluded.insert(symbol);
        }

        const std::string hash() const {
            std::string hash;

            for (const auto &v : this->values) {
                hash += v;
            }

            return hash;
        }

        const bool operator==(const Transition &other) const {
            if (this->getValues().size() != other.getValues().size()) {
                return false;
            }

            for (const auto &value : this->getValues()) {
                if (!other.getValues().count(value)) {
                    return false;
                }
            }

            return true;
        }
    private:
        StringSet values;
        StringSet excluded;
        transitionType type = Normal;
    };
}

namespace std {
    template<>
    struct hash<automata::Transition> {
        size_t
        operator()(const automata::Transition &obj) const {
            return hash<string>()(obj.hash());
        }
    };
}

#endif //TEXTTEMPLATE_TRANSITION_H
