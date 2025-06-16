#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <random>
#include <memory>

using namespace std;

// 数学ユーティリティ
class MathUtils {
public:
    static constexpr double EPS = 1e-6;
    
    static bool isEqual(double a, double b, double eps = EPS) {
        return abs(a - b) < eps;
    }
    
    static bool isLess(double a, double b, double eps = EPS) {
        return a < b - eps;
    }
    
    static double clamp(double value, double min_val, double max_val) {
        return max(min_val, min(max_val, value));
    }
};

// 色情報クラス
class Color {
private:
    double c, m, y;  // CMY各成分 (0.0-1.0)
    
public:
    Color(double c = 0.0, double m = 0.0, double y = 0.0) : c(c), m(m), y(y) {}
    
    // アクセサ
    double getC() const { return c; }
    double getM() const { return m; }
    double getY() const { return y; }
    void setC(double c) { this->c = c; }
    void setM(double m) { this->m = m; }
    void setY(double y) { this->y = y; }
    
    // 演算
    Color operator+(const Color& other) const {
        return Color(c + other.c, m + other.m, y + other.y);
    }
    
    Color operator*(double scalar) const {
        return Color(c * scalar, m * scalar, y * scalar);
    }
    
    Color operator/(double scalar) const {
        return Color(c / scalar, m / scalar, y / scalar);
    }
    
    // ユーティリティ
    double distance(const Color& other) const {
        double dc = c - other.c;
        double dm = m - other.m;
        double dy = y - other.y;
        return sqrt(dc*dc + dm*dm + dy*dy);
    }
    
    bool isValid() const {
        return c >= 0.0 && c <= 1.0 && m >= 0.0 && m <= 1.0 && y >= 0.0 && y <= 1.0;
    }
    
    string toString() const {
        stringstream ss;
        ss << fixed << setprecision(6) << "(" << c << "," << m << "," << y << ")";
        return ss.str();
    }
};

// ウェル情報クラス
class Well {
private:
    int id;
    set<pair<int, int>> cells;
    Color color;
    double volume;
    int capacity;
    
public:
    Well(int id) : id(id), color(0, 0, 0), volume(0.0), capacity(0) {}
    
    // セル管理
    void addCell(int i, int j) {
        cells.insert({i, j});
        capacity = cells.size();
    }
    
    void removeCell(int i, int j) {
        cells.erase({i, j});
        capacity = cells.size();
    }
    
    set<pair<int, int>> getCells() const { return cells; }
    int getCapacity() const { return capacity; }
    
    // 絵の具管理
    Color getColor() const { return color; }
    double getVolume() const { return volume; }
    void setColor(const Color& color) { this->color = color; }
    void setVolume(double volume) { this->volume = volume; }
    
    // 操作
    bool canAddPaint(double amount) const {
        return volume + amount <= capacity + MathUtils::EPS;
    }
    
    void addPaint(const Color& paintColor, double amount) {
        double actualAmount = min(amount, capacity - volume);
        if (actualAmount <= MathUtils::EPS) return;
        
        if (volume <= MathUtils::EPS) {
            color = paintColor;
            volume = actualAmount;
        } else {
            // 混合計算
            Color newColor = (color * volume + paintColor * actualAmount) / (volume + actualAmount);
            color = newColor;
            volume += actualAmount;
        }
    }
    
    bool canTakePaint(double amount) const {
        return volume >= amount - MathUtils::EPS;
    }
    
    pair<Color, double> takePaint(double amount) {
        if (volume < 1.0 - MathUtils::EPS) {
            throw runtime_error("Insufficient paint for handover");
        }
        
        double takeAmount;
        if (volume >= 1.0) {
            takeAmount = 1.0;
        } else {
            takeAmount = volume;
        }
        
        Color takenColor = color;
        volume -= takeAmount;
        
        if (volume <= MathUtils::EPS) {
            volume = 0.0;
            color = Color(0, 0, 0);
        }
        
        return {takenColor, takeAmount};
    }
    
    void discardPaint(double amount) {
        if (volume <= amount) {
            volume = 0.0;
            color = Color(0, 0, 0);
        } else {
            volume -= amount;
        }
    }
    
    // 判定
    bool isEmpty() const {
        return volume <= MathUtils::EPS;
    }
    
    bool contains(int i, int j) const {
        return cells.count({i, j}) > 0;
    }
    
    string toString() const {
        stringstream ss;
        ss << "Well[" << id << "] cap=" << capacity << " vol=" << fixed << setprecision(3) << volume 
           << " color=" << color.toString();
        return ss.str();
    }
};

// パレット管理クラス
class Palette {
private:
    int size;
    vector<vector<int>> cellToWell;
    map<int, Well> wells;
    vector<vector<bool>> verticalBarriers;
    vector<vector<bool>> horizontalBarriers;
    int nextWellId;
    
public:
    Palette(int size) : size(size), nextWellId(0) {
        if (size <= 0 || size > 1000) {
            throw runtime_error("Invalid palette size: " + to_string(size));
        }
        try {
            cellToWell.assign(size, vector<int>(size, -1));
            verticalBarriers.assign(size, vector<bool>(size-1, false));
            horizontalBarriers.assign(size-1, vector<bool>(size, false));
        } catch (const exception& e) {
            throw runtime_error("Failed to initialize palette arrays: " + string(e.what()));
        }
    }
    
    void initializeBarriers(
        const vector<vector<int>>& vBarriers,
        const vector<vector<int>>& hBarriers
    ) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size-1; j++) {
                verticalBarriers[i][j] = (vBarriers[i][j] == 1);
            }
        }
        for (int i = 0; i < size-1; i++) {
            for (int j = 0; j < size; j++) {
                horizontalBarriers[i][j] = (hBarriers[i][j] == 1);
            }
        }
        buildWells();
    }
    
    void buildWells() {
        wells.clear();
        cellToWell.assign(size, vector<int>(size, -1));
        nextWellId = 0;
        
        set<pair<int, int>> visited;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (visited.count({i, j}) == 0) {
                    Well well(nextWellId);
                    vector<pair<int, int>> connectedCells = getConnectedCells(i, j, visited);
                    for (auto& cell : connectedCells) {
                        well.addCell(cell.first, cell.second);
                        cellToWell[cell.first][cell.second] = nextWellId;
                    }
                    wells.emplace(nextWellId, well);
                    nextWellId++;
                }
            }
        }
    }
    
    int getWellId(int i, int j) const {
        if (!isValidCell(i, j)) return -1;
        return cellToWell[i][j];
    }
    
    Well& getWell(int wellId) {
        return wells.at(wellId);
    }
    
    const Well& getWell(int wellId) const {
        return wells.at(wellId);
    }
    
    vector<int> getAllWellIds() const {
        vector<int> ids;
        for (const auto& pair : wells) {
            ids.push_back(pair.first);
        }
        return ids;
    }
    
    bool canToggleBarrier(int i1, int j1, int i2, int j2) const {
        if (!areAdjacent(i1, j1, i2, j2)) return false;
        return true;
    }
    
    void toggleBarrier(int i1, int j1, int i2, int j2) {
        if (!areAdjacent(i1, j1, i2, j2)) return;
        
        if (abs(i1 - i2) == 1 && j1 == j2) {
            // 横の仕切り
            int row = min(i1, i2);
            horizontalBarriers[row][j1] = !horizontalBarriers[row][j1];
        } else if (i1 == i2 && abs(j1 - j2) == 1) {
            // 縦の仕切り
            int col = min(j1, j2);
            verticalBarriers[i1][col] = !verticalBarriers[i1][col];
        }
        
        // ウェル再構築
        rebuildWellsFromBarriers();
    }
    
    bool isValidCell(int i, int j) const {
        return i >= 0 && i < size && j >= 0 && j < size;
    }
    
    bool areAdjacent(int i1, int j1, int i2, int j2) const {
        return ((abs(i1 - i2) == 1 && j1 == j2) || (i1 == i2 && abs(j1 - j2) == 1));
    }
    
