# Turing Machine visualizer
A small TUI program for visualizing how a turing program works.

A turing program needs to be in the Examples folder given as a .txt file
where each line is an instruction in the format of $$q_i|a|b|T|q_j$$
- $q_i$(string) the current step
- $q_j$(string) the next step
- $a$(char) the character in the current position
- $b$(char) the updated character in the current position
- $T$ is either 'R' for right, 'L' for left, or 'P' (also 'S') for staying in the current position
comments starting with '#' and empty lines will be ignored

Once started use 'a' and 'd' to move the viewport, and 's' to move to the next step

Use the "macros.h" for configuration before compiling

# Future additions
- ability to choose file containing the program during runtime
- reverting to a previous step