cmd_/home/kernel/modules/helloModule.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/kernel/modules/helloModule.ko /home/kernel/modules/helloModule.o /home/kernel/modules/helloModule.mod.o ;  true