private:
    vector<pair<int, int>> getConnectedCells(int startI, int startJ, set<pair<int, int>>& visited) {
        vector<pair<int, int>> result;
        queue<pair<int, int>> q;
        q.push({startI, startJ});
        visited.insert({startI, startJ});
        
        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            result.push_back({i, j});
            
            // 上
            if (i > 0 && !horizontalBarriers[i-1][j] && visited.count({i-1, j}) == 0) {
                visited.insert({i-1, j});
                q.push({i-1, j});
            }
            // 下
            if (i < size-1 && !horizontalBarriers[i][j] && visited.count({i+1, j}) == 0) {
                visited.insert({i+1, j});
                q.push({i+1, j});
            }
            // 左
            if (j > 0 && !verticalBarriers[i][j-1] && visited.count({i, j-1}) == 0) {
                visited.insert({i, j-1});
                q.push({i, j-1});
            }
            // 右
            if (j < size-1 && !verticalBarriers[i][j] && visited.count({i, j+1}) == 0) {
                visited.insert({i, j+1});
                q.push({i, j+1});
            }
        }
        return result;
    }
    
    void rebuildWellsFromBarriers() {
        // 既存ウェルの絵の具情報を保存
        map<pair<int, int>, pair<Color, double>> cellPaintInfo;
        for (const auto& [wellId, well] : wells) {
            if (!well.isEmpty()) {
                for (const auto& cell : well.getCells()) {
                    cellPaintInfo[cell] = {well.getColor(), well.getVolume() / well.getCapacity()};
                }
            }
        }
        
        // ウェル再構築
        buildWells();
        
        // 絵の具情報を復元
        for (const auto& [cell, paintInfo] : cellPaintInfo) {
            int wellId = getWellId(cell.first, cell.second);
            if (wellId >= 0) {
                Well& well = getWell(wellId);
                double paintPerCell = paintInfo.second;
                double totalPaint = paintPerCell * well.getCapacity();
                well.addPaint(paintInfo.first, totalPaint);
            }
        }
    }
};

// 操作クラス
enum class ActionType {
    ADD_PAINT,
    HANDOVER,
    DISCARD,
    TOGGLE_BARRIER,
    SKIP
};

class Action {
private:
    ActionType type;
    int i, j, k, i2, j2;
    
public:
    Action() : type(ActionType::ADD_PAINT), i(0), j(0), k(0), i2(-1), j2(-1) {}  // デフォルトコンストラクタ
    Action(ActionType type, int i, int j, int k = -1, int i2 = -1, int j2 = -1)
        : type(type), i(i), j(j), k(k), i2(i2), j2(j2) {}
    
    ActionType getType() const { return type; }
    int getI() const { return i; }
    int getJ() const { return j; }
    int getK() const { return k; }
    int getI2() const { return i2; }
    int getJ2() const { return j2; }
    
    // 比較演算子（ソート用）
    bool operator<(const Action& other) const {
        if (type != other.type) return type < other.type;
        if (i != other.i) return i < other.i;
        if (j != other.j) return j < other.j;
        if (k != other.k) return k < other.k;
        if (i2 != other.i2) return i2 < other.i2;
        return j2 < other.j2;
    }
    
    string toString() const {
        stringstream ss;
        switch (type) {
            case ActionType::ADD_PAINT:
                ss << "1 " << i << " " << j << " " << k;
                break;
            case ActionType::HANDOVER:
                ss << "2 " << i << " " << j;
                break;
            case ActionType::DISCARD:
                ss << "3 " << i << " " << j;
                break;
            case ActionType::TOGGLE_BARRIER:
                ss << "4 " << i << " " << j << " " << i2 << " " << j2;
                break;
            case ActionType::SKIP:
                break;
        }
        return ss.str();
    }
};

// ゲーム状態管理クラス
class GameState {
private:
    int N, K, H, T, D;
    vector<Color> tubeColors;
    vector<Color> targetColors;
    Palette palette;
    int currentTurn;
    int tubeUsageCount;
    int handoverCount;
    vector<Color> madeColors;
    
public:
    GameState(int N, int K, int H, int T, int D)
        : N(N), K(K), H(H), T(T), D(D), palette(N), currentTurn(0), tubeUsageCount(0), handoverCount(0) {}
    
    // 初期化
    void setTubeColors(const vector<Color>& colors) { tubeColors = colors; }
    void setTargetColors(const vector<Color>& colors) { targetColors = colors; }
    
    void initializePalette(const vector<vector<int>>& vBarriers, const vector<vector<int>>& hBarriers) {
        palette.initializeBarriers(vBarriers, hBarriers);
    }
    
    // 状態取得
    int getCurrentTurn() const { return currentTurn; }
    int getTubeUsageCount() const { return tubeUsageCount; }
    int getHandoverCount() const { return handoverCount; }
    Color getCurrentTargetColor() const { return targetColors[handoverCount]; }
    Color getTubeColor(int k) const { return tubeColors[k]; }
    Palette& getPalette() { return palette; }
    const Palette& getPalette() const { return palette; }
    int getN() const { return N; }
    int getK() const { return K; }
    int getH() const { return H; }
    int getT() const { return T; }
    int getD() const { return D; }
    
    // 操作実行
    bool canExecuteAction1(int i, int j, int k) const {
        if (!palette.isValidCell(i, j) || k < 0 || k >= K) return false;
        int wellId = palette.getWellId(i, j);
        if (wellId < 0) return false;
        return palette.getWell(wellId).canAddPaint(1.0);
    }
    
    bool canExecuteAction2(int i, int j) const {
        if (!palette.isValidCell(i, j) || handoverCount >= H) return false;
        int wellId = palette.getWellId(i, j);
        if (wellId < 0) return false;
        return palette.getWell(wellId).canTakePaint(1.0 - MathUtils::EPS);
    }
    
    bool canExecuteAction3(int i, int j) const {
        if (!palette.isValidCell(i, j)) return false;
        int wellId = palette.getWellId(i, j);
        if (wellId < 0) return false;
        return !palette.getWell(wellId).isEmpty();
    }
    
    bool canExecuteAction4(int i1, int j1, int i2, int j2) const {
        return palette.canToggleBarrier(i1, j1, i2, j2);
    }
    
    void executeAction1(int i, int j, int k) {
        int wellId = palette.getWellId(i, j);
        palette.getWell(wellId).addPaint(tubeColors[k], 1.0);
        tubeUsageCount++;
        currentTurn++;
    }
    
    void executeAction2(int i, int j) {
        int wellId = palette.getWellId(i, j);
        auto [takenColor, amount] = palette.getWell(wellId).takePaint(1.0);
        madeColors.push_back(takenColor);
        handoverCount++;
        currentTurn++;
    }
    
    void executeAction3(int i, int j) {
        int wellId = palette.getWellId(i, j);
        palette.getWell(wellId).discardPaint(1.0);
        currentTurn++;
    }
    
    void executeAction4(int i1, int j1, int i2, int j2) {
        palette.toggleBarrier(i1, j1, i2, j2);
        currentTurn++;
    }
    
    // 評価
    double calculateColorError() const {
        double totalError = 0.0;
        for (int i = 0; i < handoverCount; i++) {
            totalError += madeColors[i].distance(targetColors[i]);
        }
        return totalError;
    }
    
