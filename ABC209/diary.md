2024/12/13

ABC209
バーチャル参加

[A] 2:11(1)

a以上b以下の個数はa < bの時b - (a - 1)、それ以外の時0<br>
サンプルを全然確認していなくて1ペナを踏んでしまった；；<br>

[B] 5:14

iが偶数の時ans += (a[i]-1)、奇数の時ans += a[i]を計算してans > xの時No、それ以外の時Yes<br>
実装するだけ

[C] 19:24

条件が厳しくないのでcをsortする。i番目(0-idx)を見ているときdp[i+1] = dp[i] * (c[i]-i)<br>
ただし、i+1 > c[i]の時は0を出力<br>
選べるパターン数がc[i]-iで求まるのでパターン数を掛けていくと答え<br>

[D] 89:29(1)

https://qiita.com/recuraki/items/72e37eb9be9f71bc623a#lca<br>
https://wk1080id.hatenablog.com/entry/2020/05/30/004858<br>
https://atcoder.github.io/ac-library/production/document_ja/segtree.html<br>
クエリなので毎回最短経路を求めている暇はない。辺の本数がN-1本でかつすべての頂点が繋がっているのでオイラーツアー＋LCA＋セグ木で答える。<br>
この方法を調べて初めて知ったけど実装できてよかった。もっと簡単な解法があったっぽい？<br>
セグ木のサイズが制約より小さくて1ペナ(RE)
