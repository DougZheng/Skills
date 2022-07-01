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
do
	echo $i
done
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

### 快捷参考

**man** [-k] term **(manual)** ：查看 `term` 的使用，`-k` 显示匹配关键字的简要描述。

**help** [-d] term：查看 shell 内置命令的使用，`-d` 简要显示用途。

**type** [-a] term ：查看命令类型，可执行文件、shell 内置命令或别名，`-a` 查看全部。

term **--help** ：查看命令的具体用法。

### 快捷命令

**Tab** ：自动补全参数，若有多选项则按两次 `tab` 后出现选项。

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

**ctrl + a, #, enter** ：注释该行命令并执行，可以在历史命令找到。

**{ }** ：路径展开，如  `/tmp/{x/{a,b},y,z}` 展开为 `/tmp/x/a,/tmp/x/b,/tmp/y,/tmp/z` 。

**\*** ：匹配任意数量的字符，如 `.*` 匹配任意后缀。

**?** ：匹配单个字符。

**[ ]** ：匹配指定范围内的任意单个字符，如 `[a-zA-Z], [0-9], [ax19]` 等。

**[^ ]** ：匹配除指定范围的任意单个字符，如 `[^a-zA-z], [^02468abc]` 等。

### 目录切换

**ls** [-a] [-l] [dir] **(list)** ：列出 `dir` 目录下的所有文件，默认为 . ，`-a` 列出包括隐藏文件和 . 及 .. ，`-l` 以长格式列出具体信息。

**pwd (print working directory)** ：打印当前目录路径。

**cd** [dir] **(change directory)**：切换到 `dir` ，`~` 为 home 目录（`~/.bashrc` 访问 home 目录下文件），`-` 为上一次目录。

**dirs** [-v] [-c] **(directories)**：显示目录栈，栈顶是当前目录，`-v` 按行显示并带编号，`-c` 清空栈。

**pushd** [dir | +N] **(push directory)** ：`dir` 压入一个目录，`+N` 表示让编号为 N 的目录成为栈顶（切换到该目录）。

**popd** [+N] **(pop directory)** ：`+N` 表示弹出编号为 N 的目录。

### 进程管理

**ps** [-e] [-f] **(processes)** ：打印进程状态，`-e` 打印所有进程（包括其他终端），`-f` 打印全格式。

**pstree** [-p] **(processes tree)** ：打印进程树状图，`-p` 打印 pid 。

**ctrl + z** ：将当前进程放到后台并挂起。

**ctrl + c** ：中止前台进程。

**ctrl + d** ：EOF ，文件终止符。

**\&** ：加在命令最后，可以将该命令放到后台执行。

**nohup** command \& **(no hang up)** ：在后台不挂起运行命令，退出终端不会影响，默认将输出定向 `./nohup.out` 。

**jobs** [-l] ：查看后台进程，`-l` 显示 pid 。

**fg** n **(foreground)** ：将 jobid 为 n 的进程调到前台执行。

**bg** n **(background)** ：让 jobid 为 n 的进程在后台执行。

**kill** [-9 | -19 | -l] [%n | pid] ：正常停止一个进程，`-9` 强制杀死，`-19` 挂起进程，`-l` 查看支持的信号，`%n` 指代 jobid 为 n 的进程。

**top** ：动态显示进程 cpu 、内存等使用情况，`P` 按 cpu 占比降序排列。

**free** ：查看内存情况。

### 文件管理

**mkdir** [-p] [-v] dir **(make directory)** ：创建目录 `dir` ，`-p` 自动创建所需父目录，`-v` 打印创建信息。

**rmdir** [-p] [-v] dir **(remove directory)** ：移除空目录 `dir` ，`-p` 自动移除空的父目录，`-v` 打印移除信息。

**cp** [-i] [-R] [-f] [-a] source dest **(copy)** ：复制文件 `source` 到 `dest`，`-i` 为覆盖提示，`-R` 递归复制，`-f` 强制，`-a` 即 `-dpr` 保留链接、文件属性，并递归复制目录下所有内容。

