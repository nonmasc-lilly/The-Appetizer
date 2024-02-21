
shell_intro: du "USER> ", 0x0

command_string:
    .EXT:   du "EXT", 0xD, 0xA, 0x0
    .LIST:  du "LIST", 0x0
    .MKDIR: du "MKDIR", 0x0
    .NEW:   du "NEW", 0x0
    .SAY:   du "SAY", 0x0

err_msg:
    .INVALID_CMD: du "invalid command!", 0xA, 0xD, 0x0
    .INVALID_ARGS: du "invalid args!", 0xA, 0xD, 0x0

