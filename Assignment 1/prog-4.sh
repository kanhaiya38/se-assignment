#!/bin/bash

# 4. to find the area and circumference of a circle.

PI=3.14

echo "Enter radius of the circle"
read r 

echo "Area: $(bc <<< "$PI * $r * $r")"
echo "Circumference: $(bc <<< "2 * $PI * $r")"
