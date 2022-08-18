// bitsetExamples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <stack>
#include <algorithm>
// Given an array of N non-neg integers, define a function that returns 
// (i,j) pairs where i<j<N and f(A[i]) = f(A[j]) f(A[i]) is the number or 1 bits in A[i]

using namespace std;

int countNumBitsForArr(vector<int> arr) {
    int N = arr.size();
    vector<int> countBits;
    unordered_map<int,int> countMap;
    for (int i = 0; i < N;i++) {
        bitset<16> y(arr[i]);
        countBits.push_back(y.count());
        cout << arr[i] << " " << y << " " << y.count() << endl;
        countMap[y.count()]++;
    }
    int cnt = 0;
    for (auto x : countMap) {
        if (x.second > 1)
            cnt+=x.second;
    }
    return cnt;
}
void findCharInBoard(vector<vector<char>> board, string s, int idx,  vector<int>& index,vector<string> &res) {
        
    if (index.size() == s.length()) {
        res.push_back(s);
        return;
    }
        
    if (idx >= s.length())
        return;
    int c = s[idx];

    for (auto x = board.begin(); x != board.end(); x++) {
        int found = 0;
        int indx;
        auto it = find((*x).begin(), (*x).end(), c);
        while (it != (*x).end()) {
            int col = distance((*x).begin(), it);
            int row = distance(board.begin(), x);
            indx = board[0].size() * row + col;
            if (index.empty()) {
                index.push_back(indx);
                findCharInBoard(board, s, idx + 1, index, res);
                index.pop_back();
            }
            else if (find(index.begin(), index.end(), indx) == index.end()) {
                int lastCol = index.back() % board[0].size();
                int lastRow = (index.back() - lastCol) / board[0].size();
                if (abs(lastCol - col) <= 1 && abs(lastRow - row) <= 1) {
                    index.push_back(indx);
                    findCharInBoard(board, s, idx + 1, index, res);
                    index.pop_back();
                }
            }
            it = find(it+1, (*x).end(), c);
        }

        /*if (found) {
            index.push_back(indx);
            findCharInBoard(board, s, idx + 1, index, res);
            index.pop_back();
        }*/
    }
    return;
}

vector<string> solutionX(vector<vector<char>> board, vector<string> words) {
    vector<string> sol;
    while (!words.empty()) {
        string word = words.front();
        words.erase(words.begin());
        vector<int> index;
        findCharInBoard(board, word, 0, index,sol);
    }
    sort(sol.begin(), sol.end());
    sol.erase(unique(sol.begin(),sol.end()), sol.end());
    return sol;
}

vector<string> powerSetOfInt(string str) {
    int sz = str.length();
    vector<string> ret;
    for (int i = 0; i < pow(2, sz); i++) {
        string sub;
        for (int j = 0; j < sz; j++) {   
            if ((i >> j) & 1)
                sub += str[j];
        }
        ret.push_back(sub);
    }
    return ret;

}

int countMultiplesOfThree(string s) {
    vector<string> combs = powerSetOfInt(s);
    int cnt = 0;
    for (auto x : combs) {
        if (x.empty())
            continue;
        int ii = atoi(&x[0]);
        if (x[0] == '0' && ii > 0)
            continue;
        if (ii % 3 ==0)
            cnt++;
    }  
    return cnt;
}

int findAlternatingSum(int s) {
    int sum = 0;
    int mult = 1;
   
    while (s > 0) { 
        sum += mult * s%10;
        mult *= -1;
        s = s / 10;
    }

    return (mult < 0) ? sum: -sum;
}

int main()
{
    int bitNum = 16;
    vector<int> A(16);
    vector<int> B = { 1,2,3,4,5,6,7,8,9,10,11,12 };
    bitset<16> xx(0), x1(1);
    for (int i = 0; i < bitNum; i++) {
        x1.set(i);
        x1.set(bitNum - i - 1);
        A[i] = (int)(x1.to_ullong());
    }
    cout << findAlternatingSum(182) << " " << findAlternatingSum(1234567) << endl;
    cout << countNumBitsForArr(A) << endl;
    cout << countMultiplesOfThree("456") << " " << countMultiplesOfThree("103") << endl;
    vector<vector<char>> board = { {'R','L','D'}, {'U','O','E'},{'C','S','O'} };
    vector<string> words = { "CODE", "SOLO", "RULES", "COOL" };
    
    vector<vector<char>> board2 = {{'A', 'X', 'V', 'W'},
                                   {'A', 'L', 'T', 'I'},
                                   {'T', 'T', 'J', 'R'}};
    vector<string> words2 =
    { "AXOLOTL",
        "TAXA",
        "ABA",
        "VITA",
        "VITTA",
        "GO",
        "AXAL",
        "LATTE",
        "TALA",
        "RJ" };
    vector<vector<char>> board3 = { {'O', 'T', 'T', 'S'},
        {'H', 'O', 'P', 'E'},
        {'E', 'R', 'A', 'R'},
        {'M', 'O', 'D', 'N'} };
    vector<string> words3 = { "ADORE", "APER","APES","APRES", "APSE", "APTER" };
    vector<string> res = solutionX(board2, words2);
    for (auto x : res)
        cout << x << " ";
    cout << endl;
}
