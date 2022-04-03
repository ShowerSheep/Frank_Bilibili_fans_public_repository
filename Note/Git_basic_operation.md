# 配置

## windows：

```shell
1.设置git的username和email：
git config --global user.name "*****"
git config --global user.email "****@****.com"
2.生成密匙：
ssh-keygen -t rsa -C "******@****.com"
用户.ssh文件里得到两个文件：id_rsa和id_rsa.pub
3.打开 ssh-agent 使之在后台运行
eval "$(ssh-agent -s)"
4.将私钥添加到 ssh-agent 之中
ssh-add ~/.ssh/id_rsa
5.查看并复制公钥
把id_rsa.pub文件里的内容复制到github里ssh keys
```



## Linux：

```shell
1.设置git的username和email：
git config --global user.name "*****"
git config --global user.email "****@****.com"
2.生成并配置密钥/公钥
ssh-keygen -t rsa -C "******@****.com"
    在 WSL 下生成 SSH 公钥—私钥对（将邮箱替换为你的邮箱），此时生成的 SSH 密钥默认位于 ~/.ssh 路径下，公钥为 id_rsa.pub，私钥为 id_rsa
3.打开 ssh-agent 使之在后台运行
eval "$(ssh-agent -s)"
4.将私钥添加到 ssh-agent 之中
ssh-add ~/.ssh/id_rsa
5.查看并复制公钥
cat ~/.ssh/id_rsa.pub
6.将复制的公钥信息添加到 Github/Gitee
```





# 本地改变，推到远程

##### 1、拉取远程库

```shell
git pull
```

##### 2、查看文件修改情况

```shell
git status
```

##### 3、添加文件(添加所有文件是“ . “)

```shell
git add .
```

##### 4、提交文件(xxx为提交说明)

```shell
git commit -m "xxx"
```

##### 5、推文件（同步到远程）

```shell
git push
```



## 代理设置

```shell
git config --global http.proxy http://127.0.0.1:7890
git config --global https.proxy http://127.0.0.1:7890
```

取消代理

```shell
git config --global --unset http.proxy
git config --global --unset https.proxy
```

