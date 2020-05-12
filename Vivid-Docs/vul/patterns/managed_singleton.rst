.. _vul-patterns-managed-singleton-my:

Managed singleton
=================

.. contents::
   :local:

Managed singleton is a class, that can be used for program-level singleton
values. It is similar to an ordinary singleton pattern, but it has a clear
value lifetime and can't be altered directly from other places within the
program.

Usage
-----

.. code:: cpp
   
   managed_singleton<logger> a;
   //Calling get or ptr before init leads to undefined behavior.
   if(a.init("log.txt") == 0) abort();
   //Use static get() or ptr() to get the variable.
   //They can be called anywhere inside the program between init and term
   managed_singleton<logger>::get().log("Hello world!");
   managed_singleton<logger>::ptr()->log("Goodbye world!");
   if (a.term() == 0) abort();
   
.. danger::
   Do not call :code:`init()` or :code:`term()` for more than one instance of
   the same type of this class. This will lead to memory corruption.
   
.. important::
   This class does not terminate on destruction, you have to call :code:`term()`
   manually.
   
.. note::
   This class does not use any special thread safety mechanisms.

Example
-------

.. code:: cpp
   
   void log_thing() {
       managed_singleton<logger>::get().log("thing");
   }
   
   int main() {
       managed_singleton<logger> a;
       if (a.init("log.txt") == 0) return 0;
       log_thing();
       a.term();
       return 0;
   }

API
---

.. doxygenclass:: vul::patterns::managed_singleton
   :members:
.. :undoc-members:
