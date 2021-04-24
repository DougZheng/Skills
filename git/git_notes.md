**创建版本库**
```cpp
git init // 创建版本库
```
**提交修改**
```cpp
git add <path> // 添加文件到暂存区
git add . // 新增/修改的添加到暂存区
git add -A // 新增/修改/删除的
git commit -m <msg> // 提交暂存区的文件
```
**撤销修改**
```cpp
git restore <path> // 版本库版本覆盖工作区版本
git restore --staged <path> // 撤销暂存区的修改
```
**版本管理**
```cpp
git status // 查看状态
git diff <path> // 查看文件内容变更情况
git log [--pretty=oneline] // 查看版本
git log [--oneline] [--graph] // 简化
git reset --hard <commit> // 回退到指定版本
git revert -n <commit> // 反做（撤销）某版本
git reflog // git历史命令记录
```
**添加远程库**
```cpp
git remote [-v] // 查看本地添加了哪些远程分支地址
git remote add origin <repository> // 关联远程仓库
git push -u origin master // -u参数指定默认远程主机origin，后续直接push
```
**克隆远程库**
```cpp
git clone <repository> // 克隆远程库
```
**分支管理**
```cpp
git branch -r // 查看分支
git branch <branchname> // 创建分支
git switch <branchname> // 切换到分支
git switch -c <branchname> // 创建并切换分支
git merge <branchname> // 合并分支到当前分支
git branch -d <branchname> // 删除分支
git log --graph // 查看分支合并图
git merge --no-ff [-m <msg>] <branchname> // 通过一个commit来合并分支，可以有历史合并信息
git fetch origin master:<branchname> // 拉取最新内容到本地branch分支
git pull origin master // 拉取并与本地分支合并（fetch + merge）
```
**$\text{bug}$ 分支**
```cpp
git stash // 隐藏暂存区内容
git stash list // 查看隐藏列表
git stash pop // 恢复并从隐藏列表中删除
git stash apply stash@{0} // 恢复指定的stash
git stash drop stash@{0} // 从隐藏列表中删除
git cherry-pick <commit> // 复制一个特定提交到当前分支  
git cherry-pick L^..R // 复制L..R的所有提到当前分支 
```