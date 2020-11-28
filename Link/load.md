# 加载

当程序链接完成后已经是可执行的文件，二进制文件如何加载，毕竟只有在内存中文件才能被CPU执行。每个程序运行后会拥有自己独立的地址空间，虚拟地址空间（VAS），这个空间的大小是由CPU的寻址能力决定的，比如32位就只有4GB的寻址空间，而64位的处理器有 $2^{64}$ 的寻址能力。C的指针大小就代表了虚拟空间的位数。显然64位虚拟空间的大小超过了目前实际内存的大小，物理内存空间并没有这么大的空间，虚拟和物理的映射是一种解决方案 （MMU）

**虚拟空间的分配是由操作系统控制**

```dump
# Linux 4GB 地址空间 分配策略

+----------+  0xffffffff
|          |      OS       1GB
+----------+  0xc0000000
|          |
|          |  User Space   3GB
|          |
+----------+  0x00000000

# 0x0 ~ 0xbfffffff 是可使用的虚拟空间
```

硬盘数据如何载入内存？

1. 一次性全部载入 【太浪费】
2. 只放当前需要的和常用的部分，运行时缺哪些再载入 【局部性原理】

> 旧时代的节约内存的方法 OverLay 机制 
>
> 无依赖模块的相互覆盖 ->  跨模块调用 x
>
> ![image-20201127154551407](assets/image-20201127154551407.png)

## 页映射机制

与物理内存的分页机制相结合

![image-20201127154621498](assets/image-20201127154621498.png)

物理内存必然受到限制，如果接下来要载入F4，但是没有空间可换则必然要选择一个页面进行替换 【页面替换算法】，操作系统中必然有个程序要进行内存页的替换管理！-> 存储管理器。

## 进程建立过程

1. 虚拟空间的建立 【并不是空间分配】
2. 建立虚拟空间和可执行文件的映射关系
3. 设置CPU IP 到ENTRY

虚拟空间的创建过程实际是分配一个数据结构用来记录该数据空间，读取文件头后建立虚拟内存空间与可执行文件的映射关系。

### 虚拟内存区域 （VMA）

记录结构中会保存 磁盘上 某个 段 的偏移 和虚拟页地址的关系

当程序开始启动时，设置了程序的入口地址，当CPU执行时，却发现这个页面是空页面 -> 缺页中断 于是根据映射关系将可执行文件中偏移量为n的数据载入分配的物理内存中，物理内存页和虚拟内存页面再进行关联。

![image-20201127162726008](assets/image-20201127162726008.png)

## 映射关系

如果将每个section都映射到一个VMA中，而VMA又必须按照页大小分配对齐，section的大小如果是1kb却仍然分配4kb，这会产生明显的内存碎片。每一个section实际上只是给程序员理解的，操作系统或者CPU不需要按照section来进行执行，所以不同的section应该想办法合并来减少空间浪费。

每个section是存在权限的，.text和.data不应该合并，因为一个是只读不可写，但按照相同权限来进行合并则不会有影响。

常见权限：

1. .text 可读可执行
2. .data .bss 可读可写
3. .rodata 只读

将每权限相似，可合并的section拼接一起可以成为一个Segment （也称为段）

```dump
# readelf -l a.out

Elf file type is EXEC (Executable file)
Entry point 0x401a30
There are 8 program headers, starting at offset 64

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  LOAD           0x0000000000000000 0x0000000000400000 0x0000000000400000
                 0x0000000000000470 0x0000000000000470  R      0x1000
  LOAD           0x0000000000001000 0x0000000000401000 0x0000000000401000
                 0x000000000007b351 0x000000000007b351  R E    0x1000
  LOAD           0x000000000007d000 0x000000000047d000 0x000000000047d000
                 0x000000000002374c 0x000000000002374c  R      0x1000
  LOAD           0x00000000000a10e0 0x00000000004a20e0 0x00000000004a20e0
                 0x00000000000051f0 0x0000000000006940  RW     0x1000
  NOTE           0x0000000000000200 0x0000000000400200 0x0000000000400200
                 0x0000000000000044 0x0000000000000044  R      0x4
  TLS            0x00000000000a10e0 0x00000000004a20e0 0x00000000004a20e0
                 0x0000000000000020 0x0000000000000060  R      0x8
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x00000000000a10e0 0x00000000004a20e0 0x00000000004a20e0
                 0x0000000000002f20 0x0000000000002f20  R      0x1

 Section to Segment mapping:
  Segment Sections...
   00     .note.ABI-tag .note.gnu.build-id .rela.plt
   01     .init .plt .text __libc_freeres_fn .fini
   02     .rodata .eh_frame .gcc_except_table
   03     .tdata .init_array .fini_array .data.rel.ro .got .got.plt .data __libc_subfreeres __libc_IO_vtables __libc_atexit .bss __libc_freeres_ptrs
   04     .note.ABI-tag .note.gnu.build-id
   05     .tdata .tbss
   06
   07     .tdata .init_array .fini_array .data.rel.ro .go
```

Linux 一切皆文件

```dump
00400000-00401000 r--p 00000000 fd:01 1058962                            /home/ics/src/ld/secmp.elf
00401000-0047d000 r-xp 00001000 fd:01 1058962                            /home/ics/src/ld/secmp.elf
0047d000-004a1000 r--p 0007d000 fd:01 1058962                            /home/ics/src/ld/secmp.elf
004a2000-004a8000 rw-p 000a1000 fd:01 1058962                            /home/ics/src/ld/secmp.elf
004a8000-004a9000 rw-p 00000000 00:00 0
01446000-01469000 rw-p 00000000 00:00 0                                  [heap]
7ffc9e94d000-7ffc9e96e000 rw-p 00000000 00:00 0                          [stack]
7ffc9e9fa000-7ffc9e9fc000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

p权限代表private 私有空间 与之对应的是共享空间 s

如果segment的大小如果是页面倍数多一些，但是仍然要占用一个页面，所以可以将多个segment映射到一个物理页面，但是物理页可以映射两份到虚拟页。

## ELF文件的装载过程

Linux系统API调用

```c
// unistd.h
int execve(const char* filename, char* const argv[], char* const envp[]);
```

