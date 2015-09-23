/* Generated file - do not edit. */
/* See doc/docstrings/ *.rst. */

#include "pycurl.h"

PYCURL_INTERNAL const char curl_doc[] = "Curl() -> New Curl object\n\
\n\
Creates a new :ref:`curlobject` which corresponds to a\n\
``CURL`` handle in libcurl. Curl objects automatically set\n\
CURLOPT_VERBOSE to 0, CURLOPT_NOPROGRESS to 1, provide a default\n\
CURLOPT_USERAGENT and setup CURLOPT_ERRORBUFFER to point to a\n\
private error buffer.\n\
\n\
Implicitly calls :py:func:`pycurl.global_init` if the latter has not yet been called.";

PYCURL_INTERNAL const char curl_close_doc[] = "close() -> None\n\
\n\
Close handle and end curl session.\n\
\n\
Corresponds to `curl_easy_cleanup`_ in libcurl. This method is\n\
automatically called by pycurl when a Curl object no longer has any\n\
references to it, but can also be called explicitly.\n\
\n\
.. _curl_easy_cleanup:\n\
    http://curl.haxx.se/libcurl/c/curl_easy_cleanup.html";

PYCURL_INTERNAL const char curl_errstr_doc[] = "errstr() -> string\n\
\n\
Return the internal libcurl error buffer of this handle as a string.\n\
\n\
Return value is a ``str`` instance on all Python versions.";

PYCURL_INTERNAL const char curl_getinfo_doc[] = "getinfo(info) -> Result\n\
\n\
Extract and return information from a curl session.\n\
\n\
Corresponds to `curl_easy_getinfo`_ in libcurl, where *option* is\n\
the same as the ``CURLINFO_*`` constants in libcurl, except that the\n\
``CURLINFO_`` prefix has been removed. (See below for exceptions.)\n\
*Result* contains an integer, float or string, depending on which\n\
option is given. The ``getinfo`` method should not be called unless\n\
``perform`` has been called and finished.\n\
\n\
In order to distinguish between similarly-named CURLOPT and CURLINFO\n\
constants, some have ``OPT_`` and ``INFO_`` prefixes. These are\n\
``INFO_FILETIME``, ``OPT_FILETIME``, ``INFO_COOKIELIST`` (but ``setopt`` uses\n\
``COOKIELIST``!), ``INFO_CERTINFO``, and ``OPT_CERTINFO``.\n\
\n\
The value returned by ``getinfo(INFO_CERTINFO)`` is a list with one element\n\
per certificate in the chain, starting with the leaf; each element is a\n\
sequence of *(key, value)* tuples.\n\
\n\
Example usage::\n\
\n\
    import pycurl\n\
    c = pycurl.Curl()\n\
    c.setopt(pycurl.URL, \"http://sf.net\")\n\
    c.setopt(pycurl.FOLLOWLOCATION, 1)\n\
    c.perform()\n\
    print c.getinfo(pycurl.HTTP_CODE), c.getinfo(pycurl.EFFECTIVE_URL)\n\
    ...\n\
    --> 200 \"http://sourceforge.net/\"\n\
\n\
\n\
Raises pycurl.error exception upon failure.\n\
\n\
.. _curl_easy_getinfo:\n\
    http://curl.haxx.se/libcurl/c/curl_easy_getinfo.html";

PYCURL_INTERNAL const char curl_pause_doc[] = "pause(bitmask) -> None\n\
\n\
Pause or unpause a curl handle. Bitmask should be a value such as\n\
PAUSE_RECV or PAUSE_CONT.\n\
\n\
Corresponds to `curl_easy_pause`_ in libcurl. The argument should be\n\
derived from the ``PAUSE_RECV``, ``PAUSE_SEND``, ``PAUSE_ALL`` and\n\
``PAUSE_CONT`` constants.\n\
\n\
Raises pycurl.error exception upon failure.\n\
\n\
.. _curl_easy_pause: http://curl.haxx.se/libcurl/c/curl_easy_pause.html";

PYCURL_INTERNAL const char curl_perform_doc[] = "perform() -> None\n\
\n\
Perform a file transfer.\n\
\n\
Corresponds to `curl_easy_perform`_ in libcurl.\n\
\n\
Raises pycurl.error exception upon failure.\n\
\n\
.. _curl_easy_perform:\n\
    http://curl.haxx.se/libcurl/c/curl_easy_perform.html";

PYCURL_INTERNAL const char curl_reset_doc[] = "reset() -> None\n\
\n\
Reset all options set on curl handle to default values, but preserves\n\
live connections, session ID cache, DNS cache, cookies, and shares.\n\
\n\
Corresponds to `curl_easy_reset`_ in libcurl.\n\
\n\
.. _curl_easy_reset: http://curl.haxx.se/libcurl/c/curl_easy_reset.html";

PYCURL_INTERNAL const char curl_setopt_doc[] = "setopt(option, value) -> None\n\
\n\
Set curl session option. Corresponds to `curl_easy_setopt`_ in libcurl.\n\
\n\
*option* specifies which option to set. PycURL defines constants\n\
corresponding to ``CURLOPT_*`` constants in libcurl, except that\n\
the ``CURLOPT_`` prefix is removed. For example, ``CURLOPT_URL`` is\n\
exposed in PycURL as ``pycurl.URL``. For convenience, ``CURLOPT_*``\n\
constants are also exposed on the Curl objects themselves::\n\
\n\
    import pycurl\n\
    c = pycurl.Curl()\n\
    c.setopt(pycurl.URL, \"http://www.python.org/\")\n\
    # Same as:\n\
    c.setopt(c.URL, \"http://www.python.org/\")\n\
\n\
In order to distinguish between similarly-named CURLOPT and CURLINFO\n\
constants, some have CURLOPT constants have ``OPT_`` prefixes.\n\
These are ``OPT_FILETIME`` and ``OPT_CERTINFO``.\n\
As an exception to the exception, ``COOKIELIST`` does not have an ``OPT_``\n\
prefix but the corresponding CURLINFO option is ``INFO_COOKIELIST``.\n\
\n\
*value* specifies the value to set the option to. Different options accept\n\
values of different types:\n\
\n\
- Options specified by `curl_easy_setopt`_ as accepting ``1`` or an\n\
  integer value accept Python integers, long integers (on Python 2.x) and\n\
  booleans::\n\
\n\
    c.setopt(pycurl.FOLLOWLOCATION, True)\n\
    c.setopt(pycurl.FOLLOWLOCATION, 1)\n\
    # Python 2.x only:\n\
    c.setopt(pycurl.FOLLOWLOCATION, 1L)\n\
\n\
- Options specified as accepting strings by ``curl_easy_setopt`` accept\n\
  byte strings (``str`` on Python 2, ``bytes`` on Python 3) and\n\
  Unicode strings with ASCII code points only.\n\
  For more information, please refer to :ref:`unicode`. Example::\n\
\n\
    c.setopt(pycurl.URL, \"http://www.python.org/\")\n\
    c.setopt(pycurl.URL, u\"http://www.python.org/\")\n\
    # Python 3.x only:\n\
    c.setopt(pycurl.URL, b\"http://www.python.org/\")\n\
\n\
- ``HTTP200ALIASES``, ``HTTPHEADER``, ``POSTQUOTE``, ``PREQUOTE`` and\n\
  ``QUOTE`` accept a list of strings. The same rules apply to the strings\n\
  as do to string option values. Example::\n\
\n\
    c.setopt(pycurl.HTTPHEADER, [\"Accept:\"])\n\
\n\
- ``READDATA`` accepts a file object or any Python object which has\n\
  a ``read`` method. On Python 2, a file object will be passed directly\n\
  to libcurl and may result in greater transfer efficiency, unless\n\
  PycURL has been compiled with ``AVOID_STDIO`` option.\n\
  On Python 3 and on Python 2 when the value is not a true file object,\n\
  ``READDATA`` is emulated in PycURL via ``READFUNCTION``.\n\
  The file should generally be opened in binary mode. Example::\n\
\n\
    f = open('file.txt', 'rb')\n\
    c.setopt(c.READDATA, f)\n\
\n\
- ``WRITEDATA`` and ``WRITEHEADER`` accept a file object or any Python\n\
  object which has a ``write`` method. On Python 2, a file object will\n\
  be passed directly to libcurl and may result in greater transfer efficiency,\n\
  unless PycURL has been compiled with ``AVOID_STDIO`` option.\n\
  On Python 3 and on Python 2 when the value is not a true file object,\n\
  ``WRITEDATA`` is emulated in PycURL via ``WRITEFUNCTION``.\n\
  The file should generally be opened in binary mode. Example::\n\
\n\
    f = open('/dev/null', 'wb')\n\
    c.setopt(c.WRITEDATA, f)\n\
\n\
- ``*FUNCTION`` options accept a function. Supported callbacks are documented\n\
  in :ref:`callbacks`. Example::\n\
\n\
    # Python 2\n\
    import StringIO\n\
    b = StringIO.StringIO()\n\
    c.setopt(pycurl.WRITEFUNCTION, b.write)\n\
\n\
- ``SHARE`` option accepts a :ref:`curlshareobject`.\n\
\n\
It is possible to set integer options - and only them - that PycURL does\n\
not know about by using the numeric value of the option constant directly.\n\
For example, ``pycurl.VERBOSE`` has the value 42, and may be set as follows:\n\
\n\
    c.setopt(42, 1)\n\
\n\
*setopt* can reset an option to its default value, performing the job of\n\
:py:meth:`pycurl.Curl.unsetopt`, if ``None`` is passed\n\
for the option value. The following two calls are equivalent:\n\
\n\
    c.setopt(c.URL, None)\n\
    c.unsetopt(c.URL)\n\
\n\
Raises TypeError when the option value is not of a type accepted by the\n\
respective option, and pycurl.error exception when libcurl rejects the\n\
option or its value.\n\
\n\
.. _curl_easy_setopt: http://curl.haxx.se/libcurl/c/curl_easy_setopt.html";

PYCURL_INTERNAL const char curl_unsetopt_doc[] = "unsetopt(option) -> None\n\
\n\
Reset curl session option to its default value.\n\
\n\
Only some curl options may be reset via this method.\n\
\n\
libcurl does not provide a way to reset a single option to its default value;\n\
:py:meth:`pycurl.Curl.reset` resets all options to their default values,\n\
otherwise :py:meth:`pycurl.Curl.setopt` must be called with whatever value\n\
is the default. For convenience, PycURL provides this unsetopt method\n\
to reset some of the options to their default values.\n\
\n\
Raises pycurl.error exception on failure.\n\
\n\
``c.unsetopt(option)`` is equivalent to ``c.setopt(option, None)``.";

PYCURL_INTERNAL const char multi_doc[] = "CurlMulti() -> New CurlMulti object\n\
\n\
Creates a new :ref:`curlmultiobject` which corresponds to\n\
a ``CURLM`` handle in libcurl.";

PYCURL_INTERNAL const char multi_add_handle_doc[] = "add_handle(Curl object) -> None\n\
\n\
Corresponds to `curl_multi_add_handle`_ in libcurl. This method adds an\n\
existing and valid Curl object to the CurlMulti object.\n\
\n\
IMPORTANT NOTE: add_handle does not implicitly add a Python reference to the\n\
Curl object (and thus does not increase the reference count on the Curl\n\
object).\n\
\n\
.. _curl_multi_add_handle:\n\
    http://curl.haxx.se/libcurl/c/curl_multi_add_handle.html";

PYCURL_INTERNAL const char multi_close_doc[] = "close() -> None\n\
\n\
Corresponds to `curl_multi_cleanup`_ in libcurl. This method is\n\
automatically called by pycurl when a CurlMulti object no longer has any\n\
references to it, but can also be called explicitly.\n\
\n\
.. _curl_multi_cleanup:\n\
    http://curl.haxx.se/libcurl/c/curl_multi_cleanup.html";

PYCURL_INTERNAL const char multi_fdset_doc[] = "fdset() -> tuple of lists with active file descriptors, readable, writeable, exceptions\n\
\n\
Returns a tuple of three lists that can be passed to the select.select() method.\n\
\n\
Corresponds to `curl_multi_fdset`_ in libcurl. This method extracts the\n\
file descriptor information from a CurlMulti object. The returned lists can\n\
be used with the ``select`` module to poll for events.\n\
\n\
Example usage::\n\
\n\
    import pycurl\n\
    c = pycurl.Curl()\n\
    c.setopt(pycurl.URL, \"http://curl.haxx.se\")\n\
    m = pycurl.CurlMulti()\n\
    m.add_handle(c)\n\
    while 1:\n\
        ret, num_handles = m.perform()\n\
        if ret != pycurl.E_CALL_MULTI_PERFORM: break\n\
    while num_handles:\n\
        apply(select.select, m.fdset() + (1,))\n\
        while 1:\n\
            ret, num_handles = m.perform()\n\
            if ret != pycurl.E_CALL_MULTI_PERFORM: break\n\
\n\
.. _curl_multi_fdset:\n\
    http://curl.haxx.se/libcurl/c/curl_multi_fdset.html";

PYCURL_INTERNAL const char multi_info_read_doc[] = "info_read([max_objects]) -> tuple(number of queued messages, a list of successful objects, a list of failed objects)\n\
\n\
Returns a tuple (number of queued handles, [curl objects]).\n\
\n\
Corresponds to the `curl_multi_info_read`_ function in libcurl. This\n\
method extracts at most *max* messages from the multi stack and returns them\n\
in two lists. The first list contains the handles which completed\n\
successfully and the second list contains a tuple *(curl object, curl error\n\
number, curl error message)* for each failed curl object. The number of\n\
queued messages after this method has been called is also returned.\n\
\n\
.. _curl_multi_info_read:\n\
    http://curl.haxx.se/libcurl/c/curl_multi_info_read.html";

PYCURL_INTERNAL const char multi_perform_doc[] = "perform() -> tuple of status and the number of active Curl objects\n\
\n\
Corresponds to `curl_multi_perform`_ in libcurl.\n\
\n\
.. _curl_multi_perform:\n\
    http://curl.haxx.se/libcurl/c/curl_multi_perform.html";

PYCURL_INTERNAL const char multi_remove_handle_doc[] = "remove_handle(Curl object) -> None\n\
\n\
Corresponds to `curl_multi_remove_handle`_ in libcurl. This method\n\
removes an existing and valid Curl object from the CurlMulti object.\n\
\n\
IMPORTANT NOTE: remove_handle does not implicitly remove a Python reference\n\
from the Curl object (and thus does not decrease the reference count on the\n\
Curl object).\n\
\n\
.. _curl_multi_remove_handle:\n\
    http://curl.haxx.se/libcurl/c/curl_multi_remove_handle.html";

PYCURL_INTERNAL const char multi_select_doc[] = "select([timeout]) -> number of ready file descriptors or -1 on timeout\n\
\n\
Returns result from doing a select() on the curl multi file descriptor\n\
with the given timeout.\n\
\n\
This is a convenience function which simplifies the combined use of\n\
``fdset()`` and the ``select`` module.\n\
\n\
Example usage::\n\
\n\
    import pycurl\n\
    c = pycurl.Curl()\n\
    c.setopt(pycurl.URL, \"http://curl.haxx.se\")\n\
    m = pycurl.CurlMulti()\n\
    m.add_handle(c)\n\
    while 1:\n\
        ret, num_handles = m.perform()\n\
        if ret != pycurl.E_CALL_MULTI_PERFORM: break\n\
    while num_handles:\n\
        ret = m.select(1.0)\n\
        if ret == -1:  continue\n\
        while 1:\n\
            ret, num_handles = m.perform()\n\
            if ret != pycurl.E_CALL_MULTI_PERFORM: break";

PYCURL_INTERNAL const char multi_socket_action_doc[] = "socket_action(sockfd, ev_bitmask) -> Tuple.\n\
\n\
Returns result from doing a socket_action() on the curl multi file descriptor\n\
with the given timeout.";

PYCURL_INTERNAL const char multi_socket_all_doc[] = "socket_all() -> Tuple.\n\
\n\
Returns result from doing a socket_all() on the curl multi file descriptor\n\
with the given timeout.";

PYCURL_INTERNAL const char pycurl_global_cleanup_doc[] = "global_cleanup() -> None\n\
\n\
Cleanup curl environment.\n\
\n\
Corresponds to `curl_global_cleanup`_ in libcurl.\n\
\n\
.. _curl_global_cleanup: http://curl.haxx.se/libcurl/c/curl_global_cleanup.html";

