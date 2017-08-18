#ifndef __SIMPLE_RNG_H_INCLUDED__
#define __SIMPLE_RNG_H_INCLUDED__

#include <ctime>
#include <cstdlib>
using namespace std;

class simple_rng {
  private:
    char one_byte_of_memory;
  public:
    simple_rng() {
      srand(time(NULL));
    };
    bool r1bit() {
      if ((rand()%2)==1) {return true;};
      return false;
    };
    unsigned char r8bit() {
      return rand()%256;
    };
    unsigned short r16bit() {
      unsigned short ou = (((unsigned short)rand())%((unsigned short)256));
      ou = ou*((unsigned short)256) + (((unsigned short)rand())%((unsigned short)256));
      return ou;
    };
    unsigned long r32bit() {
      unsigned long ou = (((unsigned long)rand())%((unsigned long)256));
      ou = ou*((unsigned long)256) + (((unsigned long)rand())%((unsigned long)256)); // 1
      ou = ou*((unsigned long)256) + (((unsigned long)rand())%((unsigned long)256)); // 2
      ou = ou*((unsigned long)256) + (((unsigned long)rand())%((unsigned long)256)); // 3
      return ou;
    };
    unsigned long long r64bit() {
      unsigned long long ou = (((unsigned long long)rand())%((unsigned long long)256));
      ou = ou*((unsigned long long)256) + (((unsigned long long)rand())%((unsigned long long)256)); // 1
      ou = ou*((unsigned long long)256) + (((unsigned long long)rand())%((unsigned long long)256)); // 2
      ou = ou*((unsigned long long)256) + (((unsigned long long)rand())%((unsigned long long)256)); // 3
      ou = ou*((unsigned long long)256) + (((unsigned long long)rand())%((unsigned long long)256)); // 4
      ou = ou*((unsigned long long)256) + (((unsigned long long)rand())%((unsigned long long)256)); // 5
      ou = ou*((unsigned long long)256) + (((unsigned long long)rand())%((unsigned long long)256)); // 6
      ou = ou*((unsigned long long)256) + (((unsigned long long)rand())%((unsigned long long)256)); // 7
      return ou;
    };
    unsigned long long r_in_range(unsigned long long cap) {
      return r64bit()%cap;
    };
};

simple_rng my_rng;

#endif
