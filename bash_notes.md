## Shell 编程基础

### 变量

shell 变量默认是字符串，赋值 `=` 左右不能有空格，取用变量 `a` 的值需要在变量名前面加 `$` ，即 `$a` ，或者 `${a}` 。

```shell
#!/bin/bash
# 第一行称为shabang（sharp+bang），指引操作系统使用指定程序执行此文件
a="hello world"
b=$a
echo $b
```

单引号字符串内无转义，双引号字符串内可使用转义字符、使用变量。

```shell
a="hell"
s1='${a}o'
s2="${a}o"
echo $s1 $s2 # ${a}o hello  
```

使用 `readonly` 限定变量为只读变量，使用 `unset` 删除变量。

```shell
a="hello"
readonly a
a="world" # error
b="hello"
unset b
echo $b # 空
```

使用命令执行结果，可用 `` ` ` `` 或 `$( )` 。

```shell
echo `expr 1 + 2`
echo $(expr 1 + 2)
```

### 字符串

```shell
s="banana"
```

|            格式            |      示例      |     结果      |                           作用                            |
| :------------------------: | :------------: | :-----------: | :-------------------------------------------------------: |
|   `${string1}${string2}`   |    `$s $s`     | banana banana |                 字符串连着写，字符串连接                  |
|  `${string:start:length}`  |   `${s:1:2}`   |      an       |        截取 string 的 start 位置往后 length 个字符        |
|     `${string:start}`      |    `${s:1}`    |     anana     |           截取 string 的 start 位置往后所有字符           |
| `${string:0-start:length}` |  `${s:0-3:2}`  |      an       | 截取 string 的倒数 start 位置往后 length 个字符（1-base） |
|    `${string:0-start}`     |   `${s:0-3}`   |      ana      |    截取 string 的倒数 start 位置往后所有字符（1-base）    |
|     `${string#*chars}`     |   `${s#*an}`   |      ana      |       匹配第一个 *chars ，截取 *chars 右边所有字符        |
|    `${string##*chars}`     |  `${s##*an}`   |       a       |      匹配最后一个 *chars ，截取 *chars 右边所有字符       |
|     `${string%chars*}`     |   `${s%*an}`   |      ban      |     匹配右起第一个 chars* ，截取 chars* 左边所有字符      |
|    `${string%%chars*}`     |  `${s%%*an}`   |       b       |    匹配右起最后一个 chars* ，截取 chars* 左边所有字符     |
| `${string/chars1/chars2}`  | `${s/ana/bnb}` |    bbnbna     |         将所有 chars1 替换为 chars2（不改变原串）         |

### 数组

bash 支持一维数组，不限定数组大小。`@` 或 `*` 可获取数组所有元素。

```shell
array=(0 2 "3" 4) # 空格或回车分隔
array=([0]=0 [1]=2 [2]="3" [3]=4)
array=(${array[*]} ${array[@]}) # 数组拼接
array[0]=1
len=${#array[*]} # 获取数组长度
echo ${array[@]:1:2} # 2 3
echo ${!array[@]} # 输出索引 0 1 2 3 4 5 6 7
```

关联数组，类似 python 中的字典。

```shell
declare -A array
array=(["123"]="hello" ["456"]="world")
echo ${#array[*]} # 长度 2
echo ${!array[*]} # 索引 123 456
echo ${array[*]} # 值 hello world
```

### 传参

`$1` ：获取第 1 个参数。

`${10}` ：获取第 10 个参数。

`$#` ：获取参数个数。

`$*` ：以一个单字符串显示所有参数，传参 1 2 3 ，`"$*"` 等价于 `"1 2 3"` 。

`$@` ：与 `$*` 类似，但是传参 1 2 3 ，`"$@"` 等价于 `"1" "2" "3"` （三个参数）。

`$?` ：获取上一命令的退出状态，或者获取上一函数的返回值。

### 输入输出

`read` 用于输入。

`echo` 用于输出，默认换行，使用 `-n` 不换行，使用 `-e` 开启转义后 `\n` 用作换行符、`\c` 使结果不换行。

```shell
echo "1" # 输出 1 ，然后换行
echo -n "2" # 输出 2 ，不换行
echo -e "3\n" # 输出 3 ，换行后输出一行空行
echo -e "4\c" # 输出 4 ，不换行
```

`printf` 用于格式化输出，格式控制符与 C 语言相同 。

```shell
printf "%-10s %.2f\n" "hello" 3.1415
```

