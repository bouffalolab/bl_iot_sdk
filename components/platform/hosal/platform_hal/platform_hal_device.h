#ifndef __PLATFORM_HAL_DEVICE_H__
#define __PLATFORM_HAL_DEVICE_H__
#include <FreeRTOS.h>
#include <task.h>

#ifdef __cplusplus
extern "C"
{
#endif
int platform_hal_device_init(void);

/*TMP solution for getting API from c scope*/
int printf(const char *fmt, ...);
void *memcpy(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include <stdint.h>

class BLLinkedItem {
private:
    class BLLinkedItem *next;
public:
    BLLinkedItem();
    class BLLinkedItem* attach(class BLLinkedItem &item);
    class BLLinkedItem* detach();
};

class BLAesRequest : public BLLinkedItem {
public:
    uint32_t key[4];
    uint32_t iv[4];
    uint8_t *src;
    uint8_t *dst;
    size_t len;
    int first_use;

    int is_encryption;//0 for encryption, 1 for decryption
    /*section for task control*/
    TaskHandle_t task_handle;
    int done;
public:
    BLAesRequest();
    BLAesRequest(uint8_t *key, uint8_t *iv, uint8_t *src, uint8_t *dst, int len);
    int done_pre(int use_encryption);
    int done_wait();
    int done_set();
    int done_set_auto();
    int done_set_FromISR();
};

class BLLinkedList {
protected:
    class BLLinkedItem *head;
    class BLLinkedItem *tail;
public:
    BLLinkedList();
    class BLLinkedList* push(class BLLinkedItem &item);
    class BLLinkedItem* pop();
    class BLLinkedList* dump();
};

class BLAesEngine : public BLLinkedList {
private:
    class BLLinkedList head;

    void encryption_trigger();
    void decryption_trigger();
public:
    int encryption(BLAesRequest &req);
    int decryption(BLAesRequest &req);
};

#endif

#endif
