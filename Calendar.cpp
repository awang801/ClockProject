



#include<iostream>


std::string Calendar(int month, int day)
{
	int m_value = 0;
	int months[] = {31,29,31,30,31,30,31,31,30,31,30,31};
	std::string weekday[] = {"Fri","Sat","Sun","Mon","Tues","Wed","Thurs"};

	for(int i=0;i<month-1;i++)
	{
		m_value += months[i];
	}
	m_value += day;
	m_value = (m_value%7);



	if((m_value) == 0)
	{
		return(weekday[6]);
	}
	return (weekday[m_value-1]);
}

int main()
{
  std::cout<<"Month:"<<std::endl;
  int i;
std::cin>>i;

  std::cout<<"Day:"<<std::endl;
  int j;
  std::cin>>j;

 std::string ans =Calendar(i,j);
 std::cout<<ans<<std::endl;

    return 0;
}