**cp** source... directory ：多源复制到目录 `directory` 下。

**mv** [-i] [-f] source dest **(move)** ：移动文件（可用于改名），`-i` 为覆盖提示，`-f` 强制。

**mv** source... directory ：多源复制到目录 `directory` 下。

**rm** [-i] [-R] [-f] file... **(remove)** ：移除文件，`-i` 为提示，`-R` 递归移除，`-f` 强制。

**cat** [-n] file **(concatenate)** ：连接文件 `file` 并打印到标准输出设备上，`-n` 为行编号。

**more** file ：类似 cat ，以分页形式打印 `file`，不能向前翻页。

**less** [-f] [+F] file ：以分页形式查看 `file` ，可向前向后翻页。`-f` 强制打开，`+F` 行为类似 `tail -f` ，但可中断，按 `F` 继续。

**head** [-n +k | -n -k] file ：默认输出 `file` 的前十行，`-n +k` 输出前 `k` 行，`-n -k` 输出文件头至倒数第 `k` 行的内容。

**tail** [-n +k | -n -k] [-f] file ：默认输出 `file` 的末十行，`-n -k` 输出末 `k` 行，`-n +k` 输出第 `k` 行至文件末尾的内容，`-f` 动态输出文件末尾增长的内容。

**touch** [-c] [-a] [-m] [-t [[CC]YY]MMDDmm[.ss]] file... ：可用于创建新文件 `file` ，`-c` 强制不创建。文件存在则修改时间戳。`-a` 修改 access time ，`-m` 修改 modify time ，change time 修改为当前系统时间 ，`-t` 指定修改为某个时间戳。

**stat** file **(status)** ：查看 `file` 的元数据信息（ inode 信息）。

**file**  file... ：查看 `file` 的类型。

**ln** [-s] target link_name **(link)** ：为 `target` 建立链接 `link_name` ，默认为硬链接，`-s` 表示符号链接（软链接）。

**find** file [-name "pattern"] ：查找 `file` 中的文件，`-name "pattern"` 查找所有文件名符合 `pattern` 的文件。

### 权限控制

**chmod** [-R] [-v] abc file... ：修改 `file` 权限，`abc` 为八进制数，分别代表 ugo 的权限，`-R` 递归作用，`-v` 打印变更信息。

**chmod** [-R] [-v] [ugoa]\[+-=]\[rwx] file...  **(change mode)**  ：修改 `file` 权限，`ugoa` 代表 user ，group ，other 和 all 。 

**chgrp** [-R] [-v] group file... **(change group)** ：修改 `file` 所属组为 `group` ，`-R` 递归作用，`-v` 打印变更信息。 

**chown** [-R] [-v] [user[:group]] file... **(change owner)** ：修改 `file` 所有者为 `user` ，所属组为 `group` 。

### 文件压缩

| 文件格式   | 命令                                         | 说明                                                         |
| ---------- | -------------------------------------------- | ------------------------------------------------------------ |
| `.tar`     | `tar -cvf test.tar file...`                  | `-c` ，打包，将 `file` 打包成 `test.tar`                     |
| `.tar`     | `tar -xvf test.tar [file...] [-C path]`      | `-x` ，解包，`file...` 解包部分文件，`-C path` 解包到指定目录 |
| `.tar`     | `tar -tvf test.tar`                          | `-t` ，查看 `test.tar` 内的文件                              |
| `.gz`      | `gzip -kv file...`                           | 压缩 `file...` 为 `.gz` 格式，不能压缩目录，`-k` 保留原文件  |
| `.gz`      | `gunzip -kv file...`                         | 解压 `.gz` 格式的 `file...` ，`-k` 保留原文件，`-v` 打印详细信息 |
| `.bz2`     | `bzip2 -kv file...`                          | 压缩 `file...` 为 `.bz2` 格式，不能压缩目录，`-k` 保留原文件 |
| `.bz2`     | `bunzip2 -kv file...`                        | 解压 `.bz2` 格式的 `file...` ，`-k` 保留原文件，`-v` 打印详细信息 |
| `.tar.gz`  | `tar -zcvf test.tar.gz file...`              | `-c` 打包，`-z` 压缩为 `.gz` 格式                            |
| `.tar.gz`  | `tar -zxvf test.tar.gz [file...] [-C path]`  | `-x` 解包，`-z` 解压缩 `.gz` 格式                            |
| `.tar.bz2` | `tar -jcvf test.tar.bz2 file...`             | `-c` 打包，`-j` 压缩为 `.bz2` 格式                           |
| `.tar.bz2` | `tar -jxvf test.tar.bz2 [file...] [-C path]` | `-x` 解包，`-j` 解压缩 `.bz2` 格式                           |

