// ifndef not include header files more than once

#ifndef __Buttons_H__
#define __Buttons_H__
extern int fd;


// extern: this prototype is used outside of this implementation
extern void buttonCallBackLedOff(int state, void *);
extern void buttonCallBackLedOn (int state, void *);
extern void buttonCallBackSave  (int state, void *);

#endif