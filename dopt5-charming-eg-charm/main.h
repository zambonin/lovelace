#ifndef __MAIN_H__
#define __MAIN_H__

#include "main.decl.h"

class Main : public CBase_Main {
public:
  Main(CkArgMsg *msg);
  Main(CkMigrateMessage *msg);
  void exit();
};

#endif //__MAIN_H__
