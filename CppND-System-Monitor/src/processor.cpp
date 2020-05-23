#include "processor.h"
#include "linux_parser.h"
#include <vector>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::vector<std::string> cpustring=LinuxParser::CpuUtilization();
    std::vector<float> cpufloat(10);
    for (int i=0;i<10;i++)
    {
        cpufloat[i]=std::stof(cpustring[i]);
    }
    float Idle=cpufloat[3]+cpufloat[4];
    float NonIdle=cpufloat[0]+cpufloat[1]+cpufloat[2]+cpufloat[5]+cpufloat[6]+cpufloat[7];
    float Total=Idle+NonIdle;

    return ((Total-Idle)/Total);
     }