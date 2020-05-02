#include <vector>
#include <algorithm>

using namespace std;

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif // DEBUG


bool binary_search(int mid, int foot_range, vector<int> stone) {
	int count = 0;

	for (int i = 0; i < stone.size(); i++) {
		if (stone[i] <= mid)
			count++;
		else
			count = 0;

		if (count >= foot_range)
			return true; // 미드가 너무 크므로 맥시멈을 줄임
	}
	return false; // 미드가 너무 작으므로 미니멈을 올림
}

int solution(vector<int> stone, int step_range) {
	int min = 1;
	int max = *max_element(stone.begin(), stone.end());

	while (min <= max) {
		int mid = (min + max) >> 1;
#ifdef DEBUG
		cout << "min : " << min << endl;
		cout << "max : " << max << endl;
		cout << "mid : " << mid << endl;
		cout << "=================" << endl;
#endif // DEBUG
		if (binary_search(mid, step_range, stone))
			max = mid-1;
		else
			min = mid+1;
	}

#ifdef DEBUG
	cout << "answer : " << min << endl;
#endif // DEBUG

	return min;
}