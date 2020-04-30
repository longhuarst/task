#include <stdint.h>
#include <stdbool.h>
#include "System.h"

#include <sys/time.h>

#include <stdio.h>
//雪花算法



//移植需要修改的代码  返回64位定时 时间

/**
 * 返回以毫秒为单位的当前时间
 * @return 当前时间(毫秒)
 */
int64_t timeGen() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (int64_t)tv.tv_usec/1000 +  (int64_t)tv.tv_sec*1000;;//System.currentTimeMillis();
}



 /** 开始时间截 (2015-01-01) */
const int64_t twepoch =  1420041600000;








/** 机器id所占的位数 */
const int64_t workerIdBits = 5L;

/** 数据标识id所占的位数 */
const int64_t datacenterIdBits = 5L;

/** 支持的最大机器id，结果是31 (这个移位算法可以很快的计算出几位二进制数所能表示的最大十进制数) */
const int64_t maxWorkerId = -1L ^ (-1L << workerIdBits);

/** 支持的最大数据标识id，结果是31 */
const int64_t maxDatacenterId = -1L ^ (-1L << datacenterIdBits);

/** 序列在id中占的位数 */
const int64_t sequenceBits = 12L;

/** 机器ID向左移12位 */
const int64_t workerIdShift = sequenceBits;

/** 数据标识id向左移17位(12+5) */
const int64_t datacenterIdShift = sequenceBits + workerIdBits;

/** 时间截向左移22位(5+5+12) */
const int64_t timestampLeftShift = sequenceBits + workerIdBits + datacenterIdBits;

/** 生成序列的掩码，这里为4095 (0b111111111111=0xfff=4095) */
const int64_t sequenceMask = -1L ^ (-1L << sequenceBits);

/** 工作机器ID(0~31) */
int64_t workerId;

/** 数据中心ID(0~31) */
int64_t datacenterId;

/** 毫秒内序列(0~4095) */
int64_t sequence = 0L;

/** 上次生成ID的时间截 */
int64_t lastTimestamp = -1L;

//==============================Constructors=====================================
/**
 * 构造函数
 * @param workerId 工作ID (0~31)
 * @param datacenterId 数据中心ID (0~31)
 */
bool SnowflakeIdWorker(int64_t workerId, int64_t datacenterId) {
    if (workerId > maxWorkerId || workerId < 0) {
        //throw new IllegalArgumentException(String.format("worker Id can't be greater than %d or less than 0", maxWorkerId));
        System->logger->error("worker Id can't be greater than %d or less than 0", maxWorkerId);
        return false;
    }
    if (datacenterId > maxDatacenterId || datacenterId < 0) {
        //throw new IllegalArgumentException(String.format("datacenter Id can't be greater than %d or less than 0", maxDatacenterId));
        System->logger->error("datacenter Id can't be greater than %d or less than 0", maxDatacenterId);
        return false;
    }
    workerId = workerId;
    datacenterId = datacenterId;


    return true;
}





/**
 * 阻塞到下一个毫秒，直到获得新的时间戳
 * @param lastTimestamp 上次生成ID的时间截
 * @return 当前时间戳
 */
int64_t tilNextMillis(int64_t lastTimestamp) {
    printf("tilNextMillis");
    int64_t timestamp = timeGen();
    while (timestamp <= lastTimestamp) {
        timestamp = timeGen();
    }
    return timestamp;
}




// ==============================Methods==========================================
/**
 * 获得下一个ID (目前版本 该方法 【不是】 线程安全的， 尽量不要在中断中使用) 
 * @return SnowflakeId
 */
int64_t nextId() {
    int64_t timestamp = timeGen();

    //如果当前时间小于上一次ID生成的时间戳，说明系统时钟回退过这个时候应当抛出异常
    if (timestamp < lastTimestamp) {
        // throw new RuntimeException(
        //         String.format("Clock moved backwards.  Refusing to generate id for %d milliseconds", lastTimestamp - timestamp));
        System->logger->error("Clock moved backwards.  Refusing to generate id for %d milliseconds", lastTimestamp - timestamp);
        return 0;
    }


    //如果是同一时间生成的，则进行毫秒内序列
    if (lastTimestamp == timestamp) {
        sequence = (sequence + 1) & sequenceMask;
        //毫秒内序列溢出
        if (sequence == 0) {
            //阻塞到下一个毫秒,获得新的时间戳
            timestamp = tilNextMillis(lastTimestamp);
        }
    }
    //时间戳改变，毫秒内序列重置
    else {
        sequence = 0L;
    }

    //上次生成ID的时间截
    lastTimestamp = timestamp;

    //移位并通过或运算拼到一起组成64位的ID
    return ((timestamp - twepoch) << timestampLeftShift) //
            | (datacenterId << datacenterIdShift) //
            | (workerId << workerIdShift) //
            | sequence;
}





bool snowFlakeInit(SnowFlake_TypeDef *object)
{
    object->next = nextId;

    return true;
}

////==============================Test=============================================
///** 测试 */
//public static void main(String[] args) {
//    SnowflakeIdWorker idWorker = new SnowflakeIdWorker(0, 0);
//    for (int i = 0; i < 1000; i++) {
//        int64_t id = idWorker.nextId();
//        System.out.println(int64_t.toBinaryString(id));
//        System.out.println(id);
//    }
//}
