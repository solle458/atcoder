#!/bin/bash

# パラメータ最適化スクリプト
# Usage: ./optimize_params.sh [mode] [iterations]

set -e

# デフォルト値
MODE=${1:-"quick"}
ITERATIONS=${2:-30}

# 色付きの出力関数
print_header() {
    echo -e "\033[1;34m=== $1 ===\033[0m"
}

print_success() {
    echo -e "\033[1;32m✓ $1\033[0m"
}

print_warning() {
    echo -e "\033[1;33m⚠ $1\033[0m"
}

print_error() {
    echo -e "\033[1;31m✗ $1\033[0m"
}

# ヘルプ表示
show_help() {
    echo "Parameter Optimization Tool for AHC048"
    echo "Usage: $0 [mode] [iterations]"
    echo ""
    echo "Modes:"
    echo "  quick    - Quick random search (default, 30 iterations)"
    echo "  random   - Random search with custom iterations"
    echo "  grid     - Grid search optimization"
    echo "  genetic  - Genetic algorithm optimization"
    echo "  full     - Comprehensive optimization (all methods)"
    echo "  help     - Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 quick           # Quick optimization"
    echo "  $0 random 100     # Random search with 100 iterations"
    echo "  $0 grid           # Grid search"
    echo "  $0 genetic        # Genetic algorithm"
    echo "  $0 full           # Full optimization suite"
}

# 前提条件の確認
check_prerequisites() {
    print_header "Checking Prerequisites"
    
    # コンパイラの確認
    if ! command -v g++ &> /dev/null; then
        print_error "g++ compiler not found"
        exit 1
    fi
    print_success "g++ compiler found"
    
    # makeの確認
    if ! command -v make &> /dev/null; then
        print_error "make not found"
        exit 1
    fi
    print_success "make found"
    
    # ソースファイルの確認
    if [[ ! -f "main.cpp" ]]; then
        print_error "main.cpp not found"
        exit 1
    fi
    print_success "main.cpp found"
    
    # テストファイルの確認
    test_files_found=0
    for file in test_input.txt test_advanced.txt test_complex.txt; do
        if [[ -f "$file" ]]; then
            ((test_files_found++))
        fi
    done
    
    if [[ $test_files_found -eq 0 ]]; then
        print_warning "No test files found, will create default test case"
    else
        print_success "$test_files_found test files found"
    fi
}

# 進捗表示
show_progress() {
    local current=$1
    local total=$2
    local percentage=$(( current * 100 / total ))
    local filled=$(( percentage / 2 ))
    local empty=$(( 50 - filled ))
    
    printf "\rProgress: ["
    printf "%${filled}s" | tr ' ' '='
    printf "%${empty}s" | tr ' ' '-'
    printf "] %d%% (%d/%d)" $percentage $current $total
}

# 最適化実行
run_optimization() {
    local mode=$1
    local iterations=$2
    
    print_header "Starting Parameter Optimization"
    echo "Mode: $mode"
    if [[ "$mode" == "random" || "$mode" == "quick" ]]; then
        echo "Iterations: $iterations"
    fi
    echo "Timestamp: $(date)"
    echo ""
    
    # ビルド
    print_header "Building Optimizer"
    make parameter_optimizer
    print_success "Build completed"
    
    # 最適化実行
    print_header "Running Optimization"
    case $mode in
        "quick"|"random")
            ./parameter_optimizer random $iterations
            ;;
        "grid")
            ./parameter_optimizer grid
            ;;
        "genetic"|"full")
            print_warning "Genetic algorithm not implemented in simple version. Running grid search instead."
            ./parameter_optimizer grid
            ;;
        *)
            print_error "Unknown mode: $mode"
            exit 1
            ;;
    esac
    
    print_success "Optimization completed"
}

# 結果の表示
show_results() {
    print_header "Optimization Results"
    
    if ls *_results.txt 1> /dev/null 2>&1; then
        for file in *_results.txt; do
            echo ""
            echo "📊 $file:"
            echo "$(head -n 20 "$file")"
            echo ""
        done
    else
        print_warning "No result files found"
    fi
}

# ベンチマーク実行
run_benchmark() {
    if [[ -f "main" ]]; then
        print_header "Running Benchmark"
        echo "Testing performance with optimized parameters..."
        
        if [[ -f "test_input.txt" ]]; then
            time ./main < test_input.txt > /dev/null
            print_success "Benchmark completed"
        else
            print_warning "test_input.txt not found, skipping benchmark"
        fi
    fi
}

# 結果のエクスポート
export_results() {
    local timestamp=$(date +"%Y%m%d_%H%M%S")
    local export_dir="optimization_results_${timestamp}"
    
    print_header "Exporting Results"
    mkdir -p "$export_dir"
    
    # 結果ファイルをコピー
    for file in *_results.txt; do
        if [[ -f "$file" ]]; then
            cp "$file" "$export_dir/"
        fi
    done
    
    # 設定ファイルを作成
    cat > "$export_dir/optimization_config.txt" << EOF
Optimization Configuration
=========================
Mode: $MODE
Iterations: $ITERATIONS
Timestamp: $(date)
System: $(uname -a)
Compiler: $(g++ --version | head -n 1)
EOF
    
    print_success "Results exported to $export_dir"
}

# メイン処理
main() {
    case $MODE in
        "help"|"-h"|"--help")
            show_help
            exit 0
            ;;
    esac
    
    print_header "AHC048 Parameter Optimization Tool"
    
    # 前提条件確認
    check_prerequisites
    
    # 最適化実行
    run_optimization "$MODE" "$ITERATIONS"
    
    # 結果表示
    show_results
    
    # ベンチマーク
    run_benchmark
    
    # 結果エクスポート
    export_results
    
    print_header "Optimization Complete"
    print_success "Check the exported results directory for detailed analysis"
    
    # 推奨される次のステップ
    echo ""
    echo "Next steps:"
    echo "1. Review the optimization results"
    echo "2. Update main.cpp with the best parameters"
    echo "3. Run 'make test' to verify improvements"
    echo "4. Submit the optimized solution"
}

# スクリプト実行
main "$@" 
