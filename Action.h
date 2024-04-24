#define Uchar unsigned char
#define Uint unsigned int
#define LeftFire P1_2
#define RightFire P1_4
#define Fan_On P1_3 = 1
#define Fan_Off P1_3 = 0

extern void stepLR(Uchar way);
extern void stepFollow(Uchar side);
extern void correctFollow(Uchar side);
extern void correct();
extern void forwardA(Uchar side);
extern void forwardD(Uchar side, Uchar dist);
extern void forwardTurnB(Uchar yside, Uchar jcside, Uchar dist);
extern void extinguish(Uchar side);
extern void turnFire(Uchar side, Uchar isFire);