#include "varexp.h"
#include <vector>
#include <cstring>

/*

  (c) 2003 squell ^ zero functionality!
  see the file 'COPYING' for license conditions

  an adapted version of a smaller, simpler wildcard match routine to
  support a primitive form of pattern matching

  the base C version included at the end, if you're interested

*/

bool varexp::match(const char* mask, const char* test)
{
    std::vector<const char*> _vars = vars;     // backup previous values
    std::vector<int>         _varl = varl;     //
    bool flag = false;

    char m, c;
    do {
        switch( c=*test++, m=*mask++ ) {
        case '[':
            if( in_set(c,mask,test) ) return 1;
        default :
            if( m != c ) return 0;
        case '?':
            flag = false;
            break;

        case '*':
            if(!flag) {
                vars.push_back(test-1);   // add entry for new variable
                varl.push_back(0);        // + length count
                flag = true;
            }
            if( match(mask,test-1) ) return 1;
            --mask, ++varl.back();
        }
    } while(c);

    if(m) {
       vars = _vars;
       varl = _varl;
       return 0;
    }
    return 1;
}

 /*
     auxilliary code to detect character ranges in expressions
 */

int varexp::in_set(char c, const char* set, const char* test)
{
    int  inv = 0, t = 0;
    char prev, m;
    if(*set=='!' || *set=='^') {
        inv = 1;                       // match chars NOT in set
        ++set;
    }
    for(prev = 0; (m = *set++); prev = m)
        if(m=='-' && prev && *set!='\0' && *set!=']') {
            t |= (c >= prev) && (c <= *set);
        } else {
            if(m==']')
                return (t^inv) && match(set, test);
            t |= (m==c);
        }
    return 0;
}

/*

 C version without pattern matching (more concise):

int match(const char *mask, const char *test)
{
    char c, m;
    do {
        switch( c=*test++, m=*mask++ ) {
        default :
            if( m != c ) return 0;
        case '?':
            break;
        case '*':
            if( match(mask,test-1) ) return 1;
            --mask;
        }
    } while(c);
    return !m;
}

*/
