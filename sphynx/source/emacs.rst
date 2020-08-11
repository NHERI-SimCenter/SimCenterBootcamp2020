

.. _lblHelp:

*****
Emacs
*****

`Emacs <https://www.gnu.org/software/emacs/>`_, which has been under development from the 1970's, is a basic text editor and hugely popular on Unix systems. It is an immensely powerful text editor and is available on all TACC login nodes along with it's main contender for favorite programmers editor **vi**. For editing files at TACC we will be using this editor.

The following are how to start emacs from the terminal:

    1. To start the emacs application with no file loaded:

    .. code::

       emacs

    2. To start the emacs application with some file named **filename** located in the current directory opened in the editor:

    .. code::

       emacs filename

Once inside emacs, you are in a mode similar to INSERT in vi. You can use up, and sideways keys to move the cursor around the characters of the file. There are a number of options available to you through use of either the **<Control>** key or the **<Escape>** key that perform certain common file editor operations. Emacs has over 10,000 built in commands! Only a dozen or so commands are needed for most editing purposes. The following is a list of my most used commands. This short list are more than sufficient for most editing purposes.

1. Quit application (will prompt to save files):

.. code::

   <Control> x <Control> c

2. Save current file:

.. code::

   <Control> x <Control> s

3. Delete from current cursor to end of line (copies to clipboard). Will append to clipboard if lines follow one another.

.. code::

   <Control> k

4. Delete from current cursor to end of line and delete next n-1 lines. note n is a number.

.. code::

   <Escape> n <Control> k

5. Paste clipboard to current cursor location

.. code::

   <Control> y

6. Undo last command

.. code::

   <Control> x u

7. Move cursor to start of line

.. code::

   <Control> a

8. Move cursor to end of line

.. code::

   <Control> e


9. Move cursor to start of file

.. code::

   <Escape> <

10. Move cursor to end of file

.. code::

   <Escape> >

11. Search for text **blah** in file forwards from current cursor

.. code::

   <Control> s blah


12. Search for text **blah** in file backwards from current cursor

.. code::

   <Control> r blah

13. Find and replace text from current cursor location.

.. code::

   <Escape> % 

14. Find and replace text from current cursor location. (avoiding lucky 13!)

.. code::

   <Escape> x replace-string <RET>

There are of course more commands available (over 10,000!). But those are some basic ones and enough to get you merrily editing files!





