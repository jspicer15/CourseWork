# Bradford Smith (bsmith8)
# CS 492 Assignment 3 README.txt
# 05/01/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

A note on `file_list.txt` and `dir_list.txt`:
    These files have intentionally not been included in this archive because the
    Makefile automatically generates them. The Makefile contains a target
    `inputs` that will generate these input files, this target also runs
    automatically any time the default `all` target is run. By default the
    `inputs` target uses this directory (`..` relative to the `src` directory) as
    the "root" for generating the input files but this can be changed by
    defining the `ROOT` variable. (e.g. `make inputs ROOT=~` will generate input
    files using the user's home directory as the "root", and this also works for
    the default `all` target, i.e `make ROOT=~`) These files will only be
    generated if they do not already exist, so the program can still be used
    with preexisting input files.

To run the code:
    Use the Makefile to compile the program, `make` should be sufficient in most
    situations. The executable will be named `fs`.
