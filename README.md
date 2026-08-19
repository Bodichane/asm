# x86 Assembly — lab work

Four x86 assembly labs written in **MSVC inline assembly** (`__asm` blocks inside
C++ code). Each lab targets a family of instructions: data transfer, arithmetic,
control transfer, then logical and bit-manipulation instructions.

## Important constraint: 32-bit only

MSVC **only accepts `__asm` blocks in 32-bit (x86) builds**. This syntax is
simply rejected by the compiler in x64. You must therefore select the **x86 /
Win32** platform in Visual Studio, otherwise the build fails before it even
reaches the code.

## The four labs

### Lab 1 — Registers and data transfer
Swaps the contents of two registers, done at all three widths (32-bit
`ESI`/`EBX`, 16-bit `CX`/`DI`, 8-bit `DH`/`DL`) and by four different methods for
each:

1. the dedicated `XCHG` instruction;
2. going through a memory variable (`LEA` + `MOV`);
3. going through a third register;
4. going through the stack (`PUSH` / `POP`).

Ends with a comparison between `MOVSX` (sign extension) and `MOVZX`
(zero extension).

### Lab 2 — Arithmetic instructions
Evaluates the integer expression:

```
(c / 4 - d * 62) / (a * a + 1)
```

Illustrates the difference between `MUL`/`DIV` (unsigned) and `IDIV` (signed),
preparing the 64-bit dividend via `EDX:EAX`, the role of `CDQ` for sign
extension, and reading the remainder left in `EDX`.

### Lab 3 — Control transfer
Generates 512 unsigned 16-bit integers, then sorts them into four categories of
128 elements each in a destination array:

| Category | Condition | Offset in `data` |
|---|---|---|
| Large values | `>= 50000` | +512 bytes |
| Small values | `< 10000` | +768 bytes |
| Even | otherwise, bit 0 clear | +0 |
| Odd | otherwise, bit 0 set | +256 bytes |

Uses conditional jumps (`JAE`, `JB`, `JZ`), parity testing via `TEST ax, 1`, and
scaled-index addressing (`[esi + ebx*2 + offset]`). The four counters are kept in
the half-registers `CH`, `CL`, `DH`, `DL` so that only two registers are used.

### Lab 4 — Logical instructions
Four operations on the constant `0x12546FD1`:

- **`countBitsShiftMethod`** — counts 0 and 1 bits by successive shifts
  (`SHR` + `TEST`).
- **`countBitsBSFMethod`** — same count via `BSF` (find first set bit) then `BTR`
  (clear the found bit). Both methods must produce the same result.
- **`countPairedBits`** — counts adjacent identical bit pairs (`00` and `11`),
  relying on the carry flag left by `SHR`.
- **`exchangeBits`** — swaps, in the low byte, the symmetric bits: 0↔7, 1↔6,
  2↔5, 3↔4, by masking and shifting.

## Build and run

### With Visual Studio
Each lab has its own solution:

```
lab1/lab1.sln    lab2/lab2.sln    lab3/lab3.sln    lab4/lab4.sln
```

Open the desired solution, **select the `Debug | x86` configuration** (not
`x64`, see the constraint above), then build and run.

### From the command line (Developer Command Prompt)

```bat
msbuild lab4\lab4.sln /p:Configuration=Debug /p:Platform=x86
lab4\Debug\lab4.exe
```

## Repository layout

```
lab1/ … lab4/   One Visual Studio solution per lab
problems/       Statements of the four labs (.docx)
results/        Submitted reports for each lab (.docx)
```

The problem statements and reports are written in Russian.

## Note on repository history

This repository initially contained Visual Studio build outputs and cache
(`.vs/`, `*.ipch`, `*.pdb`, `*.exe`, `Browse.VC.db`, …), i.e. more than 400 MB of
artifacts for roughly 6 KB of real code. These files were removed from tracking
and a `.gitignore` was added to keep them out. They remain present in earlier
commits.
