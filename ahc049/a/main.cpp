#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <cmath>
#include <set>

using namespace std;

struct Position {
    int x, y;
    
    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
    
    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }
    
    bool isValid(int N = 20) const {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    int distance(const Position& other) const {
        return abs(x - other.x) + abs(y - other.y);
    }
};

enum Direction {
    UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

const Position DIRECTIONS[] = {
    Position(-1, 0),  // UP
    Position(1, 0),   // DOWN
    Position(0, -1),  // LEFT
    Position(0, 1)    // RIGHT
};

const char DIRECTION_CHARS[] = {'U', 'D', 'L', 'R'};

struct Box {
    int weight;
    int durability;
    int originalDurability;
    
    Box() : weight(0), durability(0), originalDurability(0) {}
    Box(int w, int d) : weight(w), durability(d), originalDurability(d) {}
    
    bool isBroken() const {
        return durability <= 0;
    }
    
    void decreaseDurability(int amount) {
        durability -= amount;
    }
    
    void resetDurability() {
        durability = originalDurability;
    }
};

enum ActionType {
    PICK_UP = 1,
    PUT_DOWN = 2,
    MOVE = 3
};

// 操作を表すクラス
struct Action {
    ActionType type;
    Direction direction;  // 移動の場合のみ使用
    
    Action(ActionType t) : type(t), direction(UP) {}
    Action(ActionType t, Direction d) : type(t), direction(d) {}
    
    char getChar() const {
        if (type == PICK_UP) return '1';
        if (type == PUT_DOWN) return '2';
        if (type == MOVE) return DIRECTION_CHARS[direction];
        return '?';
    }
};

// ゲームの状態を管理するクラス
class GameState {
private:
    static const int N = 20;
    Box board[N][N];              // ボード上の箱
    bool hasBox[N][N];            // 各マスに箱があるかどうか
    vector<Box> handStack;        // 手に持っている箱のスタック
    Position currentPos;          // 現在位置
    int totalOperations;          // 総操作回数
    int moveCount;               // 移動回数
    
public:
    GameState() : currentPos(0, 0), totalOperations(0), moveCount(0) {
        // ボードを初期化
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                board[i][j] = Box();
                hasBox[i][j] = false;
            }
        }
    }
    
    // 入力からゲーム状態を初期化
    void initialize() {
        int n;
        cin >> n;  // N=20固定だが念のため読む
        
        // 重さを読み込み
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int weight;
                cin >> weight;
                board[i][j].weight = weight;
            }
        }
        
        // 耐久力を読み込み
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int durability;
                cin >> durability;
                board[i][j].durability = durability;
                board[i][j].originalDurability = durability;
                
                // (0,0)以外は全て箱がある
                if (i != 0 or j != 0) {
                    hasBox[i][j] = true;
                }
            }
        }
    }
    
    // 現在位置を取得
    Position getCurrentPosition() const {
        return currentPos;
    }
    
    // 現在位置に箱があるかチェック
    bool hasBoxAtCurrentPosition() const {
        return hasBox[currentPos.x][currentPos.y];
    }
    
    // 指定位置に箱があるかチェック
    bool hasBoxAt(const Position& pos) const {
        if (!pos.isValid(N)) return false;
        return hasBox[pos.x][pos.y];
    }
    
    // 現在位置の箱を取得
    Box getBoxAtCurrentPosition() const {
        return board[currentPos.x][currentPos.y];
    }
    
    // 指定位置の箱を取得
    Box getBoxAt(const Position& pos) const {
        if (!pos.isValid(N)) return Box();
        return board[pos.x][pos.y];
    }
    
    // 手に持っている箱の数
    int getHandStackSize() const {
        return handStack.size();
    }
    
    // 手に持っている箱が空かチェック
    bool isHandEmpty() const {
        return handStack.empty();
    }
    
    // 手に持っている箱の一番上を取得
    Box getTopHandBox() const {
        if (handStack.empty()) return Box();
        return handStack.back();
    }
    
    // 残っている箱の総数を取得
    int getRemainingBoxCount() const {
        int count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (hasBox[i][j]) count++;
            }
        }
        return count;
    }
    
    // 移動回数を取得
    int getMoveCount() const {
        return moveCount;
    }
    
    // 総操作回数を取得
    int getTotalOperations() const {
        return totalOperations;
    }
    
    // 操作の実行可能性チェック
    bool canPickUp() const {
        return hasBoxAtCurrentPosition();
    }
    
    bool canPutDown() const {
        return !handStack.empty() && !hasBoxAtCurrentPosition();
    }
    
    bool canMove(Direction dir) const {
        Position nextPos = currentPos + DIRECTIONS[dir];
        return nextPos.isValid(N);
    }
    
    // 操作の実行
    bool executeAction(const Action& action) {
        if (totalOperations >= 2 * N * N * N) return false; // 操作回数制限
        
        totalOperations++;
        
        switch (action.type) {
            case PICK_UP:
                return executePickUp();
            case PUT_DOWN:
                return executePutDown();
            case MOVE:
                return executeMove(action.direction);
        }
        return false;
    }
    
