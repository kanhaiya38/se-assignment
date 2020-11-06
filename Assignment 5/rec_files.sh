#!/bin/bash

find ~/Downloads -mtime -20 -ls | sort -k 5 -rn | head -11 
