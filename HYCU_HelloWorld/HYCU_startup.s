.extern _start 
.section .hardware_init,"ax",@progbits 

.global _hardware_init 
.ent        _start; 
j        _start; 
.end _hardware_init