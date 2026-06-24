#include <iostream>
#include <iomanip>
#include <random>

int main()
{
	std::random_device dev;
	std::mt19937 generator(dev());
	std::uniform_int_distribution<unsigned short> distribution(0, 65535);

	const size_t size = 512;
	unsigned short mass[size];
	unsigned short data[size] = {0};

	for (size_t i = 0; i < size; i++)
	{
		mass[i] = distribution(generator);
	}

	__asm {
		pushad
		lea edi, mass
		lea esi, data
		mov ebx, 0
		mov ecx, 0
		mov edx, 0

		dist:
			mov ax, word ptr[edi]
			cmp ax, 50000
			jae big_number
			cmp ax, 10000
			jb less_number
			test ax, 1
			jz even_number
			jmp odd_number

		big_number:
			movzx ebx, ch
			cmp ebx, 128
			je end_loop
			mov [esi + ebx*2 + 512], ax
			inc ch
			jmp increment_number

		less_number:
			movzx ebx, cl
			cmp ebx, 128
			je end_loop
			mov [esi + ebx*2 + 768], ax
			inc cl
			jmp increment_number

		even_number:
			movzx ebx, dh
			cmp ebx, 128
			je end_loop
			mov [esi + ebx*2], ax
			inc dh
			jmp increment_number

		odd_number:
			movzx ebx, dl
			cmp ebx, 128
			je end_loop
			mov [esi + ebx*2 +256], ax
			inc dl
			jmp increment_number

		increment_number:
			add edi, 2
			jmp dist

		end_loop:
			popad
	}
	for (int i = 0; i < size; i++) {
		std::cout << std::setw(8) << mass[i] << "   ----->   " << std::setw(5) << data[i] << "   i = " << i << std::endl;
	}   
    return 0;
}
