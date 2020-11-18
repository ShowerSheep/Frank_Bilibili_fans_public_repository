# mybatis的使用

## mybatis的开发环境搭建步骤

1. 创建empty project,创建module(模块)

2. 在pom.xml文件添加依赖

   - **mybatis的依赖**

   - **jdbc驱动依赖**

     ```xml
     <dependencies>
         <!--jdbc驱动-->
         <dependency>
           <groupId>mysql</groupId>
           <artifactId>mysql-connector-java</artifactId>
           <version>8.0.20</version>
         </dependency>
         <!--mybatis-->
         <dependency>
           <groupId>org.mybatis</groupId>
           <artifactId>mybatis</artifactId>
           <version>3.5.5</version>
         </dependency>
         <dependency>
           <groupId>junit</groupId>
           <artifactId>junit</artifactId>
           <version>4.11</version>
           <scope>test</scope>
         </dependency>
       </dependencies>
     ```

3. 在resources目录下,创建mybatis-config.xml

   ```xml
   <environments default="jdbc">
       <environment id="jdbc">
           <transactionManager type="JDBC"/>
           <dataSource type="POOLED">
               <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
               <property name="url" value="jdbc:mysql://localhost:3306/smbms?useUnicode=true&amp;characterEncoding=utf-8&amp;serverTimezone=Asia/Shanghai"/>
               <property name="username" value="root"/>
               <property name="password" value="123456"/>
           </dataSource>
       </environment>
   </environments>
   ```

4. 根据业务需求,根据数据库创建实体类

   ```java
   package com.zhigu.pojo;
   
   public class User {
       private Integer id;
       private String userName;
       private String address;
   
       public Integer getId() {
           return id;
       }
   
       public void setId(Integer id) {
           this.id = id;
       }
   
       public String getUserName() {
           return userName;
       }
   
       public void setUserName(String userName) {
           this.userName = userName;
       }
   
       public String getAddress() {
           return address;
       }
   
       public void setAddress(String address) {
           this.address = address;
       }
   
       @Override
       public String toString() {
           return "User{" +
                   "id=" + id +
                   ", userName='" + userName + '\'' +
                   ", address='" + address + '\'' +
                   '}';
       }
   }
   
   ```

5. 创建对应的dao接口

   ```java
   public interface UserDao {
       //查询所有的用户信息
       List<User> getUserList();
   }
   ```

6. 在接口对应的包下,创建对应的mapper映射文件

   ```xml
   <?xml version="1.0" encoding="UTF-8" ?>
   <!DOCTYPE mapper
           PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
           "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<!--namespace:命名空间,去找对应的接口-->   
   <mapper namespace="com.zhigu.dao.UserDao">
       <!--id是唯一的,对应的接口中的抽象方法名,resultType:返回值类型,如果返回的是集合,类型就写集合中的对象类型-->
       <select id="getUserList" resultType="User">
           select * from smbms_user
       </select>
   </mapper>
```
   
7. 在mybtis-config.xml中添加配置

   ```xml
   <?xml version="1.0" encoding="UTF-8"?>
   <!DOCTYPE configuration PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
           "http://mybatis.org/dtd/mybatis-3-config.dtd">
   <configuration>
       <!------------------设置实体类的别名,简化操作------------------->
       <typeAliases>
           <package name="com.zhigu.pojo"/>
       </typeAliases>
         <!------------------------------------->
       <environments default="jdbc">
           <environment id="jdbc">
               <transactionManager type="JDBC"/>
               <dataSource type="POOLED">
                   <property name="driver" value="com.mysql.cj.jdbc.Driver"/>
                   <property name="url" value="jdbc:mysql://localhost:3306/smbms?useUnicode=true&amp;characterEncoding=utf-8&amp;serverTimezone=Asia/Shanghai"/>
                   <property name="username" value="root"/>
                   <property name="password" value="123456"/>
               </dataSource>
           </environment>
       </environments>
         <!-------引入映射文件,方便mybatis-config.xml被加载,映射文件也一起被加载-------------->
       <mappers>
           <mapper resource="com/zhigu/dao/UserMapper.xml"/>
       </mappers>
         <!------------------------------------->
   </configuration>
   ```

8. 测试会报错:`找不到com/zhigu/dao/UserMapper.xml文件`

   ```java
   public void testUserList() throws IOException {
   	//加载mybatis-config.xml文件
       Reader reader = Resources.getResourceAsReader("mybatis-config.xml");
       //读取配置文件,构建SqlSessionFactory
       SqlSessionFactory sessionFactory  =  new SqlSessionFactoryBuilder().build(reader);
       //生产sqlsession对象
       SqlSession session = sessionFactory.openSession(false);//使用事务
       System.out.println(session);
       //加载接口
       UserDao mapper = session.getMapper(UserDao.class);
       List<User> userList = mapper.getUserList();
       System.out.println(userList);
       session.close();
   }
   ```

   

   原因是:**idea默认情况下,会去找resources目录下的xml配置文件,如果没有,就会包找不到xml文件的错误**

   解决方案:

   1. 将配置的映射文件mapper.xml放在resources目录下

   2. 在pom.xml文件中,找到`<build>`节点添加配置

      ```xml
      <resources>
          <resource>
              <!--从src目录去找文件-->
              <directory>src/main/java</directory>
              <includes><!--包含的意思-->
                  <!--所有的xml文件-->
                  <include>**/*.xml</include>
              </includes>
          </resource>
      </resources>
      ```

      

