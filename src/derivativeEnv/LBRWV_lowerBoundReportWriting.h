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


#ifndef _INCL_LBRWV_H
#define _INCL_LBRWV_H
namespace LBRWV{ 
  struct Counters{
  public:
    long sectionCounter=0; 
    void incrementCounters();
  } GL_counters;
  void Counters::incrementCounters(){
    ++sectionCounter;
  }  
  struct NameComponents{
  public:
    std::string name;
    long from;
    long to;
    LBLCV::CompVector<long> env;
    long rest;
    NameComponents(const std::string& ="");
    void fromString(const std::string& ="");
    int operator<(const NameComponents& ) const;
  }; 
  struct PictureData{
  public:
    std::string pictureString;
    ssm::set<std::string> gammaThetaIntro;
    ssm::set<std::string> hatGammaThetaIntro;
  };
  struct WritingData{
  public:
    std::map<std::string,std::string> tMap;
    std::string uniqueLabel;
    ssm::set<std::string> parameters;
    ssm::set<std::string> parametersH;
    std::map< LBLCV::CompVector<long> , long > vp2Repaired;
    std::map<long,ssm::set<std::string> > inequalities;
    std::map<LBLCV::CompVector<long>, ssm::set<NameComponents> > rawThetas;
    std::string derInequality;
    std::string translate(const std::string& ) const;
    void addEquationForOneEnvironment(const LBLCV::CompVector<long>& ,const ssm::set<LBAMV::LinCombination<long> >& );
    void getEquationsInequalitiesAndParameters(const LBLCV::LowerBoundProofData<long>& );
  };      


}

#endif
