//*************************************************************************************************
//*************************************************************************************************
//* The MIT License (MIT)                                                                         *
//* Copyright (C) 2025 Ivan Matic, Rados Radoicic, and Dan Stefanica                              *
//*                                                                                               *
//* Permission is hereby granted, free of charge, to any person obtaining a copy of this          *
//* software and associated documentation files (the "Software"), to deal in the Software         *
//* without restriction, including without limitation the rights to use, copy, modify, merge,     *
//* publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons    *
//* to whom the Software is furnished to do so, subject to the following conditions:              *
//*                                                                                               *
//* The above copyright notice and this permission notice shall be included in all copies or      *
//* substantial portions of the Software.                                                         *
//*                                                                                               *
//* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,           *
//* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR      *
//* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE     *
//* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR          *
//* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        *
//* DEALINGS IN THE SOFTWARE.                                                                     *
//*************************************************************************************************


#ifndef _INCL_MDINV_CPP
#define _INCL_MDINV_CPP
namespace MDINV{
  template<typename VECT> 
  long incrementMultiDimensionalIndex(VECT& ind, const VECT& bounds, const long& add=1){
    long carryOver=add;
    long i=ind.size();
    if(i<1){return 0;}
    if(i!=bounds.size()){return -1;}
    while((i>0)&&(carryOver>0)){
      --i;
      ind[i]+=carryOver;carryOver=ind[i]/bounds[i];ind[i]%=bounds[i];
    }
    return carryOver;
  }
  template<typename VECT>
  long incrementMultiDimensionalIndex(VECT& ind, const long& modulo, const long& add=1){
    long carryOver=add;
    long i=ind.size();
    if(i<1){return 0;}  
    while((i>0)&&(carryOver>0)){
      --i;
      ind[i]+=carryOver;carryOver=ind[i]/modulo;ind[i]%=modulo;
    }
    return carryOver;
  } 
  template<typename VECT>
  long incrementIncreasing(VECT& v,long uBound){ 
    long sz=v.size();
    long i=sz-1;
    while((i>-1)&&(v[i]==uBound-sz+i)){
      --i;
    }
    if(i==-1){return 1;}
    ++v[i];
    ++i;
    while(i<sz){
      v[i]=v[i-1]+1;
      ++i;
    }
    return 0;
  }
  template<typename VECT>
  int isDistinct(const VECT& v){
    std::set<long> s;
    long i=0;
    long sz=v.size();
    long oldSz;
    while(i<sz){
      oldSz=s.size();
      s.insert(v[i]);
      if(oldSz==s.size()){return 0;}
      ++i;
    }
    return 1;
  }
  template<typename VECT>
  long incrementDistinct(VECT& v, long uBound){
    long carryover=incrementMultiDimensionalIndex(v,uBound);
    if(carryover==1){return 1;}
    while(carryover==0){
      if(isDistinct(v)==1){return 0;}
      carryover=incrementMultiDimensionalIndex(v,uBound);
    }
    return 1;
  }
}

#endif
