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


#ifndef _INCL_LBLCV_CPP
#define _INCL_LBLCV_CPP
namespace LBLCV{
    long twoToPower(long n){
      if(n<0){n*=-1;}
      long res=1;
      while(n!=0){
        res*=2;
        --n;
      }
      return res;
    }
   template<typename T>
   int CompVector<T>::operator<(const CompVector<T>& oth) const{
     long sz=v.size();
     if(sz<oth.v.size()){return 1;}
     if(sz>oth.v.size()){return 0;}
     long i=0;
     int result=-1;
     while(i<sz){
       if(v[i]<oth.v[i]){result=1;}
       if(v[i]>oth.v[i]){result=0;}
       ++i;
     }
     if(result==-1){result=0;}
     return result;
   }
   template<typename T>
   const T& CompVector<T>::operator[](long i) const{return v[i];}
   template<typename T>
   T& CompVector<T>::operator[](long i){return v[i];}
   template<typename T>
   void CompVector<T>::resize(long sz){v.resize(sz); }
   template<typename T>
   long CompVector<T>::size() const{return v.size();}
   std::string to_string_c(const std::string& x){return x;}
   std::string to_string_c(const long& x){return std::to_string(x);}
   template<typename T>
   std::string CompVector<T>::toString(const std::string& oT, const std::string& cT, const std::string& eS) const{
     long sz=v.size();
     if(sz<1){return "";}
     std::string res;
     int printed=0;
     for(long i=0;i<sz;++i){
       if(printed==0){
         res+= oT; 
       }
       else{
         res+=eS;
       }
       printed=1;
       res+=to_string_c(v[i]);
     }
     res+=cT;
     return res;
   }
   long toInteger(long x){return x;}
   template<typename T>
   long CompVector<T>::sum(long start, long end) const{
    if(end<0){end=v.size();}
    if(end>v.size()){end=v.size();}
    if(start<0){start=0;}
     long total=0;
     for(long i=start;i<end;++i){
       total+=toInteger(v[i]);
     }
     return total;
   }
   template<typename T>
   int HelpfulnessIndicators<T>::operator<(const HelpfulnessIndicators<T>& oth) const{
    if(r<oth.r){return 1;}
    if(oth.r<r){return 0;}
    if(hIndicators<oth.hIndicators){return 1;}
    return 0;
   }
   template<typename T>
   std::string HelpfulnessIndicators<T>::toString() const{
     long sz=r.size();
     if((sz<1) || (sz!=hIndicators.size())){return "Invalid indicators";}
     std::string res;
     for(long i=0;i<sz;++i){
       if(r[i]==0){res+='a';}
       if(r[i]==1){res+='b';}
     }
     res+="->";
     for(long i=0;i<sz;++i){
       res+=std::to_string(hIndicators[i]);
     }
     return res;
   }
   long firstHelpfulIndex(const HelpfulnessIndicators<long>& h){
     // returns -1 if there are no helpful indices
     // returns -2 if the structure is broken
     long sz=h.r.size();
     if( (sz<1) || (h.r.size()!=h.hIndicators.size()) ) return -2;
     long result=-1, i=0;
     while((result==-1)&&(i<sz)){
       if(h.hIndicators[i]!=0){result=i;}
       ++i;
     }
     return result;
   }
   template<typename T>
   std::string DirectPathSegment<T>::toString() const{
     std::string res=cost.toString();
     if(restrictions.size()>0){
       res+=" (restrictions: ";
       typename std::map<long,T>::const_iterator it,itE;
       it=restrictions.begin();
       itE=restrictions.end();
       while(it!=itE){
         res+="(";
         res+=to_string_c(it->first)+","+to_string_c(it->second);
         res+=") ";
         ++it;
       }
       res+=")";
     }
     return res;
   }
   template<typename T>
   int DirectPathSegment<T>::restrictionsSatisfied(const CompVector<T>& env) const{
    typename std::map<long,T>::const_iterator it,itE;
    it=restrictions.begin();itE=restrictions.end();
    while(it!=itE){
      if(env[it->first]!=it->second){return 0;}
      ++it;
    }
    return 1;
   }
   template<typename T> 
   int compareMapsLex(const std::map<long,T>& a,const std::map<long,T>& b){
    long sz=a.size();
    if(sz<b.size()){return 1;}
    if(b.size()<sz){return 0;}
    typename std::map<long,T>::const_iterator itA=a.begin(), itAE=a.end(), itB=b.begin(), itBE=b.end();
    while(itA!=itAE){
      if((itA->first)<(itB->first)){return 1;}
      if((itB->first)<(itA->first)){return 0;}
      if((itA->second)<(itB->second)){return 1;}
      if((itB->second)<(itA->second)){return 0;}
      ++itA;++itB;
    }
    return 0;
   }
   template<typename T>
   int DirectPathSegment<T>::operator<(const DirectPathSegment<T>& oth) const{
    if(cost<oth.cost){return 1;}
    if(oth.cost<cost){return 0;}
    return compareMapsLex(restrictions,oth.restrictions);
   }
   template<typename T>
   std::string mapToString(const std::map<CompVector<T>,DirectPathSegment<T> >& m,const std::string& lineBegin){
     std::string res;
     typename std::map<CompVector<T>,DirectPathSegment<T> >::const_iterator it,itE;
     it=m.begin();itE=m.end();
     while(it!=itE){
       res+=lineBegin;
       res+="("+(it->first).toString()+") ";
       res+=(it->second).toString();
       ++it;
     }
     return res;
   }
   template<typename T>
   std::string MainGraph<T>::toString() const{
     std::string res;
     typename std::map<CompVector<T>, std::map<CompVector<T>,DirectPathSegment<T> > >::const_iterator it,itE;
     it=g.begin();itE=g.end();
     while(it!=itE){
       res+=(it->first).toString()+": "+mapToString(it->second,"\n\t\t")+"\n";
       ++it;
     }
     return res;
   }
   template<typename T>
   LowerBoundProofData<T>::LowerBoundProofData(){proofFound=0;}
   std::string createNameForVertex(long i){
     return BF::padded(i,GL_powerOfTenForPadding,"0");
   }
   LBAMV::Monomial<long> createBasicEdgeMonomial(long i, long j){
     LBAMV::Monomial<long> t;
     t.name="e"+GL_sepOpenTag+createNameForVertex(i)+GL_sepCloseTag;
     t.name+=GL_sepOpenTag+createNameForVertex(j)+GL_sepCloseTag;
     t.c=1;
     return t;
   }
   LBAMV::Monomial<long> createThetaMonomial(long i, long j,const std::string& additionToName,const CompVector<long>& env){
     LBAMV::Monomial<long> t;
     t.name="t"+GL_sepOpenTag+createNameForVertex(i)+GL_sepCloseTag;
     t.name+=GL_sepOpenTag+createNameForVertex(j)+GL_sepCloseTag;
     t.name+=GL_sepOpenTag+additionToName+GL_sepCloseTag;
     t.c=env.sum(i,j); 
     return t;
   }
   LBAMV::Monomial<long> createMonomial(const std::string& _nm,long c){
     LBAMV::Monomial<long> t;
     t.name=_nm;
     t.c=c;
     return t;
   }
   LBAMV::LinCombination<long> createBasicEdge(long start,long end, const std::string& additionToName){
    LBAMV::LinCombination<long> res;
    long i=start;
    while(i<end){
      res.terms.insert(createBasicEdgeMonomial(i,i+1));
      ++i;
    }
    return res;
   }
   CompVector<long> createBaseEnvironment(long m=4){
     CompVector<long> res;
     res.resize(m);
     for(long i=0;i<m;++i){
       res[i]=0;
     }
     return res;
   }
   DirectPathSegment<long> simpleSegment(long start, long end, const CompVector<long>& env,long restrictionInd,std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > >& rM){
    DirectPathSegment<long> res;
    res.cost=createBasicEdge(start,end,env.toString() );
    if(end>start+1){
      res.cost.terms.insert(createMonomial("a",end-start-1));
    }
    if((restrictionInd+1>start)&&(restrictionInd+1<end)){
      LBAMV::Monomial<long> tm=createThetaMonomial(start,end,env.toString()+"R",env);
      res.cost.terms.insert(tm);
      res.restrictions[restrictionInd]=env[restrictionInd];
      rM[env].insert(tm);
      return res;
    }
    if(end>start+1){res.cost.terms.insert(createThetaMonomial( start,end,env.toString(),env ));}
    return res;
   }
   std::map<CompVector<long>,DirectPathSegment<long> > simpleSegmentMap(const CompVector<long>& env, long start, long end, long restrictionInd, std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > >& rM){
      std::map<CompVector<long>,DirectPathSegment<long> > res;
      res[env]=simpleSegment(start,end,env,restrictionInd,rM);
      return res;
   }
   MainGraph<long> createInitialGraph(long m=4){
      std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > > empty;
     if(m<1){m=4;}
     if(m>GL_MAX_M){m=4;}
     MainGraph<long> res;
     CompVector<long> tempPair;
     tempPair.resize(2);
     CompVector<long> base=createBaseEnvironment(m);
     for(long i=0;i<m+1;++i){
       tempPair[0]=i;tempPair[1]=i+1;
       res.g[tempPair]=simpleSegmentMap(base,i,i+1,-1,empty);
     }
     return res;
   }
   CompVector<long> toCompVect(long x, long nBits){
     CompVector<long> res;
     res.resize(nBits);
     while(nBits>0){
       --nBits;
       res[nBits]=x%2;x/=2;
     }
     return res;
   }
   CompVector<long> negativelyHelpfulAssociate(const HelpfulnessIndicators<long>& h){
     CompVector<long> res;
     if(h.r.size()!=GL_OnlyAcceptableM){return res;}
     if(h.hIndicators.size()!=GL_OnlyAcceptableM){return res;}
     long sz=GL_OnlyAcceptableM;
     long i=0;
     while((i<sz)&&(h.hIndicators[i]==0)){++i;}
     if(i==sz){return res;}
     res=h.r;
     res[i]=1-res[i];
     return res;
   }
   long findFlipThatHitsTheTarget(CompVector<long> toFlip, const CompVector<long>& target){
     long sz=toFlip.size();
     if((sz<1)||(sz!=target.size())){return 1;}
     long result=-1;
     long i=0;
     while((i<sz)&&(result==-1)){
       toFlip[i]=1-toFlip[i];
       if(!( (toFlip<target) || (target<toFlip) ) ){result=i;}
       toFlip[i]=1-toFlip[i];
       ++i;
     }
     return result;
   }
   std::string toString(const ssm::set<CompVector<long> >& s){
     std::string res;
     for(long i=0;i<s.size();++i){
       res+=s[i].toString()+" ";
     }
     return res;
   }
   int isRepairablePair(const CompVector<long>& v, long hIndicator, long i){
    if(i==0){
      if(v[2]==0){
        if((hIndicator!=0)&&(hIndicator!=1)){
          return 1;
        }
      }
      return 0;
    }
    if(i==v.size()-1){
      if(v[i-1]==0){
        if((hIndicator!=i-1)&&(hIndicator!=i)){
          return 1;
        }
      }
      return 0;
    }
    if( (v[i-1]==0)&&(v[i+1]==0)){
      if( (hIndicator!=i-1) && (hIndicator!=i) && (hIndicator!=i+1) ){
        return 1;
      }
    }
    return 0;
   }
   void updateInformationForRepairs(std::set<CompVector<long> >& res, const CompVector<long> & v, long hIndicator){
    CompVector<long> tmp;tmp.resize(2);
    for(long i=0;i<v.size();++i){
      if(isRepairablePair(v,hIndicator,i)){
        tmp[0]=i;
        tmp[1]=v[i];
        res.insert(tmp);
      }
    }
   }
   std::set<CompVector<long> > getInformationForRepairs(const std::map< CompVector<long> , long >& es){
    std::set<CompVector<long> > res;
    std::map< CompVector<long> , long >::const_iterator it,itE;
    it=es.begin();itE=es.end();
    while(it!=itE){
      updateInformationForRepairs(res,it->first,it->second);
      ++it;
    }
    return res;
   }
   void doTheRepair(const CompVector<long>& v, long& indexOfBrokenInclusion){ 
     indexOfBrokenInclusion=-1;
   }
   void repairIfPossible01(const CompVector<long>& v, long& indexOfBrokenInclusion, const std::set<CompVector<long> >& rE){
    CompVector<long> forSearch;
    forSearch.resize(2);
    forSearch[0]=indexOfBrokenInclusion;
    forSearch[1]=v[indexOfBrokenInclusion];
    if(indexOfBrokenInclusion==0){
      if(v[1]!=0){return ;}
      if(rE.find(forSearch)!=rE.end()){
        doTheRepair(v,indexOfBrokenInclusion);
      }
      return;
    }
    if(indexOfBrokenInclusion==v.size()-1){
      if(v[v.size()-2]!=0){return ;}
      if(rE.find(forSearch)!=rE.end()){
        doTheRepair(v,indexOfBrokenInclusion);
      }
      return;
    }
    if(v[indexOfBrokenInclusion-1]!=0){return;}
    if(v[indexOfBrokenInclusion+1]!=0){return;}
    if(rE.find(forSearch)!=rE.end()){
      doTheRepair(v,indexOfBrokenInclusion);
    }
    return;
   }  
   void repairEnvironments(std::map< CompVector<long> , long >& es){
    std::set<CompVector<long> > rE=getInformationForRepairs(es);
    // the vector contains the pairs: (i,alpha)
    // The meaning is the following: (i,i+1,i+2) is reparable triple if
    // r[i+1] is equal to alpha
    std::map<CompVector<long>, long>::iterator it,itE;
    itE=es.end();
    it=es.begin();
    while(it!=itE){
      if(it->second>-1){ 
        repairIfPossible01(it->first,it->second,rE); 
      }
      ++it;
    }
   }
   std::map< CompVector<long> , long > splitTheSetVPlus2(const HelpfulnessIndicators<long>& h,int indDoTheRepairs=1){
     std::map< CompVector<long> , long > res;
     if(h.r.size()!=GL_OnlyAcceptableM){return res;}
     if(h.hIndicators.size()!=GL_OnlyAcceptableM){return res;}
     CompVector<long> nha=negativelyHelpfulAssociate(h);
     if(!( (nha<h.r) || (h.r<nha) )){return res;}
     if(nha.size()<1){return res;}
     long i=0; long sz=h.r.size();
     CompVector<long> vI;
     long bound=twoToPower(sz);
     while(i<bound){
       vI=toCompVect(i,sz);
       if( ((vI<h.r) || (h.r<vI) )&& (vI.sum()==GL_OnlyAcceptableNumAs)){
         res[vI]=findFlipThatHitsTheTarget(vI,nha);
       }
       ++i;
     }
     res[createBaseEnvironment(h.r.size())]=-1;
     if(indDoTheRepairs==1){repairEnvironments(res);}
     return res;
   }
   template<typename T>
   std::string EvaluationsForOneEnvironment<T>::toString() const{
     std::string res; 
     for(long i=0;i<eOne.size();++i){
        res+=std::to_string(i)+"->"+(eOne[i]).toString()+",\n";
     }
     return res;
   }
   template<typename T>
   std::string EvaluationsForAllEnvironments<T>::toString() const{
     std::string res;
     typename std::map<CompVector<T>, EvaluationsForOneEnvironment<T> >::const_iterator it,itE;
     it=eAll.begin();itE=eAll.end();
     while(it!=itE){
       res+=(it->first).toString()+":\n";
       res+=(it->second).toString()+"\n";
       ++it;
     }
     return res;
   }
   template<typename T>
   std::string MainEvaluator<T>::toString() const{
      std::string res;
      res+="\n***** Main graph *****\n"+mG.toString();
      res+="\n***** All environment evaluations *****\n"+eAE.toString();
      if(errorMessages==""){
        res+="\n***** No error messages *****\n";
      }
      else{
        res+="\n***** Error messages: *****\n"+errorMessages;
      }
      res+="Number of critical errors: "+std::to_string(criticalErrors)+"\n";
      res+="Remaining environments: \n";
      for(long i=0;i<remainingEnvironments.size();++i){
        res+="***** N(b)="+std::to_string(i)+"\n"; 
        for(long j=0;j<remainingEnvironments[i].size();++j){
          res+=(remainingEnvironments[i])[j].toString()+" ";
        }
        res+="\n";
      }
      return res;
   }
   template<typename T>
   std::string MainEvaluatorDynamicBackTracking<T>::toString() const{
      std::string res; 
      res+="\n***** Backgracking - all environment evaluations *****\n"+eAE.toString();
      res+="Remaining environments: \n";
      for(long i=0;i<remainingEnvironments.size();++i){
        res+="***** N(b)="+std::to_string(i)+"\n"; 
        for(long j=0;j<remainingEnvironments[i].size();++j){
          res+=(remainingEnvironments[i])[j].toString()+" ";
        }
        res+="\n";
      }
      return res;
   }
   std::pair<int,LBAMV::LinCombination<long> > getAcceptablePathSegment(const std::map<CompVector<long>,DirectPathSegment<long> > &possibleSegments, const CompVector<long>& env){
    std::pair<int,LBAMV::LinCombination<long> > res;
    std::map<CompVector<long>,DirectPathSegment<long> >::const_iterator it,itE;
    it=possibleSegments.begin(); itE=possibleSegments.end();
    res.first=0;
    while((it!=itE)&&(res.first==0)){
      if((it->second).restrictionsSatisfied(env)){
        res.first=1;
        res.second=(it->second).cost;
      }
      ++it;
    }
    return res;
   }
   LBAMV::LinCombination<long> straightforwardEvaluationLinComb(const CompVector<long>& env, const MainGraph<long>& mG){
      LBAMV::LinCombination<long> empty;
      LBAMV::LinCombination<long> res;
      LBAMV::Monomial<long> m_totalAs;
      m_totalAs.name='a';m_totalAs.c=0;
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::const_iterator it;
      CompVector<long> nextEdge;
      nextEdge.resize(2);
      nextEdge[0]=0;nextEdge[1]=1;
      long vertexReached=0;
      long destination=env.size()+1;
      while(vertexReached<destination){
        while( (nextEdge[1]<destination) && (env[nextEdge[1]-1]==1) ){
          nextEdge[1]=nextEdge[1]+1;
        }
        it=(mG.g).find(nextEdge);
        if( it==(mG.g).end() ){return empty;}
        std::pair<int, LBAMV::LinCombination<long> > p=getAcceptablePathSegment(it->second,env);
        if(p.first==0){return empty;}
        m_totalAs.c+=1;
        res+=p.second;
        vertexReached=nextEdge[1];
        nextEdge[0]=nextEdge[1];
        nextEdge[1]+=1;
      }
      m_totalAs.c-=1;
      LBAMV::LinCombination<long> totalAs;
      totalAs.terms.insert(m_totalAs);
      res+=totalAs;
      return res;
   }
   EvaluationsForOneEnvironment<long> straightforwardEvaluation(const CompVector<long>& env, const MainGraph<long>& mG){
      EvaluationsForOneEnvironment<long> res; 
      res.eOne.insert(straightforwardEvaluationLinComb(env,mG));
      return res;
   }
   EvaluationsForAllEnvironments<long> createInitialEvaluations(const MainGraph<long>& mG, const CompVector<long> env){
      EvaluationsForAllEnvironments<long> res;
      res.eAll[env] = straightforwardEvaluation(env,mG);
      return res;
   }
   void straightforwardUpdate(EvaluationsForAllEnvironments<long>& e, const MainGraph<long>& mG, const CompVector<long> env){
      e.eAll[env] = straightforwardEvaluation(env,mG);
   }
   int isA(long num, const CompVector<long>& env){
    if(num==0){return 1;}
    if(num>env.size()){return 1;}
    if(env[num-1]==0){return 1;}
    return 0;
   }
   MainGraph<long> subgraphOfAs(const MainGraph<long>& mG,const CompVector<long>& env){
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::const_iterator it;
      it=mG.g.begin();
      MainGraph<long> res;
      while(it!=mG.g.end()){
        if((isA(it->first[0],env))&&(isA(it->first[1],env))){
          res.g[it->first]=it->second;
        }
        ++it;
      }
      return res;
   }
   void removeDoubleEdges(std::map<CompVector<long>,DirectPathSegment<long> >& m, const CompVector<long>& env){
      if(m.size()<2){return;}
      if(m.find(env)==m.end()){return; }
      std::map<CompVector<long>,DirectPathSegment<long> >::iterator it,itE;
      while(m.size()>1){
        it=m.find(env);
        if(it==m.begin()){
          ++it;
        }
        else{
          --it;
        }
        m.erase(it->first);
      }
   }
   void removeDoubleEdges(MainGraph<long>& mg,const CompVector<long>& env){
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::iterator it=mg.g.begin(),itE=mg.g.end();
      while(it!=itE){
          removeDoubleEdges(it->second,env);
        ++it;
      }
   }
   void updateNeighbors(std::map<long,ssm::set<long> >& m, const CompVector<long>& e){
      if(m.find(e[0])==m.end()){
        ssm::set<long> tmp;
        tmp.insert(e[1]);
        m[e[0]]=tmp;
        return;
      }
      m[e[0]].insert(e[1]);
   }
   std::map<long,ssm::set<long> > getNeighbors(const MainGraph<long>& g){
      std::map<long,ssm::set<long> > res;
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::const_iterator it,itE;
      it=g.g.begin();itE=g.g.end();
      while(it!=itE){
        updateNeighbors(res,it->first);
        ++it;
      }
      return res;
   }
   ssm::set<long> getNeighbors(const std::map<long,ssm::set<long> >& nbAll,long rho){
    std::map<long,ssm::set<long> >::const_iterator it;
    it=nbAll.find(rho);
    if(it==nbAll.end()){ssm::set<long> empty; return empty;}
    return it->second;
   }
   std::map<long, DirectPathSegment<long> > getAllPassageTimes(const MainGraph<long>& mg, long start, long end,const CompVector<long>& env){
      std::map<long, DirectPathSegment<long> > res;
      CompVector<long> tmp; tmp.resize(2);tmp[0]=start;tmp[1]=end;
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::const_iterator itM;
      itM=mg.g.find(tmp);
      if(itM==mg.g.end()){return res;}
      std::map<CompVector<long>,DirectPathSegment<long> >::const_iterator it,itE;
      it=(itM->second).begin(); itE=(itM->second).end();
      long i=0;
      while(it!=itE){
        if((it->second).restrictionsSatisfied(env)){
          res[i]=it->second;
          ++i;
        }
        ++it;
      }
      return res;
   }
   void updatePassageTimes(std::map<CompVector<long>,DirectPathSegment<long> >& m, const DirectPathSegment<long>& cmb){
      std::map<CompVector<long>,DirectPathSegment<long> >::iterator it=m.begin(),itE=m.end();
      while(it!=itE){
        if( ((it->second).cost).partialOrderLEQ(cmb.cost) ){
          return;
        }
        if( (cmb.cost).partialOrderLNEQ((it->second).cost) ){
          (it->second).cost=cmb.cost;
          return;
        }
        ++it;
      }
      CompVector<long> newName;newName.resize(1);
      newName[0]=m.size();
      m[newName]=cmb;
   }
   void updatePassageTimes(MainGraph<long>& mg, const DirectPathSegment<long>& cmb, long dest){
      CompVector<long> tmp;
      tmp.resize(2); tmp[0]=0;tmp[1]=dest;
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::iterator it;
      it=mg.g.find(tmp);
      if(it==mg.g.end()){
        std::map<CompVector<long>,DirectPathSegment<long> > mn;
        CompVector<long> q;
        q.resize(1);q[0]=0;
        mn[q]=cmb;
        mg.g[tmp]=mn;
        return;
      }
      updatePassageTimes(it->second,cmb);
   }
   void updatePassageTimes(MainGraph<long>& mg,const DirectPathSegment<long>& f, const DirectPathSegment<long>& s, long dest){
      DirectPathSegment<long> combinedTime;
      LBAMV::Monomial<long> oneAM("a",1);
      combinedTime.cost.terms.insert(oneAM);
      combinedTime.cost+=f.cost;
      combinedTime.cost+=s.cost;
      combinedTime.restrictions=f.restrictions;
      std::map<long,long>::const_iterator it=s.restrictions.begin(),itE=s.restrictions.end(),itCTR;
      while(it!=itE){
        itCTR=(combinedTime.restrictions).find(it->first);
        if(itCTR==(combinedTime.restrictions).end()){
          combinedTime.restrictions[it->first]=it->second;
        }
        else{
          if(itCTR->second!=it->second){return;}
        }
        ++it;
      }
      updatePassageTimes(mg,combinedTime,dest);
   }
   void updatePassageTimes(MainGraph<long>& mg,const std::map<long, DirectPathSegment<long> >& f, std::map<long, DirectPathSegment<long> >& s,long dest){
      std::map<long, DirectPathSegment<long> >::const_iterator itF,itFE,itS,itSE;
      itF=f.begin();itFE=f.end();itS=s.begin();itSE=s.end(); 
      std::string debSt;
      while(itF!=itFE){
        itS=s.begin();
        while(itS!=itSE){ 
          updatePassageTimes(mg,itF->second,itS->second,dest);
          ++itS;
        }
        ++itF;
      } 
   }
   void updatePassageTimes(MainGraph<long>& mg, long intermediateStop, long destination,const CompVector<long>& env){
      std::map<long, DirectPathSegment<long> > firstPiece= getAllPassageTimes(mg,0,intermediateStop,env);
      if(firstPiece.size()<1){return;}
      std::map<long, DirectPathSegment<long> > secondPiece= getAllPassageTimes(mg,intermediateStop,destination,env);
      if(secondPiece.size()<1){return;} 
      updatePassageTimes(mg,firstPiece,secondPiece,destination);
   }
   std::map<CompVector<long>,DirectPathSegment<long> > shortestPathThroughAs(EvaluationsForAllEnvironments<long>& e,const MainGraph<long>& mG,const CompVector<long>& env){
      MainGraph<long> g=subgraphOfAs(mG,env);
      removeDoubleEdges(g,env);
      std::map<long,ssm::set<long> > originalNeighbors=getNeighbors(g);
      ssm::set<long> researched, toResearch;
      toResearch.insert(0);
      LBAMV::LinCombination<long> empty;
      while(toResearch.size()>0){
        long rho=toResearch[0];long nbNext; 
        ssm::set<long> neighborsOfRho=getNeighbors(originalNeighbors,rho); 
        for(long j=0;j<neighborsOfRho.size();++j){
          nbNext=neighborsOfRho[j]; 
          updatePassageTimes(g,rho,nbNext,env);
          toResearch.insert(nbNext);
        }
        toResearch.erase(rho);
      }
      std::map<CompVector<long>,DirectPathSegment<long> > emptyRet;
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::const_iterator it;
      CompVector<long> startToEnd; startToEnd.resize(2);
      startToEnd[0]=0;startToEnd[1]=env.size()+1;
      it=g.g.find(startToEnd);
      if(it==g.g.end()){return emptyRet;}
      return it->second;
   }
   void updateMainGraphEdge(std::map<CompVector<long>,DirectPathSegment<long> >& currentEdges,const CompVector<long>& env, long start, long end, long restrictionInd, std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > >& rM){
      currentEdges[env]=simpleSegmentMap(env,start,end,restrictionInd,rM)[env];
   }
   void straightforwardGraphUpdate(MainGraph<long>& mG, const CompVector<long>& env, long restrictionInd,std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > >& rM){
      CompVector<long> nextEdge;
      nextEdge.resize(2);
      nextEdge[0]=0;nextEdge[1]=1;
      long vertexReached=0;
      long destination=env.size()+1;
      std::map<CompVector<long>, std::map<CompVector<long>,DirectPathSegment<long> > >::iterator it;
      while(vertexReached<destination){
        while( (nextEdge[1]<destination) && ( (env[nextEdge[1]-1]==1) || (nextEdge[1]-1==restrictionInd) ) ){
          nextEdge[1]=nextEdge[1]+1;
        }
        if(nextEdge[1]-nextEdge[0]>1){
          it=(mG.g).find(nextEdge);
          if( it == (mG.g).end() ){
            (mG.g)[nextEdge]=simpleSegmentMap(env,nextEdge[0],nextEdge[1],restrictionInd,rM);
          }
          else{
            if( (restrictionInd+1>nextEdge[0])&&(restrictionInd+1<nextEdge[1]) ){
              updateMainGraphEdge(it->second,env,nextEdge[0],nextEdge[1],restrictionInd,rM); 
            }
          }
        }
        vertexReached=nextEdge[1];
        nextEdge[0]=nextEdge[1];
        nextEdge[1]+=1;
      }
   }
  BestEvaluationWithErrorMessage<long> chooseFirstEvaluationIfMany(const std::map<CompVector<long>,DirectPathSegment<long> > & sp){
    BestEvaluationWithErrorMessage<long> res;
    if(sp.size()<1){
      res.errorMessage="Error: No paths";
      return res;
    }
    if(sp.size()>1){
      res.errorMessage="Warning: Multiple paths. Chosen the first one";
    } 
    res.bestEv.eOne.insert(((sp.begin())->second).cost);
    return res;
  }
  BestEvaluationWithErrorMessage<long> chooseEvaluationThatContainsMonomial(const std::map<CompVector<long>,DirectPathSegment<long> > & sp,const LBAMV::Monomial<long> & m){
    BestEvaluationWithErrorMessage<long> res;
    if(sp.size()<1){
      res.errorMessage="Error: No paths";
      return res;
    }
    std::map<CompVector<long>,DirectPathSegment<long> >::const_iterator it=sp.begin();
    long numFound=0;
    while(it!=sp.end()){
      if( (it->second).cost.terms.find(m)>-1 ){
        if(numFound==0){ 
          res.bestEv.eOne.insert((it->second).cost);
        }
        ++numFound; 
      }
      ++it;
    }
    if(numFound==0){ 
      res.bestEv.eOne.insert( ((sp.begin())->second).cost);
      res.errorMessage="Warning: No path that contains restricted environment.";
    }
    if(numFound>1){
      res.errorMessage="Warning: Multiple paths that contain restricted environment. Chosen the first one.";
    }
    return res;
  }
  BestEvaluationWithErrorMessage<long> chooseBestEvaluationIfMany(const std::map<CompVector<long>,DirectPathSegment<long> > & sp, const std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > >& rM, const CompVector<long>& env){
    std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > >::const_iterator it;
    it=rM.find(env);
    if(it==rM.end()){
      return chooseFirstEvaluationIfMany(sp);
    }
    if((it->second).size()<1){
      return chooseFirstEvaluationIfMany(sp);
    }
    return chooseEvaluationThatContainsMonomial(sp, *(it->second).begin()); 
   } 
   long isNumberOfZeroesOdd(const CompVector<long>& v){ 
    return (v.size()-v.sum())%2;
   }
   LBAMV::LinCombination<long> bMinusA(){
      LBAMV::Monomial<long> b,ma;
      b.name="b";ma.name="a";
      b.c=1;ma.c=-1;
      LBAMV::LinCombination<long> res;
      res.terms.insert(b);res.terms.insert(ma);
      return res;
   }
   EvaluationsForOneEnvironment<long> verySimpleEvaluationForOneEnvironment(const std::string& mName, long numOfBMinusA){
      EvaluationsForOneEnvironment<long> x;
      LBAMV::Monomial<long> envMonomial;
      LBAMV::LinCombination<long> lC;
      envMonomial.name=mName;
      envMonomial.c=1;
      lC.terms.insert(envMonomial);
      if(numOfBMinusA!=0){
        LBAMV::LinCombination<long> bma=bMinusA();
        if(numOfBMinusA!=1){bma*=numOfBMinusA;}
        lC+=bma;
      }
      x.eOne.insert(lC);
      return x;
   }
   void updateHelpfulPair(std::map<CompVector<long>, EvaluationsForOneEnvironment<long> >& e, const HelpfulnessIndicators<long>& h){
      EvaluationsForOneEnvironment<long> x=verySimpleEvaluationForOneEnvironment(GL_environmentAbbreviation+h.r.toString(),0);
      e[h.r]=x;
      CompVector<long> nha=negativelyHelpfulAssociate(h);
      if(!( (nha<h.r) || (h.r<nha) )){return;} 
      long sh=(h.r).sum();
      long snha=nha.sum();
      if(snha>sh){
        e[nha]=x;
      }
      else{ 
        e[nha]=verySimpleEvaluationForOneEnvironment(GL_environmentAbbreviation+h.r.toString(),-1);
      }
   } 
   std::vector<ssm::set<CompVector<long> > > getAllEnvironments(long m){
    std::vector<ssm::set<CompVector<long> > > res;
    if(m<1){return res;}
    res.resize(m+1);
    long bound=twoToPower(m)+1;
    long i=0;
    CompVector<long> tmp;
    while(i<bound){
      tmp=toCompVect(i,m); 
      res[tmp.sum()].insert(tmp);
      ++i;
    }
    return res;
   }
   void removeEvaluatedEnvironments(std::vector<ssm::set<CompVector<long> > >& v, const std::map<CompVector<long>, EvaluationsForOneEnvironment<long> >& e){
    std::map<CompVector<long>, EvaluationsForOneEnvironment<long> >::const_iterator it=e.begin(),itE=e.end();
    while(it!=itE){ 
      v[(it->first).sum()].erase(it->first);
      ++it;
    }
   } 
   ssm::set<LBAMV::LinCombination<long> > chooseBestSegmentCosts(const std::map<CompVector<long>,DirectPathSegment<long> >& sp,long numberOfPathsToInclude){
      ssm::set<LBAMV::LinCombination<long> > res;
      if(sp.size()<1){return res;}
      std::map<CompVector<long>,DirectPathSegment<long> >::const_iterator it=sp.begin(); 
      long sz=sp.size();
      if(numberOfPathsToInclude<0){
        numberOfPathsToInclude=sz;
      }
      if(numberOfPathsToInclude>sz){
        numberOfPathsToInclude=sz;
      }
      long i=0;
      while(i<numberOfPathsToInclude){
        res.insert((it->second).cost);
        ++i;++it;
      }
      return res; 
   }
   int attemptObvious(MainEvaluator<long>& res, const CompVector<long>& env,long numberOfPathsToInclude){
    std::map<CompVector<long>,DirectPathSegment<long> > sp=shortestPathThroughAs(res.eAE,res.mG,env); 
    if(sp.size()>0){ 
      EvaluationsForOneEnvironment<long> t; 
      t.eOne=chooseBestSegmentCosts(sp,numberOfPathsToInclude);
      res.eAE.eAll[env]=t; 
      return 1;
    } 
    return 0;
   }
   void attemptObvious(MainEvaluator<long>& res, ssm::set<CompVector<long> >& remainingEnvs,long numberOfPathsToInclude){
      ssm::set<CompVector<long> > rECopy=remainingEnvs;
      long i=0;
      CompVector<long> current;
      while(i<rECopy.size()){
        current=rECopy[i];
        int succ=attemptObvious(res,current,numberOfPathsToInclude);
        if(succ){
          remainingEnvs.erase(current);
        }
        ++i;
      }
   }  
   MainEvaluator<long> createME(const HelpfulnessIndicators<long>& h){
      MainEvaluator<long> res;
      std::map<CompVector<long>,std::set<LBAMV::Monomial<long> > > restrictedMonomials;
      res.mG=createInitialGraph(h.r.size());
      CompVector<long> bE=createBaseEnvironment(h.r.size());
      res.eAE=createInitialEvaluations(res.mG,bE);
      std::map< CompVector<long> , long > vp2=splitTheSetVPlus2(h);
      std::map< CompVector<long> , long >::const_iterator it,itE=vp2.end();
      it=vp2.begin();
      while(it!=itE){
        if(it->second==-1){
          straightforwardGraphUpdate(res.mG,it->first,it->second,restrictedMonomials);
          straightforwardUpdate(res.eAE,res.mG,it->first);
        }
        ++it;
      }
      MainEvaluator<long> savedRes=res;
      it=vp2.begin();
      while(it!=itE){
        if(it->second!=-1){
          straightforwardGraphUpdate(res.mG,it->first,it->second,restrictedMonomials);
        }
        ++it;
      }
      it=vp2.begin();
      while(it!=itE){
        if(it->second!=-1){ 
          std::map<CompVector<long>,DirectPathSegment<long> > sp=shortestPathThroughAs(res.eAE,res.mG,it->first);
          BestEvaluationWithErrorMessage<long> bEWithErrorM=chooseBestEvaluationIfMany(sp,restrictedMonomials,it->first);
          res.eAE.eAll[it->first]=bEWithErrorM.bestEv;
          if(bEWithErrorM.errorMessage!=""){res.errorMessages+=bEWithErrorM.errorMessage+"\n";}
        }
        ++it;
      }
      updateHelpfulPair(res.eAE.eAll,h);
      res.remainingEnvironments=getAllEnvironments(h.r.size());
      removeEvaluatedEnvironments(res.remainingEnvironments,res.eAE.eAll); 
      //(1a 3b)
      attemptObvious(res,res.remainingEnvironments[3],1);
      //(3a,1b)
      attemptObvious(res,res.remainingEnvironments[1],-1);
      res.criticalErrors=0;
      for(long i=0;i<res.remainingEnvironments.size()-2;++i){
        if(res.remainingEnvironments[i].size()>0){
          res.errorMessages+="Error: Was not able to find suitable paths in environments where N(b)="+std::to_string(i)+"\n";
          ++res.criticalErrors;
        }
      }
      return res;
   }
  EvaluationsForAllEnvironments<long> selectCorrectElements(const EvaluationsForAllEnvironments<long>& in, const CompVector<long>& indChosen){
    EvaluationsForAllEnvironments<long> res=in;
    long twoToM=res.eAll.size();
    std::map<CompVector<long>, EvaluationsForOneEnvironment<long> >::iterator it=res.eAll.begin(); 
    long i=0;
    while(i<twoToM){
      if((it->second).eOne.size()>1){
        ssm::set<LBAMV::LinCombination<long> > oneElSeq;
        oneElSeq.insert((it->second).eOne[indChosen[i]]);
        (it->second).eOne=oneElSeq;
      }
      ++i;++it;
    }
    return res;
  }
  long getLowerBoundForAllT(const LBAMV::LinCombination<long>& x){
    long res=0;
    LBAMV::Monomial<long> current;
    for(long i=0;i<x.terms.size();++i){
      current=x.terms[i];
      if( (current.name!="a") && (current.name!="b") ){
        if(current.c<0){
          res+=current.c;
        }
      }
    }
    return res;
  } 
  long getBMAComponent(const LBAMV::LinCombination<long>& x){
    return x.getComponent("b"); 
  }
  int doesTheBoundHold(const LBAMV::LinCombination<long>& envDerivativeF,long desiredLowerBound){ 
    return getLowerBoundForAllT(envDerivativeF)+getBMAComponent(envDerivativeF)>=desiredLowerBound;
  }
  std::pair<int, LBAMV::LinCombination<long> > doesTheBoundHold(const MainEvaluatorDynamicBackTracking<long>& me,long desiredLowerBound,const CompVector<long>& indChoices){
    LBAMV::LinCombination<long> envDerivativeF,currentValue;
    long twoToM=me.eAE.eAll.size();
    long i=0;
    std::map<CompVector<long>, EvaluationsForOneEnvironment<long> >::const_iterator it=me.eAE.eAll.begin(); 
    while(i<twoToM){
      currentValue=((it->second).eOne)[indChoices[i]];
      if(isNumberOfZeroesOdd(it->first)){
        currentValue*=-1;
      }
      envDerivativeF+=currentValue;
      ++i;++it;
    }
    std::pair<int, LBAMV::LinCombination<long> > res;
    res.first=doesTheBoundHold(envDerivativeF,desiredLowerBound);
    if(res.first){res.second=envDerivativeF;}
    return res;
  }
  LowerBoundProofData<long> lowerBoundSearchForProofGraphIsReady(const MainEvaluatorDynamicBackTracking<long>& me,long desiredLowerBound){
    LowerBoundProofData<long> res;
    CompVector<long> ind,bounds;
    long twoToM=me.eAE.eAll.size();
    ind.resize(twoToM);
    bounds.resize(twoToM);
    std::map<CompVector<long>, EvaluationsForOneEnvironment<long> >::const_iterator it=me.eAE.eAll.begin(); 
    for(long i=0;i<twoToM;++i){
      ind[i]=0;bounds[i]=(it->second).eOne.size(); 
      ++it;
    } 
    long reachedTheEnd=0;
    std::pair<int, LBAMV::LinCombination<long> > pFound;
    while((reachedTheEnd==0)&&(res.proofFound==0)){
      pFound=doesTheBoundHold(me,desiredLowerBound,ind);
      res.proofFound=pFound.first;
      if(res.proofFound==1){
        res.envDerivativeF=pFound.second;
        res.eAE=selectCorrectElements(me.eAE,ind);
      }
      reachedTheEnd=MDINV::incrementMultiDimensionalIndex(ind,bounds);
    }
    GL_DEB_totalPrint+= me.toString()+"\n";
    return res;
  }
  LowerBoundProofData<long> lowerBoundSearchForProof(MainEvaluatorDynamicBackTracking<long>& me, long desiredLowerBound){
    if(me.remainingEnvironments[3].size()<1){
      return lowerBoundSearchForProofGraphIsReady(me,desiredLowerBound);
    }
    LowerBoundProofData<long> lD;
    CompVector<long> attemptToMatch=(me.remainingEnvironments[3])[0];
    CompVector<long> unhelpfulPair;
    (me.remainingEnvironments[3]).erase(attemptToMatch);
    me.eAE.eAll[attemptToMatch]=verySimpleEvaluationForOneEnvironment(GL_environmentAbbreviation+attemptToMatch.toString(),0);
    EvaluationsForOneEnvironment<long> envUnhelpfulMatch=verySimpleEvaluationForOneEnvironment(GL_environmentAbbreviation+attemptToMatch.toString(),-1);
    long i=0;
    long m=attemptToMatch.size();
    while((i<m)&&(lD.proofFound==0)){
      if(attemptToMatch[i]==1){
        unhelpfulPair=attemptToMatch;
        unhelpfulPair[i]=0; 
        EvaluationsForOneEnvironment<long> save=me.eAE.eAll[unhelpfulPair];
        if(save.eOne.size()>0){
          if( (save.eOne)[0].terms.size()>4){
            me.eAE.eAll[unhelpfulPair]=envUnhelpfulMatch;
            lD=lowerBoundSearchForProof(me,desiredLowerBound);
            me.eAE.eAll[unhelpfulPair]=save;
          }
        }
      }
      ++i;
    }
    me.eAE.eAll.erase(attemptToMatch);
    (me.remainingEnvironments[3]).insert(attemptToMatch);
    return lD;
  }
  LowerBoundProofData<long> lowerBoundSearchForProof(MainEvaluatorDynamicBackTracking<long> me, const CompVector<long>& env3ToBBBB, long desiredLowerBound){
    CompVector<long> envBBBB=(me.remainingEnvironments[4])[0];
    (me.remainingEnvironments[4]).clear();
    (me.remainingEnvironments[3]).erase(env3ToBBBB);
    me.eAE.eAll[envBBBB]=verySimpleEvaluationForOneEnvironment(GL_environmentAbbreviation+envBBBB.toString(),0);
    me.eAE.eAll[env3ToBBBB]=me.eAE.eAll[envBBBB];
    return lowerBoundSearchForProof(me,desiredLowerBound); 
  }
  LowerBoundProofData<long> lowerBoundSearchForProof(const HelpfulnessIndicators<long>& h,long desiredLowerBound){
    MainEvaluator<long> me=createME(h);
    GL_DEB_totalPrint+=me.toString()+"\n";
    MainEvaluatorFixed<long> meF;
    MainEvaluatorDynamicBackTracking<long> meD;
    meF.mG=me.mG;
    meD.eAE=me.eAE;
    meD.remainingEnvironments=me.remainingEnvironments;
    LowerBoundProofData<long> lD;
    long i=0;
    while((lD.proofFound==0)&&(i<meD.remainingEnvironments[3].size())){
      lD=lowerBoundSearchForProof(meD,(meD.remainingEnvironments[3])[i],desiredLowerBound);
      ++i;
    }
    return lD;
  }
   HelpfulnessIndicators<long> oneHelpIndFromString(const std::string& s){
     HelpfulnessIndicators<long> res;
     std::map<long,long> rMap,hMap;
     long rI=0,hI=0,sI=0;
     long sz=s.length();
     while(sI<sz){
       if( (s[sI]=='a')||(s[sI]=='A') ){rMap[rI]=0;++rI;}
       if( (s[sI]=='b')||(s[sI]=='B') ){rMap[rI]=1;++rI;}
       if( (s[sI]=='0') || (s[sI]=='1') ){hMap[hI]=static_cast<long>(s[sI])-static_cast<long>('0');++hI;}
       ++sI;
     }
     while(hI<rI){
       hMap[hI]=0;++hI;
     }
     res.r.resize(rI);
     res.hIndicators.resize(rI);
     for(long i=0;i<rI;++i){
       res.r[i]=rMap[i];
       res.hIndicators[i]=hMap[i];
     }
     return res;
   }
   std::map<std::string,HelpfulnessIndicators<long> > fromString(const std::string& s){
     std::map<std::string,std::string> raws=SF::stringToMap(s,"_k_","_/k_","_v_","_/v_");
     std::map<std::string,std::string>::const_iterator it=raws.begin(),itE=raws.end();
     std::map<std::string,HelpfulnessIndicators<long> > res;
     while(it!=itE){
       res[it->first]=oneHelpIndFromString(it->second);
       ++it;
     }
     return res;
   }
   template<typename T>
   CompVector<T> reverse(const CompVector<T>& in){
      CompVector<T> out=in;
      for(long i=0;i<in.size();++i){out[i]=in[in.size()-i-1];}
      return out;
   }
   HelpfulnessIndicators<long> reverse(const HelpfulnessIndicators<long>& in){
      HelpfulnessIndicators<long> out;
      out.r=reverse(in.r);
      out.hIndicators=reverse(in.hIndicators);
      return out;
   }
   ssm::set<HelpfulnessIndicators<long> > generateHelpfulnessIndicators(long m=GL_OnlyAcceptableM){
      m=GL_OnlyAcceptableM;
      ssm::set<HelpfulnessIndicators<long> > res;
      HelpfulnessIndicators<long> tmp;
      tmp.r.resize(m);
      tmp.hIndicators.resize(m);
      for(long i=0;i<m;++i){tmp.r[i]=0;tmp.hIndicators[i]=0;}
      long bound=twoToPower(m);
      for(long i=0;i<bound;++i){
        tmp.r=toCompVect(i,m);
        if((tmp.r).sum()==GL_OnlyAcceptableNumAs){
          for(long j=0;j<m;++j){
            tmp.hIndicators[j]=1;
            if( (res.find(reverse(tmp))==-1) ){
              res.insert(tmp);
            }
            tmp.hIndicators[j]=0;
          }
        } 
      }
      return res;
   }
}

#endif
