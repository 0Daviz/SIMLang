#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <optional>

enum class TokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    TokenType type;
    std::optional<std::string> value;

    Token(TokenType type, std::optional<std::string> value = std::nullopt)
        : type(type), value(value) {}
};

std::vector<Token> tokeny(const std::string& source) {
    std::vector<Token> tokens;
    std::string current_lexeme;

    for (size_t i = 0; i < source.length(); ++i) {
        const char c = source[i];

        if (std::isalpha(c)) {
            current_lexeme.push_back(c);
            ++i;
            while (i < source.length() && std::isalnum(source[i])) {
                current_lexeme.push_back(source[i]);
                ++i;
            }
            --i;

            if (current_lexeme == "return") {
                tokens.emplace_back(TokenType::_return);
            } else {
                std::cerr << "IT'S OVER." << std::endl;
                exit(EXIT_FAILURE);
            }
            current_lexeme.clear();

        } else if (std::isdigit(c)) {
            current_lexeme.push_back(c);
            ++i;
            while (i < source.length() && std::isdigit(source[i])) {
                current_lexeme.push_back(source[i]);
                ++i;
            }
            --i;

            tokens.emplace_back(TokenType::int_lit, current_lexeme);
            current_lexeme.clear();

        } else if (c == ';') {
            tokens.emplace_back(TokenType::semi);
        } else if (std::isspace(c)) {
            //white space
            continue;
        } else {
            std::cerr << "IT'S OVER." << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}

std::string to_asm(const std::vector<Token>& tokens) {
    std::stringstream output;
    output << "global _start\n_start:\n";
    for (size_t i = 0; i < tokens.size(); ++i) {
        const Token& token = tokens[i];

        if (token.type == TokenType::_return) {
            if (i + 2 < tokens.size() &&
                tokens[i+1].type == TokenType::int_lit &&
                tokens[i+2].type == TokenType::semi) {
                
                output << "    mov rax, 60\n"
                       << "    mov rdi, " << tokens[i+1].value.value() << "\n"
                       << "    syscall\n";
                i += 2;
            }
        }
    }

    return output.str();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "no no\n./main <something.sim>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string contents;
    if (std::ifstream input{argv[1]}) {
        contents.assign(std::istreambuf_iterator<char>(input), {});
    }
    const auto tokens = tokeny(contents);
    //std::cout << to_asm(tokens) << std::endl;
    std::ofstream("out.asm") << to_asm(tokens);
    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}