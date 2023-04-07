# CuriousMalloc
This is an implementation of my own malloc() function and a custom tiny allocator in C.
<br>
<br>
The idea of this project was to learn more about malloc, memory allocation and try to create something by myself. The project does not use any 3rd party or built-in allocation mechanisms or methods. A user may allocate and free memory using dedicated c_malloc (Curious malloc) and c_free (Curious free) functions. Allocation supports 2 strategies - First Fit and Best fit to prevent fragmentation.
<br>
In order to compile the allocator for the First Fit strategy, use `make ff`.
<br>
To utilize the Best Fit strategy, use `make bf`.
<br>
By default with `make` the allocator is compiled with the First FIt strategy.
<br>
You may see examples of allocation and freeing of memory in `main.c` file. Just run `./main` after compiling with the commands from above.
