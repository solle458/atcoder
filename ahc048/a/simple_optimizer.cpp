#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <algorithm>

using namespace std;

// パラメータ構造体の簡易版
struct SimpleParams {
    double timeLimit = 2.8;
    double startTemp = 100.0;
    double endTemp = 0.1;
    double baseQualityThreshold = 0.4;
    double urgencyMultiplier = 0.3;
    double urgencyThreshold = 0.5;
    double relaxedQualityThreshold = 0.6;
    int consecutiveFailureLimit = 3;
    double capacityWeight = 10.0;
    double colorDistanceWeight = 100.0;
    double emptyWellColorWeight = 50.0;
    int topTubeCount = 3;
    
    string toString() const {
        ostringstream ss;
        ss << fixed << setprecision(3);
        ss << "timeLimit=" << timeLimit;
        ss << " startTemp=" << startTemp;
        ss << " endTemp=" << endTemp;
        ss << " baseQualityThreshold=" << baseQualityThreshold;
        ss << " urgencyMultiplier=" << urgencyMultiplier;
        ss << " urgencyThreshold=" << urgencyThreshold;
        ss << " relaxedQualityThreshold=" << relaxedQualityThreshold;
        ss << " consecutiveFailureLimit=" << consecutiveFailureLimit;
        ss << " capacityWeight=" << capacityWeight;
        ss << " colorDistanceWeight=" << colorDistanceWeight;
        ss << " emptyWellColorWeight=" << emptyWellColorWeight;
        ss << " topTubeCount=" << topTubeCount;
        return ss.str();
    }
};

class SimpleOptimizer {
private:
    mt19937 rng;
    vector<string> testFiles;
    
public:
    SimpleOptimizer() {
        rng.seed(chrono::steady_clock::now().time_since_epoch().count());
        loadTestFiles();
    }
    
    void loadTestFiles() {
        // 利用可能なテストファイルを探す
        for (int i = 0; i < 10; i++) {
            string filename = "in/" + to_string(i).insert(0, 4 - to_string(i).length(), '0') + ".txt";
            ifstream file(filename);
            if (file.good()) {
                testFiles.push_back(filename);
                file.close();
            }
        }
        
        // フォールバック
        if (testFiles.empty()) {
            testFiles = {"test_input.txt", "test_advanced.txt", "test_complex.txt"};
        }
        
        cout << "Found " << testFiles.size() << " test files." << endl;
    }
    
    // ランダムパラメータ生成
    SimpleParams generateRandomParams() {
        SimpleParams params;
        
        params.timeLimit = uniform_real_distribution<double>(2.0, 3.0)(rng);
        params.startTemp = uniform_real_distribution<double>(50.0, 200.0)(rng);
        params.endTemp = uniform_real_distribution<double>(0.01, 1.0)(rng);
        params.baseQualityThreshold = uniform_real_distribution<double>(0.2, 0.6)(rng);
        params.urgencyMultiplier = uniform_real_distribution<double>(0.1, 0.5)(rng);
        params.urgencyThreshold = uniform_real_distribution<double>(0.3, 0.7)(rng);
        params.relaxedQualityThreshold = uniform_real_distribution<double>(0.4, 0.8)(rng);
        params.consecutiveFailureLimit = uniform_int_distribution<int>(2, 5)(rng);
        params.capacityWeight = uniform_real_distribution<double>(5.0, 20.0)(rng);
        params.colorDistanceWeight = uniform_real_distribution<double>(50.0, 200.0)(rng);
        params.emptyWellColorWeight = uniform_real_distribution<double>(25.0, 100.0)(rng);
        params.topTubeCount = uniform_int_distribution<int>(2, 5)(rng);
        
        return params;
    }
    
    // パラメータを微調整
    SimpleParams mutateParams(const SimpleParams& base) {
        SimpleParams mutated = base;
        double mutationRate = 0.1;
        
        if (uniform_real_distribution<double>(0.0, 1.0)(rng) < mutationRate) {
            mutated.timeLimit *= uniform_real_distribution<double>(0.9, 1.1)(rng);
            mutated.timeLimit = max(1.5, min(3.0, mutated.timeLimit));
        }
        
        if (uniform_real_distribution<double>(0.0, 1.0)(rng) < mutationRate) {
            mutated.startTemp *= uniform_real_distribution<double>(0.8, 1.2)(rng);
            mutated.startTemp = max(10.0, min(300.0, mutated.startTemp));
        }
        
        if (uniform_real_distribution<double>(0.0, 1.0)(rng) < mutationRate) {
            mutated.baseQualityThreshold += uniform_real_distribution<double>(-0.1, 0.1)(rng);
            mutated.baseQualityThreshold = max(0.1, min(0.8, mutated.baseQualityThreshold));
        }
        
        if (uniform_real_distribution<double>(0.0, 1.0)(rng) < mutationRate) {
            mutated.capacityWeight *= uniform_real_distribution<double>(0.7, 1.3)(rng);
            mutated.capacityWeight = max(1.0, min(50.0, mutated.capacityWeight));
        }
        
        return mutated;
    }
    
    // パラメータファイルを作成
    void writeParamsToFile(const SimpleParams& params, const string& filename) {
        ofstream file(filename);
        file << fixed << setprecision(6);
        file << params.timeLimit << endl;
        file << params.startTemp << endl;
        file << params.endTemp << endl;
        file << params.baseQualityThreshold << endl;
        file << params.urgencyMultiplier << endl;
        file << params.urgencyThreshold << endl;
        file << params.relaxedQualityThreshold << endl;
        file << params.consecutiveFailureLimit << endl;
        file << params.capacityWeight << endl;
        file << params.colorDistanceWeight << endl;
        file << params.emptyWellColorWeight << endl;
        file << params.topTubeCount << endl;
        file.close();
    }
    