    int calculateAbsoluteScore() const {
        double E = calculateColorError();
        return 1 + D * (tubeUsageCount - handoverCount) + (int)round(10000.0 * E);
    }
    
    bool isComplete() const {
        return handoverCount >= H;
    }
    
    bool hasRemainingTurns() const {
        return currentTurn < T;
    }
};

// 解を表すクラス
class Solution {
private:
    vector<Action> actions;
    double score;
    bool isValid;
    
public:
    Solution() : score(INFINITY), isValid(false) {}
    
    void setActions(const vector<Action>& actions) {
        this->actions = actions;
    }
    
    const vector<Action>& getActions() const {
        return actions;
    }
    
    void setScore(double score) {
        this->score = score;
    }
    
    double getScore() const {
        return score;
    }
    
    void setValid(bool valid) {
        this->isValid = valid;
    }
    
    bool getValid() const {
        return isValid;
    }
    
    size_t size() const {
        return actions.size();
    }
    
    Action& operator[](size_t index) {
        return actions[index];
    }
    
    const Action& operator[](size_t index) const {
        return actions[index];
    }
    
    void addAction(const Action& action) {
        actions.push_back(action);
    }
};

// 焼きなまし法クラス
class SimulatedAnnealing {
private:
    GameState initialState;
    mt19937 rng;
    double startTime;
    static constexpr double TIME_LIMIT = 2.8; // 時間制限（秒）
    static constexpr double START_TEMP = 100.0;
    static constexpr double END_TEMP = 0.1;
    
    // ウェル使用統計を追加
    map<int, int> wellUsageCount;
    
public:
    SimulatedAnnealing(const GameState& state) : initialState(state) {
        rng.seed(chrono::steady_clock::now().time_since_epoch().count());
        startTime = getCurrentTime();
        
        // ウェル使用統計を初期化
        for (int wellId : state.getPalette().getAllWellIds()) {
            wellUsageCount[wellId] = 0;
        }
    }
    
    double getCurrentTime() const {
        return chrono::duration_cast<chrono::nanoseconds>
            (chrono::steady_clock::now().time_since_epoch()).count() * 1e-9;
    }
    
    double getTemperature(double progress) const {
        return START_TEMP * pow(END_TEMP / START_TEMP, progress);
    }
    
    Solution solve() {
        Solution currentSolution = generateInitialSolution();
        Solution bestSolution = currentSolution;
        
        int iteration = 0;
        while (getCurrentTime() - startTime < TIME_LIMIT) {
            double progress = (getCurrentTime() - startTime) / TIME_LIMIT;
            double temperature = getTemperature(progress);
            
            Solution neighbor = generateNeighbor(currentSolution);
            
            if (neighbor.getValid()) {
                double delta = neighbor.getScore() - currentSolution.getScore();
                
                if (delta < 0 || exp(-delta / temperature) > uniform_real_distribution<double>(0.0, 1.0)(rng)) {
                    currentSolution = neighbor;
                    
                    if (currentSolution.getScore() < bestSolution.getScore()) {
                        bestSolution = currentSolution;
                    }
                }
            }
            
            iteration++;
            if (iteration % 1000 == 0) {
                // 進捗確認
                if (getCurrentTime() - startTime > TIME_LIMIT * 0.95) break;
            }
        }
        
        // デバッグ用：ウェル使用統計を出力（開発時のみ）
        if (false) { // 本番では無効化
            cerr << "Well Usage Statistics:" << endl;
            for (const auto& pair : wellUsageCount) {
                cerr << "Well " << pair.first << ": " << pair.second << " times" << endl;
            }
        }
        
        return bestSolution;
    }
    
private:
    Solution generateInitialSolution() {
        // 複数の戦略で初期解を生成し、最良のものを選択
        vector<Solution> candidates;
        
        // 戦略1: 改良版貪欲法
        candidates.push_back(generateImprovedGreedySolution());
        
        // 戦略2: ランダム化貪欲法
        candidates.push_back(generateRandomizedGreedySolution());
        
        // 戦略3: セーフフォールバック
        candidates.push_back(generateSafeFallbackSolution());
        
        // 最良の候補を選択
        Solution bestSolution;
        for (const auto& candidate : candidates) {
            if (candidate.getValid() && candidate.getScore() < bestSolution.getScore()) {
                bestSolution = candidate;
            }
        }
        
        return bestSolution.getValid() ? bestSolution : generateSafeFallbackSolution();
    }
    
    // 戦略1: 改良版貪欲法
    Solution generateImprovedGreedySolution() {
        Solution solution;
        GameState state = initialState;
        
        // 改良版貪欲法：長期計画を考慮
        int maxAttempts = state.getT() * 2;
        int attempts = 0;
        int consecutiveFailures = 0; // 連続失敗カウンタ
        
        while (!state.isComplete() && state.hasRemainingTurns() && attempts < maxAttempts) {
            Action action = selectImprovedGreedyAction(state);
            
            if (!isActionValid(state, action)) {
                attempts++;
                consecutiveFailures++;
                
                // 連続で失敗している場合はより安全な操作を選択
                if (consecutiveFailures > 3) {
                    action = generateSafeAlternativeAction(state);
                    consecutiveFailures = 0; // リセット
                }
                
                if (!isActionValid(state, action)) {
                    break;
                }
            } else {
                consecutiveFailures = 0; // 成功したらリセット
            }
            
            solution.addAction(action);
            executeAction(state, action);
            attempts++;
        }
        
        if (state.isComplete()) {
            solution.setScore(state.calculateAbsoluteScore());
            solution.setValid(true);
        } else {
            solution.setScore(INFINITY);
            solution.setValid(false);
        }
        
        return solution;
    }
    
    // ランダム化貪欲法
    Solution generateRandomizedGreedySolution() {
        Solution solution;
        GameState state = initialState;
        
        int maxAttempts = state.getT() * 2;
        int attempts = 0;
        
        while (!state.isComplete() && state.hasRemainingTurns() && attempts < maxAttempts) {
            // 複数の良い選択肢からランダムに選択
            vector<Action> goodActions = generateGoodActionCandidates(state);
            
            if (goodActions.empty()) {
                attempts++;
                continue;
            }
            
            int selectedIndex = uniform_int_distribution<int>(0, goodActions.size() - 1)(rng);
            Action action = goodActions[selectedIndex];
            
            if (isActionValid(state, action)) {
                solution.addAction(action);
                executeAction(state, action);
            }
            
            attempts++;
        }
        
        if (state.isComplete()) {
            solution.setScore(state.calculateAbsoluteScore());
            solution.setValid(true);
        } else {
            solution.setScore(INFINITY);
            solution.setValid(false);
        }
        
        return solution;
    }
    
