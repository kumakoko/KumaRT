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
 * \file krt_object.h
 * \date 2019/11/11 15:49
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 定义了作为KRT框架中各个对象的统一基类。这个基类包含了以下的信息：
 *       1 名称信息，即每个KRT内的object，都应有一个Name属性，用来标识该对象的名称
 *
 * \note
*/
#ifndef krt_object_h__
#define krt_object_h__

#include "krt_tools_macro.h"

namespace krt
{
    class Object : public std::enable_shared_from_this<Object>
    {
    protected:
        std::string name_;
    public:
        /*********************************************************
        构造函数       
        *********************************************************/
        Object();

        /*********************************************************
        构造函数
        @param  const char * name 本object的名字字符串       
        *********************************************************/
        Object(const char* name);
        
        /*********************************************************
        构造函数
        @param  const std::string & name 本object的名字字符串
        *********************************************************/
        Object(const std::string& name);

        /*********************************************************
        析构函数       
        *********************************************************/
        virtual ~Object();

        /*********************************************************
        拷贝构造函数
        @param  const Object& rhs 作为拷贝源的对象
        *********************************************************/
        Object(const Object& rhs);

        /*********************************************************
        移动构造函数
        @param  Object&& rhs 作为拷贝源的右值对象
        *********************************************************/
        Object(Object&& rhs);

        /*********************************************************
        设置本object的名字
        @param  const char * name 本object的名字字符串     
        *********************************************************/
        KRT_INLINE void set_name(const char* name)
        {
            name_ = name;
        }

        /*********************************************************
        设置本object的名字
        @param  const std::string & name      
        *********************************************************/
        KRT_INLINE void set_name(const std::string& name)
        {
            name_ = name;
        }

        /*********************************************************
        获取到本object的名字
        @return  本object的名字       
        *********************************************************/
        KRT_INLINE const std::string& name() const
        {
            return name_;
        }

        /*********************************************************
        从本对象克隆一个副本出来的接口函数
        @return 返回一个本对象克隆出来的副本对象      
        *********************************************************/
        virtual std::shared_ptr<Object> Clone() const = 0;
    };

    typedef std::shared_ptr<Object> ObjectSPtr;
}


#endif // krt_object_h__