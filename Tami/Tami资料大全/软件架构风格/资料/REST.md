###REST

#### 1.REST的相关概念

自从Roy Fielding博士在2000年他的博士论文中提出[REST](http://zh.wikipedia.org/wiki/REST)（Representational State Transfer）风格的软件架构模式后，REST就基本上迅速取代了复杂而笨重的SOAP，成为Web API的标准了。

SOAP (Simple Object Access Protocol) 顾名思义，是一个严格定义的信息交换协议，用于在Web Service中把远程调用和返回封装成机器可读的格式化数据。事实上SOAP数据使用XML数据格式，定义了一整套复杂的标签，以描述调用的远程过程、参数、返回值和出错信息等等。而且随着需要的增长，又不得增加协议以支持安全性，这使SOAP变得异常庞大，背离了简单的初衷。

这里对REST与SOAP进行了比较：http://www.fly63.com/article/detial/1938

**Representational State Transfer  表现层状态转化 。**

- 轻量级的解决方案，不必向SOAP那样要构建一个标准的SOAP XML
- 可读性比较好:可以把URL的名字取得有实际意义
- 不需要SDK支持：直接一个Http请求就可以，但是SOAP则可能需要使用到一些Webservice的类库（例如Apache的Axis）
- 复杂的应用中，URL可能非常长，而且不容易解析

#### 2.REST的使用举例

如果我们想要获取某个电商网站的某个商品，输入`http://localhost:9999/products/123`，就可以看到id为123的商品页面，但这个结果是HTML页面，它同时混合包含了Product的数据和Product的展示两个部分。对于用户来说，阅读起来没有问题，但是，如果机器读取，就很难从HTML中解析出Product的数据。

如果一个URL返回的不是HTML，而是机器能直接解析的数据，这个URL就可以看成是一个Web API。比如，读取`http://localhost:9999/api/products/123`，如果能直接返回Product的数据，那么机器就可以直接读取。

REST就是一种设计API的模式。最常用的数据格式是JSON。由于JSON能直接被JavaScript读取，所以，以JSON格式编写的REST风格的API具有简单、易读、易用的特点。

编写API有什么好处呢？由于API就是把Web App的功能全部封装了，所以，通过API操作数据，可以极大地把前端和后端的代码隔离，使得后端代码易于测试，前端代码编写更简单。

此外，如果我们把前端页面看作是一种用于展示的客户端，那么API就是为客户端提供数据、操作数据的接口。这种设计可以获得极高的扩展性。例如，当用户需要在手机上购买商品时，只需要开发针对iOS和Android的两个客户端，通过客户端访问API，就可以完成通过浏览器页面提供的功能，而后端代码基本无需改动。

####3.Rest架构的主要原则

- 网络上的所有事物都被抽象为资源

- 每个资源都有一个唯一的资源标识符
- 同一个资源具有多种表现形式(xml,json等)

- 对资源的各种操作不会改变资源标识符

- 所有的操作都是无状态的

- 符合REST原则的架构方式即可称为RESTful

#### 4.REST的重要特征

1. 统一的接口 同一个资源  对外暴漏的URL一致  

2. 无状态

3. 可缓存

4. 客户端/服务器模式

5. 分层系统

   ***url代表一种资源，客户端与服务器交互就是传递这种资源的表现层的过程***

