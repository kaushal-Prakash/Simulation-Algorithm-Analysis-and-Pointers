/*
 * File:   main.c
 * Author: Mohith B P
 */

 #define _CRT_SECURE_NO_WARNINGS
 
 #include <stdio.h>
 #include <stdlib.h>
 
 #define MAX_LENGTH 100
 
 /*
  * Walking the Walk Programming Assignment
  */
 int main(int argc, char** argv)
 {
	 // IMPORTANT: Only add code in the section
	 // indicated below. The code I've provided
	 // makes your solution work with the 
	 // automated grader on Coursera
	 char input[MAX_LENGTH];
	 fgets(input, MAX_LENGTH, stdin);
	 while (input[0] != 'q')
	 {
		 int n = atoi(input);
 
		 // Add your code between this comment
		 // and the comment below. You can of
		 // course add more space between the
		 // comments as needed
 
		 // Step 1: Allocate memory
		 int* array = (int*)malloc(n * sizeof(int));
		 if (array == NULL)
		 {
			 return 1; // Allocation failed
		 }
 
		 // Step 2: Set values using pointer
		 int* ptr = array;
		 for (int i = 0; i < n; i++)
		 {
			 *(ptr + i) = i;
		 }
 
		 // Step 3: Print values using pointer
		 for (int i = 0; i < n; i++)
		 {
			 printf("%d ", *(ptr + i));
		 }
 
		 // Step 4: Calculate sum using pointer
		 int sum = 0;
		 for (int i = 0; i < n; i++)
		 {
			 sum += *(ptr + i);
		 }
		 printf("%d\n", sum);
 
		 // Step 5: Free memory and null pointer
		 free(array);
		 array = NULL;
 
		 // Don't add or modify any code below
		 // this comment
		 fgets(input, MAX_LENGTH, stdin);
	 }
 
	 return 0;
 }
 