private:
    bool executePickUp() {
        if (!canPickUp()) return false;
        
        Box box = board[currentPos.x][currentPos.y];
        handStack.push_back(box);
        hasBox[currentPos.x][currentPos.y] = false; // 箱を削除
        return true;
    }
    
    bool executePutDown() {
        if (!canPutDown()) return false;
        
        Box box = handStack.back();
        handStack.pop_back();
        board[currentPos.x][currentPos.y] = box;
        hasBox[currentPos.x][currentPos.y] = true; // 箱を設置
        return true;
    }
    
    bool executeMove(Direction dir) {
        if (!canMove(dir)) return false;
        
        // 移動前に耐久力を減らす
        if (!updateDurability()) return false; // 箱が潰れた場合
        
        currentPos = currentPos + DIRECTIONS[dir];
        moveCount++;
        
        // 出入り口に到着した場合、手持ちの箱を全て運び出す
        if (currentPos == Position(0, 0)) {
            handStack.clear();
        }
        
        return true;
    }
    
    bool updateDurability() {
        for (size_t i = 0; i < handStack.size(); i++) {
            int weightAbove = 0;
            for (size_t j = i + 1; j < handStack.size(); j++) {
                weightAbove += handStack[j].weight;
            }
            handStack[i].decreaseDurability(weightAbove);
            if (handStack[i].isBroken()) {
                return false; // 箱が潰れた
            }
        }
        return true;
    }
};

// ビームサーチのための状態管理
struct SearchState {
    Position pos;
    vector<Box> handStack;
    vector<vector<bool>> hasBox;  // ボード上の箱の存在状態
    int moveCount;
    int deliveredBoxes;
    double score;
    vector<Action> actionHistory;  // この状態に至るまでの行動履歴
    
    SearchState() : pos(0, 0), moveCount(0), deliveredBoxes(0), score(0.0) {
        hasBox.resize(20, vector<bool>(20, false));
    }
    
    SearchState(const GameState& game) : pos(game.getCurrentPosition()), 
                                        moveCount(game.getMoveCount()),
                                        deliveredBoxes(0), score(0.0) {
        hasBox.resize(20, vector<bool>(20, false));
        // ゲーム状態から盤面状態をコピー
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                hasBox[i][j] = game.hasBoxAt(Position(i, j));
            }
        }
        deliveredBoxes = 399 - countRemainingBoxes();
    }
    
    int countRemainingBoxes() const {
        int count = 0;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (hasBox[i][j]) count++;
            }
        }
        return count;
    }
    
    // 評価関数
    double evaluate() const {
        if (countRemainingBoxes() == 0) {
            // 全て運搬完了の場合、高得点 - 移動回数
            return 16400.0 - moveCount;
        }
        
        // 改善された評価関数
        int remainingBoxes = countRemainingBoxes();
        double deliveryRate = (double)(399 - remainingBoxes) / 399.0;
        double efficiency = moveCount > 0 ? deliveryRate / moveCount : deliveryRate;
        
        // 進捗に応じた重み付け
        double progressBonus = deliveryRate * 10000;  // 進捗を大きく評価
        double efficiencyBonus = efficiency * 1000;   // 効率も評価
        double movePenalty = moveCount * 0.1;         // 移動回数のペナルティは小さく
        
        return progressBonus + efficiencyBonus - movePenalty;
    }
    
    bool operator<(const SearchState& other) const {
        return score < other.score;  // priority_queueは最大ヒープなので
    }
};

