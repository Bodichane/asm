#include <iostream>

int main()
{
	int a;
	__asm {
		pushad

		MOV ESI, 3609857455
		MOV EBX, 2001729633

		MOV CX, 54633
		MOV DI, 8498

		MOV DH, 183
		MOV DL, 114

		// part 1
		XCHG EBX, ESI

		LEA EAX, a
		MOV dword ptr[EAX], ESI
		MOV ESI, EBX
		MOV EBX, dword ptr[EAX]

		MOV EAX, ESI
		MOV ESI, EBX
		MOV EBX, EAX

		PUSH ESI
		PUSH EBX
		POP ESI
		POP EBX

		// part 2
		XCHG CX, DI

		LEA EAX, a
		MOV word ptr[EAX], CX
		MOV CX, DI
		MOV DI, word ptr[EAX]

		MOV SI, CX
		MOV CX, DI
		MOV DI, SI

		PUSH CX
		PUSH DI
		POP CX
		POP DI
		// part 3
		XCHG DH, DL

		LEA EAX, a
		MOV byte ptr[EAX], DH
		MOV DH, DL
		MOV DL, byte ptr[EAX]

		MOV AH, DH
		MOV DH, DL
		MOV DL, AH

		PUSH DH
		PUSH DL
		POP DH
		POP DL

		MOVSX SI, CX
		MOVSX CX, DI

		MOVZX SI, CX
		MOVZX SI, CX
		popad
	}
	return 0;
}

