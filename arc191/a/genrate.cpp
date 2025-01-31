#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

int main() {
    // 出力ファイル名
    const string file_name = "test_case.in";

    // 乱数生成器を初期化
    random_device rd;
    mt19937 gen(rd());
    
    // 長さNとMを生成 (1 <= N, M <= 10^6)
    uniform_int_distribution<int> dist_nm(1, 10);  // 1～10^6 の範囲で乱数
    int N = dist_nm(gen);
    int M = dist_nm(gen);
    
    // 数字(1～9)の生成
    uniform_int_distribution<int> dist_digit(1, 9);

    // S を生成
    string S;
    for (int i = 0; i < N; ++i) {
        S += '0' + dist_digit(gen);
    }

    // T を生成
    string T;
    for (int i = 0; i < M; ++i) {
        T += '0' + dist_digit(gen);
    }

    // .inファイルに書き込み
    ofstream outfile(file_name);
    if (outfile.is_open()) {
        outfile << N << " " << M << endl;
        outfile << S << endl;
        outfile << T << endl;
        outfile.close();
        cout << "テストケースを " << file_name << " に保存しました。" << endl;
    } else {
        cerr << "ファイルを開けませんでした。" << endl;
    }

    return 0;
}
