CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = main
OPTIMIZER = parameter_optimizer
TEST_FILES = test_input.txt test_advanced.txt test_complex.txt

# デフォルトターゲット
all: $(TARGET)

# メインプログラムのコンパイル
$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp

# パラメータ最適化プログラムのコンパイル
$(OPTIMIZER): simple_optimizer.cpp
	$(CXX) $(CXXFLAGS) -o $(OPTIMIZER) simple_optimizer.cpp

# パラメータ最適化の実行
optimize: $(OPTIMIZER)
	./$(OPTIMIZER) random 30

# グリッドサーチの実行
grid-search: $(OPTIMIZER)
	./$(OPTIMIZER) grid

# 遺伝的アルゴリズムの実行
genetic: $(OPTIMIZER)
	./$(OPTIMIZER) genetic

# フル最適化の実行
full-optimize: $(OPTIMIZER)
	./$(OPTIMIZER) full

# 実行
run: $(TARGET)
	./$(TARGET) < test_input.txt

# テスト実行
test: $(TARGET)
	@echo "Running tests..."
	@for file in $(TEST_FILES); do \
		if [ -f $$file ]; then \
			echo "Testing with $$file"; \
			./$(TARGET) < $$file > output_$$file; \
		fi; \
	done

# 結果の確認
check-results:
	@echo "Optimization Results:"
	@echo "===================="
	@for file in *_results.txt; do \
		if [ -f $$file ]; then \
			echo "--- $$file ---"; \
			cat $$file; \
			echo ""; \
		fi; \
	done

# ベンチマーク実行
benchmark: $(TARGET)
	@echo "Running benchmark..."
	@time ./$(TARGET) < test_input.txt > /dev/null

# クリーンアップ
clean:
	rm -f $(TARGET) $(OPTIMIZER) *.txt output_* default_test.txt *_results.txt

# デバッグビルド
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

# プロファイリング用ビルド
profile: CXXFLAGS += -pg
profile: $(TARGET)

# ヘルプ
help:
	@echo "Available targets:"
	@echo "  all          - Build main program"
	@echo "  optimize     - Run quick parameter optimization (30 random trials)"
	@echo "  grid-search  - Run grid search optimization"
	@echo "  genetic      - Run genetic algorithm optimization"
	@echo "  full-optimize- Run comprehensive optimization (all methods)"
	@echo "  run          - Run main program with test_input.txt"
	@echo "  test         - Run tests on all available test files"
	@echo "  check-results- Display optimization results"
	@echo "  benchmark    - Run timing benchmark"
	@echo "  clean        - Clean all generated files"
	@echo "  debug        - Build with debug symbols"
	@echo "  profile      - Build with profiling support"

.PHONY: all optimize grid-search genetic full-optimize run test check-results benchmark clean debug profile help 
