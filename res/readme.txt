�ȸ��´���б�
ui
cfg
music��������
image����
armature
proto

�̶���apk�������е�·��
fonts
image����
music��������
video

Ĭ�ϵ�search path��
vector<string> searchpath;
searchpath.push_back("fonts");
searchpath.push_back("image");
searchpath.push_back("video");

�ȸ�����ӵ�����·����
auto writebalepath = getWritebalePath();
searchpath.push_back(writebalepath);
searchpath.push_back(writebalepath + "ui");
searchpath.push_back(writebalepath + "cfg");
searchpath.push_back(writebalepath + "music"); 
searchpath.push_back(writebalepath + "image");
searchpath.push_back(writebalepath + "armature");
//ui��cfg��armature·�����Բ���ӣ������ȸ�������ֻ��һ�����ڴ����е�binWidget("ui/" .. name)����
  require("cfg/card")����·��
//���music�������󲻻��ٱ䣬����Ƶ�apkĬ�ϵ�searchpath�music·��Ҳ�ɲ���ӽ�ȥ����
  ������getMusic()��getSound()ʱ����ӣ����ٸ�����·����ߵ�Ч��

proto�ļ�������luapb�и����ȸ���������main.lua��·�����õ�MapPath������Ҫ��������·��