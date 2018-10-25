#include "i2c/i2c.h"

#define PCA9685_MODE1 0x00
#define PCA9685_MODE2 0x01
#define PCA9685_LED0_ON_L 0x06
#define PCA9685_ADDRESS 0x40
#define PCA9685_ALLCALL 0x01
#define PCA9685_SLEEP 0x10
#define PCA9685_AI 0x20
#define PCA9685_OUTDRV 0x04
#define PCA9685_PRE_SCALE 0xFE
#define PCA9685_MAX_DUTY_CICLE 4095
#define PCA9685_REGISTERS_PER_CHANNEL 4
int PCA9685_init(smah_i2c bus);
int PCA9685_setDutyCycle(smah_i2c bus, char channel, short value);
int PCA9685_setFreq(smah_i2c bus, unsigned short freq);
int PCA9685_stop(smah_i2c bus);
