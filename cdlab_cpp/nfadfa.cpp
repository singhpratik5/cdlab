#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

set<int> epsilonClosure(int state, const map<int, vector<int>>& epsilonTransitions) {
    set<int> closure;
    queue<int> q;

    closure.insert(state);
    q.push(state);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next : epsilonTransitions.at(current)) {
            if (closure.find(next) == closure.end()) {
                closure.insert(next);
                q.push(next);
            }
        }
    }

    return closure;
}

set<int> epsilonClosure(const set<int>& states, const map<int, vector<int>>& epsilonTransitions) {
    set<int> closure;

    for (int state : states) {
        set<int> stateClosure = epsilonClosure(state, epsilonTransitions);
        closure.insert(stateClosure.begin(), stateClosure.end());
    }

    return closure;
}

set<int> move(const set<int>& states, char symbol, const map<int, map<char, vector<int>>>& transitions) {
    set<int> result;

    for (int state : states) {
        if (transitions.count(state) && transitions.at(state).count(symbol)) {
            const vector<int>& nextStates = transitions.at(state).at(symbol);
            result.insert(nextStates.begin(), nextStates.end());
        }
    }

    return result;
}

void lambdaNFAtoDFA(
    int startState,
    const vector<int>& finalStates,
    const map<int, map<char, vector<int>>>& transitions,
    const map<int, vector<int>>& epsilonTransitions
){
    set<int> startClosure = epsilonClosure(startState, epsilonTransitions);

    map<set<int>, int> dfaStates;
    vector<set<int>> stateList;

    queue<set<int>> q;
    q.push(startClosure);
    dfaStates[startClosure] = 0; 

    int dfaStateCounter = 1;

    map<int, map<char, int>> dfaTransitions;

    while (!q.empty()) {
        set<int> currentSet = q.front();
        q.pop();

        if (dfaStates[currentSet] >= stateList.size()) {
            stateList.push_back(currentSet);
        }

        for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
            set<int> movedSet = move(currentSet, symbol, transitions);
            set<int> closure = epsilonClosure(movedSet, epsilonTransitions);

            if (!closure.empty()) {
                if (dfaStates.find(closure) == dfaStates.end()) {
                    dfaStates[closure] = dfaStateCounter++;
                    q.push(closure);
     
                dfaTransitions[dfaStates[currentSet]][symbol] = dfaStates[closure];
            }
        }
    }
}
}

int main() {
    map<int, map<char, vector<int>>> transitions = {
        {0, {{'a', {1}}, {'b', {2}}}},
        {1, {{'a', {1}}, {'b', {2}}}},
        {2, {{'a', {0}}}}
    };

    map<int, vector<int>> epsilonTransitions = {
        {0, {1}},
        {1, {}},
        {2, {}}
    };

    int startState = 0;
    vector<int> finalStates = {2};

    lambdaNFAtoDFA(startState, finalStates, transitions, epsilonTransitions);

    return 0;
}
