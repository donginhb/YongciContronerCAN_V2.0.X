/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/** 
 * <p>application name： Delay.h</p> 
 * <p>application describing： Delay宏定义</p> 
 * <p>copyright： Copyright (c) 2017 Beijing SOJO Electric CO., LTD.</p> 
 * <p>company： SOJO</p> 
 * <p>time： 2017.05.20</p> 
 * 
 * @updata:[日期YYYY-MM-DD] [更改人姓名][变更描述]
 * @author Zhangxiaomou 
 * @version ver 1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_DELAY_H
#define	XC_DELAY_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#include "tydef.h"

#define GET_TEMP_TIME   20000   //获取温度数据时间   (ms)
    
typedef struct TagTimeStamp
{
    uint32_t startTime;    //超时判断起始时间
    uint32_t delayTime;   
    
    //系统运行时需要的时间值

}TimeStamp;

typedef struct TagTimeStampCollect
{
    uint32_t  msTicks;          //系统时间MsTick
    TimeStamp getTempTime;      //记录上一次获取温度值的时间
    TimeStamp sendDataTime;     //记录上一次上传数据的时间
    TimeStamp scanTime;         //记录上一次按键扫描的时间
    TimeStamp changeLedTime;    //记录上一次改变指示灯的时间
    TimeStamp getCapVolueTime;  //获取电容电压的时间间隔
    TimeStamp canStartTime;     //CAN启动时间定时器
    TimeStamp overTime;         //超时检测时间
    TimeStamp offlineTime;      //DeviceNet 离线时间    
    TimeStamp refusalActionTime; //拒动检测时间    
    
}TimeStampCollect;



void InitSystemTime();
void DelayMs(uint32_t ms);
uint8_t IsOverTimeStamp(TimeStamp* pStamp);
uint8_t IsOverTime(uint32_t startTime, uint32_t delayTime);
//void OverflowDetection(uint32_t delayTime);

extern TimeStampCollect g_TimeStampCollect;    //状态时间


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

