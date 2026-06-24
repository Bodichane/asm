#include <iostream>

int countBitsShiftMethod() {
    int count0;
    int count1;
    __asm {
        pushad

        mov eax, 0x12546FD1
        xor ebx, ebx

        start_loop:
            cmp eax, 0
            je end_loop
            test eax, 1
            jnz one_bits
            shr eax, 1
            jmp start_loop

        one_bits:
            inc ebx
            shr eax, 1
            jmp start_loop

        end_loop:
            mov count1, ebx
            mov count0, 32
            sub count0, ebx

        popad
    }
    std::cout << "Shift Method: The number of bits of 0 and 1 are respectively "
              << count0 << " and " << count1 << std::endl;
}

int countBitsBSFMethod() {
    int count0;
    int count1;
    __asm {
        pushad

        mov eax, 0x12546FD1
        xor esi, esi
        xor ecx, ecx

        start_loop:
            bsf ecx, eax
            jz end_loop
            inc esi
            btr eax, ecx
            jmp start_loop

        end_loop:
            mov count1, esi
            mov count0, 32
            sub count0, esi

        popad
    }
    std::cout << "BSF Method: The number of bits of 0 and 1 are respectively "
              << count0 << " and " << count1 << std::endl;
}

int countPairedBits() {
    int count00;
    int count11;
    __asm {
        pushad

        mov eax, 0x12546FD1
        xor ecx, ecx
        xor edx, edx
        mov ebx, 31

        loop_start:
            shr eax, 1
            jc check_11
            test eax, 1
            jnz next_bit
            inc ecx
            jmp next_bit

        check_11:
            test eax, 1
            jz next_bit
            inc edx

        next_bit:
            dec ebx
            jnz loop_start

        mov count00, ecx
        mov count11, edx
        popad
    }
    std::cout << "Count of 00 pairs: " << count00 << std::endl;
    std::cout << "Count of 11 pairs: " << count11 << std::endl;
}

int exchangeBits() {
    int value;
    __asm {
        pushad

        mov eax, 0x12546FD1
        mov ebx, eax
        and ebx, 0xFF

        ; Bits 0 and 7
        mov ecx, ebx
        and ecx, 0x01
        shl ecx, 7
        mov edx, ebx
        and edx, 0x80
        shr edx, 7
        and ebx, 0x7E
        or ebx, ecx
        or ebx, edx

        ; Bits 1 and 6
        mov ecx, ebx
        and ecx, 0x02
        shl ecx, 5
        mov edx, ebx
        and edx, 0x40
        shr edx, 5
        and ebx, 0xBD
        or ebx, ecx
        or ebx, edx

        ; Bits 2 and 5
        mov ecx, ebx
        and ecx, 0x04
        shl ecx, 3
        mov edx, ebx
        and edx, 0x20
        shr edx, 3
        and ebx, 0xDB
        or ebx, ecx
        or ebx, edx

        ; Bits 3 and 4
        mov ecx, ebx
        and ecx, 0x08
        shl ecx, 1
        mov edx, ebx
        and edx, 0x10
        shr edx, 1
        and ebx, 0xE7
        or ebx, ecx
        or ebx, edx

        and eax, 0xFFFFFF00
        or eax, ebx

        mov value, eax
        popad
    }
    std::cout << "Value after direct bit exchange: 0x" << std::hex << value << std::endl;
    return value;
}

int main() {
    countBitsShiftMethod();
    countBitsBSFMethod();
    countPairedBits();
    exchangeBits();

    return 0;
}
