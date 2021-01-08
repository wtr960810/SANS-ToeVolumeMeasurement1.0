/****************************************************************************************
ʹ�ñض�
cmd_queue.c�й�5�����������ָ������queue_reset()���Ӵ������ָ������queue_push()��
�Ӷ�����ȡһ������queue_pop().��ȡ��������Ч���ݸ���queue_size()����ָ�������ȡ��һ��������ָ��queue_find_cmd����
����ֲ������ƽ̨����Ҫ�޸ĵײ�Ĵ�������,����ֹ�޸ĺ������ƣ������޷���HMI������(hmi_driver.c)ƥ�䡣
--------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------*/
#include "cmd_queue.h"
#include "config.h"


#define CMD_HEAD 0XEE                                                  //֡ͷ
#define CMD_TAIL 0XFFFCFFFF                                            //֡β

#define U3_CMD_HEAD 0XAABB                                            //֡ͷ
#define U3_CMD_TAIL 0XCCDD                                            //֡β

typedef struct _QUEUE                                             
{                                                                 
    qsize _head;                                                       //����ͷ
    qsize _tail;                                                       //����β
    qdata _data[QUEUE_MAX_SIZE];                                       //�������ݻ�����
}QUEUE;   

typedef struct _QUEUE1                                             
{                                                                 
    qsize _head;                                                       //����ͷ
    qsize _tail;                                                       //����β
    qdata _data[QUEUE_MAX_SIZE];                                       //�������ݻ�����
}QUEUE1;  


static QUEUE que = {0,0,0};                                            //ָ�����
static uint32 cmd_state = 0;                                           //����֡β���״̬
static qsize cmd_pos = 0;                                              //��ǰָ��ָ��λ��

static QUEUE1  U3_que = {0,0,0};                                            //ָ�����
static uint16_t U3_cmd_heard = 0;                                           //����֡β���״̬
static uint16_t U3_cmd_state = 0;                                           //����֡β���״̬
static qsize  U3_cmd_pos = 0;                                              //��ǰָ��ָ��λ��
/*! 
*  \brief  ���ָ������
*/
void queue_reset()
{
    que._head = que._tail = 0;
    cmd_pos = cmd_state = 0;
}

void U3_queue_reset()
{
    U3_que._head = U3_que._tail = 0;
    U3_cmd_pos = U3_cmd_state = 0;
}
/*! 
* \brief  ���ָ������
* \detial ���ڽ��յ����ݣ�ͨ���˺�������ָ����� 
*  \param  _data ָ������
*/
void queue_push(qdata _data)
{
    qsize pos = (que._head+1)%QUEUE_MAX_SIZE;
    if(pos!=que._tail)                                                //����״̬
    {
        que._data[que._head] = _data;
        que._head = pos;
    }
}

void U3_queue_push(qdata _data)
{
    qsize pos = (U3_que._head+1)%QUEUE_MAX_SIZE;
    if(pos!=U3_que._tail)                                              //����״̬
    {
        U3_que._data[U3_que._head] = _data;
        U3_que._head = pos;
    }
}

//�Ӷ�����ȡһ������
static void queue_pop(qdata* _data)
{
    if(que._tail!=que._head)                                          //�ǿ�״̬
    {
        *_data = que._data[que._tail];
        que._tail = (que._tail+1)%QUEUE_MAX_SIZE;
    }
}
//�Ӷ�����ȡһ������
static void U3_queue_pop(qdata* _data)
{
    if(U3_que._tail!=U3_que._head)                                     //�ǿ�״̬
    {
        *_data = U3_que._data[U3_que._tail];
        U3_que._tail = (U3_que._tail+1)%QUEUE_MAX_SIZE;
    }
}

//��ȡ��������Ч���ݸ���
static qsize queue_size()
{
    return ((que._head+QUEUE_MAX_SIZE-que._tail)%QUEUE_MAX_SIZE);
}

static qsize U3_queue_size()
{
    return ((U3_que._head+QUEUE_MAX_SIZE-U3_que._tail)%QUEUE_MAX_SIZE);
}
/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
qsize queue_find_cmd(qdata *buffer,qsize buf_len)
{
    qsize cmd_size = 0;
    qdata _data = 0;

    while(queue_size()>0)
    {
        //ȡһ������
        queue_pop(&_data);

        if(cmd_pos==0&&_data!=CMD_HEAD)                               //ָ���һ���ֽڱ�����֡ͷ����������
        {
            continue;
        }
        if(cmd_pos<buf_len)                                           //��ֹ���������
            buffer[cmd_pos++] = _data;

        cmd_state = ((cmd_state<<8)|_data);                           //ƴ�����4���ֽڣ����һ��32λ����

        //���4���ֽ���֡βƥ�䣬�õ�����֡
        if(cmd_state==CMD_TAIL)
        {
            cmd_size = cmd_pos;                                       //ָ���ֽڳ���
            cmd_state = 0;                                            //���¼��֡β��
            cmd_pos = 0;                                              //��λָ��ָ��

#if(CRC16_ENABLE)
            //ȥ��ָ��ͷβEE��βFFFCFFFF����5���ֽڣ�ֻ�������ݲ���CRC
            if(!CheckCRC16(buffer+1,cmd_size-5))                      //CRCУ��
                return 0;

            cmd_size -= 2;                                            //ȥ��CRC16��2�ֽڣ�
#endif
            return cmd_size;
        }
    }
    return 0;                                                         //û���γ�������һ֡
}

qsize U3_queue_find_cmd(qdata *buffer,qsize buf_len)
{
    qsize cmd_size = 0;
    qdata _data = 0;
    while(U3_queue_size()>0)
    {
        //ȡһ������
        U3_queue_pop(&_data);
			  if(U3_cmd_pos==0)                                                                //ָ���һ���ֽڱ�����֡ͷ����������
        {
			   U3_cmd_heard=_data;
				}
        if(U3_cmd_pos==1&&((U3_cmd_heard<<8)|_data)!=U3_CMD_HEAD)                        //ָ���һ���ֽڱ�����֡ͷ����������
        {
					  U3_cmd_pos=0;
            continue;
        }
        if(U3_cmd_pos<buf_len)                                           //��ֹ���������
            buffer[U3_cmd_pos++] = _data;
        U3_cmd_state = ((U3_cmd_state<<8)|_data);                           //ƴ�����2���ֽڣ����һ��16λ����
        //���4���ֽ���֡βƥ�䣬�õ�����֡
        if(U3_cmd_state==U3_CMD_TAIL)
        {
					  
            cmd_size = U3_cmd_pos;                                       //ָ���ֽڳ���
            U3_cmd_state = 0;                                            //���¼��֡β��
            U3_cmd_pos = 0;                                              //��λָ��ָ��

#if(CRC16_ENABLE)
            //ȥ��ָ��ͷβAABB��βCCDD����4���ֽڣ�ֻ�������ݲ���CRC
            if(!CheckCRC16(buffer+1,cmd_size-4))                      //CRCУ��
                return 0;

            cmd_size -= 2;                                            //ȥ��CRC16��2�ֽڣ�
#endif
            return cmd_size;
        }
    }
    return 0;                                                         //û���γ�������һ֡
}
