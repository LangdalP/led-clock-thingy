#! /usr/bin/env bash

#input_file=$1
#file_root="${input_file%%.*}"

# find . -maxdepth 3 -iname "*.jpeg" | xargs -L1 -I "{}" convert -resize 720 "{}" "${+%%.*}_small.jpeg"

find . -maxdepth 3 -iname "*.jpeg" | while IFS= read -r pathname; do
    #base=$(basename "$pathname"); name=${base%.*}; ext=${base##*.}
    file_root=${pathname%.*}
    convert -resize 720 $pathname ${file_root}_small.jpeg
done


