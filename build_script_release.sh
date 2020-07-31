#!/bin/bash

rm bin/Release-linux-x86_64/Sandbox/Sandbox
make config=release
bin/Release-linux-x86_64/Sandbox/Sandbox
