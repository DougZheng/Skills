# MySQL	

## 基本语法

### 数据库操作

- 启动 mysql 服务

  `systemctl start mysqld`

- 连接 mysql

  `mysql -u user -p -h host -P port` 

- 显示所有数据库

  `SHOW DATABASES;`

- 创建数据库

  `CREATE DATABASE database;`

- 删除数据库

  `DROP DATABASE database;`

- 选择数据库

  `USE database;`

- 显示数据库所有表

  `SHOW TABLES;`

- 显示表的所有列

  `SHOW COLUMNS FROM table;` 或 `DESC[RIBE] table;`

### 检索数据

```mysql
SELECT DISTINCT column1, column2, columnN
FROM table
ORDER BY column1 DESC, column2 DESC, column3 # default: ASC
LIMIT irow, nrow; # LIMIT nrow OFFSET irow
```

- 选择指定列

  `SELECT column1, column2, columnN`

- 结果去重

  `DISTINCT`

- 按指定行排序

  `ORDER BY column1 DESC, column2 DESC, column3` ，默认按升序排列，`DESC` 限定该列按降序排列。

- 选择指定行范围

  `LIMIT irow, nrow` 或 `LIMIT nrow OFFSET irow` ，返回从 `irow` 开始的 `nrow` 行。（0-index）

### 过滤数据

#### WHERE 子句

```mysql
SELECT *
FROM table
WHERE attr1 = 'xxx';
# WHERE attr2 BETWEEN 1 AND 5;
# WHERE attr3 IS NULL;
# WHERE attr4 IN ('a', 'b') OR attr5 NOT IN (123, 456);
```

- 检查单个值

  `WHERE attr op val` ，可用 `op` 操作符有 `=, >, <, >=, <=, !=, <>` 。

- 范围值检查

  `WHERE attr BETWEEN lval AND rval` ，检查 `attr` 值是否落在 `[lval, rval]` 。

- 空值检查

  `WHERE attr IS NULL` ，检查 `attr` 值是否为空。

- 组合 WHERE 子句

  `NOT, AND, OR` 进行组合。

- IN 操作符

  `WHERE attr IN (val1, val2, valN)` ，检查 `attr` 是否在 `(val1, val2, valN)` 内。

#### 通配符过滤

```mysql
SELECT *
FROM table
WHERE attr LIKE '%do_g';
```

- 通配 0 个、1 个或多个字符

  `%` 

- 通配 1 个字符

  `_`

#### 正则表达式过滤

```mysql
SELECT *
FROM table
WHERE attr REGEXP BINARY '^hello[^a-z][[:space:]].?.+.*.{2}.{3,}.{4,5}(abc|xyz)\\.\\\$';
```

- 匹配特殊字符：

  `\\` 进行转义，如 `\\.` 匹配 `.` 。

- 匹配区分大小写：

  `BINARY` 让匹配区分大小写，默认不区分。

### 计算字段

```mysql
SELECT Concat(column1, '(', column2, ')') AS column1_column2, 
       column3 * column4 AS column3_column4
FROM table;
```

- 拼接字段

  `Concat(column1, column2)` 将两列拼接，作为一个计算字段。

- 执行算术计算

  `column3 * column4` 将两列结果相乘，作为一个计算字段。

- 别名

  `AS` 关键字，可缺省。

### 数据处理函数

#### 文本处理函数

| 函数                       | 说明                                                     | 例子                       | 结果   |
| -------------------------- | -------------------------------------------------------- | -------------------------- | ------ |
| Left(str, len) / Right     | 返回 str 左边的 len 个字符                               | LEFT('foobarbar', 5)       | fooba  |
| Length(str)                | 返回 str 的长度                                          | LENGTH('text')             | 4      |
| Locate(str, substr, pos=1) | 返回 str 中 substr 首次出现下标（1-index），找不到返回 0 | LOCATE('bar', 'foobarbar') | 4      |
| Lower(str) / Upper         | 将 str 转换为小写                                        | LOWER('Hello')             | hello  |
| LTrim(str) / RTrim         | 去掉 str 左边的空格                                      | LTRIM('  barbar')          | barbar |
| Soundex(str)               | 返回 str 的SOUNDEX 串                                    | SOUNDEX('Hello')           | H400   |
| SubStr(str, pos, len=INF)  | 返回 str 从 pos 开始的 len 个字符（1-index）             | SUBSTR('Sakila', -5, 3)    | aki    |

参考：https://dev.mysql.com/doc/refman/8.0/en/string-functions.html

#### 日期和时间处理函数

| 函数                                                    | 说明                      | 例子                                          | 结果                |
| ------------------------------------------------------- | ------------------------- | --------------------------------------------- | ------------------- |
| CurDate()                                               | 返回当前日期 'YYYY-MM-DD' | CurDate()                                     | 2021-06-13          |
| CurTime()                                               | 返回当前时间 'hh:mm:ss'   | CurTime()                                     | 19:44:48            |
| Now()                                                   | 'YYYY-MM-DD hh:mm:ss'     | Now()                                         | 2021-06-13 19:44:48 |
| Date(expr)                                              | 返回 expr 的日期部分      | Date('2021-06-13 19:44:48')                   | 2021-06-13          |
| Time(expr)                                              | 返回 expr 的时间部分      | Time('2021-06-13 19:44:48')                   | 19:44:48            |
| DateDiff(expr1, expr2)                                  | 返回 expr1 - expr2 的天数 | DateDiff('2021-06-13 19:44:48', '2021-06-14') | -1                  |
| Date_Format(date, format)                               | 返回一个格式化的时间      | Date_Format('2021-06-13', '%W %M')            | Sunday June         |
| Year / Month / Day / DayOfWeek / Hour / Minute / Second | 1-index，周日是 1         | DayOfWeek('2021-06-13')                       | 1                   |

