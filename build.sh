gcc -c schedulingSim.c -g
gcc -c queue.c -g
gcc -o schedSim queue.o schedulingSim.o -g