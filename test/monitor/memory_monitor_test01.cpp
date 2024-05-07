//
// Created by 12992 on 24-5-7.
//

#include "monitor/memory_monitor.h"

#include <gtest/gtest.h>
#include <iostream>

TEST(memory_monitor, test01)
{
    using namespace system_monitor::monitor;
    auto monitor1 = memory_monitor::get_memory_monitor();
    cout << "total: " << monitor1->get_total_ram() << "\tfree: " << monitor1->get_free_ram() << endl;
    cout << "rate: " << monitor1->get_ram_usage() << endl;
}