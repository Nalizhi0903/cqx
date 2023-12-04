#include <qapplication.h>
#include <qlabel>
//第一行和第二行包含了类 QApplication和Label的定义。对于每个Qt类，都有一个与该类同名的头文件，在这个头文件中包括了对该类的定义。

int main(int argc, char* argv[])
{
	//创建了一个Qapplication的对象，用来管理整个应用程序所用用到的资源，构造函数需要两个参数，分别是argc 和argv ，因为 Qt 支持它自己的一些命令行参数。
	QApplication app(argc, argv);
	//创建了一个显示 "Hello Qt!"的 Label 窗口部件(widget)
	QLabel* label = new QLabel("Hello Qt");
	//使label标签可见，在创建窗口部件的时候，标签通常是隐藏的
	label->show();
	//行将应用程序的控制权传递给Qt 此时，程序会进入事件循环状态，这是一种等待模式，程序会等候用户的动作
	return app.exec();
}
