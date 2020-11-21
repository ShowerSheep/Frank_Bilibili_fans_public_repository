# VMware WorkStation PRO 安装MacOS系统

######      																												发布：Monster_Xia

## ·   示例部署环境: 

 VMware-workstation-full-16.0.0-16894299

MacOS Catalina-10.15.7(19H2)

Win10 1909

## ·   解锁工具：

- - ### VMware15及以下版本：

  - - https://github.com/paolo-projects/unlocker/releases
    - 下载完成后，解压unlocker.zip文件，并选择以管理员身份运行打开win-install.cmd文件

  - ### VMware16：

  - - https://github.com/paolo-projects/auto-unlocker/releases
    - 下载完成后，解压Unlocker.zip文件，并选择以管理员身份运行打开Unlocker文件

## ·   具体解锁：

- - ### 运行前请务必打开任务管理器，关闭所有VMware进程，然后运行解锁工具开始解锁任务并下载相关文件

  - ### 如果解锁过程中出现下载慢或者部分文件无法下载请执行一下操作：

  - #### 使用浏览器打开网址：

    - http://softwareupdate.vmware.com/cds/vmw-desktop/fusion/
    - 选择列表中最大的版本
    - 点击数字
    - 点击core
    - 将com.vmware.fusion.zip.tar文件下载到本地
    - 解压压缩文件
    - 运行Unlocker后会产生tools文件夹，在解压出来的文件夹中找到darwin.iso和darwinPre15.iso两个文件，将其复制到tools文件夹下
    - 再将darwin.iso和darwinPre15.iso文件复制到WMware的安装目录中，然后用管理员权限运行一下        Unlocker
    - 出现A backup        folder…….输入Y回车

#### ·   至此你的VMware已经能够安装MacOS系统

### ·   请注意：MacOS系统使用的镜像文件不是iso，而是cdr（Apple原生的系统文件格式是dmg，而对VMware来说不支持安装dmg格式文件，因此你需要找到cdr格式的系统镜像文件）

#### ·   此处提供MacOS Catalina-10.15.7(19H2)的镜像文件下载地址：

- - https://pan.baidu.com/s/1RN3UWna9KlfJZrEOUQ-jlA 
  - 提取码：jcjm