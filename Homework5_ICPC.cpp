#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
-----------How I use Induction?-----------
Base case: find the first legal sequence.

If a smaller sequence A is legal,
concatenate A with another legal sequence B is still legal.
So on and so forth.
*/


vector<int> sum;
vector<int> frontSum;

int main() {
    int total = 0;
    cin >> total;

    int validSum = 0;

    sum.resize(total + 2);
    std::fill(sum.begin(), sum.end(), 0);
    frontSum.resize(total + 2);
    std::fill(frontSum.begin(), frontSum.end(), 0);

    //t_i >= 0 的字串編號放入 leftSeq
    vector<int> leftSeq;
    //t_i < 0 的字串編號放入 rightSeq
    vector<int> rightSeq;

    for (int i = 1; i <= total; i++) {
        //當下讀到的第i個()字串
        string seq;
        cin >> seq;

        //處理輸入，計算出sum和frontSum
        string::iterator it;

        for (it = seq.begin(); it < seq.end(); it++) {
            if (*it == '(') {
                sum[i] += 1;
            } else if (*it == ')') {
                sum[i] -= 1;

                if (sum[i] < frontSum[i]) {
                    frontSum[i] = sum[i];
                }
            }
        }

        validSum += sum[i];
        
        if (sum[i] >= 0) {
            leftSeq.push_back(i);
        } else {
            rightSeq.push_back(i);
        }
    }

    //左邊的排序運用frontSum[a] > frontSum[b];
    //右邊的排序運用(frontSum[a] - sum[a]) < (frontSum[b] - sum[b])
    //這樣可以盡量避免不合法的()組合
    if (validSum != 0) {
        cout << "impossible" << endl;
    } else {
        sort(leftSeq.begin(), leftSeq.end(), [&](int a, int b) {
            return frontSum[a] > frontSum[b];
        });
        sort(rightSeq.begin(), rightSeq.end(), [&](int a, int b) {
            return (frontSum[a] - sum[a]) < (frontSum[b] - sum[b]);
        });


        vector<int>::iterator iter = leftSeq.begin();
        int check = 0;
        int valid = 1;

        for (; iter < leftSeq.end(); iter++) {
            if (check + frontSum[*iter] < 0) {
                valid = 0;
                break;
            }

            check += sum[*iter];
        }

        if (valid == 1) {
            iter = rightSeq.begin();

            for (; iter < rightSeq.end(); iter++) {
                if (check + frontSum[*iter] < 0) {
                    valid = 0;
                    break;
                }

                check += sum[*iter];
            }
        }
        //印出答案
        if (valid == 0) {
            cout << "impossible" << endl;
        } else {
            iter = leftSeq.begin();

            for (; iter < leftSeq.end(); iter++) {
                cout << *iter << endl;
            }

            iter = rightSeq.begin();

            for (; iter < rightSeq.end(); iter++) {
                cout << *iter << endl;
            }
        }
    }
}
