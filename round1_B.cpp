#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <bitset>

using namespace std;

int a() {
	int N;
	cin >> N;
	vector<int> d(N);
	int m = 0;
	int res = 0;
	for (size_t p = 0; p < N; p++)
	{
		cin >> d[p];
	}
	int b = 0;
	int e = N - 1;
	while (b != e) {
		if (d[b] <= d[e]) {
			if (d[b] >= m) {
				m = d[b];
				++res;
			}
			++b;
		}
		else {
			if (d[e] >= m) {
				m = d[e];
				++res;
			}
			--e;
		}
	}
	if (d[e] >= m) {
		++res;
	}
	return res;
}

vector<vector<size_t>> products;
int N;
int P;

size_t vabs(size_t a, size_t b) {
	return (a > b ? a - b : b - a);
}

size_t dp_b(int cust, size_t start) {

	size_t diff = products[cust][P - 1] - products[cust][0];
	if (cust == N - 1) {
		return min(vabs(start, products[cust][0]) + diff, vabs(start, products[cust][P - 1]) + diff);
	}
	return min(vabs(start, products[cust][0]) + diff + dp_b(cust + 1, products[cust][P - 1]),
		vabs(start, products[cust][P - 1]) + diff + dp_b(cust + 1, products[cust][0]));
}

size_t b() {
	cin >> N;
	cin >> P;
	products.clear();
	products.resize(N);
	for (size_t c = 0; c < N; c++)
	{
		products[c].resize(P);
		for (size_t p = 0; p < P; p++)
		{
			cin >> products[c][p];
		}
		sort(products[c].begin(), products[c].end());
	}

	return dp_b(0, 0);
}

void c() {
	bitset<8> flipit("11111111");
	bitset<8> bs("00000000");
	vector<bitset<8>> consecutive(9);
	consecutive[0] = bs;
	consecutive[1] = bitset<8>("00000001");
	consecutive[2] = bitset<8>("00000011");
	consecutive[3] = bitset<8>("00000111");
	consecutive[4] = bitset<8>("00001111");
	consecutive[5] = bitset<8>("00011111");
	consecutive[6] = bitset<8>("00111111");
	consecutive[7] = bitset<8>("01111111");
	consecutive[8] = flipit;
	bitset<8> alternate("01010101");

	cout << bs << endl;
	cin >> N;
	int iter = 1;
	while (N > 0)
	{
		++iter;
		if (N == 8) {
			cerr << "iter = " << iter << ", N = " << N << ", bs was = " << bs << " , we flip it !" << endl;
			bs = flipit;
			cout << bs << endl;
			cin >> N;
		}
		else {
			if (N == 1) {
				// prayge
				bitset<8> gamble = flipit;
				gamble[rand() % 8] = 0;
				cout << gamble << endl;
				cin >> N;
			}
			else if (N == 7) {
				// prayge
				bitset<8> gamble("00000000");
				gamble[rand() % 8] = 1;
				cout << gamble << endl;
				cin >> N;
			}
			else {
				//consecutive[rand() % 7 + 1];
				cout << consecutive[8 - N] << endl;
				cin >> N;
			}
		}
	}
	cerr << "iter = " << iter << ", N = " << N << ", bs was = " << bs << endl;
}

int main(int argc, char* argv[]) {
	int T;
	cin >> T;
	for (int nr = 1; nr <= T; ++nr) {
		c();
		if (N < 0) {
			return 0;
		}
	}
	return 0;
}