### 文本处理

**wc** [-l] [-w] [-c] [-m] file... **(word count)** ：统计 `file` 行数、词数、字节数，`-l` 行数，`-w` 词数，`-c` 字节数，`-m` 字符数。

**sort** [-r] [n] [-u] [-o file] file... ：对 `file` 的行按字典序排序并输出，`-r` 逆序，`-n` 按数值排序，`-u` 去重，`-o file` 结果存到 `file` 。

**uniq** [-d] [-u] [-c] file... **(unique)** ：对 `file` 的相邻行去重并输出，`-d` 仅打印重复的行，`-u` 仅打印不重复的行，`-c` 打印重复次数。

**cut** [-b -n] [-c] [-d 'char' -f] N file... ：对 `file` 进行列切割，`-b -n` 按字节，`-c` 按字符，`-d 'char' -f` 按 `char` 分隔，`N` 指示列。

**paste** [-d 'char'] file... ：对 `file` 按列合并，`-d 'char'` 按 `char` 分隔，`-` 可用指代标准输入。

**egrep** [option] pattern file... **(extended grep)**：查找 `file...` 中符合 `pattern` 的字符串。

| 选项   | 说明                                             |
| ------ | ------------------------------------------------ |
| `-i`   | 忽略大小写                                       |
| `-v`   | 反过来，只打印不匹配的                           |
| `-n`   | 打印匹配的行号                                   |
| `-w`   | 只能匹配单词，不能匹配单词的一部分               |
| `-c`   | 结果是匹配的行数                                 |
| `-o`   | 只打印匹配的字符串，而不是整行                   |
| `-A n` | 打印匹配的字符串所在行及后 `n` 行（after）       |
| `-B n` | 打印匹配的字符串所在行及前 `n` 行（before）      |
| `-C n` | 打印匹配的字符串所在行及前后各 `n` 行（context） |

tips ：若 `pattern` 不使用正则表达式，可用 `fgrep` **（fixed grep）**提高查找速度。

**awk** ：

**sed** **(stream editor)** ：

### 远程登录

**ssh** [-l login_name] destination ：远程登录，`-l` 指定登录用户名 `login_name` 。

### 磁盘管理

**df** [-h] [-i] [-T] **(disk free)** ：查看文件系统磁盘可用空间，`-h` 以人易阅读的形式显示，`-i` 用 inode 数量显示，`-T` 显示文件系统类型。

**du** [-h] [-s] file **(disk usage)** ：查看 `file` 使用空间情况，`-h` 以人易阅读的形式显示，`-s` 对每个子目录列出总量。

**fdisk** [-l] ：列出所有分区。（识别 u 盘）

**mount** source directory ：将 `source` 挂载到 `directory` 下。如 `mount /dev/sdb /mnt/usb` 。

**umount** directory **(unmount)** ：卸载 directory ，如 `umount /mnt/usb` 。

### 网络相关

**ping** [-c count] dest ：发送 ICMP 报文到 `dest` ，检查网络连通性， `-c count` 指定发送 `count` 个。

**tracepath** dest ：追踪到 `dest` 的每一跳路由。

**mtr** dest ：`ping` 和 `tracepath` 命令的整合。

