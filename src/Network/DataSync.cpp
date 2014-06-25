﻿/*

数据同步对象设计：

同步：
	1.简单的一对一对同步
	2.单向或双向(如玩家自身数据)同步
	3.一对多同步(如同屏玩家数据群发)

数据：
	1.原生数据直接memcpy
	2.复合数据使用LoadFromStream/SaveToStream实现

同步原理：
	1.为每一个数据产生一个计数器，并依次加1，如有A,B,C三个数据,则计数全部为0或0,1,2，并记录最大更新计数为2
	2.当某个数据更新时，最大计数器+1变为3，并为相应数据的计数器更新为最大计数器
	3.被同步者提交自身最新数据计数器数据，如为1，则将>1的所有数据发送给被同步者
*/
