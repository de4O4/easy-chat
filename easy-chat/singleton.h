#ifndef SINGLETON_H
#define SINGLETON_H
#include <mutex>
#include <iostream>
#include <memory>

template <typename T>
class SingteTon{
protected:
    SingteTon() = default;
    SingteTon(const SingteTon<T>&) = delete;
    SingteTon& operator =(SingteTon<T>&) = delete;
    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> getintance(){
        static std::once_flag s_flag;
        std::call_once(s_flag ,[&](){
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }

    void printaddress(){
        std::cout<<_instance.get()<<std::endl;
    }
    ~SingteTon(){
        std::cout<<"singleton destruct!"<<std::endl;
    }
};

template <typename T>
std::shared_ptr<T> SingteTon<T>::_instance = nullptr;





#endif // SINGLETON_H
