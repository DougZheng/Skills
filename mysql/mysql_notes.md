# MySQL	

## 基本语法

### 连接数据库

- 启动 mysql 服务

- 连接 mysql

  `mysql -u user -p -h host -P port` 

### 选择数据库

- 显示所有数据库

  `SHOW DATABASES;`

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
ORDER BY columnX DESC, columnY DESC # default: ASC
LIMIT irow, nrow; # LIMIT nrow OFFSET irow
```

- 选择指定列

  `SELECT column1, column2, columnN`

- 结果去重

  `DISTINCT`

- 选择指定行范围

  `LIMIT irow, nrow` 或 `LIMIT nrow OFFSET irow` ，返回从 `irow` 开始的 `nrow` 行。（0-index）

### 排序检索数据

```mysql
SELECT *
FROM table
ORDER BY column1 DESC, column2 DESC, column3;
```

- 按指定行排序

  `ORDER BY column1 DESC, column2 DESC, column3` ，默认按升序排列，`DESC` 限定该列按降序排列。

### 过滤数据

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

### 通配符过滤