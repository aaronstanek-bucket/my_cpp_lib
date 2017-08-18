#ifndef __OBJECT_BUILDER_H_INCLUDED__
#define __OBJECT_BUILDER_H_INCLUDED__

#include "string"
#include "psdmh.h"
#include "file_io.h"
using namespace std;

namespace object_builder {

  class notactive: public exception {
    public:
      virtual const char* what() const throw() {
        return "A builder object is being used without being activated first.";
      };
    };

  class invalid_code: public exception {
    public:
      virtual const char* what() const throw() {
        return "A writer object was sent an invalid code.";
      };
    };

  class builder {
    private:
      psdmh <string> indata;
      string * poi;
    public:
      unsigned long long indata_size;
      unsigned long long spot;
      string value;
      char code;
      void reset() {
        poi = NULL;
        indata_size = 0;
        spot = 0;
        value = "";
        code = '?';
      };
      builder() {
        reset();
      };
      void activate(psdmh <string> ac) {
        indata = ac;
        reset();
        poi = indata.getPointer();
        indata_size = poi->size();
      };
      builder(const psdmh <string> ac) {
        activate(ac);
      };
      void getNext() {
        if (poi==NULL) {throw notactive();};
        value = "";
        code = '?';
        char p;
        while (true) {
          if (spot>=indata_size) {
            value = "";
            code = 'e';
            return;
          };
          p = poi->at(spot);
          spot = spot+1;
          if ((p>=16) && (p<=31)) {
            code = p;
            return;
          }
          else {
            value.push_back(p);
          };
        };
      };
  };

  class writer {
    private:
      psdmh <string> outdata;
      string * poi;
    public:
      void reset() {
        outdata.makeNew();
        poi = outdata.getPointer();
      };
      writer() {
        reset();
      };
      void addCode(char c) {
        if ((c>31) || (c<16)) {throw invalid_code();};
        poi->push_back(c);
      };
      void addString(string & s, char c) {
        poi->append(s);
        addCode(c);
      };
      psdmh <string> getOutdata() {
        return outdata;
      };
  };

  psdmh <builder> builder_from_file(const char * filename) {
    psdmh <string> b;
    b = file_io::read(filename);
    psdmh <builder> ou;
    ou.getPointer()->activate(b);
    return ou;
  };

  void writer_to_file(const char * filename, writer & w) {
    psdmh <string> ou;
    ou = w.getOutdata();
    file_io::write(filename,ou);
  };

  void writer_to_file(const char * filename, psdmh <writer> w) {
    psdmh <string> ou;
    ou = w.getPointer()->getOutdata();
    file_io::write(filename,ou);
  };

};

#endif
