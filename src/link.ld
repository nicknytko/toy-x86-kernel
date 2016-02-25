ENTRY(start)
SECTIONS
{
  . = 0xC0100000;

  .text : AT(ADDR(.text) - 0xC0000000)
  {
    code = .; _code = .; __code = .;
    *(.multiboot)
    *(.text)
    . = ALIGN(4096);
  }

  .data : AT(ADDR(.data) - 0xC0000000)
  {
     data = .; _data = .; __data = .;
     *(.data)
     *(.rodata)
     . = ALIGN(4096);
  }

  .bss : AT(ADDR(.bss) - 0xC0000000)
  {
    bss = .; _bss = .; __bss = .;
    _sbss = .;
    *(COMMON)
    *(.bss)
    _ebss = .;
    . = ALIGN(4096);
  }

  end = .;
}
