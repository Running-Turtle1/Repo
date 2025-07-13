# ADO.NET

## 一般步骤

使用 ADO.NET 访问数据库遵循基本的编程思路。一般步骤如下 :

S1 : 使用 `using` 添加 `System.Data` 及其相关子命名空间的引用（如果想要访问 SQL Server 数据库就必须引用 `System.Data.SqlClient` 

S2 : 使用 `Connection` 对象连接数据源。

S3 : 视情况使用 Command 对象、DataReader 对象或 DataAdapter 对象操作数据库

S4 : 将操作结果返回到应用程序中，进行进一步处理。

---

简略的说，就是先添加命名空间，再链接数据源，之后使用 `Command` ，`DataReader` ，`DataAdapter` 操作数据库，最后返回操作结果做进一步处理。
