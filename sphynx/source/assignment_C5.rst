C: Tapis-cli
============

.. note::

   Initial setup is required of the **Tapis-cli**. This is done by invoking the dollowing in a linux (see warning below) shell:

   .. code:: 

       pip install tapis-cli

 Once the cli is installed you need to configure it to use deignsafe and you need to provide your username and password:

   .. code::  

      tapis auth init

   The application will prompt for a number of things. For tenant enter **designsafe**, for username and password your DesignSafe username and password. For others, ignore by just hitting enter.


Today we have a number of exercises. The purpose of these exercisess is to set it up so that you are able to run your parallel application on Frontera or Stampede2 by issuing commnds in the terminal of your desktop utilizing DesignSafe resources for storing files and results.


.. warning:: 

   At time of writing, the **-F** option was failing **tapis** commands for all python versions tested running on Windows. Try the command, if not fixed you will have to install the **Ubuntu system for Windows** and run this exercise from a Ubutu shell. If that fails, you can complete the exercise logged into Frontera or Stampede2!
      
.. tip::

   **How to install the Ubuntu subsystem on Windows 10**

   The Ubuntu subsystem is actually a full Ubuntu linux system running within a virtual machine while
   Windows is running as the primary OS. Microsoft provides step-by-step instructions on how to install
   it on your Windows system.  See
   `https://docs.microsoft.com/en-us/windows/wsl/install-win10 <https://docs.microsoft.com/en-us/windows/wsl/install-win10>`__
   for details.
 
   :red:`Warning`: If you are running Windows in a virtual environment such as VMware or Parallels,
   installing the Ubuntu subsystem in Windows will fail.  Install Ubuntu in a separate virtual machine
   instead.

There are 4 steps to this process that follow the videos presented in class:

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

In this file you need to search for the following and replace them with appropriate text. The **${ALLOCATION}** text is replaced with **-A FTA-DD-SimCenter** if using Frontera and with **-A **:

${USERNAME}, 
${PASSWORD}, 
${SCRATCH_DIR} and
${ALLOCATION}.

Once the file has been completed, you can create the system by invoking one of the the following command.


for Frontera:

 .. code::
  
      tapis systems create  -F fronteraSystem.json

 Now have a look for it. In the file we named it demo something.

 .. code::

    tapis systems search --name like demo -f json

 The system should appear in what is returned.


Thats it, congratulations you have created an execution system.


.. note::

   To change name of app for subsequent use, you can edit the app id on line **37**, you just cannot use an existing name.
   
.. warning::

   Never check the file into github unless you remove your **password**.


Step 2: Exploring File System Commands
--------------------------------------

Tapis provide commands for doing file operartions. It providess commands for uploading and downloading files to and from the storage systems as well as typical commands dealing with file system opeartions at thr remove stoarge system.

Some commands we would like you to try.

Begin by listing the files in your home directory

.. code::

   tapis files list agave://designsafe.storage/default/YOUR_NAME

Add a directory tmp to your home folder at DesignSafe

.. code::

   tapis files mkdir agave://designsafe.storage/default/YOUR_NAME tmp

Copy a small file **SimCenterBootcamp2020/code/agave/ExerciseDays4/ex1/mpiPI.c** to your current directory. From there send it to your new folder at DesignSafe.

.. code::

   tapis files upload agave://desihnsafe.storage/default/YOUR_NAME/tmp  mpiPI.c

Remove your local copy and try and copy the file you just uploaded.

.. code::

   tapis files download agave://designsafe.storage/default/YOUR_NAME/tmp/mpiPI.c

List the other **tapis** file commands and explore what they do.

.. code::

   tapis files -h



Step 3: Build a Tapis app
-------------------------

A Tapis **apps** is a containerized application. Each app has a description that describes it's name, inputs and parameters. This description can be obtained using the **tapis apps show** command. The description contains information about where the container for the application resides, inputs and outputs, information about the execution system on which the app will run and  and information about the bash script, **wrapper.sh**. **wrapper.sh** is the sript that is run when the application is started running at a HPC resource. **wrapper.sh** will have access to all the files in the app container when it is run.

We are going a tapis container application we are going to use some tapis apps and files comamnds to do so. To build our app, like all programmers do, we are going to start by cloning an existing one that has similar inputs to the one we want, basically an input directory and a parameter. We will name the app **mpiCompileRun** and associate it with the exe srvice we created in exercise 1. (You will need the name). Use the following command to see what is needed.


The app we have in mind is one that will compile a program we have uploaded **mpiPI.c** say and run it. A wrapper.sh file for this purpose is shown below:


We are first going to search for an app to clone. Let us look at simcenter apps.

.. code::
   
   tapis apps search --name like simcenter -f json

You should see one with an id **simcenter-dakota-1.0.0u1**. Have a look at it's description.

.. code::
   
   tapis apps show simcenter-dakota-1.0.0u1 -f json

You will see it takes an input directory and some parameters to run. We will use it to clone our app. Have a look at the inputs for **tapis apps clone** with the following:

.. code::

      tapis apps clone -h

After having reviewed results of previous, you should be able to understand the following. The command to clone is some modifications based on your account to the following:

.. code:: 

   tapis apps clone -e designsafe.demo.exec.frontera.fmk -n mpiCompileRun -x 0.0.1  simcenter-dakota-1.0.0u1

Having cloned the app, let us look at it's description to see the inputs and outputs. We can get this description using the following:

.. code::
   
   tapis apps show -f json mpiCompileRun-0.0.1 > mpiCompileRun.json


This command as placed the description of the **mpiCompileRun** to json file mpiCompileRun.json. Open it up and have a look. You will see the input and parameters section for this app. Also you will see the application directory, which is in your home/applications foler at designsafe. From the application directory download the wrapper.sh script. We will modify it a bit. We will only have one input parameter **inputFile**.

.. code::

   tapis files upload agave://designsafe.storage.default/YOUR_NAME/applications/mpiCompileRun-0.0.1. wrapper.sh

After editing the app description file, we can update the app.

.. code::

   tapis apps update -F mpiCompileRun.json mpiCompileRun-0.0.1

We now have an application ready and wating to compile our code and run it!
   
Step 4: Submitting a Job
------------------------

Last exercise is to actually submit a job using a file. In the **code/agave** folder there is a file **piMPI.c** and a json file **cloneSubmit.json**. The **piMPI.c** we have alredy used in files and placed in a demo folder at designsafe off our remote home folder. To submit a job to run at TACC through tapis we need to create the input file telling tapis what to do. The input file is application specific. An input file template for our app is found in **cloneSubmit.json** which is shown below:

.. literalinclude:: ./assignments/c5/cloneSubmit.json
  :language: json
  :linenos:

     
