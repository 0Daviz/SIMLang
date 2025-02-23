# SIMLang
Installation & Usage

    Clone repository:
git clone https://github.com/0Daviz/SIMLang.git
cd SIMLang
    Compile a SIMLang program:
make input.sim

    Execute the compiled program:
./out
echo $?  # View exit status

Compilation Process

    Tokenization (tokeny function)

        Identifies:

            return keyword

            Integer literals

            Semicolon terminator

    Assembly Generation (to_asm function)

        Produces x86_64 Linux assembly:
    global _start
    _start:
        mov rax, 60         ;sys_exit system call
        mov rdi, <value>    ;exit status value
        syscall
