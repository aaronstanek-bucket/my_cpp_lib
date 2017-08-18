#ifndef __PSDMH_H_INCLUDED__
#define __PSDMH_H_INCLUDED__

#include <exception>
using namespace std;;

namespace psdmh_exceptions {

  class max_refcount: public exception {
    public:
      virtual const char* what() const throw() {
        return "A psdmh object exceeded the maximum reference count.";
      };
    };

  class udef_count: public exception {
    public:
      virtual const char* what() const throw() {
        return "The reference count for an undefined psdmh reference object was requested.";
      };
    };

  class udef_poi: public exception {
    public:
      virtual const char* what() const throw() {
        return "The pointer for an undefined psdmh reference object was requested.";
      };
    };

};

template <class T> class psdmh_object {
  public:
    unsigned short refcount;
    T value;
    psdmh_object() {
      refcount = 0;
    };
    void increment_refcount() {
      refcount = refcount+1;
      if (refcount>65000) {throw psdmh_exceptions::max_refcount();};
    };
    void decrement_refcount() {
      if (refcount<2) {
        delete this;
        return;
      };
      refcount = refcount-1;
    };
};

template <class T> class psdmh {
  private:
    psdmh_object <T> * ob;
  public:
    void remove_ref() {
      if (ob!=NULL) {
        ob->decrement_refcount();
        ob = NULL;
      };
    };
    void makeNew() {
      remove_ref();
      ob = new psdmh_object <T>;
      ob->increment_refcount();
    };
    void operator=(const psdmh <T> & source) {
      remove_ref();
      ob = source.ob;
      if (ob!=NULL) {
        ob->increment_refcount();
      };
    };
    bool isActive() {
      if (ob==NULL) {
        return false;
      };
      return true;
    };
    unsigned short getRefCount() {
      if (ob==NULL) {throw psdmh_exceptions::udef_count();};
      return ob->refcount;
    };
    T * getPointer() {
      if (ob==NULL) {throw psdmh_exceptions::udef_poi();};
      return &(ob->value);
    };
    psdmh <T> returnCopy() {
      psdmh <T> ou;
      if (ob==NULL) {return ou;};
      ou.makeNew();
      *(ou.getPointer()) = *(getPointer());
      return ou;
    };
    psdmh() {
      ob = NULL;
    };
    psdmh(const psdmh <T> & source) {
      ob = source.ob;
      if (ob!=NULL) {
        ob->increment_refcount();
      };
    };
    ~psdmh() {
      remove_ref();
    };
    bool operator==(const psdmh <T> & other) {
      if (ob==other.ob) {return true;};
      return false;
    };
    bool operator!=(const psdmh <T> & other) {
      if (ob!=other.ob) {return true;};
      return false;
    };
};


#endif
