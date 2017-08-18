#ifndef __PSDMH_QUEUE_H_INCLUDED__
#define __PSDMH_QUEUE_H_INCLUDED__

#include <exception>
#include "psdmh.h"
using namespace std;

namespace psdmh_queue {

  class null_psdmh: public exception {
    public:
      virtual const char* what() const throw() {
        return "An inactive psdmh object was added to a psdmh queue.";
      };
    };

  template <class T> element {
    public:
      T value;
      psdmh < element<T> > next;
  };

  template <class T> queue {
    private:
      unsigned long long count;
      psdmh < element<T> > first;
      psdmh < element<T> > last;
    public:
      queue() {
        count = 0;
      };
      unsigned long long size() {
        return count;
      };
      void push_back(psdmh < element<T> > pb) {
        if (pb.isActive()==false) {throw null_psdmh();};
        if (count==0) {
          first = pb;
          last = pb;
        }
        else {
          last.getPointer().next = pb;
          last = pb;
        };
        count = count+1;
      };
      psdmh < element<T> > pop_front() {
        if (count>1) {
          //count>1
          psdmh < element<T> > ou = first;
          first = first.getPointer()->next;
          ou.getPointer()->next.remove_ref();
          count = count-1;
          return ou;
        }
        else if (count==1) {
          //count==1
          psdmh < element<T> > ou = first;
          first.remove_ref();
          last.remove_ref();
          ou.getPointer()->next.remove_ref();
          count = 0;
          return ou;
        }
        else {
          //count==0
          psdmh < element<T> > ou;
          return ou;
        };
      };
      void clearQueue() {
        while (count!=0) {pop_front();};
      };
      ~queue() {
        clearQueue();
      };
  };

};

#endif
