/* Script for -z combreloc: combine and sort reloc sections */
OUTPUT_FORMAT("elf32-bigscore", "elf32-bigscore",
	      "elf32-littlescore")
OUTPUT_ARCH(score)
SECTIONS
{
  .text           :
  {
    *(.text .stub .text.* .gnu.linkonce.t.*)    
  } =0
  .ide_res        :
  {
    *(.data .data.* .gnu.linkonce.d.*)
  }
  .data1          : { *(.data1) }
}


