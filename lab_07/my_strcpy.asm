section .text

global my_strcpy

my_strcpy:
    mov rbx, rdi
    mov rcx, rdx
    
    cmp rdi, rsi
    jbe copy  

    mov rax, rdi
    sub rax, rsi
    cmp rax, rcx
    ja copy      
    
    
    add rdi, rcx
    dec rdi
    add rsi, rcx
    dec rsi    
    std       

copy:
    rep movsb    ; Команда MOVSB копирует один байт из ячейки памяти по адресу DS:SI в ячейку памяти по адресу ES:DI.
        		 ; После выполнения команды, регистры SI и DI увеличиваются на 1, если флаг DF = 0, или уменьшаются на 1, если DF = 1.
        		 ; Если команда используется в 32-разрядном режиме адресации, то используются регистры ESI и EDI соответственно.
    cld          ; очищает флаг направления (DF)
    mov rax, rbx  
ret