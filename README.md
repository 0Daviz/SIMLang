# SIMLang

A minimal compiler it can't get more minimal then this

## 🚀 Quick Start

```bash
# Clone repository
git clone https://github.com/0Daviz/SIMLang.git
cd SIMLang

# Compile example program
make main

# Execute compiled binary
./main main.sim
echo $?  # Should show 42 (let's say inside of main.sim it's return 42;)
```

## 📖 Language Syntax

SIMLang currently supports exactly one statement format:

```sim
return <integer>;
```

### Valid Example
```sim
return 0;
```

### Invalid Example
```sim
return 3.14;  # Error: No decimal support
```

## 🔧 Compilation Pipeline

1. **Tokenization** (lexical analysis)
2. **Assembly Generation**
3. **Binary Linking**

## 🧠 Internal Representation

### Token Types
```cpp
enum class TokenType {
    _return,
    int_lit,
    semi
};
```

### Sample Assembly Output
```asm
global _start
_start:
    mov rax, 60     ; SYS_exit
    mov rdi, 42     ; Exit code
    syscall
```

## 🚨 Error Handling

```sim
return missing_semi  # Triggers error
```

```text
IT'S OVER.
```


IT'S SO OVER.
Making this README was more pain in the ass then making this simple compiler.
