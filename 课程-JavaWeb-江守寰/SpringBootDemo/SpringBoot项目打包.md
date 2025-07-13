- 终端输入 `mvn clean install` 命令，等待控制台输出 BUILD SUCCESS，在 target 目录生成一个 `.jar` 包

- 复制 `.jar` 包的路径，例如 `/Users/evan/IdeaProjects/boot-demo/target/1.jar` ，控制台输入 `cd /Users/evan/IdeaProjects/boot-demo/target/` ，输入 `ll` 可以查看内容。

- 使用 `java -jar 1.jar` 即可运行启动应用，直接访问项目 ；也可以修改端口，`java -jar 1.jar --server.port=8081` 
