#!/bin/bash

# Define a list of arguments
args=(
    map_test/good/cheese_maze2.cub
    map_test/good/cheese_maze.cub
    map_test/good/test_map.cub
    map_test/good/subject_map.cub
    map_test/good/test_pos_left.cub
    map_test/good/test_whitespace.cub
    map_test/good/test_map_hole.cub
    map_test/good/library.cub
    map_test/good/works.cub
    map_test/good/test_textures.cub
    map_test/good/dungeon.cub
    map_test/good/test_pos_right.cub
    map_test/good/test_pos_bottom.cub
    map_test/bad/*.cub
    ourmaps/bad/*.cub
)

# Iterate over each argument
for arg in "${args[@]}"; do
    echo "Executing command with argument: $arg"
    # Replace 'command' with your command and "$arg" as its argument
    $1 "$arg"
done