//
// Created by 12992 on 24-5-7.
//
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
#include "monitor/utils/cpu_info.h"
#include "monitor/cpu_usage_monitor.h"
using namespace std;
TEST(monitor_test, test01)
{
    cout << "hello world！" << endl;
}

TEST(monitor_test, test02)
{
    ifstream cpu_stat("/proc/stat");
    ASSERT_TRUE(cpu_stat);
    string line1;
    getline(cpu_stat,line1);
    system_monitor::monitor::utils::cpu_info info(line1);
    ASSERT_GT(info.get_total_time(),0);
}

TEST(monitor_test,test03)
{
    using namespace system_monitor::monitor;
    auto test_monitor = cpu_usage_monitor::get_monitor();
    ASSERT_TRUE(test_monitor);
}