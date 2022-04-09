#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <numeric>

void a(int R, int C)
{
	std::string line1;
	std::string line2;
	std::string pattern1;
	std::string pattern2;
	for (size_t j = 0; j < C; j++)
	{
		pattern1 += "+-";
		pattern2 += "|.";
		if (j == 0) {
			line1 += "..";
			line2 += "..";
		}
		else {
			line1 += "+-";
			line2 += "|.";
		}
	}
	pattern1 += "+";
	pattern2 += "|";
	line1 += "+";
	line2 += "|";
	for (size_t i = 0; i < R; i++)
	{
		if (i == 0)
		{
			std::cout << line1 << std::endl;
			std::cout << line2 << std::endl;
		}
		else {
			std::cout << pattern1 << std::endl;
			std::cout << pattern2 << std::endl;
		}
	}
	std::cout << pattern1 << std::endl;
}

void b(int P,
	std::vector<long>& c,
	std::vector<long>& m,
	std::vector<long>& y,
	std::vector<long>& k)
{
	long long sumcolor{};
	long cyan;
	long mag;
	long yel;
	long blk;
	cyan = *(std::min_element(c.begin(), c.end()));
	if (cyan >= 1000000) {
		std::cout << "1000000 0 0 0" << std::endl;
		return;
	}
	sumcolor += cyan;
	mag = *(std::min_element(m.begin(), m.end()));
	if (sumcolor + mag >= 1000000) {
		std::cout << cyan << " " << 1000000 - sumcolor << " 0 0" << std::endl;
		return;
	}
	sumcolor += mag;
	yel = *(std::min_element(y.begin(), y.end()));
	if (sumcolor + yel >= 1000000) {
		std::cout << cyan << " " << mag << " " << 1000000 - sumcolor << " 0" << std::endl;
		return;
	}
	sumcolor += yel;
	blk = *(std::min_element(k.begin(), k.end()));
	if (sumcolor + blk >= 1000000) {
		std::cout << cyan << " " << mag << " " << yel << " " << 1000000 - sumcolor << std::endl;
		return;
	}
	std::cout << "IMPOSSIBLE" << std::endl;
	return;
}

int c(std::queue<std::pair<int, int>>& dices)
{
	if (dices.size() == 1) {
		return std::min(dices.front().first, dices.front().second);
	}
	else {
		std::pair<int, int> p = dices.front();
		dices.pop();
		int sofar = c(dices);
		return std::min(sofar + p.second, p.first);
	}
	return 0;
}

std::pair<size_t, size_t> d(std::vector<std::vector<int>>& childs, std::vector<size_t>& fun, int root)
{
	std::vector<size_t> childsminfun, childsmaxfun;
	if (childs[root].empty()) {
		return std::make_pair(fun[root], fun[root]);
	}
	for (int& node : childs[root])
	{
		auto p = d(childs, fun, node);
		childsminfun.push_back(p.first);
		childsmaxfun.push_back(p.second);
	}
	auto it = std::min_element(childsminfun.begin(), childsminfun.end());
	size_t newmax = std::accumulate(childsmaxfun.begin(), childsmaxfun.end(), size_t()) - *it + std::max(fun[root], *it);
	return  std::make_pair(std::max(fun[root], *it), newmax);;
}

void e() {
	int N, K;
	std::cin >> N;
	std::cin >> K;
	int R, P;
	size_t edges = 0;
	std::map<int, int> already;
	if (K > N)
	{
		for (int r = 1; r <= N; r++)
		{
			std::cin >> R;
			std::cin >> P;
			edges += P;
			std::cout << "T " << r << std::endl;
		}
		std::cin >> R;
		std::cin >> P;
		std::cout << "E " << edges / 2 << std::endl;
		return;
	}
	for (int r = 0; r < K; r++)
	{
		std::cin >> R;
		std::cin >> P;
		already[R] = P;
		if (r % 2 == 0) {
			std::cout << "T " << (std::rand() % N + 1) << std::endl;
		}
		else
		{
			edges += P;
			std::cout << "W" << std::endl;
		}
	}
	double ratio = 2 * (N - K) / K;
	size_t edges_est = edges * ratio;
	for (int r = 1; r <= N; r++)
	{
		edges_est += already[r];
	}
	std::cin >> R;
	std::cin >> P;
	std::cout << "E " << edges_est / 2 << std::endl;
}