#!/bin/bash

IMG_FOLDER="img/"
IMG_FOLDER_LENGTH=${#IMG_FOLDER}
OUT_FOLDER="out_img/"

for entry in "$search_dir"img/*
do
    file_name_with_extension="${entry:($IMG_FOLDER_LENGTH)}"
    file_name=${file_name_with_extension::(-4)}
    file_extension="${entry:(-3)}"

    histogram_path="$OUT_FOLDER/$file_name._histogram.$file_extension"
    sobel_path="$OUT_FOLDER/$file_name.sobel.$file_extension"
    equalize_path="$OUT_FOLDER/$file_name.equalize.$file_extension"
    histogram_equalized_path="$OUT_FOLDER/$file_name._histogram.equalize.$file_extension"
    rif1dh_path="$OUT_FOLDER/$file_name.fir1dh.$file_extension"
    rif2dx_path="$OUT_FOLDER/$file_name.fir2dx.$file_extension"
    rif2dy_path="$OUT_FOLDER/$file_name.fir2dy.$file_extension"

    if [ $file_extension = "bmp" ]
    then
        echo "> $entry -> BMP"
        ./imagetools-cli.out -b $entry --histogram c $histogram_path --sobel -s $sobel_path
        ./imagetools-cli.out -b $entry --equalize-hist -s $equalize_path --histogram c $histogram_equalized_path
        ./imagetools-cli.out -b $entry --fir1d-h 4 -s $rif1dh_path
        ./imagetools-cli.out -b $entry --fir2d-x -s $rif2dx_path
        ./imagetools-cli.out -b $entry --fir2d-y -s $rif2dy_path
    elif [ $file_extension = "pgm" ]
    then
        echo "> $entry -> PGM"
        ./imagetools-cli.out -p $entry --histogram c $histogram_path --sobel -s $sobel_path
        ./imagetools-cli.out -p $entry --equalize-hist -s $equalize_path --histogram c $histogram_equalized_path
        ./imagetools-cli.out -p $entry --fir1d-h 4 -s $rif1dh_path
        ./imagetools-cli.out -p $entry --fir2d-x -s $rif2dx_path
        ./imagetools-cli.out -p $entry --fir2d-y -s $rif2dy_path
    else
        echo "> $entry is not an image readable by imagtools"
    fi
done