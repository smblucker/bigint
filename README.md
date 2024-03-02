## Program Problem

Integer primitive integer-like types are inadequate for some applications--ie.
cryptography and combinatorics.

|      **Type**       |   **SizeOf(Type)**  |          **Max Value**           |
|:--------------------|:--------------------|:---------------------------------|
| unint8_t            |          1          |                               255|
| unsigned short      |          2          |                            65,535|
| unsigned integer    |          4          |                     4,294,967,295|
| unsigned long long  |          8          |        18,446,744,073,709,551,615|     

While it seems like a 'long long' would be enough for most applications,
cryptographic applications and the like typically use values that are hundreds
of digits long.

## Program Solution

Create a 'bigint' data type in C++ that will support an arbitrary number of
digits (limited only by computer memory constraints).

  * Achieved through placing digits of number into dynamically allocated array
  * Supported mathematical operations include addition, subtraction, division,
  and multiplication
  * Supported comparison operations include equality, inequality, and
  determination of sign
  * Other operations include negating a value and conversion to absolute values

## Instructional Objectives

The specific educational aims of this project include, but should not be limited
to, the following:

  * Provide introduction to dynamic allocation
  * Reinforce 'test first' class design and development
  * Reinforce proper object-oriented design and development of C++ classes 
