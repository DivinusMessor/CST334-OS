#!/bin/bash
# Name: Yukio Rivera
# Date: March 8, 2022
# Title: Lab1 - task
# Description: This program computes the area of a rectangle and circle

# Questions:
# 1) What linux system are you using?
#       - I'm using CentOS 6.10
# 2) Did you experience any difficulties with this lab task?
#       - The hardest part about this lab was figuring out the while loop format.
#         I'm sure there is a better way to do than using 3 while loops but since
#         I was also learning the syntax I did what made sense to me at the time.


# Source code that was provided by professor that echos info 
echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! There are $numusers users logged on."
# Checks to see if I'm, Yukio, running file
if [ $user = "rive2817" ]
then
    echo "Now you can proceed!"
    response="Yes"
# Loop that gets user input, height and width, to calculate area of rectangle
    while [ $response != "No" ]
    do
        echo "Enter height of rectangle: "
        read height
        echo "Enter the width of the rectangle: "
        read width
        area=`expr $height \* $width`
        echo "The area of the rectangle is $area"
        echo "Would you like to repeat for another rectangle [Yes/No]?"
        read response
# If user said they do not want to calculate another rectangle area it will
# prompt user for radius to calculate area of circle
        while [ $response != "Yes" ]
        do
            response_c="Yes"
# If you says no to circle prompt then it will end the program
            while [ $response_c != "No" ]
            do

                echo "Enter the radius of the circle: "
                read r
                area=$(echo "3.14*$r*$r" | bc )
                echo "area of the circle is: " $area
                echo "Would you like to repeat for another circle [Ye/No]?"
                read response_c
            done
            exit 1
        done
    done
else
    echo "Check who logged in!"
    exit 1
fi