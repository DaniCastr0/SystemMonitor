#include "ncurses_display.h"
#include "system.h"
#include "linux_parser.h"
#include "format.h"
#include<iostream>
#include<vector>
#include <unistd.h>


int main() {
  System system;
  NCursesDisplay::Display(system);
  
  // for (int i=0;i<processCpu.size();i++)
  // {
  //   std::cout<<processCpu[i]<<std::endl;
  // }
  // std::vector<int>Ids=LinuxParser::Pids();
  //   std::vector<Process>processes;
  //   for(int i=0;i<Ids.size();i++)
  //   {
  //       Process process(Ids[i]);
  //       //processes.push_back(process);
  //       std::cout<<process.CpuUtilization()<<std::endl;
  //   }
}