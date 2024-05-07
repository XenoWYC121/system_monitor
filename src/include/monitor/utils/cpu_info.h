//
// Created by 12992 on 24-5-6.
//

#ifndef SYSTEM_MONITOR_CPU_INFO_H
#define SYSTEM_MONITOR_CPU_INFO_H

#include <iostream>

namespace system_monitor::monitor::utils
{
    using namespace std;

    class cpu_info
    {
    public:
        explicit cpu_info(const string &cpu_info_line);

        const string &get_m_cpu_name() const;

        int get_nice() const;

        int get_system() const;

        int get_idle() const;

        int get_iowait() const;

        int get_irq() const;

        int get_softirq() const;

        int get_steal() const;

        int get_guest() const;

        int get_guest_nice() const;

        int get_total_time() const;

        int get_user() const;

    private:
        void init(const string &cpu_info_line);

    private:
        string m_cpu_name;  //cpu名称
        int user;           //用户态时间
        int nice;           //低优先级程序所占用的用户态的cpu时间
        int system;         //处于核心态的运行时间
        int idle;           //CPU空闲的时间（不包含IO等待）
        int iowait;         //等待IO响应的时间
        int irq;            //处理硬件中断的时间
        int softirq;        //处理软中断的时间
        int steal;          //其他系统所花的时间
        int guest;          //运行时间为客户操作系统下的虚拟CPU控制
        int guest_nice;     //低优先级程序所占用的用户态的cpu时间
        mutable int total_time{0};   //运行总时间
    };

} // utils
// abstract_monitor
// system_monitor

#endif //SYSTEM_MONITOR_CPU_INFO_H