// 状態遷移のための行動シミュレーション
bool simulateActions(SearchState& state, const vector<Action>& actions, 
                    const vector<vector<Box>>& originalBoard) {
    for (const Action& action : actions) {
        if (action.type == MOVE) {
            // 移動前に耐久力をチェック
            for (size_t i = 0; i < state.handStack.size(); i++) {
                int weightAbove = 0;
                for (size_t j = i + 1; j < state.handStack.size(); j++) {
                    weightAbove += state.handStack[j].weight;
                }
                state.handStack[i].decreaseDurability(weightAbove);
                if (state.handStack[i].isBroken()) {
                    return false; // 箱が潰れた
                }
            }
            
            // 移動実行
            state.pos = state.pos + DIRECTIONS[action.direction];
            state.moveCount++;
            
            // 出入り口に到着した場合
            if (state.pos == Position(0, 0)) {
                state.deliveredBoxes += state.handStack.size();
                state.handStack.clear();
            }
            
        } else if (action.type == PICK_UP) {
            if (state.hasBox[state.pos.x][state.pos.y]) {
                // 元のボードから箱情報を取得
                Box box = originalBoard[state.pos.x][state.pos.y];
                state.handStack.push_back(box);
                state.hasBox[state.pos.x][state.pos.y] = false;
            } else {
                return false; // 無効な操作
            }
            
        } else if (action.type == PUT_DOWN) {
            if (!state.handStack.empty() && !state.hasBox[state.pos.x][state.pos.y]) {
                state.hasBox[state.pos.x][state.pos.y] = true;
                state.handStack.pop_back();
            } else {
                return false; // 無効な操作
            }
        }
        
        state.actionHistory.push_back(action);
    }
    return true;
}

// 指定位置への最短経路を生成
vector<Action> generateMovePath(const Position& from, const Position& to) {
    vector<Action> path;
    Position current = from;
    
    // 縦方向移動
    while (current.x != to.x) {
        if (current.x < to.x) {
            path.push_back(Action(MOVE, DOWN));
            current.x++;
        } else {
            path.push_back(Action(MOVE, UP));
            current.x--;
        }
    }
    
    // 横方向移動
    while (current.y != to.y) {
        if (current.y < to.y) {
            path.push_back(Action(MOVE, RIGHT));
            current.y++;
        } else {
            path.push_back(Action(MOVE, LEFT));
            current.y--;
        }
    }
    
    return path;
}

// 前方宣言
vector<SearchState> expandStateForRow(const SearchState& current, 
                                     const vector<vector<Box>>& originalBoard, 
                                     int targetRow);
double evaluateForRow(const SearchState& state, int targetRow);
vector<Action> fallbackStrategyForRow(GameState& currentGame, int targetRow, 
                                     const vector<vector<Box>>& originalBoard);
vector<Action> finalCleanup(GameState& game);

