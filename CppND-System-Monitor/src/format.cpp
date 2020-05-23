#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    string sseconds,sminutes,shours,result;
    if ((seconds/3600<10)){shours="0"+std::to_string((seconds/3600));}
    else{shours=std::to_string((seconds/3600));}
    
    if (((seconds/60)%60<10)){sminutes="0"+std::to_string((seconds/60)%60);}
    else{sminutes=std::to_string((seconds/60)%60);}

    if ((seconds%60)<10){sseconds="0"+std::to_string(seconds%60);}
    else{sseconds=std::to_string(seconds%60);}
    

    result=shours+":"+sminutes+":"+sseconds;

     return result; 
     }