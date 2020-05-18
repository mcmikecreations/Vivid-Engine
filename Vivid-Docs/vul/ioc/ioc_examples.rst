.. _vul-di-examples-my:

IoC Container Examples
======================

.. contents::
   :local:

Basic example
-------------

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