// 改善された状態展開関数
vector<SearchState> expandStateAdvanced(const SearchState& current, 
                                       const vector<vector<Box>>& originalBoard, 
                                       int targetRow) {
    vector<SearchState> nextStates;
    
    // 対象行の残り箱を探す
    vector<Position> remainingBoxes;
    for (int col = 0; col < 20; col++) {
        if (current.hasBox[targetRow][col]) {
            remainingBoxes.push_back(Position(targetRow, col));
        }
    }
    
    if (remainingBoxes.empty()) {
        return nextStates;
    }
    
    // 最も近い箱を優先
    sort(remainingBoxes.begin(), remainingBoxes.end(), 
         [&current](const Position& a, const Position& b) {
             return current.pos.distance(a) < current.pos.distance(b);
         });
    
    // 複数の戦略を試す
    for (int strategy = 0; strategy < min(3, (int)remainingBoxes.size()); strategy++) {
        Position targetBox = remainingBoxes[strategy];
        
        // 戦略1: 単体で運搬
        {
            SearchState newState = current;
            vector<Action> actions;
            
            // 箱まで移動
            vector<Action> moveToBox = generateMovePath(current.pos, targetBox);
            actions.insert(actions.end(), moveToBox.begin(), moveToBox.end());
            
            // 箱を拾う
            actions.push_back(Action(PICK_UP));
            
            // 出入り口まで移動
            vector<Action> moveToExit = generateMovePath(targetBox, Position(0, 0));
            actions.insert(actions.end(), moveToExit.begin(), moveToExit.end());
            
            if (simulateActions(newState, actions, originalBoard)) {
                newState.score = evaluateForRow(newState, targetRow);
                nextStates.push_back(newState);
            }
        }
        
        // 戦略2: 複数箱を集めて運搬（耐久力チェック付き）
        if (remainingBoxes.size() > 1) {
            SearchState newState = current;
            vector<Action> actions;
            
            // 最初の箱を取得
            vector<Action> moveToBox = generateMovePath(current.pos, targetBox);
            actions.insert(actions.end(), moveToBox.begin(), moveToBox.end());
            actions.push_back(Action(PICK_UP));
            
            // 次の箱を探す（耐久力を考慮）
            for (int i = strategy + 1; i < min(strategy + 3, (int)remainingBoxes.size()); i++) {
                Position nextBox = remainingBoxes[i];
                
                // 重量と耐久力をチェック
                Box currentBox = originalBoard[targetBox.x][targetBox.y];
                Box nextBoxData = originalBoard[nextBox.x][nextBox.y];
                
                // 簡単な耐久力チェック
                int distance = targetBox.distance(nextBox) + nextBox.distance(Position(0, 0));
                if (currentBox.durability > nextBoxData.weight * distance) {
                    vector<Action> moveToNext = generateMovePath(targetBox, nextBox);
                    actions.insert(actions.end(), moveToNext.begin(), moveToNext.end());
                    actions.push_back(Action(PICK_UP));
                    targetBox = nextBox;
                }
            }
            
            // 出入り口まで移動
            vector<Action> moveToExit = generateMovePath(targetBox, Position(0, 0));
            // moveToExit上のダンボールが回収できるなら回収(耐久チェック付き)
            actions.insert(actions.end(), moveToExit.begin(), moveToExit.end());
            
            if (simulateActions(newState, actions, originalBoard)) {
                newState.score = evaluateForRow(newState, targetRow);
                nextStates.push_back(newState);
            }
        }
    }
    
    return nextStates;
}

