现在还有2个问题： 早上说的我们假设输入：1.影像点开始编号,2.影像总数，3.行数、列数；
现在我想的是tpc文件作为排好的数据仓库，根据我们得输入条件，赛选出部分影像，做成xpf文件；
我用（m,n)表示tpc中的一个影像，
假如我输入从5号开始编号，总数9，行3，列4，那么

排列是：
(1,2)(1,3)(1,4)(1,5)
(1,9)(1,8)(1,7)(1,6)
(1,10)

这样子， 生成的xpf文件中，差不多就是这个样子：

$PHOTO
$PHOTO_NUM : 005
$PHOTO_POINTS: 
(1,2)
$END_POINTS
$END 

PHOTO
$PHOTO_NUM : 006
$PHOTO_POINTS: 
(1,3)
$END_POINTS
$END

……

$PHOTO
$PHOTO_NUM : 009
$PHOTO_POINTS: 
(1,9)
$END_POINTS
$END

$PHOTO
$PHOTO_NUM : 010
$PHOTO_POINTS: 
(1,8)
$END_POINTS
$END
…

这样的顺序生成的xpf文件；不知道理解的对不对，
还有，就是tpc文件转到xpf文件之后，tpc文件中得行列信息丢掉了，
xpf文件中的ADJUSTED_POINTS 矫正点，这组信息是什么？是如何算出来的，有啥作用，

====================================