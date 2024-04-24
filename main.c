#include <at89x52.h>
#include <boebot.h>
#include <uart.h>
#include "GetSonarDis.h"
#include "Param.h"
#include "Move.h"
#include "Action.h"

// debug 模式代码
#define ZERO 1              // 舵机调零
#define HCSR04 2            // 超声波模块测试
#define FAN_TEST 3          // 风扇测试
#define FIRE_TEST 4         // 红外传感器测试
#define EXTINGUISH_L_TEST 5 // 左侧灭火测试
#define EXTINGUISH_R_TEST 6 // 右侧灭火测试
#define TURN_L90 10         // 左转90度测试
#define TURN_BACKL 11       // 左转180度测试
#define TURN_R90 20         // 右转90度测试
#define TURN_BACKR 21       // 右转180度测试
#define TEST 88
// debug 模式调整
#define DEBUG EXTINGUISH_L_TEST

// run 模式代码
#define DEBUG_ON 0 // 打开debug模式
#define S2 200     // S2模式
#define S3 300     // S3模式
// run 模式调整
#define RUN S3

// run 模式优先级高于debug模式
#if (RUN != DEBUG_ON)
#undef DEBUG
#endif

// 参数调整
FollowDistance = 130; // 沿墙距离
TurnLeftSteps = 36;   // 左转90度步数
TurnRightSteps = 36;  // 右转90度步数
Uchar Fire1 = 1;      // 1火焰状态
Uchar Fire2 = 1;      // 2火焰状态
Uchar Fire3 = 1;      // 3火焰状态
Uchar Fire4 = 1;      // 4火焰状态
Uchar Fire5 = 1;      // 5火焰状态
Uchar Fire6 = 1;      // 6火焰状态
Uchar Fire7 = 1;      // 7火焰状态
Uchar Fire8 = 1;      // 8火焰状态
Uchar Fire9 = 1;      // 9火焰状态

// S3路线图
#if (RUN == S3)
void runS3()
{
    Uchar c = 5;
    Uchar rside = 2;
    Uchar lside = 1;
    Uchar toSide = 2;
    Uchar d = 20;

    forwardA(rside); // 1huo 2
    turnFire(rside, Fire1);
    turnLeft();
    d = 20;
    forwardTurnB(rside, lside, d);
    correctFollow(rside);
    turnLeft();

    correct();
    correct();
    correct();
    forwardA(rside);
    turnLeft();      //   to room
    forwardA(rside); // 9huo 2
    turnFire(rside, Fire9);
    // hui
    turnBack();
    forwardA(lside);
    turnRight();
    forwardA(lside);
    turnLeft(); // out room

    forwardA(rside);
    turnLeft();
    d = 20;
    forwardTurnB(rside, rside, d);
    correct();
    turnRight();

    forwardA(lside); // 3huo 1        to room
    turnFire(lside, Fire3);
    turnRight();
    forwardA(lside);
    turnRight();
    forwardA(lside); // 2huo 1
    turnFire(lside, Fire2);

    // hui
    turnRight();
    forwardA(lside);
    turnRight();
    correct();
    correct();
    correct();
    forwardA(lside);
    turnLeft();
    forwardA(rside);
    turnLeft();

    forwardA(rside); // zai shizilukou      //out room
    turnLeft();
    forwardA(lside);
    turnRight();
    forwardA(lside);
    turnRight();
    forwardA(lside);
    delay_nms(10000);
}
#endif

// S2路线图
#if (RUN == S2)
void runS2()
{
    Uchar c = 5;
    Uchar lside = 1;
    Uchar rside = 2;
    Uchar toSide = 2;
    Uchar d = 20;
    forwardA(lside);
    turnLeft();
    forwardA(rside); // way
    // 6huo 1
    turnFire(lside, Fire6); // to room
    turnRight();
    forwardA(lside); // 5huo 1
    turnFire(lside, Fire5);
    turnRight();
    forwardA(lside);
    turnRight();
    forwardA(lside); // 4huo 1
    turnFire(lside, Fire4);
    turnRight();
    forwardA(lside);
    turnLeft(); // kou

    forwardA(rside);
    turnLeft();
    d = 5;
    forwardTurnB(rside, rside, d);
    d = 7;
    forwardD(lside, d);
    turnRight();
    correct(); // lu

    forwardA(lside); // 8huo 1
    turnFire(lside, Fire8);
    turnRight();
    forwardA(lside); // 7huo 1
    turnFire(lside, Fire7);
    FollowDistance = 200;
    turnBack();
    forwardA(rside);
    turnLeft();
    FollowDistance = 130;
    forwardA(rside);
    turnRight();
    d = 20;
    forwardD(lside, d);
    turnRight();
    forwardA(rside);
    delay_nms(10000);
}
#endif

// 主函数
int main()
{
    // 初始化
    LeftFire = 1;
    RightFire = 1;
    Fan_Off;
    delay_nms(2000);
    uart_Init();
    ScanDis();
#if (RUN == S2)
    runS2();
#elif (RUN == S3)
    runS3();
#endif

#ifdef DEBUG
#if (DEBUG == TEST)
    while (1)
    {
        stepFollow(1);
    }
#elif (DEBUG == ZERO)
    while (1)
    {
        Forward(0, 0);
    }
#elif (DEBUG == HCSR04)
    while (1)
    {
        ScanDis();
        printf("L:%d ", left_dis);
        printf("F:%d ", front_dis);
        printf("R:%d\n", right_dis);
    }
#elif (DEBUG == FAN_TEST)
    while (1)
    {
        Fan_On;
        delay_nms(5000);
        Fan_Off;
        delay_nms(5000);
    }
#elif (DEBUG == FIRE_TEST)
    while (1)
    {
        printf("L:%d--R:%d\n", LeftFire, RightFire);
        if ((LeftFire == 0) && (RightFire == 1))
        {
            turnLeft();
        }
        else if ((LeftFire == 1) && (RightFire == 0))
        {
            turnRight();
        }
    }
#elif (DEBUG == EXTINGUISH_L_TEST)
    while (1)
    {
        delay_nms(5000);
        turnFire(1, 1);
        delay_nms(5000);
    }
#elif (DEBUG == EXTINGUISH_R_TEST)
    while (1)
    {
        delay_nms(5000);
        turnFire(2, 1);
        delay_nms(5000);
    }
#elif (DEBUG == TURN_L90)
    while (1)
    {
        turnLeft();
        delay_nms(2000);
    }
#elif (DEBUG == TURN_BACKL)
    while (1)
    {
        turnBackL();
        delay_nms(2000);
    }
#elif (DEBUG == TURN_R90)
    while (1)
    {
        turnRight();
        delay_nms(2000);
    }
#elif (DEBUG == TURN_BACKR)
    while (1)
    {
        turnBackR();
        delay_nms(2000);
    }
#endif
#endif
    return 0;
}