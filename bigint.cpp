#include "bigint.h"
#include <cassert>
#include <iostream>
using namespace std;

namespace csis3700
{
    bigint::bigint(long long l)
    {
        if(l==0)
        {
            digits = new uint8_t[1];
            capacity = 1;
            used = 1;
            negative = false;
            
            digits[used-1] = 0;
        }
        else
        {
            if(l<0)
            {
                l = l * -1;
                negative = true;
            }
            
            else
                negative = false;
            
            digits = new uint8_t[20];
            capacity = 20;
            used = 0;
            
            while(l>0)
            {
                digits[used] = l%10;
                l = l/10;
                used++;
            }
            
        }
        
    }
    
    bigint::bigint(uint8_t d[], size_t ndigits, bool is_negative)
    {
        capacity = ndigits;
        digits = new uint8_t[capacity];
        used = ndigits;
        negative = is_negative;
        
        for(size_t i = 0; i < used; i++)
            digits[i] = d[i];
    }
    
    bigint::bigint(const bigint& other)
    {
        digits = new uint8_t[other.capacity];
        capacity = other.capacity;
        used = other.used;
        negative = other.negative;
        
        for(size_t i=0; i < other.used; i++)
            digits[i] = other.digits[i];
    }
    
    bigint::~bigint()
    {
        delete []digits;
    }
    
    size_t bigint::get_digit_count() const
    {
        return used;
    }
    
    uint8_t bigint::get_digit(size_t i) const
    {
        assert(i < used);
        return digits[i];
    }
    
    bool bigint::is_negative() const
    {
        return negative;
    }
    
    bigint bigint::negate() const
    {
        bigint b(digits, used, negative);
        bigint b1(digits, used, true);
        bigint b2(digits, used, false);
        
        if(b.is_negative()==true)
            return b2;
        else
            return b1;
    }
    
    bigint bigint::abs() const
    {
        bigint b(digits, used, negative);
        bigint b1(digits, used, false);
        
        if(b.is_negative()==true)
            return b1;
        else
            return b;
    }
    
    bool operator ==(const bigint& i1, const bigint& i2)
    {
        bigint b1(i1);
        bigint b2(i2);
        bool are_equal;
        size_t i;
        
        if(b1.is_negative() != b2.is_negative())
        {
            are_equal = false;
            return are_equal;
        }
        
        if(b1.get_digit_count() != b2.get_digit_count())
        {
            are_equal = false;
            return are_equal;
        }
        
        for(i=0; i<b1.get_digit_count(); i++)
        {
            if(b1.get_digit(i) != b2.get_digit(i))
            {
                are_equal = false;
                return are_equal;
            }
            else
                are_equal = true;
        }
        
        return are_equal;
        
    }
    
    bool operator <(const bigint& i1, const bigint& i2)
    {
        size_t i;
        
        if((i1.is_negative()==false) and (i2.is_negative()==true))
        {
            return false;
        }
        
        if((i1.is_negative()==true) and (i2.is_negative()==false))
        {
            return true;
        }
        
        if(i1.get_digit_count() > i2.get_digit_count())
        {
            return false;
        }
        
        if(i1.get_digit_count() < i2.get_digit_count())
        {
            return true;
        }
        
        for(i=i1.get_digit_count(); i>0; i--)
        {
            if(i1.is_negative()==false and i2.is_negative()==false)
            {
                if(i1.get_digit(i-1) > i2.get_digit(i-1))
                {
                    return false;
                }
                
                if(i1.get_digit(i-1) < i2.get_digit(i-1))
                {
                    return true;
                }

            }
            
            if(i1.is_negative()==true and i2.is_negative()==true)
            {
                if(i1.get_digit(i-1) > i2.get_digit(i-1))
                {
                    return true;
                }
                
                if(i1.get_digit(i-1) < i2.get_digit(i-1))
                {
                    return false;
                }

            }
        }
        
        return false;
    }
    
    void bigint::operator +=(const bigint& other)
    {
        size_t i;
        uint8_t* a;
        int carry = 0;
        size_t newcap = 0;
        
        if(!negative and other.negative)
        {
            (*this) -= other.negate();
        }
        
        if(negative and !other.negative)
        {
            negative = false;
            (*this) -= other;
            negative = !negative;
        }
        
        else
        {
            if(get_digit_count() > other.get_digit_count())
            newcap = get_digit_count() + 1;
            
            else
                newcap = other.get_digit_count() + 1;

            a = new uint8_t[newcap];

            for(i=0; i<newcap; i++)
            {
                a[i] = 0;
            }

            for(i=0; i<newcap; i++)
            {
                uint8_t i1d = 0;
                uint8_t i2d = 0;

                if(i<get_digit_count())
                    i1d = get_digit(i);

                if(i<other.get_digit_count())
                    i2d = other.get_digit(i);

                a[i] = ((i1d + i2d + carry) % 10);
                carry = ((i1d + i2d + carry) / 10);
            }

            delete[] digits;
            digits = a;

            if(a[newcap - 1] != 0)
            {
                used = newcap;
                capacity = newcap;
            }

            else
            {
                used = newcap - 1;
                capacity = newcap - 1;
            }
        }
    }
    
