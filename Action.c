#include <AT89X52.h>
#include "GetSonarDis.h"
#include "Move.h"
#include "Param.h"
#include "Action.h"
extern delay_nus(unsigned int i);
extern delay_nms(unsigned int i);

Uint DistLast = 0;

void stepLR(Uchar way)
{
    Uchar siz = 4, a = 200, b = 200;
    switch (way)
    {
    case 0:
        break;
    case 11:
        a -= 20;
        break;
    case 12:
        a -= 60;
        break;
    case 21:
        b -= 20;
        break;
    case 22:
        b -= 60;
        break;
    }
    while (siz > 0)
    {
        Forward(a, b);
        siz--;
    }
}

void stepFollow(Uchar side)
{
    if (side == 1)
    {
        if (left_dis > DistLast)
        {
            if (left_dis > FollowDistance)
            {
                if (DistLast > FollowDistance)
                {
                    stepLR(12);
                }
                else if (DistLast <= FollowDistance)
                {
                    stepLR(11);
                }
            }
            else
            {
                stepLR(0);
            }
        }
        else if (left_dis < DistLast)
        {
            if (left_dis < FollowDistance)
            {
                if (DistLast > FollowDistance)
                {
                    stepLR(21);
                }
                else if (DistLast < FollowDistance)
                {
                    stepLR(22);
                }
            }
            else
            {
                stepLR(0);
            }
        }
        else
        {
            if (DistLast > FollowDistance)
            {
                stepLR(11);
            }
            else if (DistLast < FollowDistance)
            {
                stepLR(21);
            }
            else
            {
                stepLR(0);
            }
        }
        DistLast = left_dis;
    }
    else if (side == 2)
    {
        if (right_dis > DistLast)
        {
            if (right_dis > FollowDistance)
            {
                if (DistLast > FollowDistance)
                {
                    stepLR(22);
                }
                else if (DistLast <= FollowDistance)
                {
                    stepLR(21);
                }
            }
            else
            {
                stepLR(0);
            }
        }
        else if (right_dis < DistLast)
        {
            if (right_dis < FollowDistance)
            {
                if (DistLast > FollowDistance)
                {
                    stepLR(11);
                }
                else if (DistLast < FollowDistance)
                {
                    stepLR(12);
                }
            }
            else
            {
                stepLR(0);
            }
        }
        else
        {
            if (DistLast > FollowDistance)
            {

                stepLR(21);
            }
            else if (DistLast < FollowDistance)
            {
                stepLR(11);
            }
            else
            {
                stepLR(0);
            }
        }
        DistLast = right_dis;
    }
}

void correctFollow(Uchar side) // yanbianxiuzhen
{
    Uchar i = 7;
    while (i > 0)
    {
        stepFollow(side);
        ScanDis();
        i--;
    }
}

void correct()
{
    Uchar i = 5, side = 0;
    while (i > 0)
    {
        stepLR(side);
        i--;
    }
}

void forwardA(Uchar side)
{
    Uchar t = 0;
    ScanDis();
    while (1)
    {
        ScanDis();
        if (front_dis > 150)
        {
            if (side == 1 && left_dis > 500)
            {
                stepLR(t);
            }
            else if (side == 2 && right_dis > 500)
            {
                stepLR(t);
            }
            else
            {
                stepFollow(side);
            }
        }
        else
        {
            break;
        }
    }
}

void forwardD(Uchar side, Uchar dist)
{
    ScanDis();
    while (dist > 0)
    {
        ScanDis();
        if (side == 0)
        {
            stepLR(side);
        }
        else
        {
            stepFollow(side);
        }
        dist--;
    }
}

void forwardTurnB(Uchar yside, Uchar jcside, Uchar dist)
{ // 检测优先
    Uchar t = 0;
    /*ScanDis();
  stepFollow(yside);*/
    while (1)
    {
        ScanDis();
        /*
        if(front_dis<150){
            if(jcside==1){
                turnLeftSteps();break;
               }else{
                   turnRightSteps();break;
                   }
        }*/
        if (jcside == 1)
        {
            if (left_dis < 300 || dist > 0)
            {
                if (yside == 1 && left_dis > 500)
                {
                    stepLR(t);
                }
                else if (yside == 2 && right_dis > 500)
                {
                    stepLR(t);
                }
                else
                {
                    stepFollow(yside);
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            if (right_dis < 300 || dist > 0)
            {
                if (yside == 1 && left_dis > 500)
                {
                    stepLR(t);
                }
                else if (yside == 2 && right_dis > 500)
                {
                    stepLR(t);
                }
                else
                {
                    stepFollow(yside);
                }
            }
            else
            {
                break;
            }
        }
        if (dist > 0)
        {
            dist--;
        }
    }
}

void extinguish(Uchar side)
{
    Uchar l_count = 0, r_count = 0;
    Uchar l_step = 3, r_step = 3;
    Uchar steps = 4;
    Uchar i;
    // if ((LeftFire == 0) || (RightFire == 0))
    // {
    //     FIRE = 1;
    // }
    while (1)
    {
        ScanDis();
        if ((LeftFire == 0) && (RightFire == 1))
        {
            Fan_On;
            turnLeftSteps(l_step);
            l_count++;
        }
        else if ((LeftFire == 1) && (RightFire == 0))
        {
            Fan_On;
            turnRightSteps(r_step);
            r_count++;
        }
        else if ((LeftFire == 0) && (RightFire == 0))
        {
            Fan_On;
            for (i = 0; i < steps; i++)
            {
                turnLeftSteps(l_step);
                delay_nms(500);
            }
            turnRightSteps(steps * l_step);
            for (i = 0; i < steps; i++)
            {
                turnRightSteps(r_step);
                delay_nms(500);
            }
            turnLeftSteps(steps * r_step);
            if (side == 1)
            {
                turnLeftSteps(steps * r_step);
                l_count += steps;
            }
            else
            {
                turnRightSteps(steps * r_step);
                r_count += steps;
            }
        }
        else if ((LeftFire == 1) && (RightFire == 1))
        {
            Fan_Off;
            turnLeftSteps(l_count * l_step);
            turnRightSteps(r_count * r_step);
            break;
        }
    }
}

void turnFire(Uchar side, Uchar isFire)
{
    if (isFire)
    {
        Uchar t = 15;
        if (side == 2)
        {
            turnRightSteps(t);
        }
        else
        {
            turnLeftSteps(t);
        }
        extinguish(side);
        if (side == 2)
        {
            turnLeftSteps(t);
        }
        else
        {
            turnRightSteps(t);
        }
        delay_nms(333);
    }
}
