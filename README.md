# README
## 有限状态机的C++实现

### 实现动机
项目应用层涉及了复杂的状态管理，原本使用基于函数指针的方式实现的有限状态机，经过了很多人很多次的功能添加、修改，变得异常庞大、难以维护。现在使用设计模式里的状态模式重构应用层代码。

重构思路借鉴了《设计模式：可复用面向对象软件的基础》的思想。

### 层次架构
```
hsm/
├── Factory.h          # 状态工厂
├── Machine.cpp
├── Machine.h          # 使用状态机的机器类
├── MonitorState.cpp
├── MonitorState.h     # 具体的状态类 继承状态基类
└── hsm_core           # 层次状态机核心代码
    ├── Context.cpp 
    ├── Context.h      # 状态机上下文，管理多个状态
    ├── Input.h        # 输入事件类
    ├── State.cpp
    └── State.h        # 状态基类
main.cpp               # 测试代码

```

### 编译运行
```
$ mkdir build && cd build && cmake .. && make                                                 

$ ./hsm                                                       
enter stopped state
Please input: 1 - Start, 2 - Stop.
1
T1: recieve start input.
exit stopped state
enter starting state
T2: check running
exit starting state
enter running state
T4: check error
exit running state
enter stopping state
T5: stop done
exit stopping state
```
