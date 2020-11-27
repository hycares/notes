# 内联汇编

## 汇编格式

使用gcc汇编 采用 AT&T 格式，简要复习intel格式区别

1. 操作数位置相反
   1. intel: op-code dst src
   2. AT&T: op-code src dst
2. 寄存器名称 AT&T 需要加上 % 前缀
3. 立即数
   1. intel: 100h (hexadecimal)
   2. AT&T:  $0x100
4. 操作数大小
   1. intel: 使用前缀 byte ptr |  word ptr  |  dword ptr   (8, 16, 32)
   2. AT&T:  指令后缀：b  w  l
5. 内存操作 计算
   1. intel:  [base + index * scale + disp]
   2. AT&T: disp(base, index, scale)    内存访问的立即数 不需要使用 $ 前缀

```dump
+------------------------------+------------------------------------+
|       Intel Code             |      AT&T Code                     |
+------------------------------+------------------------------------+
| mov     eax,1                |  movl    $1,%eax                   |   
| mov     ebx,0ffh             |  movl    $0xff,%ebx                |   
| int     80h                  |  int     $0x80                     |   
| mov     ebx, eax             |  movl    %eax, %ebx                |
| mov     eax,[ecx]            |  movl    (%ecx),%eax               |
| mov     eax,[ebx+3]          |  movl    3(%ebx),%eax              | 
| mov     eax,[ebx+20h]        |  movl    0x20(%ebx),%eax           |
| add     eax,[ebx+ecx*2h]     |  addl    (%ebx,%ecx,0x2),%eax      |
| lea     eax,[ebx+ecx]        |  leal    (%ebx,%ecx),%eax          |
| sub     eax,[ebx+ecx*4h-20h] |  subl    -0x20(%ebx,%ecx,0x4),%eax |  
+------------------------------+------------------------------------+
```

标准内联汇编

```c
// single line
asm("movl %ecx, %eax");
__asm__("movb %bh, (%eax)");  // 可以使用 asm 和 __asm__

// multi line
asm("movl %eax, %ebx\n\t"
   	"movl $56, %esi\n\t"
   	"leal (%ebx,%ecx),%eax");  // 需要在行后加上 \n\t  因为是直接传入 as 而每行的格式都是尾部有 \n\t
```

存在问题，修改的寄存器可能会间接影响到其他值。比如如果eax存在其他值，但是使用了eax，并且退出时并不复原，则存在奔溃的可能。

扩展形式

```c
asm ( assembler template 
     : output operands                  /* optional */
     : input operands                   /* optional */
     : list of clobbered registers      /* optional */
    );
```

例子

```c
int a=10, b;
asm ("movl %1, %%eax; // 两个%% 区别 操作数
     movl %%eax, %0;"
     :"=r"(b)        /* output  r指定寄存器 =代表write only 第一个变量 %0 */
     :"r"(a)         /* input */
     :"%eax"         /* clobbered register */
    );       
```

直接或间接改变的寄存器（不是分配的）需要在第三个冒号后列出

拒绝优化 `volatile` 关键字 或 `__volatile__`

## 约束符 

### 寄存器限制

指定使用哪些寄存器

```dump
+---+--------------------+
| r |    Register(s)     |
+---+--------------------+
| a |   %eax, %ax, %al   |
| b |   %ebx, %bx, %bl   |
| c |   %ecx, %cx, %cl   |
| d |   %edx, %dx, %dl   |
| S |   %esi, %si        |
| D |   %edi, %di        |
+---+--------------------+
```

## 内存限制

```c
asm("sidt %0\n" : :"m"(loc)); // 使用 m 约束 直接内存操作
```

## 匹配限制

```c
asm("incl %0" :"=a"(var) :"0"(var));  // output "0" 修饰代表 第一个变量
```

## 字符串拷贝函数实现

```c
static inline char * strcpy(char * dest,const char *src)
{
int d0, d1, d2;
__asm__ __volatile__(  "1:\tlodsb\n\t" // label 
                       "stosb\n\t"
                       "testb %%al,%%al\n\t"
                       "jne 1b"
                     : "=&S" (d0), "=&D" (d1), "=&a" (d2)  //esi edi eax
                     : "0" (src),"1" (dest) 
                     : "memory");
return dest;
}
```

参考：[GCC-Inline-Assembly-HOWTO (ibiblio.org)](http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html)



























