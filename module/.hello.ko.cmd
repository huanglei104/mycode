cmd_/home/huanglei/Code/module/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 --build-id  -T ./scripts/module-common.lds -o /home/huanglei/Code/module/hello.ko /home/huanglei/Code/module/hello.o /home/huanglei/Code/module/hello.mod.o;  true
