Name: Nallabolu Manasa

Project: Ring Buffer Implementation in Embedded C

Build Instructions:
gcc -Wall -std=c99 main.c ringbuf.c -o ringbuf
./ringbuf


Description:
This project implements an 8-byte circular ring buffer for uint8_t data.
It supports initialization, write, read, full/empty checks, and byte count operations.
It also uses bitwise AND optimization for efficient wrap-around indexing.
