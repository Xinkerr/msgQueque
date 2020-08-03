/***************************************************************************
*
* Copyright (c) 2019, Xinkerr
*
* This file is part of msgQueque.
*
* msgQueque is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* msgQueque is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with msgQueque.  If not, see <https://www.gnu.org/licenses/>.
*	
* LICENSE: LGPL V2.1
* see: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
*
* Date:    2019/8/5
* Author:  鄭訫
* Version: 1.0
* Github:  https://github.com/Xinkerr/msgQueque
* Mail:    634326056@qq.com
*
* Disclaimer:
* AUTHOR MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* AUTHOR SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
****************************************************************************/
#include "msgQueque.h"
#include <string.h>

#define DEBUG_LOG	0
#if 	DEBUG_LOG	
#include <stdio.h>
#endif

/**@brief     消息队列初始化
 *
 * @details   对消息队列的结构体初始化，传入存储数据的结构体地址，以及消息队列的大小
 *
 * @param[in] msg:    消息队列结构体
 * @param[in] pdata:  保存消息内容的结构体
 * @param[in] size:   设定消息队列的大小，保存消息内容的结构体数组的大小
 *
 * @return    -1：参数错误；
 *			   0：正常
 */
int msgQueque_init(msgQueque_t* msg, queque_data_t* pdata, uint16_t size)
{
	if(msg == NULL || pdata == NULL || size == 0)
	{
		return -1;
	}
	memset(msg, 0, sizeof(msgQueque_t));
	msg->pdata = pdata;
	msg->queque_size = size;
	memset(pdata, 0, sizeof(queque_data_t)*size);
	return 0;
}

/**@brief     消息队列的状态
 *
 * @details   检测消息的队列的状态，用于是否可以写入或读取
 *
 * @param[in] msg:    消息队列结构体
 *
 * @return    msgQUEQUE_ERROR：消息队列传入错误
 *			  msgQUEQUE_EMPTY：消息队列空
 *			  msgQUEQUE_FULL ：消息队列满
 *			  msgQUEQUE_NORMAL：消息队列正常
 */
queque_state_m msgQueque_status(msgQueque_t* msg)
{
	if(msg == NULL)
		return msgQUEQUE_ERROR;

    if(msg->write_index == msg->read_index)
    {
    	//read和write在同一层且同一位置数据为空，read和write互相成镜像层同一位置数据为满
        if(msg->_bMirror == false)
        {
        	#if 	DEBUG_LOG
        	printf("msg quequq empty\n");
        	#endif
            return msgQUEQUE_EMPTY;
        }
        else
        {
        	#if 	DEBUG_LOG
        	printf("msg quequq full\n");
        	#endif
            return msgQUEQUE_FULL;
        }
    }
	return msgQUEQUE_NORMAL;
}

/**@brief     加入消息队列
 *
 * @details   将具体的数据内容写入消息队列中
 *
 * @param[in] msg:    消息队列结构体
 * @param[in] event:  消息事件（指向消息的来源、原因，或是消息的名称，或是消息的标志）
 * @param[in] pdata:  数据
 * @param[in] size:   数据大小
 *
 * @return    -1：失败
 *			   0：成功
 */
int msgQueque_put(msgQueque_t* msg, uint16_t event, uint8_t *pdata, msgbuf_szie_t size)
{
	queque_state_m msg_status;
	msg_status = msgQueque_status(msg);
	//有空间、无异常下加入消息队列数据
	if(msg_status == msgQUEQUE_NORMAL || msg_status == msgQUEQUE_EMPTY)
	{
		msg->pdata[msg->write_index].event = event;
		memcpy(msg->pdata[msg->write_index].buf, pdata, size);
		msg->pdata[msg->write_index].buf_size = size;
		if(msg->write_index == msg->queque_size - 1)
		{
			msg->_bMirror = !msg->_bMirror;
			msg->write_index = 0;
		}
		else
		{
			msg->write_index ++;
		}
		#if 	DEBUG_LOG
		printf("write_index:%u\n", msg->write_index);
		#endif
	}
	else
		return -1;

	return 0;
}

/**@brief     取出消息队列
 *
 * @details   取出消息队列内的数据
 *
 * @param[in] msg:    消息队列结构体
 * @param[in] msgData:  消息数据结构体
 *
 * @return    -1：失败
 *			   0：成功
 */
int msgQueque_get(msgQueque_t* msg, queque_data_t* msgData)
{
	queque_state_m msg_status;
	msg_status = msgQueque_status(msg);
	if(msg_status == msgQUEQUE_NORMAL || msg_status == msgQUEQUE_FULL)
	{
		// msgData = &(msg->pdata[msg->read_index]);
		memcpy(msgData, &msg->pdata[msg->read_index], sizeof(queque_data_t));

		if(msg->read_index == msg->queque_size - 1)
		{
			msg->_bMirror = !msg->_bMirror;
			msg->read_index = 0;
		}
		else
		{
			msg->read_index ++;
		}
		#if 	DEBUG_LOG
		printf("read_index:%u\n", msg->read_index);
		#endif
	}
	else
		return -1;

	return 0;
}

/**@brief     读取消息队列
 *
 * @details   读取消息队列内的数据，并非取出，指针不移动
 *
 * @param[in] msg:    消息队列结构体
 * @param[in] msgData:  消息数据结构体
 *
 * @return    -1：失败
 *			   0：成功
 */
int msgQueque_read(msgQueque_t* msg, queque_data_t* msgData)
{
	queque_state_m msg_status;
	msg_status = msgQueque_status(msg);
	if(msg_status == msgQUEQUE_NORMAL || msg_status == msgQUEQUE_FULL)
	{
		// msgData = &(msg->pdata[msg->read_index]);
		memcpy(msgData, &msg->pdata[msg->read_index], sizeof(queque_data_t));

		#if 	DEBUG_LOG
		printf("read_index:%u\n", msg->read_index);
		#endif
	}
	else
		return -1;

	return 0;
}

/**@brief     移动读指针
 *
 * @details   read指针向下一地址移动(配合msgQueque_read()使用)
 *
 * @param[in] msg:    消息队列结构体
 *
 */
void msgQueque_next(msgQueque_t* msg)
{
	if(msg->read_index == msg->queque_size - 1)
	{
		msg->_bMirror = !msg->_bMirror;
		msg->read_index = 0;
	}
	else
	{
		msg->read_index ++;
	}
}

/**@brief     清除消息队列所有数据
 *
 *
 * @param[in] msg:    消息队列结构体
 *
 */
void msgQueque_all_clear(msgQueque_t* msg)
{
	memset(msg->pdata, 0, msg->queque_size);
	msg->write_index = 0;
	msg->read_index = 0;
	msg->_bMirror = 0;
}

