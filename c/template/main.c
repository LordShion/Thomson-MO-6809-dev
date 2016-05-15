#define mon_putc(car) { \
   asm(" SWI \n"\
      " FCB 2"\
      ::"B" ((unsigned char) (car))\
   ); \
}

void   myputs(char *str)
{
   while (*str)
      mon_putc(*str++);
}

void   main(void)   // Should NOT return INT ! (else gcc will include strange code affecting U register, don't bother the Warning from GCC about this)
{
   myputs("Hello, World !\r\n");
}