# AHC048 パラメータ最適化ツール

このツールは、AtCoder Heuristic Contest 048「Mixing on the Palette」問題の解答プログラムにおけるパラメータを自動的に最適化するためのフレームワークです。

## 🚀 クイックスタート

```bash
# 簡単な最適化を実行
./optimize_params.sh quick

# より詳細な最適化
./optimize_params.sh full
```

## 📋 最適化可能なパラメータ

### 焼きなまし法パラメータ
- `timeLimit`: 実行時間制限（デフォルト: 2.8秒）
- `startTemp`: 開始温度（デフォルト: 100.0）
- `endTemp`: 終了温度（デフォルト: 0.1）

### 戦略パラメータ
- `baseQualityThreshold`: 基本品質閾値（デフォルト: 0.4）
- `urgencyMultiplier`: 緊急度乗数（デフォルト: 0.3）
- `urgencyThreshold`: 緊急度閾値（デフォルト: 0.5）
- `relaxedQualityThreshold`: 緩い品質閾値（デフォルト: 0.6）
- `consecutiveFailureLimit`: 連続失敗限界（デフォルト: 3）

### 評価関数パラメータ
- `capacityWeight`: 容量重み（デフォルト: 10.0）
- `colorDistanceWeight`: 色距離重み（デフォルト: 100.0）
- `emptyWellColorWeight`: 空ウェル色重み（デフォルト: 50.0）
- `topTubeCount`: 上位チューブ数（デフォルト: 3）

### ウェル選択パラメータ（新機能）
- `randomWellProbability`: ランダムウェル選択確率（デフォルト: 0.3）
- `explorationBonus`: 探索ボーナス重み（デフォルト: 2.0）
- `adaptiveWellSelection`: 適応的ウェル選択の有効化（デフォルト: true）
- `adaptationRate`: 適応率（デフォルト: 0.1）
- `diversityCheckCount`: 多様性チェック対象数（デフォルト: 5）

## 🛠️ 使用方法

### 1. Makefileを使用

```bash
# コンパイル
make all

# パラメータ最適化の実行
make optimize          # クイック最適化
make grid-search      # グリッドサーチ
make genetic          # 遺伝的アルゴリズム
make full-optimize    # フル最適化

# 結果の確認
make check-results

# クリーンアップ
make clean
```

### 2. 最適化スクリプトを使用

```bash
# ヘルプ表示
./optimize_params.sh help

# 各種最適化の実行
./optimize_params.sh quick           # 30回のランダムサーチ
./optimize_params.sh random 100     # 100回のランダムサーチ
./optimize_params.sh grid           # グリッドサーチ
./optimize_params.sh genetic        # 遺伝的アルゴリズム
./optimize_params.sh full           # 全手法を順次実行
```

### 3. 直接実行

```bash
# コンパイル
g++ -std=c++17 -O2 -o parameter_optimizer parameter_optimizer.cpp

# 実行
./parameter_optimizer random 50
./parameter_optimizer grid
./parameter_optimizer genetic
```

## 📊 最適化手法

### 1. ランダムサーチ
- **概要**: パラメータをランダムに生成して評価
- **利点**: 高速、実装が簡単
- **用途**: 初期探索、ベースライン設定

### 2. グリッドサーチ
- **概要**: 主要パラメータの格子点を系統的に探索
- **利点**: 確実性が高い、再現性がある
- **用途**: 重要パラメータの精密調整

### 3. 遺伝的アルゴリズム
- **概要**: 生物の進化を模倣した最適化手法
- **利点**: 局所最適解の回避、複雑な相互作用の考慮
- **用途**: 高精度な最適化、複数パラメータの同時調整

## 📈 結果の評価

### 出力ファイル
- `random_search_results.txt`: ランダムサーチの結果
- `grid_search_results.txt`: グリッドサーチの結果
- `genetic_results.txt`: 遺伝的アルゴリズムの結果

### 評価指標
各パラメータセットは以下の指標で評価されます：
```
Score = 1 + D × (V - H) + round(10^4 × E)
```
- `V`: チューブ使用回数
- `H`: 目標色数
- `D`: チューブコスト
- `E`: 色誤差の合計

## 🔧 カスタマイズ

### テストケースの追加
1. `test_input.txt`, `test_advanced.txt`, `test_complex.txt` を用意
2. 以下の形式で記述:
```
N K H T D
c1 m1 y1    # チューブ色1
c2 m2 y2    # チューブ色2
...
target_c1 target_m1 target_y1    # 目標色1
target_c2 target_m2 target_y2    # 目標色2
...
```

### パラメータ範囲の調整
`ParameterOptimizer::generateRandomParams()` 関数内で各パラメータの範囲を変更できます。

### 新しい最適化手法の追加
1. `ParameterOptimizer` クラスに新しいメソッドを追加
2. `ParameterTuner` クラスに対応する実行メソッドを追加
3. Makefile とスクリプトにターゲットを追加

## 📝 ベストプラクティス

### 1. 段階的最適化
```bash
# ステップ1: 粗い探索
./optimize_params.sh random 50

# ステップ2: 有望領域の詳細探索
./optimize_params.sh grid

# ステップ3: 微調整
./optimize_params.sh genetic
```

### 2. パラメータ適用
最適化後、得られたパラメータを `main.cpp` に適用：
```cpp
// デフォルトパラメータを最適化結果で更新
OptimizationParams defaultParams;
defaultParams.timeLimit = 2.5;          // 最適化結果から
defaultParams.startTemp = 150.0;        // 最適化結果から
defaultParams.baseQualityThreshold = 0.35;  // 最適化結果から
// ... 他のパラメータも同様に更新
```

### 3. 検証
```bash
# 最適化前のスコア記録
make benchmark > before_optimization.txt

# パラメータ適用後
make benchmark > after_optimization.txt

# 改善を確認
diff before_optimization.txt after_optimization.txt
```

## 🐛 トラブルシューティング

### コンパイルエラー
```bash
# C++17対応コンパイラの確認
g++ --version

# 必要に応じてアップデート
# macOS: brew install gcc
# Ubuntu: sudo apt install g++
```

### 実行時エラー
```bash
# テストファイルの確認
ls -la test_*.txt

# 権限の確認
chmod +x optimize_params.sh

# デバッグビルド
make debug
```

### メモリ不足
```bash
# 最適化の規模を縮小
./optimize_params.sh random 10    # 少ないイテレーション
```

## 📚 参考情報

### アルゴリズム理論
- [焼きなまし法](https://ja.wikipedia.org/wiki/焼きなまし法)
- [遺伝的アルゴリズム](https://ja.wikipedia.org/wiki/遺伝的アルゴリズム)
- [グリッドサーチ](https://scikit-learn.org/stable/modules/grid_search.html)

### AtCoder関連
- [AtCoder Heuristic Contest](https://atcoder.jp/contests/archive?ratedType=3)
- [競技プログラミングにおけるパラメータ調整](https://qiita.com/thun-c/items/058743a25c37c87b8aa4)

## 🤝 貢献

バグ報告や改善提案は Issue または Pull Request でお願いします。

## 📄 ライセンス

このツールは MIT ライセンスの下で公開されています。 
