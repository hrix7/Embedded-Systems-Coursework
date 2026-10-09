#include "course1.h"
int main(void)
{
#ifdef COURSE1
    return course1();
#else
    return 0;
#endif
}
