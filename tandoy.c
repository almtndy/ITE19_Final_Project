#include <stdio.h>  // Standard I/O library for input and output functions
#include <stdlib.h> // Standard library for general utilities like memory allocation, program control
#include <string.h> // Library for string handling functions like strlen, strcpy, etc.

// Function Prototypes
int romanValue(char c);                                        // Function to get the decimal value of a Roman numeral character
int romanToDecimal(char roman[]);                              // Function to convert a Roman numeral string to its decimal equivalent
void numberToWords(int num, char result[]);                    // Function to convert a number to its word representation
long long performOperation(int num1, int num2, char operator); // Function to perform arithmetic operations
void readInputAndProcess();                                    // Function to read input, process data, and write results

// Arrays for Roman numeral values and corresponding characters
int romanValues[] = {1000, 500, 100, 50, 10, 5, 1};      // Decimal values of Roman numerals
char romanChars[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'}; // Roman numeral characters

int main()
{
    // Start the program by reading input and processing it
    readInputAndProcess();
    return 0;
}

// Convert a Roman numeral string to its decimal equivalent
int romanToDecimal(char roman[])
{
    int total = 0;     // Initialize total to store the decimal result
    int i;             // Loop counter
    int current, next; // Variables to store the current and next Roman numeral values

    // Loop through each character in the Roman numeral string
    for (i = 0; roman[i] != '\0'; i++)
    {
        current = romanValue(roman[i]);  // Get the decimal value of the current character
        next = romanValue(roman[i + 1]); // Get the decimal value of the next character

        // Subtract if the current value is less than the next; otherwise, add
        if (current < next)
        {
            total -= current;
        }
        else
        {
            total += current;
        }
    }

    return total; // Return the total decimal value
}

// Map Roman numeral characters to their decimal values
int romanValue(char c)
{
    // Loop through the romanChars array to find the matching character
    for (int i = 0; i < 7; i++)
    {
        if (c == romanChars[i])
        {
            return romanValues[i]; // Return the corresponding decimal value
        }
    }

    return 0; // Return 0 if the character is not a valid Roman numeral
}

// Perform arithmetic operation based on the given operator
long long performOperation(int num1, int num2, char operator)
{
    switch (operator) // Determine the operation based on the operator
    {
    case '+': // Addition
        return num1 + num2;
    case '-': // Subtraction
        return num1 - num2;
    case '*': // Multiplication
        return (long long)num1 * num2;
    default: // Invalid operator
        return 0;
    }
}

// Convert a number to its word representation
void numberToWords(int num, char result[])
{
    // Arrays for word representations of numbers
    const char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *teen[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

    if (num == 0) // Handle the special case for 0
    {
        strcpy(result, "Zero");
        return;
    }

    char buffer[200] = ""; // Temporary buffer to store the result

    if (num < 0) // Handle negative numbers
    {
        strcat(buffer, "Negative ");
        num = -num; // Convert to positive for processing
    }

    // Convert millions place (if applicable)
    if (num >= 1000000)
    {
        sprintf(buffer + strlen(buffer), "%s Million ", ones[num / 1000000]);
        num %= 1000000;
    }

    // Convert hundreds of thousands
    if (num >= 100000)
    {
        sprintf(buffer + strlen(buffer), "%s Hundred ", ones[num / 100000]);
        num %= 100000;
    }

    // Convert tens of thousands
    if (num >= 20000)
    {
        sprintf(buffer + strlen(buffer), "%s Thousand ", tens[num / 10000]);
        num %= 10000;
    }

    // Convert teens in the thousands place
    if (num >= 10000)
    {
        sprintf(buffer + strlen(buffer), "%s Thousand ", teen[num / 1000 - 10]);
        num %= 1000;
    }
    else if (num >= 1000) // Convert thousands
    {
        sprintf(buffer + strlen(buffer), "%s Thousand ", ones[num / 1000]);
        num %= 1000;
    }

    // Convert hundreds
    if (num >= 100)
    {
        sprintf(buffer + strlen(buffer), "%s Hundred ", ones[num / 100]);
        num %= 100;
    }

    // Convert tens place
    if (num >= 20)
    {
        sprintf(buffer + strlen(buffer), "%s ", tens[num / 10]);
        num %= 10;
    }

    // Convert teen numbers
    if (num >= 10)
    {
        sprintf(buffer + strlen(buffer), "%s ", teen[num - 10]);
        num = 0;
    }

    // Convert ones place
    if (num > 0)
    {
        sprintf(buffer + strlen(buffer), "%s", ones[num]);
    }

    strcpy(result, buffer); // Copy the result to the output string
}

// Read input from a file, process each line, and write the results to the output file
void readInputAndProcess()
{
    // Open the input file for reading
    FILE *inputFile = fopen("Input.txt", "r");
    // Open the output file for writing
    FILE *outputFile = fopen("Output.txt", "w");

    if (!inputFile || !outputFile) // Check if files opened successfully
    {
        printf("Error opening file.\n");
        return;
    }

    char line[100];                              // Buffer to store each line of input
    while (fgets(line, sizeof(line), inputFile)) // Read each line from the input file
    {
        char roman1[50], roman2[50], operator;               // Variables to store parsed data
        sscanf(line, "%s %c %s", roman1, &operator, roman2); // Parse the line into Roman numerals and operator

        int num1 = romanToDecimal(roman1);                         // Convert the first Roman numeral to decimal
        int num2 = romanToDecimal(roman2);                         // Convert the second Roman numeral to decimal
        long long result = performOperation(num1, num2, operator); // Perform the arithmetic operation

        char resultWords[1000] = "";        // Buffer to store the result in words
        numberToWords(result, resultWords); // Convert the result to words

        fprintf(outputFile, "%s\n", resultWords); // Write the result in words to the output file
    }

    fclose(inputFile);  // Close the input file
    fclose(outputFile); // Close the output file
}