// 特定の行に対するビームサーチ（改善版）
vector<Action> beamSearchForRow(GameState& currentGame, int targetRow, int beamWidth = 80) {
    // 元のボード情報を保存
    vector<vector<Box>> originalBoard(20, vector<Box>(20));
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            originalBoard[i][j] = currentGame.getBoxAt(Position(i, j));
        }
    }
    
    // 対象行の箱数をカウント
    int targetRowBoxes = 0;
    for (int col = 0; col < 20; col++) {
        if (currentGame.hasBoxAt(Position(targetRow, col))) {
            targetRowBoxes++;
        }
    }
    
    if (targetRowBoxes == 0) {
        return vector<Action>(); // 対象行に箱がない
    }
    
    priority_queue<SearchState> beam;
    SearchState initialState(currentGame);
    initialState.score = initialState.evaluate();
    beam.push(initialState);
    
    vector<SearchState> completedStates; // 行の全箱を運搬完了した状態
    const int maxIterations = 500000; // 増加
    int iteration = 0;
    
    // cerr << "Row " << targetRow << ": " << targetRowBoxes << " boxes to transport" << endl;
    
    while (!beam.empty() && iteration < maxIterations) {
        vector<SearchState> nextStates;
        
        // 現在のビームから次の状態を生成
        int statesProcessed = 0;
        while (!beam.empty() && statesProcessed < beamWidth) {
            SearchState current = beam.top();
            beam.pop();
            statesProcessed++;
            
            // 対象行の箱が全て運搬完了したかチェック
            int currentRowBoxes = 0;
            for (int col = 0; col < 20; col++) {
                if (current.hasBox[targetRow][col]) {
                    currentRowBoxes++;
                }
            }
            
            if (currentRowBoxes == 0) {
                // 対象行の全箱が運搬完了
                completedStates.push_back(current);
                continue;
            }
            
            // 改善された状態展開
            vector<SearchState> expanded = expandStateAdvanced(current, originalBoard, targetRow);
            nextStates.insert(nextStates.end(), expanded.begin(), expanded.end());
        }
        
        if (nextStates.empty()) {
            break;
        }
        
        // 評価してビーム幅に削減
        sort(nextStates.begin(), nextStates.end(), 
             [](const SearchState& a, const SearchState& b) {
                 return a.score > b.score;
             });
        
        beam = priority_queue<SearchState>();
        int addedStates = 0;
        for (const SearchState& state : nextStates) {
            if (addedStates >= beamWidth) break;
            beam.push(state);
            addedStates++;
        }
        
        iteration++;
    }
    
    // 完了状態の中で移動回数が最小のものを選択
    if (completedStates.empty()) {
        // cerr << "Row " << targetRow << ": Failed to complete all boxes, trying fallback" << endl;
        // フォールバック戦略
        return fallbackStrategyForRow(currentGame, targetRow, originalBoard);
    }
    
    sort(completedStates.begin(), completedStates.end(), 
         [](const SearchState& a, const SearchState& b) {
             return a.moveCount < b.moveCount;
         });
    
    SearchState bestCompleted = completedStates[0];
    // cerr << "Row " << targetRow << ": Completed with " << bestCompleted.moveCount << " moves" << endl;
    
    return bestCompleted.actionHistory;
}

// フォールバック戦略：貪欲アルゴリズム
vector<Action> fallbackStrategyForRow(GameState& currentGame, int targetRow, 
                                     const vector<vector<Box>>& originalBoard) {
    vector<Action> solution;
    SearchState state(currentGame);
    
    // 対象行の残り箱を全て個別に運搬
    for (int col = 0; col < 20; col++) {
        if (state.hasBox[targetRow][col]) {
            Position targetPos(targetRow, col);
            
            // 箱まで移動
            vector<Action> moveToBox = generateMovePath(state.pos, targetPos);
            for (const Action& action : moveToBox) {
                solution.push_back(action);
                if (simulateActions(state, {action}, originalBoard)) {
                    // 成功
                } else {
                    // cerr << "Fallback failed at move to box" << endl;
                    return solution;
                }
            }
            
            // 箱を拾う
            solution.push_back(Action(PICK_UP));
            if (simulateActions(state, {Action(PICK_UP)}, originalBoard)) {
                // 成功
            } else {
                // cerr << "Fallback failed at pick up" << endl;
                return solution;
            }
            
            // 出入り口まで移動
            vector<Action> moveToExit = generateMovePath(targetPos, Position(0, 0));
            for (const Action& action : moveToExit) {
                solution.push_back(action);
                if (simulateActions(state, {action}, originalBoard)) {
                    // 成功
                } else {
                    // cerr << "Fallback failed at move to exit" << endl;
                    return solution;
                }
            }
        }
    }
    
    // cerr << "Row " << targetRow << ": Fallback completed" << endl;
    return solution;
}

// 特定の行に特化した状態展開
vector<SearchState> expandStateForRow(const SearchState& current, 
                                     const vector<vector<Box>>& originalBoard, 
                                     int targetRow) {
    return expandStateAdvanced(current, originalBoard, targetRow);
}

