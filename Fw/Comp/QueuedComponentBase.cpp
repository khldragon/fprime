#include <Fw/Comp/QueuedComponentBase.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/EightyCharString.hpp>
#include <Fw/Cfg/Config.hpp>

#include <stdio.h>

namespace Fw {

#if FW_OBJECT_NAMES
    QueuedComponentBase::QueuedComponentBase(const char* name) : PassiveComponentBase(name),m_msgsDropped(0) {

    }
#else    
    QueuedComponentBase::QueuedComponentBase() : PassiveComponentBase(),m_msgsDropped(0) {

    }
#endif
    QueuedComponentBase::~QueuedComponentBase() {

    }
    
    void QueuedComponentBase::init(NATIVE_INT_TYPE instance) {
        PassiveComponentBase::init(instance);
    }

#if FW_OBJECT_TO_STRING == 1 && FW_OBJECT_NAMES == 1
    void QueuedComponentBase::toString(char* buffer, NATIVE_INT_TYPE size) {
        (void)snprintf(buffer, size,"QueueComp: %s", this->m_objName);
        buffer[size-1] = 0;
    }
#endif
    
    Os::Queue::QueueStatus QueuedComponentBase::createQueue(NATIVE_INT_TYPE depth, NATIVE_INT_TYPE msgSize) {
        
        Fw::EightyCharString queueName;
#if FW_OBJECT_NAMES == 1
        queueName = this->m_objName;
#else
        char queueNameChar[FW_QUEUE_NAME_MAX_SIZE];
        (void)snprintf(queueNameChar,sizeof(queueNameChar),"CompQ_%d",Os::Queue::getNumQueues());
        queueName = queueNameChar;
#endif
    	return this->m_queue.create(queueName, depth, msgSize);
    }

    NATIVE_INT_TYPE QueuedComponentBase::getNumMsgsDropped(void) {
        return this->m_msgsDropped;
    }

    void QueuedComponentBase::incNumMsgDropped(void) {
        this->m_msgsDropped++;
    }

}
