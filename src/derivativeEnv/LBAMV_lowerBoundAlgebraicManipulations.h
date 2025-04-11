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


#ifndef _INCL_LBAMV_H
#define _INCL_LBAMV_H
namespace LBAMV{ 
  template<typename TTT>
  struct Monomial{
  public:
    std::string name;
    TTT c;
    Monomial(const std::string& ="", const TTT& =0);
    int operator<(const Monomial<TTT>& ) const;
  };
  
  template<typename TTT>
  struct LinCombination{
  public:
    ssm::set<Monomial<TTT> > terms;
    LinCombination<TTT>& operator+=(const LinCombination<TTT>& );
    LinCombination<TTT>& operator*=(const TTT& );
    LinCombination<TTT>& operator-=(const LinCombination<TTT>& );
    int partialOrderLEQ(const LinCombination<TTT>& ) const;
    int partialOrderLNEQ(const LinCombination<TTT>& ) const;
    int operator==(const LinCombination<TTT>& )const;
    int operator<(const LinCombination<TTT>& )const; //total ordering: lexicographic tiebraking
    void setFromString(const std::string& );
    std::string toString() const;
    TTT getComponent(const std::string& ) const;
  };       

}

#endif
