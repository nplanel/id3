/*

  set_tag::echo applicative class

  (c) 2005 squell ^ zero functionality!
  see the file 'COPYING' for license conditions

  Usage:

  The set_tag::echo class doesn't set anything, but reports back info.

*/

#ifndef __ZF_SETQUERY
#define __ZF_SETQUERY

#include "set_base.h"
#include "charconv.h"

namespace set_tag {

class echo : public single_tag {
    const char* fmt;
public:
    echo(bool t=true) : single_tag(t) { }

    void format(const char* s)
    { fmt=s; }

    virtual bool vmodify(const char*, const subst&) const;
    virtual void log(const cvtstring&) const;

  // standard set - dummies

    echo& set(ID3field, const char*)
    { return *this; }

    echo& clear()
    { return *this; }
};

}

#endif
