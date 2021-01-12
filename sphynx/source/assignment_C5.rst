C: Tapis-cli
============

.. note::

   Initial setup is required of the **Tapis-cli**. This is done by invoking the dollowing in a linux (see warning below) shell. For some systems, i.e. **ubuntu** you should use **pip3** instead of **pip**:

   .. code:: 

       pip install tapis-cli

 
 Once the cli is installed you need to configure it to use deignsafe and you need to provide your username and password:

   .. code::  

      tapis auth init

   The application will prompt for a number of things. For tenant enter **designsafe**, for username and password your DesignSafe username and password. For others, ignore by just hitting enter.

.. warning:: 

   If you fail in last part of first exercise it means that the **tapis-cli** is not going to work. You can still use the fwork you have done up until this point, but you need to do something different. We provide 3 solutions, in order of time to proceed:

   1. Try and update to the latest version of **tapis-cli**:

     .. code::

        git clone https://github.com/TACC-Cloud/tapis-cli.git
        $ cd tapis-cli
        $ pip install --upgrade .
   
   2. Run exercise at TACC using either Frontera or Stampede2. To do this you need to install **tapis-cli** as a local user.


     .. code::

	pip intall tapis-cli --user
      
   3. Install and use the **Ubuntu subsystem on Windows 10**

   The Ubuntu subsystem is actually a full Ubuntu linux system running within a virtual machine while
   Windows is running as the primary OS. Microsoft provides step-by-step instructions on how to install
   it on your Windows system.  See
   `https://docs.microsoft.com/en-us/windows/wsl/install-win10 <https://docs.microsoft.com/en-us/windows/wsl/install-win10>`__
   for details.
 
   :red:`Warning`: If you are running Windows in a virtual environment such as VMware or Parallels,
   installing the Ubuntu subsystem in Windows will fail.  Install Ubuntu in a separate virtual machine
   instead.


Today we have a number of exercises. The purpose of these exercisess is to set it up so that you are able to run your parallel application on Frontera or Stampede2 by issuing commands in the terminal of your desktop. Time permitting we will share the applications with fellow classmates. The advantage of beong able to do this from a terminal is convenience and speed. In addition, for those teaching, you can set the applications up for others, i.e. students to use your applications.

There are 5 steps to this process that follow the videos presented for class (that are enclosed in hints herein):

Step 1: Setting Up an Execution System
--------------------------------------

Tapis provides **systems** which provide access to the file systems and hardware resources, e.g. Frontera and Stampede, at TACC. For our **Storage System** we will be using the default provided by DesignSafe (designsafe.storage.default). In this exercise we are going to create an execution system by providing a .json file containing basic information to one of our machine logins, e.g. username, password, and locations within our machine account of directories to place temporary files (the location the files are placed when we run an app).


Before you create a system, you might want to issue some tapis commands to get comfortable with the tapis-cli.

   .. code::
      
      tapis -h
      tapis systems -h
      tapis systems search --default eq true
      tapis systems show designsafe.storage.default
      tapis systems list      
      tapis systems search --execution-type eq HPC


