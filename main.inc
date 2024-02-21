macro STRUCT name {
    virtual at 0  
        name name 
    end virtual   
} 

struc M16 {
    align 2
    . dw ?
}
struc M32 {
    align 4
    . dd ?
}
struc M64 {
    align 8
    . dq ?
}
struc MHDR {
    align 8
    . db 24 dup ?
}
struc EFI_SYSTEM_TABLE {
    align 8
    .Hdr MHDR
    .FirmwareVendor M64
    .FirmwareRevision M32
    .ConsoleInHandle M64
    .ConIn M64
    .ConsoleOutHandle M64
    .ConOut M64
    .StandardErrorHandle M64
    .StdErr M64
    .RuntimeServices M64
    .BootServices M64
    .NumberOfTableEntries M64
    .ConfigurationTable M64
}
struc EFI_SIMPLE_OUTPUT_PROTOCOL {
    .Reset M64
    .OutputString M64
    .TestString M64
    .QueryMode M64
    .SetMode M64
    .ClearScreen M64
    .SetCursorPosition M64
    .EnableCursor M64
    .Mode M64
}
struc EFI_SIMPLE_INPUT_PROTOCOL {
    .Reset M64
    .ReadKeyStroke M64
    .Key M64
}
struc EFI_INPUT_KEY {
    .ScanCode M16
    .UnicodeChar M16
}
struc EFI_RUNTIME_SERVICES {
    .Hdr MHDR
    .GetTime M64
    .SetTime M64
    .GetWakeupTime M64
    .SetWakeupTime M64
    .SetVirtualAddress M64
    .ConvertPointer M64
    .GetVariable M64
    .GetNextVariable M64
    .SetVariable M64
    .GetNextHighMonotonicCount M64
    .ResetSystem M64
    .UpdateCapsule M64
    .QueryCapsuleCapabilities M64
    .QueryVariableInfo M64
}
STRUCT EFI_INPUT_KEY
STRUCT EFI_SYSTEM_TABLE
STRUCT EFI_SIMPLE_OUTPUT_PROTOCOL
STRUCT EFI_SIMPLE_INPUT_PROTOCOL
STRUCT EFI_RUNTIME_SERVICES

SHELL_LEN = 2048
