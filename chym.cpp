#include "chym.h"

#include "kvector.h"

#include "cmath"
#include <algorithm>

chym::chym(const int anRank,
           const int anLength):
  m_nRank(anRank),
  m_nLength(anLength)
{
  m_nSize = std::pow(m_nRank,m_nLength);
//  m_vL = matrix<int>(m_nSize, m_nLength);
  m_vl = std::vector<std::vector<int> >(m_nSize, std::vector<int>(m_nLength));
  kvector vHelpGen(m_nLength,m_nRank);

  for (std::size_t i =0; i < m_nSize; ++i)
  {
    m_vl[i] = vHelpGen.get();
    vHelpGen++;
  }

}

int chym::sort()
{
 // std::sort(m_vl.begin(), m_vl.end(), sortF);
    std::sort(m_vl.begin(), m_vl.end(), sortF);
  return 0;
}

bool chym::sortF(const std::vector<int>& aObj1,
           const std::vector<int>& aObj2)
{
  int nSumObj1 = aObj1[0];
  int nSumObj2 = aObj2[0];
  for (std::size_t i  = 1; i < aObj1.size(); ++i)
  {
      nSumObj1 += aObj1[i];
      nSumObj2 += aObj2[i];
  }
  if (nSumObj1 > nSumObj2)
    return false;
  if (nSumObj1 < nSumObj2)
    return true;

  bool r = false;
  for (std::size_t i  = 0; i < aObj1.size(); ++i)
//  for (int i  = aObj1.size()-1; i >= 0; --i)
  {
     if (aObj1[i] < aObj2[i])
        r = false;
     if (aObj1[i] > aObj2[i])
         r = true;
  }
  return r;
}

int chym::get(const int i, const int j) const
{
  return m_vl[i][j];
}
