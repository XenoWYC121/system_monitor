//
// Created by 12992 on 24-5-6.
//

#include "monitor/cpu_usage_monitor.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <regex>
#include <sstream>

namespace system_monitor::monitor
{
    unique_ptr<abstract_monitor> cpu_usage_monitor::clone()
    {
        return std::make_unique<cpu_usage_monitor>(*this);
    }

    string cpu_usage_monitor::to_string()
    {
        this->calculate();
        string res;
//        for (const auto &[key, usage]: this->cpu_usages)
//        {
//            ss << key << ":" << endl;
//            ss << '\t' << "total : " << usage.get_usage() << "\t system : " << usage.get_system_usage()
//               << "\t user : " << usage.get_user_usage() << endl;
//        }
//        return ss.rdbuf()->str();
        for (const auto &[key, usage]: this->cpu_usages)
        {
            res.append(key).append(":\n");
            res.append("\t total: ").append(std::to_string(usage.get_usage()))
                    .append("\t system: ").append(std::to_string(usage.get_system_usage()))
                    .append("\t user: ").append(std::to_string(usage.get_user_usage()))
                    .append("\n");
        }
        return res;
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
            : cpu_infos(cpu_usage_monitor::get_info())
    {
    }

    void cpu_usage_monitor::calculate()
    {
        if (chrono::system_clock::now() - this->m_tp > 3s)
        {
            //已经超过三秒,重新计算利用率
            this->cpu_usages.clear();
            auto new_info = cpu_usage_monitor::get_info();
            for (auto it1{this->cpu_infos.begin()}, it2{new_info.begin()};
                 it1 != this->cpu_infos.end() && it2 != new_info.end(); it1++, it2++)
            {
                if (it1->first != it2->first)
                {
                    throw logic_error("cpu names are not same!");
                }
                auto temp = it2->second - it1->second;
                this->cpu_usages.emplace(it1->first, temp);
            }
            //重新设定时钟
            this->m_tp = chrono::system_clock::now();
            this->cpu_infos = std::move(new_info);
        }
    }
}