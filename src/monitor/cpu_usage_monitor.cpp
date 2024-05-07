//
// Created by 12992 on 24-5-6.
//

#include "../include/monitor/cpu_usage_monitor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

namespace system_monitor::monitor
{
    unique_ptr<abstract_monitor> cpu_usage_monitor::clone()
    {
        return unique_ptr<cpu_usage_monitor>();
    }

    string cpu_usage_monitor::to_string()
    {
        return {};
    }

    unique_ptr<cpu_usage_monitor> cpu_usage_monitor::get_monitor()
    {
        return unique_ptr<cpu_usage_monitor>(new cpu_usage_monitor);
    }

    map<string, utils::cpu_info> cpu_usage_monitor::get_info()
    {
        map<string, utils::cpu_info> res;
        ifstream proc_stat("/proc/stat");
        if (!proc_stat)
        {
            throw std::invalid_argument("can not open the stat file");
        }
        regex regex1("cpu[0-9]*");
        string temp_line;
        while (getline(proc_stat, temp_line) && regex_search(temp_line, regex1))
        {
            utils::cpu_info temp_info(temp_line);
            res.emplace(temp_info.get_m_cpu_name(), temp_info);
        }
        return res;
    }

    cpu_usage_monitor::cpu_usage_monitor()
    {
        this->get_info();
    }
}