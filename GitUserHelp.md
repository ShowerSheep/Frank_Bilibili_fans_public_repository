First install Git on your computer.
You can find the installation package in the software in the BS profile of the group file.
After installation, find the location you plan to download on your computer.
Right-click and select Git Bash Here.
Input command: 
    git clone https://github.com.cnpmjs.org/MonsterXia/Frank_Bilibili_fans_public_repository.git
If you have cloned the library, but the remote library has changed, please use the following code to update your local library:
    git pull
Then you can see the files you want in the local folder.

For new developers:
If this is your first time uploading code, please enter the following code to link to the remote library, otherwise please skip this step:
    git remote add origin https://github.com/MonsterXia/Frank_Bilibili_fans_public_repository.git

We recommend that you use these two commands to log in at the beginning:
(Please enter your username and email address in the appropriate places in the instructions below.)
    git config --global user.name "......"
    git config --global user.email "......";
If you create a new file in the local library, please use the command: 
    git add -A
When you have finished modifying the file, please use the following commands to save your changes to the local library:
(Please enter the remarks you have modified this time in single quotes. You can choose to leave the single quotes blank, but we still recommend filling in to let others know what you did.)
    git commit -a -m ''
Finally, use the following code to synchronize the local library to the remote library (Github):
    git push
(This step may ask you to fill in your Github account password. This is normal, please fill in normally.)

