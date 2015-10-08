#define __LOG_ON 1
// std
#include <type.h>
#include <asm.h>
#include <dbg.h>
// x86
#include <pm.h>
#include <isr.h>
#include <timer.h>
#include <syscall.h>
// libs
#include <string.h>
#include <printk.h>
// drv
#include <vga.h>
#include <kb.h>
#include <ide.h>
// mm
#include <pmm.h>
#include <vmm.h>
// proc
#include <proc.h>
// pipe
#include <pipe.h>
// fs
#include <bcache.h>
#include <inode.h>
// dev
#include <dev.h>

/* 好无聊 */
static void print_ok(){
    int i;
    for (i = 27; i <= 80; i++){
        putchar(' ');
    }

    putchar('[');
    vga_setcolor(COL_L_GREEN, COL_BLACK);
    puts("OK");
    vga_setcolor(COL_L_GREY, COL_BLACK);
    putchar(']');
}

int osmain(void)
{
    vga_init();

    puts("Installing GDT...     ");
    gdt_init();
    print_ok();

    puts("Installing IDT...     ");
    idt_init();
    print_ok();

    puts("Installing ISR...     ");
    isr_init();
    print_ok();

    puts("timer init...         ");
    timer_init(); 
    print_ok();

    puts("pmm init...           ");
    pmm_init();
    pmm_mem_info();
    print_ok();
    // pmm_test();
    
    puts("vmm init...           ");
    vmm_init();
    print_ok();
    // vmm_test();
    
    puts("kb init...            ");
    kb_init();
    print_ok();

    puts("ide init...           ");
    ide_init();
    print_ok();
    // ide_test();

    puts("buffer cache init...  ");
    bcache_init();
    print_ok();

    puts("inode cache init...   ");
    inode_init();
    print_ok();

    puts("file table init...    ");
    file_init();
    print_ok();

    puts("virtual device init...");
    dev_init();
    print_ok();

    puts("porcess init...       ");
    proc_init();
    print_ok();

    vga_setcolor(COL_CYAN, COL_BLACK);
    puts("Welcome to OS67...\n");
    vga_setcolor(COL_L_GREY, COL_BLACK);

    scheduler();
    
    panic("you shouldn't see this :( \n");
    return 67;
}
