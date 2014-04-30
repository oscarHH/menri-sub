Installation
============

.. warning:: Pillow >= 2.1.0 no longer supports "import _imaging". Please use "from PIL.Image import core as _imaging" instead.

.. warning:: Pillow >= 1.0 no longer supports "import Image". Please use "from PIL import Image" instead.

.. warning:: PIL and Pillow currently cannot co-exist in the same environment.
    If you want to use Pillow, please remove PIL first.

.. note:: Pillow >= 2.0.0 supports Python versions 2.6, 2.7, 3.2, 3.3, 3.4

.. note:: Pillow < 2.0.0 supports Python versions 2.4, 2.5, 2.6, 2.7.

Simple installation
-------------------

.. note::

    The following instructions will install Pillow with support for most formats.
    See :ref:`external-libraries` for the features you would gain by installing
    the external libraries first. This page probably also include specific
    instructions for your platform.

You can install Pillow with :command:`pip`::

    $ pip install Pillow

Or :command:`easy_install` (for installing `Python Eggs
<http://peak.telecommunity.com/DevCenter/PythonEggs>`_, as :command:`pip` does
not support them)::

    $ easy_install Pillow

Or download the `compressed archive from PyPI`_, extract it, and inside it
run::

    $ python setup.py install

.. _compressed archive from PyPI: https://pypi.python.org/pypi/Pillow

.. _external-libraries:

External libraries
------------------

Many of Pillow's features require external libraries:

* **libjpeg** provides JPEG functionality.

  * Pillow has been tested with libjpeg versions **6b**, **8**, and **9**

* **zlib** provides access to compressed PNGs

* **libtiff** provides group4 tiff functionality

  * Pillow has been tested with libtiff versions **3.x** and **4.0**

* **libfreetype** provides type related services

* **littlecms** provides color management

  * Pillow version 2.2.1 and below uses liblcms1, Pillow 2.3.0 and
    above uses liblcms2. Tested with **1.19** and **2.2**.

* **libwebp** provides the Webp format.

  * Pillow has been tested with version **0.1.3**, which does not read
    transparent webp files. Versions **0.3.0** and **0.4.0** support
    transparency. 

* **tcl/tk** provides support for tkinter bitmap and photo images. 

* **openjpeg** provides JPEG 2000 functionality. 

  * Pillow has been tested with openjpeg **2.0.0**.

If the prerequisites are installed in the standard library locations for your
machine (e.g. :file:`/usr` or :file:`/usr/local`), no additional configuration
should be required. If they are installed in a non-standard location, you may
need to configure setuptools to use those locations (i.e. by editing
:file:`setup.py` and/or :file:`setup.cfg`). Once you have installed the
prerequisites, run::

    $ pip install Pillow

Linux installation
------------------

.. note::

    Fedora, Debian/Ubuntu, and ArchLinux include Pillow (instead of PIL) with
    their distributions. Consider using those instead of installing manually.

.. note::

    You *do not* need to install all of the external libraries to get Pillow's
    basics to work.

**We do not provide binaries for Linux.** If you didn't build Python from
source, make sure you have Python's development libraries installed. In Debian
or Ubuntu::

    $ sudo apt-get install python-dev python-setuptools

Or for Python 3::

    $ sudo apt-get install python3-dev python3-setuptools

In Fedora, the command is::
    
    $ sudo yum install python-devel

Prerequisites are installed on **Ubuntu 10.04 LTS** with::

    $ sudo apt-get install libtiff4-dev libjpeg62-dev zlib1g-dev \
        libfreetype6-dev tcl8.5-dev tk8.5-dev python-tk

Prerequisites are installed with on **Ubuntu 12.04 LTS** or **Raspian Wheezy
7.0** with::

    $ sudo apt-get install libtiff4-dev libjpeg8-dev zlib1g-dev \
        libfreetype6-dev liblcms2-dev libwebp-dev tcl8.5-dev tk8.5-dev python-tk

