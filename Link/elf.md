# ELF文件剖析

```
ELF HEADER
.text
.data
.bss
.rodata
.comment
...
section header table
string table
symbol table
```

elf文件信息存储在文件头部，用来描述基本属性，之后存储每一个的段表信息

## ELF-header section

在32位机器和64位机器并不一致

```c
// /usr/include/elf.h

typedef struct
{
  unsigned char e_ident[EI_NIDENT]; /* Magic number and other info */
  Elf32_Half  e_type;     /* Object file type */
  Elf32_Half  e_machine;    /* Architecture */
  Elf32_Word  e_version;    /* Object file version */
  Elf32_Addr  e_entry;    /* Entry point virtual address */
  Elf32_Off e_phoff;    /* Program header table file offset */
  Elf32_Off e_shoff;    /* Section header table file offset */
  Elf32_Word  e_flags;    /* Processor-specific flags */
  Elf32_Half  e_ehsize;   /* ELF header size in bytes */
  Elf32_Half  e_phentsize;    /* Program header table entry size */
  Elf32_Half  e_phnum;    /* Program header table entry count */
  Elf32_Half  e_shentsize;    /* Section header table entry size */
  Elf32_Half  e_shnum;    /* Section header table entry count */
  Elf32_Half  e_shstrndx;   /* Section header string table index */
} Elf32_Ehdr;

// 64位结构 使用64位的typedef类型
```

```dump
# 32bits dump header
# readelf -h a.o

ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00
  --> '\DEL' 'E' 'L' 'F' (1 -> 32bits 2 -> 64bits) (endian) (version) (nouse)...
  
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          1056 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           40 (bytes)
  Number of section headers:         15
  Section header string table index: 14  # 段表名称段索引
```

## section table section

段表存储每个段的名称，长度，偏移等属性

```c
typedef struct
{
  Elf32_Word  sh_name;    /* Section name (string tbl index) 名称在.shstrtab段中 使用偏移即可*/
  Elf32_Word  sh_type;    /* Section type */
  Elf32_Word  sh_flags;   /* Section flags */
  Elf32_Addr  sh_addr;    /* Section virtual addr at execution */
  Elf32_Off sh_offset;    /* Section file offset */
  Elf32_Word  sh_size;    /* Section size in bytes */
  Elf32_Word  sh_link;    /* Link to another section */
  Elf32_Word  sh_info;    /* Additional section information */
  Elf32_Word  sh_addralign;   /* Section alignment */
  Elf32_Word  sh_entsize;   /* Entry size if section holds table */
} Elf32_Shdr;
```

```dump
# readelf -S a.o

There are 15 section headers, starting at offset 0x420:

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0 # 第一个是NULL
  [ 1] .group            GROUP           00000000 000034 000008 04     12  16  4
  [ 2] .text             PROGBITS        00000000 00003c 00007f 00  AX  0   0  1
  [ 3] .rel.text         REL             00000000 00033c 000048 08   I 12   2  4 # text中的重定位表
  [ 4] .data             PROGBITS        00000000 0000bc 000008 00  WA  0   0  4
  [ 5] .bss              NOBITS          00000000 0000c4 000004 00  WA  0   0  4
  [ 6] .rodata           PROGBITS        00000000 0000c4 000004 00   A  0   0  1
  [ 7] .text.__x86.get_p PROGBITS        00000000 0000c8 000004 00 AXG  0   0  1
  [ 8] .comment          PROGBITS        00000000 0000cc 00001d 01  MS  0   0  1
  [ 9] .note.GNU-stack   PROGBITS        00000000 0000e9 000000 00      0   0  1
  [10] .eh_frame         PROGBITS        00000000 0000ec 00007c 00   A  0   0  4
  [11] .rel.eh_frame     REL             00000000 000384 000018 08   I 12  10  4
  [12] .symtab           SYMTAB          00000000 000168 000140 10     13  13  4
  [13] .strtab           STRTAB          00000000 0002a8 000092 00      0   0  1
  [14] .shstrtab         STRTAB          00000000 00039c 000082 00      0   0  1
  
REL 代表 relocate 重定位信息 info 存储作用在 哪一个的段上
```

解析ELF头，可以找到section header的索引，通过.shstrtab解析所有的section

### gcc指定段

```c
__attribute__((section("foo"))) int global = 0;
__attribute__((section("BAR"))) int bar = 1;
```



## 程序、数据段

.text 段存储所有可执行代码 只读，.data .bss存放数据，区别在于 .data 存放所有已初始化的数据，在文件中是存在空间的，而bss段中只是一个标记（预留位置），并不会实际存放数据，用来在运行时生成空间。

将程序数据分离，并且text只读拥有下述优势

1. 指令和数据分区，权限设置读写，text不可修改，能够防止篡改
2. 指令和数据的缓存特性 局部性原理
3. 对于text段而言，所有进程可以共享一份代码能够有效减少空间开销

## 符号表

在生成目标文件时，外部定义的函数变量无法直接得到地址，必须在链接阶段才能确认，

> 对于在b文件中使用了a文件的函数bar，称之为 a文件Define  bar  b文件Refer bar

所有refer的符号都需要进行保存

```dump
# nm a.o  ; readelf -s a.o

00000000 T func1
00000000 D global_init_var
         U _GLOBAL_OFFSET_TABLE_
00000004 C global_uninit_var
0000002e T main
         U printf
00000004 d static_var.1558
00000000 b static_var2.1559
00000000 T __x86.get_pc_thunk.ax
```

### 符号

> 针对定义时而非引用

默认函数和初始化变量为强符号，未初始化变量为弱符号可使用`__attribute__((weak))`将强符号改成弱符号

#### 符号决议

1. 强符号不可多次定义
2. 当多个弱符号和一个强符号出现，选择强符号
3. 都是弱符号，选择空间最大的符号

### 引用

默认强引用，如果未找到链接器，那么提示未定义错误。针对弱引用 `__attribute__((weakref))` ，如果没有找到则为0

#### 弱引用函数

```c
__attribute__((weakref)) void foo();

int main() {
  if (foo) foo(); // 如果直接 foo() 当没有找到定义时 等价于 零地址 调用 运行时错误
}
```

## 调试段

编译时增加 `-g`

调试信息格式 DWARF

