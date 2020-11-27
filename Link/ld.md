# 链接

问题 多个目标文件如何链接成为一个目标文件，各个段如何处理?

1. 直接拼接，所有段组合，这种操作开销非常大，段存在地址对齐的操作 （4kb)，如果一个段只有1kb但仍然需要4kb的大小
2. 相似段拼接，text组合在一起，bss组合在一起

针对第二种方法的拼接，两个步骤：

1. 空间地址分配，扫描所有obj，每个段信息整理，收集所有符号定义与引用到全局符号表，合并段，计算位置
2. 重定位信息，调整代码地址

如果某个段存在重定位信息，则必然存在一个针对该段的重定位段 .text  -> .rel.text   .data -> .rel.data

## 重定位表

```c
typedef struct
{
  Elf32_Addr  r_offset;   /* Address */
  // info 中 low 8bits -> type  high 24bits -> index
  Elf32_Word  r_info;     /* Relocation type and symbol index */
} Elf32_Rel;
```

```dump
# objdump -r a.o

a.o:     file format elf32-i386

RELOCATION RECORDS FOR [.text]:
OFFSET   TYPE              VALUE
00000013 R_386_PC32        __x86.get_pc_thunk.ax
00000018 R_386_GOTPC       _GLOBAL_OFFSET_TABLE_
00000028 R_386_GOT32X      shared   # 偏移地址 绝对地址
00000034 R_386_PLT32       swap     # 相对地址
```

两种寻址方式的差别：

绝对寻址就是绝对地址，相对寻址则是修正后的地址差

## 最小HelloWorld

```c
// hello.c

char *str = "hello world!\n";  // 13

void print() {
    asm("movl $13, %%edx \n\t"
       	"movl %0, %%ecx \n\t"
        "movl $0, %%ebx \n\t"
        "movl $4, %%eax \n\t"    // write 系统调用
        "int $0x80 \n\t"
        ::"r"(str):"edx", "ecx", "ebx");
}

// x86 必须要有这段代码才能正确返回到操作系统
void exit() {
    asm("movl $42, %ebx \n\t"
        "movl $1, %eax \n\t"
        "int $0x80 \n\t");
}

void nomain() {
    print();
    exit();
}
```

```bash
 gcc -fno-builtin -c hello.c
 ld -static -e nomain -o hello hello.o
```

## 链接脚本

链接的程序段可以自行指定，选择，丢弃

```lds
ENTRY(nomain) /* 指定入口 */

SECTIONS
{
  . = 0x8048000 + SIZEOF_HEADERS; /* 指定起始地址 */
  
  /* 控制语法 *代表统配所有文件  filename(.text .data) *(.rodata) */
  tinytext : { *(.text) *(.data) *(.rodata) }
  
  /* 丢弃指定段 */
  /DISCARD/ : { *(.comment) }
}
```

 `ld -verbose`查看内置脚本 `-t` 加载指定脚本