#include <iostream>


int main()
{
    int a = 5678901;
    int c = 7890123;
    int d = 8901234;
    int result;
    int remainder;
    __asm {
        pushad
        ; numerator c / 4 - d * 62
        mov eax, c
        mov ebx, 4
        mov edx, 0
        div ebx
        push eax
        mov eax, d
        mov ebx, 62
        mul ebx
        pop ebx
        sub ebx, eax

        ; denominator a * a + 1
        mov eax, a
        mul eax
        add eax, 1
        adc edx, 0
        mov ecx, eax
        mov esi, edx

        ; divide numerator by denominator
        mov eax, ebx
        mov edx, 0
        cdq
        idiv ecx

        mov result, eax
        mov remainder, edx
        popad
    }
    std::cout << "result = " << result << " and remainder = " << remainder << std::endl;

    return 0;
}

