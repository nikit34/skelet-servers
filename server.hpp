#ifndef server_hpp
#define server_hpp

#include <stdio.h>

/* for UNIX */

// auto setup uniqe programm name
#define INIT() (program_name = strrchr(argv[0], '/')) ? program_name++: (program_name = argv[0])
// wrapper ?
#define EXIT(s) exit(s)
// wrapper and check correct
#define CLOSE(s) if (close(s)) error(1, errno, "ошибка close")
// set err status
#define set_errno(e) errno = (e)
// wrapper ?
#define isvalidsock(s) ((s) >= 0)

typedef int SOCKET;

#endif