    bigint operator +(const bigint& i1, const bigint& i2)
    {
        bigint answer(0);
        answer += i1;       
        answer += i2;
        
        return answer;
    }
    
    void bigint::operator -=(const bigint& other)
    {
        size_t i;
        uint8_t* a;
        int carry = 0;
        size_t newcap = 0;
        
        if(!negative and other.negative)
        {
            (*this) += other.negate();
        }
        
        if(negative and !other.negative)
        {
            negative = false;
            (*this) += other;
            negative = !negative;
        }
        
        else
        {
            if(get_digit_count() > other.get_digit_count())
                newcap = get_digit_count();
            
            else
                newcap = other.get_digit_count();

            a = new uint8_t[newcap];

            for(i=0; i<newcap; i++)
            {
                a[i] = 0;
            }

            for(i=0; i<newcap; i++)
            {
                uint8_t i1d = 0;
                uint8_t i2d = 0;

                if(i<get_digit_count())
                    i1d = get_digit(i);

                if(i<other.get_digit_count())
                    i2d = other.get_digit(i);

                if(i1d<i2d)
                {
                    a[i] = i1d - i2d + carry + 10;
                    carry = -1;
                }

                else
                {
                    a[i] = i1d - i2d + carry;
                }
            }

            for(i=newcap; i > 0; i--)
            {
                if(a[i-1]==0)
                    newcap--;
            }

            delete[] digits;
            digits = a;
            used = newcap;
            capacity = newcap;
        }
    }
    
    bigint operator -(const bigint& i1, const bigint& i2)
    {
        bigint answer(0);
        answer += i1;       
        answer -= i2;
        
        return answer;
    }
    
    void bigint::operator *=(const bigint& other)
    {
        uint8_t* new_digits;
        size_t i;
        size_t idx;
        size_t newcap;
        int carry;

        if(other == 0)
        {
            delete[] digits;
            digits = new uint8_t[1];
            digits[0] = 0;
            capacity = 1;
            used = 1;
            negative = false;
        }
        
        if(negative == other.negative)
        {
            negative = false;
        }
        
        else
        {
            negative = true;
        }

        newcap = used + other.used;
        new_digits = new uint8_t[newcap];
        
        for(i = 0; i < newcap; i++)
        {
            new_digits[i] = 0;
        }

        for(i = 0; i < other.used; i++)
        {
            carry = 0;
            
            for(idx = 0; idx < used; idx++)
            {
                if(digits[idx] * other.digits[i] + carry > 9)
                {
                    new_digits[i + idx] += ((digits[idx] * other.digits[i] + carry) % 10);
                    carry = (digits[idx] * other.digits[i] + carry) / 10;
                }
                
                else
                {
                    new_digits[i + idx] += (digits[idx] * other.digits[i] + carry);
                    carry = 0;
                }
                
                if(new_digits[i + idx] > 9)
                {
                    new_digits[i + idx + 1] += (new_digits[i + idx] / 10);
                    new_digits[i + idx] = (new_digits[i + idx] % 10);
                }
            }
            
            new_digits[i + idx] += carry;
        }

        new_digits[newcap - 1] = carry;
        
        if(new_digits[newcap - 1] != 0)
        {
            used = newcap;
            capacity = newcap;
        }
        
        else
        {
            used = newcap - 1;
            capacity = newcap - 1;
        }
        
        delete[] digits;
        digits = new_digits;
        
    }
    
    bigint operator *(const bigint& i1, const bigint& i2)
    {
        bigint answer(0);
        answer += i1;
        answer *= i2;
        
        return answer;
    }
    
    void bigint::operator =(const bigint& other)
    {
        uint8_t* new_digits;
        
        if(this == &other)
            return;
        
        if(capacity != other.capacity)
        {
            new_digits = new uint8_t[other.capacity];
            delete[] digits;
            digits = new_digits;
            capacity = other.capacity;
        }
        
        used = other.used;
        negative = other.negative;
        
        for(size_t i = 0; i<other.used; i++)
            digits[i] = other.digits[i];
    }
    
    std::ostream& operator <<(std::ostream& out, const bigint& i)
    {
        /*for(size_t n= 0; n<i.get_digit_count(); n++)
            std::cout << (int)i.get_digit(n);*/
        
        if(i.is_negative()==false)
        {
            for(size_t n=i.get_digit_count(); n>0; n--)
                out << (int)i.get_digit(n-1);
        }
        
        else
        {
            out << "-";
            
            for(size_t n=i.get_digit_count(); n>0; n--)
                out << (int)i.get_digit(n-1);
        }
            

        
        return out;
    }
}

