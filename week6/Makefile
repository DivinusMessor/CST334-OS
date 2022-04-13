# Name: Yukio Rivera
# Date: 4/12/2022 
# Title: Lab 6 – Makefile  
# Description: Makefile for Lab6

threadsync: threadsync.o
	gcc -o threadsync threadsync.o -lpthread

threadsync.o: threadsync.c
	gcc -c -o threadsync.o threadsync.c -lpthread

lab6: lab6.o
	gcc -o lab6 lab6.o -lpthread

lab6.o: lab6.c
	gcc -c -o lab6.o lab6.c -lpthread