## 项目报告 - `MYGO!!!!!` 小游戏

- 注意，不需要下载图形库就可以运行的游戏 `.exe` 文件在 `build` 文件夹；用编译指令直接编译出来的应用程序在 `src` 文件夹，应该需要电脑内置图形库运行环境才能运行。

- 操作系统：Windows 11
- 图形库：SDL 2
- C 语言环境：
	- GCC version 12.1.0; 
	- C 17; 
	- 编译器：Visual Studio Code, 版本：1.84.2
	- 编译指令：进入 `./src` 目录下后输入指令 `if ($?) { gcc GO_on.c game.c menu.c ./utils/display.c ./utils/audio.c ./utils/linkedlist.c ./utils/input.c -o GO_on -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -lSDL2_image } ; if ($?) { .\GO_on }`
- 操作方法：
	- 开始菜单中
		- 按键 `w` `s` 或 `↑` `↓` 选择选项，
		- 按键 `space` 或 `enter` 确认选项
		- `Start Game`: 开始游戏，进入二级菜单选择人物
		- `Exit Game`: 结束游戏 
	- 二级菜单：操作逻辑与开始菜单相同，五个人物可供选择~ 按 `esc` 返回主菜单~
	- 进入游戏：横向三条道路，按 `c` 蹲下， `space` 跳跃，`w` 和 `s` 切换道路。道路中有如下五种元素（*roadblocks*）：(*斜体字*为在代码中的名字)
		- 黑洞 (*blackhole*): 产生无法逃脱的强大重力场！只能切换道路
		- 单行道（一方通行）指示牌 (*jumpblock*): 可以跳跃躲过
		- 道闸 (*rollblock*): 可以翻滚躲避
		- 金币 (*coin*): 加 `1` 分
		- 抹茶芭菲 (*parfait*): 加 `5` 分，同时给予 ` 5s ` 无敌 (*invincible*)时间
	- 暂停菜单：开始游戏后按 `esc` 进入暂停菜单，菜单操作逻辑与之前一样，共三种选项：
		- `back to game`: 无缝回到游戏继续游玩
		- `back to menu`: 回到主菜单，之前的游戏进度不会保存
		- `exix game`: 直接退出游戏
	- 结算画面：显示温馨寄语，游戏分数与存活时间。按 `任意键` 打断施法回到主菜单。


- 写在后面：
	- `src` 文件夹里面提供了编译好的游戏可执行文件 `GO_on.exe`
	- 更适合 go 批体质的 `MYGO!!!!!` 小游戏；为不同人物出场、动作、死亡、吃道具做了足够多样的~~够使~~音效，请品鉴
	- 菜单音乐来自 b 站视频 `BV1Qz4y1x7h7`，菜单鼠标来自 b 站视频 `BV1xN4y1f7H3`
	- 本质上是~~引流~~二创，做的图一乐，也确实做得很开心。年后应该会完善一下游戏，加入更多~~更唐~~的内容！
	- 感谢耐心回答我愚蠢或不愚蠢问题的朋友和助教，感谢助教录的知识密度 `>=` 黑洞密度的视频，祝大家新年快乐喵~