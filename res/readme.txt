热更新打包列表：
ui
cfg
music（待定）
image部分
armature
proto

固定在apk发布包中的路径
fonts
image部分
music（待定）
video

默认的search path：
vector<string> searchpath;
searchpath.push_back("fonts");
searchpath.push_back("image");
searchpath.push_back("video");

热更新添加的搜索路径：
auto writebalepath = getWritebalePath();
searchpath.push_back(writebalepath);
searchpath.push_back(writebalepath + "ui");
searchpath.push_back(writebalepath + "cfg");
searchpath.push_back(writebalepath + "music"); 
searchpath.push_back(writebalepath + "image");
searchpath.push_back(writebalepath + "armature");
//ui、cfg和armature路径可以不添加，都是热更新来的只有一处，在代码中的binWidget("ui/" .. name)或者
  require("cfg/card")中添路径
//如果music发布包后不会再变，这个移到apk默认的searchpath里，music路径也可不添加进去，在
  代码中getMusic()，getSound()时候添加，减少个搜索路径提高点效率

proto文件夹是在luapb中根据热更新上来的main.lua的路径设置的MapPath，不需要设置搜索路径