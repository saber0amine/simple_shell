#include "main.h"
/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * functionWich contains a copy of the string given as a parameter.
 *
 * @str: string input
 *
 * Return: pointer
 */
char *_strdup(const char *str)
{
        int i, len = 0;
        char *result;

        if (str == NULL)
                return (NULL);

        while (str[len] != '\0')
                len++;

        result = (char *)malloc((len + 1) * sizeof(char));

        if (result == NULL)
                return (NULL);

        for (i = 0; i <= len; i++)
                result[i] = str[i];

        return (result);
}


/**
 * Cnum - check if a string is a number
 * @status: string to be checked
 * Return: void
 */
int Cnum(const char *status)
{
        if (status == NULL || status[0] == '\0')
                return (0);
        while (*status)
        {
                if (!Cdigit(*status))
                        return (0);
                status++;
        }
        return (1);
}


/**
 * Cdigit - check if charachter is number
 * @c: charachter
 * Return: 1 if its a digit 0 otherwise
 */
int Cdigit(int c)
{
        return (c >= '0' && c <= '9');
}