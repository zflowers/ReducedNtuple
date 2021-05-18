#include "MET_Trigger_SF.h"

int main()
{
 MET_Trigger_SF Example;
 Example.ParseCSV();
 //std::cout << Example.Get_EFF(180.,650.,2018,false,false,true,0) << std::endl;
 //std::cout << Example.Get_SF(180.,650.,2016,false,false,0) << std::endl;
 std::cout << Example.Get_Name(650.,2016,true,false,true) << std::endl;
 return 0;
}
