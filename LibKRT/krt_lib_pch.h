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
 * \file krt_lib_pch.h
 * \date 2018/12/26 13:50
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: 包含KumaRT库使用各头文件，也作为工程的预编译头文件
 *
 * \note
*/
#ifndef krt_lib_pch_h__
#define krt_lib_pch_h__

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <array>
#include <memory>
#include <exception>
#include <iosfwd>
#include <sstream>
#include <fstream>
#include <bitset>
#include <cstdint>
#include <functional>
#include <set>
#include <array>
#include <cstdlib>
#include <cfloat>

#ifndef  GLM_FORCE_SSE2
#define  GLM_FORCE_SSE2
#endif

#ifndef  GLM_FORCE_INLINE
#define  GLM_FORCE_INLINE
#endif

#ifndef  GLM_MESSAGES
#define  GLM_MESSAGES
#endif

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtx/transform.hpp"
#include "gtc/quaternion.hpp"
#include "gtx/quaternion.hpp"

#endif // krt_lib_pch_h__