// 行に特化した評価関数
double evaluateForRow(const SearchState& state, int targetRow) {
    // 対象行の残り箱数
    int remainingInRow = 0;
    for (int col = 0; col < 20; col++) {
        if (state.hasBox[targetRow][col]) {
            remainingInRow++;
        }
    }
    
    if (remainingInRow == 0) {
        // 行の全箱が完了：移動回数を最小化
        return 100000.0 - state.moveCount;
    }
    
    // 行の進捗を重視
    int totalInRow = 20; // 1行の最大箱数（(0,0)を除く）
    if (targetRow == 0) totalInRow = 19; // 0行目は(0,0)を除く
    
    double progress = (double)(totalInRow - remainingInRow) / totalInRow;
    double efficiency = state.moveCount > 0 ? progress / state.moveCount : progress;
    
    return progress * 10000 + efficiency * 1000 - state.moveCount * 0.1;
}

// 行ごとにビームサーチを実行するメイン関数（改善版）
vector<Action> solveRowByRowBeamSearch(GameState& game) {
    vector<Action> totalSolution;
    GameState currentGame = game; // ゲーム状態のコピー
    
    // 各行を順次処理（0行目から）
    for (int row = 19; row >= 0; row--) {
        // この行に箱があるかチェック
        bool hasBoxInRow = false;
        for (int col = 0; col < 20; col++) {
            if (row == 0 && col == 0) continue; // (0,0)はスキップ
            if (currentGame.hasBoxAt(Position(row, col))) {
                hasBoxInRow = true;
                break;
            }
        }
        
        if (!hasBoxInRow) {
            continue;
        }
        
        // この行に対してビームサーチ実行
        vector<Action> rowSolution = beamSearchForRow(currentGame, row);
        
        if (rowSolution.empty()) {
            // cerr << "Row " << row << ": No solution found, skipping" << endl;
            continue;
        }
        
        // 解をメイン解に追加
        totalSolution.insert(totalSolution.end(), rowSolution.begin(), rowSolution.end());
        
        // ゲーム状態を更新
        for (const Action& action : rowSolution) {
            if (!currentGame.executeAction(action)) {
                // cerr << "Failed to execute action in row " << row << endl;
                break;
            }
        }
        
        // cerr << "Row " << row << ": Solution applied, remaining total boxes: " 
            //  << currentGame.getRemainingBoxCount() << endl;
    }
    
    // 残り箱があれば最終クリーンアップ
    if (currentGame.getRemainingBoxCount() > 0) {
        // cerr << "Final cleanup: " << currentGame.getRemainingBoxCount() << " boxes remaining" << endl;
        vector<Action> cleanupSolution = finalCleanup(currentGame);
        totalSolution.insert(totalSolution.end(), cleanupSolution.begin(), cleanupSolution.end());
    }
    
    return totalSolution;
}

// 最終クリーンアップ戦略
vector<Action> finalCleanup(GameState& game) {
    vector<Action> solution;
    
    // 残り箱を全て個別に運搬
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (game.hasBoxAt(Position(i, j))) {
                Position targetPos(i, j);
                Position currentPos = game.getCurrentPosition();
                
                // 箱まで移動
                vector<Action> moveToBox = generateMovePath(currentPos, targetPos);
                for (const Action& action : moveToBox) {
                    solution.push_back(action);
                    game.executeAction(action);
                }
                
                // 箱を拾う
                if (game.canPickUp()) {
                    solution.push_back(Action(PICK_UP));
                    game.executeAction(Action(PICK_UP));
                }
                
                // 出入り口まで移動
                vector<Action> moveToExit = generateMovePath(targetPos, Position(0, 0));
                for (const Action& action : moveToExit) {
                    solution.push_back(action);
                    game.executeAction(action);
                }
                
                currentPos = Position(0, 0);
            }
        }
    }
    
    return solution;
}

int main() {
    // chrono::system_clock::time_point start = chrono::system_clock::now();

    GameState game;
    game.initialize();
    
    // 行ごとにビームサーチを実行
    vector<Action> solution = solveRowByRowBeamSearch(game);
    
    // 解の出力
    for (const Action& action : solution) {
        cout << action.getChar() << endl;
    }

    // chrono::system_clock::time_point end = chrono::system_clock::now();
    // chrono::duration<double> elapsed = end - start;
    // cerr << "Time: " << elapsed.count() << " seconds" << endl;
    
    return 0;
}
