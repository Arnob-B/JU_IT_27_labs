#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

class DFA {
    int start_state;
    unordered_set<int> accept_states;
    vector<unordered_map<char, int>> transitions;

public:
    DFA(int num_states, int start, const vector<int> &accept)
        : start_state(start), transitions(num_states) {
        accept_states.insert(accept.begin(), accept.end());
    }

    void addTransition(int from, char symbol, int to) {
        transitions[from][symbol] = to;
    }

    void printTransitionTable(const vector<char> &alphabet) {
        cout << "\nTransition Table:\n";
        cout << "State\t";
        for (char c : alphabet) cout << c << "\t";
        cout << "\n--------------------------------\n";
        for (int state = 0; state < (int)transitions.size(); state++) {
            cout << state << "\t";
            for (char c : alphabet) {
                if (transitions[state].count(c))
                    cout << transitions[state][c] << "\t";
                else
                    cout << "-\t";
            }
            cout << "\n";
        }
        cout << "Accept States: { ";
        for (int s : accept_states) cout << s << " ";
        cout << "}\n\n";
    }

		bool run(const string &input) {
			int current = start_state;
			cout << "Start State: " << current << "\n";

			for (char c : input) {
				if (transitions[current].count(c) == 0) {
					cout << "No transition from state " << current << " on '" << c << "' → Reject\n";
					return false;
				}
				int next = transitions[current][c];
				cout << "Read '" << c << "' : " << current << " → " << next << "\n";
				current = next;
			}

			bool accepted = accept_states.count(current) > 0;
			cout << "Final State: " << current << " → " 
				<< (accepted ? "ACCEPT" : "REJECT") << "\n";
			return accepted;
		}

		unordered_set<int> getAcceptStates(){
			return accept_states;
		}
		int getAllStates(){
			int n= transitions.size();
			return n;
		}


		int getTrasition(int state, char input){
			if(state >= transitions.size()){
				return -1;
			}
			if(!transitions[state].count(input)){
				return -1;
			}
			return transitions[state][input];
		}
};
