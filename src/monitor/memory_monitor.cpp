//
// Created by 12992 on 24-5-7.
//

#include "monitor/memory_monitor.h"
#include <sys/errno.h>

#include <sstream>
#include <string>
#include <iostream>
#include <cstring>
#include <chrono>

namespace system_monitor::monitor
{
    using namespace std;

    unique_ptr<abstract_monitor> memory_monitor::clone()
    {
        return make_unique<memory_monitor>(*this);
    }

    string memory_monitor::to_string()
    {
        stringstream ss;
        ss << "total : " << this->get_total_ram() << "\tfree : " << this->get_free_ram();
        struct sysinfo sysinfo1{};
        sysinfo(&sysinfo1);
        // cout << "hello : " << sysinfo1.freeram + sysinfo1.freehigh << endl;
        // cout << "hello2 : " << (sysinfo1.totalram + sysinfo1.totalhigh) / 1024 / 1024 << endl;
        return ss.rdbuf()->str();
    }

    unique_ptr<memory_monitor> memory_monitor::get_memory_monitor()
    {
        return unique_ptr<memory_monitor>(new memory_monitor);
    }


    unsigned long memory_monitor::get_total_ram()
    {
        decltype(auto) info = memory_monitor::get_sys_info();
        return info.totalram / (1024 * 1024);
    }

    struct sysinfo &memory_monitor::get_sys_info()
    {
        static chrono::system_clock::time_point tp = chrono::system_clock::now() - 4s;
        static struct sysinfo info{};
        if (chrono::system_clock::now() - tp > 3s)
        {
            int res = sysinfo(&info);
            if (res != 0)
            {
                throw runtime_error(strerror(errno));
            }
            tp = chrono::system_clock::now();
        }
        return info;
    }

    unsigned long memory_monitor::get_free_ram()
    {
        decltype(auto) info = memory_monitor::get_sys_info();
        return (info.freeram + info.freehigh) / (1024 * 1024);
    }

    double memory_monitor::get_ram_usage()
    {
        return 1 - static_cast<double>(this->get_free_ram()) / static_cast<double>(this->get_total_ram());
    }
}
