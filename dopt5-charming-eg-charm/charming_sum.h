#ifndef __CHARMING_SUM_H__
#define __CHARMING_SUM_H__

#include "charming_sum.decl.h"

class charming_sum : public CBase_charming_sum {
public:
  charming_sum();
  charming_sum(CkMigrateMessage *msg);
  void sum_neighbors(int i);
};

#endif //__CHARMING_SUM_H__
