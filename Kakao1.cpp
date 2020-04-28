#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
	int answer = 0;
	stack<int> s;

	int depth = board.size();
	int command_num = moves.size();

	for (int i = 0; i < command_num; i++) {
		for (int j = 0; j < depth; j++) {
			if (board[j][moves[i] - 1] != 0) {
				if (s.empty()) {
					s.push(board[j][moves[i] - 1]);
				}
				else {
					if (board[j][moves[i] - 1] == s.top()) {
						s.pop();
						answer+=2;
					}
					else
						s.push(board[j][moves[i] - 1]);
				}
				board[j][moves[i] - 1] = 0;
				break;
			}
		}
	}
	return answer;
}