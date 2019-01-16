#include "kvector.h"

#include "chym.h"


int calcV(const chym& my,
          const int n,
          const int i,
          const std::vector<std::vector<int> > & vZh)
{
  int sum = 0;
  // Все элементы которые уже есть в множестве Zh*
  for (int k = 0; k < n; ++k)
  {
    bool flag = true;   // Пока считаем что подходит
    for (int m = 0 ; m < my.m_nLength; ++m)
    {
      if (my.get(i,m) < vZh[k][m])
        flag = false;
    }

    // Если они меньше чем теекущий элемент
    if (flag)
    {
      //Сложение
      sum += vZh[k][my.m_nLength];
    }
  }

  //if(sum)
 //   sum --;

  if (sum < 0)
    sum = my.m_nRank + sum;
  return sum % my.m_nRank;
}


kvector::kvector(const int anLength, const int anRank):
  m_kv(anLength),
  m_l(anLength),
  m_r(anRank)
{

}

std::vector<int> kvector::get() const
{
  return m_kv;
}

kvector kvector::operator++(int)
{
  kvector result(*this);
//  bool f = true;
  if (m_kv[0] != m_r - 1)
  {
    m_kv[0] ++;
    return result;
  }
  //else if (m_kv[i] == m_r - 1)
  m_kv[0] = 0;

  for (std::size_t j = 1; j < m_l; ++j)
  {
      if (m_kv[j] != m_r - 1)
      {
        m_kv[j]++;
//        f = false;
        return result;
      }
      m_kv[j]=0;
  }

//  if (f)
//  {
    for (std::size_t k = 0; k < m_l; ++k)
    {
        m_kv[k] = 0;
    }
 // }
  return result;
}
