#!/bin/bash

rm bin/Debug-linux-x86_64/Sandbox/Sandbox
make config=debug
bin/Debug-linux-x86_64/Sandbox/Sandbox
