/**
 * @file Singleton.h
 * @brief 单例模式的模版类
 * @author HonePhy
 * @class-name	
 * Copyright () 2014-2020 QuantDigger. All rights reserved.
 * @chanege-log	
	2014-04-08 HonePhy 初始定义
 * @version 1.0
 * @date 2014-04-08
 */

#ifndef __SINGLETON_H_
#define __SINGLETON_H_

namespace QuantDigger {
namespace Util {
    

template <class T>
class Singleton
    {
    private:
        struct object_creator{
            object_creator()
                {
                Singleton<T>::instance();
                }
            //定义这个空函数主要目的是通过类的成员函数调用，确保不管什么样的编译器static 成员都能得到完整的初始化
            inline void do_nothing() const { }
        };
        static object_creator create_object;

        Singleton();
        Singleton(const Singleton& obj);
        Singleton& operator = (const Singleton& obj);
    public:
        typedef T object_type;
        static object_type* instance()
        {
            static object_type obj;
            create_object.do_nothing();
            return &obj;
        }
    };

template <class T> typename Singleton<T>::object_creator Singleton<T>::create_object;


#define DECLARE_SINGLETON_CLASS( ObjClass ) \
   friend class QuantDigger::Util::Singleton<ObjClass>

};

} /* Util */
#endif  /** __SINGLETION_H_ */
