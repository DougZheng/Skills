# 计算机网络

## TCP/IP 详解卷一

### TCP

![image-20210308102857516](C:\Users\Doug\AppData\Roaming\Typora\typora-user-images\image-20210308102857516.png)

TIME_WAIT 状态也称为 2MSL（Maximum Segment Lifetime） 等待状态，当 TCP 执行一个主动关闭并发回最后一个 ACK，该连接必须在 TIME_WAIT 状态停留 2倍 MSL 的时间，这样可以让 TCP 再次发送最后的 ACK 以防止这个 ACK 丢失。