## 当SQL查询返回的列名与pojo类的属性名不一致时,怎么办?

#### 1.修改属性名

#### 2.为SQL语句设置别名,与属性名一致即可

```java
<!--根据用户名和用户角色id进行查询-->
    <select id="getUserByNameAndRole" parameterType="User" resultType="User">
    select u.*,r.roleName as  userRoleName  from smbms_user u,smbms_role r where u.userRole=r.id and userName like CONCAT('%',#{userName},'%')
    and userRole=#{userRole}

</select>
```

#### 3.使用resultMap来映射数据库表中的字段名与实体类中的属性名

```java
<resultMap id="userMap" type="User">
    <id property="id" column="id"/>
    <result property="userName" column="userName"/>
    <result property="address" column="address"/>
    <result property="userRoleName" column="roleName"/>
    </resultMap>
    <!--根据用户名和用户角色id进行查询-->
    <select id="getUserByNameAndRole" parameterType="User" resultMap="userMap" >
    select u.*,r.roleName   from smbms_user u,smbms_role r where u.userRole=r.id and userName like CONCAT('%',#{userName},'%')
    and userRole=#{userRole}

</select>
```

## mybatis传参(多个参数)

### 1.使用javaBean封装

将参数封装在一个新的javaBean中(在项目中新建一个java类,根据参数来封装,类似于User)

### 2.使用@Param传递参数

```java
/**
     * 根据用户名和角色id查询,使用@Param传递参数
     * @param name 用户名
     * @param id 角色id
     * @return 用户集合(包含了角色名称)
     */
public List<User> getUserByParam(@Param("userName")String name,@Param("roleId") Integer id);
```

映射文件

```xml
<select id="getUserByParam" resultMap="userMap" >
    select u.*,r.roleName   from smbms_user u,smbms_role r where u.userRole=r.id and userName like CONCAT('%',#{userName},'%')  and userRole=#{roleId}
</select>

```



测试:

```java
@Test
    public void testUserByParam() throws IOException {

        Reader reader = Resources.getResourceAsReader("mybatis-config.xml");
        SqlSessionFactory sessionFactory  =  new SqlSessionFactoryBuilder().build(reader);
        SqlSession session = sessionFactory.openSession(false);
        System.out.println(session);
        UserDao mapper = session.getMapper(UserDao.class);
        List<User> userList = mapper.getUserByParam("赵",3);
        System.out.println(userList);
        session.close();
    }
```

## mybatis中的一对多

`查询老师的信息,包含了所有学生`

**所有的学生怎么封装起来???**

#### 在老师实体类中添加对应的属性来封装

- 在老师实体类中添加对应的属性来封装

```java
private Integer id;
private String name;
//一个老师对应多个学生
private List<Student> stuList;
```

- 在映射文件中设置

  ```xml
  <select id="getTeachers" parameterType="int" resultMap="teacherList">
      <!--多表联查时,一定要注意返回的列名,不能重复,最好取别名-->
      SELECT t.id tid,t.name tname,s.id sid,s.name sname,s.tid stid FROM `student` s inner join `teacher` t  on s.tid=t.id where t.id=#{id};
  </select>
  
  <resultMap id="teacherList" type="Teacher">
      <id column="tid" property="id"/>
      <result column="tname" property="name"/>
      <!--学生表中的数据:一对多的关系:stuList是Teacher类中的属性,是一个集合 ofType:集合中所装对象的类型-->
      <collection property="stuList" ofType="Student" >
          <id column="sid" property="id"/>
          <result column="sname" property="name"/>
          <result column="stid" property="tid"/>
      </collection>
  </resultMap>
  ```

### mybatis中的一对一

#### 	1.在pojo类中定义一个相关的属性

```java
  private Integer id;
    private String userName;
    private String address;

    private Integer userRole;
    //角色名称:一个用户只能有一种角色,这个是一对一的关系
    private String userRoleName;
```

```xml
<resultMap id="userMap" type="User">
    <id property="id" column="id"/>
    <result property="userName" column="userName"/>
    <result property="address" column="address"/>
    <result property="userRoleName" column="roleName"/>
</resultMap>
<!--根据用户名和用户角色id进行查询-->
<select id="getUserByNameAndRole" parameterType="User" resultType="User">
    select u.*,r.roleName as  userRoleName  from smbms_user u,smbms_role r where u.userRole=r.id and userName like CONCAT('%',#{userName},'%')
    and userRole=#{userRole}

</select>
```

#### 2.在实体类定义对应的对象属性

1. 在pojo类中定义一个对应的对象属性

   ```java
   private Integer id;
   private String userName;
   private String address;
   private Integer userRole;
   //一个用户对象对应一个角色对象:一对一
   private Role role;
   ```

2. 在映射文件使用association

   ```xml
   <!--根据用户名和用户角色id进行查询-->
   <select id="getUserByNameAndUserRole2" parameterType="User" resultMap="userMap1">
       select u.*,r.id as rid,r.roleName as  userRoleName  from smbms_user u,smbms_role r where u.userRole=r.id and userName like CONCAT('%',#{userName},'%')
       and userRole=#{userRole}
   
   </select>
   <resultMap id="userMap1" type="User1">
       <id property="id" column="id"/>
       <result property="userName" column="userName"/>
       <result property="address" column="address"/>
       <association property="role" javaType="Role">
           <id column="rid" property="id"></id>
           <result column="userRoleName" property="roleName"/>
       </association>
   </resultMap>
   
   ```

   