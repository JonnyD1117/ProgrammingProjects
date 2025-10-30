# 6502 Assembler

## Required Functionality

1. Read in 6502 Assembly files
2. Parsing Pass #1, populate symbol table and identify addressing modes
3. Parsing Pass #2, generate machine code from instruction & symbol tables
4. Write machine code to binary/hex file?

## Identifying Addressing Modes

### Immediate Mode

- OP #$FF       ; Immediate Addressing (literal must be <1 Byte (e.g. <=$FF))

### Asbolute Mode

- OP $FFFF      ; Absolute Addressing Supplied 2-byte memory address which must be fetched

### Zero Page Addressing

- OP $FF        ; Zero Page is an absolute addressing mode for the first byte of addressable memory ( <$FF )

### Absolute-Indexed (X | Y) Addressing

- OP $!1234, X|Y    ; Compute effective address from given address plus respective index X | Y

### Zero Page-Indexed (X | Y) Addressing

- OP $12, X|Y       ; Compute effective address from zero-page address plus respective index X|Y (if index > zero page truncate high-byte)

### Index Indirect X Addressing

- OP ($LL, X)       ; Computer effective address (from zero-page + X-index ) use that address and fetch its value from computed address

### Indirect Index Y Addressing

- OP ($LL),Y        ; Compute Effective address (zero-page address) fetch value from that address and then + Y offset

# value    Immediate            Literal value

------------------------------------------------------------------
$LL        Zero Page               1-byte address
$HHLL      Absolute                2-byte address
$LL,X      Zero Page,X             Zero page plus X register
$LL,Y      Zero Page,Y             Zero page plus Y register
$HHLL,X    Absolute,X              Absolute plus X register
$HHLL,Y    Absolute,Y              Absolute plus Y register
($HHLL)    Indirect (JMP only)     Jump indirect
($LL,X)    Indexed Indirect (X)    Zero page indexed indirect
($LL),Y    Indirect Indexed (Y)    Zero page indirect plus Y
  A        Accumulator             Operand is accumulator itself
(none)     Implied                 No operand
