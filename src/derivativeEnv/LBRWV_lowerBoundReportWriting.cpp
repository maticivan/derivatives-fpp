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

#ifndef _INCL_LBRWV_CPP
#define _INCL_LBRWV_CPP
namespace LBRWV{   
  std::string WritingData::translate(const std::string& k) const{
    std::string res;
    std::map<std::string,std::string>::const_iterator it=tMap.find(k);
    if(it==tMap.end()){return "Translation not found for "+k;}
    return it->second;
  }
  std::string getABstring(const LBLCV::CompVector<long>& r,const std::string& open, const std::string& close, const std::string& separator){
    if(r.size()<1){return "";}
    std::string res=open;
    int printedAlready=0;
    for(long i=0;i<r.size();++i){
      if(printedAlready){res+=separator;}
      printedAlready=1;
      if(r[i]==0){
        res+="a";
      }
      else{
        res+="b";
      }
    }
    return res+close;
  }
  std::string sigmaString(const LBLCV::CompVector<long>& r){
    return "\\sigma^{"+getABstring(r,"(",")",",")+"}";
  }
  std::string sigmaOmega(const LBLCV::CompVector<long>& r){
    return sigmaString(r)+"(\\omega)";
  }
  std::string fSigmaOmega(const LBLCV::CompVector<long>& r){
    return "f("+sigmaOmega(r)+")";
  }
  std::string makeTheta(long from,long to, const LBLCV::CompVector<long> env, long rest){
    std::string res= "\\theta_{"+std::to_string(from)+std::to_string(to)+"}"+getABstring(env,"(",")",",");
    if(rest){res="\\hat"+res;}
    return res;
  }       
  NameComponents::NameComponents(const std::string& _in){
    fromString(_in);
  }
  int NameComponents::operator<(const NameComponents& oth) const{
    if(name<oth.name){return 1;}
    if(oth.name<name){return 0;}
    if(from<oth.from){return 1;}
    if(oth.from<from){return 0;}
    if(to<oth.to){return 1;}
    if(oth.to<to){return 0;}
    if(env<oth.env){return 1;}
    if(oth.env<env){return 0;}
    if(rest<oth.rest){return 1;}
    return 0;
  }
  void NameComponents::fromString(const std::string& _in){
    from=0;to=0;rest=0;
    name="";
    long zero=static_cast<long>('0');
    env.resize(LBLCV::GL_OnlyAcceptableM);
    for(long i=0;i<env.size();++i){env[i]=-1;}
    if(_in.length()<1){return;}
    if(_in[0]=='e'){
      if(_in.length()!=5){return;}
      name="e";
      from=_in[2]-zero;
      to=_in[4]-zero;
      return;
    }
    if(_in[0]=='d'){
      if(_in.length()!=LBLCV::GL_OnlyAcceptableM+3){return;}
      name="d";
      for(long i=0;i<LBLCV::GL_OnlyAcceptableM;++i){
        env[i]=_in[i+2]-zero;
      }
      return;
    }
    if(_in[0]=='t'){
      long acceptableLength=LBLCV::GL_OnlyAcceptableM+7;
      if(!((_in.length()==acceptableLength)||(_in.length()==acceptableLength+1))){
        return;
      }
      name="t";
      from=_in[2]-zero;
      to=_in[4]-zero;
      for(long i=0;i<LBLCV::GL_OnlyAcceptableM;++i){
        env[i]=_in[i+6]-zero;
      }
      if(_in.length()==acceptableLength+1){
        rest=1;
      } 
    }
    return;
   }
  std::string toLatex(std::map<LBLCV::CompVector<long>, ssm::set<NameComponents> >& rTh,ssm::set<std::string>&  p, ssm::set<std::string>&  pH,const std::string& monName){
    if((monName=="a")||(monName=="b")){return monName;}
    NameComponents nc(monName);
    if(nc.name=="e"){
      return "e_{"+std::to_string(nc.from)+std::to_string(nc.to)+"}";
    }
    if(nc.name=="d"){
      return fSigmaOmega(nc.env);
    }
    if(nc.name=="t"){
      std::string th=makeTheta(nc.from,nc.to,nc.env,nc.rest);
      LBLCV::CompVector<long> thetaVector;
      thetaVector.resize(2);
      thetaVector[0]=nc.from;
      thetaVector[1]=nc.to;
      rTh[thetaVector].insert(nc);
      if(nc.rest){
        pH.insert(th);
      }
      else{
        p.insert(th);
      }
      return th;
    }
    return "";
  }
  std::string toLatex(std::map<LBLCV::CompVector<long>,ssm::set<NameComponents> >& rTh,ssm::set<std::string>&  p, ssm::set<std::string>&  pH, const LBAMV::Monomial<long>& m, int printedAlready){
    std::string sgn="";
    if(m.c<0){
      sgn="-";
    }
    else{
      if(printedAlready){
        sgn="+";
      }
    }
    std::string cS;
    long cL=m.c;
    if(cL<0){cL*=-1;}
    if(cL>1){cS=std::to_string(cL);}
    std::string monName=toLatex(rTh,p, pH, m.name);
    if(monName==""){return "";}
    return sgn+cS+monName;
  }
  std::string toLatex(std::map<LBLCV::CompVector<long>,ssm::set<NameComponents> >& rTh, ssm::set<std::string>&  p, ssm::set<std::string>&  pH, const LBAMV::LinCombination<long>& lC){
    std::string res;
    for(long i=0;i<lC.terms.size();++i){
      res+=toLatex(rTh,p,pH,lC.terms[i],i!=0);
    }
    return res;
  }
  std::string ineqSign(long numBs,int omegaAppearsOnTheRHS){
    if( (numBs==2) && (omegaAppearsOnTheRHS==0) ){return "=";}
    if(numBs%2==0){return "\\geq";}
    return "\\leq";
  }
  void WritingData::addEquationForOneEnvironment(const LBLCV::CompVector<long>& env,const ssm::set<LBAMV::LinCombination<long> >& st){
    long numBs=env.sum();
    std::string left=fSigmaOmega(env);
    std::string right=toLatex(rawThetas,parameters,parametersH,st[0]);
    if(left!=right){
      std::map<long,ssm::set<std::string> >::const_iterator it=inequalities.find(numBs);
      if(it==inequalities.end()){
        ssm::set<std::string> empty;
        inequalities[numBs]=empty;
      }
      inequalities[numBs].insert(left+" & "+ineqSign(numBs,right!=SF::findAndReplace(right,"omega",""))+" & "+right);
    }
  }
  void WritingData::getEquationsInequalitiesAndParameters(const LBLCV::LowerBoundProofData<long>& pd){
    derInequality="\\partial_Sf(\\omega)&\\geq&"+toLatex(rawThetas,parameters,parametersH, pd.envDerivativeF);
    std::map<LBLCV::CompVector<long>, LBLCV::EvaluationsForOneEnvironment<long> >::const_iterator it=pd.eAE.eAll.begin(),itE=pd.eAE.eAll.end();
    while(it!=itE){
      addEquationForOneEnvironment(it->first,(it->second).eOne);
      ++it;
    }
  }
  std::string correctSet(long alpha, long i,long complement=0){
    std::string complementAdditionE="",complementAdditionHE="^C";
    if(complement){complementAdditionE="^C";complementAdditionHE="";}
    std::string res="E_{";
    if(alpha==1){res="\\hat "+res;}
    res+=std::to_string(i+1)+"}";
    if(alpha==1){
      res+=complementAdditionHE;
    }
    else{
      res+=complementAdditionE;
    }
    return res;
  }
  std::string correctSubset(const LBLCV::HelpfulnessIndicators<long>& hI){
    std::string res;
    int printedAlready=0;
    for(long i=0;i<hI.r.size();++i){
      if(hI.hIndicators[i]==0){
        if(printedAlready){res+=" \\cap ";}
        res+=correctSet(hI.r[i],i);
        printedAlready=1;
      }
    }
    return res;
  }
  std::string badSubset(const LBLCV::HelpfulnessIndicators<long>& hI){
    long fHI=LBLCV::firstHelpfulIndex(hI);
    if((fHI<0)||(fHI>=hI.r.size())){
      return "";
    }
    return correctSet(hI.r[fHI],fHI,1); 
  }
  std::string conclusion(const LBLCV::HelpfulnessIndicators<long>& hI,int indEqnArray=0){
    std::string add="";
    if(indEqnArray){add="&";}
    return sigmaOmega(hI.r)+add+"\\in "+add+correctSubset(hI);
  }
  std::string caseDescription(const LBLCV::HelpfulnessIndicators<long>& hI,int indEqnArray=0){
    std::string add="";
    if(indEqnArray){add="&";}
    return sigmaOmega(hI.r)+add+"\\in "+add+badSubset(hI);
  }
  std::string conclusion(const LBLCV::CompVector<long>& r, long j,int indEqnArray=0){
    LBLCV::HelpfulnessIndicators<long> hI;
    hI.r=r;
    hI.hIndicators.resize(r.size());
    for(long i=0;i<r.size();++i){hI.hIndicators[i]=0;}
    if((j>-1)&&(j<r.size())){hI.hIndicators[j]=1;}
    return conclusion(hI,indEqnArray);
  }
  std::string commentsAboutTheRepair(const WritingData& wd,const LBLCV::CompVector<long>& env, long repairedIndex, long printedAlready){
    std::string res;
    if(printedAlready==0){
      res+=wd.translate("openingFirstRepair");
    }
    else{
      res+=wd.translate("openingAdditionalRepair");
    }
    res+="$"+sigmaOmega(env) +" \\in "+correctSet(env[repairedIndex],repairedIndex) + "$.";
    LBLCV::HelpfulnessIndicators<long> hTemp;
    hTemp.r=env;
    hTemp.hIndicators.resize(env.size());
    for(long i=0;i<env.size();++i){hTemp.hIndicators[i]=0;}
    res+=wd.translate("closeRepair")+"$"+conclusion(hTemp) + "$.\n";
    return res;
  }
  std::string commentsAboutTheRepair(const WritingData& wd, const std::map<LBLCV::CompVector<long> , long >& before, std::map<LBLCV::CompVector<long> , long >& after){
    std::string res;
    std::map<LBLCV::CompVector<long> , long >::const_iterator itB,itA;
    itB=before.begin();
    while(itB!=before.end()){
      if(itB->second>-1){
        itA=after.find(itB->first);
        if(itA!=after.end()){
          if(itA->second==-1){
            res+=commentsAboutTheRepair(wd,itB->first,itB->second, res.length());
          }
        }
      }
      ++itB;
    }
    return res;
  }
  std::string latexLabel(const WritingData& wd,const std::string& lbn){
    return "{eqn|"+wd.uniqueLabel+lbn+"}";
  }
  std::string summarizeEnvironment(const WritingData& wd, const std::map< LBLCV::CompVector<long> , long >& vp2, long includeEqNumbers ){
    std::string res;
    res+=wd.translate("openingEnvSummary"+std::to_string(includeEqNumbers));
    std::string lastEq=".\\nonumber \n";
    if(includeEqNumbers){lastEq=".\\label"+latexLabel(wd,"environments")+"\n";} 
    std::map< LBLCV::CompVector<long> , long >::const_iterator it=vp2.begin(),itE=vp2.end();
    while(it!=itE){ 
      res+=conclusion(it->first,it->second,1); 
      ++it;
      if(it==itE){
        res+=lastEq;
      }
      else{
        res+=";\\nonumber \\\\ \n";
      }
    }
    res+=wd.translate("closingEnvSummary"+std::to_string(includeEqNumbers));
    return res;
  }
  std::string listOfAllThetas(const WritingData& wd){
    std::string res;
    long total=wd.parameters.size()+wd.parametersH.size();
    long i=0;
    long j=0;
    res+="\\begin{eqnarray*}&& ";
    while(j<wd.parameters.size()){
      if(i==total-1){res+=", \\mbox{ and }";}
      res+=wd.parameters[j];
      if(i<total-2){res+=", ";}
      if(i==2){res+="\\\\&&";}
      ++j;++i;
    }
    j=0;
    while(j<wd.parametersH.size()){
      if(i==total-1){res+=", \\mbox{ and }";}
      res+=wd.parametersH[j];
      if(i<total-2){res+=", ";}
      ++j;++i;
    }
    res+="\\end{eqnarray*}";
    return res;
  }
  std::string listOfEqsAtLevel(const WritingData& wd, const ssm::set<std::string>& ss, long level){
    if(ss.size()<1){return "";}
    std::string res;
    res+="\\begin{eqnarray}\n";
    long counter=0;
    for(long i=0;i<ss.size();++i){
      res+=ss[i];
      if(i==ss.size()-1){
        res+=". \\label"+latexLabel(wd,"l"+std::to_string(level)+"Last");
      }
      else{
        res+=", \\label"+latexLabel(wd,"l"+std::to_string(level)+"c"+std::to_string(counter));
        res+="\\\\";
      }
      ++counter;
    }
    res+="\\end{eqnarray}\n";
    return res;
  }
  std::string listOfEqsAtLevel(const WritingData& wd, long level){
    std::map<long,ssm::set<std::string> >::const_iterator it=wd.inequalities.find(level);
    if(it==wd.inequalities.end()){return "";}
    return listOfEqsAtLevel(wd,it->second,level);
  }
  std::string summarizeEnvironment(WritingData& wd, const LBLCV::HelpfulnessIndicators<long>& hI){
    std::map< LBLCV::CompVector<long> , long > vp2=LBLCV::splitTheSetVPlus2(hI,0);
    wd.vp2Repaired=vp2;
    LBLCV::repairEnvironments(wd.vp2Repaired);
    std::string res;
    std::string cRep=commentsAboutTheRepair(wd,vp2,wd.vp2Repaired);
    if(cRep==""){
      res+=summarizeEnvironment(wd,vp2,1);}
    else{
      res+=summarizeEnvironment(wd,vp2,0)+cRep+summarizeEnvironment(wd,wd.vp2Repaired,1);
    }
    return res;
  }
  std::string conclusionFromPropositionComputer(const WritingData& wd, const LBLCV::HelpfulnessIndicators<long>& hI){
    std::string res; 
    res+=fSigmaOmega(hI.r)+"=";
    long fHI=LBLCV::firstHelpfulIndex(hI);
    if(hI.r[fHI]==1){
      res+="(b-a)+";
    }
    LBLCV::CompVector<long> flippedR=hI.r;
    flippedR[fHI]=1-flippedR[fHI];
    res+=fSigmaOmega(flippedR);
    res+=". \\label"+latexLabel(wd,"theoremForComputer");
    return res;
  }
  std::string geodesicSectionName(long f, long t){
    if(f==0){return " before the edge $v_{"+std::to_string(t)+"}$. ";}
    if(t==5){return " after the edge $v_{"+std::to_string(f)+"}$. ";}
    return " between the edges $v_{"+std::to_string(f)+"}$ and $v_{"+std::to_string(t) + "}$. ";
  }
  std::string getEStrings(long f, long t){
    std::string res;
    int printed=0;
    for(long i=f;i<t;++i){
      if(printed==1){res+="+";}
      printed=1;
      res+="e_{"+std::to_string(i)+std::to_string(i+1)+"}";
    }
    return res;
  } 
  std::string prepareGammaThetaEquation(const WritingData& wd, const NameComponents& nc,const std::string& gLabel, const std::string& tLabel){
    std::map<std::string,std::string> krMap;
    krMap["*gName*"]=gLabel;
    krMap["*enName*"]=sigmaOmega(nc.env);
    krMap["*eStrs*"]=getEStrings(nc.from,nc.to);
    krMap["*thScalar*"]="";
    krMap["*aScalar*"]="";
    if(nc.to-nc.from>2){
      std::string tScalar=std::to_string(nc.env.sum(nc.from,nc.to));if(tScalar=="1"){tScalar="";}
      krMap["*thScalar*"]=tScalar;
      tScalar=std::to_string(nc.to-nc.from-1);if(tScalar=="1"){tScalar="";}
      krMap["*aScalar*"]=tScalar;
    }
    krMap["*theta*"]=tLabel;
    return MFRF::findAndReplace(wd.translate("envAnalysis07"),krMap); 
  }
  std::string generateHatGTI(const WritingData& wd, const NameComponents& nc){
    std::string res;
    res+=wd.translate("envAnalysis02");
    res+="\\hat\\gamma"+getABstring(nc.env,"(",")",",")+"$";
    res+=wd.translate("envAnalysis03");
    res+="$"+sigmaOmega(nc.env)+"$. "; 
    res+=wd.translate("envAnalysis04");
    std::string geodesicLabel="\\hat\\gamma_{"+std::to_string(nc.from)+std::to_string(nc.to)+"}"+getABstring(nc.env,"(",")",",");
    std::string thetaLabel="\\hat\\theta_{"+std::to_string(nc.from)+std::to_string(nc.to)+"}"+getABstring(nc.env,"(",")",",");
    res+="$"+geodesicLabel+"$ ";
    res+=wd.translate("envAnalysis05");
    res+=geodesicSectionName(nc.from,nc.to);
    res+=wd.translate("envAnalysis06");
    res+="$"+thetaLabel;
    res+=prepareGammaThetaEquation(wd,nc,geodesicLabel,thetaLabel);
    res+=wd.translate("envAnalysis08HatB");
    std::map< LBLCV::CompVector<long> , long >::const_iterator it=wd.vp2Repaired.find(nc.env);
    if(it==wd.vp2Repaired.end()){
      res+=" error}$.";
    }
    else{
      res+=std::to_string(it->second+1)+"} = ";
      if(nc.env[it->second]==0){res+="a";}else{res+="b";}
      res+="$. ";
    }
    return res;
  }
  std::string generateGTI(const WritingData& wd, const NameComponents& nc){
    std::string res;
    res+=wd.translate("envAnalysis02");
    res+="\\gamma"+getABstring(nc.env,"(",")",",")+"$";
    res+=wd.translate("envAnalysis03");
    res+="$"+sigmaOmega(nc.env)+"$. "; 
    res+=wd.translate("envAnalysis04");
    std::string geodesicLabel="\\gamma_{"+std::to_string(nc.from)+std::to_string(nc.to)+"}"+getABstring(nc.env,"(",")",",");
    std::string thetaLabel="\\theta_{"+std::to_string(nc.from)+std::to_string(nc.to)+"}"+getABstring(nc.env,"(",")",",");
    res+="$"+geodesicLabel+"$ ";
    res+=wd.translate("envAnalysis05");
    res+=geodesicSectionName(nc.from,nc.to);
    res+=wd.translate("envAnalysis06");
    res+="$"+thetaLabel;
    res+=prepareGammaThetaEquation(wd,nc,geodesicLabel,thetaLabel);
    res+=wd.translate("envAnalysis08Reg");
    return res;
  }
  void addGammaThetaIntro(PictureData& pd, const WritingData& wd, const NameComponents& nc){
    if(nc.rest){
      pd.hatGammaThetaIntro.insert(generateHatGTI(wd,nc));
      return;
    }
    pd.gammaThetaIntro.insert(generateGTI(wd,nc));
  }
  void addTwoArcs(PictureData& pd, const WritingData& wd,long start, long end, const std::string& key, const ssm::set<NameComponents>& rtSS){
    std::string res;
    for(long i=0;i<rtSS.size();++i){
      res+=wd.translate(key+"a"+std::to_string(i));
      if(rtSS[i].rest==1){res+="\\hat";}
      res+="\\gamma_{";
      res+=std::to_string(start)+std::to_string(end);
      res+="}";
      res+=getABstring(rtSS[i].env,"(",")",",");
      res+="$};\n";
      addGammaThetaIntro(pd,wd,rtSS[i]);
    }
    pd.pictureString+=res;
  }
  void addArcIfNeeded(PictureData& pd, const WritingData& wd,long start, long end, const std::string& key){
    LBLCV::CompVector<long> pathId;
    pathId.resize(2);pathId[0]=start;pathId[1]=end;
    std::map<LBLCV::CompVector<long>,ssm::set<NameComponents> >::const_iterator it=wd.rawThetas.find(pathId);
    if(it==wd.rawThetas.end()){return;}
    const ssm::set<NameComponents>& rtSS=it->second;
    if(rtSS.size()>1){
      return addTwoArcs(pd,wd,start,end,key,rtSS);
    }
    std::string res;
    res+=wd.translate(key);
    if(rtSS[0].rest==1){res+="\\hat";}
    res+="\\gamma_{";
    res+=std::to_string(start)+std::to_string(end);
    res+="}";
    res+=getABstring(rtSS[0].env,"(",")",","); 
    res+="$};\n";
    addGammaThetaIntro(pd,wd,rtSS[0]);
    pd.pictureString+=res;
  }
  std::string generateGammaThetaIntroString(const WritingData& wd, const PictureData& pd){
    std::string res;
    for(long i=0;i<pd.gammaThetaIntro.size();++i){
      res+=pd.gammaThetaIntro[i];
    }
    for(long i=0;i<pd.hatGammaThetaIntro.size();++i){
      res+=pd.hatGammaThetaIntro[i];
    }
    return res;
  }
  std::string drawPicture(const WritingData& wd, const LBLCV::HelpfulnessIndicators<long>& hI){
    PictureData pd;
    addArcIfNeeded(pd,wd,0,2,"pictureGamma02B");
    addArcIfNeeded(pd,wd,0,3,"pictureGamma03B");
    addArcIfNeeded(pd,wd,0,4,"pictureGamma04B");
    addArcIfNeeded(pd,wd,1,3,"pictureGamma13B");
    addArcIfNeeded(pd,wd,1,4,"pictureGamma14B");
    addArcIfNeeded(pd,wd,1,5,"pictureGamma15B");
    addArcIfNeeded(pd,wd,2,4,"pictureGamma24B");
    addArcIfNeeded(pd,wd,2,5,"pictureGamma25B");
    addArcIfNeeded(pd,wd,3,5,"pictureGamma35B");
    std::string res;
    res+=wd.translate("pictureBegin");
    res+=pd.pictureString;
    res+=wd.translate("pictureEnd");
    res+=generateGammaThetaIntroString(wd,pd);
    return res;
  }
  std::string writeReport(const LBLCV::HelpfulnessIndicators<long>& hI, const LBLCV::LowerBoundProofData<long>& proofData ){
    std::string res; 
    WritingData wd;
    wd.uniqueLabel="cb"+BF::padded(GL_counters.sectionCounter,1000,"0")+"ce";
    wd.tMap=SF::stringToMap(IOF::fileToString("setupForProofWriting.txt"),"_k_","_/k_","_v_","_/v_");
    std::string cD=caseDescription(hI);
    res+=wd.translate("sectionName")+"$"+cD+"$}\n";
    res+=wd.translate("introduction01");
    res+=conclusionFromPropositionComputer(wd,hI);
    res+=wd.translate("introduction02");
    wd.getEquationsInequalitiesAndParameters(proofData);
    res+=summarizeEnvironment(wd,hI);
    res+=wd.translate("level0Open");
    res+="\\label"+latexLabel(wd,"env0");
    res+=wd.translate("level0Close");
    res+=drawPicture(wd,hI);
    res+=wd.translate("level2P01")+latexLabel(wd,"environments");
    res+=wd.translate("level2P02");
    res+=listOfAllThetas(wd);
    res+=wd.translate("level2P03");
    res+=listOfEqsAtLevel(wd,2);
    res+=wd.translate("level1P01");
    res+=listOfEqsAtLevel(wd,1);
    res+=wd.translate("level3P01");
    res+=listOfEqsAtLevel(wd,3);
    res+=wd.translate("concludingSentence01");
    res+="(\\ref"+latexLabel(wd,"env0")+"--\\ref"+latexLabel(wd,"l3Last")+")";
    res+=wd.translate("concludingSentence02");
    res+="\\begin{eqnarray}"+wd.derInequality+".\\nonumber\\end{eqnarray}\n"; 
    if(SF::findAndReplace(wd.derInequality,"theta","")!=wd.derInequality){
      res+=wd.translate("thetaIn0bma");
    }
    res+=wd.translate("finalParagraph01")+"$"+cD+"$"+wd.translate("finalParagraph02");
    res=SF::findAndReplace(res,"4a+e_{01}+e_{12}+e_{23}+e_{34}+e_{45}+","\\rho+");
    GL_counters.incrementCounters();
    return res;
  }
}

#endif
