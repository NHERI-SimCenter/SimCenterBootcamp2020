Known installation issues
=======

Windows
-------

1. Failure to install fiona package

.. figure:: figures/installIssue1.png
   :align: center
   :figclass: align-center

   Reported installation error message

.. note::

   proposed solution
   --------

   It appears that the gdal package is the source of the problem. We recommend downloading the
   **gdal** and **fiona** packages closest to your system configuration from

   * gdal: https://www.lfd.uci.edu/~gohlke/pythonlibs/#gdal
   * fiona: https://www.lfd.uci.edu/~gohlke/pythonlibs/#fiona

   Install those packages using

   * **with anaconda installation**

   conda install gdal*.whl fiona*.whl

   * **python.org installation**

   sudo pip install gdal*.whl fiona*.whl


   

   


MacOS
------

No problems reported so far.