    // セーフフォールバック解法
    Solution generateSafeFallbackSolution() {
        Solution solution;
        GameState state = initialState;
        
        // 改良版戦略：混合を活用してより良い色を作る
        while (!state.isComplete() && state.hasRemainingTurns()) {
            Color targetColor = state.getCurrentTargetColor();
            
            // 既存のウェルから良い色がないかチェック
            int bestExistingWellId = findBestExistingWell(state, targetColor);
            bool useExistingWell = false;
            
            if (bestExistingWellId >= 0) {
                const Well& existingWell = state.getPalette().getWell(bestExistingWellId);
                double existingDistance = existingWell.getColor().distance(targetColor);
                
                // 既存の色が十分良い場合は、改良を試みる
                if (existingDistance < 0.8) { // より緩い条件
                    useExistingWell = true;
                    
                    // 既存の色をさらに改良するか判断
                    if (existingDistance > 0.3 && existingWell.getCapacity() > existingWell.getVolume()) {
                        // 改良余地があり、容量に余裕がある場合は改良を試行
                        int improvementTube = findBestImprovementTube(state, existingWell.getColor(), targetColor);
                        if (improvementTube >= 0) {
                            auto cells = existingWell.getCells();
                            auto it = cells.begin();
                            
                            Action addAction(ActionType::ADD_PAINT, it->first, it->second, improvementTube);
                            solution.addAction(addAction);
                            executeAction(state, addAction);
                            continue; // 次のターンで再評価
                        }
                    }
                    
                    // 既存の色をそのまま使用
                    if (existingWell.getVolume() >= 1.0 - MathUtils::EPS) {
                        auto cells = existingWell.getCells();
                        auto it = cells.begin();
                        
                        Action handoverAction(ActionType::HANDOVER, it->first, it->second);
                        solution.addAction(handoverAction);
                        executeAction(state, handoverAction);
                        continue;
                    }
                }
            }
            
            // 新しいウェルで混合色を作成
            vector<ColorMixCandidate> mixCandidates = findBestColorMixes(state, targetColor);
            bool foundGoodMix = false;
            
            // 2色・3色混合を優先的に試行
            for (const auto& candidate : mixCandidates) {
                if (candidate.tubeIndices.size() >= 2 && candidate.tubeIndices.size() <= 3) {
                    if (createColorMixture(state, solution, candidate)) {
                        foundGoodMix = true;
                        break;
                    }
                }
            }
            
            // 混合が不可能な場合は単色で最適なものを使用
            if (!foundGoodMix) {
                for (const auto& candidate : mixCandidates) {
                    if (candidate.tubeIndices.size() == 1) {
                        if (createColorMixture(state, solution, candidate)) {
                            foundGoodMix = true;
                            break;
                        }
                    }
                }
            }
            
            // どうしても作れない場合は緊急フォールバック
            if (!foundGoodMix) {
                if (!emergencyFallback(state, solution, targetColor)) {
                    break; // もうできることがない
                }
            }
        }
        
        if (state.isComplete()) {
            solution.setScore(state.calculateAbsoluteScore());
            solution.setValid(true);
        } else {
            solution.setScore(INFINITY);
            solution.setValid(false);
        }
        
        return solution;
    }
    
