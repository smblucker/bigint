/* 
 * File:   bigint.h
 * Author: seanblucker
 *
 * Created on February 11, 2016, 2:19 PM
 */

#ifndef BIGINT_H
#define	BIGINT_H

#include <cstdlib>
#include <iostream>

namespace csis3700
{
    class bigint
    {
    public:
        //Constructors
        bigint(long long l);
        bigint(uint8_t d[], size_t ndigits, bool is_negative);
        bigint(const bigint& other);
        //Destructor
        ~bigint();
        //Constant member functions
        size_t get_digit_count() const;
        uint8_t get_digit(size_t i) const;
        bool is_negative() const;
        bigint negate() const;
        bigint abs() const;
        //Overloaded Operators
        void operator +=(const bigint& other);
        void operator -=(const bigint& other);
        void operator *=(const bigint& other);
        void operator =(const bigint& other);
    private:
        uint8_t* digits;        //pointer to base of dynamically allocated array
        size_t capacity;        //number of digits allocated in digits array
        size_t used;            //number of digits actually being used
        bool negative;          //true if this number is negative; false otherwise
    };
    
    bool operator ==(const bigint& i1, const bigint& i2);
    bool operator <(const bigint& i1, const bigint& i2);
    bigint operator +(const bigint& i1, const bigint& i2);
    bigint operator -(const bigint& i1, const bigint& i2);
    bigint operator *(const bigint& i1, const bigint& i2);
    std::ostream& operator <<(std::ostream& out, const bigint& i);
}



#endif	/* BIGINT_H */

