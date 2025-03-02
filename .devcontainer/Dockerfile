# syntax=docker/dockerfile:latest

FROM ubuntu:22.04

# 必要なパッケージをインストール
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential g++ cmake python3 python3-pip python3-venv \
    pypy3 pypy3-dev \
    rustc cargo \
    golang \
    git curl unzip wget \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# C++ / Python / Rust / Go 用の AtCoder 環境
RUN pip3 install --no-cache-dir online-judge-tools

# Go の開発環境をセットアップ
ENV GOPATH="/go"
ENV PATH="${GOPATH}/bin:/usr/local/go/bin:${PATH}"
RUN go version

# AtCoder の作業フォルダを作成
WORKDIR /workspace

CMD ["/bin/bash"]
