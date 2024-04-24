#define Uchar unsigned char
#define Uint unsigned int

#define TrigL P2_0 // 左超声波触发信号
#define EchoL P2_1 // 左超声波echo引脚信号
#define TrigF P2_2 // 前超声波触发信号
#define EchoF P2_3 // 前超声波echo引脚信号
#define TrigR P2_4 // 右超声波触发信号
#define EchoR P2_5 // 右超声波echo引脚信号

extern Uchar timer_cnt;
extern Uint sonar_used_time;

extern Uint left_dis, right_dis, front_dis;
extern Uint GetSonarDis(char pos);
extern void ScanDis(void);