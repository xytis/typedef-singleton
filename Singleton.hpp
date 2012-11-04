/******************************************************************************
 *                                                                            *
 *                           Singleton template                               *
 *                                                                            *
 *  from:  http://www.yolinux.com/TUTORIALS/C++Singleton.html                 *
 *  usage: #include "Singleton.hpp"                                           *
 *         typedef Singleton<MyClass> MySingleton;                            *
 *         MySingleton::instance()->do_stuff();                               *
 *         MySingleton::destroy();                                            *
 *                                                                            *
 *  warning: no multithreading support.                                       *
 *                                                                            *
 *  Edit:                                                                     *
 *    Due to feedback from coworker Singleton has received a private Keeper   *
 *    class, which strictly reduces the risk of accidental (yeah, right)      *
 *    deletion of singleton class with 'delete MySingle::instance()'          *
 *    Now the keeper forbids the deletion by safeguarding the pointer.        *
 *    This also adds some nice features, like You may have a forward          *
 *    declaration of singleton shortcut.                                      *
 *  Edit:                                                                     *
 *    Sometimes Singleton is required to be initialized at specific time,     *
 *    calling 'MySingleton::instance();' is not descriptive, so 'create()'    *
 *    method can be used.                                                     *
 ******************************************************************************/
#ifndef __SINGLETON_HPP_
#define __SINGLETON_HPP_

#include <iostream>

template <class T>
class Singleton
{
  public:
    template <class U>
      class Keeper {
        private:
          U * _pointer;
        protected:
          friend class Singleton<U>;

          bool valid() { return _pointer; }
          //TODO: add multithreading support
          void create() { _pointer = new U(); }
          void destroy() { if (valid()) { delete _pointer; _pointer = nullptr; } }
        public:
          Keeper():_pointer(nullptr) {}
          Keeper(const Keeper & copy): _pointer(copy._pointer) {}
          ~Keeper() {}

          U * operator -> () { return _pointer; }
          const U * operator -> () const { return _pointer; }

          Keeper & operator = (const Keeper & copy) { _pointer = copy._pointer; return *this; }
      };

    // Manually create the instance (if required.)
    static void create()
    {
      if (!m_pInstance.valid())
      {
        m_pInstance.create();
      }
    }

    // Return existing or create new instance
    static Keeper<T> instance()
    {
      // Do we have an instance of this type? If so return it, otherwise create a new one.
      return m_pInstance.valid() ? m_pInstance : (m_pInstance.create(), m_pInstance);
    }

,   // Manually destroy an existing instance. Call at end of program to clean up.
    static void destroy()
    {
      if (m_pInstance.valid())
      {
        m_pInstance.destroy();
      }
    }

  private:
    Singleton();                            // Constructor                   (empty & cannot be called externally)
    ~Singleton();                           // Destructor                    (empty & cannot be called externally)
    Singleton(Singleton const&);            // Copy constructor              (empty & cannot be called externally - no copies allowed)
    Singleton& operator=(Singleton const&); // Assignment operator           (empty & cannot be called externally - no assignment allowed)
    static Keeper<T> m_pInstance;           // Static template-type instance
};

// Set static instance value to NULL
template <class T> typename Singleton<T>::template Keeper<T> Singleton<T>::m_pInstance = Keeper<T>();

#endif