### 整数运算

`(( ))` 用于整数运算，使用 `$` 获取表达式的值，在 `(( ))` 内部不需要使用 `$` 。

支持 `+ - * / % ** < > = != && || -- ++ ,` 及各种复合运算。

`let exprssion` 等价于 `((expression))` ，都是用于整数运算。

```shell
((a=1+2-3*4/5%6)) # 1
b=$((a**a)) # 1**1
c=$((--a&&b)) # 0
let ++c
```

### 浮点数运算

 `bc` 命令可用于浮点数运算，需要设置 `scale` ，此外还可以设置输入进制 `ibase` 和 输出进制 `obase` 。（幂次运算为 `^` ）

```shell
a=2
b=3
c=`echo "scale=3;$a/$b" | bc`
printf "%.2f\n" $c # 0.67
```

### 条件表达式

tips：以下条件表达式符号间均需要空格隔开，没有 `<=` 和 `>=` 。

`[ ]` 和 `test` 用于条件测试，条件表达式结果为真则返回 `0`（true），否则返回 `1`（false）。

| 选项  |              示例               |                    作用                    |
| :---: | :-----------------------------: | :----------------------------------------: |
| `-eq` |         `[ $a -eq $b ]`         |        检测左边的**数**是否等于右边        |
| `-ne` |         `[ $a -ne $b ]`         |       检测左边的**数**是否不等于右边       |
| `gt`  |         `[ $a -gt $b ]`         |        检测左边的**数**是否大于右边        |
| `lt`  |         `[ $a -lt $b ]`         |        检测左边的**数**是否小于右边        |
| `ge`  |         `[ $a -ge $b ]`         |      检测左边的**数**是否大于等于右边      |
| `le`  |         `[ $a -le $b ]`         |      检测左边的**数**是否小于等于右边      |
|  `!`  |          `[ ! false ]`          |                   非运算                   |
| `-a`  |   `[ $a -ge 10 -a $b gt 10 ]`   |                and ，与运算                |
| `-o`  |   `[ $a -le 10 -o $b lt 10 ]`   |                or ，或运算                 |
| `&&`  | `[ $a -ge 10 ] && [ $b gt 10 ]` |     逻辑与，有短路（`[ ]` 中不能使用）     |
| `||`  | `[ $a -le 10 ] || [ $b lt 10 ]` |     逻辑或，有短路（`[ ]` 中不能使用）     |
| `==`  |        `[ $s1 == $s2 ]`         |      检测左边的**字符串**是否等于右边      |
| `!=`  |        `[ $s1 != $s2 ]`         |     检测左边的**字符串**是否不等于右边     |
| `\>`  |        `[ $s1 \> $s2 ]`         | 检测左边的**字符串**是否大于右边（字典序） |
| `\<`  |        `[ $s1 \< $s2 ]`         | 检测左边的**字符串**是否小于右边（字典序） |
| `-z`  |           `[ -z $s ]`           |           检测**字符串**是否为空           |
| `-n`  |          `[ -n "$s" ]`          |          检测**字符串**是否不为空          |

`[[ ]]` 中不需要也不能对 `>` 和 `<` 进行转义，并且能使用 `&&` 和 `||` ，但是不能使用 `-a` 和 `-o` ，此外支持 `[[ $s =~ regex ]]` 。

ps ：`[ -n "$s" ]` 中 `$s` 需要加上 `""` ，若使用 `[[ ]]` 则不需要。

文件测试运算符：

|   选项    |            作用            |
| :-------: | :------------------------: |
| `-b file` |  检测文件是否是块设备文件  |
| `-c file` | 检测文件是否是字符设备文件 |
| `-d file` |     检测文件是否是目录     |
| `-f file` |   检测文件是否是普通文件   |
| `-e file` |      检测文件是否存在      |
| `-r file` |      检测文件是否可读      |
| `-w file` |      检测文件是否可写      |
| `-x file` |     检测文件是否可执行     |

### 流程控制

**`if` 语句** ：

```shell
read i
if ((i >= 85))
then
	echo "A"
elif ((i >= 60))
then
	echo "B"
else
	echo "C"
fi
```

**`for` 语句** ：

