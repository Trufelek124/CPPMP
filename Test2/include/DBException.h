#ifndef DBEXCEPTION_H
#define DBEXCEPTION_H

#include <iostream>
#include <exception>

class DBException: public std::exception
{
    public:
      virtual const char* what() const throw()
      {
        return "Database error";
      };
      private:
};

#endif // DBEXCEPTION_H