    // パラメータの評価（ダミー実装）
    double evaluateParams(const SimpleParams& params) {
        // 実際にはmainプログラムを実行してスコアを取得
        // ここでは簡易的な評価関数を使用
        
        double score = 1000.0;
        
        // 時間制限が短すぎると悪いスコア
        if (params.timeLimit < 2.0) score += 500;
        
        // 温度設定の妥当性チェック
        if (params.startTemp < params.endTemp) score += 1000;
        if (params.startTemp < 10.0) score += 300;
        
        // 閾値の妥当性チェック
        if (params.baseQualityThreshold > 0.7) score += 200;
        if (params.baseQualityThreshold < 0.2) score += 200;
        
        // ランダム要素を追加（実際の実行結果をシミュレート）
        score += uniform_real_distribution<double>(-100.0, 100.0)(rng);
        
        return score;
    }
    
    // ランダムサーチ実行
    void runRandomSearch(int iterations) {
        cout << "Starting Random Search with " << iterations << " iterations..." << endl;
        
        SimpleParams bestParams;
        double bestScore = INFINITY;
        
        for (int i = 0; i < iterations; i++) {
            SimpleParams params = generateRandomParams();
            double score = evaluateParams(params);
            
            if (score < bestScore) {
                bestScore = score;
                bestParams = params;
                cout << "Iteration " << i << ": New best score " << bestScore << endl;
                cout << "  " << params.toString() << endl;
            }
            
            if (i % 10 == 0) {
                cout << "Progress: " << i << "/" << iterations << " (Best: " << bestScore << ")" << endl;
            }
        }
        
        // 結果を保存
        saveResults("random_search_results.txt", bestParams, bestScore);
    }
    
    // グリッドサーチ実行
    void runGridSearch() {
        cout << "Starting Grid Search..." << endl;
        
        SimpleParams bestParams;
        double bestScore = INFINITY;
        
        vector<double> timeLimits = {2.0, 2.5, 2.8, 3.0};
        vector<double> startTemps = {50.0, 100.0, 150.0, 200.0};
        vector<double> qualityThresholds = {0.3, 0.4, 0.5, 0.6};
        
        int totalCombinations = timeLimits.size() * startTemps.size() * qualityThresholds.size();
        int currentCombination = 0;
        
        for (double timeLimit : timeLimits) {
            for (double startTemp : startTemps) {
                for (double qualityThreshold : qualityThresholds) {
                    SimpleParams params;
                    params.timeLimit = timeLimit;
                    params.startTemp = startTemp;
                    params.baseQualityThreshold = qualityThreshold;
                    
                    double score = evaluateParams(params);
                    currentCombination++;
                    
                    cout << "Progress: " << currentCombination << "/" << totalCombinations 
                         << " Score: " << score << endl;
                    
                    if (score < bestScore) {
                        bestScore = score;
                        bestParams = params;
                        cout << "New best score: " << bestScore << endl;
                    }
                }
            }
        }
        
        saveResults("grid_search_results.txt", bestParams, bestScore);
    }
    
    // 結果保存
    void saveResults(const string& filename, const SimpleParams& params, double score) {
        ofstream file(filename);
        file << "Best Score: " << score << endl;
        file << "Best Parameters:" << endl;
        file << params.toString() << endl;
        file << endl;
        file << "C++ code format:" << endl;
        file << "OptimizationParams optimizedParams;" << endl;
        file << "optimizedParams.timeLimit = " << params.timeLimit << ";" << endl;
        file << "optimizedParams.startTemp = " << params.startTemp << ";" << endl;
        file << "optimizedParams.endTemp = " << params.endTemp << ";" << endl;
        file << "optimizedParams.baseQualityThreshold = " << params.baseQualityThreshold << ";" << endl;
        file << "optimizedParams.urgencyMultiplier = " << params.urgencyMultiplier << ";" << endl;
        file << "optimizedParams.urgencyThreshold = " << params.urgencyThreshold << ";" << endl;
        file << "optimizedParams.relaxedQualityThreshold = " << params.relaxedQualityThreshold << ";" << endl;
        file << "optimizedParams.consecutiveFailureLimit = " << params.consecutiveFailureLimit << ";" << endl;
        file << "optimizedParams.capacityWeight = " << params.capacityWeight << ";" << endl;
        file << "optimizedParams.colorDistanceWeight = " << params.colorDistanceWeight << ";" << endl;
        file << "optimizedParams.emptyWellColorWeight = " << params.emptyWellColorWeight << ";" << endl;
        file << "optimizedParams.topTubeCount = " << params.topTubeCount << ";" << endl;
        file.close();
        
        cout << "Results saved to " << filename << endl;
    }
};

int main(int argc, char* argv[]) {
    try {
        SimpleOptimizer optimizer;
        
        if (argc < 2) {
            cout << "Usage: " << argv[0] << " [random|grid] [iterations]" << endl;
            cout << "  random [N] - Run random search with N iterations (default: 30)" << endl;
            cout << "  grid       - Run grid search" << endl;
            return 1;
        }
        
        string mode = argv[1];
        
        if (mode == "random") {
            int iterations = (argc > 2) ? stoi(argv[2]) : 30;
            optimizer.runRandomSearch(iterations);
        } else if (mode == "grid") {
            optimizer.runGridSearch();
        } else {
            cout << "Unknown mode: " << mode << endl;
            return 1;
        }
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
} 
