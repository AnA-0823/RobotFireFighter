#include <AT89X52.h>
#include "GetSonarDis.h"
extern delay_nus(unsigned int i);
extern delay_nms(unsigned int i);
extern int printf   (const char *, ...);

Uint left_dis=0,right_dis=0,front_dis=0;  //�ֱ��Ӧ ��࣬�Ҳ࣬�м� �������ɼ���ֵ
Uchar timer_cnt=0;	// ��¼����ʱ���жϴ���
Uchar scan_sonar_cnt=1;
Uint sonar_used_time=0;
/***********************************************************************/
// ��ʱ����ʼ��
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
	��ʱ��0����ж�
*/
void Interrupt(void) interrupt 1
{
	TR0 = 0;
}
/***********************************************************************/
// ��ຯ��
// ������posʱΪ������װ��λ��L��F��R�ֱ������ǰ��λ�á�
/***********************************************************************/

Uint GetSonarDis(char pos)
{
   Uint dis=0; 
	 Uint high, low;
//   TrigL=0;EchoL=0;TrigF=0;EchoF=0;TrigR=0;EchoR=0;  //��I/O���õ�
	 InitTimer();  //��ʱ����ʼ��
   switch(pos)
	{
	  case 'L':
		  TrigL=1;        //trig�ø� ����10us�ĸߵ�ƽ�ź� 
		  delay_nus(25);   
		  TrigL=0;
			while(EchoL == 0);
		  TR0=1;
       //������ʱ����ʼ��ʱ
		  while(EchoL == 1 && TR0 == 1);   //�ȴ�echo�õ�
			TR0 = 0;
		  break;
	  case 'F':
		  TrigF=1;        //trig�ø� ����10us�ĸߵ�ƽ�ź� 
		  delay_nus(10);  
		  TrigF=0;
			while(EchoF == 0);
		  TR0=1;
		  while(EchoF == 1 && TR0 == 1);   //�ȴ�echo�õ�
			TR0 = 0;
		  break;
   	case 'R':
		  TrigR=1;        //trig�ø� ����10us�ĸߵ�ƽ�ź� 
		  delay_nus(25);
		  TrigR=0;
		  while(EchoR == 0);   //�ȴ�echo�ø�
		  TR0=1;           //������ʱ����ʼ��ʱ
		  while(EchoR == 1 && TR0 == 1);    //�ȴ�echo�õ�
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
//����������ɼ�����
/***********************************************************************/
void ScanDis(void)       //�ɼ�����������������������
{   left_dis=GetSonarDis('L');	
	  front_dis=GetSonarDis('F');	   
  	right_dis=GetSonarDis('R');		 
}