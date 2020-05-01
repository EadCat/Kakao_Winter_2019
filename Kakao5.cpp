#include <vector>
using namespace std;

#define MAX_COND 200000000

int solution(vector<int> stones, int k) {
    int answer;
    int tries = stones.size() - k + 1;
    int z = 0;
    answer = MAX_COND;

    for (int i = 0; i < tries; i++) {
        for (int j = 0; j < k; j++) {
            if (z < stones[i + j])
                z = stones[i + j];
        }
        if (answer > z)
            answer = z;
        z = 0;
    }

    return answer;
}