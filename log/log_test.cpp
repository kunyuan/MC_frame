#include <iostream>

#include "log.h"

int main (int argc, char *argv[])
{
    Logger log;

    //set log file
    //log.set_file("c.log");

    //set log level
    log.set_level (0);
    log.set_label ("MC");

    log.debug () << "debug" << std::endl;

    log.info () << "info" << std::endl;

    log.warning () << "warning" << std::endl;

    log.error () << "error" << std::endl;

    //std::cout<<__FILE__<<std::endl;
    //std::cout<<__LINE__<<std::endl;
    //std::cout<<__FUNCTION__<<std::endl;

    return 0;
}
