#!/bin/bash

delay=${1:-0.1}

tput clear
input=$(cat)

pos=""

line_num=0

while IFS= read -r line; do
    col_num=0
    while [ $col_num -lt ${#line} ]; do
        char="${line:$col_num:1}"
        pos="$pos$line_num $col_num $char\n"
        col_num=$((col_num + 1))
    done
    line_num=$((line_num + 1))
done <<< "$input"

shuffle=$(printf "$pos" | shuf)

printf "$shuffle" | while read -r line col char; do    
    tput cup "$line" "$col"
    printf "%s" "$char"
    sleep "$delay"
done

tput cup "$line_num" 0
