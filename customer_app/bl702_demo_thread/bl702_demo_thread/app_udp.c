#include <utils_log.h>

#include <openthread/udp.h>
#include <openthread/thread.h>
#include <openthread_port.h>

#include <main.h>

static otUdpSocket          appSock;
static void (*app_udpHandler) (uint32_t);

static void otUdpReceive_handler(void *aContext, otMessage *aMessage, const otMessageInfo *aMessageInfo) 
{
    uint32_t val;
    otMessageRead(aMessage, 0, &val, sizeof(val));
    printf ("UPD Packet received, port: %d, len: %d, val: %ld\r\n", aMessageInfo->mPeerPort, otMessageGetLength(aMessage), val);

    if (app_udpHandler) {
        app_udpHandler(val);
    }
}

void app_sockInit(otInstance *instance, void (*handler)(uint32_t)) 
{
    otSockAddr sockAddr;

    memset(&appSock, 0 ,sizeof(otUdpSocket));
    memset(&sockAddr, 0, sizeof(otSockAddr));

    if (OT_ERROR_NONE == otUdpOpen(instance, &appSock, otUdpReceive_handler, instance)) {
        app_udpHandler = handler;
        sockAddr.mPort = THREAD_UDP_PORT;
        if (OT_ERROR_NONE == otUdpBind(instance, &appSock, &sockAddr, OT_NETIF_THREAD)) {
            printf("UDP PORT           : 0x%x\r\n", THREAD_UDP_PORT);
        }
    }
}

void app_udpSend(otInstance *instance, uint32_t val) 
{
    otNeighborInfo          neighborInfo;
    otNeighborInfoIterator  nbrIter = OT_NEIGHBOR_INFO_ITERATOR_INIT;
    otMessage               *pmsg;
    otMeshLocalPrefix       *pprefix = NULL;
    otMessageInfo           messageInfo;

    pprefix = (otMeshLocalPrefix *)otThreadGetMeshLocalPrefix(instance);

    nbrIter = OT_NEIGHBOR_INFO_ITERATOR_INIT;
    while (otThreadGetNextNeighborInfo(instance, &nbrIter, &neighborInfo) == OT_ERROR_NONE){

        memset(&messageInfo, 0, sizeof(messageInfo));

        memcpy(messageInfo.mPeerAddr.mFields.m8, pprefix->m8, sizeof(pprefix->m8));
        messageInfo.mPeerAddr.mFields.m8[11] = 0xff;
        messageInfo.mPeerAddr.mFields.m8[12] = 0xfe;
        messageInfo.mPeerAddr.mFields.m8[14] = neighborInfo.mRloc16 >> 8;
        messageInfo.mPeerAddr.mFields.m8[15] = neighborInfo.mRloc16 & 0xff;
        messageInfo.mPeerPort = THREAD_UDP_PORT;
        messageInfo.mHopLimit          = 0;
        messageInfo.mAllowZeroHopLimit = false;

        pmsg = otIp6NewMessage(instance, NULL);
        if (OT_ERROR_NONE == otMessageAppend(pmsg, &val, sizeof(val)) && OT_ERROR_NONE == otMessageSetLength(pmsg,  sizeof(val))) {
            if (OT_ERROR_NONE == otUdpSendDatagram(instance, pmsg, &messageInfo)) {
                printf ("UDP Packet sent, Rloc16: %x, val: %ld\r\n", neighborInfo.mRloc16, val);
            }
            else {
                otMessageFree(pmsg);
            }
        }
    }
}