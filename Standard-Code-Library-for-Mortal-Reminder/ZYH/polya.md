###burnside引理
设$G$为置换群。
$C(f)$为$f$置换下不动点的个数。
$N(G,C)={1 \over |G|} \sum _{f \in G} |C(f)|$
###polay定理
设$\#f$为$f$的循环数。
设$k$表示染色的颜色数。
Polya定理描述为：$N(G,C)={1 \over |G|}\sum _{f \in G}k^{\#f}$
###生成函数
设$e_i$为$f$的循环分解中长度为$i$的循环的个数。
$N(G,C)={1 \over |G|}\sum _{f \in G} \prod_{i=1} ^n z_i ^{e_i}={1 \over |G|}\sum _{f \in G}k^{\sum_{i=1} ^n e_i} = {1 \over |G|}\sum _{f \in G} \prod_{i=1}^n k^{e_i}$
将$k$用生成函数$(r^i + b^i + g^i)$代替
$r^nb^mg^x$的系数为答案。