参考：https://dev.mysql.com/doc/refman/8.0/en/date-and-time-functions.html

#### 数值处理函数

| 函数            | 说明                    | 例子               | 结果 |
| --------------- | ----------------------- | ------------------ | ---- |
| Abs(x)          | 返回 x 的绝对值         | Abs(-32)           | 32   |
| Round(x, d=0)   | 对 x 四舍五入，精度为 d | Round(15.32, 1)    | 15.3 |
| Truncate(x, d)  | 对 x 截断，精度为 d     | Truncate(15.38, 1) | 15.3 |
| Sqrt(x)         | 返回 x 的平方根         | Sqrt(4)            | 2    |
| Pow(x, y)       | 返回 x 的 y 次幂        | Pow(2, 10)         | 1024 |
| Log(b=e, x)     | 返回 x 的对数，底数为 b | Log(10, 100)       | 2    |
| Floor(x) / Ceil | 向下取整、向上取整      | Floor(10.5)        | 10   |

参考：https://dev.mysql.com/doc/refman/8.0/en/numeric-functions.html

### 聚集函数

```mysql
SELECT COUNT(DISTINCT column1), 
       AVG(column2),  
       MIN(column3),
       MAX(column5), 
       SUM(column6 * column7)
FROM table;
```

### 分组数据

```mysql
SELECT column1, SUM(column2 * column3) AS column2_column3
FROM table
WHERE attr IS NOT NULL
GROUP BY column1
HAVING SUM(column2_column3) >= val
ORDER BY column1
LIMIT 3 OFFSET 0;
```

- 分组

  除聚集计算语句外，`SELECT` 中的每个列都必须在 `GROUP BY` 子句中给出。

- 分组后过滤

  `HAVING` 对分组数据进行过滤，使用同 `WHERE` 。

### 子查询

#### 子查询过滤

```mysql
SELECT column1
FROM table1
WHERE column2 IN (
	SELECT column2
    FROM table2
);
```

#### 子查询作为计算字段

```mysql
SELECT column1
       (SELECT COUNT(*)
        FROM table2
        WHERE table2.column2 = table1.column2) AS col2
FROM table1;
```

### 表连接

#### 内连接

```mysql
SELECT column1
FROM table1 INNER JOIN table2
ON table1.column2 = table2.column2
WHERE table1.column3 = val;
```

使用 `WHERE` 子句也可以达到同样效果：

```mysql
SELECT column1
FROM table1, table2
WHERE table1.column2 = table2.column2 AND table1.column3 = val;
```

#### 外连接

```mysql
SELECT column1
FROM table1 LEFT JOIN table2
ON table1.column2 = table2.column2;
```

- 左外连接

  `LEFT JOIN` 保留左边的表所有行，右边没有关联的行用 `NULL` 表示。

- 右外连接

  `RIGHT JOIN` 保留右边的表所有行，左边没有关联的行用 `NULL` 表示。

### 组合查询

```mysql
SELECT column1
FROM table1
UNION
SELECT column1
FROM table2
ORDER BY column1 DESC;
```

- 组合查询

  `UNION` 对两个查询结果组合，对结果去重，`UNION ALL` 则不作去重。

- 组合查询结果排序

  `ORDER BY` 只对最终结果排序，不能对组合结果部分排序。

### 数据修改

#### 插入数据

```mysql
INSERT INTO table(column1, column2, ...)
VALUES(value1, value2, ...), (value1, value2, ...);

INSERT INTO table1(column1, column2, ...)
SELECT column1, column2, ...
FROM table2;
```

#### 更新数据

```mysql
UPDATE table
SET column1 = value1, column2 = value2
WHERE column3 = value3;
```

#### 删除数据

```mysql
DELETE FROM table
WHERE column1 = value1;
```

### 表操作

#### 创建表

```mysql
CREATE TABLE table IF NOT EXISTS(
	column1  int         NOT NULL AUTO_INCREMENT, 
    column2  char(10)    NOT NULL, 
    column3  varchar(10) NULL, 
    column4  int         NOT NULL DEFAULT 1, 
    PRIMARY KEY(column1, column2)
) ENGINE = InnoDB;
```

#### 更新表

```mysql
ALTER TABLE table
ADD column5 char(20);

ALTER TABLE table
DROP column5;

ALTER TABLE table1
ADD CONSTRAINT column6
FOREIGN KEY(column3) REFERENCES table2(column5);
```

#### 删除表

```mysql
DROP TABLE table;
```

#### 重命名表

```mysql
RENAME TABLE table1 TO table2,
             table3 TO table4;
```

