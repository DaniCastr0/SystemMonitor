#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int PID): _PID(PID) {CpuUse();}
// TODO: Return this process's ID
int Process::Pid() { 
    return _PID; 
    }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const
{ 
    
    
    return _cpu;
    
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(Pid());
     }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    std::string sram= LinuxParser::Ram(Pid());
    if (sram.size()<3){return "0";}
    sram.erase(sram.size()-3,sram.size()-2);
    return sram; 
    }

// TODO: Return the user (name) that generated this process
string Process::User() {
    
    return LinuxParser::User(Pid()); 
    }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime(Pid()); 
    
    }
void Process::CpuUse()
{
    std::vector<std::string> processCpu=LinuxParser::CpuUtilization(Pid());
    std::vector<float> processcpufloat(5);
    for (int i=0;i<5;i++)
    {
        processcpufloat[i]=std::stof(processCpu[i]);
    }
    long up=LinuxParser::UpTime();
    float total_time=processcpufloat[0]+processcpufloat[1]+processcpufloat[2]+processcpufloat[3];
    float seconds=up-(processcpufloat[4]/sysconf(_SC_CLK_TCK));
    float result=(total_time/seconds)/100;

    _cpu=result;
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }