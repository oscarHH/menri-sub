About Pillow
============

Goals
-----

The fork authors' goal is to foster active development of PIL through:

- Continuous integration testing via `Travis CI`_
- Publicized development activity on `GitHub`_
- Regular releases to the `Python Package Index`_
- Solicitation for community contributions and involvement on `Image-SIG`_

.. _Travis CI: https://travis-ci.org/python-imaging/Pillow
.. _GitHub: https://github.com/python-imaging/Pillow
.. _Python Package Index: https://pypi.python.org/pypi/Pillow
.. _Image-SIG: http://mail.python.org/mailman/listinfo/image-sig

License
-------

like PIL itself, Pillow is licensed under the MIT-like `PIL Software License <http://www.pythonware.com/products/pil/license.htm>`::

    Software License

    The Python Imaging Library (PIL) is

        Copyright © 1997-2011 by Secret Labs AB
        Copyright © 1995-2011 by Fredrik Lundh

    By obtaining, using, and/or copying this software and/or its associated documentation, you agree that you have read, understood, and will comply with the following terms and conditions:

    Permission to use, copy, modify, and distribute this software and its associated documentation for any purpose and without fee is hereby granted, provided that the above copyright notice appears in all copies, and that both that copyright notice and this permission notice appear in supporting documentation, and that the name of Secret Labs AB or the author not be used in advertising or publicity pertaining to distribution of the software without specific, written prior permission.

    SECRET LABS AB AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL SECRET LABS AB OR THE AUTHOR BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Why a fork?
-----------

PIL is not setuptools compatible. Please see `this Image-SIG post`_ for a more
detailed explanation. Also, PIL's current bi-yearly (or greater) release
schedule is too infrequent to accommodate the large number and frequency of
issues reported.

.. _this Image-SIG post: https://mail.python.org/pipermail/image-sig/2010-August/006480.html

What about PIL?
---------------

.. note::

    Prior to Pillow 2.0.0, very few image code changes were made. Pillow 2.0.0
    added Python 3 support and includes many bug fixes from many contributors.

As more time passes since the last PIL release, the likelihood of a new PIL
release decreases. However, we've yet to hear an official "PIL is dead"
announcement. So if you still want to support PIL, please
`report issues here first`_, then
`open the corresponding Pillow tickets here`_.

.. _report issues here first: https://bitbucket.org/effbot/pil-2009-raclette/issues

.. _open the corresponding Pillow tickets here: https://github.com/python-imaging/Pillow/issues

Please provide a link to the PIL ticket so we can track the issue(s) upstream.
