#ifndef CHYM_H
#define CHYM_H

//#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

class kvector;
//using namespace boost::numeric::ublas;

class chym
{
public:
  chym(const int anRank,
       const int anLength);
  int sort();

  int m_nLength;
  int m_nSize;
  int m_nRank;

  int get(const int i, const int j) const;
private:
  static bool sortF(const std::vector<int>& aObj1,
             const std::vector<int>& aObj2);

  //matrix<int> m_vL;
  std::vector<std::vector<int> > m_vl;
};

#endif // CHYM_H
