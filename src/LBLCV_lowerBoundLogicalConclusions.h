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


#ifndef _INCL_LBLCV_H
#define _INCL_LBLCV_H
namespace LBLCV{
   long GL_MAX_M = 10;
   long GL_OnlyAcceptableM=4;
   long GL_OnlyAcceptableNumAs=2; 
   std::string GL_vSepOpenTag="(";
   std::string GL_vSepCloseTag=")"; 
   std::string GL_vEntrySep="";//","
   long GL_powerOfTenForPadding=10;//1000
   std::string GL_sepOpenTag="";//"_n_";
   std::string GL_sepCloseTag="";//"_/n_";
   std::string GL_environmentAbbreviation="d";//"env"
   std::string GL_DEB_totalPrint;
  template<typename T>
  class CompVector{
  private:
    std::vector<T> v;
  public:
    int operator<(const CompVector<T> &) const;
    const T& operator[](long ) const;
    T& operator[](long );
    void resize(long );
    long size() const;
    std::string toString(const std::string& =GL_vSepOpenTag, const std::string& =GL_vSepCloseTag, const std::string& =GL_vEntrySep) const;
    long sum(long =0, long =-1) const;
  };
  template<typename T>
  struct HelpfulnessIndicators{
  public:
    CompVector<T> r;
    CompVector<long> hIndicators;
    int operator<(const HelpfulnessIndicators<T> &) const;
    std::string toString() const;
  };

  template<typename T>
  struct DirectPathSegment{
  public:
    LBAMV::LinCombination<long> cost;
    std::map<long,T> restrictions; // key:   edge name
                                   // value: the passage time that the edge must have in order for path to be valid
    std::string toString() const;
    int restrictionsSatisfied(const CompVector<T>& ) const;
    int operator<(const DirectPathSegment<T>& ) const;
  };

  template<typename T>
  struct MainGraph{
  public:
    std::map<CompVector<T>, std::map<CompVector<T>,DirectPathSegment<T> > > g;
    // key: pair of edges.
    // value: list of possible direct path segments.
    //        There could be several DirectPathSegment (s)
    //          Hence, they are kept in the map. The map key is the name of the segment.
    //          This is how the program will make the names: The name will be simply the vector r
    //          such that the analysis of \sigma^r(\omega) resulted in the construction of the
    //          this DirectPathSegment
    std::string toString() const;
  };
  template<typename T>
  struct EvaluationsForOneEnvironment{
  public: 
    ssm::set<LBAMV::LinCombination<T> > eOne;
    // there could be several evaluations. That's why we use StatSeq
    std::string toString() const;
  };
  template<typename T>
  struct EvaluationsForAllEnvironments{
    std::map<CompVector<T>, EvaluationsForOneEnvironment<T> > eAll;
    std::string toString() const;
  };

  template<typename T>
  struct MainEvaluatorFixed{
  public:
    MainGraph<T> mG;
  };
  template<typename T>
  struct MainEvaluatorDynamicBackTracking{
  public:
    EvaluationsForAllEnvironments<T> eAE;
    std::vector<ssm::set<CompVector<T> > > remainingEnvironments;
    std::string toString() const;
  };
  template<typename T>
  struct MainEvaluator{
  public:
    MainGraph<T> mG;
    EvaluationsForAllEnvironments<T> eAE;
    std::vector<ssm::set<CompVector<T> > > remainingEnvironments;
    long criticalErrors;
    std::string errorMessages;
    std::string toString() const;
  };

  template<typename T>
  struct BestEvaluationWithErrorMessage{
    public:
      EvaluationsForOneEnvironment<T> bestEv;
      std::string errorMessage;
  };

  template<typename T>
  struct LowerBoundProofData{
  public:
    //long lowerBound;
    int proofFound;
    LBAMV::LinCombination<T> envDerivativeF;
    EvaluationsForAllEnvironments<T> eAE;
    LowerBoundProofData();
  };
}

#endif
