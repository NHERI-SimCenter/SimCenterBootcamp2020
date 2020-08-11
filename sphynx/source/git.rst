.. _lblHelp:

************
Git & GitHub
************

`Git <http://git.com>`_ is the most widely used version control system today.  Version control software is software that enables programmers to manage changes to software over time. It is great for individuals as it keeps track of every modification to the code made in a special kind of database. If a mistake is made, the individual can turn back the clock and compare earlier versions of the code to help fix the mistake. Version control software is indespensible for groups of programmers working on a shared software project for it aids programmers when the programmers are making changes to the same files (seemlessly intagrating changes from different programmers when these changes are in different parts of the files and notifying developers of 'conflicts' (situations when the different programmers have made changes to same parts of the same file). Version control software is an essential part of the every-day of the modern software team's professional practices.



There are a number of places that will host your repos:
#. github
#. gitlab
#. bitbucket
#. sourceforge


Working with your Fork
----------------------




Synching your Fork with Original
--------------------------------

Say you forked a repo to start your repo and now you want to pull any changes in that repo to your own. 

#. To do so you first have to set up your locat .git repo. Open a terminal, cd to the folder containing your git repo and type in get remote -v. As shown below you should see info about your local repo.

.. code:: 

   git remote -v
   > origin  https://github.com/YOUR_USERNAME/REPO.git (fetch)
   > origin  https://github.com/YOUR_USERNAME/REPO.git (push)

#. Next step is to specify the remote upstream repo. In same terminal window type:

.. code::

   git remote add upstream https://github.com/ORIGINAL_OWNER/REPO.git

#. Now if you type git remote -v again, you should see it as part of your remotes

.. code::

   git remote -v
   > origin    https://github.com/YOUR_USERNAME/REPO.git (fetch)
   > origin    https://github.com/YOUR_USERNAME/REPO.git (push)
   > upstream  https://github.com/ORIGINAL_OWNER/REPO.git (fetch)
   > upstream  https://github.com/ORIGINAL_OWNER/REPO.git (push)


#. To Synch your Fork with the original you need to fetch the branches and their respective commits from the upstream repository. Commits to original master branch will be stored in a local branch, upstream/master.

.. code::

   git fetch upstream
   > remote: Counting objects: XX, done.
   > remote: Compressing objects: 100% (XX/XX), done.
   > remote: Total YY (delta XX), reused XX (delta 9)
   > Unpacking objects: 100% (YY/YY), done.
   > From https://github.com/ORIGINAL_OWNER/REPO
   >  * [new branch]      master     -> upstream/master


#. Switch to your own master branch, if you don't use branches you will be here so this is not necessary.

.. code::

   git checkout master
   > Switched to branch 'master'

#. Now merge the changes between the two into your local master branch

.. code::

   git merge upstream/master
   >    Updating wkflkqjflkfwlkfgq
   > Fast-forward
   >  X files changed, Y insertions(+), Z deletions(-)
   >  .....
   >  .....

.. note::
   
   Messages differ depending on your local commits

#. Finally merge any conlicts. Hopefully there are none.





