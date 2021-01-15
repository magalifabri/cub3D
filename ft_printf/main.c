#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>
#include <math.h>

int main()
{
	// ft_printf("%d, %c, %s\n", 10, 'a', "b, c");
	// printf("%g\n", (double)-2147483648);
	// ft_printf("%g\n", (double)-2147483648);
	// printf("%g\n", (double)503);
	// ft_printf("%g\n", (double)503);

	// printf("\n");
	// double ae = 0;
	// double ae2 = 0;
	// double be = 1;
	// double ce = -1;
	// double de = 123123.123;
	// double ee = -123123.123;
	// double fe = -214;
	// printf("|%+-14g| |%+014g| |%+014.6g| |%+-14.6g| |%+-10.5g| |%+-10.4g| |%+015.5g|\n", ae, ae2, be, ce, de, ee, fe);
	// ft_printf("|%+-14g| |%+014g| |%+014.6g| |%+-14.6g| |%+-10.5g| |%+-10.4g| |%+015.5g|\n", ae, ae2, be, ce, de, ee, fe);

	// printf("\n");
	// double ag = 0;
	// double bg = 1;
	// double c1g = -1;
	// double c2g = -1.1;
	// double c3g = -1.003;
	// double dg = 123.123;
	// double eg = -123.123;
	// double fg = 2;
	// printf("|%+10g| |%+10.1g| |%+10.5g| |%+10.5g| |%+10.5g| |%+10.4g| |%+015.5g| |%+10g|\n", ag, bg, c1g, c2g, c3g, dg, eg, fg);
	// ft_printf("|%+10g| |%+10.1g| |%+10.5g| |%+10.5g| |%+10.5g| |%+10.4g| |%+015.5g| |%+10g|\n", ag, bg, c1g, c2g, c3g, dg, eg, fg);
	// printf("\n");

	// double ag2 = 123.123;
	// double bg2 = 123.123;
	// double c1g2 = 123.123;
	// double c2g2 = 123.123;
	// double c3g2 = 123.123;
	// double dg2 = 123.123;
	// double eg2 = -123.123;
	// double fg2 = 123.123;
	// printf("|%+g| |%+.g| |%+.0g| |%+.1g| |%+.2g| |%+.3g| |%+.4g| |%+.5g|\n", ag2, bg2, c1g2, c2g2, c3g2, dg2, eg2, fg2);
	// ft_printf("|%+g| |%+.g| |%+.0g| |%+.1g| |%+.2g| |%+.3g| |%+.4g| |%+.5g|\n", ag2, bg2, c1g2, c2g2, c3g2, dg2, eg2, fg2);
	// double ae3 = 123.123;
	// double be2 = 123.123;
	// double c1e2 = 123.123;
	// double c2e2 = 123.123;
	// double c3e2 = 123.123;
	// double de2 = 123.123;
	// double ee2 = -123.123;
	// double fe2 = 123.123;
	// printf("|%e| |%.e| |%.0e| |%.1e| |%.2e| |%.3e| |%.4e| |%.5e|\n", ae3, be2, c1e2, c2e2, c3e2, de2, ee2, fe2);
	// ft_printf("|%e| |%.e| |%.0e| |%.1e| |%.2e| |%.3e| |%.4e| |%.5e|\n", ae3, be2, c1e2, c2e2, c3e2, de2, ee2, fe2);

	// printf("%#.20e\n", 123.025978548534310421734);
	// ft_printf("%#.20e\n", 123.025978548534310421734);
	// printf("%#.17e\n", -123.025978548534310421734);
	// ft_printf("%#.17e\n", -123.025978548534310421734);
	// printf("%#.13e\n", 0.999999999);
	// ft_printf("%#.13e\n", 0.999999999);
	// printf("%#.13e\n", -0.999999999);
	// ft_printf("%#.13e\n", -0.999999999);
	// printf("%#.e\n", 153.6);
	// ft_printf("%#.e\n", 153.6);
	// printf("%#e\n", -123.6);
	// ft_printf("%#e\n", -123.6);
	// printf("%#.1e\n", 123.6);
	// ft_printf("%#.1e\n", 123.6);
	// printf("%#.2e\n", 123.6);
	// ft_printf("%#.2e\n", 123.6);
	// printf("%#.3e\n", 123.6);
	// ft_printf("%#.3e\n", 123.6);
	// printf("%#.4e\n", 123.6);
	// ft_printf("%#.4e\n", 123.6);
	// printf("%#.5e\n", 123.6);
	// ft_printf("%#.5e\n", 123.6);
	// printf("%#.e\n", 12.3);
	// ft_printf("%#.e\n", 12.3);
	// printf("%#e\n", -0.6);
	// ft_printf("%#e\n", -0.6);
	// printf("%#.1e\n", 0.6);
	// ft_printf("%#.1e\n", 0.6);
	// printf("%#e\n", 0.0);
	// ft_printf("%#e\n", 0.0);

	// printf("%.6e\n", 11.11111);
	// ft_printf("%.6e\n\n", 11.11111);

	// int n1;
	// int n2;
	// printf("%.*e %n\n", 0, 0.6, &n1);
	// printf("n: %d\n", n1);
	// ft_printf("%.*e %n\n", 0, 0.6, &n1);
	// printf("n: %d\n\n", n1);
	// printf("%.*e %n\n", 0, 0.06, &n1);
	// printf("n: %d\n", n1);
	// ft_printf("%.*e %n\n", 0, 0.06, &n1);
	// printf("n: %d\n\n", n1);
	// printf("%.*e %n\n", 0, 0.006, &n1);
	// printf("n: %d\n", n1);
	// ft_printf("%.*e %n\n", 0, 0.006, &n1);
	// printf("n: %d\n\n", n1);
	// printf("%.*e %n\n", 1, 0.0006, &n1);
	// printf("n: %d\n", n1);
	// ft_printf("%.*e %n\n", 1, 0.0006, &n1);
	// printf("n: %d\n\n", n1);
	// printf("%.*e %n\n", 10, 6.0, &n1);
	// printf("n: %d\n", n1);
	// ft_printf("%.*e %n\n", 10, 6.0, &n1);
	// printf("n: %d\n\n", n1);
	// printf("%.*e %n\n", 20, 60000.0, &n1);
	// printf("n: %d\n", n1);
	// ft_printf("%.*e %n\n", 20, 60000.0, &n1);
	// printf("n: %d\n\n", n1);

	// double e;
	// int p;

	// e = 0.0;
	// while (e > -0.5)
	// {
	// 	p = 0;
	// 	while (p < 35)
	// 	{
	// 		printf("%.*e\n", p, e);
	// 		ft_printf("%.*e\n\n", p, e);
	// 		p++;
	// 	}
	// 	e -= 0.1;
	// }

	// ft_printf("test: %s %d %s\n", "one, ", 2, "three...");
	// ft_printf("test: %s\n", "two, ");
	// ft_printf("test: %s\n", "three...");

	// printf("%g\n", 0.000039);
	// ft_printf("%g\n", 0.000039);
	// printf("%g\n", 0.00003);
	// ft_printf("%g\n", 0.00003);
	// printf("%g\n", 0.00039);
	// ft_printf("%g\n", 0.00039);
	// printf("%g\n", 0.0000039);
	// ft_printf("%g\n", 0.0000039);
	// printf("%g\n", 0.00000039);
	// ft_printf("%g\n", 0.00000039);

	// printf("%s\n", ft_ftoa(0.5, 0, '0'));
	// printf("%s\n", ft_ftoa(1.5, 0, '0'));
	// printf("%s\n", ft_ftoa(0.0, 0, '0'));
	// printf("%s\n", ft_ftoa(-0.5, 0, '-'));
	// printf("%s\n", ft_ftoa(-0.0, 0, '-'));
	// printf("%s\n", ft_ftoa(0.0, 0, '0'));

	// char *s = "test";
	// char c1 = 't';
	// int d1 = 100;
	// int d2 = 8;
	// int n1;
	// int n2;
	// int n3;
	// int n4;
	// int n5;
	// printf("|%5c| %n |%-15s| %n |%015p| %n |%5p| %n |%p| %n\n", c1, &n1, s, &n2, s, &n3, d1, &n4, d2, &n5);
	// printf("%d, %d, %d, %d, %d\n", n1, n2, n3, n4, n5);
	// ft_printf("|%5c| %n |%-15s| %n |%015p| %n |%5p| %n |%p| %n\n", c1, &n1, s, &n2, s, &n3, d1, &n4, d2, &n5);
	// ft_printf("%d, %d, %d, %d, %d\n", n1, n2, n3, n4, n5);


	// static unsigned int		mx_u = 235;
	// static char				mx_c = 'G';
	// static char			   *mx_s = "Hello, World!";
	// static int				mx_i = 42;
	
	// printf("\n\nM I X E D    T E S T S\n\n");
	
	// printf("11+  %i    %p    %X    %u    %s    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_s, mx_u);
	// ft_printf("11-  %i    %p    %X    %u    %s    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_s, mx_u);
	// ft_printf("11-  %i    %p    %X    %u    %s    %x    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_s, mx_u, mx_u);
	// ft_printf("11-  %i    %p    %X    %u    %x    %x    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_u, mx_u, mx_u);
	// ft_printf("11-  %x    %x    %x    %x    %x    %x    %x  \n", mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u);
	// ft_printf("11-  %x    %x    %x    %x    %x    %x    %x    %x    %x    %x    %x    %x    %x  \n", mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u);
	
	// printf("+  %u    %%    %p    %x    %s    %i  \n", mx_u, &mx_i, mx_u, mx_s, mx_i);
	// ft_printf("-  %u    %%    %p    %x    %s    %i  \n", mx_u, &mx_i, mx_u, mx_s, mx_i);
	// printf("+  %x    %c    %X    %s    %u    %p  \n", mx_u, mx_c, mx_u, mx_s, mx_u, &mx_i);
	// ft_printf("-  %x    %c    %X    %s    %u    %p  \n", mx_u, mx_c, mx_u, mx_s, mx_u, &mx_i);
	// printf("+  %%    %i    %X    %p    %c    %s  \n", mx_i, mx_u, &mx_i, mx_c, mx_s);
	// ft_printf("-  %%    %i    %X    %p    %c    %s  \n", mx_i, mx_u, &mx_i, mx_c, mx_s);
	// printf("+  %u    %%    %s    %c    %x    %X  \n", mx_u, mx_s, mx_c, mx_u, mx_u);
	// ft_printf("-  %u    %%    %s    %c    %x    %X  \n", mx_u, mx_s, mx_c, mx_u, mx_u);
	// printf("+  %i    %c    %x    %u    %%    %X  \n", mx_i, mx_c, mx_u, mx_u, mx_u);
	// ft_printf("-  %i    %c    %x    %u    %%    %X  \n", mx_i, mx_c, mx_u, mx_u, mx_u);
	// printf("+  %c    %X    %i    %%    %s    %p  \n", mx_c, mx_u, mx_i, mx_s, &mx_i);
	// ft_printf("-  %c    %X    %i    %%    %s    %p  \n", mx_c, mx_u, mx_i, mx_s, &mx_i);
	// printf("+  %p    %x    %i    %c    %s    %u  \n", &mx_i, mx_u, mx_i, mx_c, mx_s, mx_u);
	// ft_printf("-  %p    %x    %i    %c    %s    %u  \n", &mx_i, mx_u, mx_i, mx_c, mx_s, mx_u);
	// printf("+  %i    %s    %%    %u    %c    %x  \n", mx_i, mx_s, mx_u, mx_c, mx_u);
	// ft_printf("-  %i    %s    %%    %u    %c    %x  \n", mx_i, mx_s, mx_u, mx_c, mx_u);
	// printf("+  %X    %p    %s    %%    %u    %x  \n", mx_u, &mx_i, mx_s, mx_u, mx_u);
	// ft_printf("-  %X    %p    %s    %%    %u    %x  \n", mx_u, &mx_i, mx_s, mx_u, mx_u);
	// printf("+  %c    %%    %u    %i    %x    %X  \n", mx_c, mx_u, mx_i, mx_u, mx_u);
	// ft_printf("-  %c    %%    %u    %i    %x    %X  \n", mx_c, mx_u, mx_i, mx_u, mx_u);
	
	// printf("11+  %i    %p    %X    %u    %s    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_s, mx_u);
	// ft_printf("11-  %i    %p    %X    %u    %s    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_s, mx_u);
	// ft_printf("11-  %i    %p    %X    %u    %s    %x    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_s, mx_u, mx_u);
	// ft_printf("11-  %i    %p    %X    %u    %x    %x    %x  \n", mx_i, &mx_i, mx_u, mx_u, mx_u, mx_u, mx_u);
	// ft_printf("11-  %x    %x    %x    %x    %x    %x    %x  \n", mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u);
	// ft_printf("11-  %x    %x    %x    %x    %x    %x    %x    %x    %x    %x    %x    %x    %x  \n", mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u, mx_u);
	
	// printf("+  %X    %c    %p    %x    %i    %u  \n", mx_u, mx_c, &mx_i, mx_u, mx_i, mx_u);
	// ft_printf("-  %X    %c    %p    %x    %i    %u  \n", mx_u, mx_c, &mx_i, mx_u, mx_i, mx_u);
	// printf("+  %%    %i    %u    %s    %c    %X  \n", mx_i, mx_u, mx_s, mx_c, mx_u);
	// ft_printf("-  %%    %i    %u    %s    %c    %X  \n", mx_i, mx_u, mx_s, mx_c, mx_u);
	// printf("+  %u    %c    %x    %s    %X    %i  \n", mx_u, mx_c, mx_u, mx_s, mx_u, mx_i);
	// ft_printf("-  %u    %c    %x    %s    %X    %i  \n", mx_u, mx_c, mx_u, mx_s, mx_u, mx_i);
	// printf("15+  %s    %p    %X    %c    %i    %x  \n", mx_s, &mx_i, mx_u, mx_c, mx_i, mx_u);
	// ft_printf("15-  %s    %p    %X    %c    %i    %x  \n", mx_s, &mx_i, mx_u, mx_c, mx_i, mx_u);
	// printf("+  %u    %c    %X    %x    %p    %s  \n", mx_u, mx_c, mx_u, mx_u, &mx_i, mx_s);
	// ft_printf("-  %u    %c    %X    %x    %p    %s  \n", mx_u, mx_c, mx_u, mx_u, &mx_i, mx_s);
	// printf("+  %c    %%    %i    %X    %u    %x  \n", mx_c, mx_i, mx_u, mx_u, mx_u);
	// ft_printf("-  %c    %%    %i    %X    %u    %x  \n", mx_c, mx_i, mx_u, mx_u, mx_u);
	// printf("+  %s    %%    %x    %X    %c    %u  \n", mx_s, mx_u, mx_u, mx_c, mx_u);
	// ft_printf("-  %s    %%    %x    %X    %c    %u  \n", mx_s, mx_u, mx_u, mx_c, mx_u);
	// printf("+  %x    %s    %X    %%    %p    %i  \n", mx_u, mx_s, mx_u, &mx_i, mx_i);
	// ft_printf("-  %x    %s    %X    %%    %p    %i  \n", mx_u, mx_s, mx_u, &mx_i, mx_i);
	// printf("+  %%    %p    %i    %c    %x    %X  \n", &mx_i, mx_i, mx_c, mx_u, mx_u);
	// ft_printf("-  %%    %p    %i    %c    %x    %X  \n", &mx_i, mx_i, mx_c, mx_u, mx_u);
	// printf("+  %c    %s    %%    %u    %p    %x  \n", mx_c, mx_s, mx_u, &mx_i, mx_u);
	// ft_printf("-  %c    %s    %%    %u    %p    %x  \n", mx_c, mx_s, mx_u, &mx_i, mx_u);
	// printf("22+  %c    %i    %u    %s    %p    %x  \n", mx_c, mx_i, mx_u, mx_s, &mx_i, mx_u);
	// ft_printf("22-  %c    %i    %u    %s    %p    %x  \n", mx_c, mx_i, mx_u, mx_s, &mx_i, mx_u);
	// printf("+  %X    %x    %s    %c    %i    %u  \n", mx_u, mx_u, mx_s, mx_c, mx_i, mx_u);
	// ft_printf("-  %X    %x    %s    %c    %i    %u  \n", mx_u, mx_u, mx_s, mx_c, mx_i, mx_u);
	// printf("+  %x    %c    %X    %p    %s    %p  \n", mx_u, mx_c, mx_u, &mx_i, mx_s, &mx_i);
	// ft_printf("-  %x    %c    %X    %p    %s    %p  \n", mx_u, mx_c, mx_u, &mx_i, mx_s, &mx_i);
	// printf("+  %X    %%    %i    %s    %p    %x  \n", mx_u, mx_i, mx_s, &mx_i, mx_u);
	// ft_printf("-  %X    %%    %i    %s    %p    %x  \n", mx_u, mx_i, mx_s, &mx_i, mx_u);
	// printf("+  %i    %p    %x    %c    %X    %p  \n", mx_i, &mx_i, mx_u, mx_c, mx_u, &mx_i);
	// ft_printf("-  %i    %p    %x    %c    %X    %p  \n", mx_i, &mx_i, mx_u, mx_c, mx_u, &mx_i);
	// printf("+  %X    %c    %i    %u    %x    %p  \n", mx_u, mx_c, mx_i, mx_u, mx_u, &mx_i);
	// ft_printf("-  %X    %c    %i    %u    %x    %p  \n", mx_u, mx_c, mx_i, mx_u, mx_u, &mx_i);
	// printf("+  %i    %u    %c    %%    %X    %p  \n", mx_i, mx_u, mx_c, mx_u, &mx_i);
	// ft_printf("-  %i    %u    %c    %%    %X    %p  \n", mx_i, mx_u, mx_c, mx_u, &mx_i);
	// printf("+  %s    %i    %c    %p    %x    %u  \n", mx_s, mx_i, mx_c, &mx_i, mx_u, mx_u);
	// ft_printf("-  %s    %i    %c    %p    %x    %u  \n", mx_s, mx_i, mx_c, &mx_i, mx_u, mx_u);
	// printf("+  %p    %%    %x    %X    %i    %c  \n", &mx_i, mx_u, mx_u, mx_i, mx_c);
	// ft_printf("-  %p    %%    %x    %X    %i    %c  \n", &mx_i, mx_u, mx_u, mx_i, mx_c);
	// printf("+  %X    %i    %s    %%    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, &mx_i);
	// ft_printf("-  %X    %i    %s    %%    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, &mx_i);
	// printf("+  %%    %u    %p    %i    %X    %c  \n", mx_u, &mx_i, mx_i, mx_u, mx_c);
	// ft_printf("-  %%    %u    %p    %i    %X    %c  \n", mx_u, &mx_i, mx_i, mx_u, mx_c);
	// printf("+  %x    %X    %p    %s    %i    %c  \n", mx_u, mx_u, &mx_i, mx_s, mx_i, mx_c);
	// ft_printf("-  %x    %X    %p    %s    %i    %c  \n", mx_u, mx_u, &mx_i, mx_s, mx_i, mx_c);
	// printf("+  %c    %%    %s    %X    %x    %p  \n", mx_c, mx_s, mx_u, mx_u, &mx_i);
	// ft_printf("-  %c    %%    %s    %X    %x    %p  \n", mx_c, mx_s, mx_u, mx_u, &mx_i);
	// printf("+  %x    %X    %p    %s    %i    %u  \n", mx_u, mx_u, &mx_i, mx_s, mx_i, mx_u);
	// ft_printf("-  %x    %X    %p    %s    %i    %u  \n", mx_u, mx_u, &mx_i, mx_s, mx_i, mx_u);
	// printf("+  %p    %u    %s    %X    %c    %p  \n", &mx_i, mx_u, mx_s, mx_u, mx_c, &mx_i);
	// ft_printf("-  %p    %u    %s    %X    %c    %p  \n", &mx_i, mx_u, mx_s, mx_u, mx_c, &mx_i);
	// printf("+  %X    %s    %x    %p    %%    %i  \n", mx_u, mx_s, mx_u, &mx_i, mx_i);
	// ft_printf("-  %X    %s    %x    %p    %%    %i  \n", mx_u, mx_s, mx_u, &mx_i, mx_i);
	// printf("+  %x    %s    %%    %p    %i    %c  \n", mx_u, mx_s, &mx_i, mx_i, mx_c);
	// ft_printf("-  %x    %s    %%    %p    %i    %c  \n", mx_u, mx_s, &mx_i, mx_i, mx_c);
	// printf("+  %s    %u    %x    %%    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c);
	// ft_printf("-  %s    %u    %x    %%    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c);
	// printf("+  %p    %i    %x    %%    %u    %X  \n", &mx_i, mx_i, mx_u, mx_u, mx_u);
	// ft_printf("-  %p    %i    %x    %%    %u    %X  \n", &mx_i, mx_i, mx_u, mx_u, mx_u);
	// printf("+  %%    %c    %X    %p    %u    %x  \n", mx_c, mx_u, &mx_i, mx_u, mx_u);
	// ft_printf("-  %%    %c    %X    %p    %u    %x  \n", mx_c, mx_u, &mx_i, mx_u, mx_u);
	// printf("+  %u    %c    %%    %p    %i    %s  \n", mx_u, mx_c, &mx_i, mx_i, mx_s);
	// ft_printf("-  %u    %c    %%    %p    %i    %s  \n", mx_u, mx_c, &mx_i, mx_i, mx_s);
	// printf("+  %%    %i    %s    %u    %c    %X  \n", mx_i, mx_s, mx_u, mx_c, mx_u);
	// ft_printf("-  %%    %i    %s    %u    %c    %X  \n", mx_i, mx_s, mx_u, mx_c, mx_u);
	// printf("+  %%    %i    %u    %s    %X    %p  \n", mx_i, mx_u, mx_s, mx_u, &mx_i);
	// ft_printf("-  %%    %i    %u    %s    %X    %p  \n", mx_i, mx_u, mx_s, mx_u, &mx_i);
	// printf("+  %s    %c    %X    %%    %i    %p  \n", mx_s, mx_c, mx_u, mx_i, &mx_i);
	// ft_printf("-  %s    %c    %X    %%    %i    %p  \n", mx_s, mx_c, mx_u, mx_i, &mx_i);
	// printf("+  %x    %X    %u    %i    %%    %s  \n", mx_u, mx_u, mx_u, mx_i, mx_s);
	// ft_printf("-  %x    %X    %u    %i    %%    %s  \n", mx_u, mx_u, mx_u, mx_i, mx_s);
	// printf("+  %x    %u    %s    %i    %p    %p  \n", mx_u, mx_u, mx_s, mx_i, &mx_i, &mx_i);
	// ft_printf("-  %x    %u    %s    %i    %p    %p  \n", mx_u, mx_u, mx_s, mx_i, &mx_i, &mx_i);
	// printf("+  %X    %i    %s    %x    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, mx_u, &mx_i);
	// ft_printf("-  %X    %i    %s    %x    %u    %p  \n", mx_u, mx_i, mx_s, mx_u, mx_u, &mx_i);
	// printf("+  %c    %i    %%    %X    %p    %u  \n", mx_c, mx_i, mx_u, &mx_i, mx_u);
	// ft_printf("-  %c    %i    %%    %X    %p    %u  \n", mx_c, mx_i, mx_u, &mx_i, mx_u);
	// printf("+  %s    %u    %i    %X    %%    %c  \n", mx_s, mx_u, mx_i, mx_u, mx_c);
	// ft_printf("-  %s    %u    %i    %X    %%    %c  \n", mx_s, mx_u, mx_i, mx_u, mx_c);
	// printf("+  %%    %p    %X    %i    %s    %x  \n", &mx_i, mx_u, mx_i, mx_s, mx_u);
	// ft_printf("-  %%    %p    %X    %i    %s    %x  \n", &mx_i, mx_u, mx_i, mx_s, mx_u);
	// printf("4+  %%    %x    %p    %c    %u    %X  \n", mx_u, &mx_i, mx_c, mx_u, mx_u);
	// ft_printf("4-  %%    %x    %p    %c    %u    %X  \n", mx_u, &mx_i, mx_c, mx_u, mx_u);
	// printf("4+  %i    %x    %p    %c    %u    %X  \n", mx_i, mx_u, &mx_i, mx_c, mx_u, mx_u);
	// ft_printf("4-  %i    %x    %p    %c    %u    %X  \n", mx_i, mx_u, &mx_i, mx_c, mx_u, mx_u);
	// printf("+  %X    %c    %%    %i    %x    %s  \n", mx_u, mx_c, mx_i, mx_u, mx_s);
	// ft_printf("-  %X    %c    %%    %i    %x    %s  \n", mx_u, mx_c, mx_i, mx_u, mx_s);
	// printf("+  %x    %c    %u    %X    %p    %p  \n", mx_u, mx_c, mx_u, mx_u, &mx_i, &mx_i);
	// ft_printf("-  %x    %c    %u    %X    %p    %p  \n", mx_u, mx_c, mx_u, mx_u, &mx_i, &mx_i);
	// printf("+  %p    %u    %c    %s    %i    %p  \n", &mx_i, mx_u, mx_c, mx_s, mx_i, &mx_i);
	// ft_printf("-  %p    %u    %c    %s    %i    %p  \n", &mx_i, mx_u, mx_c, mx_s, mx_i, &mx_i);
	// printf("+  %x    %p    %s    %u    %%    %c  \n", mx_u, &mx_i, mx_s, mx_u, mx_c);
	// ft_printf("-  %x    %p    %s    %u    %%    %c  \n", mx_u, &mx_i, mx_s, mx_u, mx_c);
	// printf("+  %%    %i    %X    %p    %u    %s  \n", mx_i, mx_u, &mx_i, mx_u, mx_s);
	// ft_printf("-  %%    %i    %X    %p    %u    %s  \n", mx_i, mx_u, &mx_i, mx_u, mx_s);
	// printf("+  %%    %u    %c    %s    %i    %x  \n", mx_u, mx_c, mx_s, mx_i, mx_u);
	// ft_printf("-  %%    %u    %c    %s    %i    %x  \n", mx_u, mx_c, mx_s, mx_i, mx_u);
	// printf("+  %c    %i    %u    %x    %s    %p  \n", mx_c, mx_i, mx_u, mx_u, mx_s, &mx_i);
	// ft_printf("-  %c    %i    %u    %x    %s    %p  \n", mx_c, mx_i, mx_u, mx_u, mx_s, &mx_i);
	// printf("+  %c    %i    %s    %u    %x    %p  \n", mx_c, mx_i, mx_s, mx_u, mx_u, &mx_i);
	// ft_printf("-  %c    %i    %s    %u    %x    %p  \n", mx_c, mx_i, mx_s, mx_u, mx_u, &mx_i);
	// printf("+  %u    %%    %x    %i    %X    %c  \n", mx_u, mx_u, mx_i, mx_u, mx_c);
	// ft_printf("-  %u    %%    %x    %i    %X    %c  \n", mx_u, mx_u, mx_i, mx_u, mx_c);
	// printf("+  %x    %s    %u    %i    %c    %X  \n", mx_u, mx_s, mx_u, mx_i, mx_c, mx_u);
	// ft_printf("-  %x    %s    %u    %i    %c    %X  \n", mx_u, mx_s, mx_u, mx_i, mx_c, mx_u);
	// printf("+  %%    %c    %i    %p    %s    %X  \n", mx_c, mx_i, &mx_i, mx_s, mx_u);
	// ft_printf("-  %%    %c    %i    %p    %s    %X  \n", mx_c, mx_i, &mx_i, mx_s, mx_u);
	// printf("+  %s    %x    %%    %X    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c);
	// ft_printf("-  %s    %x    %%    %X    %i    %c  \n", mx_s, mx_u, mx_u, mx_i, mx_c);
	// printf("+  %x    %X    %u    %c    %%    %i  \n", mx_u, mx_u, mx_u, mx_c, mx_i);
	// ft_printf("-  %x    %X    %u    %c    %%    %i  \n", mx_u, mx_u, mx_u, mx_c, mx_i);
	// printf("+  %c    %%    %i    %p    %u    %X  \n", mx_c, mx_i, &mx_i, mx_u, mx_u);
	// ft_printf("-  %c    %%    %i    %p    %u    %X  \n", mx_c, mx_i, &mx_i, mx_u, mx_u);
	// printf("+  %i    %c    %%    %u    %X    %p  \n", mx_i, mx_c, mx_u, mx_u, &mx_i);
	// ft_printf("-  %i    %c    %%    %u    %X    %p  \n", mx_i, mx_c, mx_u, mx_u, &mx_i);
	// printf("+  %s    %i    %x    %u    %c    %p  \n", mx_s, mx_i, mx_u, mx_u, mx_c, &mx_i);
	// ft_printf("-  %s    %i    %x    %u    %c    %p  \n", mx_s, mx_i, mx_u, mx_u, mx_c, &mx_i);
	// printf("+  %s    %x    %c    %p    %u    %X  \n", mx_s, mx_u, mx_c, &mx_i, mx_u, mx_u);
	// ft_printf("-  %s    %x    %c    %p    %u    %X  \n", mx_s, mx_u, mx_c, &mx_i, mx_u, mx_u);
	// printf("+  %%    %s    %p    %i    %X    %c  \n", mx_s, &mx_i, mx_i, mx_u, mx_c);
	// ft_printf("-  %%    %s    %p    %i    %X    %c  \n", mx_s, &mx_i, mx_i, mx_u, mx_c);
	// printf("+  %x    %X    %i    %%    %s    %u  \n", mx_u, mx_u, mx_i, mx_s, mx_u);
	// ft_printf("-  %x    %X    %i    %%    %s    %u  \n", mx_u, mx_u, mx_i, mx_s, mx_u);
	// printf("+  %s    %i    %X    %c    %%    %p  \n", mx_s, mx_i, mx_u, mx_c, &mx_i);
	// ft_printf("-  %s    %i    %X    %c    %%    %p  \n", mx_s, mx_i, mx_u, mx_c, &mx_i);
	// printf("+  %x    %p    %c    %s    %X    %u  \n", mx_u, &mx_i, mx_c, mx_s, mx_u, mx_u);
	// ft_printf("-  %x    %p    %c    %s    %X    %u  \n", mx_u, &mx_i, mx_c, mx_s, mx_u, mx_u);
	// printf("+  %%    %X    %u    %x    %p    %c  \n", mx_u, mx_u, mx_u, &mx_i, mx_c);
	// ft_printf("-  %%    %X    %u    %x    %p    %c  \n", mx_u, mx_u, mx_u, &mx_i, mx_c);
	// printf("+  %p    %c    %s    %u    %i    %x  \n", &mx_i, mx_c, mx_s, mx_u, mx_i, mx_u);
	// ft_printf("-  %p    %c    %s    %u    %i    %x  \n", &mx_i, mx_c, mx_s, mx_u, mx_i, mx_u);
	// printf("+  %i    %c    %%    %p    %u    %x  \n", mx_i, mx_c, &mx_i, mx_u, mx_u);
	// ft_printf("-  %i    %c    %%    %p    %u    %x  \n", mx_i, mx_c, &mx_i, mx_u, mx_u);
	// printf("+  %X    %%    %u    %c    %p    %s  \n", mx_u, mx_u, mx_c, &mx_i, mx_s);
	// ft_printf("-  %X    %%    %u    %c    %p    %s  \n", mx_u, mx_u, mx_c, &mx_i, mx_s);
	// printf("+  %X    %i    %c    %u    %p    %s  \n", mx_u, mx_i, mx_c, mx_u, &mx_i, mx_s);
	// ft_printf("-  %X    %i    %c    %u    %p    %s  \n", mx_u, mx_i, mx_c, mx_u, &mx_i, mx_s);
	// printf("+  %p    %%    %c    %X    %u    %i  \n", &mx_i, mx_c, mx_u, mx_u, mx_i);
	// ft_printf("-  %p    %%    %c    %X    %u    %i  \n", &mx_i, mx_c, mx_u, mx_u, mx_i);
	// printf("+  %s    %c    %i    %%    %p    %X  \n", mx_s, mx_c, mx_i, &mx_i, mx_u);
	// ft_printf("-  %s    %c    %i    %%    %p    %X  \n", mx_s, mx_c, mx_i, &mx_i, mx_u);
	// printf("+  %p    %%    %c    %u    %s    %X  \n", &mx_i, mx_c, mx_u, mx_s, mx_u);
	// ft_printf("-  %p    %%    %c    %u    %s    %X  \n", &mx_i, mx_c, mx_u, mx_s, mx_u);
	// printf("+  %x    %c    %%    %s    %X    %i  \n", mx_u, mx_c, mx_s, mx_u, mx_i);
	// ft_printf("-  %x    %c    %%    %s    %X    %i  \n", mx_u, mx_c, mx_s, mx_u, mx_i);
	// printf("+  %%    %c    %i    %X    %s    %x  \n", mx_c, mx_i, mx_u, mx_s, mx_u);
	// ft_printf("-  %%    %c    %i    %X    %s    %x  \n", mx_c, mx_i, mx_u, mx_s, mx_u);
	// printf("+  %i    %X    %%    %c    %u    %s  \n", mx_i, mx_u, mx_c, mx_u, mx_s);
	// ft_printf("-  %i    %X    %%    %c    %u    %s  \n", mx_i, mx_u, mx_c, mx_u, mx_s);
	// printf("+  %p    %x    %c    %s    %u    %p  \n", &mx_i, mx_u, mx_c, mx_s, mx_u, &mx_i);
	// ft_printf("-  %p    %x    %c    %s    %u    %p  \n", &mx_i, mx_u, mx_c, mx_s, mx_u, &mx_i);
	// printf("+  %u    %p    %c    %X    %s    %p  \n", mx_u, &mx_i, mx_c, mx_u, mx_s, &mx_i);
	// ft_printf("-  %u    %p    %c    %X    %s    %p  \n", mx_u, &mx_i, mx_c, mx_u, mx_s, &mx_i);
	// printf("+  %p    %c    %u    %X    %s    %p  \n", &mx_i, mx_c, mx_u, mx_u, mx_s, &mx_i);
	// ft_printf("-  %p    %c    %u    %X    %s    %p  \n", &mx_i, mx_c, mx_u, mx_u, mx_s, &mx_i);
	// printf("+  %i    %u    %X    %p    %c    %p  \n", mx_i, mx_u, mx_u, &mx_i, mx_c, &mx_i);
	// ft_printf("-  %i    %u    %X    %p    %c    %p  \n", mx_i, mx_u, mx_u, &mx_i, mx_c, &mx_i);
	// printf("+  %i    %c    %p    %%    %X    %u  \n", mx_i, mx_c, &mx_i, mx_u, mx_u);
	// ft_printf("-  %i    %c    %p    %%    %X    %u  \n", mx_i, mx_c, &mx_i, mx_u, mx_u);
	// printf("+  %s    %c    %i    %x    %p    %u  \n", mx_s, mx_c, mx_i, mx_u, &mx_i, mx_u);
	// ft_printf("-  %s    %c    %i    %x    %p    %u  \n", mx_s, mx_c, mx_i, mx_u, &mx_i, mx_u);
	// printf("+  %u    %s    %x    %p    %i    %c  \n", mx_u, mx_s, mx_u, &mx_i, mx_i, mx_c);
	// ft_printf("-  %u    %s    %x    %p    %i    %c  \n", mx_u, mx_s, mx_u, &mx_i, mx_i, mx_c);
	// printf("+  %u    %p    %X    %c    %%    %x  \n", mx_u, &mx_i, mx_u, mx_c, mx_u);
	// ft_printf("-  %u    %p    %X    %c    %%    %x  \n", mx_u, &mx_i, mx_u, mx_c, mx_u);
	// printf("+  %c    %p    %X    %x    %%    %s  \n", mx_c, &mx_i, mx_u, mx_u, mx_s);
	// ft_printf("-  %c    %p    %X    %x    %%    %s  \n", mx_c, &mx_i, mx_u, mx_u, mx_s);
	// printf("+  %x    %c    %s    %p    %u    %i  \n", mx_u, mx_c, mx_s, &mx_i, mx_u, mx_i);
	// ft_printf("-  %x    %c    %s    %p    %u    %i  \n", mx_u, mx_c, mx_s, &mx_i, mx_u, mx_i);
	// printf("+  %X    %p    %c    %%    %u    %i  \n", mx_u, &mx_i, mx_c, mx_u, mx_i);
	// ft_printf("-  %X    %p    %c    %%    %u    %i  \n", mx_u, &mx_i, mx_c, mx_u, mx_i);
	// printf("+  %%    %i    %x    %p    %c    %s  \n", mx_i, mx_u, &mx_i, mx_c, mx_s);
	// ft_printf("-  %%    %i    %x    %p    %c    %s  \n", mx_i, mx_u, &mx_i, mx_c, mx_s);
	// printf("+  %X    %p    %c    %s    %i    %u  \n", mx_u, &mx_i, mx_c, mx_s, mx_i, mx_u);
	// ft_printf("-  %X    %p    %c    %s    %i    %u  \n", mx_u, &mx_i, mx_c, mx_s, mx_i, mx_u);
	// printf("+  %u    %i    %p    %x    %s    %X  \n", mx_u, mx_i, &mx_i, mx_u, mx_s, mx_u);
	// ft_printf("-  %u    %i    %p    %x    %s    %X  \n", mx_u, mx_i, &mx_i, mx_u, mx_s, mx_u);
	// printf("+  %i    %s    %%    %p    %X    %c  \n", mx_i, mx_s, &mx_i, mx_u, mx_c);
	// ft_printf("-  %i    %s    %%    %p    %X    %c  \n", mx_i, mx_s, &mx_i, mx_u, mx_c);
	// printf("+  %X    %p    %c    %u    %x    %i  \n", mx_u, &mx_i, mx_c, mx_u, mx_u, mx_i);
	// ft_printf("-  %X    %p    %c    %u    %x    %i  \n", mx_u, &mx_i, mx_c, mx_u, mx_u, mx_i);

	// printf("| %s +| %59lc|\n", "test", (char)204);
	// ft_printf("-|%59lc|\n", (char)204);
	// printf("+|%-8lc|\n", (char)204);
	// ft_printf("-|%-8lc|\n", (char)204);
	
	// int ret;
	// ft_printf("\nTESTING WIDE CHAR (%%lc)\n");
	// ft_printf("TEST 1: \n");
	// ret = printf("|%3lc|\n", (char)204);
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%3lc|\n", (char)204);
	// ft_printf("return: %d\n", ret);
	
	// ft_printf("\nTEST 2: \n");
	// ret = printf("|%3lc|\n", (wint_t)204);
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%3lc|\n", (wint_t)204);
	// ft_printf("return: %d\n", ret);

	// ft_printf("\nTEST 3: \n");
	// ret = printf("|%3lc|\n", (char)5000);
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%3lc|\n", (char)5000);
	// ft_printf("return: %d\n", ret);

	// ft_printf("\nTEST 4: \n");
	// ret = printf("|%3lc|\n", (wint_t)5000);
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%3lc|\n", (wint_t)5000);
	// ft_printf("return: %d\n", ret);

	// ft_printf("\nTEST 5: \n");
	// ret = printf("|%3lc|\n", 0x2620);
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%3lc|\n", 0x2620);
	// ft_printf("return: %d\n", ret);

	// ft_printf("\nTEST 6: \n");
	// ret = printf("|%3lc|\n", (char)552);
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%3lc|\n", (char)552);
	// ft_printf("return: %d\n", ret);

	// ft_printf("\nTEST 7: \n");
	// ret = printf("|%3lc|\n", (wint_t)552);
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%3lc|\n", (wint_t)552);
	// ft_printf("return: %d\n", ret);
	

	// ft_printf("\nTESTING WIDE STRING (%%ls)\n");
	// ft_printf("TEST 1: \n");
	// ret = printf("|%ls|\n", L"\xE2\x98\xA0");
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%ls|\n", L"\xE2\x98\xA0");
	// ft_printf("return: %d\n", ret);
	
	// ft_printf("\nTEST 2: \n");
	// ret = printf("|%ls|\n", L"\xE2");
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%ls|\n", L"\xE2");
	// ft_printf("return: %d\n", ret);

	// ft_printf("\nTEST 3: \n");
	// ret = printf("|%2ls|\n", L"\xE2");
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("|%2ls|\n", L"\xE2");
	// ft_printf("return: %d\n", ret);

	// ft_printf("\nTEST 4: \n");
	// ret = printf("+|%ls%4s|\n", L"hello ", "world");
	// ft_printf("return: %d\n", ret);
	// ret = ft_printf("+|%ls%4s|\n", L"hello ", "world");
	// ft_printf("return: %d\n", ret);

	// system("leaks a.out > leaks_test.txt");

	printf("%.0p\n", 0);
	ft_printf("%.0p\n", 0);
	printf("%p\n", 0);
	ft_printf("%p\n", 0);
	printf("%.0p\n", 100);
	ft_printf("%.0p\n", 100);
	printf("%.1p\n", 0);
	ft_printf("%.1p\n", 0);
	printf("%.2p\n", 0);
	ft_printf("%.2p\n", 0);

	printf("%.0d\n", 0);
	ft_printf("%.0d\n", 0);
	printf("%.0d\n", 100);
	ft_printf("%.0d\n", 100);
	printf("%.1d\n", 0);
	ft_printf("%.1d\n", 0);
	printf("%.2d\n", 0);
	ft_printf("%.2d\n", 0);
	return (0);
}


/*
./disable-test "*_g"
./disable-test "*_notrequired"
./disable-test argnum
./disable-test notinsubject

*/