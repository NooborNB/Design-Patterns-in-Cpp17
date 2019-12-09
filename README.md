![Supported Platforms](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-green.svg)
[![Build Status](https://travis-ci.org/downdemo/Design-Patterns-in-Cpp17.svg?branch=master)](https://travis-ci.org/downdemo/Design-Patterns-in-Cpp17)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/downdemo/Design-Patterns-in-Cpp17/LICENSE)

建筑师Christopher Alexander说，`Each pattern describes a problem which occurs over and over again in our environment, and then describes the core of the solution to that problem, in such a way that you can use this solution a million times over, without ever doing it the same way twice.`后来，模式的思想也被引入了软件工程领域。设计模式是从已有的软件设计中，针对重复出现的问题提取出的一套经验论，其概念源自[《Design Patterns: Elements of Reusable Object-Oriented Software》](https://www.oreilly.com/library/view/design-patterns-elements/0201633612/)（四人合著，因此简称`GoF（Gang of Four）`），即[《设计模式：可复用面向对象软件的基础》](https://book.douban.com/subject/1052241/)。一些设计模式已经用在编程语言或框架中了，比如Qt的信号槽、C#的委托事件、JavaScript的Promise、Angular的Observable，都是观察者模式的应用。设计模式减少了术语交流的沟通成本，灵活使用它来写出低耦合少重复的代码。

## Creational Pattern（创建型模式）
* [Abstract Factory/Kit（抽象工厂模式）](docs/Creational_Pattern/Abstract_Factory.md)：[source code](src/Abstract_Factory.cpp)
* [Builder（建造者模式）](docs/Creational_Pattern/Builder.md)：[source code](src/Builder.cpp)
* [Factory Method/Virutal Contructor（工厂方法模式）](docs/Creational_Pattern/Factory_Method.md)：[source code](src/Factory_Method.cpp)
* [Prototype（原型模式）](docs/Creational_Pattern/Prototype.md)：[source code](src/Prototype.cpp)
* [Singleton（单例模式）](docs/Creational_Pattern/Singleton.md)：[source code](src/Singleton.cpp)

## Structural Pattern（结构型模式）
* [Adapter/Wrapper（适配器模式）](docs/Structural_Pattern/Adapter.md)：[source code](src/Adapter.cpp)
* [Bridge/Handle/Body（桥接模式）](docs/Structural_Pattern/Bridge.md)：[source code](src/Bridge.cpp)
* [Composite（组合模式）](docs/Structural_Pattern/Composite.md)：[source code](src/Composite.cpp)
* [Decorator/Wrapper（装饰器模式）](docs/Structural_Pattern/Decorator.md)：[source code](src/Decorator.cpp)
* [Facade（外观模式）](docs/Structural_Pattern/Facade.md)：[source code](src/Facade.cpp)
* [Flyweight（享元模式）](docs/Structural_Pattern/Flyweight.md)：[source code](src/Flyweight.cpp)
* [Proxy/Surrogate（代理模式）](docs/Structural_Pattern/Proxy.md)：[source code](src/Proxy.cpp)

## Behavioral Pattern（行为型模式）
* [Chain of Responsibility（责任链模式）](docs/Behavioral_Pattern/Chain_of_Responsibility.md)：[source code](src/Chain_of_Responsibility.cpp)
* [Command/Action/Transaction（命令模式）](docs/Behavioral_Pattern/Command.md)：[source code](src/Command.cpp)
* [Interpreter（解释器模式）](docs/Behavioral_Pattern/Interpreter.md)：[source code](src/Interpreter.cpp)
* [Iterator/Cursor（迭代器模式）](docs/Behavioral_Pattern/Iterator.md)：[source code](src/Iterator.cpp)
* [Mediator（中介者模式）](docs/Behavioral_Pattern/Mediator.md)：[source code](src/Mediator.cpp)
* [Memento/Token（备忘录模式）](docs/Behavioral_Pattern/Memento.md)：[source code](src/Memento.cpp)
* [Observer/Dependents/Publish-Subscribe（观察者模式）](docs/Behavioral_Pattern/Observer.md)：[source code](src/Observer.cpp)
* [State/Objects for States（状态模式）](docs/Behavioral_Pattern/State.md)：[source code](src/State.cpp)
* [Strategy/Policy（策略模式）](docs/Behavioral_Pattern/Strategy.md)：[source code](src/Strategy.cpp)
* [Template Method（模板方法模式）](docs/Behavioral_Pattern/Template_Method.md)：[source code](src/Template_Method.cpp)
* [Visitor（访问者模式）](docs/Behavioral_Pattern/Visitor.md)：[source code](src/Visitor.cpp)