#include"zlog.h"

int main(void)
{
	Zlog zlog;
	zlog.w("start", "begin", 0, Zlog::OPEN_TYPE::OVER);
	zlog.p(1, 111, __LINE__);
	zlog.p("tag", "msg", __LINE__);
	zlog.w(1, 111, __LINE__);
	zlog.w("tag", "msg", __LINE__);

	return 0;
}