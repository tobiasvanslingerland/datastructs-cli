This is an experimental program that runs a CLI (Command Line Interface) on the TI CC3220S Launchpad.
It communicates with any terminal over UART, which runs at 115200 baud.
The command "help" will give a list of available commands.
Pressing tab will give command suggestions, and the command history can be navigated by using the arrow keys.
Programmers can easily add their own commands in the cmds.h file.

I wrote this program to teach myself some more advanced C skills and some basic data structures.
This program includes the Trie for storing commands and their function pointers, and a doubly linked list for the command history.
Only a debug configuration is included, as this program is not meant to be flashed to a microcontroller permanently.
The program uses TI RTOS, and additional threads can be added easily.
