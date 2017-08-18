#ifndef __FILE_IO_H_INCLUDED__
#define __FILE_IO_H_INCLUDED__

#include <fstream>
#include <string>
#include "psdmh.h"
using namespace std;

namespace file_io {

  psdmh <string> read(const char * filename) {
    //setup dynamic
    psdmh <string> ou;
    ou.makeNew();
    string * oup = ou.getPointer();
    //setup local
    unsigned long long bufferSize = 16*1024;
    char buffer[bufferSize];
    fstream infile;
    infile.open(filename, std::fstream::in | std::fstream::binary);
    infile.seekg(0,ios::end);
    unsigned long long fileSize = infile.tellg();
    unsigned long long getSize;
    unsigned long long i = 0; //marks spot in file
    unsigned long long j = 0; //marks spot in indata
    unsigned long long k; //temporary, marks spot in buffer
    oup->resize(fileSize);
    //read file
    while (i<fileSize) {
      getSize = fileSize-i;
      if (getSize>bufferSize) {getSize = bufferSize;};
      infile.seekg(i,ios::beg);
      infile.read(buffer,getSize);
      for (k=0;k<getSize;k++) {
        oup->at(j) = buffer[k];
        j = j+1;
      };
      i = i+bufferSize;
    };
    infile.close();
    return ou;
  };

  void write(const char * filename, psdmh <string> outdata) {
    //setup dynamic
    string * osp = outdata.getPointer();
    //setup local
    const unsigned long long bufferSize = 16*1024;
    char buffer[bufferSize];
    fstream outfile;
    outfile.open(filename, std::fstream::out | std::fstream::trunc | std::fstream::binary);
    unsigned long long dataSize = osp->size();
    unsigned long long getSize;
    unsigned long long i = 0; //marks spot in file
    unsigned long long j = 0; //marks spot in outdata
    unsigned long long k; //temporary, marks spot in buffer
    //write file
    while (i<dataSize) {
      getSize = dataSize-i;
      if (getSize>bufferSize) {getSize = bufferSize;};
      for (k=0;k<getSize;k++) {
        buffer[k] = osp->at(j);
        j = j+1;
      };
      outfile.seekp(i,ios::beg);
      outfile.write(buffer,getSize);
      i = i+bufferSize;
    };
    outfile.close();
  };
};

#endif
