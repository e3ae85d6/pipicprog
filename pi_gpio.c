#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PI_GPIO_LIB
#include "pi_gpio.h"

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#define BLOCK_SIZE (4*1024)

static int mem_fd = 0;

int pi_gpio_map() {
    
    if(gpio_registers)
	return 0;
    
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
	perror("open");
	return -1;
    }
    
    void *gpio_map = mmap(NULL, sizeof(gpio_registers_t),
	    PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);

    if (gpio_map == MAP_FAILED) {
	close(mem_fd);
	perror("mmap");
	return -1;
    }

    gpio_registers = (volatile gpio_registers_t*) gpio_map;
    
    return 0;
}

void pi_gpio_unmap() {
    
    if(gpio_registers && gpio_registers != MAP_FAILED) {
	if(munmap((void*)gpio_registers, sizeof(gpio_registers_t))) {
	    perror("munmap");
	}
	
	gpio_registers = NULL;
    }
    
    if(mem_fd) {
	if(close(mem_fd)) {
	    perror("close");
	}
	
	mem_fd = 0;
    }
}
