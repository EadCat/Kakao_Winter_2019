#include <string>
#include <vector>
#include <map>

using namespace std;

map<long long, long long> table;

long long search(long long input) {
	if (table[input] == 0) {
		table[input] = input + 1;
		return input;
	}
	else {
		return table[input] = search(table[input]); // update
	}
}

vector<long long> solution(long long k, vector<long long> room_number) {
	vector <long long> answer;

	for (int i = 0; i < room_number.size(); i++) {
		long long copy = search(room_number[i]);
		answer.push_back(copy);
	}
	return answer;
}