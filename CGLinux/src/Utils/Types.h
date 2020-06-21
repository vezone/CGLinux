#pragma once

#include <stdint.h>

/*
    ==================
    ==================
    ==              ==
    ==    COLORS    ==
    ==              ==
    ==================
    ==================

	Name            BG  FG
	Black           30  40
	Red             31  41
	Green           32  42
	Yellow          33  43
	Blue            34  44
	Magenta         35  45
	Cyan            36  46
	White           37  47
	Bright Black    90  100
	Bright Red      91  101
	Bright Green    92  102
	Bright Yellow   93  103
	Bright Blue     94  104
	Bright Magenta  95  105
	Bright Cyan     96  106
	Bright White    97  107
	
    [a;b;cmTEXT\033[0m
    
    a - mode can be: 
    	* 1 - жирный блеклый
    	* 2 - обычный текст
    	* 3 - курсив 
    	* 4 - подчеркнутый текст 
    	* 5 - мигающий текст
    b - background color
    c - foreground color	
    \033 - foreground & background
    
    examples:
    printf("\033[36mTexting\033[0m \n");
	
	//Background
	printf("\033[1;42;30mTexting\033[0m\t\t");
    printf("\033[3;44;30mTexting\033[0m\t\t");
    printf("\033[4;104;30mTexting\033[0m\t\t");
    printf("\033[5;100;30mTexting\033[0m\n");

    printf("\033[4;47;35mTexting\033[0m\t\t");
    printf("\033[3;47;35mTexting\033[0m\t\t");
    printf("\033[3;43;30mTexting\033[0m\t\t");
*/
#define	BLACK(x) "\x1B[30m"x"\033[0m"
#define	RED(x) "\x1B[31m"x"\033[0m"  
#define	GREEN(x) "\x1B[32m"x"\033[0m"  
#define	YELLOW(x) "\x1B[33m"x"\033[0m"  
#define BLUE(x) "\x1B[34m"x"\033[0m"
#define	MAGNETA(x) "\x1B[35m"x"\033[0m"  
#define	CYAN(x) "\x1B[36m"x"\033[0m"  
#define WHITE(x) "\x1B[37m"x"\033[0m"  

#define	BRIGHTBLACK(x) "\x1B[90m"x"\033[0m"  
#define BRIGHTRED(x) "\x1B[91m"x"\033[0m"  
#define BRIGHTGREEN(x) "\x1B[92m"x"\033[0m"  
#define BRIGHTYELLOW(x) "\x1B[93m"x"\033[0m"  
#define BRIGHTBLUE(x) "\x1B[94m"x"\033[0m"  
#define BRIGHTMAGNETA(x) "\x1B[95m"x"\033[0m"  
#define BRIGHTCYAN(x) "\x1B[96m"x"\033[0m"   
#define BRIGHTWHITE(x) "\x1B[97m"x"\033[0m" 

#define RED5(x) "\033[5;1;31m"x"\033[0m"
#define REDBG5(x) "\033[5;101;30m"x"\033[0m"
#define	GREEN5(x) "\033[5;1;32m"x"\033[0m"  

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof(x[0]))
#define TO_STRING(x) #x
#define KB(x) (i64)1024 * (i64)x
#define MB(x) (i64)1024 * KB(x)
#define GB(x) (i64)1024 * MB(x)
#define nullptr ((void*) 0)

#define TOKB(x) ((f64) x) / 1024
#define TOMB(x) ((f64) TOKB(x)) / 1024
#define TOGB(x) ((f64) TOMB(x)) / 1024
