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

    // integer ��̷� ����
    // ����, ����, ���������� ���
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

    // [��� ���� : ���] ����, �ڵ� ��Ʈ
    // ��, 2���� ���� ���
    for (unsigned int i = 0; i < arr.size(); i++) {
        seq.insert(pair<int, vector<int>>(arr[i].size(), arr[i]));
    }
    // [Map�� ��ȸ]
    // ��, ��, ���� ���
    for (unsigned int i = 1; i <= seq.size(); i++) {
        // Map�� vector �迭�� ũ�⸸ŭ �ݺ�
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