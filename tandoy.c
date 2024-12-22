#include <stdio.h>  // Include the standard input/output library for functions like printf and scanf
#include <stdlib.h> // Include the standard library for functions like malloc, free, etc.
#include <string.h> // Include the string library for string manipulation functions like strcpy, strlen, etc.

// Function Prototypes
int romanValue(char c);                                        // function to convert Roman numeral characters to their decimal values
int romanToDecimal(char roman[]);                              // function to convert a Roman numeral string to its decimal value
void convertToWords(long long num, char result[]);             // function to convert a number to words
long long performOperation(int num1, int num2, char operator); // function to perform arithmetic operations
void readInputAndProcess();                                    // function to read input, process data, and output results

// Arrays for Roman numeral values
int romanValues[] = {1000, 500, 100, 50, 10, 5, 1};      // Array to store the decimal values of Roman numerals
char romanChars[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'}; // Array to store the Roman numeral characters

// Arrays for words representation of numbers
char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
char *hundreds[] = {"", "One Hundred", "Two Hundred", "Three Hundred", "Four Hundred", "Five Hundred", "Six Hundred", "Seven Hundred", "Eight Hundred", "Nine Hundred"};
char *thousands[] = {"", "Thousand", "Million", "Billion"}; // Arrays for powers of thousand (Thousand, Million)

// Main function that runs the program
int main()
{
    // Read input, process it, and write output
    readInputAndProcess(); // Calls the function to process the input file and generate the output
    return 0;              // Return 0 to indicate successful execution
}

// Convert a Roman numeral string to its decimal equivalent
int romanToDecimal(char roman[])
{
    int total = 0; // Variable to store the final decimal result
    int i;
    int current, next; // Variables to store the value of current and next Roman characters

    for (i = 0; roman[i] != '\0'; i++) // Iterate through each character in the Roman numeral string
    {
        current = romanValue(roman[i]);  // Get the decimal value of the current Roman character
        next = romanValue(roman[i + 1]); // Get the decimal value of the next Roman character

        if (current < next) // If the current character represents a smaller value than the next (IV for 4)
        {
            total -= current; // Subtract the current value from the total
        }
        else
        {
            total += current; // Otherwise, add the current value to the total
        }
    }

    return total; // Return the decimal value of the Roman numeral
}

// Map Roman characters to their decimal values
int romanValue(char c)
{
    for (int i = 0; i < 7; i++) // Iterate through the romanChars array
    {
        if (c == romanChars[i]) // If the character matches, return the corresponding value from romanValues
        {
            return romanValues[i];
        }
    }

    return 0; // Return 0 if the character is not a valid Roman numeral
}

// Perform arithmetic operation based on the operator
long long performOperation(int num1, int num2, char operator)
{
    switch (operator) // Check which operator is provided ('+', '-', '*')
    {
    case '+':
        return num1 + num2; // Return the sum of the two numbers
    case '-':
        return num1 - num2; // Return the difference of the two numbers
    case '*':
        return (long long)num1 * num2; // Return the product of the two numbers
    default:
        return 0; // Return 0 if an invalid operator is provided
    }
}

// Convert a number to its word representation
void convertToWords(long long num, char result[])
{
    if (num < 0) // If the number is negative
    {
        strcat(result, "Negative "); // Append "Negative" to the result string
        num = -num;                  // Make the number positive for easier processing
    }

    int parts[4] = {0}; // Array to store groups of three digits (thousands, millions, etc.)
    int partIndex = 0;  // Index to keep track of the current part of the number

    while (num > 0) // Split the number into parts of 3 digits
    {
        parts[partIndex++] = num % 1000; // Store the last three digits in the current part
        num /= 1000;                     // Remove the last three digits
    }

    for (int i = partIndex - 1; i >= 0; i--) // Process each part from the most significant to the least significant
    {
        int current = parts[i]; // Get the current part

        if (current >= 100) // If the part is in the hundreds place
        {
            strcat(result, hundreds[current / 100]); // Append the word for the hundreds place
            strcat(result, " ");                     // Add a space after the word
            current %= 100;                          // Remove the hundreds place
        }

        if (current >= 20) // If the part is in the tens place
        {
            strcat(result, tens[current / 10]); // Append the word for the tens place
            strcat(result, " ");                // Add a space
            current %= 10;                      // Remove the tens place
        }

        if (current > 0) // If the part is in the ones place
        {
            strcat(result, ones[current]); // Append the word for the ones place
            strcat(result, " ");           // Add a space
        }

        if (parts[i] > 0 && i > 0) // If the part is not zero and it's not the least significant part
        {
            strcat(result, thousands[i]); // Append the word for the place (Thousand)
            strcat(result, " ");          // Add a space
        }
    }
}

// Read input from a file, process each line, and write the results to the output file
void readInputAndProcess()
{
    FILE *inputFile = fopen("Input.txt", "r");   // Open the input file for reading
    FILE *outputFile = fopen("Output.txt", "w"); // Open the output file for writing

    if (!inputFile || !outputFile) // If either file cannot be opened
    {
        printf("Error opening file.\n"); // Print an error message
        return;                          // Exit the function
    }

    char line[100];                              // Buffer to hold each line of input
    while (fgets(line, sizeof(line), inputFile)) // Read each line from the input file
    {
        char roman1[50], roman2[50], operator;               // Variables to store the two Roman numerals and the operator
        sscanf(line, "%s %c %s", roman1, &operator, roman2); // Parse the line into the Roman numerals and operator

        int num1 = romanToDecimal(roman1);                         // Convert the first Roman numeral to decimal
        int num2 = romanToDecimal(roman2);                         // Convert the second Roman numeral to decimal
        long long result = performOperation(num1, num2, operator); // Perform the arithmetic operation

        char resultWords[1000] = "";         // Buffer to store the result in words
        convertToWords(result, resultWords); // Convert the result to words

        fprintf(outputFile, "%s\n", resultWords); // Write the result in words to the output file
    }

    fclose(inputFile);  // Close the input file
    fclose(outputFile); // Close the output file
}
