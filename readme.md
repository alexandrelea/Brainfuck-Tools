# BFI
The program `bfi` is an interpreter which can edit&run&debug [Brainfuck](https://esolangs.org/wiki/Brainfuck) programs.

# BF2C
The program `bf2c` can turn Brainfuck program into C program.

Usage: 
```bash
bf2c xxx.bf -o xxx.c
```

You can't exchange arguments' postitions.

If you wan't to make C programs into executable programs and run them, please enter:

```bash
cc xxx.c -o xxx
./xxx
```

You can change `xxx` into your filename.

External tools: [String to brainfuck](https://www.splitbrain.org/services/ook).

# Compile

You can use `make` to compile all files, but you must seprate the command(there are only 2 files :-).

```bash
make bfi
make bf2c
```

And if you want to copy programs into `/usr/bin`, you can type

```bash
make install
```

in `sudo`.
