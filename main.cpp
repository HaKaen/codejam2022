#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <bitset>
//#include "qualif.h"
//#include "round1A.h"

using namespace std;

void a() {
	string s, current;
	cin >> s;
	for (char c : s)
	{
		if (current.empty()) {
			current += c;
			continue;
		}
		if (current.back() == c) current += c;
		if (current.back() < c) {
			cout << current << current;
			current = c;
		}
		if (current.back() > c) {
			cout << current;
			current = c;
		}
	}
	cout << current << endl;
}

void b() {
	int N;
	cin >> N;
}


vector<vector<int>>  need;
stack<vector<int>> machine;
vector<int> load;

int E, W;

int adjust(int& e) {
	int r = 0;
	if (machine.empty()) {
		machine.push(need[e]);
		for (int w = 0; w < W; ++w) {
			load[w] = need[e][w];
		}
		r += accumulate(need[e].begin(), need[e].end(), 0);
	}
	else {
		vector<int> available = machine.top();
		machine.pop();
		vector<int> pushing(W, 0);
		for (int w = 0; w < W; ++w) {
			int tmp = load[w] - need[e][w];
			if (tmp <= 0) continue;
			if (tmp <= available[w]) {
				load[w] = need[e][w];
				available[w] -= tmp;
				r += tmp;
			}
			else {
				for (int w2 = 0; w2 < W; ++w2) { //unload
					load[w2] -= available[w2];
					r += available[w2];
					available[w2] = 0;
				}
				if (!machine.empty()) {
					available = machine.top();
					machine.pop();
				}
			}
		}
		if (std::count(available.begin(), available.end(), 0) != available.size()) {
			machine.push(available);
		}
		bool more = false;
		for (int w = 0; w < W; w++)
		{
			int tmp = need[e][w] - load[w];
			if (tmp > 0) {
				load[w] = need[e][w];
				r += tmp;
				pushing[w] = tmp;
				more = true;
			}
		}
		if (more) machine.push(pushing);
	}
	return r;
}

int c() {
	long res = 0;
	cerr << "begin , res = " << res << endl;
	for (int e = 0; e < E; e++)
	{
		res += adjust(e);
		cerr << "for e = " << e << ", res = " << res << endl;
	}
	// unload everything
	while (!machine.empty()) {
		vector<int> available = machine.top();
		res += accumulate(available.begin(), available.end(), 0);
		machine.pop();
	}
	cerr << "unloading ... " << "res = " << res << endl;
	return res;
}

int main(int argc, char *argv[]){
	int T;
	cin >> T;
	for (int nr = 1; nr <= T; ++nr) {
		cin >> E;
		cin >> W;
		need.resize(E);
		load.assign(W, 0);
		for (int e = 0; e < E; e++)
		{
			need[e].resize(W);
			for (int w = 0; w < W; w++)
			{
				int n;
				cin >> n;
				need[e][w] = n;
			}
		}
		cout << "Case #" << nr << ": " << c() << endl;
	}
	return 0;
}