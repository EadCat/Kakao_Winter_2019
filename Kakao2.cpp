#include <string>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include "union.h"

using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    vector<vector<int>> arr;
    vector<int> ins;
    stack<int> stk;
    map<int, vector<int>> seq;
    set<int> checker;

    int bracket_count = 0;
    int level = 1;
    int sum = 0;

    // integer 어레이로 정리
    // 스택, 벡터, 이차원벡터 사용
    for (int i = s.size() - 2; i > 0; i--) {
        if (s[i] == '}')
            bracket_count = true;
        else {
            //cout << "bracket : " << bracket_count << endl;
            if (bracket_count) { // meaning "open"
                if (s[i] == ',') { // number recognition
                    stk.push(sum);
                    //cout << "stack input : " << stk.top() << endl;
                    sum = 0;
                    level = 1;
                }
                else if (s[i] == '{') { // "close"
                    stk.push(sum);
                    //cout << "stack input : " << stk.top() << endl;
                    sum = 0;
                    level = 1;
                    bracket_count = false;
                    unsigned int limit = stk.size();
                    for (unsigned int j = 0; j < limit; j++) {
                        ins.push_back(stk.top());
                        //cout << "moving stack size : " << stk.size() << endl;
                        //cout << "insert input : " << stk.top() << endl;
                        stk.pop();
                    }
                    arr.push_back(ins);
                    ins.clear();
                }
                else {
                    //cout << "s[i] : " << s[i] << endl;
                    sum += (s[i] - 48) * level;
                    level *= 10;
                }
            }
        }

    }

    // [어레이 길이 : 어레이] 맵핑, 자동 소트
    // 맵, 2차원 벡터 사용
    for (unsigned int i = 0; i < arr.size(); i++) {
        seq.insert(pair<int, vector<int>>(arr[i].size(), arr[i]));
    }
    // [Map을 순회]
    // 맵, 셋, 벡터 사용
    for (unsigned int i = 1; i <= seq.size(); i++) {
        // Map의 vector 배열의 크기만큼 반복
        for (unsigned int j = 0; j < seq.find(i)->second.size(); j++) {  
            answer.push_back(seq.find(i)->second[j]);
            if (!checker.empty()) {
                if (checker.find(seq.find(i)->second[j]) != checker.end())
                    answer.pop_back();
            }
            checker.insert(seq.find(i)->second[j]);
        }
    }

    return answer;
}