    // 既存のウェルから最良のものを見つける
    int findBestExistingWell(const GameState& state, const Color& targetColor) {
        int bestWellId = -1;
        double minDistance = INFINITY;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.getVolume() >= 1.0 - MathUtils::EPS) {
                double distance = well.getColor().distance(targetColor);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestWellId = wellId;
                }
            }
        }
        
        return bestWellId;
    }
    
    // 既存の色を改良するための最適なチューブを見つける
    int findBestImprovementTube(const GameState& state, const Color& currentColor, const Color& targetColor) {
        int bestTube = -1;
        double bestImprovement = 0.0;
        
        double currentDistance = currentColor.distance(targetColor);
        
        for (int k = 0; k < state.getK(); k++) {
            // 1:1の混合を仮定して改良効果を評価
            Color mixedColor = (currentColor + state.getTubeColor(k)) / 2.0;
            double newDistance = mixedColor.distance(targetColor);
            double improvement = currentDistance - newDistance;
            
            if (improvement > bestImprovement) {
                bestImprovement = improvement;
                bestTube = k;
            }
        }
        
        // 十分な改良効果がある場合のみ推奨
        return (bestImprovement > 0.05) ? bestTube : -1;
    }
    

    
    // 緊急フォールバック（最後の手段）
    bool emergencyFallback(GameState& state, Solution& solution, const Color& targetColor) {
        // 最も近いチューブを選択
        int bestTube = 0;
        double minDistance = INFINITY;
        for (int k = 0; k < state.getK(); k++) {
            double distance = state.getTubeColor(k).distance(targetColor);
            if (distance < minDistance) {
                minDistance = distance;
                bestTube = k;
            }
        }
        
        // バランス重視でウェルを選択
        int selectedWellId = selectBalancedWellForFallback(state, bestTube);
        
        if (selectedWellId < 0) return false;
        
        const Well& well = state.getPalette().getWell(selectedWellId);
        auto cells = well.getCells();
        auto it = cells.begin();
        
        // 絵の具を追加
        Action addAction(ActionType::ADD_PAINT, it->first, it->second, bestTube);
        solution.addAction(addAction);
        executeAction(state, addAction);
        
        if (!state.hasRemainingTurns()) return false;
        
        // すぐに取り出し（緊急時のみ）
        Action handoverAction(ActionType::HANDOVER, it->first, it->second);
        solution.addAction(handoverAction);
        executeAction(state, handoverAction);
        
        return true;
    }
    
    // 改良版貪欲操作選択
    Action selectImprovedGreedyAction(const GameState& state) {
        Color targetColor = state.getCurrentTargetColor();
        
        // 十分な絵の具があるウェルをチェック
        int bestWellId = -1;
        double minDistance = INFINITY;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.getVolume() >= 1.0 - MathUtils::EPS) {
                double distance = well.getColor().distance(targetColor);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestWellId = wellId;
                }
            }
        }
        
        // 動的な品質判定
        bool shouldHandover = false;
        if (bestWellId >= 0) {
            // 残りターンによる緊急度
            double remainingRatio = (double)(state.getT() - state.getCurrentTurn()) / state.getT();
            double targetRatio = (double)(state.getH() - state.getHandoverCount()) / state.getH();
            double urgency = max(0.0, targetRatio - remainingRatio);
            
            // 品質閾値を動的調整
            double qualityThreshold = 0.4 + urgency * 0.3; // 緊急時は閾値を緩く
            
            shouldHandover = (minDistance < qualityThreshold) || (urgency > 0.5);
        }
        
        if (shouldHandover) {
            const Well& well = state.getPalette().getWell(bestWellId);
            auto cells = well.getCells();
            auto it = cells.begin();
            return Action(ActionType::HANDOVER, it->first, it->second);
        }
        
        // 絵の具追加（改良版）
        return selectBestAddAction(state, targetColor);
    }
    
    // 色混合計算のヘルパーメソッド
    Color mixColors(const vector<Color>& colors, const vector<double>& ratios) {
        if (colors.size() != ratios.size() || colors.empty()) {
            return Color(0, 0, 0);
        }
        
        double totalRatio = 0.0;
        for (double ratio : ratios) {
            totalRatio += ratio;
        }
        
        if (totalRatio <= MathUtils::EPS) {
            return Color(0, 0, 0);
        }
        
        Color result(0, 0, 0);
        for (int i = 0; i < colors.size(); i++) {
            double normalizedRatio = ratios[i] / totalRatio;
            result = result + colors[i] * normalizedRatio;
        }
        
        return result;
    }
    
    // 最適な2色混合を見つける
    struct ColorMixCandidate {
        vector<int> tubeIndices;
        vector<double> ratios;
        Color resultColor;
        double distanceToTarget;
        
        ColorMixCandidate(const vector<int>& tubes, const vector<double>& ratios, 
                         const Color& result, double distance)
            : tubeIndices(tubes), ratios(ratios), resultColor(result), distanceToTarget(distance) {}
    };
    
    vector<ColorMixCandidate> findBestColorMixes(const GameState& state, const Color& targetColor) {
        vector<ColorMixCandidate> candidates;
        
        // 単色候補
        for (int k = 0; k < state.getK(); k++) {
            Color tubeColor = state.getTubeColor(k);
            double distance = tubeColor.distance(targetColor);
            candidates.emplace_back(vector<int>{k}, vector<double>{1.0}, tubeColor, distance);
        }
        
        // 2色混合候補（1:1の比率）
        for (int k1 = 0; k1 < state.getK(); k1++) {
            for (int k2 = k1 + 1; k2 < state.getK(); k2++) {
                vector<Color> colors = {state.getTubeColor(k1), state.getTubeColor(k2)};
                vector<double> ratios = {1.0, 1.0};
                Color mixedColor = mixColors(colors, ratios);
                double distance = mixedColor.distance(targetColor);
                candidates.emplace_back(vector<int>{k1, k2}, ratios, mixedColor, distance);
            }
        }
        
        // 3色混合候補（1:1:1の比率）
        for (int k1 = 0; k1 < state.getK(); k1++) {
            for (int k2 = k1 + 1; k2 < state.getK(); k2++) {
                for (int k3 = k2 + 1; k3 < state.getK(); k3++) {
                    vector<Color> colors = {state.getTubeColor(k1), state.getTubeColor(k2), state.getTubeColor(k3)};
                    vector<double> ratios = {1.0, 1.0, 1.0};
                    Color mixedColor = mixColors(colors, ratios);
                    double distance = mixedColor.distance(targetColor);
                    candidates.emplace_back(vector<int>{k1, k2, k3}, ratios, mixedColor, distance);
                }
            }
        }
        
        // 距離でソート（昇順）
        sort(candidates.begin(), candidates.end(), 
             [](const ColorMixCandidate& a, const ColorMixCandidate& b) {
                 return a.distanceToTarget < b.distanceToTarget;
             });
        
        return candidates;
    }
    
    // 混合戦略でウェルと操作を計画（改良版）
    vector<Action> planMixingStrategy(const GameState& state, const ColorMixCandidate& candidate) {
        vector<Action> actions;
        
        if (candidate.tubeIndices.size() == 1) {
            // 単色の場合：バランス重視のウェル選択
            int k = candidate.tubeIndices[0];
            int selectedWellId = selectOptimalWell(state, k, candidate.resultColor);
            
            if (selectedWellId >= 0) {
                const Well& well = state.getPalette().getWell(selectedWellId);
                auto cells = well.getCells();
                auto it = cells.begin();
                actions.push_back(Action(ActionType::ADD_PAINT, it->first, it->second, k));
            }
        } else {
            // 混合の場合：バランスを考慮したウェル選択
            int bestWellId = selectMixingWell(state, candidate);
            
            if (bestWellId >= 0) {
                const Well& well = state.getPalette().getWell(bestWellId);
                auto cells = well.getCells();
                auto it = cells.begin();
                
                // 各色を順番に追加
                for (int k : candidate.tubeIndices) {
                    actions.push_back(Action(ActionType::ADD_PAINT, it->first, it->second, k));
                }
            }
        }
        
        return actions;
    }
    
    // 混合用ウェル選択（バランス考慮）
    int selectMixingWell(const GameState& state, const ColorMixCandidate& candidate) {
        vector<int> availableWells;
        vector<double> scores;
        
        // 平均使用回数を計算
        double averageUsage = 0.0;
        int totalWells = 0;
        for (const auto& pair : wellUsageCount) {
            averageUsage += pair.second;
            totalWells++;
        }
        averageUsage = totalWells > 0 ? averageUsage / totalWells : 0.0;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            // 複数回の追加に対応できる容量があるかチェック
            if (well.getCapacity() - well.getVolume() >= candidate.tubeIndices.size() - MathUtils::EPS) {
                availableWells.push_back(wellId);
                
                double score = 0.0;
                
                // 1. 基本的な容量評価
                double availableCapacity = well.getCapacity() - well.getVolume();
                score += availableCapacity * 5.0;
                
                // 2. 空のウェルにボーナス（従来より控えめ）
                if (well.isEmpty()) {
                    score += 20.0; // 以前の100.0から削減
                }
                
                // 3. バランス評価
                int currentUsage = wellUsageCount.count(wellId) ? wellUsageCount[wellId] : 0;
                double usageRatio = averageUsage > 0 ? currentUsage / averageUsage : 0.0;
                
                if (usageRatio < 1.0) {
                    score += (1.0 - usageRatio) * 40.0; // バランスボーナス（強化）
                } else {
                    score -= (usageRatio - 1.0) * 30.0; // 過使用ペナルティ（強化）
                }
                
                // 4. 色の予想品質
                Color expectedColor = candidate.resultColor;
                if (!well.isEmpty()) {
                    double totalVolume = well.getVolume() + candidate.tubeIndices.size();
                    expectedColor = (well.getColor() * well.getVolume() + 
                                   expectedColor * candidate.tubeIndices.size()) / totalVolume;
                }
                // 色評価は軽微なファクターとして扱う
                score += 5.0; // 基本ボーナス
                
                scores.push_back(score);
            }
        }
        
        if (availableWells.empty()) {
            // フォールバック：従来方式
            return selectMixingWellTraditional(state, candidate);
        }
        
        // 重み付き確率選択
        return selectWithWeightedProbability(availableWells, scores);
    }
    
    // 従来の混合ウェル選択（フォールバック用）
    int selectMixingWellTraditional(const GameState& state, const ColorMixCandidate& candidate) {
        int bestWellId = -1;
        double bestScore = -INFINITY;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.getCapacity() - well.getVolume() >= candidate.tubeIndices.size() - MathUtils::EPS) {
                double score = well.getCapacity() - well.getVolume();
                
                if (well.isEmpty()) {
                    score += 100.0;
                }
                
                if (score > bestScore) {
                    bestScore = score;
                    bestWellId = wellId;
                }
            }
        }
        
        return bestWellId;
    }
    
    // 色混合を実際に作成する
    bool createColorMixture(GameState& state, Solution& solution, const ColorMixCandidate& candidate) {
        // バランス重視でウェルを選択
        int selectedWellId = selectOptimalWellForMixture(state, candidate);
        
        if (selectedWellId < 0) return false;
        
        const Well& well = state.getPalette().getWell(selectedWellId);
        auto cells = well.getCells();
        auto it = cells.begin();
        
        // 各色を順番に追加
        for (int k : candidate.tubeIndices) {
            Action addAction(ActionType::ADD_PAINT, it->first, it->second, k);
            solution.addAction(addAction);
            executeAction(state, addAction);
            
            // ターン数制限をチェック
            if (!state.hasRemainingTurns()) return false;
        }
        
        // 混合後に取り出し
        Action handoverAction(ActionType::HANDOVER, it->first, it->second);
        solution.addAction(handoverAction);
        executeAction(state, handoverAction);
        
        return true;
    }
    
    // 混合用ウェル選択（セーフフォールバック版）
    int selectOptimalWellForMixture(const GameState& state, const ColorMixCandidate& candidate) {
        vector<int> availableWells;
        vector<double> scores;
        
        // 平均使用回数を計算
        double averageUsage = 0.0;
        int totalWells = 0;
        for (const auto& pair : wellUsageCount) {
            averageUsage += pair.second;
            totalWells++;
        }
        averageUsage = totalWells > 0 ? averageUsage / totalWells : 0.0;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            
            // 混合に必要な容量があるかチェック
            double requiredCapacity = candidate.tubeIndices.size();
            if (well.getCapacity() - well.getVolume() >= requiredCapacity - MathUtils::EPS) {
                availableWells.push_back(wellId);
                
                double score = 0.0;
                
                // 1. 容量評価
                double availableCapacity = well.getCapacity() - well.getVolume();
                score += availableCapacity * 10.0;
                
                // 2. 空のウェルボーナス（適度に）
                if (well.isEmpty()) {
                    score += 30.0;
                }
                
                // 3. バランス評価
                int currentUsage = wellUsageCount.count(wellId) ? wellUsageCount[wellId] : 0;
                double usageRatio = averageUsage > 0 ? currentUsage / averageUsage : 0.0;
                
                if (usageRatio < 1.0) {
                    score += (1.0 - usageRatio) * 25.0;
                } else {
                    score -= (usageRatio - 1.0) * 15.0;
                }
                
                // 4. ランダム性要素
                score += uniform_real_distribution<double>(-5.0, 5.0)(rng);
                
                scores.push_back(score);
            }
        }
        
        if (availableWells.empty()) return -1;
        
        // 重み付き確率選択
        return selectWithWeightedProbability(availableWells, scores);
    }
    
    // ランダムなウェルを選択するヘルパーメソッド
    int selectRandomWell(const GameState& state, int tubeIdx) {
        vector<int> availableWells;
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.canAddPaint(1.0)) {
                availableWells.push_back(wellId);
            }
        }
        
        if (availableWells.empty()) return -1;
        
        int selectedIndex = uniform_int_distribution<int>(0, availableWells.size() - 1)(rng);
        return availableWells[selectedIndex];
    }
    
    // バランス重視のウェル選択（新機能）
    int selectBalancedWell(const GameState& state, int tubeIdx, const Color& targetColor) {
        vector<int> availableWells;
        vector<double> scores;
        
        // 平均使用回数を計算
        double averageUsage = 0.0;
        int totalWells = 0;
        for (const auto& pair : wellUsageCount) {
            averageUsage += pair.second;
            totalWells++;
        }
        averageUsage = totalWells > 0 ? averageUsage / totalWells : 0.0;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.canAddPaint(1.0)) {
                availableWells.push_back(wellId);
                
                // バランススコアを計算
                double score = 0.0;
                
                // 1. 基本的な適合性（容量・色）
                double availableCapacity = well.getCapacity() - well.getVolume();
                score += availableCapacity * 10.0;
                
                if (!well.isEmpty()) {
                    Color mixedColor = (well.getColor() * well.getVolume() + 
                                      state.getTubeColor(tubeIdx) * 1.0) / 
                                     (well.getVolume() + 1.0);
                    double colorDistance = mixedColor.distance(targetColor);
                    score -= colorDistance * 50.0; // 色誤差にペナルティ（軽減）
                } else {
                    double colorDistance = state.getTubeColor(tubeIdx).distance(targetColor);
                    score -= colorDistance * 25.0;
                }
                
                // 2. 使用バランスボーナス（重要）
                int currentUsage = wellUsageCount.count(wellId) ? wellUsageCount[wellId] : 0;
                double usageRatio = averageUsage > 0 ? currentUsage / averageUsage : 0.0;
                
                // 使用頻度が低いウェルにボーナス
                if (usageRatio < 1.0) {
                    score += (1.0 - usageRatio) * 50.0; // バランスボーナス（強化）
                } else {
                    score -= (usageRatio - 1.0) * 40.0; // 過使用ペナルティ（強化）
                }
                
                // 3. ランダム性要素（探索の多様性）
                score += uniform_real_distribution<double>(-5.0, 5.0)(rng);
                
                scores.push_back(score);
            }
        }
        
        if (availableWells.empty()) return -1;
        
        // 重み付き確率選択（上位候補から選択）
        return selectWithWeightedProbability(availableWells, scores);
    }
    
    // 重み付き確率選択
    int selectWithWeightedProbability(const vector<int>& wells, const vector<double>& scores) {
        if (wells.empty()) return -1;
        
        // スコアを正の値に正規化
        double minScore = *min_element(scores.begin(), scores.end());
        vector<double> weights;
        double totalWeight = 0.0;
        
        for (double score : scores) {
            double weight = exp((score - minScore) / 10.0); // ソフトマックス的変換
            weights.push_back(weight);
            totalWeight += weight;
        }
        
        // 確率的選択
        double rand = uniform_real_distribution<double>(0.0, totalWeight)(rng);
        double cumulative = 0.0;
        
        for (int i = 0; i < wells.size(); i++) {
            cumulative += weights[i];
            if (rand <= cumulative) {
                return wells[i];
            }
        }
        
        return wells[0]; // フォールバック
    }
    
    // 最適なウェルを選択するヘルパーメソッド（改良版）
    int selectOptimalWell(const GameState& state, int tubeIdx, const Color& targetColor) {
        // 確率的に選択方式を決定
        double rand = uniform_real_distribution<double>(0.0, 1.0)(rng);
        
        if (rand < 0.5) {
            // 50%の確率でバランス重視選択
            return selectBalancedWell(state, tubeIdx, targetColor);
        } else if (rand < 0.7) {
            // 20%の確率でランダム選択
            return selectRandomWell(state, tubeIdx);
        } else {
            // 30%の確率で従来の最適選択（効率重視）
            return selectOptimalWellTraditional(state, tubeIdx, targetColor);
        }
    }
    
    // 従来の最適選択（名前を変更）
    int selectOptimalWellTraditional(const GameState& state, int tubeIdx, const Color& targetColor) {
        int bestWellId = -1;
        double bestScore = -INFINITY;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.canAddPaint(1.0)) {
                double score = 0.0;
                
                // 容量の余裕
                double availableCapacity = well.getCapacity() - well.getVolume();
                score += availableCapacity * 10.0;
                
                // 既存の色との相性（混合後の予想色）
                if (!well.isEmpty()) {
                    Color mixedColor = (well.getColor() * well.getVolume() + 
                                      state.getTubeColor(tubeIdx) * 1.0) / 
                                     (well.getVolume() + 1.0);
                    double colorDistance = mixedColor.distance(targetColor);
                    score -= colorDistance * 100.0; // 色誤差にペナルティ
                } else {
                    // 空のウェルの場合はチューブ色そのものの距離
                    double colorDistance = state.getTubeColor(tubeIdx).distance(targetColor);
                    score -= colorDistance * 50.0;
                }
                
                if (score > bestScore) {
                    bestScore = score;
                    bestWellId = wellId;
                }
            }
        }
        
        return bestWellId;
    }
    
    // 良い操作候補の生成（混合戦略優先）
    vector<Action> generateGoodActionCandidates(const GameState& state) {
        vector<Action> candidates;
        Color targetColor = state.getCurrentTargetColor();
        
        // 取り出し候補
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.getVolume() >= 1.0 - MathUtils::EPS) {
                double distance = well.getColor().distance(targetColor);
                if (distance < 0.6) { // より緩い閾値
                    auto cells = well.getCells();
                    auto it = cells.begin();
                    candidates.push_back(Action(ActionType::HANDOVER, it->first, it->second));
                }
            }
        }
        
        // 混合戦略による追加候補（優先）
        vector<ColorMixCandidate> mixCandidates = findBestColorMixes(state, targetColor);
        
        // 上位5つの混合候補を選択（2色・3色混合を優先）
        int addedMixCandidates = 0;
        for (const auto& mixCandidate : mixCandidates) {
            if (addedMixCandidates >= 5) break;
            
            // 2色混合・3色混合を優先（単色は後回し）
            if (mixCandidate.tubeIndices.size() >= 2) {
                vector<Action> mixActions = planMixingStrategy(state, mixCandidate);
                for (const Action& action : mixActions) {
                    candidates.push_back(action);
                }
                addedMixCandidates++;
            }
        }
        
        // 単色候補も少し追加（従来の戦略）
        int addedSingleCandidates = 0;
        for (const auto& mixCandidate : mixCandidates) {
            if (addedSingleCandidates >= 2) break;
            
            if (mixCandidate.tubeIndices.size() == 1) {
                vector<Action> singleActions = planMixingStrategy(state, mixCandidate);
                for (const Action& action : singleActions) {
                    candidates.push_back(action);
                }
                addedSingleCandidates++;
            }
        }
        
        return candidates;
    }
    
    Action generateSafeAlternativeAction(const GameState& state) {
        // 最も安全な操作：空いているウェルに目標色に最も近いチューブから絵の具を追加
        Color targetColor = state.getCurrentTargetColor();
        int bestTube = 0;
        double minDistance = INFINITY;
        
        for (int k = 0; k < state.getK(); k++) {
            double distance = state.getTubeColor(k).distance(targetColor);
            if (distance < minDistance) {
                minDistance = distance;
                bestTube = k;
            }
        }
        
        // 容量に余裕のあるセルを探す
        for (int i = 0; i < state.getN(); i++) {
            for (int j = 0; j < state.getN(); j++) {
                if (state.canExecuteAction1(i, j, bestTube)) {
                    return Action(ActionType::ADD_PAINT, i, j, bestTube);
                }
            }
        }
        
        // フォールバック：廃棄操作
        for (int i = 0; i < state.getN(); i++) {
            for (int j = 0; j < state.getN(); j++) {
                if (state.canExecuteAction3(i, j)) {
                    return Action(ActionType::DISCARD, i, j);
                }
            }
        }
        
        // 最後の手段
        return Action(ActionType::ADD_PAINT, 0, 0, 0);
    }
    
    Action selectGreedyAction(const GameState& state) {
        Color targetColor = state.getCurrentTargetColor();
        
        // まず十分な絵の具があるウェルを探す
        int bestWellId = -1;
        double minDistance = INFINITY;
        
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.getVolume() >= 1.0 - MathUtils::EPS) {
                double distance = well.getColor().distance(targetColor);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestWellId = wellId;
                }
            }
        }
        
        // 良い色が見つかった場合、または締切が近い場合は取り出し
        bool shouldHandover = false;
        if (bestWellId >= 0) {
            // 色の品質または緊急性で判定
            shouldHandover = (minDistance < 0.4) || 
                           (state.getCurrentTurn() > (state.getT() / state.getH()) * state.getHandoverCount());
        }
        
        if (shouldHandover) {
            const Well& well = state.getPalette().getWell(bestWellId);
            auto cells = well.getCells();
            auto it = cells.begin();
            return Action(ActionType::HANDOVER, it->first, it->second);
        }
        
        // そうでなければ新しい絵の具を追加して色を改善
        return selectBestAddAction(state, targetColor);
    }
    
    Action selectBestAddAction(const GameState& state, const Color& targetColor) {
        // 混合戦略を優先して最適な操作を選択
        vector<ColorMixCandidate> mixCandidates = findBestColorMixes(state, targetColor);
        
        // 最も良い候補（2色・3色混合を優先）を選択
        for (const auto& candidate : mixCandidates) {
            // 2色・3色混合を優先的に試行
            if (candidate.tubeIndices.size() >= 2) {
                vector<Action> actions = planMixingStrategy(state, candidate);
                if (!actions.empty()) {
                    return actions[0]; // 最初の操作を返す
                }
            }
        }
        
        // 混合が不可能な場合は単色で最適なものを選択
        for (const auto& candidate : mixCandidates) {
            if (candidate.tubeIndices.size() == 1) {
                vector<Action> actions = planMixingStrategy(state, candidate);
                if (!actions.empty()) {
                    return actions[0];
                }
            }
        }
        
        // フォールバック: 従来の方式
        int bestTube = 0;
        double minDistance = INFINITY;
        
        for (int k = 0; k < state.getK(); k++) {
            double distance = state.getTubeColor(k).distance(targetColor);
            if (distance < minDistance) {
                minDistance = distance;
                bestTube = k;
            }
        }
        
        return Action(ActionType::ADD_PAINT, 0, 0, bestTube);
    }
    
    Solution generateNeighbor(const Solution& current) {
        if (current.size() == 0) return current;
        
        Solution neighbor = current;
        
        // より安全な近傍操作の選択
        int operationType = uniform_int_distribution<int>(0, 2)(rng); // より安全な操作のみ
        
        switch (operationType) {
            case 0: return deleteAction(neighbor);
            case 1: return replaceActionSafely(neighbor);
            case 2: return insertActionSafely(neighbor);
            default: return neighbor;
        }
    }
    
    Solution deleteAction(Solution& solution) {
        if (solution.size() == 0) return solution;
        
        int index = uniform_int_distribution<int>(0, solution.size() - 1)(rng);
        
        // 指定されたインデックスの操作を削除
        vector<Action> newActions;
        for (int i = 0; i < solution.size(); i++) {
            if (i != index) {
                newActions.push_back(solution[i]);
            }
        }
        
        solution.setActions(newActions);
        
        // index以降を貪欲で作り直す
        rebuildFromIndex(solution, index);
        
        return solution;
    }
    
    // 指定されたインデックス以降を貪欲法で再構築
    void rebuildFromIndex(Solution& solution, int fromIndex) {
        // fromIndex以降の操作を削除
        vector<Action> newActions;
        for (int i = 0; i < min(fromIndex, (int)solution.size()); i++) {
            newActions.push_back(solution[i]);
        }
        
        // fromIndexまでの状態を再現
        GameState state = initialState;
        for (int i = 0; i < newActions.size(); i++) {
            if (!isActionValid(state, newActions[i])) {
                // 無効な操作がある場合は、そこまでで切る
                newActions.resize(i);
                break;
            }
            executeAction(state, newActions[i]);
        }
        
        // 残りをランダム化貪欲法で構築
        buildRandomizedGreedyFromState(state, newActions);
        
        solution.setActions(newActions);
        evaluateSolution(solution);
    }
    
    // 現在の状態からランダム化貪欲法で解を構築
    void buildRandomizedGreedyFromState(GameState& state, vector<Action>& actions) {
        int maxAttempts = state.getT() * 2;
        int attempts = 0;
        
        while (!state.isComplete() && state.hasRemainingTurns() && attempts < maxAttempts && actions.size() < state.getT()) {
            // 複数の良い選択肢からランダムに選択（generateRandomizedGreedySolutionと同じ方式）
            vector<Action> goodActions = generateGoodActionCandidates(state);
            
            if (goodActions.empty()) {
                attempts++;
                continue;
            }
            
            // 良い選択肢からランダムに選択
            int selectedIndex = uniform_int_distribution<int>(0, goodActions.size() - 1)(rng);
            Action action = goodActions[selectedIndex];
            
            if (isActionValid(state, action)) {
                actions.push_back(action);
                executeAction(state, action);
            }
            
            attempts++;
        }
    }
    
    Solution replaceActionSafely(Solution& solution) {
        if (solution.size() == 0) return solution;
        
        int index = uniform_int_distribution<int>(0, solution.size() - 1)(rng);
        Action newAction = generateValidAction();
        solution[index] = newAction;
        
        // index以降を貪欲で作り直す
        rebuildFromIndex(solution, index + 1);
        
        return solution;
    }
    
    Solution insertActionSafely(Solution& solution) {
        if (solution.size() >= initialState.getT()) return solution;
        
        int index = uniform_int_distribution<int>(0, solution.size())(rng);
        Action newAction = generateValidAction();
        
        vector<Action> newActions;
        for (int i = 0; i < index; i++) {
            newActions.push_back(solution[i]);
        }
        newActions.push_back(newAction);
        for (int i = index; i < solution.size(); i++) {
            newActions.push_back(solution[i]);
        }
        
        solution.setActions(newActions);
        
        // index以降を貪欲で作り直す
        rebuildFromIndex(solution, index + 1);
        
        return solution;
    }
    
    Action generateValidAction() {
        // より現実的な操作を生成
        int actionType = uniform_int_distribution<int>(1, 3)(rng); // 操作4は複雑なので除外
        int i = uniform_int_distribution<int>(0, initialState.getN() - 1)(rng);
        int j = uniform_int_distribution<int>(0, initialState.getN() - 1)(rng);
        
        switch (actionType) {
            case 1: {
                int k = uniform_int_distribution<int>(0, initialState.getK() - 1)(rng);
                return Action(ActionType::ADD_PAINT, i, j, k);
            }
            case 2:
                return Action(ActionType::HANDOVER, i, j);
            case 3:
                return Action(ActionType::DISCARD, i, j);
            default:
                return Action(ActionType::ADD_PAINT, 0, 0, 0);
        }
    }
    
    void evaluateSolution(Solution& solution) {
        GameState state = initialState;
        bool valid = true;
        
        for (const Action& action : solution.getActions()) {
            if (!state.hasRemainingTurns()) {
                valid = false;
                break;
            }
            
            if (!isActionValid(state, action)) {
                valid = false;
                break;
            }
            
            executeAction(state, action);
        }
        
        if (valid && state.isComplete()) {
            solution.setScore(state.calculateAbsoluteScore());
            solution.setValid(true);
        } else {
            solution.setScore(INFINITY);
            solution.setValid(false);
        }
    }
    
    bool isActionValid(const GameState& state, const Action& action) {
        switch (action.getType()) {
            case ActionType::ADD_PAINT:
                if (!state.getPalette().isValidCell(action.getI(), action.getJ()) || 
                    action.getK() < 0 || action.getK() >= state.getK()) return false;
                return state.canExecuteAction1(action.getI(), action.getJ(), action.getK());
            case ActionType::HANDOVER: {
                if (!state.getPalette().isValidCell(action.getI(), action.getJ())) return false;
                if (state.getHandoverCount() >= state.getH()) return false;
                int wellId = state.getPalette().getWellId(action.getI(), action.getJ());
                if (wellId < 0) return false;
                const Well& well = state.getPalette().getWell(wellId);
                return well.getVolume() >= 1.0 - MathUtils::EPS;
            }
            case ActionType::DISCARD:
                if (!state.getPalette().isValidCell(action.getI(), action.getJ())) return false;
                return state.canExecuteAction3(action.getI(), action.getJ());
            case ActionType::TOGGLE_BARRIER:
                return state.canExecuteAction4(action.getI(), action.getJ(), action.getI2(), action.getJ2());
        }
        return false;
    }
    
    void executeAction(GameState& state, const Action& action) {
        // 使用統計を更新（ADD_PAINTの場合）
        if (action.getType() == ActionType::ADD_PAINT) {
            int wellId = state.getPalette().getWellId(action.getI(), action.getJ());
            if (wellId >= 0) {
                wellUsageCount[wellId]++;
            }
        }
        
        switch (action.getType()) {
            case ActionType::ADD_PAINT:
                state.executeAction1(action.getI(), action.getJ(), action.getK());
                break;
            case ActionType::HANDOVER:
                state.executeAction2(action.getI(), action.getJ());
                break;
            case ActionType::DISCARD:
                state.executeAction3(action.getI(), action.getJ());
                break;
            case ActionType::TOGGLE_BARRIER:
                state.executeAction4(action.getI(), action.getJ(), action.getI2(), action.getJ2());
                break;
        }
    }
    
    // セーフフォールバック用のバランス重視ウェル選択
    int selectBalancedWellForFallback(const GameState& state, int tubeIdx) {
        vector<int> availableWells;
        vector<double> scores;
        
        // 平均使用回数を計算
        double averageUsage = 0.0;
        int totalWells = 0;
        for (const auto& pair : wellUsageCount) {
            averageUsage += pair.second;
            totalWells++;
        }
        averageUsage = totalWells > 0 ? averageUsage / totalWells : 0.0;
        
        // 利用可能なウェルを評価
        for (int wellId : state.getPalette().getAllWellIds()) {
            const Well& well = state.getPalette().getWell(wellId);
            if (well.isEmpty() && well.canAddPaint(1.0)) {
                availableWells.push_back(wellId);
                
                double score = 0.0;
                
                // 1. 基本的な容量ボーナス
                score += well.getCapacity() * 10.0;
                
                // 2. バランス評価（最重要）
                int currentUsage = wellUsageCount.count(wellId) ? wellUsageCount[wellId] : 0;
                double usageRatio = averageUsage > 0 ? currentUsage / averageUsage : 0.0;
                
                // 使用頻度が低いウェルに大きなボーナス
                if (usageRatio < 1.0) {
                    score += (1.0 - usageRatio) * 100.0; // 強力なバランスボーナス
                } else {
                    score -= (usageRatio - 1.0) * 50.0; // 過使用ペナルティ
                }
                
                // 3. ランダム性要素（探索の多様性）
                score += uniform_real_distribution<double>(-10.0, 10.0)(rng);
                
                scores.push_back(score);
            }
        }
        
        if (availableWells.empty()) {
            return -1; // 利用可能なウェルなし
        }
        
        // 重み付き確率選択でバランス重視
        return selectWithWeightedProbability(availableWells, scores);
    }
};

