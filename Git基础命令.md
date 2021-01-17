以下内容搬运自[廖雪峰的git教程](https://www.liaoxuefeng.com/wiki/896043488029600)
##说明
该文档仅用于初期自己熟悉命令以及练习书写md文档；  
你们可以看一下参考，也可以自己网上查；  
后期该文档可能会删除。
#Git教程
|操作|对应命令|备注|
|:---|:---|:---:|
|将文件添加到仓库|`git add filename`|	可以多次添加后，统一commit提交
|将文件提交到仓库|`git commit -m "message"`|
|查看当前文件状态|`git status`|
|		|
|查看文件与上次提交的变化|`git diff`|
|查看提交历史记录|`git log`|
|回退上一个版本|`git reset --hard HEAD^`|
|撤销提交的修改|`git checkout -- filename`|
|删除文件|`git rm filename`|

### [分支管理](https://www.liaoxuefeng.com/wiki/896043488029600/896954848507552) 
这部分很重要，但我还没有完全理解

|操作|对应命令|备注|
|:---|:---|:---:|
|克隆远程仓库|`git clone git@gitee.com:e202-xd01/XD01-2021TI.git`|尽量使用SSH协议，速度比https快|
|创建dev分支并切换到dev分支|`git checkout -b dev`  或者`git switch -c dev`|我们平时的代码都在dev分支中提交；master为发布版本主分支|
|创建分支|`git branch dev`|	|
|切换分支|`git checkout dev`|	|
|查看分支|`git branch`|当前分支前会有一个`*`号|
|合并指定分支到当前分支|`git merge dev`|合并dev分支到当前分支|
|删除分支|`git branch -d dev`|

#### 多人协作
|操作|对应命令|备注|
|:---|:---|:---:|
|查看远程库的信息|`git remote`|查看更详细的信息`git remote -v`|
|推送分支到远程库|`git push origin master`|通常将master分支，dev分支，（合作开发）feature分支与远程同步|

### [标签管理](https://www.liaoxuefeng.com/wiki/896043488029600/902335212905824) 

|操作|对应命令|备注|
|:---|:---|:---:|
|添加标签|`git tag <name>`|标签是便于查看，如 `git tag v1.0`;默认标签是打在最新提交的commit上的,方便我们回档|
|删除标签|`git tag -d v0.1`|
|推送某个标签|`git push origin <tagname>`|
|推送所有本地标签|`git push origin --tags`|


*未完待续*