#!/bin/bash

rm bin/Debug-linux-x86_64/CGLinux/CGLinux
make config=debug
bin/Debug-linux-x86_64/CGLinux/CGLinux
