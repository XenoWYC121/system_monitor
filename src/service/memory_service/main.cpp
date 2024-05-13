//
// Created by fsy on 24-5-13.
//
#include "service/memory_service/memory_service.h"


int main()
{
    using namespace system_monitor::service;
    memory_service::run_server("127.0.0.1:25002");
}
