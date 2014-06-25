#ifndef HGL_PROC_FIFO_INCLUDE
#define HGL_PROC_FIFO_INCLUDE
namespace hgl
{
	/**
	 * 命名管道通信
	 */
	class Fifo																						///命名管道通信
	{
	public:

		char filename[1024];

		int fd;

	public:

		Fifo()
		{
			*filename=0;
			fd=-1;
		}

		bool Create(const char *);																	///<创建一个管道通信文件(注：只需要文件名，不需要完整路径)
	};//namespace hgl
}//namespace hgl
#endif//HGL_PROC_FIFO_INCLUDE
