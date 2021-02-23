""""""""""""""""
""" DEFAULTS """
""""""""""""""""

syntax on

filetype off
filetype plugin indent on

"" shows normal-mode entries in bottom right
set noerrorbells
set showcmd

"" line numbers + color column
set relativenumber
set number
set tw=79
set nowrap
set fo-=t
set colorcolumn=80

"" tab indentation
set tabstop=4
set softtabstop=4
set shiftwidth=4
set shiftround
set expandtab
set smartindent
set backspace=indent,eol,start

"" better word search
set hlsearch
set incsearch
set ignorecase
set smartcase

"" stop swap files
set nobackup
set nowritebackup
set noswapfile



"""""""""""""""
""" PLUGINS """
"""""""""""""""

call plug#begin('~/.vim/plugged')

"" colorscheme
Plug 'morhetz/gruvbox'

"" fuzzy file finder
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plug 'junegunn/fzf.vim'
Plug 'stsewd/fzf-checkout.vim'

"" coc autocompletion
Plug 'neoclide/coc.nvim', {'branch': 'release'}

"" language pack
Plug 'sheerun/vim-polyglot'

call plug#end()


"" gruvbox colorscheme
colorscheme gruvbox
set background=dark

"" fzf layout
let g:fzf_layout = { 'window': { 'width': 0.8, 'height': 0.8 } }
let $FZF_DEFAULT_OPTS='--reverse'



"""""""""""""""""""
""" KEYBINDINGS """
"""""""""""""""""""

"" toggle splits with vim keys
map <C-h> <C-W>h
map <C-j> <C-W>j
map <C-k> <C-W>k
map <C-l> <C-W>l

"" brace completion for C and java
if expand("%:e") == "c" || expand("%:e") == "java" 
    inoremap {<TAB> {}<ESC>i<CR><ESC>O
endif

"" coc tab completion
function! s:check_back_space() abort
    let col = col('.') - 1
    return !col || getline('.')[col - 1]  =~ '\s'
endfunction

inoremap <silent><expr> <Tab>
    \ pumvisible() ? "\<C-n>" :
    \ <SID>check_back_space() ? "\<Tab>" :
    \ coc#refresh()



""""""""""""""""""""""""""""""""
""" LEADER SHORTCUT MAPPINGS """
""""""""""""""""""""""""""""""""

"" set spacebar as leader
nnoremap <SPACE> <Nop>
let mapleader=" "

"" yank to primary register
nnoremap <leader>y "*y
vnoremap <leader>y "*y

"" fzf git checkout shortcut
nnoremap <leader>gc :GCheckout<CR>

"" write command shortcut
nnoremap <leader><leader> :w<CR>



"""""""""""""""""""""""""
""" COMPILE SHORTCUTS """
"""""""""""""""""""""""""

let extension = expand("%:e")

"" compile and run code writtent in C
if extension  == "c"
    map  <F5> :w <CR> :!clear && gcc % -o %< && ./%<  <CR>

"" compile and run code writtent in C++
elseif extension  == "cpp"
    map  <F5> :w <CR> :!clear && g++ % -o %< && ./%<  <CR>

"" compile and run code writtent in Java
elseif extension == "java"
    map  <F5> :w <CR> :!clear && javac % && java %<  <CR>

"" compile and run code writtent in Python
elseif extension == "py"
    map  <F5> :w <CR> :!clear && python3 %  <CR>
    
"" run a shell script (and make it executable)
elseif extension == "sh"
        map <F5> :w <CR> :!clear && chmod +x % && ./% <CR>

"" compile LaTeX document
elseif extension == "tex"
    map <F5> :w <CR> :!clear && latexmk -pvc -pdf -interaction=nonstopmode %
        \ && open %<.pdf <CR>

endif

