//
// Created by 12992 on 24-5-7.
//
#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include "monitor/utils/cpu_info.h"
#include "monitor/utils/cpu_usage.h"
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
    getline(cpu_stat, line1);
    system_monitor::monitor::utils::cpu_info info(line1);
    ASSERT_GT(info.get_total_time(), 0);
}

TEST(monitor_test, test03)
{
    using namespace system_monitor::monitor;
    auto test_monitor = cpu_usage_monitor::get_monitor();
    ASSERT_TRUE(test_monitor);
}

TEST(monitor_test, test04)
{
    using namespace system_monitor::monitor::utils;
    ifstream cpu_stat("/proc/stat");
    ASSERT_TRUE(cpu_stat);
    string line1;
    getline(cpu_stat, line1);
    cpu_info info1(line1);
    this_thread::sleep_for(100ms);
    cpu_stat.close();
    cpu_stat.open("/proc/stat");
    getline(cpu_stat, line1);
    cpu_info info2(line1);
    ASSERT_THROW(info1 - info2, std::logic_error);

}