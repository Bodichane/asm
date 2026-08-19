# Assembleur x86 — travaux de laboratoire

Quatre laboratoires d'assembleur x86 écrit en **inline assembly MSVC** (blocs
`__asm` à l'intérieur de code C++). Chaque laboratoire cible une famille
d'instructions : transfert de données, arithmétique, transfert de contrôle,
puis instructions logiques et manipulation de bits.

## Contrainte importante : 32 bits uniquement

MSVC **n'accepte les blocs `__asm` qu'en compilation 32 bits (x86)**. Cette
syntaxe est purement et simplement rejetée par le compilateur en x64. Il faut
donc sélectionner la plateforme **x86 / Win32** dans Visual Studio, sinon la
compilation échoue avant même d'atteindre le code.

## Les quatre laboratoires

### Lab 1 — Registres et transfert de données
Échange du contenu de deux registres, décliné sur les trois largeurs (32 bits
`ESI`/`EBX`, 16 bits `CX`/`DI`, 8 bits `DH`/`DL`) et par quatre méthodes
différentes pour chacune :

1. l'instruction dédiée `XCHG` ;
2. le passage par une variable en mémoire (`LEA` + `MOV`) ;
3. le passage par un registre tiers ;
4. le passage par la pile (`PUSH` / `POP`).

Se termine par une comparaison entre `MOVSX` (extension signée) et `MOVZX`
(extension par zéros).

### Lab 2 — Instructions arithmétiques
Évaluation de l'expression entière :

```
(c / 4 - d * 62) / (a * a + 1)
```

Illustre la différence entre `MUL`/`DIV` (non signés) et `IDIV` (signé), la
préparation du dividende sur 64 bits via `EDX:EAX`, le rôle de `CDQ` pour
l'extension de signe, et la récupération du reste laissé dans `EDX`.

### Lab 3 — Transfert de contrôle
Génère 512 entiers non signés de 16 bits, puis les répartit en quatre catégories
de 128 éléments chacune dans un tableau de destination :

| Catégorie | Condition | Décalage dans `data` |
|---|---|---|
| Grandes valeurs | `>= 50000` | +512 octets |
| Petites valeurs | `< 10000` | +768 octets |
| Paires | reste, bit 0 à 0 | +0 |
| Impaires | reste, bit 0 à 1 | +256 octets |

Met en œuvre les sauts conditionnels (`JAE`, `JB`, `JZ`), le test de parité par
`TEST ax, 1`, et l'adressage indexé avec facteur d'échelle
(`[esi + ebx*2 + décalage]`). Les quatre compteurs sont maintenus dans les
demi-registres `CH`, `CL`, `DH`, `DL` afin de n'utiliser que deux registres.

### Lab 4 — Instructions logiques
Quatre traitements sur la constante `0x12546FD1` :

- **`countBitsShiftMethod`** — compte les bits à 0 et à 1 par décalages
  successifs (`SHR` + `TEST`).
- **`countBitsBSFMethod`** — même comptage via `BSF` (recherche du premier bit
  à 1) puis `BTR` (mise à zéro du bit trouvé). Les deux méthodes doivent
  produire le même résultat.
- **`countPairedBits`** — compte les paires de bits adjacents identiques
  (`00` et `11`), en s'appuyant sur le drapeau de retenue laissé par `SHR`.
- **`exchangeBits`** — échange, dans l'octet de poids faible, les bits
  symétriques : 0↔7, 1↔6, 2↔5, 3↔4, par masquage et décalage.

## Compilation et exécution

### Avec Visual Studio
Chaque laboratoire possède sa propre solution :

```
lab1/lab1.sln    lab2/lab2.sln    lab3/lab3.sln    lab4/lab4.sln
```

Ouvrir la solution voulue, **sélectionner la configuration `Debug | x86`**
(et non `x64`, voir la contrainte ci-dessus), puis compiler et lancer.

### En ligne de commande (invite « Developer Command Prompt »)

```bat
msbuild lab4\lab4.sln /p:Configuration=Debug /p:Platform=x86
lab4\Debug\lab4.exe
```

## Structure du dépôt

```
lab1/ … lab4/   Une solution Visual Studio par laboratoire
problems/       Énoncés des quatre laboratoires (.docx)
results/        Rapports rendus pour chaque laboratoire (.docx)
```

Les énoncés et les rapports sont rédigés en russe.

## Note sur l'historique du dépôt

Ce dépôt contenait initialement les sorties de compilation et le cache de
Visual Studio (`.vs/`, `*.ipch`, `*.pdb`, `*.exe`, `Browse.VC.db`, …), soit
plus de 400 Mo d'artefacts pour environ 6 Ko de code réel. Ces fichiers ont été
retirés du suivi et un `.gitignore` a été ajouté pour éviter qu'ils ne
reviennent. Ils restent présents dans l'historique des commits antérieurs.
