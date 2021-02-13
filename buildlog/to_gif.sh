#! /usr/bin/env bash

input_file=$1
file_root="${input_file%%.*}"
filename_gif="$file_root.gif"

palette="/tmp/palette.png"
filters="fps=15,scale=320:-1:flags=lanczos"

ffmpeg -i $input_file -vf "$filters,palettegen" -y $palette
ffmpeg -i $input_file -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse" -y $filename_gif

#gifsicle -O1 $filename_gif -o $filename_gif_opt
