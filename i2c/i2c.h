#ifndef I2C_h
#define I2C_h

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define I2C_JOIN_ERR	0b00000001
#define I2C_WRITE_ERR	0b00000010
#define I2C_READ_ERR	0b00000100

struct smah_i2c_t;		/*I2C opaque struct. Use the typedefed type i2c instead*/
typedef struct smah_i2c_t * smah_i2c;		/*I2C object*/
smah_i2c smah_i2c_open(const char *filename) __attribute__((warn_unused_result));
int smah_i2c_write(smah_i2c bus, int addr, unsigned char *buffer, int buffersize);
int smah_i2c_reg_write(smah_i2c bus, int addr, int reg, int data);
int smah_i2c_read(smah_i2c bus, int addr, unsigned char *buffer, int buffersize);
void smah_i2c_close(smah_i2c bus);

#endif
