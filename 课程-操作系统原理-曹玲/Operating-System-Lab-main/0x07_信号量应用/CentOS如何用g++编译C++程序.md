1，打开下载权限

```bash
su root
```

2，更新包管理器

```bash
sudo yum update
```

3，安装开发工具包（包含 g++) :

```bash
sudo yum groupinstall "Development Tools"
```

也可以只安装 `g++` :

```bash
sudo yum install gcc-c++
```

4，检查是否安装成功

```bash
g++ --version
```


