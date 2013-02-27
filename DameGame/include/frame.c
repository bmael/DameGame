#include "frame.h"


frame make_frame(in_addr src, in_addr dest, const char * datatype, char * data){
    frame f;
    f.src = src;
    f.dest = dest;
    strcpy(f.data_type, datatype);
    strcpy(f.data, data);

    return f;
}