PYCURL_INTERNAL const char pycurl_global_init_doc[] = "global_init(option) -> None\n\
\n\
Initialize curl environment.\n\
\n\
*option* is one of the constants pycurl.GLOBAL_SSL, pycurl.GLOBAL_WIN32,\n\
pycurl.GLOBAL_ALL, pycurl.GLOBAL_NOTHING, pycurl.GLOBAL_DEFAULT.\n\
\n\
Corresponds to `curl_global_init`_ in libcurl.\n\
\n\
.. _curl_global_init: http://curl.haxx.se/libcurl/c/curl_global_init.html";

PYCURL_INTERNAL const char pycurl_module_doc[] = "This module implements an interface to the cURL library.\n\
\n\
Types:\n\
\n\
Curl() -> New object.  Create a new curl object.\n\
CurlMulti() -> New object.  Create a new curl multi object.\n\
CurlShare() -> New object.  Create a new curl share object.\n\
\n\
Functions:\n\
\n\
global_init(option) -> None.  Initialize curl environment.\n\
global_cleanup() -> None.  Cleanup curl environment.\n\
version_info() -> tuple.  Return version information.";

PYCURL_INTERNAL const char pycurl_version_info_doc[] = "version_info() -> tuple\n\
\n\
Returns a 12-tuple with the version info.\n\
\n\
Corresponds to `curl_version_info`_ in libcurl. Returns a tuple of\n\
information which is similar to the ``curl_version_info_data`` struct\n\
returned by ``curl_version_info()`` in libcurl.\n\
\n\
Example usage::\n\
\n\
    >>> import pycurl\n\
    >>> pycurl.version_info()\n\
    (3, '7.33.0', 467200, 'amd64-portbld-freebsd9.1', 33436, 'OpenSSL/0.9.8x',\n\
    0, '1.2.7', ('dict', 'file', 'ftp', 'ftps', 'gopher', 'http', 'https',\n\
    'imap', 'imaps', 'pop3', 'pop3s', 'rtsp', 'smtp', 'smtps', 'telnet',\n\
    'tftp'), None, 0, None)\n\
\n\
.. _curl_version_info: http://curl.haxx.se/libcurl/c/curl_version_info.html";

PYCURL_INTERNAL const char share_doc[] = "CurlShare() -> New CurlShare object\n\
\n\
Creates a new :ref:`curlshareobject` which corresponds to a\n\
``CURLSH`` handle in libcurl. CurlShare objects is what you pass as an\n\
argument to the SHARE option on :ref:`Curl objects <curlobject>`.";

PYCURL_INTERNAL const char share_close_doc[] = "close() -> None\n\
\n\
Close shared handle.\n\
\n\
Corresponds to `curl_share_cleanup`_ in libcurl. This method is\n\
automatically called by pycurl when a CurlShare object no longer has\n\
any references to it, but can also be called explicitly.\n\
\n\
.. _curl_share_cleanup:\n\
    http://curl.haxx.se/libcurl/c/curl_share_cleanup.html";

PYCURL_INTERNAL const char share_setopt_doc[] = "setopt(option, value) -> None\n\
\n\
Set curl share option.\n\
\n\
Corresponds to `curl_share_setopt`_ in libcurl, where *option* is\n\
specified with the ``CURLSHOPT_*`` constants in libcurl, except that the\n\
``CURLSHOPT_`` prefix has been changed to ``SH_``. Currently, *value* must be\n\
either ``LOCK_DATA_COOKIE`` or ``LOCK_DATA_DNS``.\n\
\n\
Example usage::\n\
\n\
    import pycurl\n\
    curl = pycurl.Curl()\n\
    s = pycurl.CurlShare()\n\
    s.setopt(pycurl.SH_SHARE, pycurl.LOCK_DATA_COOKIE)\n\
    s.setopt(pycurl.SH_SHARE, pycurl.LOCK_DATA_DNS)\n\
    curl.setopt(pycurl.URL, 'http://curl.haxx.se')\n\
    curl.setopt(pycurl.SHARE, s)\n\
    curl.perform()\n\
    curl.close()\n\
\n\
Raises pycurl.error exception upon failure.\n\
\n\
.. _curl_share_setopt:\n\
    http://curl.haxx.se/libcurl/c/curl_share_setopt.html";

