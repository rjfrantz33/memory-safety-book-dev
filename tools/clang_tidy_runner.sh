#!/bin/bash
# Invokes clang-tidy via a Python wrapper that fixes -isystem ordering
# for GCC 15 + clang-tidy 18. See clang_tidy_wrapper.py for details.
exec python3 -c "
import os, sys

args, isystem_cpp, isystem_other = [], [], []
it = iter(sys.argv[1:])
for arg in it:
    if arg == '-isystem':
        path = next(it)
        (isystem_cpp if '/c++/' in path else isystem_other).extend(['-isystem', path])
    else:
        args.append(arg)

os.execvp('clang-tidy', ['clang-tidy'] + args + isystem_cpp + isystem_other)
" "$@"
