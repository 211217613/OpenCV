#ifndef __Serial_H_
#define __Serial_H_

//*******************************************************
//Serial initialization
extern int serialport_init(const char* serialport, int baud);
extern int serialport_writebyte(int fd, uint8_t b);
extern int serialport_write(int fd, const char* str);
//********************************************************

#endif