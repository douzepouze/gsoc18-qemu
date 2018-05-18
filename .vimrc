" QEMU .vimrc

set tabstop=4 " Four columns in a tab
set expandtab " In insert mode insert spaces instead of tabs when tab key is hit
set shiftwidth=4 " Count of columns to be used with reindet operations (<< and >>)
set colorcolumn=80 " Insert coloured colum at max line length
highlight ColorColumn ctermbg=darkgray 

" Filetype detection
augroup project
    autocmd!
    autocmd BufRead,BufNewFile *.h,*.c set filetype=c
augroup END

" Vim search path for gf (open file under cursor) command
set path +=qemu/include

" includeexpr is used by vim to transform a string into a file name with gf command
" set includeexpr=substitute(v:fname,'\\.','/','g')

