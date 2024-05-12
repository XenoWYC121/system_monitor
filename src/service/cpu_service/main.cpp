//
// Created by 12992 on 24-5-11.
//
#include <iostream>
#include "service/cpu_service/cpu_service.h"

using namespace std;
using namespace system_monitor::service;

int main()
{
    cpu_service::run_server("0.0.0.0:25001");
}