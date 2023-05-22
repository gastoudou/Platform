#ifndef __SINGLETON_H__
#define __SINGLETON_H__

/// GS_Singleton
/// This class ensures a class has one instance, and provides a global point of access to it
template< class T >
class GS_Singleton
{
public:
	static T* getInstance()
	{
		static T s_instance;
		return &s_instance;
	}

protected:
	GS_Singleton()
	{
	}

	virtual ~GS_Singleton()
	{
	}

private:
	GS_Singleton( GS_Singleton const& ) = delete;
	GS_Singleton& operator=( GS_Singleton const& ) = delete;
};

#endif