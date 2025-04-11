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


#ifndef _INCL_BIJFUNCTION_CPP
#define _INCL_BIJFUNCTION_CPP
 

namespace BF{ 
  const char CONST_DECIMAL_SEPARATOR='.';
  const std::string CONST_DECIMAL_SEPARATOR_ST=".";
  const char CONST_THOUSANDS_SEPARATOR=',';
  const std::string CONST_THOUSANDS_SEPARATOR_ST=","; 
  int isNumeric(const std::string & s,const long & tolerateSignsInFront = 1){
    long sz=s.length();
    long i=0;
    long numDecPoints=0;
    int res=1;
    if(tolerateSignsInFront){
      while( (i<sz) && ((s[i]=='-')||(s[i]=='+'))){
        ++i;
      }
    }
    while((res==1)&&(i<sz)){
      if(s[i]==CONST_DECIMAL_SEPARATOR){
        ++numDecPoints;
      }
      else{
        if((s[i]!=CONST_THOUSANDS_SEPARATOR)&&((s[i]<'0')||(s[i]>'9'))){
          res=0;
        }
      }
      if(numDecPoints>1){res=0;}
      ++i;
    }
    return res;
  }
  std::string makeItZeroIfNotNumeric(const std::string &s, const long & tolerateSignsInFront = 1){
    if(isNumeric(s,tolerateSignsInFront)){
      return s;
    }
    return "0";
  }
  std::string padded(const long & _x,const long & _d, const std::string &paddingSt=" "){
    // Examples:
    // BF::padded(3,100,"0")=003
    // BF::padded(33,100,"0")=033
    // BF::padded(0,100,"0")=000
    // BF::padded(33,100000,"0")=000033
      long x=_x;
      if(x<0){x*=-1;}
      long d=_d;
      std::string fR="";
      while(d>x){
          fR+=paddingSt;
          d/=10;
      }
      if(x>0){fR+=std::to_string(x);}
      return fR;
  }
  std::string removeASCII10AND13(const std::string &_input,const std::string & _replaceWith=""){
      std::string output;
      long len=_input.length();
      long i=0;
      while(i<len){
          if(( static_cast<long>(_input[i])!=13)&&( static_cast<long>(_input[i])!=10)){
              output+=_input[i];
          }
          else{
            output+=_replaceWith;
          }
          ++i;
      }
      return output;
  }
  std::string cleanSpaces(const std::string & _input, const int & removeAllSpaces=0, const int & remove10And13 = 1){
      // removes double space characters
      // removes leading spaces in string
      std::string input=_input;
      if(remove10And13){input=removeASCII10AND13(_input);}
      std::string output="";
      int spaceBefore=1;
      int spaceNow;
      long len=input.length();
      for(long i=0;i<len;++i){
          spaceNow=0;
          if((input[i]==' ')||(input[i]=='\t')||(input[i]=='\n')||(static_cast<long>(input[i])==13)){
              spaceNow=1;
          }
          if(spaceNow!=1){
              output+=input[i];
              spaceBefore=0;
          }
          else{
              if(spaceBefore!=1){
                  if(removeAllSpaces==0){output+=input[i];}
              }
              spaceBefore=1;
          }
      }
      return output;
  }
  std::string cleanAllSpaces(const std::string &_input){
    return cleanSpaces(_input,1);
  } 
  long stringToInteger(const std::string &_s){
    std::string t=cleanSpaces(_s,1);
    long sign=1;
    long pos=0;
    long len=t.length();
    if(len<1){
      return 0;
    }
    long fR=0;
      while((pos<len)&&((t[pos]=='+')||(t[pos]=='-'))){
          if(t[pos]=='-'){
              sign *=-1;
          }
          ++pos;
      }
    long zero=static_cast<long>('0');
    while(pos<len){
      if(t[pos]!=CONST_THOUSANDS_SEPARATOR){
        fR*=10;
        fR+=static_cast<long>(t[pos])-zero;
      }
      ++pos;
    }
    fR*=sign;
    return fR;
  }
  std::string removeNonNumericStart(const std::string & _s){
    std::string res;
    long sz=_s.length();
    int stillOK=1;
    while(stillOK&&(sz>0)){
      --sz;
      if( (_s[sz]>='0')&&(_s[sz]<='9') ){
        res = _s[sz]+res;
      }
      else{
        stillOK=1;
      }
    }
    if(sz<1){return res;}
    stillOK=0;++sz;
    while(stillOK && (sz>0)){
      --sz;
      if( (_s[sz]=='-')||(_s[sz]=='+')){
        res = _s[sz] + res;
      }
      else{
        if( (_s[sz]!=' ')&&(_s[sz]!='\t')&&(_s[sz]!='\n') ){
          stillOK=0;
        }
      }
    }
    return res;
  }
  long stringToIntegerRemoveStart(const std::string& _s){
    return stringToInteger(removeNonNumericStart(_s));
  }
  long stringToIntegerRemoveStartAndEnd(const std::string& _s, long maxInt=1000000){
    long res=0;
    long i=0; long sz=_s.length();
    long zero=static_cast<long>('0');
    if(maxInt<1){maxInt=1000000;}
    while((i<sz)&&((_s[i]<'0')||(_s[i]>'9'))){++i;}
    while((i<sz)&&(_s[i]>='0')&&(_s[i]<='9')){
      res*=10;
      res+=static_cast<long>(_s[i])-zero;
      res%=maxInt;
      ++i;
    }
    return res;
  } 
}
#endif
