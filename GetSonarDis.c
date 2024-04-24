#include <AT89X52.h>
#include "GetSonarDis.h"
extern delay_nus(unsigned int i);
extern delay_nms(unsigned int i);
extern int printf   (const char *, ...);

Uint left_dis=0,right_dis=0,front_dis=0;  //分别对应 左侧，右侧，中间 超声波采集数值
Uchar timer_cnt=0;	// 记录进定时器中断次数
Uchar scan_sonar_cnt=1;
Uint sonar_used_time=0;
/***********************************************************************/
// 定时器初始化
/***********************************************************************/
void InitTimer(void)
{
	  TMOD |= 0x01;
    TH0 = 0xF1;
    TL0 = 0x0A;
    EA = 1;
    ET0 = 1;
    TR0 = 0;
}
/*
	定时器0溢出中断
*/
void Interrupt(void) interrupt 1
{
	TR0 = 0;
}
/***********************************************************************/
// 测距函数
// 参数：pos时为超声波装置位置L、F、R分别代表左前右位置。
/***********************************************************************/

Uint GetSonarDis(char pos)
{
   Uint dis=0; 
	 Uint high, low;
//   TrigL=0;EchoL=0;TrigF=0;EchoF=0;TrigR=0;EchoR=0;  //各I/O口置低
	 InitTimer();  //定时器初始化
   switch(pos)
	{
	  case 'L':
		  TrigL=1;        //trig置高 发出10us的高电平信号 
		  delay_nus(25);   
		  TrigL=0;
			while(EchoL == 0);
		  TR0=1;
       //开启定时器开始计时
		  while(EchoL == 1 && TR0 == 1);   //等待echo置低
			TR0 = 0;
		  break;
	  case 'F':
		  TrigF=1;        //trig置高 发出10us的高电平信号 
		  delay_nus(10);  
		  TrigF=0;
			while(EchoF == 0);
		  TR0=1;
		  while(EchoF == 1 && TR0 == 1);   //等待echo置低
			TR0 = 0;
		  break;
   	case 'R':
		  TrigR=1;        //trig置高 发出10us的高电平信号 
		  delay_nus(25);
		  TrigR=0;
		  while(EchoR == 0);   //等待echo置高
		  TR0=1;           //开启定时器开始计时
		  while(EchoR == 1 && TR0 == 1);    //等待echo置低
			TR0 = 0;
		  break;
	  default: break;
	 }
	 high = (TH0 - 0xF1) * 256;
	 low = TL0 - 0x0A;
	 dis = (high + low) / 5.88;	
   return dis;	 
}
/***********************************************************************/
//超声波距离采集函数
/***********************************************************************/
void ScanDis(void)       //采集三个超声波传感器的数据
{   left_dis=GetSonarDis('L');	
	  front_dis=GetSonarDis('F');	   
  	right_dis=GetSonarDis('R');		 
}