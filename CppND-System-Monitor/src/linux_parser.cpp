#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include<fstream>
#include <sstream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, os2,kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> os2>> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::string memTotal="MemTotal";
  std::string memfree="MemFree";
  std::string line;
  float Totalmem,freemem;

  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if (filestream.is_open()) {
     while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      if (line.find(memTotal) != std::string::npos) {
        linestream>> memTotal>> Totalmem;
      }
      if (line.find(memfree) != std::string::npos) {
        linestream >> memfree>> freemem;
        return ((Totalmem-freemem)/Totalmem);
      }
    }
  }
  return 0.0; 
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime;
  std::ifstream filestream(kProcDirectory+kUptimeFilename);
  std::string line;
  std::getline(filestream, line);
  std::istringstream linestream(line);
  linestream>> uptime;
  return uptime; 
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  std::vector<std::string> result(10);
  std::ifstream filestream(kProcDirectory+kStatFilename);
  std::string line,word;
  std::getline(filestream, line);
  std::istringstream linestream(line);
  linestream>> word; 
  int cont=0;
  while (!linestream.eof()){
    linestream>> word;
    result[cont]=word;
    cont++;
  }
  return result;
}
vector<string> LinuxParser::CpuUtilization(int pid) { 
  vector<string> val(5);
  string line;
  string value;
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
  int cont=0;
  if (filestream.is_open()) {
    std::getline(filestream, line); 
    std::istringstream linestream(line);
    while (linestream >> value) {
          
          if (cont==13){val[0]=value;}
          if (cont==14){val[1]=value;}
          if (cont==15){val[2]=value;}
          if (cont==16){val[3]=value;}
          if (cont==21){val[4]=value;}
          cont++;      
        
        }
      
    }
  return val; 
  }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::ifstream filestream(kProcDirectory+kStatFilename);
  std::string word,line;
  int processes;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream>>word>>processes;
      if (word=="processes"){return processes;}
    }
    filestream.close();

  }
  return 0; 
   }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::ifstream filestream(kProcDirectory+kStatFilename);
  std::string word,line;
  int processes;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream>>word>>processes;
      if (word=="procs_running"){return processes;}
    }
  }
  return 0; 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  std::string line;
  if (std::getline(filestream, line)){return line;}
  else {return "none";}
  }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  std::string word,line,processes;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream>>word>>processes;
      if (word=="VmSize:"){return processes;}
      }
      filestream.close();
    }
    return "0";

}
// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  std::string word,line,uid;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream>>word>>uid;
      if (word=="Uid:"){return uid;}
      }
    filestream.close();

  } 
  return "none";
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
   std::string uid=LinuxParser::Uid(pid);
   std::string username;
   std::ifstream filestream(kPasswordPath);
   std::string line;
   if (filestream.is_open()) {
     while (std::getline(filestream, line)) {
       if (line.find(uid)!=std::string::npos){
         username=line.substr(0, line.find(uid)-3);
         return username; 
       }
     }
    filestream.close();

   }
   return "none"; 
   }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatFilename);
  std::string word,line;
  std::getline(filestream, line);
  std::istringstream linestream(line);
  int cont=0;
  while (linestream>>word)
    {
        if(cont==21){
          return (std::stol(word));
        }     
        cont++;
    }
  filestream.close();

  return 0; 
  }