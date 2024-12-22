#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
int romanValue(char c); // Declare the function before usage
int romanToDecimal(char roman[]);
void numberToWords(int num, char result[]);
long long performOperation(int num1, int num2, char operator);
void readInputAndProcess();

// Arrays for Roman numeral values
int romanValues[] = {1000, 500, 100, 50, 10, 5, 1};
char romanChars[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};

int main()
{
    // Read input, process it, and write output
    readInputAndProcess();
    return 0;
}

// Convert a Roman numeral string to its decimal equivalent
int romanToDecimal(char roman[])
{
    int total = 0;
    int i;
    int current, next;

    for (i = 0; roman[i] != '\0'; i++)
    {
        current = romanValue(roman[i]);
        next = romanValue(roman[i + 1]);

        if (current < next)
        {
            total -= current; // Subtract if current is less than next
        }
        else
        {
            total += current; // Otherwise, add
        }
    }

    return total;
}

// Map Roman characters to their decimal values
int romanValue(char c)
{
    // Loop through the romanChars array to find the corresponding value
    for (int i = 0; i < 7; i++)
    {
        if (c == romanChars[i])
        {
            return romanValues[i];
        }
    }

    // If character is not found, return 0
    return 0;
}

// Perform arithmetic operation based on the operator
long long performOperation(int num1, int num2, char operator)
{
    switch (operator)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return (long long)num1 * num2;
    default:
        return 0;
    }
}

// Convert a number to its word representation
void numberToWords(int num, char result[])
{
    const char *ones[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const char *tens[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const char *teen[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

    if (num == 0)
    {
        strcpy(result, "Zero");
        return;
    }

    char buffer[200] = ""; // Temporary buffer to store the result

    // Handle negative numbers
    if (num < 0)
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
    else if (num >= 1000)
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
    FILE *inputFile = fopen("Input.txt", "r");
    FILE *outputFile = fopen("Output.txt", "w");

    if (!inputFile || !outputFile)
    {
        printf("Error opening file.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), inputFile))
    {
        char roman1[50], roman2[50], operator;
        sscanf(line, "%s %c %s", roman1, &operator, roman2);

        int num1 = romanToDecimal(roman1);
        int num2 = romanToDecimal(roman2);
        long long result = performOperation(num1, num2, operator);

        char resultWords[1000] = "";
        numberToWords(result, resultWords);

        fprintf(outputFile, "%s\n", resultWords);
    }

    fclose(inputFile);
    fclose(outputFile);
}