Prerequisites are installed on **Fedora 20** with::

    $ sudo yum install libtiff-devel libjpeg-devel libzip-devel freetype-devel \
        lcms2-devel libwebp-devel tcl-devel tk-devel


Mac OS X installation
---------------------

.. note::

    You *do not* need to install all of the external libraries to get Pillow's
    basics to work.

**We do not provide binaries for OS X**, so you'll need XCode to install
Pillow. (XCode 4.2 on 10.6 will work with the Official Python binary
distribution. Otherwise, use whatever XCode you used to compile Python.)

The easiest way to install the prerequisites is via `Homebrew
<http://mxcl.github.com/homebrew/>`_. After you install Homebrew, run::

    $ brew install libtiff libjpeg webp little-cms2

If you've built your own Python, then you should be able to install Pillow
using::

    $ pip install Pillow

Windows installation
--------------------

We provide binaries for Windows in the form of Python Eggs and `Python Wheels
<http://wheel.readthedocs.org/en/latest/index.html>`_:

Python Eggs
^^^^^^^^^^^

.. note::

    :command:`pip` does not support Python Eggs; use :command:`easy_install`
    instead.

::

    $ easy_install Pillow

Python Wheels
^^^^^^^^^^^^^

.. Note:: Experimental. Requires setuptools >=0.8 and pip >=1.4.1

::

    $ pip install --use-wheel Pillow

If the above does not work, it's likely because we haven't uploaded a
wheel for the latest version of Pillow. In that case, try pinning it
to a specific version:

::

    $ pip install --use-wheel Pillow==2.3.0


Platform support
----------------

Current platform support for Pillow. Binary distributions are contributed for
each release on a volunteer basis, but the source should compile and run
everywhere platform support is listed. In general, we aim to support all
current versions of Linux, OS X, and Windows.

.. note::

    Contributors please test on your platform, edit this document, and send a
    pull request.

+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+ 
|**Operating system**              |**Supported**|**Tested Python versions**    |**Tested Pillow versions**    |**Tested processors**  |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Mac OS X 10.8 Mountain Lion      |Yes          | 2.6,2.7,3.2,3.3              |                              |x86-64                 |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Mac OS X 10.7 Lion               |Yes          | 2.6,2.7,3.2,3.3              | 2.2.0                        |x86-64                 |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Redhat Linux 6                   |Yes          | 2.6                          |                              |x86                    |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| CentOS 6.3                       |Yes          | 2.7,3.3                      |                              |x86                    |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Fedora 20                        |Yes          | 2.7,3.3                      | 2.3.0                        |x86-64                 |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Ubuntu Linux 10.04 LTS           |Yes          | 2.6                          | 2.3.0                        |x86,x86-64             |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Ubuntu Linux 12.04 LTS           |Yes          | 2.6,2.7,3.2,3.3,PyPy2.1      | 2.3.0                        |x86,x86-64             |
|                                  |             |                              |                              |                       |
|                                  |             | 2.7,3.2                      | 2.3.0                        |ppc                    |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Ubuntu Linux 13.10               |Yes          | 2.7,3.2,3.3                  | 2.3.0                        |x86                    |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Raspian Wheezy                   |Yes          | 2.7,3.2                      | 2.3.0                        |arm                    |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Gentoo Linux                     |Yes          | 2.7,3.2                      | 2.1.0                        |x86-64                 |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Windows 7 Pro                    |Yes          | 2.7,3.2,3.3                  | 2.2.1                        |x86-64                 |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Windows Server 2008 R2 Enterprise|Yes          | 3.3                          |                              |x86-64                 |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Windows 8 Pro                    |Yes          | 2.6,2.7,3.2,3.3,3.4a3        | 2.2.0                        |x86,x86-64             |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+
| Windows 8.1 Pro                  |Yes          | 2.6,2.7,3.2,3.3,3.4          | 2.3.0, 2.4.0                 |x86,x86-64             |
+----------------------------------+-------------+------------------------------+------------------------------+-----------------------+

