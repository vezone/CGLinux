#!/bin/bash

valgrind --leak-check=yes --show-leak-kinds=definite bin/Debug-linux-x86_64/CGLinux/CGLinux
