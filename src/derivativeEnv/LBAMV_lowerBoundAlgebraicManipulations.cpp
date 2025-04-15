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

#ifndef _INCL_LBAMV_CPP
#define _INCL_LBAMV_CPP
namespace LBAMV{
  template<typename TTT>
  Monomial<TTT>::Monomial(const std::string& _n, const TTT& _c){
    c=_c;name=_n;
  }
  template<typename TTT>
  int Monomial<TTT>::operator<(const Monomial<TTT>& oth) const{
    if(name<oth.name){return 1;}
    return 0;
  } 
  template<typename TTT>
  LinCombination<TTT>& LinCombination<TTT>::operator+=(const LinCombination<TTT>& oth){
    for(long i=0;i<(oth.terms).size();++i){
      long j=terms.find((oth.terms)[i]);
      if(j<0){
        terms.insert((oth.terms)[i]);
      }
      else{
        Monomial<TTT> tOld=terms[j];
        Monomial<TTT> tToAdd=(oth.terms)[i];
        terms.erase(tOld);
        tOld.c+=tToAdd.c;
        if(tOld.c!=0){
          terms.insert(tOld);
        }
      }
    }
    return *this;
  }
  template<typename TTT>
  LinCombination<TTT>& LinCombination<TTT>::operator*=(const TTT& m){
    if(m==0){
      terms.clear();
      return *this;
    }
    for(long i=0;i<terms.size();++i){
      Monomial<TTT> t=terms[i];
      terms.erase(t);
      t.c *= m;
      terms.insert(t);
    }
    return *this;
  }
  template<typename TTT>
  LinCombination<TTT>& LinCombination<TTT>::operator-=(const LinCombination<TTT>& oth){
    LinCombination<TTT> q=oth;
    q*=-1;
    (*this)+=q;
    return *this;
  }
  template<typename TTT>
  TTT LinCombination<TTT>::getComponent(const std::string& st) const{
    TTT res=0;
    Monomial<TTT> mSearch;
    mSearch.name=st;
    long sResult=terms.find(mSearch);
    if(sResult>-1){
      res=terms[sResult].c;
    }
    return res;
  }
  template<typename TTT>
  int allMonomialsInAHaveSmallerThanOrEqualCoefficientsThanMonomialsInB(const LinCombination<TTT>& a, const LinCombination<TTT>& b){
    int stillGood=1;
    long i=0,iOth;
    Monomial<TTT> currentTerm, currentOthTerm;
    while((i<a.terms.size())&&(stillGood)){
      currentTerm=a.terms[i];currentOthTerm=currentTerm;
      currentOthTerm.c=0;
      iOth=b.terms.find(currentTerm);
      if(iOth>-1){currentOthTerm=b.terms[iOth]; }
      if(currentOthTerm.c<currentTerm.c){stillGood=0;}
      ++i;
    }
    return stillGood;
  }
  template<typename TTT>
  int allMonomialsInBMinusAHaveNonNegativeCoefficients(const LinCombination<TTT>& a, const LinCombination<TTT>& b){
    ssm::set<Monomial<TTT> > bMinusA=b.terms;
    bMinusA-=a.terms;
    int stillGood=1;
    long i=0;
    while((i<bMinusA.size())&&(stillGood)){
      if(bMinusA[i].c<0){stillGood=0;}
      ++i;
    }
    return stillGood;
  }
  template<typename TTT>
  int LinCombination<TTT>::partialOrderLEQ(const LinCombination<TTT>& oth) const {
    if(allMonomialsInAHaveSmallerThanOrEqualCoefficientsThanMonomialsInB(*this,oth)==0){return 0;}
    if(allMonomialsInBMinusAHaveNonNegativeCoefficients(*this,oth)==0){return 0;}
    return 1;
  }
  template<typename TTT>
  int LinCombination<TTT>::operator==(const LinCombination<TTT>& oth) const {
    if(terms.size()!=oth.terms.size()){return 0;}
    int stillGood=1;
    long i=0;
    Monomial<TTT> tI,oTI;
    while((stillGood)&&(i<terms.size())){
      tI=terms[i]; oTI=oth.terms[i];
      if( tI.name< oTI.name){stillGood=0;}
      if( oTI.name < tI.name){stillGood=0;}
      if( tI.c<oTI.c){stillGood=0;}
      if( oTI.c<tI.c){stillGood=0;}
      ++i;
    }
    return stillGood;
  }
  template<typename TTT>
  int LinCombination<TTT>::operator<(const LinCombination<TTT>& oth) const {
    long sz=terms.size();
    if(sz<oth.terms.size()){return 1;}
    if(oth.terms.size()<sz){return 0;}
    long i=0; 
    while(i<sz){
      Monomial<TTT> myMonomial, itsMonomial;
      myMonomial=terms[i];itsMonomial=oth.terms[i];
      if(myMonomial.name<itsMonomial.name){return 1;}
      if(itsMonomial.name<myMonomial.name){return 0;}
      if(myMonomial.c<itsMonomial.c){return 1;}
      if(itsMonomial.c<myMonomial.c){return 0;}
      ++i;
    }
    return 0;
  }
  template<typename TTT>
  int LinCombination<TTT>::partialOrderLNEQ(const LinCombination<TTT>& oth) const{
    if(*this==oth){return 0;}
    if(partialOrderLEQ(oth)){return 1;}
    return 0;
  }
  template<typename TTT>
  void LinCombination<TTT>::setFromString(const std::string& s){
    std::map<std::string,std::string> m=SF::stringToMap(s,"_k_","_/k_","_v_","_/v_");
    std::map<std::string,std::string>::const_iterator it,itE;
    it=m.begin();itE=m.end();
    while(it!=itE){
      Monomial<TTT> t;
      t.name=it->first;
      t.c=BF::stringToInteger(it->second);
      terms.erase(t);
      terms.insert(t);
      ++it;
    }
  }
  template<typename TTT>
  std::string LinCombination<TTT>::toString() const{
    std::string res;
    int printed=0;
    for(long i=0;i<terms.size();++i){
      Monomial<long> t=terms[i];
      if((printed)&&(t.c>0)){
        res+="+";
      }
      printed=1;
      res+=std::to_string(t.c);
      res+="*";
      res+=t.name;
    }
    return res;
  }
  long countAs(const std::string& x){
    long res=0;
    for(long i=0;i<x.length();++i){
      res+=(x[i]=='a');
      res+=(x[i]=='A');
    }
    return res;
  }
  LinCombination<long> simpleLinCombExtraction(const std::string& s){
    LinCombination<long> res;
    std::map<std::string,std::string> mR=SF::stringToMap(s,"_k_","_/k_","_v_","_/v_");
    std::map<std::string,std::string>::const_iterator it,itE;
    itE=mR.end();
    it=mR.find("termName");
    if(it==itE){return res;}
    long numAs=countAs(it->second);
    it=mR.find("linComb");
    if(it==itE){return res;}
    res.setFromString(it->second);
    if(numAs%2==1){
      res*=-1;
    }
    return res;
  }
  LinCombination<long> oneLinCombFromString(const std::string& s){
    LinCombination<long> res;
    std::vector<std::string> mVect=SF::stringToVector(s,"_n_","_/n_");
    for(long i=0;i<mVect.size();++i){
      res+=simpleLinCombExtraction(mVect[i]);
    }
    return res;
  }
  std::map<std::string,LinCombination<long> > fromString(const std::string& s){
    std::map<std::string,std::string> raws=SF::stringToMap(s,"_k_","_/k_","_v_","_/v_");
    std::map<std::string,std::string>::const_iterator it=raws.begin(),itE=raws.end();
    std::map<std::string,LinCombination<long> > res;
    while(it!=itE){
      res[it->first]=oneLinCombFromString(it->second);
      ++it;
    }
    return res;
  }
}

#endif
