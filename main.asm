format pe64 efi
entry main

include "main.inc" ; ###

section ".text" executable

main:
    mov [SystemTable], rdx
    
    mov rcx, string
    call print

    call shell_main 
 
    ret


print:
    mov rdx, rcx
    mov rcx, [SystemTable]
    mov rcx, [rcx+EFI_SYSTEM_TABLE.ConOut]
    mov rax, [rcx+EFI_SIMPLE_OUTPUT_PROTOCOL.OutputString]
    call rax

get_char:
    push 0x00
    mov rcx, [SystemTable]
    mov rcx, [rcx+EFI_SYSTEM_TABLE.ConIn]
    mov rax, [rcx+EFI_SIMPLE_INPUT_PROTOCOL.ReadKeyStroke]
    mov rdx, rsp
    call rax
    cmp rax, 0x6
    je .none
    xor rax, rax
    mov ax, [rsp+2]
    pop rcx
    ret
.none:
    xor rax, rax
    ret

get_line: ; rcx is buffer, rdx is buffer length
    sub rdx, 0x4
    push rbx
    xor rbx, rbx
.loop:
    push rdx
    push rcx
    call get_char
    pop rcx
    pop rdx
    or rax, rax
    jz .loop
    push rdx
    push rcx
    push 0x00
    push rax
    mov rcx, rsp
    call print
    pop rax
    pop rdi
    pop rcx
    pop rdx
    
    lea rdi, [rcx+rbx]
    mov [rdi], ax
    add rbx, 2
    CMP Rbx, rdx
    jge .too_long
    cmp rax, 0x000D
    je .loop_end
    jmp .loop
.loop_end:
    lea rdi, [rcx+rbx]
    mov dword [rdi], 0x000A
    add rdi, 2
    mov dword [rdi], 0x0000
    pop rbx
    push 0x0
    push 0x000D000A
    mov rcx, rsp
    call print
    pop rdi
    pop rdi
    ret
.too_long:
    mov dword [rcx], 0x0
    mov rcx, input_too_long_emsg
    call print
    pop rbx
    ret

strcmp:
    push rbx
    xor rdi, rdi
.loop:
    mov ax, [rcx+rdi]
    mov bx, [rdx+rdi]
    cmp bx, ax
    jne .isnt
    cmp ax, 0x0
    je .is
    add rdi, 2
    jmp .loop
.is:
    mov rax, 0x1
    pop rbx
    ret
.isnt:
    xor rax, rax
    pop rbx
    ret

include "shell.inc"

section ".data" writeable

include "data.inc"

SystemTable: dq ?
ShellInput: dw 1024 dup 0
string: du "Hello World!", 0x000A, 0x000D, 0x0000
main_terminal_string: du " > ", 0x0000
input_too_long_emsg:
    du "Error input too long!", 0x000A, 0x000D, 0x0000
