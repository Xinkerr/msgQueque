/***************************************************************************
*
* Copyright (c) 2019 - 2020, Xinkerr
*
* This file is part of msgQueque.
*
* this is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
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
* LICENSE: LGPL V2.1
* see: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
*
* Create Date:   2019/6/18
* Modified Date: 2020/10/14
* Version:3.0
* Github: https://github.com/Xinkerr
* Mail: 634326056@qq.com
*
****************************************************************************/

#ifndef __MSGQUEQUE_H__
#define __MSGQUEQUE_H__

#include "ringbuffer.h"

typedef uint16_t msgbuf_szie_t;

typedef ringbuffer_t msgQueque_t;


/**@brief     消息队列初始化
 *
 * @details   对消息队列的结构体初始化，传入存储数据的地址
 *
 * @param[in] msg:    		消息队列对象句柄
 * @param[in] msg_pool:   	消息缓冲池，存放消息的地方
 * @param[in] pool_size:   	消息缓冲池大小
 *
 * @return    -1：参数错误；
 *			   0：正常
 */
int8_t msgQueque_init(msgQueque_t* msg, uint8_t* msg_pool, uint16_t pool_size);

/**@brief     加入消息队列
 *
 * @details   将具体的数据内容写入消息队列中
 *
 * @param[in] msg:    消息队列对象句柄
 * @param[in] pdata:  数据
 * @param[in] size:   数据大小
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t msgQueque_put(msgQueque_t* msg, uint8_t *pdata, uint16_t size);

/**@brief     取出消息队列
 *
 * @details   取出消息队列内的数据
 *
 * @param[in]  msg:          消息队列对象句柄
 * @param[out] msg_content： 消息内容
 *
 * @return    取出的数据长度
 *		
 */
msgbuf_szie_t msgQueque_get(msgQueque_t* msg, uint8_t* msg_content);
#endif
