se et ts=4 sw=4 sts=4 nu sc sm lbr is hls mouse=a
sy on
ino <tab> <c-n>
ino <s-tab> <tab>
au bufwinenter * winc L

nm <f6> ggVG"+y
nm <f7> :w<cr>:!rm ##<cr>:make<cr>
nm <f8> :!@@<cr>
nm <f9> :!@@ < in<cr>
nm <s-f9> :!(time @@ < in &> out) &>> out<cr>:sp out<cr>

au filetype cpp cm @@ ./a.out | cm ## a.out | se cin fdm=syntax mp=g++\ %\ -std=c++11\ -Wall\ -Wextra\ -Wconversion\ -O2

map <c-p> :ha<cr>
se pheader=%N@%F

au filetype java cm @@ java %< | cm ## %<.class | se cin fdm=syntax mp=javac\ %
au filetype python cm @@ python % | se si fdm=indent
au bufenter *.kt setf kotlin
au filetype kotlin cm @@ kotlin _%<Kt | cm ## _%<Kt.class | se si mp=kotlinc\ %
