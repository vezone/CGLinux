#!/bin/bash

rm bin/Debug-linux-x86_64/SandboxApp/SandboxApp
make config=debug
bin/Debug-linux-x86_64/SandboxApp/SandboxApp
