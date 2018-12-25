/**************************************************************************************************************************
Copyright(C) 2014-2019 www.xionggf.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute,sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM,OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************************************/
/*!
 * \file krt_tools_macro.h
 * \date 2018/12/25 11:11
 *
 * \author Xiong Xinke
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 本文件定义了一系列工具宏
 *
 * \note
*/
#ifndef krt_tools_macro_h__
#define krt_tools_macro_h__

#define KRT_SAFE_DELETE(pointer) do{if(pointer!=nullptr){delete pointer; pointer = nullptr; }}while(0)
#define KRT_SAFE_DELETE_ARRAY(array_pointer) do{if(array_pointer!=nullptr){delete [] array_pointer; array_pointer = nullptr; }}while(0)

#endif // krt_tools_macro_h__