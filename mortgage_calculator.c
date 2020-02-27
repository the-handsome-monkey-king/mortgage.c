/*
 * mortgage_calculator.c
 *
 * Find the given periodical payments for a mortgage
 * over a set of number of years with its principal,
 * length of period, and interest rate.
 *
 * author: Ryan Morehouse
 * license: MIT
 *
 * The code to read user input is taken almost line-for-line
 * from an online article written by Felix Palmen, written
 * June 8, 2017, which can be found at 
 * http://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html,
 * entitled "A Beginner's Guide away from scanf()"
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

long get_long(char *prompt)
{
  long l;
  char buf[1024];
  int success;

  do
  {
    printf("%s", prompt);
    if(!fgets(buf, 1024, stdin))
    {
      // failed to read input
      return -1;
    }

    char *endptr;

    errno = 0; // reset error number
    l = strtol(buf, &endptr, 10);
    if(errno == ERANGE)
    {
      printf("Sorry, input is too small or too large.\n");
      success = 0;
    }
    else if (endptr == buf)
    {
      // no character was read
      success = 0;
    }
    else if (*endptr && *endptr != '\n')
    {
      // *endptr is neither end of string nor new line
      // therefore we didn't convert whole, entire input
      success = 0;
    }
    else if(l < 1)
    {
      // input shouldn't be 0 or negative in this program
      success = 0;
    }
    else
    {
      success = 1;
    }
  } while (!success); // repeat until we get valid number
  return l;
}

double get_double(char *prompt)
{
  double d;
  char buf[1024];
  int success;

  do
  {
    printf("%s", prompt);
    if(!fgets(buf, 1024, stdin))
    {
      // failed to read input
      return -1;
    }

    char *endptr;

    errno = 0; // reset error number
    d = strtod(buf, &endptr);
    if(errno == ERANGE)
    {
      printf("Sorry, input is too small or too large.\n");
      success = 0;
    }
    else if (endptr == buf)
    {
      // no character was read
      success = 0;
    }
    else if (*endptr && *endptr != '\n')
    {
      // *endptr is neither end of string nor new line
      // therefore we didn't convert whole, entire input
      success = 0;
    }
    else if (d <= 0)
    {
      // input shouldn't be negative in this program
      success = 0;
    }
    else
    {
      success = 1;
    }
  } while (!success); // repeat until we get valid number

  return d;
}

long get_period()
{
  long l;
  char buf[1024];
  int success;

  do
  {
    printf("Please select one of these three payment periods:\n");
    printf("1. monthly (12 per annum)\n");
    printf("2. weekly (48 per annum)\n");
    printf("3. daily (365 per annum)\n");
    printf("> ");
    if(!fgets(buf, 1024, stdin))
    {
      // failed to read input
      return 1;
    }

    char *endptr;

    errno = 0; // reset error number
    l = strtol(buf, &endptr, 10);
    if(errno == ERANGE)
    {
      printf("Sorry, input is too small or too large.\n");
      success = 0;
    }
    else if (endptr == buf)
    {
      // no character was read
      success = 0;
    }
    else if (*endptr && *endptr != '\n')
    {
      // *endptr is neither end of string nor new line
      // therefore we didn't convert whole, entire input
      success = 0;
    }
    else if (l != 1 && l != 2 && l != 3)
    {
      // l is not one of the selectable options
      success = 0;
    }
    else
    {
      success = 1;
    }
  } while (!success); // repeat until we get valid number

  if (l == 1)
  {
    return 12;  // monthly
  }
  else if (l == 2)
  {
    return 48;  // weekly
  }
  // else
  return 365; // daily
}

int main()
{
  // prompts
  char *principal_msg = "Please enter the principal (no decimal): ";
  char *years_msg = "Please enter the years for the mortgage: ";
  char *interest_msg = "Please enter the interest as a decimal";
  char *interest_msg2 = "(for example, enter 5% as 0.05): ";

  // mortgage variables
  long principal = get_long(principal_msg);
  long years = get_long(years_msg);
  printf("%s\n", interest_msg);
  double interest = get_double(interest_msg2);
  long period = get_period();

  if (principal == -1 || years == -1 || interest == -1 || period == -1)
  {
    // failed to read input somewhere
    return 1;
  }

  // print mortgage variables
  printf("principal: %d\n", principal);
  printf("years: %d\n", years);
  printf("interest: %lf\n", interest);
  printf("period of payments (per annum): %d\n", period);

  double total_payment = principal * pow(
    (1.0 + (interest / period)), (double)(years * period));

  double periodic_payment = total_payment / period;

  // round these figures
  printf("Final Loan Worth: %.2lf\n", total_payment);
  printf("Periodic Payment: %.2lf\n", periodic_payment);
  return 0;
}