You first need to edit a file provided in the **code/agave/** agave directory. We have two template systems to chooose from , **fronteraSystem.json** and **stampede2Syatem.json**, which to use depends on which TACC system you have been logging into.

The Frontera file is shown below:

.. literalinclude:: ./assignments/c5/fronteraSystem.json
  :language: json
  :linenos:

In this file you need to search for the following and replace them with appropriate text. The **${ALLOCATION}** text is replaced with **-A FTA-DD-SimCenter** if using Frontera.

These are the four values that need to be replaced:

${USERNAME}, 
${PASSWORD}, 
${SCRATCH_DIR} and
${ALLOCATION}.

The scratch_dir can be found by logging into Frontera, issuing the commands cds (change dir to scratch) and then pwd (print working directory). The results of pwd is your scratch dir.

Once the file has been completed, you can create the system by invoking one of the the following command.


for Frontera:

 .. code::
  
      tapis systems create  -F fronteraSystem.json

 Now have a look for it. In the file we named it demo something.

 .. code::

    tapis systems search --name like demo -f json

 The system should appear in what is returned.


Thats it, congratulations you have created an execution system.


.. warning::

   Never check the file into github unless you remove your **password**.

.. hint::

   A demonstartion is contained at end of the Video

   .. raw:: html
	 
       <p><iframe width="560" height="315" src="https://www.youtube.com/embed/TddwsA5MY_I" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>


   
Step 2: Exploring File System Commands
--------------------------------------

Tapis provide commands for doing file operartions. It providess commands for uploading and downloading files to and from the storage systems as well as typical commands dealing with file system opeartions at thr remove stoarge system.

Some commands we would like you to try.

Begin by listing the files in your home directory

.. code::

   tapis files list agave://designsafe.storage.default/YOUR_NAME

Add a directory tmp to your home folder at DesignSafe

.. code::

   tapis files mkdir agave://designsafe.storage.default/YOUR_NAME tmp

Copy a small file **SimCenterBootcamp2020/code/agave/ExerciseDays4/ex1/piMPI.c** to your current directory. From there send it to your new folder at DesignSafe.

.. code::

   tapis files upload agave://designsafe.storage.default/YOUR_NAME/tmp  piMPI.c

.. note::

   We will be using this file in our app. We compile it and run it. If yours worked from yesterday, upload your file instead. It makes the exercise somewhat more meaningful. If your file has a different name, you should be able to identify what small change you have to make in the **submitClone.json** file you will edit later.
   
Remove your local copy and try and copy the file you just uploaded.

.. code::

   tapis files download agave://designsafe.storage.default/YOUR_NAME/tmp/piMPI.c

List the other **tapis** file commands and explore what they do.

.. code::

   tapis files -h


.. hint::

   A demonstartion is contained at end of the Video   

   .. raw:: html
	 
         <p><iframe width="560" height="315" src="https://www.youtube.com/embed/eh7Etvuvo7E" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>

   

Step 3: Build a Tapis app
-------------------------

A Tapis **apps** is a containerized application. Each app has a description that describes it's name, inputs and parameters. This description can be obtained using the **tapis apps show** command. The description contains information about where the container for the application resides, inputs and outputs, information about the execution system on which the app will run and  and information about the bash script, **wrapper.sh**. **wrapper.sh** is the sript that is run when the application is started running at a HPC resource. **wrapper.sh** will have access to all the files in the app container when it is run.

We are going a tapis container application we are going to use some tapis apps and files comamnds to do so. To build our app, like all programmers do, we are going to start by cloning an existing one that has similar inputs to the one we want, basically an input directory and a parameter. We will name the app **mpiCompileRun** and associate it with the exe srvice we created in exercise 1. (You will need the name). Use the following command to see what is needed.


The app we have in mind is one that will compile a program we have uploaded **piMPI.c** say and run it. A wrapper.sh file for this purpose is shown below:


We are first going to search for an app to clone. Let us look at simcenter apps.

.. code::
   
   tapis apps search --name like simcenter -f json

You should see one with an id **simcenter-dakota-1.0.0u1**. Have a look at it's description.

.. code::
   
   tapis apps show simcenter-dakota-1.0.0u1 -f json

You will see it takes an input directory and some parameters to run. We will use it to clone our app. Have a look at the inputs for **tapis apps clone** with the following:

.. code::

      tapis apps clone -h

After having reviewed results of previous, you should be able to understand the following. The command to clone is some **modifications based on your account**, i.e. the -e refers to the execution service and for that you need to enter the **id** of the execution service you created. Also replace YOUR_NAME with yor login name:

.. code:: 

   tapis apps clone -e designsafe.demo.exec.frontera.fmk -n mpiCompileRunYOUR_NAME -x 0.0.1  simcenter-dakota-1.0.0u1

Having cloned the app, let us look at it's description to see the inputs and outputs. We can get this description using the following:

.. note::

   Your name is not needed, it will be used in part 5 so that we can share applications and as such we will want to be able to distinguish between applications. For normal application development, you may not need or want it.

.. code::
   
   tapis apps show -f json mpiCompileRunYOUR_NAME-0.0.1 > mpiCompileRunYOUR_NAME.json

This command as placed the description of the **mpiCompileRun** to json file mpiCompileRun.json. Open it up and have a look. You will see the input and parameters section for this app. Also you will see the application directory, which is in your home/applications foler at designsafe. From the application directory download the wrapper.sh script. We will modify it a bit. We will only have one input parameter **inputFile**.

.. code::

   tapis files upload agave://designsafe.storage.default/YOUR_NAME/applications/mpiCompileRunYOUR_NAME-0.0.1 wrapper.sh

After editing the app description file, we can update the app.

.. code::

   tapis apps update -F mpiCompileRun.json mpiCompileRun-0.0.1

We now have an application ready and wating to compile our code and run it!

.. hint::

   A demonstartion is contained at end of the Video

   .. raw:: html
	 
        <p><iframe width="560" height="315" src="https://www.youtube.com/embed/f2-Qg6sMsQM" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>


Step 4: Submitting a Job
------------------------

Now we want to actually submit a job and have it compile and run on a HPC. In the **code/agave** folder there is a file **piMPI.c** and a json file **cloneSubmit.json**. The **piMPI.c** we have alredy used in files and placed in a demo folder at designsafe off our remote home folder. To submit a job to run at TACC through tapis we need to create the input file telling tapis what to do. The input file is application specific. An input file template for our app is found in **cloneSubmit.json** which is shown below:

.. literalinclude:: ./assignments/c5/cloneSubmit.json
  :language: json
  :linenos:

There are 3 lines in this file needing changing. In Line 3 you need to set the **appID** to be equal to name of the app you created in step 3. You need to set the **inputDirectory** equal to the location you placed the **piMPI.c** file on line 5 and finally the name of the program to compile and run **programName** needs to be set on line 8. Other options are set for the piMPI application such as runTime, numNodes and numCores.

After file has been saved the use submits it to tapis job service by typing the following:

.. code::

   tapis jobs submit -F cloneSubmit.json

Tapis will respond with a message that hopefully says job was submitted sucessfully and will provide a **jobID**. That **jobID** is important, as you will use it to query status of job and download job information when job finished.

To look up job status, type:

.. code::

   tapis jobs status -f json 5ce7f59d-0c4f-46c1-806a-35965317525f-007

There are a number of states a job might be in, **queued**, **running**, **finished**, and the dreaded **failed**. Once a job has finished you can download the results with
     

tapis jobs  show –f json 5ce7f59d-0c4f-46c1-806a-35965317525f-007

This results in a long list of output. Buried in it is the **archivePath** section. This is where the results have been stored.

.. code:: 

     "accepted": "2021-01-08T10:19:45.773Z",
     "appId": "mpiCompileSimCenter-0.0.1",
     "appUuid": "7984683744829894165-242ac117-0001-005",
     "archive": true,
     "archivePath": "tg457427/archive/jobs/job-507792d1-35b0-4dc0-abd2-421cfba7ddc3-007",
     "archiveSystem": "designsafe.storage.default",
     "blockedCount": 0,
     "created": "2021-01-08T10:19:45.779Z",
     "ended": "7 hours ago",


The results folder can be viewed using the **tapis files list** command, i.e. for my job I would list the files in the following way:

.. code::

   tapis files list agave://designsafe.storage.default/tg457427/archive/jobs/job-507792d1-35b0-4dc0-abd2-421cfba7ddc3-007

In this folder you will see a long file name ending in **.out**. This you can download with the **tapis files download**. The results of the file I submitted is as shown below.


.. literalinclude:: ./assignments/c5/results.json
  :language: json
  :linenos:


.. hint::

   A demonstartion is contained at end of the Video
     
   .. raw:: html
	 
      <p><iframe width="560" height="315" src="https://www.youtube.com/embed/HDo5QzwOjTc" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe></p>

     
Step 5: Allowing Others to Use your App
---------------------------------------

Sharing of resources is something built into **Tapis**, which  allows researchers to share resoures (execution sytems, files, and apps). Check out the following commands:

.. code::
   
        tapis files pems drop
        tapis files pems grant
        tapis files pems list
        tapis files pems revoke
        tapis files pems show
        tapis systems roles drop
        tapis systems roles grant
        tapis systems roles list
        tapis systems roles revoke
        tapis systems roles show
        tapis apps pems grant
        tapis apps pems list
        tapis apps pems revoke
        tapis apps pems show

.. note::

   There are other tapis options that will allow you to **publish** and **unpblish** your resources, but these are not available to you to use.

For this exercise you need to select a partner, each of you need to swap usernames. You are then going to allow your partner to use your app and then you are going to run your job with their app.

To first look at your existing permissions issue the following:

.. code::

   tapis apps pems show mpiCompileRunYOUR_NAME-0.0.1

To add someone to your app who can execute issue

.. code::

   tapis apps pems show mpiCompileRunYOUR_NAME-0.0.1

You should see something like:

.. code::

   +----------+------+-------+---------+
   | username | read | write | execute |
   +----------+------+-------+---------+
   | tg457427 | True | True  | True    |
   +----------+------+-------+---------+


Now to allow the user fmk to execute your app, you would issue the command shown below. Change **fmk** to your partners name and issue the following:

   .. code::

   tapis apps pems grant mpiCompileRunYOUR_NAME-0.0.1 fmk EXECUTE


Now you should see something like:

.. code::

   +----------+-------+-------+---------+
   | username | read  | write | execute |
   +----------+-------+-------+---------+
   | tg457427 | True  | True  | True    |
   | fmk      | False | False | True    |
   +----------+-------+-------+---------+

Now see if you can figure out how to do the following:

#. Find your partners application using tapis apps search

#. Edit your job script to point to your partners app.

#. Launch the job using your partners application.

#. Check your program still works!


   


