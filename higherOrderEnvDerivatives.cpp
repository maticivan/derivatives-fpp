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


#include "src/fundamental/SHF_standardHeaders.cpp"
#include <thread>
#include "src/fundamental/SSM_simpleSetMap.cpp"
#include "src/fundamental/MFRF_massiveFindReplace.cpp"
#include "src/fundamental/BF_bijFunction.cpp"
#include "src/fundamental/TMF_timer.cpp"  
#include "src/fundamental/SF_strings.cpp" 
#include "src/fundamental/IOF_io.cpp"  
#include "src/derivativeEnv/MDINV_multiDimensionalIndices.cpp"  
#include "src/derivativeEnv/LBAMV_lowerBoundAlgebraicManipulations.h"
#include "src/derivativeEnv/LBAMV_lowerBoundAlgebraicManipulations.cpp"
#include "src/derivativeEnv/LBLCV_lowerBoundLogicalConclusions.h"
#include "src/derivativeEnv/LBLCV_lowerBoundLogicalConclusions.cpp"
#include "src/derivativeEnv/LBRWV_lowerBoundReportWriting.h"
#include "src/derivativeEnv/LBRWV_lowerBoundReportWriting.cpp" 
std::string proofInSpecialCases(){
  std::string outputFile="proofsEnvBounds.txt";
  ssm::set<LBLCV::HelpfulnessIndicators<long> > eM=LBLCV::generateHelpfulnessIndicators();
  std::string proofs,res;
  long numProofsFound=0;
  for(long i=0;i<eM.size();++i){ 
    LBLCV::LowerBoundProofData<long> lbD=LBLCV::lowerBoundSearchForProof(eM[i],-2);
    numProofsFound+=lbD.proofFound;  
    proofs=LBRWV::writeReport(eM[i],lbD)+proofs;
  }
  if(numProofsFound==eM.size()){
    IOF::toFile(outputFile,proofs);
    res+="Proofs successful. The report is in "+outputFile+"\n";
  }
  else{
    res="Proofs failed.\n";
  }
  return res;
}
int main(){
  std::string res=proofInSpecialCases();
  std::cout<<res; 
  return 0;
}