// メイン関数
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    try {
        // 入力読み込み
        int N, K, H, T, D;
        cin >> N >> K >> H >> T >> D;
        
        // チューブ色の読み込み
        vector<Color> tubeColors(K);
        for (int i = 0; i < K; i++) {
            double c, m, y;
            cin >> c >> m >> y;
            tubeColors[i] = Color(c, m, y);
        }
        
        // 目標色の読み込み
        vector<Color> targetColors(H);
        for (int i = 0; i < H; i++) {
            double c, m, y;
            cin >> c >> m >> y;
            targetColors[i] = Color(c, m, y);
        }
        
        // ゲーム状態初期化
        GameState gameState(N, K, H, T, D);
        gameState.setTubeColors(tubeColors);
        gameState.setTargetColors(targetColors);
        
        // 初期パレット設定（すべての仕切りを下げる）
        vector<vector<int>> vBarriers(N, vector<int>(N-1, 0));
        vector<vector<int>> hBarriers(N-1, vector<int>(N, 0));
        for(int i = 0; i < N; i++) {
            hBarriers[(N/4)-1][i] = 1;
            hBarriers[(N/2)-1][i] = 1;
            hBarriers[(N*3/4)-1][i] = 1;
            vBarriers[i][(N/4)-1] = 1;
            vBarriers[i][(N/2)-1] = 1;
            vBarriers[i][(N*3/4)-1] = 1;
        }
        gameState.initializePalette(vBarriers, hBarriers);
        
        // 初期パレット状態の出力
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N-1; j++) {
                cout << vBarriers[i][j];
                if (j < N-2) cout << " ";
            }
            cout << "\n";
        }
        for (int i = 0; i < N-1; i++) {
            for (int j = 0; j < N; j++) {
                cout << hBarriers[i][j];
                if (j < N-1) cout << " ";
            }
            cout << "\n";
        }
        
        // 焼きなまし法で解を求める
        SimulatedAnnealing sa(gameState);
        Solution solution = sa.solve();
        
        // 解の出力
        for (const Action& action : solution.getActions()) {
            cout << action.toString() << "\n";
        }
        cout.flush();
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}


