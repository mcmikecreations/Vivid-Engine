VUL IoC
=======

.. contents::
   :local:

IoC principle is realized in this library as an IoC Container.

- Is non-intrusive (you don't have to modify your classes to work with `di`).
- Exception-less (can be compiled with :code:`-fno-exceptions`).
- Lightweight (around 12 bytes for each object apart from the object itself).
- Supports both transient and singleton lifetime.
- Has built-in memory management.
- Uses C++20 features.

Basic example
-------------

For more examples, see :ref:`vul-di-examples-my`.

Let's assume we have the classes, listed below.

.. code:: cpp
   
   class Repo
   {
   public: virtual int get() = 0;
   };
   
   class const_repo : public Repo
   {
   public: virtual int get() override { return 5; }
   };
   
   class Logger
   {
   public: virtual void log() = 0;
   };
   
   class cout_logger : public Logger
   {
       Repo* _repo;
   public:
       cout_logger(Repo* repo) : _repo(repo) {}
       virtual void log() override { std::cout << _repo->get(); }
   };
   
This is a standard Repository-Service pattern, a piece of the Onion
Architecture. A repository accesses data (in our case a const value) and a
service uses a repository to process the accessed data. In our case a logger
class logs an int from the repo class. Now the IoC Container usage.

.. code:: cpp
   
   void example()
   {
       di d;
       if (d.add_transient<Repo, const_repo>() == 0) return;
       if (d.add_singleton<Logger, cout_logger, Repo>() == 0) return;
       d.init();
       auto logger = d.get<Logger>()->get();
       logger->log(); //We get "5" in console
       d.term();
   }
   
.. danger::
   Do not call :code:`init()` or :code:`term()` more than once for one instance
   of di. This leads to undefined behavior.
   
.. important::
   This class does not terminate on destruction, you have to call :code:`term()`
   manually.
   
.. note::
   This class does not use any special thread safety mechanisms.
   
.. hint::
   It is safe to call :code:`di::free(ptr)` in a destructor, if you are sure
   that the pointed value isn't used anywhere else. In case of an expected error
   you'll get a 0 as a return.

API
---

.. doxygenclass:: vul::ioc::di
   :members:

Scope API
---------

.. doxygenclass:: vul::ioc::di_basic_scope
   :members:

.. doxygenclass:: vul::ioc::di_scope
   :members:

.. doxygenclass:: vul::ioc::di_scope_singleton
   :members:

.. doxygenclass:: vul::ioc::di_scope_transient
   :members:
   