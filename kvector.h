#ifndef KVECTOR_H
#define KVECTOR_H

#include <vector>

class chym;

int calcV(const chym& my,const int n,
          const int i, const std::vector<std::vector<int> > & vZh);

class kvector
{
public:
  kvector(const int anLength,
          const int anRank);
  kvector operator++(int);
  std::vector<int> get() const;
private:
  std::vector<int> m_kv;
  int m_l;
  int m_r;
};

#endif // KVECTOR_H
