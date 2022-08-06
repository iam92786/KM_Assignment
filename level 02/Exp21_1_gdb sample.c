Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from sample...
(gdb) l
1	  int Change_Value = 0;
2	  int Sum_it (int, int);
3	  void error_with_code (void);
4	 int main (void)
5	 {  
6	    int Arg_1 = 20, Arg_2 = 40;
7	    int i;
8	     for (i = 0; i < 10;i++) 
9	     {
10	        if (Arg_1 > Arg_2)
(gdb) b 8
Breakpoint 1 at 0x1143: file gdb_sample.c, line 8.
(gdb) l
11	             Arg_2 = Sum_it (Arg_1, Arg_2);
12	        else
13	            Arg_1 = Sum_it (Arg_1, Arg_2);
14	     }
15	     error_with_code ();
16	 }   /* End of main() */
17	
18	 int Sum_it (int a, int b)
19	 {
20	     return a+b;
(gdb) l
21	 } /* End of Sum_it */
22	
23	 void error_with_code(void)
24	 {
25	    int divide_value;
26	    int result;
27	    divide_value = Change_Value;
28	    result = 10 / divide_value;
29	    return ;
30	
(gdb) b error_with_code
Breakpoint 2 at 0x11a8: file gdb_sample.c, line 24.
(gdb) i b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000000000001143 in main at gdb_sample.c:8
2       breakpoint     keep y   0x00000000000011a8 in error_with_code at gdb_sample.c:24
(gdb) r
Starting program: /home/im-rt-lp-1134/Downloads/level2-master/debug/user/gdb/General_Debug/sample 

Breakpoint 1, main () at gdb_sample.c:8
8	     for (i = 0; i < 10;i++) 
(gdb) p Arg1
No symbol "Arg1" in current context.
(gdb) p Arg_1
$1 = 20
(gdb) p Arg_2
$2 = 40
(gdb) s
10	        if (Arg_1 > Arg_2)
(gdb) s
13	            Arg_1 = Sum_it (Arg_1, Arg_2);
(gdb) s
Sum_it (a=21845, b=1431654864) at gdb_sample.c:19
19	 {
(gdb) 
20	     return a+b;
(gdb) s
21	 } /* End of Sum_it */
(gdb) s
main () at gdb_sample.c:8
8	     for (i = 0; i < 10;i++) 
(gdb) 
10	        if (Arg_1 > Arg_2)
(gdb) p Arg_2
$3 = 40
(gdb) p Arg_1
$4 = 60
(gdb) c
Continuing.

Breakpoint 2, error_with_code () at gdb_sample.c:24
24	 {
(gdb) p Arg_1
No symbol "Arg_1" in current context.
(gdb) p Change_value
No symbol "Change_value" in current context.
(gdb) p Change_Value
$5 = 0
(gdb) s
27	    divide_value = Change_Value;
(gdb) 
28	    result = 10 / divide_value;
(gdb) s

Program received signal SIGFPE, Arithmetic exception.
0x00005555555551bf in error_with_code () at gdb_sample.c:28
28	    result = 10 / divide_value;

