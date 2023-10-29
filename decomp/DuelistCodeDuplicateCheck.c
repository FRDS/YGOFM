#include <common.h>

char Duelist_DuplicateCheck(int * deck1, int * deck2)
{
  if (deck1[0xcd] == deck2[0xcd]) {
    return 1;
  }
  return 0;
}