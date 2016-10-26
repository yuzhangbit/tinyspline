#include <stdio.h> /* printf */
#include <stdlib.h> /* exit, EXIT_SUCCESS */

void print_help(char *name)
{
    printf("Usage: %s [OPTION]\n", name);
    printf("Options for general information:\n");
    printf("\t[--version]          return version of library\n");
    printf("\t[--cxxavailable]     return if C++ interface is available\n");
    printf("\n");
    printf("Options to get compile and link flags:\n");
    printf("\t[--cflags]           return flags to compile C using TinySpline\n");
    printf("\t[--ldflags]          return flags to link C library dynamically\n");
    printf("\t[--ldstaticflags]    return flags to link C library statically\n");
    printf("\t[--cxxflags]         return flags to compile C++ using TinySpline\n");
    printf("\t[--cxxldflags]       return flags to link C++ library dynamically\n");
    printf("\t[--cxxldstaticflags] return flags to link C++ library statically\n");
    printf("\n");
}

int main(int argc, char *argv[])
{
	int i;
	
	if (argc == 1)
	  print_help(argv[0]);
	else
      for (i = 0; i < argc; i++)
		  printf("%s\n", argv[i]);
    exit(EXIT_SUCCESS);
}
