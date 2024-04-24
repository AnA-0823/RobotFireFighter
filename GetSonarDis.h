#define Uchar unsigned char
#define Uint unsigned int

#define TrigL P2_0 // �����������ź�
#define EchoL P2_1 // ������echo�����ź�
#define TrigF P2_2 // ǰ�����������ź�
#define EchoF P2_3 // ǰ������echo�����ź�
#define TrigR P2_4 // �ҳ����������ź�
#define EchoR P2_5 // �ҳ�����echo�����ź�

extern Uchar timer_cnt;
extern Uint sonar_used_time;

extern Uint left_dis, right_dis, front_dis;
extern Uint GetSonarDis(char pos);
extern void ScanDis(void);