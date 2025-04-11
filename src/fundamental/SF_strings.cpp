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


#ifndef _INCL_SF_STRINGS_CPP
#define _INCL_SF_STRINGS_CPP

namespace SF{
  template<class T1, class T2>
  class TwoValues{
  public:
    T1 x;
    T2 y;
    long operator<(const TwoValues &) const;
  };
  template<class T1, class T2>
  long TwoValues<T1,T2>::operator<(const TwoValues<T1,T2> & oth) const{
    if(x<oth.x){
      return 1;
    }
    if(x>oth.x){
      return 0;
    }
    if(y<oth.y){
      return 1;
    }
    return 0;
  }
  template<typename T1, typename T2>
  void sortWithFollower(std::vector<T1> & v1, std::vector<T2> & v2){
    long sz=v1.size();
    if(v2.size()==sz){
      std::vector<TwoValues<T1,T2> > w;
      w.resize(sz);
      for(long i=0;i<sz;++i){
        (w[i]).x=v1[i];
        (w[i]).y=v2[i];
      }
      std::sort(w.begin(),w.end());
      for(long i=0;i<sz;++i){
        v1[i]=(w[i]).x;
        v2[i]=(w[i]).y;
      }
    }
  }
  int isLetterOrBS(const char & c){
    if( (c>='a') && (c<='z')){return 1;}
    if( (c>='A') && (c<='Z')){return 1;}
    if(c=='\\'){return 1;}
    return 0;
  }
  long getPositionOfFirstLetterOrBS(const std::string & st, const long & start=0){
    long len=st.length();
    long res=-1;
    long i=start;
    while((i<len)&&(!isLetterOrBS(st[i]))){
      ++i;
    }
    if((i<len)&&(isLetterOrBS(st[i]))){
      res=i;
    }
    return res;
  }
  bool caseInsensitiveComp(char a, char b){
    return (MFRF::toLowerCase(a)==MFRF::toLowerCase(b));
  }
  std::pair<std::string, int> getEverythingBefore(const std::string & src,
                                                  long & pos,
                                                  const std::string &endSt,
                                                  const int & caseSensitive = 0){
      //
      // If you do the following
      // std::string src="012345678901234567890123456789";
      // long pos=7;
      // std::pair<std::string,int> res=SF::getEverythingBefore(src,pos,"5678");
      // then you will have res.first="78901234" and pos=19
      std::string::const_iterator srcIt=src.begin(),j;
      srcIt+=pos;
      if(caseSensitive==0){
        j=std::search(srcIt,src.end(),endSt.begin(),endSt.end(),caseInsensitiveComp);
      }
      else{
        j=std::search(srcIt,src.end(),endSt.begin(),endSt.end());
      }
      if(j==src.end()){
        pos=src.length();
        return std::make_pair(src,0);
      }
      std::string fR;
      while(srcIt!=j){
        fR+=*srcIt; ++srcIt;++pos;
      }
      pos+=endSt.length();
      return std::make_pair(fR,1);
  }
  long firstContainsTheOther(const std::string &st1,const std::string &st2,const int & caseSensitive=0){
    long pos=0;
    std::pair<std::string,int> aD=getEverythingBefore(st1,pos,st2,caseSensitive);
    return aD.second;
  }
  std::pair<std::string,int> extract(const std::string &  ,
                                     long &  ,
                                     const std::string & ,
                                     const std::string & ,
                                     const int &  );
  std::pair<std::string,int> extrStrong(const std::string & src,
                                        long & pos,
                                        const std::string &startString,
                                        const std::string &endString,
                                        const int & caseSensitive = 0){
      if(startString==endString){
        return extract(src,pos,startString,endString,caseSensitive);
      }
      std::pair<std::string,int> fR;
      fR.first="";
      fR.second=0;
      long saveOldPos=pos;
      std::pair<std::string,int> thrashSt=getEverythingBefore(src,pos,startString,caseSensitive);
      std::pair<std::string,int> beforeNextStart,beforeNextEnd;
      if(thrashSt.second==1){
          long depth=1;
          long posAfterStart;
          long posAfterEnd;
          while(depth>0){
            posAfterStart=pos;
            posAfterEnd=pos;
            beforeNextStart=getEverythingBefore(src,posAfterStart,startString,caseSensitive);
            beforeNextEnd=getEverythingBefore(src,posAfterEnd,endString,caseSensitive);
            if((beforeNextStart.second==1)&&(beforeNextEnd.second==1)){
              if(posAfterStart<posAfterEnd){
                fR.first+=beforeNextStart.first+startString;
                pos=posAfterStart;
                ++depth;
              }
              else{
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
            }
            else{
              if(beforeNextEnd.second==1){
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
              else{
                fR.second=0;
                fR.first="";
                return fR;
              }
            }
          }
          fR.second=1;
      }
      if(fR.second==0){
          fR.first="";
          pos=saveOldPos;
      }
      return fR;
  }
  std::pair<std::string,int> extract(const std::string & src,
                                     long & pos,
                                     const std::string &startString,
                                     const std::string &endString,
                                     const int & caseSensitive = 0){

      if(startString!=endString){
        return extrStrong(src,pos,startString,endString,caseSensitive);
      }
      std::pair<std::string,int> fR;
      fR.first="";
      fR.second=0;
      std::pair<std::string,int> thrashSt=getEverythingBefore(src,pos,startString,caseSensitive);
      if(thrashSt.second==1){
          fR=getEverythingBefore(src,pos,endString,caseSensitive);
      }
      if(fR.second==0){
          fR.first="";
      }
      return fR;
  }
  std::pair<std::string,int> extractAndReplace(const std::string &  ,
                                               long &  ,
                                               const std::string & ,
                                               const std::string & ,
                                               const int &  ,
                                               const std::string &  );

  std::pair<std::string,int> extrReplStrong(const std::string & src,
                                            long & pos,
                                            const std::string &startString,
                                            const std::string &endString,
                                            const int & caseSensitive = 0,
                                            const std::string & replaceWith=""){
      if(startString==endString){
        return extractAndReplace(src,pos,startString,endString,caseSensitive,replaceWith);
      }
      std::pair<std::string,int> fR;
      fR.first="";
      fR.second=0;
      std::pair<std::string,int> thrashSt=getEverythingBefore(src,pos,startString,caseSensitive);
      std::pair<std::string,int> beforeNextStart,beforeNextEnd;
      if(thrashSt.second==1){
          long depth=1;
          long posAfterStart;
          long posAfterEnd;
          while(depth>0){
            posAfterStart=pos;
            posAfterEnd=pos;
            beforeNextStart=getEverythingBefore(src,posAfterStart,startString,caseSensitive);
            beforeNextEnd=getEverythingBefore(src,posAfterEnd,endString,caseSensitive);
            if((beforeNextStart.second==1)&&(beforeNextEnd.second==1)){
              if(posAfterStart<posAfterEnd){
                fR.first+=beforeNextStart.first+startString;
                pos=posAfterStart;
                ++depth;
              }
              else{
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
            }
            else{
              if(beforeNextEnd.second==1){
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
              else{
                fR.second=0;
                fR.first="";
                return fR;
              }
            }
          }
          fR.second=1;
      }
      if(fR.second==0){
          fR.first=src;
          return fR;
      }
      fR.first=thrashSt.first;
      fR.first+=replaceWith;
      long posSave=(fR.first).length();
      long sz=src.length();
      while(pos<sz){
        fR.first += src[pos];
        ++pos;
      }
      pos=posSave;
      return fR;
  }
  std::pair<std::string,int> extractAndReplace(const std::string & src,
                                               long & pos,
                                               const std::string &startString,
                                               const std::string &endString,
                                               const int & caseSensitive = 0,
                                               const std::string & replaceWith=""){
    if(startString!=endString){
      return extrReplStrong(src,pos,startString,endString,caseSensitive,replaceWith);
    }
    std::pair<std::string,int> fR;
    fR.first="";
    fR.second=0;
    std::pair<std::string,int> thrashSt=getEverythingBefore(src,pos,startString,caseSensitive);
    if(thrashSt.second==1){
        fR=getEverythingBefore(src,pos,endString,caseSensitive);
    }
    if(fR.second==0){
        fR.first="";
        return fR;
    }
    fR.first=thrashSt.first;
    fR.first+=replaceWith;
    long posSave=(fR.first).length();
    long sz=src.length();
    while(pos<sz){
      fR.first += src[pos];
      ++pos;
    }
    pos=posSave;
    return fR;
  }
  std::pair<std::string,int> eraseStuffBetween(const std::string & src,
                                               const std::string &startString,
                                               const std::string &endString,
                                               const long & cpos = 0,
                                               const int & caseSensitive = 0){

      long pos=cpos;
      return extractAndReplace(src,pos,startString,endString,caseSensitive,"");
  }  
  template<typename T>
  void flipTheStack(std::stack<T>& s){
    std::stack<T> t;
    t=std::move(s);
    while(!t.empty()){
      s.push(t.top());
      t.pop();
    }
  }

  template<typename TTT>
  std::stack<TTT> clearStack(std::stack<TTT> & v){
    if(v.empty()){
      return v;
    }
    v.pop();
    return clearStack(v);
  }
  template<typename TTT>
  std::vector<TTT> stackToVector(std::stack<TTT> & st){//returns flipped stack as a vector
    std::vector<TTT> fR;
    long sz=st.size();
    if(sz>0){
      fR.resize(sz);
      for(long i=0;i<sz;++i){
        fR[sz-i-1]=st.top();
        st.pop();
      }
    }
    return fR;
  }
  template<typename TTT>
  std::set<TTT> vectorToSet(const std::vector<TTT> &_v){
    std::set<TTT> fR;
    long sz=_v.size();
    for(long i=0;i<sz;++i){
      fR.insert(_v[i]);
    }
    return fR;
  }
  template<typename TTT>
  std::vector<TTT> setToVector(const std::set<TTT> &_s){
    std::vector<TTT> fR;
    long sz=_s.size();
    fR.resize(sz);
    typename std::set<TTT>::const_iterator it=_s.begin(),itE=_s.end();
    long i=0;
    while(it!=itE){
      fR[i]=*it;
      ++it;++i;
    }
    return fR;
  }
  std::string reverseString(const std::string& input){
    std::string result;
    long i=input.size();
    while(i>0){
      --i;
      result+=input[i];
    }
    return result;
  }
  std::string findAndReplace(const std::string &input,
                          const std::string &_searchFor,
                          const std::vector<std::string> &_replaceWith,
                          const int &all=1,
                          const int &caseSensitive=0){
      // Searches input for _searchFor; The first one is replaced by _replaceWith[0],
      // the second occurrence with _replaceWith[1], ..., the _replaceWith.size()-th ocurrence
      // with _replaceWith[0] again and it cycles
      if(input.length()<1){return input;}
      if(_searchFor.length()<1){return input;}
      std::string searchFor=_searchFor;
      std::vector<std::string> replaceWith=_replaceWith;
      if(replaceWith.size()==0){
        replaceWith.resize(1);replaceWith[0]="";
      }
      long ctrReplaceWith=0;
      long lenReplW=replaceWith.size();
      std::string endS="0!*#K#01909342$!#$";
      long pos=0;
      std::pair<std::string,int> allD;
      std::string output="",nBefore;
      long len=input.length();
      long lsf=searchFor.length();
      long lp1=len+1;
      long oldPos;
      while(pos<len){
        oldPos=pos;
        allD=getEverythingBefore(input,pos,searchFor,caseSensitive);
        if(allD.second==1){
          output += allD.first;
          if(pos<lp1){
            //Found the real occurrence of searchFor
            // not the fake one that we added to the end
            output+=replaceWith[ctrReplaceWith];
            if(lenReplW>1){
              ++ctrReplaceWith;
              if(ctrReplaceWith==lenReplW){
                ctrReplaceWith=0;
              }
            }
            if(all==0){
              oldPos=pos;
            }
          }
        }
        if((allD.second==0)||(all==0)){
          pos=len;
          for(long i=oldPos;i<pos;++i){
            output+=input[i];
          }
        }
      }
      return output;
  }
  std::string findAndReplace(const std::string &input,
                          const std::string &searchFor,
                          const std::string &_replaceWith,
                          const int &all=1,
                          const int &caseSensitive=0){
      if(searchFor==_replaceWith){
        return input;
      }
      if(input.length()<1){return input;}
      std::vector<std::string> replw;
      replw.resize(1);
      replw[0]=_replaceWith;
      return findAndReplace(input,searchFor,replw,all,caseSensitive);
  }
  long getFirstPosition(const std::string &input,
                        const long & _pos,
                        const std::string &searchFor,
                        const int & caseSensitive=0){
    long pos=_pos;
    std::pair<std::string,int> allD=getEverythingBefore(input,pos,searchFor,caseSensitive);
    if(allD.second==0){
      return input.length();
    }
    return pos-searchFor.length();
  }
  void updateFirstPositions(std::vector<long>& fPositions,
                            const std::string &input,
                            const long &_pos,
                            const std::vector<std::string> &searchFor,
                            const int& caseSensitive=0){
    long ln=searchFor.size();
    if((ln==fPositions.size())&&(ln>0)){
      for(long i=0;i<ln;++i){
        if( fPositions[i]<_pos ){
          fPositions[i]=getFirstPosition(input,_pos,searchFor[i],caseSensitive);
        }
      }
    }
  }
  std::pair<long,long> minAndMinimizer(const std::map<long,long> & m){
    std::pair<long,long> res;
    res.first=-1;res.second=-1;
    long sz=m.size();
    if(sz<1){return res;}
    return *(m.begin());
  }
  std::map<long,long> firstPosMap(const std::vector<long> & v){
    std::map<long,long> res;
    long i=v.size();
    while(i>0){
      --i;
      res[v[i]]=i;
    }
    return res;
  }
  std::string findAndReplaceSecureButNotVeryFast(const std::string &input,
                             const std::vector<std::string> &searchFor,
                             const std::vector<std::string> &replaceWith,
                             const int &caseSensitive=0){
      long lenSF=searchFor.size();
      if((lenSF<1)||(replaceWith.size()!=lenSF)){
        return input;
      }
      std::vector<long> fPositions;
      fPositions.resize(lenSF);
      for(long i=0;i<lenSF;++i){
        fPositions[i]=-1;
      }
      std::pair<long,long> minsV;
      long pos=0;
      updateFirstPositions(fPositions,input,pos,searchFor,caseSensitive);
      std::map<long,long> fPMap=firstPosMap(fPositions);
      long sz=input.length();
      std::string output;
      while(pos<sz){
        minsV=minAndMinimizer(fPMap);
        while(pos<minsV.first){
          output+=input[pos];
          ++pos;
        }
        if((minsV.second>-1)&&(minsV.first<sz)){
          output+=replaceWith[minsV.second];
          pos+=searchFor[minsV.second].length();
        }
        fPMap.erase(fPMap.begin());
        fPMap[getFirstPosition(input,pos, searchFor[minsV.second],caseSensitive)]=minsV.second;
      }
      return output;
  }
  std::string findAndReplace(const std::string &input,
                             const std::vector<std::string> &searchFor,
                             const std::vector<std::string> &replaceWith,
                             const int &caseSensitive=0){
      // This function trusts that
      // 1) searchFor[i] appears only once for every i.
      // 2) searchFor[i] appears before searchFor[j] if i<j
      // If 1) or 2) fails, then the function will findAndReplaceSecureButNotVeryFast.
      long lenSF=searchFor.size();
      if((lenSF<1)||(replaceWith.size()!=lenSF)){
        return input;
      }
      std::vector<long> fPositions;
      fPositions.resize(lenSF);
      for(long i=0;i<lenSF;++i){
        fPositions[i]=-1;
      }
      std::pair<long,long> minsV;
      long pos=0;
      updateFirstPositions(fPositions,input,pos,searchFor,caseSensitive);
      long trustworthy=1;
      long i=1;
      while((i<lenSF)&&(trustworthy==1)){
        if(fPositions[i-1]>=fPositions[i]){
          trustworthy=0;
        }
        ++i;
      }
      if(trustworthy==0){
        return findAndReplaceSecureButNotVeryFast(input,searchFor,replaceWith,caseSensitive);
      }
      long sz=input.length();
      std::string output;
      i=0;
      while((pos<sz)&&(i<lenSF)){
        minsV.first=fPositions[i];
        minsV.second=i;
        while(pos<fPositions[i]){
          output+=input[pos];
          ++pos;
        }
        if(fPositions[i]<sz){
          output+=replaceWith[i];
          pos+=searchFor[i].length();
        }

        ++i;
      }
      while(pos<sz){
        output+=input[pos];
        ++pos;
      }
      return output;
  }
  long countInString(const std::string & _allItems,
                                    const std::string & _nextB="_n_",
                                    const std::string & _nextE="_/n_",
                                    const std::string & _attMustHave="!*!"){
    long fR=0;
    long pos=0;
    std::pair<std::string,int> nextSt=extract(_allItems,pos,_nextB,_nextE);
    while(nextSt.second==1){
      if(_attMustHave!="!*!"){
        fR+=firstContainsTheOther(nextSt.first,_attMustHave);
      }
      else{
        ++fR;
      }
      nextSt=extract(_allItems,pos,_nextB,_nextE);
    }
    return fR;
  }
  std::string vectorToString(const std::vector<std::string> & v,
                            const std::string & _nextB="_n_",
                            const std::string & _nextE="_/n_"){
    std::string fR="";
    long sz=v.size();
    for(long i=0;i<sz;++i){
      fR+=_nextB+v[i]+_nextE;
    }
    return fR;
  }
  long copyTheRestOfTheStringAndGiveUp(const std::string& in, const long& oldPosSave, std::string& out,const int& copyIsNecessary){
    long len=in.length();
    if(copyIsNecessary==0){
      return len;
    }
    long pos=oldPosSave;
    while(pos<len){
      out+=in[pos];
      ++pos;
    }
    return pos;
  }
  std::pair<std::stack<std::string>,std::string>
                  stringToStackAndRemoveItems(const std::string & _allItems,
                                              const std::string & _nextB="_n_",
                                              const std::string & _nextE="_/n_",
                                              const int & removalIsNecessary=1,
                                              const std::string & _attMustHave="!*!"){
    std::pair<std::stack<std::string>,std::string> fR;
    long pos=0; std::pair<std::string,int> allD;
    long len=_allItems.length(); long openTagLen=_nextB.length();
    std::string stBefore,nextSt;
    long oldPosSave;
    while(pos<len){
      oldPosSave=pos;
      allD=getEverythingBefore(_allItems,pos,_nextB);
      if(allD.second==0){
        pos=copyTheRestOfTheStringAndGiveUp(_allItems,oldPosSave,fR.second,removalIsNecessary);
      }
      else{
        pos-=openTagLen;
        stBefore=allD.first;
        allD=extract(_allItems,pos,_nextB,_nextE);
        if(allD.second==0){
          pos=copyTheRestOfTheStringAndGiveUp(_allItems,oldPosSave,fR.second,removalIsNecessary);
        }
        else{
          nextSt=allD.first;
          if(removalIsNecessary){fR.second+=stBefore;}
          if((_attMustHave=="!*!") || (findAndReplace(nextSt,_attMustHave,"")!=nextSt) ){
            (fR.first).push(nextSt);
          }
        }
      }
    }
    return fR;
  }
  std::pair<std::vector<std::string>,std::string>
                  stringToVectorAndRemoveItems(const std::string & _allItems,
                                               const std::string & _nextB="_n_",
                                               const std::string & _nextE="_/n_",
                                               const int & removalIsNecessary=1,
                                               const std::string & _attMustHave="!*!"){
    std::pair<std::vector<std::string>,std::string> fR;
    std::pair<std::stack<std::string>,std::string> tmpStack;
    tmpStack=stringToStackAndRemoveItems(_allItems,_nextB,_nextE,removalIsNecessary,_attMustHave);
    fR.second=tmpStack.second;
    fR.first=stackToVector(tmpStack.first);
    return fR;
  }
  std::vector<std::string> stringToVector(const std::string & _allItems,
                                          const std::string & _nextB="_n_",
                                          const std::string & _nextE="_/n_",
                                          const std::string & _attMustHave="!*!"){
    return stringToVectorAndRemoveItems(_allItems,_nextB,_nextE,0,_attMustHave).first;
  }
  std::stack<std::string> stringToStack(const std::string & _allItems,
                                        const std::string & _nextB="_n_",
                                        const std::string & _nextE="_/n_",
                                        const std::string & _attMustHave="!*!"){
    return stringToStackAndRemoveItems(_allItems,_nextB,_nextE,0,_attMustHave).first;
  }
  std::set<std::string> stringToSet(const std::string & everything, const std::string & sepKeyB,const std::string & sepKeyE){
    std::set<std::string> fR;
    std::vector<std::string> keys=stringToVector(everything,sepKeyB,sepKeyE);
    long sz=keys.size();
    for(long i=0;i<sz;++i){
      fR.insert(keys[i]);
    }
    return fR;
  }
  std::string setToString(const std::set<std::string> & s, const std::string & sepKeyB,const std::string & sepKeyE ,const std::string &formattingSeparator=""){
    std::string fR="";
    std::set<std::string>::const_iterator it=s.begin(),itE=s.end();
    while(it!=itE){
      fR+=sepKeyB+(*it)+sepKeyE+formattingSeparator;
      ++it;
    }
    return fR;
  }
  std::map<std::string,std::string> stringToMap(const std::string & everything, const std::string & sepKeyB,const std::string & sepKeyE,const std::string & sepValB,const std::string & sepValE){
    std::map<std::string,std::string> fR;
    int stillWorking=1;
    std::pair<std::string,int> allD; long pos=0;
    std::string nextKey;
    while(stillWorking){
      allD=extract(everything,pos,sepKeyB,sepKeyE);
      if(allD.second==1){
        nextKey=allD.first;
        allD=extract(everything,pos,sepValB,sepValE);
        if(allD.second==1){
          fR[nextKey]=allD.first;
        }
        else{
          stillWorking=0;
        }
      }
      else{
        stillWorking=0;
      }
    }
    return fR;
  } 
  std::string incrementString(const std::string & x){
      std::string res=x;
      long cS=res.size();
      long success=0;--cS;
      char zeroM1='0'-1;
      char nineP1='9'+1;
      char aM1='a'-1;
      char zP1='z'+1;
      while((success==0)&&(cS>-1)){
          if((res[cS]>zeroM1)&&(res[cS]<'9')){
              res[cS]=res[cS]+1;success=1;
          }
          if((success==0)&&(res[cS]=='9')){
              res[cS]='a';success=1;
          }
          if((success==0)&&(res[cS]>aM1)&&(res[cS]<zP1)){
              if(res[cS]<'z'){
                  res[cS]=res[cS]+1;
                  success=1;
              }
              else{
                  res[cS]='0';
              }
          }
          cS--;
      }
      if(success==0){
          res='1'+res;
      }
      return res;
  } 
  template<typename T>
  void assignToConst(const T& receiver, const T& sender){
    *(T*)(&receiver)=sender;
  } 
}
#endif
