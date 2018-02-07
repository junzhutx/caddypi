#ifndef EPDBASE_H
#define EPDBASE_H

#include "epdif.h"

class EpdBase : public EpdIf {
public:
    int width;
    int height;
    
    EpdBase();
    ~EpdBase();
    virtual int Init(bool partialUpdate) = 0;
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void WaitUntilIdle(void);
    void Reset(void);
    virtual void Sleep() = 0;
    
protected:
    unsigned int reset_pin;
    unsigned int dc_pin;
    unsigned int cs_pin;
    unsigned int busy_pin;
}

#endif /* EPDBASE_H */
