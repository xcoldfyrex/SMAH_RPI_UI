#include "i2c.h"
#include <QDebug>

extern bool g_PCA9685_ready;

struct smah_i2c_t {
    int fd;
    pthread_mutex_t mutex;
};

smah_i2c smah_i2c_open(const char *filename) {
    smah_i2c bus = (smah_i2c)malloc(sizeof(struct smah_i2c_t));

    // Open I2C file
    if((bus->fd = open(filename, O_RDWR)) < 0) {
        free(bus);
        return NULL;
    }

    // create bus mutex
    if(pthread_mutex_init(&bus->mutex, NULL)) {
        close(bus->fd);
        free(bus);
        return NULL;
    }

    return bus;
}

int smah_i2c_write(smah_i2c bus, int addr, unsigned char *buffer, int buffersize) {
    if (!g_PCA9685_ready)
    {
        qCritical() << "Tried to write to I2C bus, but it's not ready: " << &buffer;
        return 0;
    }
    /* Lock mutex */
    pthread_mutex_lock(&bus->mutex);

    /* Join I2C. */
    if(ioctl(bus->fd, I2C_SLAVE, addr) < 0)
        return -1;

    /* Write to device */
    if(write(bus->fd, buffer, buffersize) != buffersize)
        return -1;

    /* Unlock mutex */
    pthread_mutex_unlock(&bus->mutex);

    return 0;
}

int smah_i2c_reg_write(smah_i2c bus, int addr, int reg, int data) {
    unsigned char buffer[] = {reg, data};

    return smah_i2c_write(bus, addr, buffer, 2);
}

int smah_i2c_read(smah_i2c bus, int addr, unsigned char *buffer, int buffersize) {
    /* Lock mutex */
    pthread_mutex_lock(&bus->mutex);

    /* Join I2C. */
    if(ioctl(bus->fd, I2C_SLAVE, addr) < 0)
        return -1;

    /* Read from device */
    if(read(bus->fd, buffer, buffersize) != buffersize)
        return -1;

    /* Unlock mutex */
    pthread_mutex_unlock(&bus->mutex);

    return 0;
}

void smah_i2c_close(smah_i2c bus) {
    pthread_mutex_destroy(&bus->mutex);
    close(bus->fd);
}
