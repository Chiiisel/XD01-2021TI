# HMI向单片机发送数据的格式

​		为方便开发，现规定HMI发送到单片机的数据格式如下。

#### 格式

​		**page+label+cmd**

​		**page**意为该指令发出的页面序号。

​		**label**意为该指令是当前页面的第几个指令。

​		**cmd**意为指令的具体内容。



​		label通过 **变量** 控件定义。设置变量为私有（只有当前页面可用）、数值类型，并赋值。

![image-20210214192929694](C:\Users\27321\AppData\Roaming\Typora\typora-user-images\image-20210214192929694.png)





#### 举例

​		在这个例子中page0一共有两个按钮b0,b1，一个开关sw0，一个滑块h0，其中开关和滑块没有实际作用，只做演示用。

​		新建四个私有变量，b0_cmd、b1_cmd、sw0_cmd、h0_cmd，其val值分别为1、2、3、4。

![image-20210216181556382](C:\Users\27321\AppData\Roaming\Typora\typora-user-images\image-20210216181556382.png)

​		在按钮b0的弹起事件中输入：

```C
printh 00              //0x00表示是page0（page）
prints b0_cmd.val,1    //发送指令标签（label），长度为1Byte
printh 00 00 00 00     //指令内容（cmd），长度为4Byte

page 1				   //进入对应的页面
```

​		由于按钮b0只有“按下”这一种动作，其没有val属性，所以按钮的cmd统一定为 00 00 00 00。

​		而对于开关sw0，它有开和关两种状态，有val属性，其cmd即为sw0.val。

​		对于滑块h0，它有更多种状态，取决于滑块val的范围，其cmd也为h0.val。

​		**即有val属性的控件，其cmd值为其val属性，没有val属性的控件，其cmd值统一定为00 00 00 00**

​		如在滑块h0的弹起事件中输入：

```C
printh 00				//page
prints h0_cmd.val,1		//label
prints h0.val,0			//cmd，自动长度，实际为4Byte
```

#### 调试运行

​		滑块h0范围0-1023，滑动滑块h0到头，模拟器返回数据00 04 FF 03 00 00。一共6Byte，分别对应page、label、cmd。

​		这里返回cmd=FF 03 00 00，可以看出HMI发送数据时是先发低位，再发高位，实际是00 00 03 FF 即1023。

![image-20210216183021922](C:\Users\27321\AppData\Roaming\Typora\typora-user-images\image-20210216183021922.png)

​		按下按钮b0(MPU6050)，进入到对应页面，模拟器返回00 01 00 00 00 00。

![image-20210216183259652](C:\Users\27321\AppData\Roaming\Typora\typora-user-images\image-20210216183259652.png)				按下返回(page1的b0)，模拟器返回01 01 00 00 00 00。

![image-20210216183432524](C:\Users\27321\AppData\Roaming\Typora\typora-user-images\image-20210216183432524.png)