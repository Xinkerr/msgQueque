/***************************************************************************
*
* Copyright (c) 2019 - 2020, Xinkerr
*
* This file is part of ringbuffer.
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
* Date: 2020/10/14
* Version:2.0
* Github: https://github.com/Xinkerr
* Mail: 634326056@qq.com
*
****************************************************************************/
#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

//-----------------------------------CONFIG-------------------------------------------//
//INCLUDE
#include <stdint.h>
#include <stdbool.h> 

//定义
typedef bool RB_BOOL;			
typedef uint16_t ring_t;	
//------------------------------------------------------------------------------------//

#define RINGBUF_OK                  0
#define RINGBUF_FAIL                -1


typedef struct 
{
	uint8_t* buffer;
	ring_t write_index;
	ring_t read_index;
	ring_t buffer_size;
	RB_BOOL	_bMirror;
}ringbuffer_t;

/**@brief     ring buffer初始化
 *
 * @details   对ring buffer的结构体初始化，传入buffer的地址，以及buffer的大小
 *
 * @param[in] rb:    ring buffer结构体
 * @param[in] buf:   buffer
 * @param[in] size:  buffer的大小
 *
 * @return    -1：参数错误；
 *			   0：正常
 */
int8_t ringbuffer_init(ringbuffer_t* rb, uint8_t* buf, uint16_t size);

/**@brief     ring buffer的空闲容量
 *
 *
 * @param[in] rb: ring buffer结构体
 *
 * @return    空闲空间大小 byte
 *
 */
ring_t ringbuffer_free_space(ringbuffer_t* rb);

/**@brief     ring buffer的已用容量
 *
 *
 * @param[in] rb: ring buffer结构体
 *
 * @return    已用空间大小 byte
 *
 */
ring_t ringbuffer_use_space(ringbuffer_t* rb);

/**@brief     数据放入ring buffer
 *
 *
 * @param[in] rb:    ring buffer结构体
 * @param[in] pdata: 数据地址
 * @param[in] len:   数据的长度 (byte)
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t ringbuffer_put(ringbuffer_t *rb, uint8_t *pdata, ring_t len);

/**@brief     从ring buffer中取出数据
 *
 *
 * @param[in] rb:    ring buffer结构体
 * @param[in] pdata: 存放数据的地址
 * @param[in] len:   数据的长度 (byte)
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t ringbuffer_get(ringbuffer_t* rb, uint8_t *pdata, ring_t len);

/**@brief     清除ring buffer
 *
 *
 * @param[in] rb:    ring buffer结构体
 *
 */
void ringbuffer_all_clear(ringbuffer_t* rb);

/**@brief     从ring buffer中读出数据，非取出
 *
 *
 * @param[in] rb:    ring buffer结构体
 * @param[in] pdata: 存放数据的地址
 * @param[in] len:   数据的长度 (byte)
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t ringbuffer_read(ringbuffer_t* rb, uint8_t *pdata, ring_t len);

/**@brief     read_index向下移动位置
 *
 *
 * @param[in] rb:    ring buffer结构体
 * @param[in] move:  read_index移动字节数
 *
 * @return    -1：失败
 *			   0：成功
 */
int8_t ringbuffer_moveDown(ringbuffer_t* rb, ring_t move);
#endif