```shell
sum=0
for ((i=1; i <= 100; ++i))
do
	((sum += i))
done

sum=0
for i in 1 2 3 4 5
do
	((sum += i))
done

# for i in {1..100} # 仅适用于整型标量
# for file in `ls /bin/*sh`
# for para in $@
```

**`while` 语句** ：

```shell
i=0
while ((i <= 5))
do
	echo $i
	((++i))
done
```

**`until` 语句** ：

```shell
i=0
until ((i > 5))
do 
	echo $i
done
```

**`case` 语句** ：

```shell
read i
case $i in # 记得加$
1)
	echo 1
	;;
[a-z])
	echo "a-z"
	;;
"A")
	echo "A"
	;;
*)
	echo "default"
esac
```

**`break` 和 `continue` 语句** ：

```shell
break # 跳出一层循环
break 2 # 跳出两层循环
continue # 继续一层循环
continue 3 # 继续三层循环
```

**`select` 语句** ：

```shell
# 类似for，但是产生交互选择
select i in "y" "n"
	echo $i
```

### 函数

函数内的变量默认是全局变量，需要加上 `local` 声明为局部变量。

```shell
function func() {
	echo $# # 参数个数
	echo $@ # 参数
	local ans=""
	for i in ${@:1:2} # 切片 $1 $2
	do
		ans=$sum$i
	done
	echo $ans # 默认返回最后一条语句的状态
	return 233 # 返回值需要是数值型
}
func para1 para2 para3
echo $? # 获得上一条命令的退出状态
```

### 重定向

文件描述符 0 是 stdin ，1 是 stdout ，2 是 stderr 。

|       选项       |           示例            |                        作用                        |
| :--------------: | :-----------------------: | :------------------------------------------------: |
| `command >file`  |       `ls -l >test`       |                将输出重定向到 file                 |
| `command >>file` |      `ls -l >>test`       |          将输出以追加的方式重定向到 file           |
| `command <file`  |     `./zbs.sh <test`      |                将输入重定向到 file                 |
|     `n>file`     |      `ls -l 2>test`       |        将文件描述符为 n 的文件重定向到 file        |
|    `n>>file`     |      `ls -l 2>>test`      |  将文件描述符为 n 的文件以追加的方式重定向到 file  |
|      `n>&m`      |    `ls -l >test 1>&2`     | 将文件描述符为 n 的文件指向到文件描述符为 m 的文件 |
|     `<<tag`      |          `<<EOF`          |  将开始标记 tag 到结束标记 tag 之间的内容作为输入  |
|   `>/dev/null`   | `ls -l ababa 2>/dev/null` |      将输出重定向到 /dev/null ，不会显示内容       |

**代码块重定向** ：

```shell
read -a arr <in # 在in中读取一行分割后存入arr
for n in ${arr[@]} 
do
	((sum += n))
	echo $n
done >out # 输出重定向到out
echo $sum
```

**Here Document** ：

```shell
# command <<delimiter
# 	  document
# delimiter
cat <<EOF
	aaa
	bbb
EOF
```

**管道** ：

```shell
command1 | command2 [ | commandN ...]
# command1的输出定向到command2的输入，以此类推
```

## Linux 常用命令

**Tab** ：自动补全参数。

**$\uparrow\downarrow$** ：切换上/下次命令。

**ctrl + r (reverse-i-search)** ：输入关键字后反向搜索最近命令。

**ctrl + w (word)** ：删除光标最后一个单词。

**ctrl + b (backward)** ：光标向后移动一个单词。

**ctrl + f (forward)** ：光标向前移动一个单词。

**ctrl + a (ahead)** ：光标移动到行首。

**ctrl + e (end)** ：光标移动到行末。

**ctrl + u (unix-line-discard)** ：剪切光标往前的所有内容。

**ctrl + k (kill)** ：剪切光标往后的所有内容。

**ctrl + y (yank)** ：粘贴之前剪切的内容。

**ctrl + l (clear)** ：清除屏幕。

**alt + .** ：使用前一个命令的参数。

**history** ：查看历史命令。

**!n** ：执行编号为 n 的命令。

**cd ~** ：进入 home 目录，`~/.bashrc` 访问 home 目录文件。

**cd -** ：进入上一次的目录。

**dirs [-v] [-c]** ：显示目录栈，栈顶是当前目录，`-v` 按行显示并带编号，`-c` 清空栈。

**pushd [dir | +N] (push directory)** ：`dir` 压入一个目录，`+N` 表示让编号为 N 的目录成为栈顶（切换到该目录）。

**popd [+N] (pop directory)** ：`+N` 表示弹出编号为 N 的目录。

**ctrl + a, #, enter** ：注释该行命令并执行，可以在历史命令找到。

**echo** ：