**host** hostname ：解析域名 `hostname` 。

**netstat** [-a] [-t] [-u] ：查看各端口网络连接情况，`-a` 查看所有连接（包括监听），`-t` 显示 tcp 连接，`-u` 显示 udp 连接。

**ip** ：mark 。

**dig** ：mark 。

**tcpdump** ：mark 。

**wget** [-c] url ：从 `URL` 下载文件，`-c` 支持断点续传。 

**scp** [-r] source... dest ：将 `source` 传输到 `dest` ，`-r` 递归作用。

**rsync** [-a] [-v]  source... dest ：将差异文件从 `source` 同步到 `dest` ，`-a` 递归且保持文件属性，`-v` 输出详细信息。

### 实用命令

command | **xargs** [option] command **(extended arguments)** ：传递参数，用于组合多个命令，将前面的管道输出转成命令参数。

`xargs` 默认执行 `echo` ，但会过滤换行和空白，转换后参数以空格分隔，`-0` 将 NULL 作为分隔符。

`-nN` 每行使用至多 `N` 个参数，`-p` 用于交互，`-I` 指定一个替换字符串 `{}` ，用于多参数指示替换位置，此时 `{}` 被参数替换。

例： `ls *.jpg | xargs -p -I {} cp {} /data/images` 。 

**uptime** [-s] [-p] ：查看系统负载情况，`-s` 打印系统启动时间，`-p` 以易阅读形式打印系统运行时间。

**/usr/bin/time** [-v] command ：查看 `command` 执行时间，`-v` 显示详细信息。

**systemctl** [start|stop|restart|status] {services} ：启动、停止、重启、查看服务。

### vsftpd 配置

**服务器端**

安装 vsftpd `apt-get install vsftpd` 。 

出现错误 Unable to locate package vsftpd，`apt-get update` 后再尝试 `apt-get install vsftpd` 。

安装完成后启动 vsftpd 服务 `systemctl start vsftpd` 。

新建用户目录 `mkdir/home/uftp` 。

新建用户 uftp 作为 vsftpd 访问用户 `useradd -d /home/uftp -s /bin/bash uftp` 。

设置用户 uftp 密码 `passwd uftp` 。

修改用户目录所属者和所属组 `chown uftp:uftp /home/uftp` 。

修改用户目录权限为 `chmod 555 /home/uftp` （无写权限）。

新建文件 /etc/vsftpd.user_list 存放可访问 ftp 的用户 `vim /etc/vsftpd.user_list` 并添加内容 uftp 。

打开 vsftpd 配置文件 /etc/vsftpd.conf `vim /etc/vsftpd.conf` ，修改以下内容（有则修改，无则新增）：

```
listen=YES
listen_port=21
listen_ipv6=NO
anonymous_enable=NO
local_enable=YES
write_enable=YES
local_umask=022
connect_from_port_20=YES
chroot_local_user=YES # 限定用户不能访问上层目录，用户根目录不能有写权限
userlist_file=/etc/vsftpd.user_list
userlist_enable=YES
userlist_deny=NO
```

重启 vsftpd 服务 `systemctl restart vsftpd` 。

**客户端**

进入 ftp 命令 `ftp` 。

连接服务器 `open` 。

上传数据 `send` 。

## zsh 使用

**zsh 安装**

`yum install zsh` 安装 zsh 。

`cat /etc/shells` 查看已安装的 shell 。

`chsh -s /bin/zsh` 切换并设置默认 shell 。

**on-my-zsh 安装**

```
sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```

**修改主题**

`ls ~/.oh-my-zsh/themes/` 查看可用主题。

`vim ~/.zshrc` 修改 `ZSH_THEME` 字段值更换主题，记得 `source ~/.zshrc` 使变更生效。

**参考**

https://www.cnblogs.com/jie-fang/p/13437335.html

有空继续捣鼓。

## 参考文档

- https://github.com/jlevy/the-art-of-command-line/blob/master/README-zh.md
- https://explainshell.com/

