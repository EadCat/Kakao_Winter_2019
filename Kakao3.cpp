#include <string>
#include <vector>
#include <map>
#include <set>

#define numstring 8
using namespace std;

set<set<string>> store[numstring];
set<string> filter;
vector<string> store_ins;

bool string_mask(string label, string data) {
	int size = label.size();

	for (int i = 0; i < size; i++) {
		if (label[i] != data[i]) {
			if (label[i] != '*')
				return false;
			else
				continue;
		}
	}
	return true;
}
void DFS(int start, int page_order, vector<vector<string>> field, int subcounter, int process) {
	int page = field.size(); // 라벨 리스트 갯수
	int next_node = 0; // 다음 노드 갯수
	int now_node; // 지금 노드 갯수

	now_node = field[start].size();
	if (start < page - 1) {
		next_node = field[start + 1].size();
	}

	if (next_node != 0) {
		for (int j = 0; j < now_node; j++) {
			for (int i = 0; i < next_node; i++) {
				//cout << field[subcounter][j] <<' ' << endl;
				store_ins.push_back(field[subcounter][j]);
				DFS(start + 1, page_order, field, subcounter + 1, i);
				store_ins.pop_back();
			}
		}
	}
	else if (next_node == 0 && subcounter == 0) {
		for (int i = 0; i < now_node; i++) {
			filter.insert(field[subcounter][i]);
			// set 출력
			/*cout << "[ ";
			for (set<string>::iterator itr = filter.begin(); itr != filter.end(); ++itr) {
				cout << *itr << ' ';
			}
			cout << ']' << endl;*/
			store[page_order].insert(filter);
			filter.clear();
		}
		
	}
	else {
		store_ins.push_back(field[subcounter][process]);
		// vector 출력 코드
		/*cout << "vector : ";
		for (int i = 0; i < store_ins.size(); i++)
			cout << store_ins[i] << " ";
		cout << endl;*/
		for (int i = 0; i < page; i++) {
			filter.insert(store_ins[i]);
		}
		if (filter.size() == page) {
			store[page_order].insert(filter);
		}
		store_ins.pop_back();
		// set 출력 코드
		/*cout << "[ ";
		for (set<string>::iterator itr = filter.begin(); itr != filter.end(); ++itr) {
			cout << *itr << ' ';
		}
		cout << ']' << endl;*/
		filter.clear();
	}

}

int solution(vector<string> user_id, vector<string> banned_id) {
	// {frodo, crodo, fradi, abc123, shop12} 벡터 스트링
	//  user[0], user[1], user[2], user[3]
	// {*ro*do}, {fr*d*}, {******} 벡터 스트링

	multimap<int, string> data;
	multimap<int, string> label;
	vector<vector<string>> checker[numstring];
	vector<string> ins;

	// 각 문자열 길이 별로 데이터 정리
	for (int i = 0; i < user_id.size(); i++) {
		data.insert(make_pair(user_id[i].size(), user_id[i]));
	}
	for (int i = 0; i < banned_id.size(); i++) {
		label.insert(make_pair(banned_id[i].size(), banned_id[i]));
	}

	// 출력 코드
	/*for (multimap<int, string>::iterator itr = data.begin(); itr != data.end(); ++itr)
		cout << "글자 갯수 : " << itr->first << " // " << "해당 항목 : " << itr->second << endl;
	for (multimap<int, string>::iterator itr = label.begin(); itr != label.end(); ++itr)
		cout << "글자 갯수 : " << itr->first << " // " << "해당 항목 : " << itr->second << endl;*/

	// 5 : frodo, crodo, fradi
	// 5 : *ro*do, fr*d*
	multimap<int, string>::iterator iter1, iter2;

	// 사이즈별로 나눈 데이터 및 라벨 출력 코드
	/*for (int i = 0; i < numstring; i++)
		printf("data[%d] : %d\n", i + 1, data_range[i]);
	for (int i = 0; i < numstring; i++)
		printf("label[%d] : %d\n", i + 1, label_range[i]);*/

	// 각 마스킹 항목에 대한 가능한 원소 모두 조사
	for (int i = 0; i < numstring; i++) {
		iter1 = label.lower_bound(i + 1);
		for (int j = 0; j < label.count(i+1); j++) {
			iter2 = data.lower_bound(i + 1);
			for (int k = 0; k < data.count(i+1); k++) {
				if (string_mask(iter1->second, iter2->second)) {
					ins.push_back(iter2->second);
				}
				++iter2;
			}
			checker[i].push_back(ins);
			ins.clear();
			++iter1;
		}
	}
	//// 트리 출력 코드
	//for (int i = 0; i < numstring; i++) {
	//	int size1 = checker[i].size();
	//	for (int j = 0; j < size1; j++) {
	//		int size2 = checker[i][j].size();
	//		for (int k = 0; k < size2; k++) {
	//			cout << " " << checker[i][j][k];
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}

	// checker[numstring][label.size][possible data.size]
	// 자료형 : vector<vector<string>> checker[8]

	for (int i = 0; i < numstring; i++) {
		if (checker[i].size() != 0)
			DFS(0, i, checker[i], 0, 0); // fill with set vector store
		else continue;
	}

	// vector<set<string>> store[numstring]
	// 출력 코드
	/*for (int i = 0; i < numstring; i++) {
		for (int j = 0; j < vecstore[i].size(); j++) {
			for (set<string>::iterator itr = vecstore[i][j].begin(); itr != vecstore[i][j].end();
				++itr) {
				cout << *itr << " ";
			}
			cout << endl;
		}
	}*/
	int answer = 1;
	// set<set<string>> store[numstring]; 정리
	for (int i = 0; i < numstring; i++) {
		int level = store[i].size();
		if (level != 0)
			answer *= level;
	}
	return answer;
}