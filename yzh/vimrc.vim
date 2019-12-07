source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
behave mswin
set hlsearch ci ai si nu ts=4 sw=4
color slate
map <F9> : ! g++ % -o %< -g -Wall -Wextra -Wconversion -Wshadow -std=c++11 <CR>
map <F5> : ! time ./%< <CR>
map <F8> : ! time ./%< < %<.in <CR>
map <F12> :r std.cpp <CR> ggdd : 15 <CR>