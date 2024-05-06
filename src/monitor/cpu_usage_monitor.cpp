//
// Created by 12992 on 24-5-6.
//

#include "../include/monitor/cpu_usage_monitor.h"

#include <iostream>
#include <string>

namespace system_monitor::monitor
{
    unique_ptr<monitor> cpu_usage_monitor::clone()
    {
        return unique_ptr<monitor>();
    }

    string cpu_usage_monitor::to_string()
    {
        return {};
    }

    unique_ptr<cpu_usage_monitor> cpu_usage_monitor::get_monitor()
    {
        return make_unique<cpu_usage_monitor>();
    }

    void cpu_usage_monitor::get_info()
    {

    }
} // monitor
// system_monitor