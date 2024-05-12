#include <string>
#include <stack>
#include <iostream>

int main() {

    std::string program;
    std::cin >> program;

    std::string ir;

    std::cout << "; ModuleID = 'brainfuck.c'" << '\n';
    std::cout << "target datalayout = \"e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"" << '\n';
    std::cout << "target triple = \"x86_64-pc-linux-gnu\"" << '\n';
    std::cout << "" << '\n';

    std::cout << "; Function Attrs: noinline nounwind optnone uwtable" << '\n';
    std::cout << "define dso_local i32 @main() #0 {" << '\n';
    std::cout << "  " << "%1 = alloca i8*, align 8" << '\n';
    std::cout << "  " << "%2 = call noalias i8* @calloc(i64 noundef 30000, i64 noundef 1) #3" << '\n';
    std::cout << "  " << "store i8* %2, i8** %1, align 8" << '\n';
    std::cout << "  " << "" << '\n';

    int RegisterID = 2;
    std::stack<int> BracketsStack;

    for(int i = 0; i < program.length(); i++) {

        switch(program[i]) {
            case '>':
                std::cout << "  " << "%" << RegisterID + 1 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = getelementptr inbounds i8, i8* %" << RegisterID + 1 << ", i32 1"<< '\n';
                std::cout << "  " << "store i8* %" << RegisterID + 2 << ", i8** %1, align 8"<< '\n';
                RegisterID += 2;
                break;
            case '<':
                std::cout << "  " << "%" << RegisterID + 1 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = getelementptr inbounds i8, i8* %" << RegisterID + 1 << ", i32 -1"<< '\n';
                std::cout << "  " << "store i8* %" << RegisterID + 2 << ", i8** %1, align 8"<< '\n';
                RegisterID += 2;
                break;
            case '+':
                std::cout << "  " << "%" << RegisterID + 1 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = load i8, i8* %" << RegisterID + 1 << ", align 1"<< '\n';
                std::cout << "  " << "%" << RegisterID + 3 << " = add i8 1, %" << RegisterID + 2 << '\n';
                std::cout << "  " << "store i8 %" << RegisterID + 3 << ", i8* %" << RegisterID + 1 << ", align 1"<< '\n';
                RegisterID += 3;
                break;
            case '-':
                std::cout << "  " << "%" << RegisterID + 1 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = load i8, i8* %" << RegisterID + 1 << ", align 1"<< '\n';
                std::cout << "  " << "%" << RegisterID + 3 << " = add i8 -1, %" << RegisterID + 2 << '\n';
                std::cout << "  " << "store i8 %" << RegisterID + 3 << ", i8* %" << RegisterID + 1 << ", align 1"<< '\n';
                RegisterID += 3;
                break;
            case '.':
                std::cout << "  " << "%" << RegisterID + 1 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = load i8, i8* %" << RegisterID + 1 << ", align 1"<< '\n';
                std::cout << "  " << "%" << RegisterID + 3 << " = sext i8 %" << RegisterID + 2 << " to i32" << '\n';
                std::cout << "  " << "%" << RegisterID + 4 << " = call i32 @putchar(i32 noundef %" << RegisterID + 3 << ")" << '\n';
                RegisterID += 4;
                break;
            case ',':
                std::cout << "  " << "%" << RegisterID + 1 << " = call i32 @getchar()"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = trunc i32 %" << RegisterID + 1 << " to i8" << '\n';
                std::cout << "  " << "%" << RegisterID + 3 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "store i8 %" << RegisterID + 2 << ", i8* %" << RegisterID + 3 << ", align 1"<< '\n';
                RegisterID += 3;
                break;
            case '[':
                std::cout << "  " << "%" << RegisterID + 1 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = load i8, i8* %" << RegisterID + 1 << ", align 1"<< '\n';
                std::cout << "  " << "%" << RegisterID + 3 << " = icmp eq i8 0, %" << RegisterID + 2 << '\n';
                std::cout << "  " << "br i1 %" << RegisterID + 3 << ", label %lc" << i << ", label %lo" << i << '\n';
                std::cout << "lo" << i << ":" << '\n';
                RegisterID += 3;
                BracketsStack.push(i);
                break;
            case ']':
                std::cout << "  " << "%" << RegisterID + 1 << " = load i8*, i8** %1, align 8"<< '\n';
                std::cout << "  " << "%" << RegisterID + 2 << " = load i8, i8* %" << RegisterID + 1 << ", align 1"<< '\n';
                std::cout << "  " << "%" << RegisterID + 3 << " = icmp eq i8 0, %" << RegisterID + 2 << '\n';
                std::cout << "  " << "br i1 %" << RegisterID + 3 << ", label %lc" << BracketsStack.top() << ", label %lo" << BracketsStack.top() << '\n';
                std::cout << "lc" << BracketsStack.top() << ":" << '\n';
                RegisterID += 3;
                BracketsStack.pop();
                break;
            default:
                break;
        }

    }
    std::cout << "  " << "ret i32 0" << '\n';
    std::cout << "}" << '\n';

    std::cout << "" << '\n';

    std::cout << "; Function Attrs: nounwind" << '\n';
    std::cout << "declare noalias i8* @calloc(i64 noundef, i64 noundef) #1" << '\n';
    std::cout << "declare i32 @putchar(i32 noundef) #2" << '\n';
    std::cout << "declare i32 @getchar() #2" << '\n';
    std::cout << "attributes #0 = { noinline nounwind optnone uwtable \"frame-pointer\"=\"all\" \"min-legal-vector-width\"=\"0\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" }" << '\n';
    std::cout << "attributes #1 = { nounwind \"frame-pointer\"=\"all\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" }" << '\n';
    std::cout << "attributes #2 = { \"frame-pointer\"=\"all\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" }" << '\n';
    std::cout << "attributes #3 = { nounwind }" << '\n';

    return 0;
}