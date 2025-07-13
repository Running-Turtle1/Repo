以 `CentOS7` 为例，执行以下语句 :

```bash
yum install gcc
```

如果下载不成功，并且网络没有问题。

执行以下语句 :

```bash
cp -r /etc/yum.repos.d /etc/yum.repos.d.bak

rm -f /etc/yum.repos.d/*.repo

curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-7.repo

yum clean all

yum makecache

yum update
```

然后检查 yum 源速度 :

```bash
yum repolist
```

出现以下就没有问题了

```textile
yum repolist                                                            
已加载插件：fastestmirror                                                                 
Loading mirror speeds from cached hostfile                                                
 * base: mirrors.aliyun.com                                                               
 * extras: mirrors.aliyun.com                                                             
 * updates: mirrors.aliyun.com                                                            
源标识                        源名称                                                状态  
base/7/x86_64                 CentOS-7 - Base - mirrors.aliyun.com                  10,072
extras/7/x86_64               CentOS-7 - Extras - mirrors.aliyun.com                   526
updates/7/x86_64              CentOS-7 - Updates - mirrors.aliyun.com                6,173
repolist: 16,771                      

```

在配置一下下面的

```bash
1、直接关闭防火墙
systemctl stop firewalld

2、禁止firewall开机启动
systemctl disable firewalld

3、查看状态
systemctl status firewalld #出现dead表示关闭成功

11.关闭selinux


```
