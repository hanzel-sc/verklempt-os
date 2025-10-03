// kernel.c — VerklemptOS kernel
#include "shell.h"

void kernel_main(){

	shell_loop();
	while (1){}
}

