#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
#include"template.h"

void minimization(DFA &dfa){
	vector<unordered_set<int>> prev(2);
	int running = true;
		int n = dfa.getAllStates();
		unordered_set<int> accepted_states = dfa.getAcceptStates();
 		for(int i =0;i<n;i++){
			if(accepted_states.count(i)){
				prev[1].insert(i);
			}
			else{
				prev[0].insert(i);
			}
		}
		for(auto &it : prev){
			for(auto &j : it){
				cout<<j<<" ";
			}
			cout<<endl;
		}
}
int main(){
	vector<unordered_map<int, int>> transitions;
	DFA dfa(8, 0, {2}); // 8 states, start=0, accept={2}

	dfa.addTransition(0, '0', 1);
	dfa.addTransition(0, '1', 5);

	dfa.addTransition(1, '0', 6);
	dfa.addTransition(1, '1', 2);

	dfa.addTransition(2, '0', 0);
	dfa.addTransition(2, '1', 2);

	dfa.addTransition(3, '0', 2);
	dfa.addTransition(3, '1', 6);

	dfa.addTransition(4, '0', 7);
	dfa.addTransition(4, '1', 5);

	dfa.addTransition(5, '0', 2);
	dfa.addTransition(5, '1', 6);

	dfa.addTransition(6, '0', 6);
	dfa.addTransition(6, '1', 4);

	dfa.addTransition(7, '0', 6);
	dfa.addTransition(7, '1', 2);
	minimization(dfa);

	return 0;
}
