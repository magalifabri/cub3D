# FT_PRINTF

## Project Description
Write a mimic of printf to learn about variadic functions.

Supported functionality:
- conversions: `cspdiuxX%`
- bonus conversions: `nfe`, some of `g`, as well as `o`
- flags: `-0.*`
- bonus flags: `lllhhh#+` and space

See `man 3 printf` for explanations on what these conversions and flags do.

## How To Use
A Makefile is included. When the `make` command is given, it will compile libftprintf.a (a library file) that contains the ft_printf function. 

To use the library, include it in compilation with `-L. libftprintf.a`. E.g.: `gcc -L. libftprintf.a main.c -o test`.

## Resources
- [video: How to write C functions with variable argument lists.](https://www.youtube.com/watch?v=S-ak715zIIE)
- [unit tester: PFT](https://github.com/gavinfielder/pft)

## Bugs
- I suspect the string produced by ft_ftoa may contain empty memory addresses on inputs such as ("%.0f", 0.0). 
