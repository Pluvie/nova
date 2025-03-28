#include "test.h"

#include <ion/ion.c>
#include "nova.c"

#include "test/suite.h"
#include "test/suite.c"

i32 main (
    i32 argc,
    char** argv
)
{
  suite_register();
  suite_run();

  if (suite_passed)
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}
