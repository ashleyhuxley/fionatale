#include <exception>
 
using namespace std;
 
class ReturnException: public exception
{
  virtual const char* what() const throw()
  {
    return "User exited";
  }
};