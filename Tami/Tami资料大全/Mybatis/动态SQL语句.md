# mybatis的动态SQL

**`基于OGNL表达式语言`**

## 什么是OGNL

​		`OGNL`是`O`bject-`G`raph `N`avigation `L`anguage的缩写，它是一种功能强大的表达式语言，通过它简单一致的表达式语法，可以存取对象的任意属性，调用对象的方法，遍历整个对象的结构图，实现字段类型转化等功能。它使用相同的表达式去存取对象的属性。这样可以更好的取得数据。

## OGNL的典型应用

`webwork2`和现在的`Struts2.x`中使用OGNL取代原来的EL来做界面数据绑定，所谓界面数据绑定，也就是把界面元素（例如一个textfield,hidden)和对象层某个类的某个属性绑定在一起，修改和显示自动同步。

## `OGNL的安全问题`

​		`		由于OGNL能够创建或更改可执行代码，因此能够为使用它的任何框架引入严重的安全漏洞。多个Apache Struts 2版本容易受到OGNL安全漏洞的攻击。截至2017年10月，Struts 2的推荐版本为2.5.13。用户被要求升级到最新版本，因为旧版本已经记录了安全漏洞 - 例如，Struts 2版本2.3.5到2.3.31和2.5到2.5.10，允许远程攻击者执行任意代码。`

## mybatis的动态SQL

- if  
- where-if  
- set-if  
- trim-if   prefix="where"  prefixOverrides="and | or"
- trim-if prefix="set" prefixOverrides="," suffix="where ..."
- foreach
  - collection
    - array
    - list
    - map-key
- chooose-when-otherwise

### if

```xml
<select id="getUserList" parameterType="User" resultType="User">
    select * from smbms_user
    where 1=1
    <if test="userName!=null and userName!=''"> AND userName like CONCAT('%',#{userName},'%')</if>
    <if test="userRole!=null and userRole!=''"> AND userRole=#{userRole}</if>
</select>
```

### where-if

```xml
<select id="getUserList" parameterType="User" resultType="User">
    select * from smbms_user
    <where>
        <if test="userName!=null and userName!=''"> AND userName like CONCAT('%',#{userName},'%')</if>
        <if test="userRole!=null and userRole!=''"> AND userRole=#{userRole}</if>
    </where>
</select>
```

### set - if

```xml
<update id="modifyUser" parameterType="User">
    update smbms_user
    <set>
        <if test="userName!=null and userName!=''">userName=#{userName},</if>
        <if test="userRole!=null and userRole!=''">userRole=#{userRole},</if>
        <if test="address!=null and address!=''">address=#{address},</if>
    </set>
    where id=#{id}
</update>
```

### trim - if	(一)

- prefix:前面拼接
- prefixOverrides:在子句的前面智能处理

```xml
<select id="getUserList" parameterType="User" resultType="User">
    select * from smbms_user
    <trim prefix="where" prefixOverrides="AND | OR">
        <if test="userName!=null and userName!=''"> AND userName like CONCAT('%',#{userName},'%')</if>
        <if test="userRole!=null and userRole!=''"> AND userRole=#{userRole}</if>
    </trim>
</select>
```

### trim - if (二)

- suffix:在后面拼接
- suffixOverrides:在子句的后面智能处理

```xml
<update id="modifyUser" parameterType="User">
    update smbms_user
    <trim prefix="set" suffix="where id=#{id}" suffixOverrides=",">
        <if test="userName!=null and userName!=''">userName=#{userName},</if>
        <if test="userRole!=null and userRole!=''">userRole=#{userRole},</if>
        <if test="address!=null and address!=''">address=#{address},</if>
    </trim>
</update>
```

### foreach

1. 数组
   - collection:必须指定
   - item:数组中的临时变量,保存值,作为遍历使用
   - open:以(符号开始
   - close:以)符号结束
   - separator:以逗号分隔开

```xml
<select id="getUserByRole" parameterType="int" resultType="User">
    select * from smbms_user where userRole IN
    <foreach collection="array" item="rid" open="(" separator="," close=")">
        #{rid}
    </foreach>
</select>
```

2. List集合
   - collection:必须指定
   - 其他的与数组一样

```xml
<select id="getUserByRole" parameterType="int" resultType="User">
    select * from smbms_user where userRole IN
    <foreach collection="list" item="rid" open="(" separator="," close=")">
        #{rid}
    </foreach>
</select>		
```

3. map集合

   - collection:map中的key
   - item:临时存储值的变量

   ```xml
   <select id="getUserByRole" parameterType="int" resultType="User">
       select * from smbms_user where userRole IN
       <foreach collection="roleIds" item="rid" open="(" separator="," close=")">
           #{rid}
       </foreach>
   </select>
   ```

   ```java
   //读取配置文件
   Reader reader = Resources.getResourceAsReader("mybatis-config.xml");
   SqlSessionFactory sessionFactory = new SqlSessionFactoryBuilder().build(reader);
   SqlSession session = sessionFactory.openSession(false);
   UserDao mapper = session.getMapper(UserDao.class);
   //Integer[] roleIds = {1,2};
   // List<Integer> roleIds = Arrays.asList(1,2);
   Map<String,Object> roleMap = new HashMap<>();
   List<Integer> roleIds = Arrays.asList(1,2);
   roleMap.put("roleIds",roleIds);
   List<User> userList = mapper.getUserByRole(roleMap);
   System.out.println(userList);
   session.close();
   ```

### choose - when - otherwise

- when:可以有多个,类似于java中的 `else -if`
- otherwise:只能有一个,类似于java中的`else`
- 一个条件,多种情况的判断

```xml
<select id="getUserList" parameterType="User" resultType="User">
    select * from smbms_user
    <where>
        <choose>
            <when test="userName!=null and userName!=''"> userName like CONCAT('%',#{userName},'%')</when>
            <otherwise>
                userRole=1
            </otherwise>
        </choose>
    </where>
</select>
```

