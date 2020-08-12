.. _lblHelp:

***
Git
***

`Git <http://git.com>`_ is the most widely used version control system today.  Version control software is software that enables programmers to manage changes to software over time. It is great for individuals as it keeps track of every modification to the code made in a special kind of database. If a mistake is made, the individual can turn back the clock and compare earlier versions of the code to help fix the mistake. Version control software is indespensible for groups of programmers working on a shared software project for it aids programmers when the programmers are making changes to the same files (seemlessly intagrating changes from different programmers when these changes are in different parts of the files and notifying developers of 'conflicts' (situations when the different programmers have made changes to same parts of the same file). Version control software is an essential part of the every-day of the modern software team's professional practices.


There are a number of places that will host your repos:

      #. github

      #. gitlab

      #. bitbucket

      #. sourceforge

Creating a Repo
---------------

For individual programmers working on a software project, the typical git eusage is to create a repo at one of the sites and point your local repo to that site. As you work with the repo you add and commit new changess to your local repo or checkout older versions of the code. At points you can send (push) your changes to github repo or pull code stored at the remote repo.

.. note::

   For purposes of documenting the commands, we will assume the remote hosting service is github.com, your user name is YOUR_USERNAME and the repo is named REPO.git

There are three options for creating a repo. 


      #. If you are part of a collaborative project, or just want to start at the state of some other open source project you find on one of the hosting sites you first **FORK** a copy of the repo into your own area. You do this in the browser. Once forked, a repo will exist in your own area which you can clone. This will bring all repo files to your computer.

      	 .. code::
   
		git clone https://github.com/YOUR_USERNAME/REPO.git

      #. If you have no existing code and want to start a new empty repo the best option is to go to the hosting site and create a repo there. Obtain the cloning address from the hosting site and then in a terminal window in directory you wish the repo folder to exist use the git clone command:

      	 .. code::
   
		git clone https://github.com/YOUR_USERNAME/REPO.git

      #. If you have existing code in a folder and wish to create a repo go again to the hosting site and create a repo. Obtain the cloing url. Then in a terminal window go to the folder whose source code you are creating the repo for. Here type the following commands to create a local repo, add the current contents of the folder, point the repo to the hosted repo, and push the files to the remote repo:

      	 .. code::
   
		git init 
		git add .
		git commit -m "First commit"
		git remote add origin https://github.com/YOUR_USERNAME/REPO.git 
		git push -u origin master


Using Your Local Repo
---------------------

Once you have created the repo there are some standard commands to use it.
To update the repo with the current state of the files:

   .. code::
   
	git add .

You can be selective here, you cam specify the files in the current folder

   .. code::
   
	git add ./

or a list of files

   .. code::
   
	git add fileName1 fileName2 .. fileNameN

Once added, all files that have been **staged** for commit, can be committed with the commit command

   .. code::
   
	git commit -m "some message as to what commit is about"


To look at the commits you have made to the repo:

   .. code::
   
	git log

To look at the last 10 commits you have made to the repo:

   .. code::
   
	git log -n 10

If you are unhappy with changes made to a file and wish to revert back to the current file in the repo

   .. code::
   
	git checkout fileName

If you are unhappy all changes made in current directory and wish to go back to one of previos commit, find that commits has and issue the following

   .. code::

      git checkout commitHash .


Working With Your Remote Repo
-----------------------------

To send the commits from your local repo to your hosted repo you issue the push command:

   .. code::
   
	git push

If you want to pull the code from your online repo and merge with your current code. Note this is more a collaborative operation. It actually does a git fetch and merge in a single operation.

   .. code::

      git pull


Synching your Fork with Original
--------------------------------

Say you forked a repo to start your remote repo and now you want to pull any changes in that repo to your own. 

.. note::

   For command deomstration purposes, we will again use github.com, the remote owner of the original forkes repo was ORIGINAL_OWNER and the repo was named REPO.git

#. To do so you first have to set up your locat .git repo. Open a terminal, cd to the folder containing your git repo and type in get remote -v. As shown below you should see info about your local repo.

.. code:: 

   git remote -v
   > origin  https://github.com/YOUR_USERNAME/REPO.git (fetch)
   > origin  https://github.com/YOUR_USERNAME/REPO.git (push)

#. Next step is to specify the remote upstream repo. In same terminal window type:

.. code::

   git remote add upstream https://github.com/ORIGINAL_OWNER/REPO.git

#. Now if you type git remote -v again, you should see it as part of your remotes.

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

#. Finally merge any conlicts. Hopefully there are none!

.. note::

   You can now update your remote repo as above using the **add**, **commit** and **push** commands.





