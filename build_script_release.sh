#!/bin/bash

rm bin/Release-linux-x86_64/CGLinux/CGLinux
make config=release
bin/Release-linux-x86_64/CGLinux/CGLinux
