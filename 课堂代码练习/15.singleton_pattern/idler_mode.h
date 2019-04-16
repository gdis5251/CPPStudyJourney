#include <iostream>
#include <mutex>

class Idler
{
public:
    Idler* GetInstance(void)
    {
        if (_m_instance == nullptr)
        {
            _m_mtx.lock();
            if (_m_instance == nullptr)
            {
                _m_instance = new Idler();
            }
            _m_mtx.unlock();
        }

        return _m_instance;
    }

    class CGorbo
    {
    public:
        ~CGorbo()
        {
            if (_m_instance != nullptr)
            {
                delete _m_instance;
            }
        }
    };

    static CGorbo _CGorbo;

private:
    Idler(){};
    Idler(Idler const&) = delete;
    Idler& operator=(Idler const&) = delete;

    static std::mutex _m_mtx;
    static Idler *_m_instance;
};

Idler* Idler::_m_instance = nullptr;
std::mutex Idler::_m_mtx;
Idler::CGorbo _CGorbo;
