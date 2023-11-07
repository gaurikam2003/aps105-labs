/*
 * This program prints: C uses escape sequences for a variety of purposes.
 *                      Some common ones are:
 *                           to print ", use \"
 *                           to print \, use \\
 *                           to jump to a new line, use \n
 */
#include <stdio.h>
int main() {
  printf(
      "C uses escape sequences for a variety of purposes.\nSome common ones are:"
      "\n     to print \", use \\\""
      "\n     to print \\, use \\\\"
      "\n     to jump to a new line, use \\n");
  return 0;
}