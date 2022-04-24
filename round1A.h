#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

void a() {
	string s;
	cin >> s;
	char prev = s[0];
	for (int c = 1; c < s.length(); ++c)
	{
		if (s[c] > prev) {
			cout << prev;
		}
		cout << prev;
		prev = s[c];
	}
	cout << s[s.length()-1]<< endl;
}

void b() {
	cout << "oh nyo" << endl;
}

void c() {
	cout << "oh nyo" << endl;
}

void test_case() {
	a();
}
