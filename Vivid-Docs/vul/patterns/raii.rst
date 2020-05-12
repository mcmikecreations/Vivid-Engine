.. _vul-patterns-raii-my:

RAII
====

.. contents::
   :local:

RAII is a class, that can be used as a wrapper around a variable of type, that
has explicit initialization and termination routines (:code:`init()` and 
:code:`term()`). If the :code:`init()` call happens at the beginning of a
function and :code:`term()` is called at the end, it is wise to use this wrapper
not to call these functions manually.

Usage
-----

.. code:: cpp
   
   {
       raii<managed_singleton<float>> r(managed_singleton<float>(), 5.6f);
       if(r.is_init() == 0) abort();
       cout << managed_singleton<float>::get() << endl; //5.6
       cout << r.get().get() << endl; //5.6
       cout << r->get() << endl; //5.6
       //term() will be called automatically
   }
   
.. note::
   This class does not use any special thread safety mechanisms.

API
---

.. doxygenclass:: vul::patterns::raii
   :members:
.. :undoc-members:
