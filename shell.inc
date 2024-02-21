


shell_main:
.loop:
    mov rcx, shell_intro
    call print
    mov rcx, ShellInput
    mov rdx, SHELL_LEN
    call get_line
; split by spaces
    mov rcx, ShellInput
    xor rdx, rdx
.split:
    mov word ax, [rcx+rdx]
    cmp ax, " "
    jne .nsp
    mov word [rcx+rdx], 0x0
    jmp .nz
.nsp:
    cmp ax, 0x0
    jne .nz
    mov word [rcx+rdx+2], 0x1
    jmp .esplit
.nz:
    add rdx, 0x2
    jmp .split
.esplit:
; call shell_command
    call shell_command
    jmp .loop
.eloop:
    ret

shell_command:
    push rbx
    mov rbx, ShellInput
    mov rdx, rbx
    mov rcx, command_string.SAY
    call strcmp
    or rax,rax
    jz .EXT
    call SHCMD.SAY
    jmp .end
.EXT:
    mov rdx, rbx
    mov rcx, command_string.EXT
    call strcmp
    or rax, rax
    jz .invalid
    call SHCMD.EXT
.end:
    pop rbx
    ret
.invalid:
    mov rcx, err_msg.INVALID_CMD
    call print
    pop rbx
    ret


SHCMD:

.SAY:
    mov rcx, ShellInput
    .SAY.findl:
        cmp word [rcx], 0x0
        je .SAY.efindl
        add rcx, 2
        jmp .SAY.findl
    .SAY.efindl:
    add rcx, 2
    call print
    ret

.EXT:
    mov rax, [SystemTable]
    mov rax, [rax+EFI_SYSTEM_TABLE.RuntimeServices]
    mov rax, [rax+EFI_RUNTIME_SERVICES.ResetSystem]
    mov rcx, 0x2
    mov rdx, 0x0
    mov r8, 0x0
    mov r9, 0x0
    call rax
    ret




